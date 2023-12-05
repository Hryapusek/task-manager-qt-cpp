#include "SettingsDialog.hpp"
#include "Ui/ui_settings.h"
#include <filesystem>

namespace
{
  std::vector< std::string > getStyleNames()
  {
    namespace fs = std::filesystem;
    std::vector< std::string > styleNames;
    auto dirEntries = fs::directory_iterator(fs::current_path() / "styles");
    for (auto const &entry : dirEntries)
    {
      if (entry.is_regular_file() && entry.path().extension() == ".qss")
      { 
        auto styleFileName = entry.path().filename().string();
        styleFileName = styleFileName.substr(0, styleFileName.size()-4);
        styleNames.push_back(std::string(styleFileName));
      }
    }
    return styleNames;
  }
}

SettingsDialog::SettingsDialog(QWidget *parent) :
  ui_(std::make_unique< Ui::SettingsDialog >())
{
  setupUi();

}

constexpr QStringList SettingsDialog::styleNames() const
{
  return styleContainer.styleNames;
}

SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::setupUi()
{
  ui_->setupUi(this);
  styleContainer.styleBox = ui_->style_styleBox;
  fillStyleBox();
}

void SettingsDialog::fillStyleBox()
{
  auto styleNames = getStyleNames();
  QStringList names;
  for (auto const &name : styleNames)
    names << QString::fromStdString(name);
  styleContainer.styleBox->addItems(names);
  styleContainer.styleNames = names;
}

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
