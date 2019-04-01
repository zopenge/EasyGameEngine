//! @file     StringFormatter.h
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Helpful Macros
//----------------------------------------------------------------------------

#define SET_PAR_BEGIN() \
	{                   \
		switch (paramnumber) {
#define SET_PAR_END() \
	default:          \
		break;        \
		}             \
		}
#define SET_PAR_DO(name)                                                                \
	SET_PAR_BEGIN()                                                                     \
	SET_PAR_##name(1, p1)                                                               \
	    SET_PAR_##name(2, p2)                                                           \
	        SET_PAR_##name(3, p3)                                                       \
	            SET_PAR_##name(4, p4)                                                   \
	                SET_PAR_##name(5, p5)                                               \
	                    SET_PAR_##name(6, p6)                                           \
	                        SET_PAR_##name(7, p7)                                       \
	                            SET_PAR_##name(8, p8)                                   \
	                                SET_PAR_##name(9, p9)                               \
	                                    SET_PAR_##name(10, p10)                         \
	                                        SET_PAR_##name(11, p11)                     \
	                                            SET_PAR_##name(12, p12)                 \
	                                                SET_PAR_##name(13, p13)             \
	                                                    SET_PAR_##name(14, p14)         \
	                                                        SET_PAR_##name(15, p15)     \
	                                                            SET_PAR_##name(16, p16) \
	                                                                SET_PAR_END()

#define SET_PAR(n, x)            \
	case n - 1: {                \
		EGE_ASSERT(n <= number); \
		x;                       \
	} break;
#define SET_PAR_INTEGER_DEC(n, x) SET_PAR(n, ParseFromString(x, substringbuffer, 10))
#define SET_PAR_INTEGER_HEX(n, x) SET_PAR(n, ParseFromString(x, substringbuffer, 16))
#define SET_PAR_FLOAT(n, x) SET_PAR(n, ParseFromString(x, substringbuffer))
#define SET_PAR_DOUBLE(n, x) SET_PAR(n, ParseFromString(x, substringbuffer))
#define SET_PAR_STRING(n, x) SET_PAR(n, ParseFromString(x, substringbuffer))

//----------------------------------------------------------------------------
// StringFormatter
//----------------------------------------------------------------------------

//! This class provides useful functions of string format.
class StringFormatter {
private:
	static _dword sUnusedInteger;

private:
	template <typename Type>
	static _void ParseFromString(Type& value, const _chara* string, _dword radix = 0);
	template <typename Type>
	static _void ParseFromString(Type& value, const _charw* string, _dword radix = 0);

	//! Parser string helper.
	template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
	static _dword ParseStringHelper(const CharType* string, const CharType* format, _dword number, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11, T12& p12, T13& p13, T14& p14, T15& p15, T16& p16);

public:
	//! Parse formated string by different number of parameter (ANSI/UNICODE version).
	template <typename CharType, typename T1>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1);

	template <typename CharType, typename T1, typename T2>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2);

	template <typename CharType, typename T1, typename T2, typename T3>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3);

	template <typename CharType, typename T1, typename T2, typename T3, typename T4>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4);

	template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5);

	template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6);

	template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7);

	template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8);

	template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9);

	template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10);

	template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11);

	template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11, T12& p12);

	template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11, T12& p12, T13& p13);

	template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11, T12& p12, T13& p13, T14& p14);

	template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11, T12& p12, T13& p13, T14& p14, T15& p15);

	template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
	static _dword ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11, T12& p12, T13& p13, T14& p14, T15& p15, T16& p16);

