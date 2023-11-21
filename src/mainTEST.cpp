#include <iostream>
#include <QApplication>
#include "GUI/MainWindow/MainWindow.hpp"
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
