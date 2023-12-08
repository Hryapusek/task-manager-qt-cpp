#include "LanguageHelper.hpp"
#include "MainWindow.hpp"
#include "Ui/ui_mainwindow.h"
#include <QComboBox>
#include <QDebug>
#include <map>
#include <ranges>
#include <QApplication>

namespace details_
{
  const std::map<QString, QString> LanguageHelper::languages_files_map = 
  {
    {QString::fromUtf8("Rus"), QString::fromUtf8("rus")},
    {QString::fromUtf8("Eng"), QString::fromUtf8("")}
  };

  LanguageHelper::LanguageHelper(MainWindow *mw) :
    mw_(mw)
  {
    translator.load("");
    qApp->installTranslator(&translator);
    for (const auto &langPair : languages_files_map)
      mw_->ui_->languageBox->addItem(langPair.first, langPair.second);
    connect(mw_->ui_->languageBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &LanguageHelper::changeLanguage);
  }

  void LanguageHelper::changeLanguage(int index)
  {
    auto lang = mw_->ui_->languageBox->itemData(index).toString();
    translator.load(lang);
  }

  LanguageHelper::~LanguageHelper() = default;
}
