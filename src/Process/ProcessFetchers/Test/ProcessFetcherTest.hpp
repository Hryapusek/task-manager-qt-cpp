#ifndef PROCESS_FETCHER_TEST
#define PROCESS_FETCHER_TEST

#include "../Interface/ProcessFetcherI.hpp"

namespace process
{
  class ProcessFetcherTest: public ProcessFetcherI
  {
  public:
    ProcessFetcherTest();
    virtual std::expected< std::vector< Process >, std::string > processes() override;
    virtual std::expected< void, std::string > kill(int pid) override;
    virtual constexpr std::vector< Field::Field_ > supportedFields() override;
  private:
    std::vector< Process > processes_;
  };
}

#endif
