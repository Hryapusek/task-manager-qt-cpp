#include "MainWindow.hpp"
#include "Ui/UiMainWindow.hpp"
#include "GUI/Model/ProcessTableModel.hpp"
#include "Process/ProcessFetchers/Test/ProcessFetcherTest.hpp"
#include <QtDebug>

namespace details_
{
  ActionsHolder::ActionsHolder(MainWindow *mw) :
    mw_(mw),
    menu_(std::make_unique< QMenu >())
  {
    createKillAction();
    actionsHolder_.push_back(killAction_.get());
    menu_->addAction(killAction_.get());
  }

  void ActionsHolder::showMenu(const QPoint &pos)
  {
    std::ranges::for_each(actionsHolder_, [](ConditionAction *action) {
      action->updateIsEnabledFlag();
    });
    menu_->exec(QCursor::pos());
  }

  void details_::ActionsHolder::createKillAction()
  {
    killAction_ = std::make_unique< ConditionAction >(tr("Kill"));
    killAction_->setIcon(mw_->style()->standardIcon(QStyle::SP_DialogCancelButton));
    killAction_->addCheckFunction(
      [mw = this->mw_]() -> bool {
      auto selectedItems = mw->ui_->processTableView->selectionModel();
      return !selectedItems->selectedRows().empty();
    });
    killActShcut_ = std::make_unique< QShortcut >(QKeySequence::Delete, mw_->ui_->processTableView);
    connect(killActShcut_.get(), &QShortcut::activated, killAction_.get(), &ConditionAction::checkAndTrigger);
    connect(killAction_.get(), &QAction::triggered,
      [action = this->killAction_.get()]() {
      qDebug() << "Kill action";
      // TODO call kill
    });
  }

  ActionsHolder::~ActionsHolder()
  { }
}
