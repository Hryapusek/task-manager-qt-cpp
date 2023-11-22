#include "MainWindow.hpp"
#include "Ui/UiMainWindow.hpp"
#include "Actions.hpp"
#include "GUI/Model/ProcessTableModel.hpp"
#include "Process/ProcessFetchers/Test/ProcessFetcherTest.hpp"
#include <QtDebug>
#include <QMessageBox>
#include <ranges>

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
      [this]() {
      qDebug() << "Kill action";
      auto selectedItems = this->mw_->ui_->processTableView->selectionModel();
      auto selectedRows = selectedItems->selectedRows();
      std::vector< int > pids;
      pids.reserve(selectedRows.size());
      for (auto modelItem : selectedRows)
      {
        auto pidStr = modelItem.data(Qt::ItemDataRole::DisplayRole).toString();
        pids.push_back(pidStr.toInt());
      }
      for (auto pid : pids)
      {
        auto res = this->mw_->processTableModel_->kill(pid);
        if (!res)
        {
          auto errorMsg = tr("Can not kill the process.")
                          .append(" ")
                          .append(QString::fromStdString(res.error()));
          QMessageBox::critical(this->mw_, tr("Error"), errorMsg, QMessageBox::Close);
          continue;
        }
      }
    });
  }

  ActionsHolder::~ActionsHolder()
  { }
}
