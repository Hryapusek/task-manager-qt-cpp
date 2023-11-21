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
  void updateEnabled();
  /**
   * @return true if ALL the conditions are met\
   * @return false otherwise
   */
  bool areConditionsMet();

private:
  std::vector< std::function< bool() > > conditions_;
};

#endif
