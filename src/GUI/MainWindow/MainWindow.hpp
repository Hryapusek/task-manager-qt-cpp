#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QShortcut>
#include <memory>
#include <thread>
#include "GUI/Model/ProcessTableModel.hpp"
#include "Utils/ConditionAction.hpp"

namespace Ui
{
  class MainWindow;
}

class MainWindow;

namespace details_
{
  class ActionsHolder;
  class ProcTableSortProxy;
}

class MainWindow: public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();
  ~MainWindow();

private:
  friend class details_::ActionsHolder;
  std::unique_ptr< Ui::MainWindow > ui_;
  std::unique_ptr< ProcessTableModel > processTableModel_;
  std::unique_ptr< details_::ProcTableSortProxy > procTableSortProxy_;
  std::unique_ptr< details_::ActionsHolder > actionsHolder_;
  std::mutex procListMut_;
  std::unique_ptr< QTimer > refreshTimer;
  void refreshFunc();
};

#endif
