#include "ProcTableViewHelper.hpp"
#include "Ui/UiMainWindow.hpp"
#include "ProcTableSortProxy.hpp"
#ifdef __WIN32
  #include "Process/ProcessFetchers/Windows/ProcessFetcherWindows.hpp"
#else
  #include "Process/ProcessFetchers/Linux/ProcessFetcherLinux.hpp"
#endif
#include "Actions.hpp"

namespace details_
{
  ProcTableViewHelper::ProcTableViewHelper(MainWindow *mw) :
	  mw_(mw)
  {
	  using namespace process;
    
    #ifdef __WIN32
      auto fetcher = std::make_unique< ProcessFetcherWindows >();
    #else
      auto fetcher = std::make_unique< ProcessFetcherLinux >();
    #endif
	  
	  mw_->processTableModel_ = std::make_unique< ProcessTableModel >(std::move(fetcher));
	  mw_->ui_->processTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	  mw_->ui_->processTableView->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
	  mw_->ui_->processTableView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
	  auto font = mw_->ui_->processTableView->font();
	  font.setPointSize(14);
	  mw_->ui_->processTableView->setFont(font);
	  mw_->procTableSortProxy_ = std::make_unique< ProcTableSortProxy >();
	  mw_->procTableSortProxy_->setSourceModel(mw_->processTableModel_.get());
	  mw_->ui_->processTableView->setModel(mw_->procTableSortProxy_.get());
	  mw_->ui_->processTableView->setSortingEnabled(true);
	  mw_->ui_->processTableView->horizontalHeader()->setSortIndicator(mw_->processTableModel_->pidColumn(), Qt::AscendingOrder);
	  mw_->ui_->processTableView->resizeColumnsToContents();
	  mw_->ui_->processTableView->setAutoScroll(false);
		mw_->ui_->processTableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
	  connect(mw_->ui_->processTableView, &QTableView::customContextMenuRequested, mw_->actionsHolder_.get(), &ActionsHolder::showMenu);
  }
}
