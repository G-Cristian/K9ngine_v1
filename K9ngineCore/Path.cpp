#include "Path.h"

#include <string>

namespace K9ngineCore {
	namespace Utility {
		std::string Path::stripEndingSeparator(const std::string& directory) {
			if (directory.empty()) {
				return directory;
			}
			else if (directory[directory.length() - 1] == Path::Separator) {
				return directory.substr(0, directory.length() - 1);
			}
			else {
				return directory;
			}
		}

		std::pair<std::string, std::string> Path::splitDirectoryFileName(const std::string& path) {
			size_t dotIndex = path.rfind('.');
			if (dotIndex == std::string::npos) {
				// No '.' found => no file extension => no file name
				return { stripEndingSeparator(path), "" };
			}

			size_t separatorIndex = path.rfind(Path::Separator);
			if (separatorIndex == std::string::npos) {
				// '.' found but no separator found => no directory found
				return { "", path };
			}

			if (dotIndex < separatorIndex) {
				// '.' appears before separator => in Linux it means hidden folder => no file name
				return { stripEndingSeparator(path), "" };
			}

			return { path.substr(0, separatorIndex), path.substr(separatorIndex + 1) };
		}

		std::pair<std::string, std::string> Path::splitFileNameExtension(const std::string& path) {
			std::string fileName = getFileName(path);
			size_t dotIndex = fileName.rfind('.');
			if (dotIndex == std::string::npos) {
				return { fileName, "" };
			}

			return { fileName.substr(0, dotIndex), fileName.substr(dotIndex + 1) };
		}
	}
}