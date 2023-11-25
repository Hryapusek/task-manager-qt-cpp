#include "ProcessTableModel.hpp"
#include <QMessageBox>
#include <QtDebug>

namespace
{
  QString fieldToString(process::Field::Field_ col, const process::Process &process)
  {
    using namespace process;
    switch (col)
    {
      case Field::PID:
        return QString::fromStdString(std::to_string(process.pid()));

      case Field::WORK_TIME:
      {
        auto time = process.time();
        std::tm *ptm = std::gmtime(&time);
        if (!ptm)
          return QString::fromUtf8("None");
        std::array< char, 15 > buffer;
        auto size = std::strftime(buffer.data(), buffer.size(), "%H:%M:%S", ptm);
        return QString::fromUtf8(buffer.data(), size);
      }

      case Field::COMMAND:
        return QString::fromStdString(process.cmd());

      case Field::MEMORY:
        return QString::fromStdString(std::to_string(process.memory()));

      default:
        std::unreachable();
    }
  }
}

ProcessTableModel::ProcessTableModel(std::unique_ptr< process::ProcessFetcherI > processFetcher) :
  processFetcher_(std::move(processFetcher))
{
  auto res = processFetcher_->processes();
  if (!res)
  {
    QMessageBox::critical(nullptr, tr("Error"), tr("Can not fetch the processes. Programm will exit now"), QMessageBox::Close);
    std::terminate();
  }
  processes_ = std::move(*res);
  futureProcesses_ = std::async(&process::ProcessFetcherI::processes, processFetcher_.get());
  supportedFields_ = processFetcher_->supportedFields();
  assert(supportedFields_[0] == process::Field::PID);
}

int ProcessTableModel::rowCount(const QModelIndex &parent) const
{
  return parent.isValid() ? 0 : processes_.size();
}

int ProcessTableModel::columnCount(const QModelIndex &parent) const
{
  return parent.isValid() ? 0 : supportedFields_.size();
}

QVariant ProcessTableModel::data(const QModelIndex &index, int role) const
{
  using namespace process;
  if (!index.isValid() || index.row() < 0 || index.row() > processes_.size())
    return QVariant();
  auto field = toField(index.column());
  const auto &process = processes_[index.row()];
  if (role == Qt::ItemDataRole::TextAlignmentRole)
  {
    if (field != Field::COMMAND)
      return int(Qt::AlignmentFlag::AlignRight);
    return int(Qt::AlignmentFlag::AlignLeft);
  }
  else if (role == Qt::ItemDataRole::DisplayRole) [[likely]]
  {
    return fieldToString(field, process);
  }
  else if (role == Qt::ItemDataRole::UserRole)
  {
    return QVariant::fromValue(process);
  }
  return QVariant();
}

QVariant ProcessTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  using namespace process;
  if (orientation != Qt::Orientation::Horizontal)
    return QVariant();
  if (role == Qt::ItemDataRole::DisplayRole)
  {
    auto columnName = Field::toString(supportedFields_[section]);
    return QString::fromStdString(columnName);
  }
  else if (role == Qt::ItemDataRole::TextAlignmentRole)
  {
    return Qt::AlignmentFlag::AlignCenter;
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
  auto newProcesses_ = futureProcesses_.get();
  futureProcesses_ = std::async(&process::ProcessFetcherI::processes, processFetcher_.get());
  if (!newProcesses_)
    return std::unexpected(std::move(newProcesses_.error()));
  auto oldProcesses = std::exchange(processes_, newProcesses_.value());
  mergeProcesses(std::move(oldProcesses));
  return { };
}

std::vector<process::Field::Field_> ProcessTableModel::supportedFields() const
{
  return supportedFields_;
}

int ProcessTableModel::pidColumn() const
{
  // PID column must be the first
  return 0;
}

int ProcessTableModel::toColumn(process::Field::Field_ field) const
{
  const auto &arr = supportedFields_;
  return std::distance(arr.begin(), std::find(arr.begin(), arr.end(), field));
}

process::Field::Field_ ProcessTableModel::toField(int column) const
{
  assert(column < supportedFields_.size());
  return supportedFields_[column];
}

void ProcessTableModel::mergeProcesses(std::vector< process::Process > oldProcesses)
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
      dataChanged(index(currentRow, 0), index(currentRow, columnCount(QModelIndex())-1));
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
