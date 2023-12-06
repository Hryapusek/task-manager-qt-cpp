#include "StyleContainer.hpp"
#include <QComboBox>
#include <QDebug>

namespace details_
{
  constexpr QStringList StyleContainer::styleNames() const
  {
    return styleNames_;
  }

  constexpr QString StyleContainer::styleName() const
  {
    return styleBox_->currentText();
  }

  void StyleContainer::setStyleName(const QString &styleName)
  {
    if (!styleNames_.contains(styleName))
    {
      qDebug() << "Style name " << styleName << " not found";
      return;
    }
    styleBox_->setCurrentText(styleName);
  }
}
