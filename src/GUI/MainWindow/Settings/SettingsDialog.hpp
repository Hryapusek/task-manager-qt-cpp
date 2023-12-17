#ifndef SETTINGS_DIALOG_HPP
#define SETTINGS_DIALOG_HPP

#include <QDialog>
#include "Ui/SettingsUi.hpp"
#include "SettingsMemento/SettingsMemento.hpp"

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
  const SettingsMemento &getMemento() const;
  void updateUi();
  void apply();
  virtual void accept() override;
  virtual void reject() override;

  ~SettingsDialog();

signals:
  void applySig();

protected:
  virtual void closeEvent(QCloseEvent *e) override;

private:
  friend class SettingsMemento;
  SettingsMemento memento_;
  details_::SettingsUi settingsUi_;
  std::unique_ptr< Ui::SettingsDialog > ui_;
  void setupUi();
  void setupStyle();
};

#endif
