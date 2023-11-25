#ifndef PROCESS_FETCHER_LINUX
#define PROCESS_FETCHER_LINUX

#include "../Interface/ProcessFetcherI.hpp"

namespace process
{
  class ProcessFetcherLinux: public ProcessFetcherI
  {
  public:
    virtual std::expected< std::vector< Process >, std::string > processes() override;
    virtual std::expected< void, std::string > kill(int pid) override;
    virtual constexpr std::vector< Field::Field_ > supportedFields() override;

  private:
    static const char *psCommand;
    friend class ProcessFetcherLinux_parsePsCommandTest_Test;
    static std::string executeCommand(const char *cmd);
    static std::expected< std::vector< Process >, std::string > parsePsCommand(std::string cmdResult);
    static std::expected< Process, std::string > parseLine(std::string_view line);
  };
}

#endif
