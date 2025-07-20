#include "Hasher.h"

#include <cstdint>
#include <string>
#include<string_view>

namespace K9ngineCore {
	namespace Common {
#ifndef NDEBUG
		using Hash = std::string;
		Hash hashString(std::string_view s) {
			return std::string{ s };
		}

		uint64_t hashToUInt64(const Hash& hash) {
			//TODO: Implement own hasher.
			return static_cast<uint64_t>(std::hash<std::string>()(hash));
		}
#else
		using Hash = uint64_t;
		Hash hashString(std::string_view s) {
			//TODO: Implement own hasher.
			return static_cast<Hash>(std::hash<std::string>()(std::string{ s }));
		}

		uint64_t hashToUInt64(const Hash& hash) {
			return hash;
		}
#endif // !NDEBUG
	}
}