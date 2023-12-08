#include "StyleContainerCreator.hpp"
#include "StyleContainer.hpp"
#include <filesystem>
#include <ranges>
#include <QSettings>
#include "ApplicationInfo.hpp"

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

namespace details_
{
  StyleContainer details_::StyleContainerCreator::createDefault()
  {
    StyleContainer result;
    auto styles = getStyleNames();
    QStringList list;
    std::ranges::transform(styles, std::back_inserter(list), &QString::fromStdString);
    list.append("None");
    result.setStyleNames(list);
    result.setStyleName("None");
    return result;
  }

  std::expected< StyleContainer, QString > StyleContainerCreator::readFromFile()
  {
    details_::StyleContainer styleContainer;
    QSettings settings(ApplicationInfo::organization, ApplicationInfo::application);
    settings.beginGroup("Settings");
    settings.beginGroup("Style");
    if (!settings.value("CurrentStyle").canConvert<QString>())
      return std::unexpected(QObject::tr("Can not convert CurrentStyle to QString"));
    styleContainer.setStyleName(settings.value("CurrentStyle").toString());
    if (!settings.value("StyleNames").canConvert<QStringList>())
      return std::unexpected(QObject::tr("Can not convert StyleNames to StringList"));
    styleContainer.setStyleNames(settings.value("StyleNames").toStringList());
    settings.endGroup();
    settings.endGroup();
    return styleContainer;
  }

  std::expected< void, QString > StyleContainerCreator::writeToFile(const StyleContainer &styleContainer)
  {
    QSettings settings(ApplicationInfo::organization, ApplicationInfo::application);
    settings.beginGroup("Settings");
    settings.beginGroup("Style");
    settings.setValue("StyleNames", styleContainer.styleNames());
    settings.setValue("CurrentStyle", styleContainer.styleName());
    settings.endGroup();
    settings.endGroup();
    return { };
  }
}
