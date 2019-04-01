//! @file     anyPlatform.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Standard Functions Implementation
//----------------------------------------------------------------------------

#if defined(_PLATFORM_WINDOWS_)

extern "C" {

int gettimeofday(struct timeval* tp, struct timezone* tzp) {
	// Note: some broken versions only have 8 trailing zero's, the correct epoch
	// has 9 trailing zero's This magic number is the number of 100 nanosecond
	// intervals since January 1, 1601 (UTC) until 00:00:00 January 1, 1970
	static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);

	SYSTEMTIME system_time;
	FILETIME file_time;
	uint64_t time;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	time = ((uint64_t)file_time.dwLowDateTime);
	time += ((uint64_t)file_time.dwHighDateTime) << 32;

	tp->tv_sec = (long)((time - EPOCH) / 10000000L);
	tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
	return 0;
}
}

#endif

#if defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_)

extern "C" {

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Luk¨¢s Chmela
 * Released under GPLv3.
 */
//! I copy the code from 'http://www.strudel.org.uk/itoa/', thanks for
//! sharing it.
#	define __EGE_SIGNED2STRING_IMPL__(FunctionName, ValueType, CharType)                \
		CharType* FunctionName(ValueType value, CharType* result, int base) {            \
			if (base < 2 || base > 36) {                                                 \
				*result = (CharType)('\0');                                              \
				return result;                                                           \
			}                                                                            \
			CharType *ptr = result, *ptr1 = result, tmp_char;                            \
			ValueType tmp_value;                                                         \
			do {                                                                         \
				tmp_value = value;                                                       \
				value /= base;                                                           \
				*ptr++ = (CharType)(                                                     \
				    "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstu" \
				    "vwxyz"[35 + (tmp_value - value * base)]);                           \
			} while (value);                                                             \
			if (tmp_value < 0) *ptr++ = (CharType)('-');                                 \
			*ptr-- = (CharType)('\0');                                                   \
			while (ptr1 < ptr) {                                                         \
				tmp_char = *ptr;                                                         \
				*ptr-- = *ptr1;                                                          \
				*ptr1++ = tmp_char;                                                      \
			}                                                                            \
			return result;                                                               \
		}

//! I copy the code from
//!'http://www.codeforge.com/read/185702/UTOA.C__html', thanks for sharing it.
#	define __EGE_UNSIGNED2STRING_IMPL__(FunctionName, ValueType, CharType)           \
		CharType* FunctionName(ValueType value, CharType* result, int base) {         \
			int i, j;                                                                 \
			CharType c;                                                               \
			i = 0;                                                                    \
			do /* generate digits in reverse order:	*/                                \
			{                                                                         \
				result[i++] =                                                         \
				    (CharType)("0123456789abcdefghijklmnopqrstuvwxyz"[value % base]); \
			} while (value /= base);                                                  \
			result[i--] = 0; /* add null terminator	*/                                \
			for (j = 0; j < i; j++, i--) /*  now reverse chars */                     \
			{                                                                         \
				c = result[j];                                                        \
				result[j] = result[i];                                                \
				result[i] = c;                                                        \
			}                                                                         \
			return result;                                                            \
		}

__EGE_SIGNED2STRING_IMPL__(__ege_itoa__, int, char)
__EGE_SIGNED2STRING_IMPL__(__ege_i64toa__, signed long long, char)
__EGE_SIGNED2STRING_IMPL__(__ege_itow__, int, wchar_t)
__EGE_SIGNED2STRING_IMPL__(__ege_i64tow__, signed long long, wchar_t)

__EGE_UNSIGNED2STRING_IMPL__(__ege_utoa__, unsigned int, char)
__EGE_UNSIGNED2STRING_IMPL__(__ege_u64toa__, unsigned long long, char)
__EGE_UNSIGNED2STRING_IMPL__(__ege_utow__, unsigned int, wchar_t)
__EGE_UNSIGNED2STRING_IMPL__(__ege_u64tow__, unsigned long long, wchar_t)

#	undef __EGE_SIGNED2STRING_IMPL__
#	undef __EGE_UNSIGNED2STRING_IMPL__
}

#endif

// Ignore the localconv() function call link error
#if defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_)
extern "C" {

struct lconv* localeconv() {
	return _null;
}
}
#endif

//----------------------------------------------------------------------------
// anyPlatform Implementation
//----------------------------------------------------------------------------

_ubool anyPlatform::Initialize() {
	STATIC_ASSERT(sizeof(_chara) == 1, "Basic data type size check");
	STATIC_ASSERT(sizeof(_charw) == 2, "Basic data type size check");
	STATIC_ASSERT(sizeof(_tiny) == 1, "Basic data type size check");
	STATIC_ASSERT(sizeof(_short) == 2, "Basic data type size check");
	STATIC_ASSERT(sizeof(_int) == 4, "Basic data type size check");
	STATIC_ASSERT(sizeof(_byte) == 1, "Basic data type size check");
	STATIC_ASSERT(sizeof(_word) == 2, "Basic data type size check");
	STATIC_ASSERT(sizeof(_dword) == 4, "Basic data type size check");
	STATIC_ASSERT(sizeof(_long) == 4 || sizeof(_long) == 8,
	              "Basic data type size check");
	STATIC_ASSERT(sizeof(_large) == 8, "Basic data type size check");
	STATIC_ASSERT(sizeof(_qword) == 8, "Basic data type size check");
	STATIC_ASSERT(sizeof(_float) == 4, "Basic data type size check");
	STATIC_ASSERT(sizeof(_double) == 8, "Basic data type size check");
	STATIC_ASSERT(sizeof(_boolean) == 1, "Basic data type size check");
	STATIC_ASSERT(sizeof(_dword) == 4, "Basic data type size check");
	STATIC_ASSERT(sizeof(_ubool) == 4, "Basic data type size check");

	// Get the main thread ID ( the main thread ID could be changed by system, so
	// we need to update it)
	gMainThreadID = Platform::GetCurrentThreadID();
	EGE_ASSERT(gMainThreadID != 0);

	// Show the long type size, build time and main thread ID
	OUTPUT_DEBUG_STRING(
	    FORMAT_ASTRING_1("EGE: '_long' type size: %d\n", (_dword)sizeof(_long)));
	OUTPUT_DEBUG_STRING(
	    FORMAT_ASTRING_2("EGE: BuildTime: %s %s\n", _BUILDDATE_A, _BUILDTIME_A));
	OUTPUT_DEBUG_STRING(
	    FORMAT_ASTRING_1("EGE: MainThread: 0x%.16llx\n", gMainThreadID));

	return _true;
}

_void anyPlatform::Finalize() {
#if (_SHOW_SKIP_ASSERT_DIALOG == 1)
	gAssertSkipSrcFileLines.Clear();
#endif
}
