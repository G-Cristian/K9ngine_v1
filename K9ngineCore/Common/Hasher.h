#ifndef HASHER_H
#define HASHER_H

#include <cstdint>
#include <string>

namespace K9ngineCore {
	namespace Common {
#ifndef NDEBUG
		using Hash = std::string;
#else
		using Hash = uint64_t;
#endif // !NDEBUG

		Hash hashString(const std::string& s);
	}
}

#endif // !HASHER_H
