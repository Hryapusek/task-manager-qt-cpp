#ifndef SETTINGS_MEMENTO_CREATOR_HPP
#define SETTINGS_MEMENTO_CREATOR_HPP

#include "SettingsMemento.hpp"
#include <QSettings>
#include <expected>

class SettingsMementoCreator
{
public:
  static SettingsMemento createDefault();  
  static std::expected<SettingsMemento, QString> readMementoFromFile();
  static std::expected<void, QString> writeMementoToFile(SettingsMemento memento);

private:
  static std::expected<SettingsMemento, QString> createMementoFromQSettings();
  static std::expected<std::unique_ptr< QSettings >, QString> readQSettingsFromFile(QString settingsPath);
  static std::expected<void, QString> writeQSettingsToFile(std::shared_ptr< QSettings > settings, QString settingsPath);
};

#endif
