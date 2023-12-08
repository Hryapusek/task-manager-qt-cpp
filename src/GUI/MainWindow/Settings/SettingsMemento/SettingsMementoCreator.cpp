#include "SettingsMementoCreator.hpp"
#include "StyleContainerCreator.hpp"
#include <QDebug>
#include <filesystem>
#include <QFile>
#include <QDir>

SettingsMemento SettingsMementoCreator::createDefault()
{
  SettingsMemento result;
  result.setStyle(details_::StyleContainerCreator::createDefault());
  return result;
}

std::expected<SettingsMemento, QString> SettingsMementoCreator::readMementoFromFile()
{
  SettingsMemento memento;
  auto styleRes = details_::StyleContainerCreator::readFromFile();
  if (!styleRes)
    return std::unexpected(std::move(styleRes).error());
  memento.setStyle(*styleRes);
  return memento;
}

std::expected<void, QString> SettingsMementoCreator::writeMementoToFile(SettingsMemento memento)
{
  auto res = details_::StyleContainerCreator::writeToFile(memento.style());
  return res;
}
