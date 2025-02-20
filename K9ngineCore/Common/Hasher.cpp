#include "Hasher.h"

#include <cstdint>
#include <string>

namespace K9ngineCore {
	namespace Common {
#ifndef NDEBUG
		using Hash = std::string;
		Hash hashString(const std::string& s) {
			return s;
		}
#else
		using Hash = uint64_t;
		Hash hashString(const std::string& s) {
			//TODO: Implement own hasher.
			return (Hash)std::hash<std::string>()(s);
		}
#endif // !NDEBUG
	}
}