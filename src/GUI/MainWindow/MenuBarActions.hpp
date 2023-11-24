#ifndef MENU_BAR_ACTIONS_HPP
#define MENU_BAR_ACTIONS_HPP

#include <QShortcut>
#include <memory>
#include "Utils/ConditionAction.hpp"

class MainWindow;

namespace details_
{
  class MenuBarActions: public QObject
  {
    Q_OBJECT
  public:
    MenuBarActions(MainWindow * mw);
    ~MenuBarActions();
    void toggleRefresh(bool value);
  private:
    MainWindow *mw_;
  };
}

#endif
