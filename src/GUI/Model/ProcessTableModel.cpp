#include "ProcessTableModel.hpp"
#include <QMessageBox>
#include <QtDebug>

ProcessTableModel::ProcessTableModel(std::unique_ptr< ProcessFetcherI > processFetcher) :
  processFetcher_(std::move(processFetcher))
{
  auto res = processFetcher_->processes();
  if (!res)
    throw std::logic_error("Can not fetch processes\n");
  processes_ = std::move(*res);
}

int ProcessTableModel::rowCount(const QModelIndex &parent) const
{
  return processes_.size();
}

int ProcessTableModel::columnCount(const QModelIndex &parent) const
{
  return nColumns;
}

QVariant ProcessTableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid() || index.row() < 0 || index.row() > processes_.size())
    return QVariant();
  if (role == Qt::ItemDataRole::TextAlignmentRole)
  {
    return int(Qt::AlignmentFlag::AlignRight);
  }
  else if (role == Qt::ItemDataRole::DisplayRole)
  {
    const auto &process = processes_[index.row()];
    switch (Column::fromInt(index.column()))
    {
      case Column::PID:
        return process.pid();
        break;

      case Column::TIME:
      {
        auto time = process.time();
        std::tm *ptm = std::gmtime(&time);
        if (!ptm)
          return QString::fromUtf8("None");
        std::array<char, 15> buffer;
        auto size = std::strftime(buffer.data(), buffer.size(), "%H:%M:%S", ptm);
        return QString::fromUtf8(buffer.data(), size);
      }

      case Column::CMD:
        return QString::fromStdString(process.cmd());

      default:
        qDebug() << index.row() << " " << index.column() << '\n';
        return QVariant();
    }
  }
  else if (role == Qt::ItemDataRole::UserRole)
  {
    return QVariant::fromValue(processes_[index.row()]);
  }
  return QVariant();
}

QVariant ProcessTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::ItemDataRole::DisplayRole && orientation == Qt::Orientation::Horizontal)
  {
    auto columnName = Column::toString(Column::fromInt(section));
    return QString::fromStdString(std::move(columnName));
  }
  return QVariant();
}

Qt::ItemFlags ProcessTableModel::flags(const QModelIndex &index) const
{
  using flags = Qt::ItemFlag;
  return (Qt::ItemFlags() | flags::ItemIsEnabled | flags::ItemIsSelectable) & ~flags::ItemIsEditable;
}

std::expected< void, std::string > ProcessTableModel::kill(int pid)
{
  return processFetcher_->kill(pid);
}

std::expected< void, std::string > ProcessTableModel::refresh()
{
  auto newProcesses_ = processFetcher_->processes();
  if (!newProcesses_)
    return std::unexpected(std::move(newProcesses_.error()));
  auto oldProcesses = std::exchange(processes_, newProcesses_.value());
  mergeProcesses(std::move(oldProcesses));
  return { };
}

void ProcessTableModel::mergeProcesses(std::vector< Process > oldProcesses)
{
  int currentRow = 0;
  auto oldProcIt = oldProcesses.begin();
  auto &newProcesses = processes_;
  auto newProcIt = newProcesses.begin();
  while (oldProcIt != oldProcesses.end() && newProcIt != newProcesses.end())
  {
    if (oldProcIt->pid() < newProcIt->pid())
    {
      beginRemoveRows(QModelIndex(), currentRow, currentRow);
      removeRow(currentRow);
      endRemoveRows();
      ++oldProcIt;
    }
    else if (oldProcIt->pid() > newProcIt->pid())
    {
      beginInsertRows(QModelIndex(), currentRow, currentRow);
      insertRow(currentRow);
      endInsertRows();
      ++currentRow;
      ++newProcIt;
    }
    else if (oldProcIt->pid() == newProcIt->pid() && oldProcIt->cmd() != newProcIt->cmd())
    {
      dataChanged(index(currentRow, 0), index(currentRow, Column::lastColumn()));
      ++currentRow;
      ++oldProcIt;
      ++newProcIt;
    }
    else if (oldProcIt->pid() == newProcIt->pid() && oldProcIt->cmd() == newProcIt->cmd())
    {
      ++currentRow;
      ++oldProcIt;
      ++newProcIt;
    }
  }
  while (oldProcIt++ != oldProcesses.end())
  {
    beginRemoveRows(QModelIndex(), currentRow, currentRow);
    removeRow(currentRow++);
    endRemoveRows();
  }
  while (newProcIt++ != newProcesses.end())
  {
    beginInsertRows(QModelIndex(), currentRow, currentRow);
    insertRow(currentRow++);
    endInsertRows();
  }
}
