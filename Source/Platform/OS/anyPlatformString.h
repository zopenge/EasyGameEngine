#pragma once

namespace EGE {

/// <summary>
/// The any-platform string.
/// </summary>
class anyPlatformString {
protected:
	//! Compare two characters.
	//! @param c1    The character 1.
	//! @param c2    The character 2.
	//! @param ignorecase  True indicates case insensitive.
	//! @return True indicates it's equal.
	template <typename CharType>
	static _ubool Equal(CharType c1, CharType c2, _ubool ignorecase);

public:
	//! Determine if string is empty, or looks like blank.
	//! @param string  The string.
	//! @return True if blank, false otherwise.
	template <class CharType>
	static _ubool IsBlank(const CharType* string);
	//! Determine the path is a full path or not, a full path will begin with "X:" or "\\"
	//! @param path  The path.
	//! @return True if full path, false otherwise.
	template <class CharType>
	static _ubool IsFullpath(const CharType* path);

	//! Trim string from left to right.
	//! @param string   The string buffer.
	//! @param stringlength The string buffer length.
	//! @param character  The character what you want to trim.
	//! @param ignorecase  True indicates case insensitive.
	//! @return The trimmed string.
	template <typename CharType>
	static CharType* TrimStringLeft(CharType* string, _dword& stringlength, CharType character, _ubool ignorecase);
	//! Trim string from right to left.
	//! @param string   The string buffer.
	//! @param stringlength The string buffer length.
	//! @param character  The character what you want to trim.
	//! @param ignorecase  True indicates case insensitive.
	//! @return The trimmed string.
	template <typename CharType>
	static CharType* TrimStringRight(CharType* string, _dword& stringlength, CharType character, _ubool ignorecase);

	//! Trim string from left to right.
	//! @param string   The string buffer.
	//! @param stringlength The string buffer length.
	//! @param charset   The substring what you want to trim.
	//! @param ignorecase  True indicates case insensitive.
	//! @return The trimmed string.
	template <typename CharType>
	static CharType* TrimStringLeft(CharType* string, _dword& stringlength, const CharType* charset, _ubool ignorecase);
	//! Trim string from right to left.
	//! @param string   The string buffer.
	//! @param stringlength The string buffer length.
	//! @param charset   The substring what you want to trim.
	//! @param ignorecase  True indicates case insensitive.
	//! @return The trimmed string.
	template <typename CharType>
	static CharType* TrimStringRight(CharType* string, _dword& stringlength, const CharType* charset, _ubool ignorecase);

	//! Search a character in the string from left to right.
	//! @param string   The string buffer.
	//! @param character  The character to be searched.
	//! @param ignorecase  True indicates case insensitive.
	//! @return The index of the first occurrence of the character or -1 indicates cant find.
	template <typename CharType>
	static _dword SearchL2R(const CharType* string, CharType character, _ubool ignorecase);
	//! Search a character in the string from right to left.
	//! @param string   The string buffer.
	//! @param character  The character to be searched.
	//! @param ignorecase  True indicates case insensitive.
	//! @return The index of the first occurrence of the character or -1 indicates cant find.
	template <typename CharType>
	static _dword SearchR2L(const CharType* string, CharType character, _ubool ignorecase);

	//! Search a substring in the string from left to right.
	//! @param string   The string buffer.
	//! @param substring  The substring to be searched.
	//! @param ignorecase  True indicates case insensitive.
	//! @param endindex  The end index of searching.
	//! @return The index of the first occurrence of the substring or -1 indicates cant find.
	template <typename CharType>
	static _dword SearchL2R(const CharType* string, const CharType* substring, _ubool ignorecase, _dword* endindex);
	//! Search a substring in the string from right to left.
	//! @param string   The string buffer.
	//! @param substring  The substring to be searched.
	//! @param ignorecase  True indicates case insensitive.
	//! @param startindex  The start index of searching.
	//! @return The index of the first occurrence of the substring or -1 indicates cant find.
	template <typename CharType>
	static _dword SearchR2L(const CharType* string, const CharType* substring, _ubool ignorecase, _dword* startindex);

	//! Copy string.
	//! @param desbuffer  The dest string buffer.
	//! @param srcbuffer  The src string buffer.
	//! @param number   The number of characters to be copied, -1 indicates auto-detected.
	//! @return The dest string buffer.
	template <typename CharType>
	static CharType* CopyString(CharType* desbuffer, const CharType* srcbuffer, _dword number = -1);

	//! Append string.
	//! @param desbuffer  The dest string buffer.
	//! @param srcbuffer  The src string buffer.
	//! @return The dest string buffer.
	template <typename CharType>
	static CharType* AppendString(CharType* desbuffer, const CharType* srcbuffer);

