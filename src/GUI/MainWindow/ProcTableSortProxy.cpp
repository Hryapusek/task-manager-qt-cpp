#include "ProcTableSortProxy.hpp"
#include "GUI/Model/ProcessTableModel.hpp"

namespace details_
{
  ProcTableSortProxy::~ProcTableSortProxy() = default;

  bool ProcTableSortProxy::lessThan(const QModelIndex &left, const QModelIndex &right) const
  {
    auto leftProc = left.data(Qt::UserRole).value< Process >();
    auto rightProc = right.data(Qt::UserRole).value< Process >();
    if (left.column() == ProcessTableModel::Column::PID)
    {
      return leftProc.pid() < rightProc.pid();
    }
    else if (left.column() == ProcessTableModel::Column::TIME)
    {
      return leftProc.time() < rightProc.time();
    }
    else if (left.column() == ProcessTableModel::Column::CMD)
    {
      return leftProc.cmd() < rightProc.cmd();
    }
    else
    {
      assert(("Bro i dunno how but am sure you gotta fix dat. Comparing on unexisting column bro)))))", false));
    }
    std::unreachable();
  }
}
