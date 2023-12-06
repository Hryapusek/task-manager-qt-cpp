#include "StyleContainerBuilder.hpp"
#include <QComboBox>
#include <source_location>
#include <QDebug>

namespace details_
{
  void StyleContainerBuilder::setStyleBox(QComboBox *styleBox)
  {
    result_.styleBox_ = styleBox;
    setStyleNames_(result_.styleNames_);
  }

  void StyleContainerBuilder::setStyleNames(std::vector<std::string> styleNames)
  {
    QStringList names;
    for (auto const &name : styleNames)
      names << QString::fromStdString(name);
    setStyleNames_(std::move(names));
  }

  void StyleContainerBuilder::setStyleNames(QStringList styleNames)
  {
    setStyleNames_(std::move(styleNames));
  }

  void StyleContainerBuilder::setStyleName(const QString &styleName)
  {
    result_.setStyleName(styleName);
  }

  StyleContainer StyleContainerBuilder::result() const & 
  {
    return result_;
  }

  StyleContainer StyleContainerBuilder::result() &&
  {
    return std::move(result_);
  }

  void StyleContainerBuilder::setStyleNames_(QStringList styleNames)
  {
    result_.styleNames_ = styleNames;
    if (result_.styleBox_)
      fillStyleBox_(styleNames);
  }

  void StyleContainerBuilder::fillStyleBox_(const QStringList &styleNames)
  {
    if (!result_.styleBox_)
    {
      std::source_location location;
      qDebug() << location.function_name() << "styleBox not initialized. Not filling it.";
      return;
    }
    result_.styleBox_->addItems(styleNames);
  }
}
