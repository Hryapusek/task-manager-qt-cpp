#ifndef PROCESS_FETCHER_HPP
#define PROCESS_FETCHER_HPP

#include "Process/Objects/Process.hpp"
#include <vector>
#include <expected>

class ProcessFetcherI
{
public:
  /**
   * @return Sorted by pid processes
   */
  virtual std::expected< std::vector< Process >, std::string > processes() const = 0;
  virtual std::expected< void, std::string > kill(int pid) = 0;
};

#endif
