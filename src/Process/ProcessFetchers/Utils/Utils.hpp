#ifndef PROCESS_UTILS_HPP
#define PROCESS_UTILS_HPP

#include <string_view>
#include <string>
#include <expected>
#include <algorithm>

namespace process::utils
{
  struct Splitter
  {
	  using Iterator_t = std::string_view::const_iterator;
	  Splitter(std::string_view string, std::string splitSymbols);
	  std::expected< std::pair< Iterator_t, Iterator_t >, bool > next();
	  bool hasNext();
	  void skipWs();
		bool skip(int nSkip);
	  std::pair< Iterator_t, Iterator_t > theRest();
	private:
	  void moveToWordEnd();
	  std::string_view string_;
	  Iterator_t curBegin_;
	  Iterator_t curEnd_;
	  Iterator_t end_;
	  std::string splitSymbols_;
  };
	std::string executeCommand(const char *cmd);
}

#endif
