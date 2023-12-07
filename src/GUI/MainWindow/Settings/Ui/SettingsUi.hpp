#ifndef SETTINGS_UI_HPP
#define SETTINGS_UI_HPP

#include "StyleUi.hpp"
#include "../SettingsMemento/SettingsMemento.hpp"

namespace details_
{
  struct SettingsUi
  { 
    StyleUi styleUi;
    void updateUi(const SettingsMemento &memento);
  };
}

#endif
