#ifndef LANGUAGE_HELPER_HPP
#define LANGUAGE_HELPER_HPP

#include <QObject>
#include <QTranslator>

class MainWindow;

namespace details_
{
  class LanguageHelper: public QObject
  {
    Q_OBJECT
  public:
    LanguageHelper(MainWindow * mw);
    void changeLanguage(int index);
    ~LanguageHelper();
  private:
    static const std::map<QString, QString> languages_files_map;
    MainWindow *mw_;
    QTranslator translator;
  };
}

#endif
