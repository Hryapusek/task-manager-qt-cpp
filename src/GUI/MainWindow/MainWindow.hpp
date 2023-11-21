#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <memory>
#include "GUI/Model/ProcessTableModel.hpp"

namespace Ui
{
  class MainWindow;
}

class MainWindow: public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();
  ~MainWindow();

private:
  struct Actions: public QObject
  {
    Q_OBJECT
    
  public:
    Actions(MainWindow *mw);
    void showMenu(const QPoint &pos);
  private:
    MainWindow *mw_;
    std::unique_ptr< QMenu > menu;
    std::unique_ptr< QAction > killAction;
    std::unique_ptr< QAction > infoAction;
  };
  std::unique_ptr< Ui::MainWindow > ui_;
  std::unique_ptr< ProcessTableModel > model_;
  std::unique_ptr< Actions > actions_;
};

#endif
