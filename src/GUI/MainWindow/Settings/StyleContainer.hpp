#ifndef STYLE_CONTAINER_HPP
#define STYLE_CONTAINER_HPP

#include <vector>
#include <QStringList>

class QComboBox;

namespace details_
{
  class StyleContainer
  {
  public:
    constexpr QStringList styleNames() const;
    constexpr QString styleName() const;
    // Remove this if unused
    void setStyleName(const QString &styleName);

  private:
    StyleContainer() = default;
    friend class StyleContainerBuilder;
    QComboBox *styleBox_ = nullptr;
    QStringList styleNames_;
  };
}

#endif
