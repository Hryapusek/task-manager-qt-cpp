#include "MainWindow.hpp"
#include "Ui/UiMainWindow.hpp"
#include "GUI/Model/ProcessTableModel.hpp"
#include "Process/ProcessFetchers/Test/ProcessFetcherTest.hpp"
#include "Actions.hpp"
#include <mutex>

MainWindow::MainWindow() :
  ui_(std::make_unique< Ui::MainWindow >())
{
  using namespace details_;
  std::unique_lock lock(procListMut_);
  ui_->setupUi(this);
  allActions_ = std::make_unique< details_::ActionsHolder >(this);
  auto fetcher = std::make_unique< ProcessFetcherTest >();
  processTableModel_ = std::make_unique< ProcessTableModel >(std::move(fetcher));
  ui_->processTableView->setModel(processTableModel_.get());
  ui_->processTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
  ui_->processTableView->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
  ui_->processTableView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
  connect(ui_->processTableView, &QTableView::customContextMenuRequested, allActions_.get(), &ActionsHolder::showMenu);
}

MainWindow::~MainWindow()
{ }
