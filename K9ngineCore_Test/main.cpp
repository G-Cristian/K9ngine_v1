#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>

#include "Handle.h"
#include "K9Debug.h"
#include "Path.h"

#define EXEC_TEST(name, success, fail, total) do{\
													total++;\
													bool res = name();\
													if(res)\
														success++;\
													else\
														fail++; \
													std::cout << "Test " << total << " (" #name << ") " << (res ? "SUCCESS" : "FAIL") << std::endl; \
												}while (false)

using namespace K9ngineCore;
using namespace K9ngineCore::Memory;
using namespace K9ngineCore::Utility;

/******** K9ASSERT ***********/
//bool showError();

/******** HANDLE TESTS ***********/
bool createIntTable();
bool addElement();
bool deleteElement();
bool createDeleteCreateElements();
bool getHandle();
bool getValid();
bool getInvalid();
bool starOperator();
bool nullHandleIsInvalid();

/******** PATH TESTS ***********/
bool getDirectoryEmptyString();
bool getDirectoryOnlyFileName();
bool getDirectoryHiddenNoFileName1();
bool getDirectoryHiddenNoFileName2();
bool getDirectoryNoHiddenNoFileName1();
bool getDirectoryNoHiddenNoFileName2();
bool getDirectoryFullPath();
bool getFileNameEmptyString();
bool getFileNameOnlyDirectory();
bool getFileNameNoDirectory();
bool getFileNameFullPath();
bool getFileNameNoExtensionNoDirectory();
bool getFileNameNoExtensionFullPath();
bool getExtensionEmptyString();
bool getExtensionNoFileName();
bool getExtensionOnlyFileName();
bool getExtensionFullPath();

int main(int argc, char** argv) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	int success = 0;
	int fail = 0;
	int total = 0;

	/******** K9ASSERT ***********/
	//EXEC_TEST(showError,success, fail, total);

	/********* HANDLE TESTS *************/
	EXEC_TEST(createIntTable, success, fail, total);
	EXEC_TEST(addElement, success, fail, total);
	EXEC_TEST(deleteElement, success, fail, total);
	EXEC_TEST(createDeleteCreateElements, success, fail, total);
	EXEC_TEST(getHandle, success, fail, total);
	EXEC_TEST(getValid, success, fail, total);
	EXEC_TEST(getInvalid, success, fail, total);
	EXEC_TEST(starOperator, success, fail, total);
	EXEC_TEST(nullHandleIsInvalid, success, fail, total);

	/********* PATH TESTS *************/
	EXEC_TEST(getDirectoryEmptyString, success, fail, total);
	EXEC_TEST(getDirectoryOnlyFileName, success, fail, total);
	EXEC_TEST(getDirectoryHiddenNoFileName1, success, fail, total);
	EXEC_TEST(getDirectoryHiddenNoFileName2, success, fail, total);
	EXEC_TEST(getDirectoryNoHiddenNoFileName1, success, fail, total);
	EXEC_TEST(getDirectoryNoHiddenNoFileName2, success, fail, total);
	EXEC_TEST(getDirectoryFullPath, success, fail, total);
	EXEC_TEST(getFileNameEmptyString, success, fail, total);
	EXEC_TEST(getFileNameOnlyDirectory, success, fail, total);
	EXEC_TEST(getFileNameNoDirectory, success, fail, total);
	EXEC_TEST(getFileNameFullPath, success, fail, total);
	EXEC_TEST(getFileNameNoExtensionNoDirectory, success, fail, total);
	EXEC_TEST(getFileNameNoExtensionFullPath, success, fail, total);
	EXEC_TEST(getExtensionEmptyString, success, fail, total);
	EXEC_TEST(getExtensionNoFileName, success, fail, total);
	EXEC_TEST(getExtensionOnlyFileName, success, fail, total);
	EXEC_TEST(getExtensionFullPath, success, fail, total);

	std::cout << std::endl;
	std::cout << "SUCCESS: " << success << std::endl;
	std::cout << "FAIL: " << fail << std::endl;
	std::cout << "TOTAL: " << total << std::endl;

	std::cout << std::endl;
	
	//_CrtDumpMemoryLeaks();
	
	return 0;
}

/******** K9ASSERT ***********/
//bool showError() {
//	K9ASSERT(false, "Asserted");
//	return true;
//}

/******** HANDLE TESTS ***********/
bool createIntTable() {
	using namespace K9ngineCore::Memory;
	HandleTable<int> table(2);
	return true;
}

bool addElement() {
	using namespace K9ngineCore::Memory;

	HandleTable<int> table(1);
	return table.createHandle(1, new int(1)) == 0;
}

bool deleteElement() {
	using namespace K9ngineCore::Memory;

	HandleTable<int> table(1);
	table.createHandle(1, new int(1));
	table.deleteHandle(0);

	return true;
}

