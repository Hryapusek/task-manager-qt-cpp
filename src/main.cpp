#include <iostream>
#include <QApplication>
#include <QTranslator>
#include "GUI/MainWindow/MainWindow.hpp"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  MainWindow window;
  QTranslator translator;
  std::cerr << translator.language().toStdString();
  translator.load("rus");
  app.installTranslator(&translator);
  window.show();
  return app.exec();
}
