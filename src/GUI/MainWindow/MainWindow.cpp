#include "MainWindow.hpp"
#include "Ui/UiMainWindow.hpp"
#include "GUI/Model/ProcessTableModel.hpp"
#include "Process/ProcessFetchers/Test/ProcessFetcherTest.hpp"

MainWindow::MainWindow() :
  ui_(std::make_unique< Ui::MainWindow >()),
  actionsHolder_(std::make_unique< details_::ActionsHolder >(this))
{
  using namespace details_;
  ui_->setupUi(this);
  auto fetcher = std::make_unique< ProcessFetcherTest >();
  model_ = std::make_unique< ProcessTableModel >(std::move(fetcher));
  ui_->processTableView->setModel(model_.get());
  ui_->processTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
  ui_->processTableView->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
  ui_->processTableView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
  connect(ui_->processTableView, &QTableView::customContextMenuRequested, actionsHolder_.get(), &ActionsHolder::showMenu);
}

MainWindow::~MainWindow()
{ }
