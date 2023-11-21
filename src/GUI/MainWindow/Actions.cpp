#include "MainWindow.hpp"
#include "Ui/UiMainWindow.hpp"
#include "GUI/Model/ProcessTableModel.hpp"
#include "Process/ProcessFetchers/Test/ProcessFetcherTest.hpp"

namespace details_
{
  ActionsHolder::ActionsHolder(MainWindow *mw) :
    mw_(mw),
    menu_(std::make_unique< QMenu >())
  {
    killAction_ = std::make_unique< ConditionAction >(tr("Kill"));
    killAction_->setIcon(mw->style()->standardIcon(QStyle::SP_DialogCancelButton));
    killAction_->addCheckFunction(
      [mw = this->mw_]() -> bool {
      auto selectedItems = mw->ui_->processTableView->selectionModel();
      return !selectedItems->selectedRows().empty();
    });
    actionsHolder_.push_back(killAction_.get());
    menu_->addAction(killAction_.get());
  }

  void ActionsHolder::showMenu(const QPoint &pos)
  {
    std::ranges::for_each(actionsHolder_, [](ConditionAction *action) {
      action->updateEnabled();
    });
    menu_->exec(QCursor::pos());
  }

  ActionsHolder::~ActionsHolder()
  { }
}
