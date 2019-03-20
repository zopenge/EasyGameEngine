//! @file     EGE_TypeChecker.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

//----------------------------------------------------------------------------
// TypeChecker
//----------------------------------------------------------------------------

#define TYPE_CHECKER(x)     \
	namespace EGE {         \
	template <>             \
	struct TypeChecker<x> { \
		TypeChecker(x) {    \
		}                   \
	};                      \
	}

// We will declare type checker class here
template <class T>
struct TypeChecker;

// Common types
TYPE_CHECKER(_chara*)
TYPE_CHECKER(_charw*)
TYPE_CHECKER(const _chara*)
TYPE_CHECKER(const _charw*)
TYPE_CHECKER(const _void*)
TYPE_CHECKER(_void*)
TYPE_CHECKER(_chara)
TYPE_CHECKER(_charw)
TYPE_CHECKER(_tiny)
TYPE_CHECKER(_short)
TYPE_CHECKER(_byte)
TYPE_CHECKER(_word)
TYPE_CHECKER(_int)
TYPE_CHECKER(_dword)
TYPE_CHECKER(_long)
TYPE_CHECKER(_large)
TYPE_CHECKER(_qword)
TYPE_CHECKER(_float)
TYPE_CHECKER(_double)
TYPE_CHECKER(_ubool)
TYPE_CHECKER(_boolean)

// Enable the type checker
#ifdef _DEBUG
#	define CHECK_ARG(i, var) TypeChecker<T##i> checker##i(var)
// Disable the type checker
#else
#	define CHECK_ARG(i, var)
#endif

#define FORMAT_STRING_1(p1) \
	Platform::FormatStringByArguments(buffer, size, format, p1)
#define FORMAT_STRING_2(p1, p2) \
	Platform::FormatStringByArguments(buffer, size, format, p1, p2)
#define FORMAT_STRING_3(p1, p2, p3) \
	Platform::FormatStringByArguments(buffer, size, format, p1, p2, p3)
#define FORMAT_STRING_4(p1, p2, p3, p4) \
	Platform::FormatStringByArguments(buffer, size, format, p1, p2, p3, p4)
#define FORMAT_STRING_5(p1, p2, p3, p4, p5) \
	Platform::FormatStringByArguments(buffer, size, format, p1, p2, p3, p4, p5)
#define FORMAT_STRING_6(p1, p2, p3, p4, p5, p6)                                 \
	Platform::FormatStringByArguments(buffer, size, format, p1, p2, p3, p4, p5, \
	                                  p6)
#define FORMAT_STRING_7(p1, p2, p3, p4, p5, p6, p7)                             \
	Platform::FormatStringByArguments(buffer, size, format, p1, p2, p3, p4, p5, \
	                                  p6, p7)
#define FORMAT_STRING_8(p1, p2, p3, p4, p5, p6, p7, p8)                         \
	Platform::FormatStringByArguments(buffer, size, format, p1, p2, p3, p4, p5, \
	                                  p6, p7, p8)
#define FORMAT_STRING_9(p1, p2, p3, p4, p5, p6, p7, p8,                         \
                        p9)                                                     \
	Platform::FormatStringByArguments(buffer, size, format, p1, p2, p3, p4, p5, \
	                                  p6, p7, p8, p9)
#define FORMAT_STRING_10(p1, p2, p3, p4, p5, p6, p7, p8,                        \
                         p9, p10)                                               \
	Platform::FormatStringByArguments(buffer, size, format, p1, p2, p3, p4, p5, \
	                                  p6, p7, p8, p9, p10)
#define FORMAT_STRING_11(p1, p2, p3, p4, p5, p6, p7, p8,                        \
                         p9, p10, p11)                                          \
	Platform::FormatStringByArguments(buffer, size, format, p1, p2, p3, p4, p5, \
	                                  p6, p7, p8, p9, p10, p11)
#define FORMAT_STRING_12(p1, p2, p3, p4, p5, p6, p7, p8,                        \
                         p9, p10, p11, p12)                                     \
	Platform::FormatStringByArguments(buffer, size, format, p1, p2, p3, p4, p5, \
	                                  p6, p7, p8, p9, p10, p11, p12)
#define FORMAT_STRING_13(p1, p2, p3, p4, p5, p6, p7, p8,                        \
                         p9, p10, p11, p12, p13)                                \
	Platform::FormatStringByArguments(buffer, size, format, p1, p2, p3, p4, p5, \
	                                  p6, p7, p8, p9, p10, p11, p12, p13)

