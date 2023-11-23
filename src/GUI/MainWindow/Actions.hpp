#ifndef ACITONS_HOLDER_HPP
#define ACITONS_HOLDER_HPP

#include <QShortcut>
#include <memory>
#include "Utils/ConditionAction.hpp"

class MainWindow;

namespace details_
{
  /*
    Shortcuts lock the mutex.
    Actions do NOT because showMenu does.
  */
  class ActionsHolder: public QObject
  {
    Q_OBJECT
  public:
    ActionsHolder(MainWindow *mw);
    ~ActionsHolder();
    void showMenu(const QPoint &pos);
    /**
     * @note Does NOT hold the process list mutex
     */
    void refresh(bool showError = true);
    /**
     * @note Does NOT hold the process list mutex
     */
    void kill();

  private:
    MainWindow *mw_;
    std::unique_ptr< QMenu > menu_;
    std::unique_ptr< ConditionAction > refreshAction_;
    std::unique_ptr< QShortcut > refreshActShcut_;
    std::unique_ptr< ConditionAction > killAction_;
    std::unique_ptr< QShortcut > killActShcut_;
    std::vector< ConditionAction * > allActions_;
    void createKillAction();
    void createRefreshAction();
    std::vector< QPersistentModelIndex > getSelectedRowsPersistIndexes() const;
    void selectPersistRowsIndexes(const std::vector< QPersistentModelIndex > &persistRowsIndexes);
  };
}

#endif
