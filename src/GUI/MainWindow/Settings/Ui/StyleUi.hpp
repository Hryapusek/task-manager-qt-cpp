#ifndef STYLE_UI_HPP
#define STYLE_UI_HPP

#include <vector>
#include "../SettingsMemento/SettingsMemento.hpp"

class QComboBox;

namespace details_
{
  struct StyleUi
  {
    QComboBox *styleBox_ = nullptr;
    void updateUi(const SettingsMemento &memento);
  };
}

#endif