public:
	//! Split a string.
	//! @param string  The source string to be split.
	//! @param substrings The split strings.
	//! @param division The delimiter of source string.
	//! @param trim  The string what you want to trim from both.
	//! @return The total number of split sub-string elements.
	template <typename CharType>
	static _dword SplitString(CharType* string, CharType** substrings, const CharType* division, const CharType* trim);
	//! Split a string.
	//! @param string  The source string to be split.
	//! @param substrings The split strings.
	//! @param division The delimiter of source string.
	//! @param trim  The string what you want to trim from both.
	//! @return The total number of split sub-string elements.
	template <typename StringArrayType>
	static _dword SplitString(const typename StringArrayType::ElementType& string, StringArrayType& substrings, const typename StringArrayType::ElementType& division, const typename StringArrayType::ElementType& trim);
	//! Split a string.
	//! @param string  The source string to be split.
	//! @param substrings The split strings.
	//! @param division The delimiter of source string.
	//! @param trim  The string what you want to trim from both.
	//! @return The total number of split sub-string elements.
	template <typename ObjectType, typename StringType = ObjectType, typename ObjectArrayType = Array<ObjectType>>
	static _dword SplitStringToObject(const StringType& string, ObjectArrayType& substrings, const StringType& division, const StringType& trim);

	//! Check whether it's integer number.
	//! @param string  The string.
	//! @return True indicates it's integer number.
	static _ubool IsIntegerNumber(AStringPtr string);
	//! Check whether it's integer number.
	//! @param string  The string.
	//! @return True indicates it's integer number.
	static _ubool IsIntegerNumber(UStringPtr string);
	//! Check whether it's integer number.
	//! @param string  The string.
	//! @return True indicates it's integer number.
	static _ubool IsIntegerNumber(WStringPtr string);
	//! Check whether it's integer number.
	//! @param string  The string.
	//! @return True indicates it's integer number.
	static _ubool IsFloatPointNumber(AStringPtr string);
	//! Check whether it's integer number.
	//! @param string  The string.
	//! @return True indicates it's integer number.
	static _ubool IsFloatPointNumber(UStringPtr string);
	//! Check whether it's integer number.
	//! @param string  The string.
	//! @return True indicates it's integer number.
	static _ubool IsFloatPointNumber(WStringPtr string);

	//! Convert markup string to C string.
	//! @param markup_string The markup string.
	//! @return c_string  The C string.
	//! @return none.
	static _void ConvertMarkupString2CString(AStringPtr markup_string, AString& c_string);
	//! Convert markup string to C string.
	//! @param markup_string The markup string.
	//! @return c_string  The C string.
	//! @return none.
	static _void ConvertMarkupString2CString(UStringPtr markup_string, UString& c_string);
	//! Convert markup string to C string.
	//! @param markup_string The markup string.
	//! @return c_string  The C string.
	//! @return none.
	static _void ConvertMarkupString2CString(WStringPtr markup_string, WString& c_string);

	//! Convert string to '\Uxxxx' C string format.
	//! @param in_string  The string what you want to convert.
	//! @param out_string  The converted result string.
	//! @param all    True indicates convert all characters, otherwise just convert >= 128 code.
	//! @return none.
	static _void ConvertString2UPrefixString(WStringPtr in_string, WString& out_string, _ubool all);
	//! Convert '\Uxxxx' C string format to string.
	//! @param in_string  The string what you want to convert.
	//! @param out_string  The converted result string.
	//! @return none.
	static _void ConvertUPrefixString2String(WStringPtr in_string, WString& out_string);

	//! URL encode.
	//! @param in_string  The string what you want to convert.
	//! @param out_string  The converted result string.
	//! @return none.
	static _void URLEncode(WStringPtr in_string, WString& out_string);
	//! URL decode.
	//! @param in_string  The string what you want to convert.
	//! @param out_string  The converted result string.
	//! @return none.
	static _void URLDecode(WStringPtr in_string, WString& out_string);

	//! Search sub-string.
	//! @param in_string   The input string.
	//! @param sub_string   The sub-string what to search.
	//! @param match_whole_word True indicates match the whole word.
	//! @return The start index of sub-string.
	template <typename CharType, typename StringType>
	static _dword SearchL2R(StringType in_string, StringType sub_string, _ubool match_whole_word);
};

//----------------------------------------------------------------------------
// StringFormatter Implementation
//----------------------------------------------------------------------------

