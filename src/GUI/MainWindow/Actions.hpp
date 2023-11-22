#ifndef ACITONS_HOLDER_HPP
#define ACITONS_HOLDER_HPP

#include <QMainWindow>
#include <QShortcut>
#include <memory>
#include "Utils/ConditionAction.hpp"

class MainWindow;

namespace details_
{
  class ActionsHolder: public QObject
  {
    Q_OBJECT
  public:
    ActionsHolder(MainWindow *mw);
    ~ActionsHolder();
    void showMenu(const QPoint &pos);

  private:
    MainWindow *mw_;
    std::unique_ptr< QMenu > menu_;
    std::unique_ptr< ConditionAction > refreshAction_;
    std::unique_ptr< QShortcut > refreshActShcut_;
    std::unique_ptr< ConditionAction > killAction_;
    std::unique_ptr< QShortcut > killActShcut_;
    std::vector< ConditionAction * > allActions_;
    void createKillAction();
    void createRefreshAction();
  };
}

#endif
