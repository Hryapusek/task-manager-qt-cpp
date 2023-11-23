#include "ProcessFetcherLinux.hpp"
#include <cstdio>
#include <memory>

std::expected< std::vector< Process >, std::string > ProcessFetcherLinux::processes() const
{
  auto psResult = executeCommand("ps -e");
  return parsePsCommand(std::move(psResult));
  return std::expected< std::vector< Process >, std::string >();
}

std::expected< void, std::string > ProcessFetcherLinux::kill(int pid)
{
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
  std::size_t beginLine = 0;
  std::size_t endLine = 0;
  std::size_t count = 0;
  while (true)
  {
    beginLine = std::exchange(endLine, cmdResult.find("\n", endLine));
    count++;
    // TODO process line
    if (endLine == std::string::npos)
      break;
    ++endLine;
  }
  return std::vector< Process >(count);
}

#ifdef GTEST_TESTING
#include <gtest/gtest.h>
#include <iostream>

TEST(ProcessFetcherLinux, parsePsCommandTest)
{
  auto res = ProcessFetcherLinux::parsePsCommand("\n\n\n\n");
  EXPECT_EQ(res.value().size(), 5);
  res = ProcessFetcherLinux::parsePsCommand("damn\njeeeez\namogus");
  EXPECT_EQ(res.value().size(), 3);
}

#endif
