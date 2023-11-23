#ifndef PROCESS_FETCHER_LINUX
#define PROCESS_FETCHER_LINUX

#include "../Interface/ProcessFetcherI.hpp"

class ProcessFetcherLinux : public ProcessFetcherI
{
public:
  virtual std::expected< std::vector< Process >, std::string > processes() const override;
  virtual std::expected< void, std::string > kill(int pid) override;

private:
  friend class ProcessFetcherLinux_parsePsCommandTest_Test;
  static std::string executeCommand(const char* cmd);
  static std::expected< std::vector< Process >, std::string > parsePsCommand(std::string cmdResult);
  static Process parseLine(std::string_view line);
};

#endif
