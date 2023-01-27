#include "MessageBox.h"

#include <cstdlib>
#include <cstring>

#if defined(WIN32) || defined(_WIN32)
#include <stringapiset.h>
#else
#error "O.S. not supported"
#endif // defined(WIN32) || defined(_WIN32)


namespace K9ngineCore {
	bool K9MessageBox::ShowError(const char* msg, const char* file, unsigned line) {
		constexpr size_t SIZE_LINE_NR = 10;
		constexpr size_t SIZE = 240 + SIZE_LINE_NR;
		char completeMsg[SIZE];
		strcpy_s(completeMsg, msg);
		strcat_s(completeMsg, ". File ");
		strcat_s(completeMsg, file);
		strcat_s(completeMsg, ". Line");
		char lineStr[SIZE_LINE_NR];
		_itoa_s(line, lineStr, 10);
		strcat_s(completeMsg, lineStr);
#if defined(WIN32) || defined(_WIN32)
		WCHAR wCompleteMsg[SIZE];
		MultiByteToWideChar(CP_ACP, 0, completeMsg, SIZE, (LPWSTR)wCompleteMsg, SIZE);
		return MessageBox(NULL, wCompleteMsg, NULL, MB_OK) != 0;
#else
#error "O.S. not supported"
#endif // defined(WIN32) || defined(_WIN32)

	}
}