#include "StyleContainer.hpp"
#include <source_location>
#include <QComboBox>
#include <QDebug>

namespace details_
{
  constexpr QStringList StyleContainer::styleNames() const
  {
    return styleNames_;
  }

  QString StyleContainer::styleName() const
  {
    return styleBox_->currentText();
  }

  void StyleContainer::setStyleName(const QString &styleName)
  {
    if (!styleNames_.contains(styleName))
    {
      std::source_location location = std::source_location::current();
      qDebug() << location.function_name() << "Style name " << styleName << " not found";
      return;
    }
    styleBox_->setCurrentText(styleName);
  }
}
