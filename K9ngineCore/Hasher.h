#ifndef HASHER_H
#define HASHER_H

#include <string>

namespace K9ngineCore {
	namespace Utility {
		uint64_t hashString(const std::string& s) {
			//TODO: Implement own hasher.
			return (uint64_t)std::hash<std::string>()(s);
		}
	}
}

#endif // !HASHER_H
