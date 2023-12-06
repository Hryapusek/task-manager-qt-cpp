#ifndef STYLE_CONTAINER_BUILDER_HPP
#define STYLE_CONTAINER_BUILDER_HPP

#include "StyleContainer.hpp"

#include <vector>
#include <QStringList>

class QComboBox;

namespace details_
{
  class StyleContainerBuilder
  {
  public:
    StyleContainerBuilder() = default;
    void setStyleBox(QComboBox *styleBox);
    void setStyleNames(std::vector< std::string > styleNames);
    void setStyleNames(QStringList styleNames);
    void setStyleName(const QString &styleName);
    StyleContainer result() const &;
    StyleContainer result() &&;
  
  private:
    StyleContainer result_;
    void setStyleNames_(QStringList styleNames);
    void fillStyleBox_(const QStringList &styleNames);
  };
}

#endif
