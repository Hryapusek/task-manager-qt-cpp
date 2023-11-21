#ifndef CONDITION_ACTION_HPP
#define CONDITION_ACTION_HPP

#include <QAction>

class ConditionAction: public QAction
{
  Q_OBJECT

public:
  using QAction::QAction;
  /**
   * @brief Register condition checker.
   */
  void addCheckFunction(std::function< bool() > checker);
  /**
   * @brief Sets isEnabled with respect to conditions.
   */
  void updateIsEnabledFlag();
  /**
   * @return True if ALL the conditions are met\
   * @return False otherwise
   */
  bool areConditionsMet();
  /**
   * @brief Triggers if areConditionsMet() == true.\
   * @brief Does nothing otherwise
   */
  void checkAndTrigger();

private:
  std::vector< std::function< bool() > > conditions_;
};

#endif
