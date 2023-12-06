#include "SettingsDialog.hpp"
#include "Ui/ui_settings.h"
#include "StyleContainerBuilder.hpp"
#include <filesystem>
#include <vector>
#include <QPushButton>

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
        styleFileName = styleFileName.substr(0, styleFileName.size() - 4);
        styleNames.push_back(std::string(styleFileName));
      }
    }
    return styleNames;
  }
}

SettingsDialog::SettingsDialog(QWidget *parent) :
  QDialog(parent),
  ui_(std::make_unique< Ui::SettingsDialog >())
{
  ui_->setupUi(this);
  setupStyle();
  connect(ui_->applyBtn, &QPushButton::clicked, this, &SettingsDialog::apply);
}

details_::StyleContainer &SettingsDialog::styleGroup()
{
  return *styleContainer_.get();
}

SettingsDialog::~SettingsDialog()
{ }

void SettingsDialog::setupStyle()
{
  details_::StyleContainerBuilder builder;
  builder.setStyleBox(ui_->style_styleBox);

  auto styleNames = getStyleNames();
  styleNames.insert(styleNames.begin(), "None");
  builder.setStyleNames(styleNames);
  builder.setStyleName(QString::fromStdString(styleNames[0]));
  
  styleContainer_ = std::make_unique< details_::StyleContainer >(std::move(builder).result());
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
