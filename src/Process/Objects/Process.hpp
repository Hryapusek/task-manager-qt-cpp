#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>

class Process
{
public:
  Process();
  int pid() const;
  void pid(int pid);
  time_t time() const;
  void time(time_t time);
  const std::string &cmd() const;
  void cmd(std::string cmd);
private:
  int pid_;
  time_t time_;
  std::string cmd_;
};

#endif
