#ifndef HASHER_H
#define HASHER_H

#include <cstdint>
#include <string>
#include<string_view>

namespace K9ngineCore {
	namespace Common {
#ifndef NDEBUG
		using Hash = std::string;
#else
		using Hash = uint64_t;
#endif // !NDEBUG

		Hash hashString(std::string_view s);
		uint64_t hashToUInt64(const Hash&);
	}
}

#endif // !HASHER_H
