#ifndef PROCESS_TABLE_VIEW_HELPER_HPP
#define PROCESS_TABLE_VIEW_HELPER_HPP

#include <QObject>
#include "MainWindow.hpp"

namespace details_
{
  class ProcTableViewHelper: public QObject
  {
    Q_OBJECT

  public:
    ProcTableViewHelper(MainWindow *mw);

  private:
    MainWindow *mw_;
  };
}

#endif
