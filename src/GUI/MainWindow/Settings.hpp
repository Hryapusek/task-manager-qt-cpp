#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <memory>
#include <QObject>

class SettingsDialog;
class MainWindow;

namespace details_
{
  class Settings: public QObject
  {
    Q_OBJECT

  public:
    Settings(MainWindow *mw);
    /// @note Do not save returned pointer
    SettingsDialog *dialog();
    void apply();
    ~Settings();

  signals:
    // Remove if unused
    void applySig();

  private:
    std::unique_ptr< SettingsDialog > dialog_;
    MainWindow *mw_;
    void applyStyle_();
    void showDialog_();
  };
}

#endif
