#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// So strange, the XCODE compile report this function is not implement yet
inline void __eprintf(const char* fmt, const char* file, unsigned line, const char* e) {
	fprintf(stderr, fmt, file, line, e);
}