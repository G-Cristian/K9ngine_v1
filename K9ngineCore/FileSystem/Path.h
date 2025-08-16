#ifndef PATH_H
#define PATH_H

#include <filesystem>
#include <string>
#include <utility>

namespace K9ngineCore {
	namespace FileSystem {
		class Path {
		public:
#ifdef _WIN32
			static const char Separator = '\\';
#elif defined(__linux__)
			static const char Separator = '/';
#else
#error "OS not supported"
#endif 
			static std::string combine(const std::string_view directory, const std::string_view fileName) { return (std::filesystem::path{ directory } / std::filesystem::path{ fileName }).string(); }
      static std::string getCurrentPath() { return std::filesystem::current_path().string(); }
			static std::string getDirectory(const std::string& path) { return splitDirectoryFileName(path).first; }
			static std::string getExtension(const std::string& path) { return splitFileNameExtension(path).second; }
			static std::string getFileName(const std::string& path) { return splitDirectoryFileName(path).second; }
			static std::string getFileNameWithoutExtension(const std::string& path) { return splitFileNameExtension(path).first; }
			static std::pair<std::string, std::string> splitDirectoryFileName(const std::string& path);
			static std::pair<std::string, std::string> splitFileNameExtension(const std::string& path);
			static std::string stripEndingSeparator(const std::string& directory);
		private:
			Path() = delete;
			Path(const Path&) = delete;
			Path(Path&&) noexcept = delete;
		};
	}
}

#endif // !PATH_H
