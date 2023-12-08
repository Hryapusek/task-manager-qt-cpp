#include "SettingsDialog.hpp"
#include "Ui/ui_settings.h"
#include <QDebug>
#include <filesystem>
#include <vector>
#include <QPushButton>
#include <source_location>
#include <QTimer>

SettingsDialog::SettingsDialog(SettingsMemento memento, QWidget *parent) :
  QDialog(parent),
  ui_(std::make_unique< Ui::SettingsDialog >())
{
  ui_->setupUi(this);
  setupUi();
  memento_ = std::move(memento);
  updateUi();
  connect(ui_->applyBtn, &QPushButton::clicked, this, &SettingsDialog::apply);
  connect(ui_->applyBtn, &QPushButton::clicked, this, &SettingsDialog::applySig);
  QTimer::singleShot(0, this, &SettingsDialog::applySig);
}

const SettingsMemento &SettingsDialog::getMemento() const
{
  return memento_;
}

void SettingsDialog::setMemento(const SettingsMemento &memento)
{
  memento_ = memento;
}

void SettingsDialog::updateUi()
{ 
  settingsUi_.updateUi(memento_);
}

void SettingsDialog::setupUi()
{
  setupStyle();
}

void SettingsDialog::apply()
{ 
  settingsUi_.updateMemento(memento_);
}

void SettingsDialog::setupStyle()
{
  settingsUi_.styleUi.styleBox_ = ui_->style_styleBox;
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
