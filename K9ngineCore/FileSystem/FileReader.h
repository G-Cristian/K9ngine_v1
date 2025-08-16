#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <string>
#include <string_view>

namespace K9ngineCore {
	namespace FileSystem {
		class FileReader;
		FileReader& operator>>(FileReader&, int&);
		FileReader& operator>>(FileReader&, unsigned int&);
		FileReader& operator>>(FileReader&, char&);
		FileReader& operator>>(FileReader&, bool&);

		class FileReader {
			friend FileReader& operator>>(FileReader&, int&);
			friend FileReader& operator>>(FileReader&, unsigned int&);
			friend FileReader& operator>>(FileReader&, char&);
			friend FileReader& operator>>(FileReader&, bool&);

		public:
			FileReader(std::string_view fileName) :
				_fileName(std::string{ fileName })
			{
				//_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				_file.open(std::string{ fileName });
			}

			~FileReader() {
				if (_file.is_open()) {
					_file.close();
				}
			}

			FileReader(const FileReader&) = delete;
			FileReader(FileReader&& rhs) = delete;

			FileReader& operator=(const FileReader&) = delete;
			FileReader& operator=(FileReader&& rhs) = delete;

			bool isOpen() const { return _file.is_open(); }

			const std::string& filename() const { return _fileName; }

			std::string getTextContent();
		private:
			std::string _fileName;
			std::ifstream _file;
		};
	}
}

#endif // !FILEREADER_H
