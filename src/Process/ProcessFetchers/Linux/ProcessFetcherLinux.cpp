#include "ProcessFetcherLinux.hpp"
#include <cstdio>
#include <memory>
#include <string_view>
#include <source_location>
#include <sstream>
#include <iomanip>
#include <charconv>
#include <QDebug>
#include <sys/signal.h>

namespace
{
  struct Splitter
  {
    using Iterator_t = std::string_view::const_iterator;
    Splitter(std::string_view string, std::string splitSymbols)
    {
      string_ = std::move(string);
      curBegin_ = string_.cbegin();
      curEnd_ = curBegin_;
      end_ = string_.cend();
      splitSymbols_ = std::move(splitSymbols);
    }
    std::expected< std::pair< Iterator_t, Iterator_t >, bool > next()
    {
      if (!hasNext())
        return std::unexpected(false);
      curBegin_ = curEnd_;
      moveToWordEnd();
      return std::pair{ curBegin_, curEnd_ };
    }
    bool hasNext()
    {
      skipWs();
      return curEnd_ != end_;
    }
    void skipWs()
    {
      while (curEnd_ != end_ && splitSymbols_.contains(*curEnd_))
        ++curEnd_;
    }
    std::pair< Iterator_t, Iterator_t > theRest()
    {
      skipWs();
      return std::pair{ curEnd_, end_ };
    }
  private:
    void moveToWordEnd()
    {
      curEnd_ = std::find_first_of(curEnd_, end_, splitSymbols_.begin(), splitSymbols_.end());
    }
    std::string_view string_;
    Iterator_t curBegin_;
    Iterator_t curEnd_;
    Iterator_t end_;
    std::string splitSymbols_;
  };
}

std::expected< std::vector< Process >, std::string > ProcessFetcherLinux::processes() const
{
  auto psResult = executeCommand("ps -eo pid,time,cmd");
  return parsePsCommand(std::move(psResult));
}

std::expected< void, std::string > ProcessFetcherLinux::kill(int pid)
{
  auto location = std::source_location::current();
  ::kill(pid, SIGKILL);
  return std::expected< void, std::string >();
}

std::string ProcessFetcherLinux::executeCommand(const char *cmd)
{
  std::array< char, 512 > buffer;
  std::string result;
  std::unique_ptr< FILE, decltype(&pclose) > pipe(popen(cmd, "r"), pclose);
  if (!pipe)
  {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}

std::expected< std::vector< Process >, std::string > ProcessFetcherLinux::parsePsCommand(std::string cmdResult)
{
  Splitter splitter(cmdResult, "\n");
  std::size_t lineNum = 0;
  std::vector< Process > processes;
  while (splitter.hasNext())
  {
    lineNum++;
    if (lineNum == 1)
    {
      splitter.next();
      continue;
    }
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
  Splitter splitter(line, " ");

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

  auto res = std::from_chars(pidStrPair.first, pidStrPair.second, pid);
  if (res.ec == std::errc::invalid_argument)
    return std::unexpected("Bad pid value found");

  Process proc;
  proc.time(time);
  proc.cmd(std::string(cmdStrPair.first, cmdStrPair.second));
  proc.pid(pid);
  return proc;
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
