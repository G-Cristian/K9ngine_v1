#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <string>

namespace K9ngineCore {
	namespace IO {
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
			FileReader(const std::string& fileName) :
				_fileName(fileName),
				_file(fileName)
			{
				//file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			}

			~FileReader() {
				if (_file.is_open()) {
					_file.close();
				}
			}

			FileReader(const FileReader&) = delete;
			FileReader(FileReader&& rhs) noexcept :
				_fileName(std::move(rhs._fileName)),
				_file(std::move(rhs._file))
			{
			}

			FileReader& operator=(const FileReader&) = delete;
			FileReader& operator=(FileReader&& rhs) noexcept;

			bool isOpen() const { return _file.is_open(); }

			const std::string& filename() const { return _fileName; }
		private:
			std::string _fileName;
			std::ifstream _file;
		};
	}
}

#endif // !FILEREADER_H
