#include "MainWindow.hpp"
#include "Ui/UiMainWindow.hpp"
#include "GUI/Model/ProcessTableModel.hpp"
#include "Process/ProcessFetchers/Test/ProcessFetcherTest.hpp"
#include "Actions.hpp"

MainWindow::MainWindow() :
  ui_(std::make_unique< Ui::MainWindow >())
{
  using namespace details_;
  ui_->setupUi(this);
  actionsHolder_ = std::make_unique< details_::ActionsHolder >(this);
  auto fetcher = std::make_unique< ProcessFetcherTest >();
  processTableModel_ = std::make_unique< ProcessTableModel >(std::move(fetcher));
  ui_->processTableView->setModel(processTableModel_.get());
  ui_->processTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
  ui_->processTableView->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
  ui_->processTableView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
  connect(ui_->processTableView, &QTableView::customContextMenuRequested, actionsHolder_.get(), &ActionsHolder::showMenu);
}

MainWindow::~MainWindow()
{ }
