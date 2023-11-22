/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *refreshOpt;
    QAction *sortPID;
    QAction *sortTime;
    QAction *sortCmd;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTableView *processTableView;
    QMenuBar *menubar;
    QMenu *menuView;
    QMenu *sortMenu;
    QMenu *menuOptions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        refreshOpt = new QAction(MainWindow);
        refreshOpt->setObjectName(QString::fromUtf8("refreshOpt"));
        refreshOpt->setCheckable(true);
        refreshOpt->setChecked(true);
        sortPID = new QAction(MainWindow);
        sortPID->setObjectName(QString::fromUtf8("sortPID"));
        sortTime = new QAction(MainWindow);
        sortTime->setObjectName(QString::fromUtf8("sortTime"));
        sortCmd = new QAction(MainWindow);
        sortCmd->setObjectName(QString::fromUtf8("sortCmd"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        processTableView = new QTableView(centralwidget);
        processTableView->setObjectName(QString::fromUtf8("processTableView"));

        gridLayout->addWidget(processTableView, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        sortMenu = new QMenu(menuView);
        sortMenu->setObjectName(QString::fromUtf8("sortMenu"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menuView->addAction(sortMenu->menuAction());
        sortMenu->addAction(sortPID);
        sortMenu->addAction(sortTime);
        sortMenu->addAction(sortCmd);
        menuOptions->addAction(refreshOpt);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        refreshOpt->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        sortPID->setText(QCoreApplication::translate("MainWindow", "PID", nullptr));
        sortTime->setText(QCoreApplication::translate("MainWindow", "TIME", nullptr));
        sortCmd->setText(QCoreApplication::translate("MainWindow", "COMMAND", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        sortMenu->setTitle(QCoreApplication::translate("MainWindow", "Sort by", nullptr));
        menuOptions->setTitle(QCoreApplication::translate("MainWindow", "Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
