#ifndef K9DEBUG_H
#define K9DEBUG_H

#include "Logger.h"
#include "MessageBox.h"

#include <cstdlib>
#include <exception>
#include <string>

namespace K9ngineCore {

#if (defined(K9_LOG_CONSOLE) && K9_LOG_CONSOLE>0) || (defined(K9_LOG_FILE) && K9_LOG_FILE>0)

#define LOG_ADD_TAB() gLogger.AddTab();
#define LOG_REMOVE_TAB() gLogger.RemoveTab();

#if K9_LOG_CONSOLE>2 && K9_LOG_FILE>2

#define LOG_MESSAGE(msg) gLogger.Log(std::stringstream() << "MESSAGE: " << msg, true, true)

#elif K9_LOG_CONSOLE>2

#define LOG_MESSAGE(msg) gLogger.Log(std::stringstream() << "MESSAGE: " << msg, true, false)

#elif K9_LOG_FILE>2

#define LOG_MESSAGE(msg) gLogger.Log(std::stringstream() << "MESSAGE: " << msg, false, true)

#else

#define LOG_MESSAGE(msg)

#endif //!K9_LOG_CONSOLE>2 && K9_LOG_FILE>2

#if K9_LOG_CONSOLE>1 && K9_LOG_FILE>1

#define LOG_WARNING(msg) gLogger.Log(std::stringstream() << "WARNING: " << msg, true, true)

#elif K9_LOG_CONSOLE>1

#define LOG_WARNING(msg) gLogger.Log(std::stringstream() << "WARNING: " << msg, true, false)

#elif K9_LOG_FILE>1

#define LOG_WARNING(msg) gLogger.Log(std::stringstream() << "WARNING: " << msg, false, true)

#else

#define LOG_WARNING(msg)

#endif //!K9_LOG_CONSOLE>1 && K9_LOG_FILE>1

#if K9_LOG_CONSOLE>0 && K9_LOG_FILE>0

#define LOG_ERROR(msg) gLogger.Log(std::stringstream() << "ERROR: " << msg, true, true)

#elif K9_LOG_CONSOLE>0

#define LOG_ERROR(msg) gLogger.Log(std::stringstream() << "ERROR: " << msg, true, false)

#elif K9_LOG_FILE>0

#define LOG_ERROR(msg) gLogger.Log(std::stringstream() << "ERROR: " << msg, false, true)

#else

#define LOG_ERROR(msg)

#endif //!K9_LOG_CONSOLE>0 && K9_LOG_FILE>0

#else

#define LOG_MESSAGE(msg)
#define LOG_WARNING(msg)
#define LOG_ERROR(msg)
#define LOG_ADD_TAB()
#define LOG_REMOVE_TAB()

#endif // !(defined(K9_LOG_CONSOLE) && K9_LOG_CONSOLE>0) || (defined(K9_LOG_FILE) && K9_LOG_FILE>0)

#if defined(K9TESTS)
#define K9ASSERT(expression, msg)	do{\
										if(!(expression)){\
											char lineStr[10];\
											_itoa_s(__LINE__, lineStr, 10);\
											std::string finalMsg = std::string(msg) + ". " + std::string(__FILE__) + ". " + std::string(lineStr);\
											throw std::exception(finalMsg.c_str());\
										}\
									}while (false)
#elif !defined(NDEBUG)
#define K9ASSERT(expression, msg) do{\
										if(!(expression)){\
											K9ngineCore::K9MessageBox::ShowError(msg, __FILE__, __LINE__);\
										}\
									}while(false)
#else
#define K9ASSERT(expression, msg)
#endif // !NDEBUG

}

#endif // !K9DEBUG_H
