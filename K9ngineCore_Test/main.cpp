#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include "Handle.h"

#define EXEC_TEST(name, success, fail, total) do{\
													total++;\
													bool res = name();\
													if(res)\
														success++;\
													else\
														fail++; \
													std::cout << "Test " << total << " (" #name << ") " << (res ? "SUCCESS" : "FAIL") << std::endl; \
												}while (false)

bool createIntTable();
bool addElement();
bool deleteElement();
bool createDeleteCreateElements();
bool getHandle();
bool getValid();
bool getInvalid();
bool starOperator();

int main(int argc, char** argv) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	int success = 0;
	int fail = 0;
	int total = 0;

	EXEC_TEST(createIntTable, success, fail, total);
	EXEC_TEST(addElement, success, fail, total);
	EXEC_TEST(deleteElement, success, fail, total);
	EXEC_TEST(createDeleteCreateElements, success, fail, total);
	EXEC_TEST(getHandle, success, fail, total);
	EXEC_TEST(getValid, success, fail, total);
	EXEC_TEST(getInvalid, success, fail, total);
	EXEC_TEST(starOperator, success, fail, total);

	std::cout << std::endl;
	std::cout << "SUCCESS: " << success << std::endl;
	std::cout << "FAIL: " << fail << std::endl;
	std::cout << "TOTAL: " << total << std::endl;

	std::cout << std::endl;
	
	//_CrtDumpMemoryLeaks();
	
	return 0;
}

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