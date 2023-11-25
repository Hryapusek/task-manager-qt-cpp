#include "ProcessFetcherWindows.hpp"
#include <cstdio>
#include <memory>
#include <string_view>
#include <source_location>
#include <sstream>
#include <iomanip>
#include <charconv>
#include <QDebug>
#include "../Utils/Utils.hpp"
#include <ranges>
#include <windows.h>


namespace process
{
  const char *ProcessFetcherWindows::tasklistCommand = "tasklist.exe /Fo csv /Nh";

  std::expected< std::vector< Process >, std::string > ProcessFetcherWindows::processes()
  {
	  auto psResult = utils::executeCommand(tasklistCommand);
	  return parseTasklistCommand(std::move(psResult));
  }

  std::expected< void, std::string > ProcessFetcherWindows::kill(int pid)
  {
		auto procHandle = OpenProcess(PROCESS_TERMINATE, false, pid);
	  TerminateProcess(procHandle, 1);
		CloseHandle(procHandle);
	  return {};
  }

  constexpr std::vector<Field::Field_> ProcessFetcherWindows::supportedFields()
  {
	  return {Field::PID, Field::COMMAND, Field::MEMORY};
  }

  std::expected< std::vector< Process >, std::string > ProcessFetcherWindows::parseTasklistCommand(std::string cmdResult)
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
    std::ranges::sort(processes, [](const Process &p1, const Process &p2){return p1.pid() < p2.pid();});
	  return processes;
  }

  std::expected< Process, std::string > ProcessFetcherWindows::parseLine(std::string_view line)
  {
	  utils::Splitter splitter(line, ",");

	  if (!splitter.hasNext())
		  return std::unexpected("Command str not found in the line");
	  auto cmdStrPair = splitter.next().value();
	  ++cmdStrPair.first;
	  --cmdStrPair.second;

	  if (!splitter.hasNext())
		  return std::unexpected("Pid str not found in the line");
	  auto pidStrPair = splitter.next().value();
	  ++pidStrPair.first;
	  --pidStrPair.second;

	  auto extraColumnsCount = 2;
	  if (!splitter.skip(extraColumnsCount))
		  return std::unexpected("Unexpected end of line");

	  auto memoryStrPair = splitter.next().value();
	  ++memoryStrPair.first;
	  while (!isdigit(*(memoryStrPair.second-1)))
		  memoryStrPair.second--;
	  if (memoryStrPair.second <= memoryStrPair.first)
		  return std::unexpected("Unrecognisable memory format");

	  int pid;
	  auto res = std::from_chars(pidStrPair.first, pidStrPair.second, pid);
	  if (res.ec == std::errc::invalid_argument)
		  return std::unexpected("Bad pid value found");

	  int memory;
	  std::string memoryStr(memoryStrPair.first, memoryStrPair.second);
	  memoryStr.erase(std::remove_if(
        memoryStr.begin(), 
        memoryStr.end(), 
        [](char c){return !isdigit(c);}), 
      memoryStr.end());
	  res = std::from_chars(memoryStr.c_str(), memoryStr.c_str() + memoryStr.size(), memory);
	  if (res.ec == std::errc::invalid_argument)
		  return std::unexpected("Bad memory value found");

	  Process proc;
	  proc.cmd(std::string(cmdStrPair.first, cmdStrPair.second));
	  proc.pid(pid);
	  proc.memory(memory);

	  return proc;
  }
}

#ifdef GTEST_TESTING
#include <gtest/gtest.h>
#include <iostream>

#endif