#define _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_1(p1) \
	FORMAT_STRING_1(p1)
#define _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_2(p1, p2) \
	FORMAT_STRING_2(p1, p2)
#define _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_3(p1, p2, p3) \
	FORMAT_STRING_3(p1, p2, p3)
#define _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_4(p1, p2, p3, p4) \
	FORMAT_STRING_4(p1, p2, p3, p4)
#define _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_5(p1, p2, p3, p4, p5) \
	FORMAT_STRING_5(p1, p2, p3, p4, p5)
#define _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_6(p1, p2, p3, p4, p5, p6) \
	FORMAT_STRING_6(p1, p2, p3, p4, p5, p6)
#define _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_7(p1, p2, p3, p4, p5, p6, p7) \
	FORMAT_STRING_7(p1, p2, p3, p4, p5, p6, p7)
#define _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_8(p1, p2, p3, p4, p5, p6, p7, p8) \
	FORMAT_STRING_8(p1, p2, p3, p4, p5, p6, p7, p8)
#define _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_9(p1, p2, p3, p4, p5, p6, p7, p8, \
                                             p9)                             \
	FORMAT_STRING_9(p1, p2, p3, p4, p5, p6, p7, p8, p9)
#define _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_10(p1, p2, p3, p4, p5, p6, p7, p8, \
                                              p9, p10)                        \
	FORMAT_STRING_10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)
#define _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_11(p1, p2, p3, p4, p5, p6, p7, p8, \
                                              p9, p10, p11)                   \
	FORMAT_STRING_11(buffer, size, format, p1, p2, p3, p4,                    \
	                 p5, p6, p7, p8, p9, p10, p11)
#define _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_12(p1, p2, p3, p4, p5, p6, p7, p8, \
                                              p9, p10, p11, p12)              \
	FORMAT_STRING_12(buffer, size, format, p1, p2, p3, p4,                    \
	                 p5, p6, p7, p8, p9, p10, p11, p12)
#define _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_13(p1, p2, p3, p4, p5, p6, p7, p8, \
                                              p9, p10, p11, p12, p13)         \
	FORMAT_STRING_13(buffer, size, format, p1, p2, p3, p4,                    \
	                 p5, p6, p7, p8, p9, p10, p11, p12, p13)

#define _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_1(p1) \
	FORMAT_STRING_1(p1)
#define _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_2(p1, p2) \
	FORMAT_STRING_2(p1, p2)
#define _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_3(p1, p2, p3) \
	FORMAT_STRING_3(p1, p2, p3)
#define _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_4(p1, p2, p3, p4) \
	FORMAT_STRING_4(p1, p2, p3, p4)
#define _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_5(p1, p2, p3, p4, p5) \
	FORMAT_STRING_5(p1, p2, p3, p4, p5)
#define _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_6(p1, p2, p3, p4, p5, p6) \
	FORMAT_STRING_6(p1, p2, p3, p4, p5, p6)
#define _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_7(p1, p2, p3, p4, p5, p6, p7) \
	FORMAT_STRING_7(p1, p2, p3, p4, p5, p6, p7)
#define _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_8(p1, p2, p3, p4, p5, p6, p7, p8) \
	FORMAT_STRING_8(p1, p2, p3, p4, p5, p6, p7, p8)
#define _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_9(p1, p2, p3, p4, p5, p6, p7, p8, \
                                             p9)                             \
	FORMAT_STRING_9(p1, p2, p3, p4, p5, p6, p7, p8, p9)
#define _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_10(p1, p2, p3, p4, p5, p6, p7, p8, \
                                              p9, p10)                        \
	FORMAT_STRING_10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)
#define _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_11(p1, p2, p3, p4, p5, p6, p7, p8, \
                                              p9, p10, p11)                   \
	FORMAT_STRING_11(buffer, size, format, p1, p2, p3, p4,                    \
	                 p5, p6, p7, p8, p9, p10, p11)
#define _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_12(p1, p2, p3, p4, p5, p6, p7, p8, \
                                              p9, p10, p11, p12)              \
	FORMAT_STRING_12(buffer, size, format, p1, p2, p3, p4,                    \
	                 p5, p6, p7, p8, p9, p10, p11, p12)
#define _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_13(p1, p2, p3, p4, p5, p6, p7, p8, \
                                              p9, p10, p11, p12, p13)         \
	FORMAT_STRING_13(buffer, size, format, p1, p2, p3, p4,                    \
	                 p5, p6, p7, p8, p9, p10, p11, p12, p13)
