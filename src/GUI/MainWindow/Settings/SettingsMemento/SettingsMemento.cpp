#include "SettingsMemento.hpp"

const details_::StyleContainer &SettingsMemento::style() const
{
  return styleContainer_;
}

details_::StyleContainer &SettingsMemento::style()
{
  return styleContainer_;
}

void SettingsMemento::setStyle(details_::StyleContainer styleContainer) {
  styleContainer_ = std::move(styleContainer);
}

bool SettingsMemento::operator==(const SettingsMemento &rhs) const
{
  return styleContainer_ == rhs.styleContainer_;
}
