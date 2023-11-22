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
  return { };
}

std::expected< void, std::string > ProcessTableModel::refresh()
{
  auto res = processFetcher_->processes();
  if (!res)
    return std::unexpected(res.error());
  processes_ = std::move(res.value());
  dataChanged(index(0, 0), index(rowCount(QModelIndex()), columnCount(QModelIndex())));
  layoutChanged();
  return {};
}
