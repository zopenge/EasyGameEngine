#include "EGEPlatform.h"

EGE_INTERNAL void __ege__assert(const wchar_t* error, const wchar_t* filename, unsigned int linenumber) {
	Platform::AssertReport(error, filename, linenumber);
}