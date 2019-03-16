//! @file     IOSHeaders.h
//! @author   LiCode
//! @version  1.1.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// So strange, the XCODE compile report this function is not implement yet
inline void __eprintf(const char* fmt, const char* file, unsigned line,
                      const char* e) {
  fprintf(stderr, fmt, file, line, e);
}