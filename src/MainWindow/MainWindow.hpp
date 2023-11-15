#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <memory>
#include "Model/ProcessTableModel.hpp"

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();
  ~MainWindow();

private:
  std::unique_ptr<Ui::MainWindow> ui_;
  std::unique_ptr<ProcessTableModel> model_;
};

#endif
