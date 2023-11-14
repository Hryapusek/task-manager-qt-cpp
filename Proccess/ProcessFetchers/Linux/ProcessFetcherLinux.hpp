#ifndef PROCESS_FETCHER_LINUX
#define PROCESS_FETCHER_LINUX

#include "../Interface/ProcessFetcherI.hpp"

class ProcessFetcherLinux : public ProcessFetcherI
{
  virtual std::vector< Process > processes() const override;
  virtual std::expected< void, std::string > kill(int pid) override;
};

#endif
