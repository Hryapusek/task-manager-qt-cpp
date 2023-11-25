#include "Process.hpp"

namespace process
{
  Process::Process()
  { }

  int Process::pid() const
  {
    return pid_;
  }

  void Process::pid(int pid)
  {
    pid_ = pid;
  }

  time_t Process::time() const
  {
    return time_;
  }

  void Process::time(time_t time)
  {
    time_ = time;
  }

  const std::string &Process::cmd() const
  {
    return cmd_;
  }

  void Process::cmd(std::string cmd)
  {
    cmd_ = std::move(cmd);
  }
}
