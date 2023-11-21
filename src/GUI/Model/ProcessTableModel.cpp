#include "ProcessTableModel.hpp"
#include <QtDebug>

ProcessTableModel::ProcessTableModel(std::unique_ptr< ProcessFetcherI > processFetcher) :
  processFetcher_(std::move(processFetcher))
{
  processes_ = processFetcher_->processes();
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
        return QString::fromLocal8Bit("time");

      case Column::CMD:
        return QString::fromStdString(process.cmd());

      default:
        qDebug() << index.row() << " " << index.column() << '\n';
        return QVariant();
    }
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
  auto res = processFetcher_->kill(pid);
  if (!res)
    return res;
  auto processToRemove = std::ranges::find_if(processes_, [pid](auto proc) {
    return proc.pid() == pid;
  });
  assert(processToRemove != processes_.end());
  auto deletedRowNum = std::distance(processes_.begin(), processToRemove);
  processes_.erase(processToRemove);
  removeRow(deletedRowNum);
  layoutChanged();
  return {};
}
