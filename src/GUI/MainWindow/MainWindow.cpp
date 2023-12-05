#include "MainWindow.hpp"
#include "Ui/ui_mainwindow.h"
#include "GUI/Model/ProcessTableModel.hpp"
#include "ProcTableViewHelper.hpp"
#include "Actions.hpp"
#include "ProcTableSortProxy.hpp"
#include "LanguageHelper.hpp"
#include <mutex>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow() :
  ui_(std::make_unique< Ui::MainWindow >())
{
  using namespace details_;
  using namespace process;
  std::unique_lock lock(procListMut_);
  ui_->setupUi(this);

  actionsHolder_ = std::make_unique< details_::ActionsHolder >(this);
  procTableViewHelper_ = std::make_unique< details_::ProcTableViewHelper >(this);
  languageHelper_ = std::make_unique< details_::LanguageHelper >(this);

  refreshTimer = std::make_unique< QTimer >();
  refreshTimer->setInterval(5000);
  connect(refreshTimer.get(), &QTimer::timeout, this, &MainWindow::refreshFunc);
  refreshTimer->start();
}

MainWindow::~MainWindow()
{ }

void MainWindow::refreshFunc()
{
  std::unique_lock lock(procListMut_, std::defer_lock);
  if (!lock.try_lock())
    return;
  auto showError = true;
  actionsHolder_->refresh(showError);
  lock.unlock();
}

void MainWindow::changeEvent(QEvent * event)
{
  if (event->type() == QEvent::LanguageChange)
  {
    ui_->retranslateUi(this);
    ui_->processTableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    return;
  }
  return QMainWindow::changeEvent(event);
}