	//! Compare two string.
	//! @param string1   The string 1.
	//! @param string2   The string 2.
	//! @param ignorecase  True indicates case insensitive.
	//! @return -1    The string 1 is smaller than string 2. <br>
	//!     0    The string 1 is equal to string 2. <br>
	//!     1    The string 1 is bigger than string 2.
	template <typename CharType>
	static _int CompareString(const CharType* string1, const CharType* string2, _ubool ignorecase = _false);
	//! Compare two characters in case insensitive mode.
	//! @param c1    The character 1.
	//! @param c2    The character 2.
	//! @param ignorecase  True indicates case insensitive.
	//! @return -1    The character 1 is smaller than character 2. <br>
	//!     0    The character 1 is equal to character 2. <br>
	//!     1    The character 1 is bigger than character 2.
	template <typename CharType>
	static _int CompareCase(CharType c1, CharType c2, _ubool ignorecase = _false);
	//! Compare two strings with wildcards.
	//! @param string   The first string will to be searched.
	//! @param matchstring  The second string with wildcards to search.
	//! @param ignorecase  True indicates case insensitive.
	//! @return True if the string meets the wildcard, false otherwise.
	//! @remarks Wildcards must in the second string, otherwise it will be normal character.<br>
	//!    <b>'*'</b> meets zero or more character.<br>
	//!    <b>'?'</b> meets exactly one character.<br>
	//!    '*' must not adjacent with other wildcards together, otherwise will get wrong result.
	//!    For example, "Hello" will meets "He??o" or "H*o" or "*Hello".
	template <typename CharType>
	static _ubool CompareWildcard(const CharType* string, const CharType* matchstring, _ubool ignorecase);

	//! Get string length.
	//! @param string   The string.
	//! @return The string length of string.
	template <typename CharType>
	static _dword StringLength(const CharType* string);

	//! Convert string to lowercase.
	//! @param string   The string.
	//! @param number   The number of characters to convert.
	//! @return The converted string.
	template <typename CharType>
	static CharType* LowercaseString(CharType* string, _dword number = -1);
	//! Convert string to uppercase.
	//! @param string   The string.
	//! @param number   The number of characters to convert.
	//! @return The converted string.
	template <typename CharType>
	static CharType* UppercaseString(CharType* string, _dword number = -1);

public:
	static _dword AnsiToUtf16(_charw* buffer, _dword size, const _chara* string, _dword number = -1);
	static _dword Utf16ToAnsi(_chara* buffer, _dword size, const _charw* string, _dword number = -1);

	static _dword Utf8ToUtf16(_charw* buffer, _dword size, const _chara* string, _dword number = -1);
	static _dword Utf16ToUtf8(_chara* buffer, _dword size, const _charw* string, _dword number = -1);

	static _chara* FormatStringByVAList(_chara* buffer, _dword size, const _chara* format, _va_list arguments);
	static _charw* FormatStringByVAList(_charw* buffer, _dword size, const _charw* format, _va_list arguments);

