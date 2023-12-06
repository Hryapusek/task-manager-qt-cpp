#ifndef SETTINGS_DIALOG_HPP
#define SETTINGS_DIALOG_HPP

#include <QDialog>
#include "StyleContainer.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class SettingsDialog;
}
class QComboBox;
QT_END_NAMESPACE


class SettingsDialog: public QDialog
{
  Q_OBJECT
public:
  SettingsDialog(QWidget *parent);
  details_::StyleContainer &styleGroup();
  ~SettingsDialog();

signals:
  void apply();

private:
  std::unique_ptr< Ui::SettingsDialog > ui_;
  std::unique_ptr< details_::StyleContainer > styleContainer_;
  void setupStyle();
};

#endif
