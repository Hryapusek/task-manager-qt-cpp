#ifndef SETTINGS_DIALOG_HPP
#define SETTINGS_DIALOG_HPP

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class SettingsDialog;
}
class QComboBox;
QT_END_NAMESPACE

namespace details_
{
  struct StyleContainer
  {
    QComboBox *styleBox = nullptr;
    QStringList styleNames;
  };
}

class SettingsDialog : public QDialog
{
  Q_OBJECT
public:
  SettingsDialog(QWidget *parent);
  void setStyle(QString styleName);
  constexpr QStringList styleNames() const;
  ~SettingsDialog();

signals:
  void apply();

private:
  std::unique_ptr< Ui::SettingsDialog > ui_;
  details_::StyleContainer styleContainer;
  void setupUi();
  void fillStyleBox();
};

#endif
