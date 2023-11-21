#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <memory>
#include "GUI/Model/ProcessTableModel.hpp"
#include "Utils/ConditionAction.hpp"

namespace Ui
{
  class MainWindow;
}

class MainWindow;

namespace details_
{
  class ActionsHolder: public QObject
  {
    Q_OBJECT
  public:
    ActionsHolder(MainWindow *mw);
    ~ActionsHolder();
    void showMenu(const QPoint &pos);

  private:
    MainWindow *mw_;
    std::unique_ptr< QMenu > menu_;
    std::unique_ptr< ConditionAction > killAction_;
    std::unique_ptr< ConditionAction > infoAction_;
    std::vector< ConditionAction * > actionsHolder_;
  };
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
  std::unique_ptr< ProcessTableModel > model_;
  std::unique_ptr< details_::ActionsHolder > actionsHolder_;
};

#endif