template <>
inline _void StringFormatter::ParseFromString<_tiny>(_tiny& value, const _chara* string, _dword radix) {
	value = Platform::ConvertStringToLong(string, radix);
}

template <>
inline _void StringFormatter::ParseFromString<_short>(_short& value, const _chara* string, _dword radix) {
	value = Platform::ConvertStringToLong(string, radix);
}

template <>
inline _void StringFormatter::ParseFromString<_int>(_int& value, const _chara* string, _dword radix) {
	value = Platform::ConvertStringToLong(string, radix);
}

template <>
inline _void StringFormatter::ParseFromString<_byte>(_byte& value, const _chara* string, _dword radix) {
	value = Platform::ConvertStringToDword(string, radix);
}

template <>
inline _void StringFormatter::ParseFromString<_word>(_word& value, const _chara* string, _dword radix) {
	value = Platform::ConvertStringToDword(string, radix);
}

template <>
inline _void StringFormatter::ParseFromString<_dword>(_dword& value, const _chara* string, _dword radix) {
	value = Platform::ConvertStringToDword(string, radix);
}

template <>
inline _void StringFormatter::ParseFromString<_float>(_float& value, const _chara* string, _dword radix) {
	value = Platform::ConvertStringToFloat(string);
}

template <>
inline _void StringFormatter::ParseFromString<_double>(_double& value, const _chara* string, _dword radix) {
	value = Platform::ConvertStringToDouble(string);
}

template <>
inline _void StringFormatter::ParseFromString<AString>(AString& value, const _chara* string, _dword radix) {
	value = string;
}

template <>
inline _void StringFormatter::ParseFromString<UString>(UString& value, const _chara* string, _dword radix) {
	value.FromString(Encoding::Ansi, string);
}

template <>
inline _void StringFormatter::ParseFromString<WString>(WString& value, const _chara* string, _dword radix) {
	value.FromString(Encoding::Ansi, string);
}

template <>
inline _void StringFormatter::ParseFromString<_tiny>(_tiny& value, const _charw* string, _dword radix) {
	value = Platform::ConvertStringToLong(string, radix);
}

template <>
inline _void StringFormatter::ParseFromString<_short>(_short& value, const _charw* string, _dword radix) {
	value = Platform::ConvertStringToLong(string, radix);
}

template <>
inline _void StringFormatter::ParseFromString<_int>(_int& value, const _charw* string, _dword radix) {
	value = Platform::ConvertStringToLong(string, radix);
}

template <>
inline _void StringFormatter::ParseFromString<_byte>(_byte& value, const _charw* string, _dword radix) {
	value = Platform::ConvertStringToDword(string, radix);
}

template <>
inline _void StringFormatter::ParseFromString<_word>(_word& value, const _charw* string, _dword radix) {
	value = Platform::ConvertStringToDword(string, radix);
}

template <>
inline _void StringFormatter::ParseFromString<_dword>(_dword& value, const _charw* string, _dword radix) {
	value = Platform::ConvertStringToDword(string, radix);
}

template <>
inline _void StringFormatter::ParseFromString<_float>(_float& value, const _charw* string, _dword radix) {
	value = Platform::ConvertStringToFloat(string);
}

template <>
inline _void StringFormatter::ParseFromString<_double>(_double& value, const _charw* string, _dword radix) {
	value = Platform::ConvertStringToDouble(string);
}

template <>
inline _void StringFormatter::ParseFromString<AString>(AString& value, const _charw* string, _dword radix) {
	value.FromString(Encoding::Utf16, string);
}

template <>
inline _void StringFormatter::ParseFromString<UString>(UString& value, const _charw* string, _dword radix) {
	value.FromString(Encoding::Utf16, string);
}

