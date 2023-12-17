#include "StyleContainer.hpp"
#include <source_location>
#include <QComboBox>
#include <QDebug>

namespace details_
{
  QStringList StyleContainer::styleNames() const
  {
    return styleNames_;
  }

  QString StyleContainer::styleName() const
  {
    return currentStyle_;
  }

  void StyleContainer::setStyleName(const QString &styleName)
  {
    currentStyle_ = styleName;
  }

  void StyleContainer::setStyleNames(const QStringList &styleNames)
  {
    styleNames_ = styleNames;
  }

  void StyleContainer::setStyleNames(std::vector<std::string> styleNames)
  {
    QStringList names;
    for (auto const &name : styleNames)
      names << QString::fromStdString(name);
    setStyleNames(names);
  }
  
  bool StyleContainer::operator==(const StyleContainer &rhs) const
  {
    return styleNames_ == rhs.styleNames_ and currentStyle_ == rhs.currentStyle_;
  }
}
