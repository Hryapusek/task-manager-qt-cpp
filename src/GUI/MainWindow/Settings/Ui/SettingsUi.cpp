#include "SettingsUi.hpp"

void details_::SettingsUi::updateUi(const SettingsMemento &memento)
{
  styleUi.updateUi(memento);
}

void details_::SettingsUi::updateMemento(SettingsMemento &memento)
{
  styleUi.updateMemento(memento);
}
