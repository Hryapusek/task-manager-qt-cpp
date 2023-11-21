#include <iostream>
#include <QApplication>
#include "GUI/MainWindow/MainWindow.hpp"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  MainWindow window;
  window.show();
  return app.exec();
}
