#ifndef K9DEBUG_H
#define K9DEBUG_H

#include "MessageBox.h"

#include <cstdlib>
#include <exception>
#include <string>

namespace K9ngineCore {

#if defined(K9TESTS)
#define K9ASSERT(expression, msg)	do{\
										if(!(expression)){\
											char lineStr[10];\
											_itoa_s(__LINE__, lineStr, 10);\
											throw std::exception((std::string(msg) + ". " + std::string(__FILE__) + ". " + std::string(lineStr)).c_str());\
										}\
									}while (false)
#elif !defined(NDEBUG)
#define K9ASSERT(expression, msg) do{if(!(expression))K9ngineCore::K9MessageBox::ShowError(msg, __FILE__, __LINE__);}while(false)
#else
#define K9ASSERT(expression, msg)
#endif // !NDEBUG

}

#endif // !K9DEBUG_H
