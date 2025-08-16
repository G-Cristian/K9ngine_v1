#include "FileReader.h"

#include "../K9Debug.h"

#include <string>
#include <sstream>

namespace K9ngineCore {
	namespace FileSystem {
		FileReader& operator>>(FileReader& fileReader, int& outVal) {
      K9ASSERT(fileReader.isOpen(), "File is not open");
			if (!fileReader.isOpen()) {
				return fileReader;
			}

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
			K9ASSERT(fileReader.isOpen(), "File is not open");
			if (!fileReader.isOpen()) {
				return fileReader;
			}

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
			K9ASSERT(fileReader.isOpen(), "File is not open");
			if (!fileReader.isOpen()) {
				return fileReader;
			}

			union {
				unsigned char uc;
				char c;
			};
			fileReader._file >> uc;
			outVal = c;

			return fileReader;
		}

		FileReader& operator>>(FileReader& fileReader, bool& outVal) {
			K9ASSERT(fileReader.isOpen(), "File is not open");
			if (!fileReader.isOpen()) {
				return fileReader;
			}

			unsigned char b;
			fileReader._file >> b;

			outVal = (b != 0);

			return fileReader;
		}

		std::string FileReader::getTextContent()
		{
			K9ASSERT(isOpen(), "File is not open");
			if (!isOpen()) {
				return "";
			}

			std::stringstream ss;
			while (!_file.eof())
			{
        std::string line;
				std::getline(_file, line);
				ss << line << std::endl;
			}

      return ss.str();
		}
	}
}