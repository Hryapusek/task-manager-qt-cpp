#include "Utils.hpp"
#include <memory>
#include <array>
#include <ranges>

namespace process::utils
{
  Splitter::Splitter(std::string_view string, std::string splitSymbols)
  {
	  string_ = std::move(string);
	  curBegin_ = string_.cbegin();
	  curEnd_ = curBegin_;
	  end_ = string_.cend();
	  splitSymbols_ = std::move(splitSymbols);
  }

  std::expected< std::pair< Splitter::Iterator_t, Splitter::Iterator_t >, bool > Splitter::next()
  {
	  if (!hasNext())
		  return std::unexpected(false);
	  curBegin_ = curEnd_;
	  moveToWordEnd();
	  return std::pair{ curBegin_, curEnd_ };
  }

  bool Splitter::hasNext()
  {
	  skipWs();
	  return curEnd_ != end_;
  }

  void Splitter::skipWs()
  {
	  while (curEnd_ != end_ && splitSymbols_.contains(*curEnd_))
		  ++curEnd_;
  }

  bool Splitter::skip(int nSkip)
  {
    for (auto i : std::views::iota(0, nSkip))
    {
      if (!hasNext())
        return false;
      next();
    }
    return hasNext();
  }

  std::pair< Splitter::Iterator_t, Splitter::Iterator_t > Splitter::theRest()
  {
	  skipWs();
	  return std::pair{ curEnd_, end_ };
  }
  
  void Splitter::moveToWordEnd()
  {
	  curEnd_ = std::find_first_of(curEnd_, end_, splitSymbols_.begin(), splitSymbols_.end());
  }
  
  std::string executeCommand(const char *cmd)
  {
    std::array< char, 512 > buffer;
    std::string result;
    std::unique_ptr< FILE, decltype(&pclose) > pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
      throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
      result += buffer.data();
    }
    return result;
  }
}