	static _dword GetFormatStringLength(const _chara* format, _va_list arguments);
	static _dword GetFormatStringLength(const _charw* format, _va_list arguments);
};

template <typename CharType>
_ubool anyPlatformString::Equal(CharType c1, CharType c2, _ubool ignorecase) {
	if (ignorecase)
		return tolower(c1) == tolower(c2);
	else
		return c1 == c2;
}

template <class CharType>
_ubool anyPlatformString::IsBlank(const CharType* string) {
	for (_dword i = 0; string[i] != 0; i++) {
		if (string[i] != ' ' && string[i] != '\t' && string[i] != '\r' && string[i] != '\n')
			return _false;
	}

	return _true;
}

template <class CharType>
_ubool anyPlatformString::IsFullpath(const CharType* path) {
	// \\fileserver\test\abc.txt, that is a full path.
	if (path[0] == '\\' && path[1] == '\\')
		return _true;

	if (path[1] != ':')
		return _false;

	// D:\Project\abc.txt, that is a full path too.
	if (path[0] >= 'A' && path[0] <= 'Z')
		return _true;

	// d:\Project\abc.txt, that is a full path too.
	if (path[0] >= 'a' && path[0] <= 'z')
		return _true;

	return _false;
}

template <typename CharType>
CharType* anyPlatformString::TrimStringLeft(CharType* string, _dword& stringlength, CharType character, _ubool ignorecase) {
	if (string == _null)
		return _null;

	if (string[0] == 0)
		return string;

	// Get the string length
	if (stringlength == 0)
		stringlength = Platform::StringLength(string);

	// Get the trim sub-string length
	_dword i = 0;
	for (; string[i] != 0; i++) {
		if (anyPlatformString::Equal(string[i], character, ignorecase) == _false)
			break;
	}

	// Move string to trim sub-string from left
	if (i > 0) {
		if (i == stringlength)
			string[0] = 0;
		else
			EGE_MEM_MOVE(string, string + i, (stringlength - i) * sizeof(CharType));

		// Feedback the string length
		stringlength -= i;

		// Set the tail of string
		string[stringlength] = 0;
	}

	return string;
}

template <typename CharType>
CharType* anyPlatformString::TrimStringRight(CharType* string, _dword& stringlength, CharType character, _ubool ignorecase) {
	if (string == _null)
		return _null;

	if (string[0] == 0)
		return string;

	// Get the string length
	if (stringlength == 0)
		stringlength = Platform::StringLength(string);

	// Get the trim sub-string length
	_dword i = 0;
	for (; string[i] != 0; i++) {
		if (anyPlatformString::Equal(string[stringlength - i - 1], character, ignorecase) == _false)
			break;
	}

	// Move string to trim sub-string from left
	if (i > 0) {
		// Feedback the string length
		stringlength -= i;

		// Trim sub-string from right
		string[stringlength] = 0;
	}

	return string;
}

template <typename CharType>
CharType* anyPlatformString::TrimStringLeft(CharType* string, _dword& stringlength, const CharType* charset, _ubool ignorecase) {
	if (string == _null)
		return _null;

	if (string[0] == 0)
		return string;

	// Get the string length
	if (stringlength == 0)
		stringlength = Platform::StringLength(string);

	// Get the trim character string length
	_dword charsetlength = Platform::StringLength(charset);
	if (charsetlength == 0)
		return string;

	// Get the trim sub-string length
	_dword i = 0;
	for (; string[i] != 0; i++) {
		_dword j = 0;
		for (; j < charsetlength; j++) {
			if (anyPlatformString::Equal(string[i], charset[j], ignorecase))
				break;
		}

		if (j == charsetlength)
			break;
	}

	// Move string to trim sub-string from left
	if (i > 0) {
		if (i == stringlength)
			string[0] = 0;
		else
			EGE_MEM_MOVE(string, string + i, (stringlength - i) * sizeof(CharType));

		// Feedback the string length
		stringlength -= i;

		// Set the tail of string
		string[stringlength] = 0;
	}

	return string;
}

template <typename CharType>
CharType* anyPlatformString::TrimStringRight(CharType* string, _dword& stringlength, const CharType* charset, _ubool ignorecase) {
	if (string == _null)
		return _null;

	if (string[0] == 0)
		return string;

	// Get the string length
	if (stringlength == 0)
		stringlength = Platform::StringLength(string);

	// Get the trim character string length
	_dword charsetlength = Platform::StringLength(charset);
	if (charsetlength == 0)
		return string;

	// Get the trim sub-string length
	_dword i = 0;
	for (; string[i] != 0; i++) {
		_dword j = 0;
		for (; j < charsetlength; j++) {
			if (anyPlatformString::Equal(string[stringlength - i - 1], charset[j], ignorecase))
				break;
		}

		if (j == charsetlength)
			break;
	}

	// Move string to trim sub-string from left
	if (i > 0) {
		// Feedback the string length
		stringlength -= i;

		// Trim sub-string from right
		string[stringlength] = 0;
	}

	return string;
}

template <typename CharType>
_dword anyPlatformString::SearchL2R(const CharType* string, CharType character, _ubool ignorecase) {
	for (_dword i = 0; string[i] != 0; i++) {
		if (anyPlatformString::Equal(string[i], character, ignorecase))
			return i;
	}

	return -1;
}

template <typename CharType>
_dword anyPlatformString::SearchR2L(const CharType* string, CharType character, _ubool ignorecase) {
	_dword length = Platform::StringLength(string);

	for (_dword i = 0; i < length; i++) {
		if (anyPlatformString::Equal(string[length - i - 1], character, ignorecase))
			return length - i - 1;
	}

	return -1;
}

template <typename CharType>
_dword anyPlatformString::SearchL2R(const CharType* string, const CharType* substring, _ubool ignorecase, _dword* endindex) {
	_dword length1 = Platform::StringLength(string), length2 = Platform::StringLength(substring);
	if (length1 < length2)
		return -1;

	for (_dword i = 0; i <= length1 - length2; i++) {
		_ubool match = _true;

		for (_dword j = 0; j < length2; j++) {
			if (anyPlatformString::Equal(string[i + j], substring[j], ignorecase) == _false) {
				match = _false;
				break;
			}
		}

		if (match == _true) {
			// Feedback the end index
			if (endindex != _null)
				*endindex = i + length2;

			return i;
		}
	}

	return -1;
}

template <typename CharType>
_dword anyPlatformString::SearchR2L(const CharType* string, const CharType* substring, _ubool ignorecase, _dword* startindex) {
	_dword length1 = Platform::StringLength(string), length2 = Platform::StringLength(substring);
	if (length1 < length2)
		return -1;

	for (_dword i = 0; i <= length1 - length2; i++) {
		_ubool match = _true;

		for (_dword j = 0; j < length2; j++) {
			if (anyPlatformString::Equal(string[length1 - length2 - i + j], substring[j], ignorecase) == _false) {
				match = _false;
				break;
			}
		}

		if (match == _true) {
			// Feedback the start index
			if (startindex != _null)
				*startindex = i;

			return length1 - length2 - i;
		}
	}

	return -1;
}

template <typename CharType>
CharType* anyPlatformString::CopyString(CharType* desbuffer, const CharType* srcbuffer, _dword number) {
	if (desbuffer == _null || srcbuffer == _null || number == 0)
		return _null;

	CharType* string = desbuffer;

	if (number == -1) {
		while ((*string++ = *srcbuffer++))
			;
	} else {
		for (_dword i = 0; i < number; i++) {
			if (!(*string++ = *srcbuffer++))
				break;
		}
	}

	return desbuffer;
}

template <typename CharType>
CharType* anyPlatformString::AppendString(CharType* desbuffer, const CharType* srcbuffer) {
	if (desbuffer == _null || srcbuffer == _null)
		return _null;

	CharType* string = desbuffer;
	while (*string)
		string++;

	while ((*string++ = *srcbuffer++))
		;

	return desbuffer;
}

template <typename CharType>
_int anyPlatformString::CompareString(const CharType* string1, const CharType* string2, _ubool ignorecase) {
	EGE_ASSERT(string1 != _null && string2 != _null);

	if (ignorecase) {
		int f, l;

		do {
			if (((f = *(string1++)) >= 'A') && (f <= 'Z'))
				f -= 'A' - 'a';
			if (((l = *(string2++)) >= 'A') && (l <= 'Z'))
				l -= 'A' - 'a';
		} while (f && (f == l));

		return (f - l);
	} else {
		int ret = 0;

		while (!(ret = *string1 - *string2) && *string2)
			++string1, ++string2;

		if (ret < 0)
			ret = -1;
		else if (ret > 0)
			ret = 1;

		return (ret);
	}
}

template <typename CharType>
_int anyPlatformString::CompareCase(CharType c1, CharType c2, _ubool ignorecase) {
	if (ignorecase) {
		CharType lowercased_c1 = tolower(c1);
		CharType lowercased_c2 = tolower(c2);

		EGE_COMPARE(lowercased_c1, lowercased_c2);
	} else {
		EGE_COMPARE(c1, c2);
	}

	return 0;
}

template <typename CharType>
_ubool anyPlatformString::CompareWildcard(const CharType* string, const CharType* matchstring, _ubool ignorecase) {
	_dword i = 0, j = 0, length1 = Platform::StringLength(string), length2 = Platform::StringLength(matchstring);

	for (i = 0, j = 0; i < length1 && j < length2; i++) {
		if (matchstring[j] == '*') {
			if (matchstring[j + 1] == 0)
				return _true;

			if (anyPlatformString::Equal(matchstring[j + 1], string[i], ignorecase))
				j += 2;
		} else if (matchstring[j] == '?' || anyPlatformString::Equal(string[i], matchstring[j], ignorecase)) {
			j++;
		} else {
			return _false;
		}
	}

	// Trim the '*' wildcard
	while (j < length2) {
		if (matchstring[j] == '*')
			j++;
		else
			break;
	}

	return i == length1 && j == length2;
}

template <typename CharType>
_dword anyPlatformString::StringLength(const CharType* string) {
	if (string == _null)
		return 0;

	const CharType* eos = string;

	while (*eos++)
		;

	return eos - string - 1;
}

template <typename CharType>
CharType* anyPlatformString::LowercaseString(CharType* string, _dword number) {
	if (string == _null || number == 0)
		return _null;

	CharType* string_temp = string;

	if (number == -1) {
		while (*string_temp != 0) {
			CharType c = tolower(*string_temp);
			*string_temp++ = c;
		}
	} else {
		while (*string_temp != 0 && number-- != 0) {
			CharType c = tolower(*string_temp);
			*string_temp++ = c;
		}
	}

	return string;
}

template <typename CharType>
CharType* anyPlatformString::UppercaseString(CharType* string, _dword number) {
	if (string == _null || number == 0)
		return _null;

	CharType* string_temp = string;

	if (number == -1) {
		while (*string_temp != 0) {
			CharType c = toupper(*string_temp);
			*string_temp++ = c;
		}
	} else {
		while (*string_temp != 0 && number-- != 0) {
			CharType c = toupper(*string_temp);
			*string_temp++ = c;
		}
	}

	return string;
}

} // namespace EGE