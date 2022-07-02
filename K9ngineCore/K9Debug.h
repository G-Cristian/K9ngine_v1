#ifndef K9DEBUG_H
#define K9DEBUG_H

#include "MessageBox.h"
#include <cassert>

namespace K9ngineCore {

#ifndef NDEBUG
#define K9ASSERT(expression, msg) do{if(!(expression))K9MessageBox::ShowError(msg, __FILE__, __LINE__);}while(false)
#else
#define K9ASSERT(expression)
#endif // !NDEBUG

}

#endif // !K9DEBUG_H
