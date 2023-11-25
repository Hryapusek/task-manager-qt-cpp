#ifndef PROCESS_FETCHER_HPP
#define PROCESS_FETCHER_HPP

#include "Process/Objects/Process.hpp"
#include <vector>
#include <expected>

namespace process
{
  class ProcessFetcherI
  {
  public:
    /**
     * @return Sorted by pid processes
     */
    virtual std::expected< std::vector< Process >, std::string > processes() = 0;
    virtual std::expected< void, std::string > kill(int pid) = 0;
    virtual std::vector< process::Field::Field_ > supportedFields() = 0;
  };
}

#endif
