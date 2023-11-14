#include "ProcessTableModel.hpp"

ProcessTableModel::ProcessTableModel(std::unique_ptr< ProcessFetcherI > processFetcher) :
  processFetcher_(std::move(processFetcher))
{
  processes_ = processFetcher_->processes();
}

int ProcessTableModel::rowCount(const QModelIndex &parent) const
{
  return nColumns;
}

int ProcessTableModel::columnCount(const QModelIndex &parent) const
{
  return processes_.size();
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
      return QVariant();
    }
  }
  return QVariant();
}

QVariant ProcessTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::ItemDataRole::DisplayRole && orientation == Qt::Orientation::Vertical)
  {
    auto columnName = Column::toString(Column::fromInt(section));
    return QString::fromStdString(std::move(columnName));
  }
  return QVariant();
}

Qt::ItemFlags ProcessTableModel::flags(const QModelIndex &index) const
{
  return Qt::ItemFlags() & ~Qt::ItemFlag::ItemIsEditable;
}
