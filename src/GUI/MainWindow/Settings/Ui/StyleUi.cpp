#include "StyleUi.hpp"
#include <cassert>
#include <QComboBox>
#include <source_location>

void details_::StyleUi::updateUi(const SettingsMemento &memento)
{
  assert(styleBox_ != nullptr);
  styleBox_->addItems(memento.style().styleNames());
  if (!memento.style().styleNames().contains(memento.style().styleName()))
  {
    std::source_location location = std::source_location::current();
    qDebug() << location.function_name() << "Style name " << memento.style().styleName() << " not found in memento style names list";
  }
  styleBox_->setCurrentText(memento.style().styleName());
}
