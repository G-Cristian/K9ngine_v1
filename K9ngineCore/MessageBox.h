#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#if defined(WIN32) || defined(_WIN32)
#include<Windows.h>
#include <winuser.h>
#else
#error "O.S. not supported"
#endif // defined(WIN32) || defined(_WIN32)

namespace K9ngineCore {
	class K9MessageBox {
	public:
		static bool ShowError(const char* msg, const char* file, unsigned line);
	};
}

#endif // !MESSAGEBOX_H
