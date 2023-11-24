#include "MenuBarActions.hpp"
#include "MainWindow.hpp"
#include "Ui/UiMainWindow.hpp"
#include <QTimer>

namespace details_
{
  MenuBarActions::MenuBarActions(MainWindow *mw) :
    mw_(mw)
  { 
    connect(mw_->ui_->refreshOpt, &QAction::toggled, this, &MenuBarActions::toggleRefresh);
  }

  MenuBarActions::~MenuBarActions()
  {
  }
  
  void MenuBarActions::toggleRefresh(bool isEnabled)
  {
    if (isEnabled && !mw_->refreshTimer->isActive())
      mw_->refreshTimer->start();
    else if (!isEnabled && mw_->refreshTimer->isActive())
      mw_->refreshTimer->stop();
  }
}
