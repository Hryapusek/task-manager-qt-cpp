#ifndef PROCESS_FETCHER_TEST
#define PROCESS_FETCHER_TEST

#include "../Interface/ProcessFetcherI.hpp"

class ProcessFetcherTest : public ProcessFetcherI
{
  virtual std::vector< Process > processes() const override;
  virtual std::expected< void, std::string > kill(int pid) override;
};

#endif
