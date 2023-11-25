#ifndef PROCESS_FETCHER_LINUX
#define PROCESS_FETCHER_LINUX

#include "../Interface/ProcessFetcherI.hpp"

namespace process
{
  class ProcessFetcherWindows: public ProcessFetcherI
  {
  public:
    virtual std::expected< std::vector< Process >, std::string > processes() override;
    virtual std::expected< void, std::string > kill(int pid) override;
    virtual constexpr std::vector< Field::Field_ > supportedFields() override;

  private:
    static const char *tasklistCommand;
    static std::expected< std::vector< Process >, std::string > parseTasklistCommand(std::string cmdResult);
    static std::expected< Process, std::string > parseLine(std::string_view line);
  };
}

#endif
