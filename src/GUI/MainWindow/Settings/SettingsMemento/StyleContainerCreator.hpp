#ifndef STYLE_CONTAINER_CREATOR
#define STYLE_CONTAINER_CREATOR

#include "StyleContainer.hpp"
#include <expected>

namespace details_
{
  class StyleContainerCreator
  {
  public:
    static StyleContainer createDefault();
    static std::expected<StyleContainer, QString> readFromFile();
    static std::expected<void, QString> writeToFile(const StyleContainer &styleContainer);
  };
}

#endif
