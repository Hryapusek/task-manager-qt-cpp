#ifndef PROCESS_FETCHER_TEST
#define PROCESS_FETCHER_TEST

#include "../Interface/ProcessFetcherI.hpp"

class ProcessFetcherTest: public ProcessFetcherI
{
public:
  ProcessFetcherTest();
  virtual std::vector< Process > processes() const override;
  virtual std::expected< void, std::string > kill(int pid) override;
private:
  std::vector< Process > processes_;
};

#endif
