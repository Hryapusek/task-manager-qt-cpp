#include "ConditionAction.hpp"
#include <QEvent>
#include <ranges>
#include <QActionEvent>

void ConditionAction::addCheckFunction(std::function< bool() > checker)
{
  conditions_.push_back(std::move(checker));
}

void ConditionAction::updateIsEnabledFlag()
{
  setEnabled(areConditionsMet());
}

bool ConditionAction::areConditionsMet()
{
  auto transRange = std::views::transform(conditions_,
    [](auto fun) -> bool {
    return fun();
  });
  return std::reduce(transRange.begin(), transRange.end(), true, std::logical_and< bool >());
}

void ConditionAction::checkAndTrigger()
{
  if (areConditionsMet())
    activate(QAction::ActionEvent::Trigger);
}


#ifdef GTEST_TESTING
#include <gtest/gtest.h>
TEST(ConditionAction, basics)
{
  {
    ConditionAction action;
    bool triggered = false;
    QObject::connect(&action, &ConditionAction::triggered,
      [&triggered]() {
      triggered = true;
    });

    action.trigger();
    EXPECT_TRUE(triggered);
    triggered = false;

    action.addCheckFunction([]() {
      return false;
    });

    action.trigger();
    EXPECT_TRUE(triggered);
    triggered = false;

    action.checkAndTrigger();
    EXPECT_FALSE(triggered);
    triggered = false;

    action.addCheckFunction([]() {
      return true;
    });

    action.checkAndTrigger();
    EXPECT_FALSE(triggered);
    triggered = false;
  }
  {
    ConditionAction action;
    bool triggered = false;
    QObject::connect(&action, &ConditionAction::triggered,
      [&triggered]() {
      triggered = true;
    });

    action.trigger();
    EXPECT_TRUE(triggered);
    triggered = false;

    action.addCheckFunction([]() {
      return true;
    });

    action.addCheckFunction([]() {
      return true;
    });

    action.trigger();
    EXPECT_TRUE(triggered);
    triggered = false;
  }
}

#endif