template <>
inline _void StringFormatter::ParseFromString<WString>(WString& value, const _charw* string, _dword radix) {
	value = string;
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
_dword StringFormatter::ParseStringHelper(const CharType* string, const CharType* format, _dword number, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11, T12& p12, T13& p13, T14& p14, T15& p15, T16& p16) {
	_dword paramnumber = 0;

	// Analyze the string
	_int j = 0;
	for (_int i = 0; format[i] != 0 && *string != 0;) {
		// Get the current and next character
		CharType currentchar = format[i];
		CharType nextchar = format[i + 1];

		// Check whether it's command key character or not
		if (currentchar == '%' && nextchar != '%' && nextchar != 0) {
			// Get the tail character
			CharType tailchar = format[i + 2];

			// Jump the '%?' character
			i += 2;
			j = i;

			// The sub-string buffer
			CharType substringbuffer[4096];
			substringbuffer[0] = 0;
			CharType* substring = substringbuffer;

			// Get the sub-string
			while (_true) {
				if (*string == tailchar || *string == 0) {
					// Complete to build the sub-string
					*substring = 0;
					break;
				}

				EGE_ASSERT(substring - substringbuffer < 4096);
				*substring++ = *string++;
			}

			// Integer-Decimal
			if (nextchar == 'd') {
				SET_PAR_DO(INTEGER_DEC)
			}
			// Integer-Hex
			else if (nextchar == 'x') {
				SET_PAR_DO(INTEGER_HEX)
			}
			// Float
			else if (nextchar == 'f') {
				SET_PAR_DO(FLOAT)
			}
			// String
			else if (nextchar == 's') {
				SET_PAR_DO(STRING)
			}
			// Break the procession when we get the unknown command character
			else {
				break;
			}

			// Increase the parameter number
			paramnumber++;
		}
		// It's normal character
		else {
			if (format[i] == *string)
				i++;
			else
				i = j;

			string++;
		}
	}

	return paramnumber;
}

template <typename CharType, typename T1>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1) {
	return ParseStringHelper(string, format, 1, p1,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger);
}

