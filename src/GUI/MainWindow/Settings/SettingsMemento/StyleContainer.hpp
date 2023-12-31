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
    StyleContainer() = default;
    QStringList styleNames() const;
    QString styleName() const;
    void setStyleName(const QString &styleName);
    void setStyleNames(const QStringList &styleNames);
    void setStyleNames(std::vector< std::string > styleNames);
    bool operator==(const StyleContainer &rhs) const;

  private:
    QStringList styleNames_;
    QString currentStyle_;
  };
}

#endif
