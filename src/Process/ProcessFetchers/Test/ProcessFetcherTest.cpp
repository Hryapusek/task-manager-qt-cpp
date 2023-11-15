#include "ProcessFetcherTest.hpp"

std::vector<Process> ProcessFetcherTest::processes() const
{
  Process proc1;
  proc1.cmd("Command1");
  proc1.pid(122);
  Process proc2;
  proc2.cmd("Command2");
  proc2.pid(233);
  Process proc3;
  proc3.cmd("Command3");
  proc3.pid(344);
  return std::vector<Process>{
    proc1,
    proc2,
    proc3
  };
}

std::expected<void, std::string> ProcessFetcherTest::kill(int pid)
{
  return std::expected<void, std::string>();
}
