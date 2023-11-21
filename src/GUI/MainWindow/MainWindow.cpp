#include "MainWindow.hpp"
#include "UiMainWindow.hpp" 
#include "Model/ProcessTableModel.hpp"
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
}

MainWindow::~MainWindow()
{}