template <typename CharType, typename T1, typename T2>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2) {
	return ParseStringHelper(string, format, 2, p1, p2,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3) {
	return ParseStringHelper(string, format, 3, p1, p2, p3,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4) {
	return ParseStringHelper(string, format, 4, p1, p2, p3, p4,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5) {
	return ParseStringHelper(string, format, 5, p1, p2, p3, p4, p5,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6) {
	return ParseStringHelper(string, format, 6, p1, p2, p3, p4, p5, p6,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger,
	                         sUnusedInteger, sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7) {
	return ParseStringHelper(string, format, 7, p1, p2, p3, p4, p5, p6, p7,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger,
	                         sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8) {
	return ParseStringHelper(string, format, 8, p1, p2, p3, p4, p5, p6, p7, p8,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9) {
	return ParseStringHelper(string, format, 9, p1, p2, p3, p4, p5, p6, p7, p8, p9,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10) {
	return ParseStringHelper(string, format, 10, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11) {
	return ParseStringHelper(string, format, 11, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11, T12& p12) {
	return ParseStringHelper(string, format, 12, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger, sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11, T12& p12, T13& p13) {
	return ParseStringHelper(string, format, 13, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13,
	                         sUnusedInteger, sUnusedInteger, sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11, T12& p12, T13& p13, T14& p14) {
	return ParseStringHelper(string, format, 14, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,
	                         sUnusedInteger, sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11, T12& p12, T13& p13, T14& p14, T15& p15) {
	return ParseStringHelper(string, format, 15, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15,
	                         sUnusedInteger);
}

template <typename CharType, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
_dword StringFormatter::ParseString(const CharType* string, const CharType* format, T1& p1, T2& p2, T3& p3, T4& p4, T5& p5, T6& p6, T7& p7, T8& p8, T9& p9, T10& p10, T11& p11, T12& p12, T13& p13, T14& p14, T15& p15, T16& p16) {
	return ParseStringHelper(string, format, 15, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16);
}

template <typename CharType>
_dword StringFormatter::SplitString(CharType* string, CharType** substrings, const CharType* division, const CharType* trim) {
	_dword length = Platform::StringLength(string), start = -1;
	_dword number = 0;

	for (_dword i = 0; i < length; i++) {
		if (Platform::SearchL2R(division, string[i]) == -1) {
			// Start of a string
			if (start == -1)
				start = i;
		} else {
			// End of a string
			if (start != -1) {
				_dword candidate_length = i - start;

				// Build candidate string
				CharType* candidate = string + start;
				candidate[candidate_length] = 0;

				// Trim candidate string
				Platform::TrimStringBoth(candidate, candidate_length, trim);

				// It is valid string, can be part of output
				if (candidate_length > 0)
					substrings[number++] = candidate;

				start = -1;
			}
		}
	}

	// End of a string
	if (start != -1) {
		_dword candidate_length = length - start;

		// Build candidate string
		CharType* candidate = string + start;
		candidate[candidate_length] = 0;

		// Trim candidate string
		Platform::TrimStringBoth(candidate, candidate_length, trim);

		// It is valid string, can be part of output
		if (candidate_length > 0)
			substrings[number++] = candidate;
	}

	return number;
}

template <typename StringArrayType>
_dword StringFormatter::SplitString(const typename StringArrayType::ElementType& string, StringArrayType& substrings, const typename StringArrayType::ElementType& division, const typename StringArrayType::ElementType& trim) {
	return SplitStringToObject<typename StringArrayType::ElementType, typename StringArrayType::ElementType, StringArrayType>(string, substrings, division, trim);
}

template <typename ObjectType, typename StringType, typename ObjectArrayType>
_dword StringFormatter::SplitStringToObject(const StringType& string, ObjectArrayType& substrings, const StringType& division, const StringType& trim) {
	_dword length = string.GetLength(), start = -1;

	for (_dword i = 0; i < length; i++) {
		if (division.SearchL2R(string[i]) == -1) {
			// Start of a string
			if (start == -1)
				start = i;
		} else {
			// End of a string
			if (start != -1) {
				// Build candidate string
				StringType candidate(string.CStr() + start, i - start);

				// Trim candidate string
				candidate.TrimBoth(trim);

				// It is valid string, can be part of output
				if (candidate.IsEmpty() == _false)
					substrings.Append(candidate);

				start = -1;
			}
		}
	}

	// End of a string
	if (start != -1) {
		// Build candidate string
		StringType candidate(string.CStr() + start);

		// Trim candidate string
		candidate.TrimBoth(trim);

		// It is valid string, can be part of output
		if (candidate.IsEmpty() == _false)
			substrings.Append(candidate);
	}

	return substrings.Number();
}

template <typename CharType, typename StringType>
_dword StringFormatter::SearchL2R(StringType in_string, StringType sub_string, _ubool match_whole_word) {
	if (match_whole_word) {
		StringType in_string_temp = in_string;

		_dword offset = 0;

		while (_true) {
			_ubool found = _true;

			_dword begin_index = in_string.SearchL2R(sub_string);
			if (begin_index == -1)
				return -1;

			if (begin_index != 0) {
				CharType begin_char = in_string[begin_index - 1];
				if ((begin_char >= 'A' && begin_char <= 'Z') || (begin_char >= 'a' && begin_char <= 'z'))
					found = _false;
			}

			_dword end_index = begin_index + sub_string.GetLength();
			if (found) {
				CharType end_char = in_string[end_index];
				if ((end_char >= 'A' && end_char <= 'Z') || (end_char >= 'a' && end_char <= 'z'))
					found = _false;
			}

			if (found)
				return offset + begin_index;

			// Update offset
			offset += end_index + 1;
			EGE_ASSERT(offset < in_string_temp.GetLength());

			// Jump to the next string and go on
			in_string = in_string_temp.SubString(offset);
		}

		// Found nothing, never reach here
		return -1;
	} else {
		return in_string.SearchL2R(sub_string);
	}
}

} // namespace EGE
