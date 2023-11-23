#ifndef PROC_TABLE_SORT_PROXY_HPP
#define PROC_TABLE_SORT_PROXY_HPP

#include <QSortFilterProxyModel>

namespace details_
{
  class ProcTableSortProxy: public QSortFilterProxyModel
  {
    Q_OBJECT
  public:
    virtual ~ProcTableSortProxy();
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
  };
}

#endif
