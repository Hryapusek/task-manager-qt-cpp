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

#endif
