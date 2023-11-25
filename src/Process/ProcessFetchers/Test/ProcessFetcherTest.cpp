#include "ProcessFetcherTest.hpp"
#include <ranges>

namespace process
{
  ProcessFetcherTest::ProcessFetcherTest()
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
    processes_ = std::vector< Process >{
      proc1,
      proc2,
      proc3
    };
  }

  std::expected< std::vector< Process >, std::string > ProcessFetcherTest::processes()
  {
    return processes_;
  }

  std::expected< void, std::string > ProcessFetcherTest::kill(int pid)
  {
    auto processToRemove = std::ranges::find_if(processes_, [pid](auto proc) {
      return proc.pid() == pid;
    });
    using namespace std::string_literals;
    if (processToRemove == processes_.end())
      return std::unexpected("Process not found"s);
    processes_.erase(processToRemove);
    Process proc;
    proc.cmd("Command5");
    proc.pid(555);
    processes_.push_back(proc);
    return { };
  }

  constexpr std::vector<Field::Field_> ProcessFetcherTest::supportedFields()
  {
    return {Field::PID, Field::WORK_TIME, Field::COMMAND};
  }
}
