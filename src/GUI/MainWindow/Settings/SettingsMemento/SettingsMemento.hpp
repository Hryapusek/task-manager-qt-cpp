#ifndef SETTINGS_MEMENTO_HPP
#define SETTINGS_MEMENTO_HPP

#include "StyleContainer.hpp"
#include <memory>

class SettingsMementoBuilder;

class SettingsMemento
{
public:
  using Builder_t = SettingsMementoBuilder;
  const details_::StyleContainer &style() const;
  details_::StyleContainer &style();
  void setStyle(details_::StyleContainer styleContainer);
  bool operator==(const SettingsMemento &rhs) const;

private:
  friend class SettingsMementoBuilder;
  details_::StyleContainer styleContainer_;
};

#endif
