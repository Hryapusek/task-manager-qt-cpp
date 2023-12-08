#include "Settings.hpp"
#include "Settings/SettingsDialog.hpp"
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <source_location>
#include "MainWindow.hpp"
#include "Ui/ui_mainwindow.h"
#include "Settings/SettingsMemento/SettingsMementoCreator.hpp"

namespace details_
{
  Settings::Settings(MainWindow *mw) :
    mw_(mw)
  {
    auto res = SettingsMementoCreator::readMementoFromFile();
    if (res)
    {
      settingsMemento_ = *res;
    }
    else
    {
      qDebug() << "Could not read a memento " << res.error();
      settingsMemento_ = SettingsMementoCreator::createDefault();
      SettingsMementoCreator::writeMementoToFile(settingsMemento_);
    }
    dialog_ = std::make_unique< SettingsDialog >(settingsMemento_, static_cast< QWidget * >(mw));
    connect(mw_->ui_->preferencesMenuAct, &QAction::triggered, this, &Settings::showDialog_);
    connect(dialog_.get(), &SettingsDialog::applySig, this, &Settings::apply);
    connect(dialog_.get(), &QDialog::accepted, this, &Settings::apply);
    connect(dialog_.get(), &QDialog::rejected, this, &Settings::rejected);
  }

  SettingsDialog *Settings::dialog()
  {
    return dialog_.get();
  }

  void Settings::apply()
  {
    settingsMemento_ = dialog_->getMemento();
    SettingsMementoCreator::writeMementoToFile(settingsMemento_);
    applyStyle_();
  }

  void Settings::rejected()
  {
    dialog_->setMemento(settingsMemento_);
    dialog_->updateUi();
  }

  Settings::~Settings() = default;

  void Settings::applyStyle_()
  {
    auto styleName = settingsMemento_.style().styleName();
    if (styleName == "None")
    {
      qApp->setStyleSheet(QString());
      return;
    }
    QFile file("styles/" + styleName + ".qss");
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen())
    {
      std::source_location location = std::source_location::current();
      qDebug() << location.function_name() << "Can not open style file. Setting default theme";
      qApp->setStyleSheet(QString());
      return;
    }
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
  }

  void Settings::showDialog_()
  {
    dialog_->show();
  }
}
