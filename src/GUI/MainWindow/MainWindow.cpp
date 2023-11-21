#include "MainWindow.hpp"
#include "Ui/UiMainWindow.hpp" 
#include "GUI/Model/ProcessTableModel.hpp"
#include "Process/ProcessFetchers/Test/ProcessFetcherTest.hpp"

MainWindow::MainWindow() :
  ui_(std::make_unique<Ui::MainWindow>())
{
  ui_->setupUi(this);
  auto fetcher = std::make_unique<ProcessFetcherTest>();
  model_ = std::make_unique<ProcessTableModel>(std::move(fetcher));
  ui_->processTableView->setModel(model_.get());
  ui_->processTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
  ui_->processTableView->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
  ui_->processTableView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
  connect(this, &QWidget::customContextMenuRequested, actions_.get(), &Actions::showMenu);
}

MainWindow::~MainWindow()
{}
