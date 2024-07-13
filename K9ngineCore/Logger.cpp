#if (defined(K9_LOG_CONSOLE) && K9_LOG_CONSOLE>0) ||  (defined(K9_LOG_FILE) && K9_LOG_FILE>0)

#include "Logger.h"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

namespace K9ngineCore {
  unsigned char Logger::mInstancesCount = 0;
  std::mutex Logger::mMutex;

  Logger::Logger() {
    mInstancesCount++;
    assert(mInstancesCount == 1);

    using path = std::filesystem::path;

    path lPath = std::filesystem::current_path();

    using namespace std::chrono;
    auto tp = zoned_time{ current_zone(), system_clock::now() }.get_local_time();
    auto dp = floor<days>(tp);
    year_month_day ymd{ dp };
    hh_mm_ss time{ floor<milliseconds>(tp - dp) };
    auto y = ymd.year();
    auto m = ymd.month();
    auto d = ymd.day();
    auto h = time.hours();
    auto M = time.minutes();
    auto s = time.seconds();
    auto ms = time.subseconds();

    std::stringstream ss;
    ss << "Log_" << y << "_" << m << "_" << d << "_" << h << "_" << M << "_" << s << ".txt";

    lPath /= ss.str();

    mLogPath = lPath.string();
  }

  void Logger::AddTab() {
    const std::lock_guard<std::mutex> lock(mMutex);
    mSpaces += "  ";
  }
  void Logger::RemoveTab() {
    const std::lock_guard<std::mutex> lock(mMutex);
    if (mSpaces.length() >= 2) {
      mSpaces.erase(0, 2);
    }
    else {
      mSpaces = "";
    }
  }

  void Logger::Log(char* msg, bool consoleLog, bool fileLog) {
    Log(std::string(msg), consoleLog, fileLog);
  }

  void Logger::Log(const std::stringstream& ss, bool consoleLog, bool fileLog) {
    Log(ss.str(), consoleLog, fileLog);
  }

  void Logger::Log(const std::string& msg, bool consoleLog, bool fileLog) {
    const std::lock_guard<std::mutex> lock(mMutex);
    std::string lFinalMsg = mSpaces + msg;

#if (defined(K9_LOG_CONSOLE) && K9_LOG_CONSOLE>0)
    if (consoleLog) {
      std::cout << lFinalMsg << std::endl;
    }
#endif

#if (defined(K9_LOG_FILE) && K9_LOG_FILE>0)
    if (fileLog) {
      std::ofstream lFile(mLogPath, std::ios_base::app);
      lFile << lFinalMsg << std::endl;
    }
#endif
  }

  Logger gLogger;
}
#endif