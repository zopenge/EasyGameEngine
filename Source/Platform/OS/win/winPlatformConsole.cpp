#include "EGEPlatform.h"

_chara Platform::GetAChar() {
	return ::getchar();
}

_charw Platform::GetWChar() {
	return ::getwchar();
}

_void Platform::WriteConsole(const _chara* string) {
	HANDLE console = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (console == INVALID_HANDLE_VALUE)
		return;

	::WriteConsoleA(console, string, Platform::StringLength(string), _null, _null);
}

_void Platform::WriteConsole(const _charw* string) {
	HANDLE console = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (console == INVALID_HANDLE_VALUE)
		return;

	::WriteConsoleW(console, string, Platform::StringLength(string), _null, _null);
}