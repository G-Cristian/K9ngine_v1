#include "FileReader.h"

namespace K9ngineCore {
	namespace IO {
		FileReader& operator>>(FileReader& fileReader, int& outVal) {
			union {
				int val;
				unsigned char bs[4];
			};
			fileReader._file >> bs[0];
			fileReader._file >> bs[1];
			fileReader._file >> bs[2];
			fileReader._file >> bs[3];
			outVal = val;

			return fileReader;
		}

		FileReader& operator>>(FileReader& fileReader, unsigned int& outVal) {
			union {
				unsigned int val;
				unsigned char bs[4];
			};
			fileReader._file >> bs[0];
			fileReader._file >> bs[1];
			fileReader._file >> bs[2];
			fileReader._file >> bs[3];
			outVal = val;

			return fileReader;
		}

		FileReader& operator>>(FileReader& fileReader, char& outVal) {
			union {
				unsigned char uc;
				char c;
			};
			fileReader._file >> uc;
			outVal = c;

			return fileReader;
		}

		FileReader& operator>>(FileReader& fileReader, bool& outVal) {
			unsigned char b;
			fileReader._file >> b;

			outVal = (b != 0);

			return fileReader;
		}

		FileReader& FileReader::operator=(FileReader&& rhs) noexcept {
			if (this != &rhs) {
				_fileName.operator=(std::move(rhs._fileName));
				_file.operator=(std::move(rhs._file));
			}

			return *this;
		}
	}
}