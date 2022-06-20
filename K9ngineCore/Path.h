#ifndef PATH_H
#define PATH_H

#include <string>
#include <utility>

namespace K9ngineCore {
	namespace Utility {
		class Path {
		public:
#ifdef _WIN32
			static const char Separator = '\\';
#elif defined(__linux__)
			static const char Separator = '/';
#else
#error "OS not supported"
#endif 
			static std::string stripEndingSeparator(const std::string& directory);
			static std::pair<std::string, std::string> splitDirectoryFileName(const std::string& path);
			static std::string getDirectory(const std::string& path) { return splitDirectoryFileName(path).first; }
			static std::string getFileName(const std::string& path) { return splitDirectoryFileName(path).second; }
			static std::pair<std::string, std::string> splitFileNameExtension(const std::string& path);
			static std::string getFileNameWithoutExtension(const std::string& path) { return splitFileNameExtension(path).first; }
			static std::string getExtension(const std::string& path) { return splitFileNameExtension(path).second; }
		private:
			Path() = delete;
			Path(const Path&) = delete;
			Path(Path&&) noexcept = delete;
		};
	}
}

#endif // !PATH_H
