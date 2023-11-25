#include "ProcTableSortProxy.hpp"
#include "GUI/Model/ProcessTableModel.hpp"

namespace details_
{
  ProcTableSortProxy::~ProcTableSortProxy() = default;

  bool ProcTableSortProxy::lessThan(const QModelIndex &left, const QModelIndex &right) const
  {
    using namespace process;
    auto leftProc = left.data(Qt::UserRole).value< Process >();
    auto rightProc = right.data(Qt::UserRole).value< Process >();
    auto model = static_cast<ProcessTableModel*>(sourceModel());
    auto leftObjField = model->toField(left.column());
    if (leftObjField == Field::PID)
    {
      return leftProc.pid() < rightProc.pid();
    }
    else if (leftObjField == Field::WORK_TIME)
    {
      return leftProc.time() < rightProc.time();
    }
    else if (leftObjField == Field::COMMAND)
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
