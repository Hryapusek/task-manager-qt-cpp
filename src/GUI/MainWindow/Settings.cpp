#include "Settings.hpp"
#include "Settings/SettingsDialog.hpp"
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <source_location>
#include "MainWindow.hpp"
#include "Ui/ui_mainwindow.h"

namespace details_
{
  Settings::Settings(MainWindow *mw) :
    mw_(mw)
  {
    dialog_ = std::make_unique< SettingsDialog >(static_cast< QWidget * >(mw));
    settingsMemento_ = dialog_->getMemento();
    connect(mw_->ui_->preferencesMenuAct, &QAction::triggered, this, &Settings::showDialog_);
    connect(dialog_.get(), &SettingsDialog::apply, this, &Settings::apply);
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
    applyStyle_();
  }

  void Settings::rejected()
  {
    dialog_->setMemento(settingsMemento_);
  }

  Settings::~Settings() = default;

  void Settings::applyStyle_()
  {
    auto styleName = dialog_->styleGroup().styleName();
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
