#include "Actions.hpp"
#include "MainWindow.hpp"
#include "Ui/UiMainWindow.hpp"
#include "GUI/Model/ProcessTableModel.hpp"
#include "Process/ProcessFetchers/Test/ProcessFetcherTest.hpp"

#include <QtDebug>
#include <QMessageBox>
#include <ranges>
#include <mutex>

namespace details_
{
  ActionsHolder::ActionsHolder(MainWindow *mw) :
    mw_(mw),
    menu_(std::make_unique< QMenu >())
  {
    createRefreshAction();
    allActions_.push_back(refreshAction_.get());
    menu_->addAction(refreshAction_.get());

    createKillAction();
    allActions_.push_back(killAction_.get());
    menu_->addAction(killAction_.get());
  }

  void ActionsHolder::showMenu(const QPoint &pos)
  {
    std::unique_lock lock(mw_->procListMut_);
    std::ranges::for_each(allActions_, [](ConditionAction *action) {
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
    connect(killActShcut_.get(), &QShortcut::activated, [mw_ = this->mw_, killAction_ = this->killAction_.get()]() {
      std::unique_lock lock(mw_->procListMut_);
      killAction_->checkAndTrigger();
    });
    connect(killAction_.get(), &QAction::triggered,
      [mw_ = this->mw_, killAction_ = this->killAction_.get()]() {
      qDebug() << "Kill action";
      auto selectedItems = mw_->ui_->processTableView->selectionModel();
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
        auto res = mw_->processTableModel_->kill(pid);
        if (!res)
        {
          auto errorMsg = tr("Can not kill the process.")
                          .append(" ")
                          .append(QString::fromStdString(res.error()));
          QMessageBox::critical(mw_, tr("Error"), errorMsg, QMessageBox::Close);
          continue;
        }
      }
    });
  }

  void ActionsHolder::createRefreshAction()
  {
    refreshAction_ = std::make_unique< ConditionAction >(tr("Refresh"));
    refreshAction_->setIcon(mw_->style()->standardIcon(QStyle::SP_BrowserReload));
    refreshActShcut_ = std::make_unique< QShortcut >(QKeySequence::Refresh, mw_->ui_->processTableView);
    connect(refreshAction_.get(), &QAction::triggered, [mw_ = this->mw_](auto unused) {
      auto res = mw_->processTableModel_->refresh();
      if (!res)
      {
        auto errorMsg = tr("Error while refreshing processes.")
                        .append(" ")
                        .append(QString::fromStdString(res.error()));
        QMessageBox::critical(mw_, tr("Error"), errorMsg, QMessageBox::Close);
      }
    });
    connect(refreshActShcut_.get(), &QShortcut::activated, [mw_ = this->mw_, refreshAction_ = this->refreshAction_.get()]() {
      std::unique_lock lock(mw_->procListMut_);
      refreshAction_->checkAndTrigger();
    });
  }

  ActionsHolder::~ActionsHolder()
  { }
}
