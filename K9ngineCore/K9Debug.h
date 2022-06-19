#ifndef K9DEBUG_H
#define K9DEBUG_H

#include <cassert>

namespace K9ngineCore {

#ifndef NDEBUG
#define K9ASSERT(expression) assert(expression)
#else
#define K9ASSERT(expression)
#endif // !NDEBUG

}

#endif // !K9DEBUG_H
