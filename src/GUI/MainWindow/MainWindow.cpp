#include "MainWindow.hpp"
#include "Ui/UiMainWindow.hpp"
#include "GUI/Model/ProcessTableModel.hpp"
#include "Process/ProcessFetchers/Test/ProcessFetcherTest.hpp"
#include "Actions.hpp"
#include <mutex>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow() :
  ui_(std::make_unique< Ui::MainWindow >())
{
  using namespace details_;
  std::unique_lock lock(procListMut_);
  ui_->setupUi(this);
  actionsHolder_ = std::make_unique< details_::ActionsHolder >(this);
  auto fetcher = std::make_unique< ProcessFetcherTest >();
  processTableModel_ = std::make_unique< ProcessTableModel >(std::move(fetcher));
  ui_->processTableView->setModel(processTableModel_.get());
  ui_->processTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
  ui_->processTableView->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
  ui_->processTableView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
  connect(ui_->processTableView, &QTableView::customContextMenuRequested, actionsHolder_.get(), &ActionsHolder::showMenu);
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
