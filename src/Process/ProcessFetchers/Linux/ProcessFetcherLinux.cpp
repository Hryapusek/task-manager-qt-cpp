#include "ProcessFetcherLinux.hpp"
#include <cstdio>
#include <memory>
#include <string_view>
#include <source_location>
#include <sstream>
#include <iomanip>
#include <charconv>
#include <QDebug>
#include "Utils/Utils.hpp"
#include <sys/signal.h>


namespace process
{
  const char *ProcessFetcherLinux::psCommand = "ps -e -o \"%p\" -o \"|%x\" -o \"|%c\" --no-headers";

  std::expected< std::vector< Process >, std::string > ProcessFetcherLinux::processes()
  {
    auto psResult = utils::executeCommand(psCommand);
    return parsePsCommand(std::move(psResult));
  }

  std::expected< void, std::string > ProcessFetcherLinux::kill(int pid)
  {
    ::kill(pid, SIGKILL);
    return {};
  }

  constexpr std::vector<Field::Field_> ProcessFetcherLinux::supportedFields()
  {
    return {Field::PID, Field::WORK_TIME, Field::COMMAND};
  }

  std::expected< std::vector< Process >, std::string > ProcessFetcherLinux::parsePsCommand(std::string cmdResult)
  {
    utils::Splitter splitter(cmdResult, "\n");
    std::vector< Process > processes;
    while (splitter.hasNext())
    {
      auto line = splitter.next().value();
      auto res = parseLine(std::string_view(line.first, line.second));
      if (!res)
      {
        qDebug() << "Bad line found. " << QString::fromStdString(res.error()) << " Skipping...\n";
        continue;
      }
      processes.push_back(res.value());
    }
    return processes;
  }

  std::expected< Process, std::string > ProcessFetcherLinux::parseLine(std::string_view line)
  {
    utils::Splitter splitter(line, "|");

    if (!splitter.hasNext())
      return std::unexpected("Pid str not found in the line");
    auto pidStrPair = splitter.next().value();

    if (!splitter.hasNext())
      return std::unexpected("Time str not found in the line");
    auto timeStrPair = splitter.next().value();

    if (!splitter.hasNext())
      return std::unexpected("Command str not found in the line");
    auto cmdStrPair = splitter.theRest();

    struct std::tm tm;
    std::istringstream ss(std::string(timeStrPair.first, timeStrPair.second));
    ss >> std::get_time(&tm, "%T");
    std::time_t time = tm.tm_sec + tm.tm_min * 60 + tm.tm_hour * 60 * 60;

    int pid;
    auto pidWordBegin = pidStrPair.first;
    auto pidWordEnd = pidStrPair.second;

    while (pidWordBegin != pidWordEnd && *pidWordBegin == ' ')
      ++pidWordBegin;
    auto res = std::from_chars(pidWordBegin, pidWordEnd, pid);
    if (res.ec == std::errc::invalid_argument)
      return std::unexpected("Bad pid value found");

    Process proc;
    proc.time(time);
    proc.cmd(std::string(cmdStrPair.first, cmdStrPair.second));
    proc.pid(pid);
    return proc;
  }
}

#ifdef GTEST_TESTING
#include <gtest/gtest.h>
#include <iostream>

TEST(ProcessFetcherLinux, parsePsCommandTest)
{
  {
    Splitter splitter("a\nb\nc\nd\n", "\n");
    auto res = splitter.next().value();
    EXPECT_EQ(std::string(res.first, res.second), "a");
  }
  {
    Splitter splitter("damn\njeeeez\namogus", " \n");
    auto res = splitter.next().value();
    EXPECT_EQ(std::string(res.first, res.second), "damn");
    res = splitter.next().value();
    EXPECT_EQ(std::string(res.first, res.second), "jeeeez");
    res = splitter.next().value();
    EXPECT_EQ(std::string(res.first, res.second), "amogus");
  }
}

#endif
