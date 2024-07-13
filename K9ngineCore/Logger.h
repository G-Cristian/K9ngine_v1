#pragma once

#if (defined(K9_LOG_CONSOLE) && K9_LOG_CONSOLE>0) ||  (defined(K9_LOG_FILE) && K9_LOG_FILE>0)

#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

namespace K9ngineCore {
  class Logger {
  public:
    Logger();

    void AddTab();
    void RemoveTab();

    void Log(char*, bool, bool);
    void Log(const std::stringstream&, bool, bool);
    void Log(const std::string&, bool, bool);
  private:
    Logger(Logger&) = delete;
    Logger(Logger&&) noexcept = delete;

    Logger& operator=(Logger&) = delete;
    Logger& operator=(Logger&&) noexcept = delete;

    std::string mLogPath;
    std::string mSpaces;

    static unsigned char mInstancesCount;
    static std::mutex mMutex;
  };

  extern Logger gLogger;
}
#endif