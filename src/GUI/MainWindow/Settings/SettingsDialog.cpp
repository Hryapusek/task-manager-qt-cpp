#include "SettingsDialog.hpp"
#include "Ui/ui_settings.h"
#include <QDebug>
#include <filesystem>
#include <vector>
#include <QPushButton>
#include <source_location>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include "SettingsMemento/SettingsMementoCreator.hpp"

SettingsDialog::SettingsDialog(QWidget *parent) :
  QDialog(parent),
  ui_(std::make_unique< Ui::SettingsDialog >())
{
  auto res = SettingsMementoCreator::readMementoFromFile();
  if (res)
  {
    memento_ = *res;
  }
  else
  {
    qDebug() << "Could not read a memento " << res.error();
    memento_ = SettingsMementoCreator::createDefault();
    SettingsMementoCreator::writeMementoToFile(memento_);
  }
  ui_->setupUi(this);
  setupUi();
  updateUi();
  connect(ui_->applyBtn, &QPushButton::clicked, this, &SettingsDialog::apply);
  QTimer::singleShot(0, this, &SettingsDialog::applySig);
}

const SettingsMemento &SettingsDialog::getMemento() const
{
  return memento_;
}

void SettingsDialog::updateUi()
{
  settingsUi_.updateUi(memento_);
}

void SettingsDialog::accept()
{
  apply();
  hide();
}

void SettingsDialog::reject()
{
  updateUi();
  hide();
}

void SettingsDialog::setupUi()
{
  setupStyle();
}

void SettingsDialog::apply()
{
  settingsUi_.updateMemento(memento_);
  SettingsMementoCreator::writeMementoToFile(memento_);
  emit applySig();
}

void SettingsDialog::setupStyle()
{
  settingsUi_.styleUi.styleBox_ = ui_->style_styleBox;
}

void SettingsDialog::closeEvent(QCloseEvent *e)
{
  auto newMemento = memento_;
  settingsUi_.updateMemento(newMemento);
  if (newMemento != memento_)
  {
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, tr("Unsaved changes"),
      tr("There are unsaved changes. Would you like to save them?\n"),
      QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
      QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes)
    {
      apply();
      e->accept();
      return;
    }
    else if (resBtn == QMessageBox::No)
    {
      reject();
      e->ignore();
      return;
    }
    else if (resBtn == QMessageBox::Cancel)
    {
      e->ignore();
      return;
    }
  }
  else
  {
    e->accept();
  }
}

SettingsDialog::~SettingsDialog()
{ }

#ifdef GTEST_TESTING
#include <gtest/gtest.h>

TEST(styleNames, basics)
{
  auto styleNames = getStyleNames();
  using namespace std::string_literals;
  bool hasMedizeStyle = std::ranges::find(styleNames, "Medize"s) != styleNames.end();
  bool hasObitStyle = std::ranges::find(styleNames, "Obit"s) != styleNames.end();
  bool hasSyNetStyle = std::ranges::find(styleNames, "SyNet"s) != styleNames.end();
  EXPECT_TRUE(hasMedizeStyle);
  EXPECT_TRUE(hasObitStyle);
  EXPECT_TRUE(hasSyNetStyle);
}

#endif
