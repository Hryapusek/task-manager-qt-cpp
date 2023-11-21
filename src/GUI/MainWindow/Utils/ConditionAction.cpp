#include "ConditionAction.hpp"
#include <QEvent>
#include <ranges>

void ConditionAction::addCheckFunction(std::function< bool() > checker)
{
  conditions_.push_back(std::move(checker));
}

void ConditionAction::updateEnabled()
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