bool createDeleteCreateElements() {
	using namespace K9ngineCore::Memory;

	HandleTable<int> table(4);
	size_t h1_0 = table.createHandle(1, new int(1));
	size_t h2_1 = table.createHandle(2, new int(2));
	size_t h3_2 = table.createHandle(3, new int(3));
	size_t h4_3 = table.createHandle(4, new int(4));
	table.deleteHandle(1);
	table.deleteHandle(2);
	size_t h5_2 = table.createHandle(5, new int(5));
	table.deleteHandle(3);
	size_t h6_3 = table.createHandle(6, new int(6));
	size_t h7_1 = table.createHandle(7, new int(7));

	return h1_0 == 0 && h2_1 == 1 && h3_2 == 2 && h4_3 == 3 && h5_2 == 2 && h6_3 == 3 && h7_1 == 1;
}

bool getHandle() {
	using namespace K9ngineCore::Memory;

	HandleTable<int> table(1);
	table.createHandle(1, new int(2));
	Handle<int> handle = table.getHandle(0);
	return true;
}

bool getValid() {
	using namespace K9ngineCore::Memory;

	HandleTable<int> table(1);
	table.createHandle(1, new int(2));
	Handle<int> handle = table.getHandle(0);
	return handle.isValid();
}

bool getInvalid() {
	using namespace K9ngineCore::Memory;

	HandleTable<int> table(1);
	table.createHandle(1, new int(2));
	Handle<int> handle = table.getHandle(0);
	table.deleteHandle(0);
	return !handle.isValid();
}

bool starOperator() {
	using namespace K9ngineCore::Memory;

	HandleTable<int> table(2);
	size_t h1 = table.createHandle(1, new int(1));
	size_t h2 = table.createHandle(2, new int(2));

	Handle<int> handle1 = table.getHandle(h1);
	Handle<int> handle2 = table.getHandle(h2);

	return *handle1 == 1 && *handle2 == 2;
}

bool nullHandleIsInvalid() {
	using namespace K9ngineCore::Memory;
	Handle<int> nullHandle = HandleTable<int>::NullHandle;

	return !nullHandle.isValid();
}

/********* PATH TESTS *************/
bool getDirectoryEmptyString() {
	return Path::getDirectory("") == std::string("");
}

bool getDirectoryOnlyFileName() {
	return Path::getDirectory(".file.txt") == std::string("");
}

bool getDirectoryHiddenNoFileName1() {
	std::string directory(".dir1");
	directory += Path::Separator + std::string("dir2");
	return Path::getDirectory(directory) == std::string(".dir1")+Path::Separator+ std::string("dir2");
}

bool getDirectoryHiddenNoFileName2() {
	std::string directory("dir1");
	directory += Path::Separator + std::string(".dir2") + Path::Separator;
	return Path::getDirectory(directory) == std::string("dir1") + Path::Separator + std::string(".dir2");
}

bool getDirectoryNoHiddenNoFileName1() {
	std::string directory("dir1");
	directory += Path::Separator + std::string("dir2");
	return Path::getDirectory(directory) == std::string("dir1") + Path::Separator + std::string("dir2");
}

bool getDirectoryNoHiddenNoFileName2() {
	std::string directory("dir1");
	directory += Path::Separator + std::string("dir2") + Path::Separator;
	return Path::getDirectory(directory) == std::string("dir1") + Path::Separator + std::string("dir2");
}

bool getDirectoryFullPath() {
	std::string directory("dir1");
	directory += Path::Separator + std::string(".dir2") + Path::Separator + ".fileName.txt";
	return Path::getDirectory(directory) == std::string("dir1") + Path::Separator + std::string(".dir2");
}

bool getFileNameEmptyString() {
	return Path::getFileName("") == std::string("");
}

bool getFileNameOnlyDirectory() {
	std::string directory(".dir1");
	directory += Path::Separator + std::string("dir2");
	return Path::getFileName(directory) == std::string("");
}

bool getFileNameNoDirectory() {
	return Path::getFileName(".filename.txt") == std::string(".filename.txt");
}

bool getFileNameFullPath() {
	std::string directory("dir1");
	directory += Path::Separator + std::string(".dir2") + Path::Separator + ".fileName.txt";
	return Path::getFileName(directory) == std::string(".fileName.txt");
}

bool getFileNameNoExtensionNoDirectory() {
	return Path::getFileNameWithoutExtension(".filename.txt") == std::string(".filename");
}

bool getFileNameNoExtensionFullPath() {
	std::string directory("dir1");
	directory += Path::Separator + std::string(".dir2") + Path::Separator + ".fileName.txt";
	return Path::getFileNameWithoutExtension(directory) == std::string(".fileName");
}

bool getExtensionEmptyString() {
	return Path::getExtension("") == std::string("");
}

bool getExtensionNoFileName() {
	std::string directory("dir1");
	directory += Path::Separator + std::string(".dir2") + Path::Separator;
	return Path::getExtension(directory) == std::string("");
}

bool getExtensionOnlyFileName() {
	return Path::getExtension(".filename.txt") == std::string("txt");
}

bool getExtensionFullPath() {
	std::string directory(".dir1");
	directory += Path::Separator + std::string(".fileName.txt");
	return Path::getExtension(directory) == std::string("txt");
}