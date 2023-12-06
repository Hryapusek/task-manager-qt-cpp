#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QTranslator>
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
  class MenuBarActions;
  class ProcTableSortProxy;
  class ProcTableViewHelper;
  class LanguageHelper;
  class Settings;
}

class MainWindow: public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();
  ~MainWindow();

private:
  friend class details_::ActionsHolder;
  friend class details_::MenuBarActions;
  friend class details_::ProcTableViewHelper;
  friend class details_::LanguageHelper;
  friend class details_::Settings;
  std::unique_ptr< Ui::MainWindow > ui_;
  std::unique_ptr< ProcessTableModel > processTableModel_;
  std::unique_ptr< details_::ProcTableSortProxy > procTableSortProxy_;
  std::unique_ptr< details_::ActionsHolder > actionsHolder_;
  std::unique_ptr< details_::ProcTableViewHelper > procTableViewHelper_;
  std::unique_ptr< details_::LanguageHelper > languageHelper_;
  std::unique_ptr< details_::Settings > settings_;
  std::mutex procListMut_;
  std::unique_ptr< QTimer > refreshTimer;
  void refreshFunc();
  void changeEvent(QEvent *event) override;
};

#endif
