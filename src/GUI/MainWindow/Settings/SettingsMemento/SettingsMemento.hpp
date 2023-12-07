#ifndef SETTINGS_MEMENTO_HPP
#define SETTINGS_MEMENTO_HPP

#include "StyleContainer.hpp"
#include <memory>

class SettingsMementoBuilder;

class SettingsMemento
{
public:
  using Builder_t = SettingsMementoBuilder;
  /**
   * @note Maybe nullptr
   */
  const details_::StyleContainer &style() const;

private:
  friend class SettingsMementoBuilder;
  details_::StyleContainer styleContainer_;
};

#endif
