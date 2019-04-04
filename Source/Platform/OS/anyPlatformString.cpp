#include "EGEPlatform.h"

_ubool Platform::IsBlank(const _chara* string) {
	return anyPlatformString::IsBlank(string);
}

_ubool Platform::IsBlank(const _charw* string) {
	return anyPlatformString::IsBlank(string);
}

_ubool Platform::IsFullpath(const _chara* path) {
	return anyPlatformString::IsFullpath(path);
}

_ubool Platform::IsFullpath(const _charw* path) {
	return anyPlatformString::IsFullpath(path);
}

_chara* Platform::TrimStringLeft(_chara* string, _dword& stringlength, _chara character, _ubool ignorecase) {
	return anyPlatformString::TrimStringLeft(string, stringlength, character, ignorecase);
}

_charw* Platform::TrimStringLeft(_charw* string, _dword& stringlength, _charw character, _ubool ignorecase) {
	return anyPlatformString::TrimStringLeft(string, stringlength, character, ignorecase);
}

_chara* Platform::TrimStringRight(_chara* string, _dword& stringlength, _chara character, _ubool ignorecase) {
	return anyPlatformString::TrimStringRight(string, stringlength, character, ignorecase);
}

_charw* Platform::TrimStringRight(_charw* string, _dword& stringlength, _charw character, _ubool ignorecase) {
	return anyPlatformString::TrimStringRight(string, stringlength, character, ignorecase);
}

_chara* Platform::TrimStringBoth(_chara* string, _dword& stringlength, _chara character, _ubool ignorecase) {
	if (TrimStringRight(string, stringlength, character) == _null)
		return _null;

	return TrimStringLeft(string, stringlength, character, ignorecase);
}

_charw* Platform::TrimStringBoth(_charw* string, _dword& stringlength, _charw character, _ubool ignorecase) {
	if (TrimStringRight(string, stringlength, character) == _null)
		return _null;

	return TrimStringLeft(string, stringlength, character, ignorecase);
}

_chara* Platform::TrimStringLeft(_chara* string, _dword& stringlength, const _chara* charset, _ubool ignorecase) {
	return anyPlatformString::TrimStringLeft(string, stringlength, charset, ignorecase);
}

_charw* Platform::TrimStringLeft(_charw* string, _dword& stringlength, const _charw* charset, _ubool ignorecase) {
	return anyPlatformString::TrimStringLeft(string, stringlength, charset, ignorecase);
}

_chara* Platform::TrimStringRight(_chara* string, _dword& stringlength, const _chara* charset, _ubool ignorecase) {
	return anyPlatformString::TrimStringRight(string, stringlength, charset, ignorecase);
}

_charw* Platform::TrimStringRight(_charw* string, _dword& stringlength, const _charw* charset, _ubool ignorecase) {
	return anyPlatformString::TrimStringRight(string, stringlength, charset, ignorecase);
}

_chara* Platform::TrimStringBoth(_chara* string, _dword& stringlength, const _chara* charset, _ubool ignorecase) {
	if (TrimStringRight(string, stringlength, charset) == _null)
		return _null;

	return TrimStringLeft(string, stringlength, charset, ignorecase);
}

_charw* Platform::TrimStringBoth(_charw* string, _dword& stringlength, const _charw* charset, _ubool ignorecase) {
	if (TrimStringRight(string, stringlength, charset) == _null)
		return _null;

	return TrimStringLeft(string, stringlength, charset, ignorecase);
}

_dword Platform::SearchL2R(const _chara* string, _chara character, _ubool ignorecase) {
	return anyPlatformString::SearchL2R(string, character, ignorecase);
}

_dword Platform::SearchL2R(const _charw* string, _charw character, _ubool ignorecase) {
	return anyPlatformString::SearchL2R(string, character, ignorecase);
}

_dword Platform::SearchR2L(const _chara* string, _chara character, _ubool ignorecase) {
	return anyPlatformString::SearchR2L(string, character, ignorecase);
}

_dword Platform::SearchR2L(const _charw* string, _charw character, _ubool ignorecase) {
	return anyPlatformString::SearchR2L(string, character, ignorecase);
}

_dword Platform::SearchL2R(const _chara* string, const _chara* substring, _ubool ignorecase, _dword* endindex) {
	return anyPlatformString::SearchL2R(string, substring, ignorecase, endindex);
}

_dword Platform::SearchL2R(const _charw* string, const _charw* substring, _ubool ignorecase, _dword* endindex) {
	return anyPlatformString::SearchL2R(string, substring, ignorecase, endindex);
}

_dword Platform::SearchR2L(const _chara* string, const _chara* substring, _ubool ignorecase, _dword* startindex) {
	return anyPlatformString::SearchR2L(string, substring, ignorecase, startindex);
}

_dword Platform::SearchR2L(const _charw* string, const _charw* substring, _ubool ignorecase, _dword* startindex) {
	return anyPlatformString::SearchR2L(string, substring, ignorecase, startindex);
}

_chara* Platform::CopyString(_chara* desbuffer, const _chara* srcbuffer, _dword number) {
	return anyPlatformString::CopyString(desbuffer, srcbuffer, number);
}

_charw* Platform::CopyString(_charw* desbuffer, const _charw* srcbuffer, _dword number) {
	return anyPlatformString::CopyString(desbuffer, srcbuffer, number);
}

_chara* Platform::AppendString(_chara* desbuffer, const _chara* srcbuffer) {
	return anyPlatformString::AppendString(desbuffer, srcbuffer);
}

_charw* Platform::AppendString(_charw* desbuffer, const _charw* srcbuffer) {
	return anyPlatformString::AppendString(desbuffer, srcbuffer);
}

_int Platform::CompareString(const _chara* string1, const _chara* string2, _ubool ignorecase) {
	return anyPlatformString::CompareString(string1, string2, ignorecase);
}

_int Platform::CompareString(const _charw* string1, const _charw* string2, _ubool ignorecase) {
	return anyPlatformString::CompareString(string1, string2, ignorecase);
}

_int Platform::CompareCase(_chara c1, _chara c2, _ubool ignorecase) {
	return anyPlatformString::CompareCase(c1, c2, ignorecase);
}

_int Platform::CompareCase(_charw c1, _charw c2, _ubool ignorecase) {
	return anyPlatformString::CompareCase(c1, c2, ignorecase);
}

_ubool Platform::CompareWildcard(const _chara* string, const _chara* matchstring, _ubool ignorecase) {
	return anyPlatformString::CompareWildcard(string, matchstring, ignorecase);
}

_ubool Platform::CompareWildcard(const _charw* string, const _charw* matchstring, _ubool ignorecase) {
	return anyPlatformString::CompareWildcard(string, matchstring, ignorecase);
}

_dword Platform::StringLength(const _chara* string) {
	return anyPlatformString::StringLength(string);
}

_dword Platform::StringLength(const _charw* string) {
	return anyPlatformString::StringLength(string);
}

_chara* Platform::LowercaseString(_chara* string, _dword number) {
	return anyPlatformString::LowercaseString(string, number);
}

_chara* Platform::UppercaseString(_chara* string, _dword number) {
	return anyPlatformString::UppercaseString(string, number);
}

_charw* Platform::LowercaseString(_charw* string, _dword number) {
	return anyPlatformString::LowercaseString(string, number);
}

_charw* Platform::UppercaseString(_charw* string, _dword number) {
	return anyPlatformString::UppercaseString(string, number);
}

_ubool Platform::IsUtf8String(const _chara* buffer, _dword size) {
	if (buffer == _null || size == 0)
		return _false;

	const uint32_t UTF8_ACCEPT = 0;
	const uint32_t UTF8_REJECT = 1;

	static const uint8_t utf8d[] = {
	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 00..1f
	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 20..3f
	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 40..5f
	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 60..7f
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, // 80..9f
	    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, // a0..bf
	    8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, // c0..df
	    0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x3, // e0..ef
	    0xb, 0x6, 0x6, 0x6, 0x5, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, // f0..ff
	    0x0, 0x1, 0x2, 0x3, 0x5, 0x8, 0x7, 0x1, 0x1, 0x1, 0x4, 0x6, 0x1, 0x1, 0x1, 0x1, // s0..s0
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, // s1..s2
	    1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, // s3..s4
	    1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, // s5..s6
	    1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // s7..s8
	};

	uint32_t state = 0;
	for (_dword i = 0; i < size; i++) {
		if (buffer[i] == 0)
			break;

		// We don't care about the codepoint, so this is a simplified version of the decode function.
		uint32_t type = utf8d[(uint8_t)buffer[i]];
		state = utf8d[256 + state * 16 + type];

		if (state == UTF8_REJECT)
			break;
	}

	if (state == UTF8_ACCEPT)
		return _true;
	else
		return _false;
}

//----------------------------------------------------------------------------
// anyPlatform-String Implementation
//----------------------------------------------------------------------------

_dword anyPlatformString::AnsiToUtf16(_charw* buffer, _dword size, const _chara* string, _dword number) {
	return Utf8ToUtf16(buffer, size, string, number);
}

_dword anyPlatformString::Utf16ToAnsi(_chara* buffer, _dword size, const _charw* string, _dword number) {
	return Utf16ToUtf8(buffer, size, string, number);
}

_dword anyPlatformString::Utf8ToUtf16(_charw* buffer, _dword size, const _chara* string, _dword number) {
	if (string == _null || *string == 0) {
		if (buffer != _null)
			buffer[0] = 0;

		return 0;
	}

	_charw* dest = buffer;
	const _chara* src = string;

	size_t extra_bytes;
	size_t len = 0;
	while (*src) {
		unsigned long c = (unsigned long)*src++ & 0xFFUL;
		if ((c & 0x80UL) == 0UL) //1 octet
		{
			if (dest)
				*dest++ = (uchar)c;

			len++;

			continue;
		} else if ((c & 0xE0UL) == 0xC0UL) //2 octet
		{
			c -= 0xC0UL;
			extra_bytes = 1;
		} else if ((c & 0xF0UL) == 0xE0UL) // 3 octet
		{
			c -= 0xE0UL;
			extra_bytes = 2;
		} else if ((c & 0xF8UL) == 0xF0UL) // 4 octet
		{
			c -= 0xF0UL;
			extra_bytes = 3;
		} else {
			//5 or 6 octets cannot be converted to UTF-16
			break;
		}

		while (extra_bytes) {
			//if(*src == 0) return 0; //unexpected end of string
			if (*src == 0)
				break;
			; //unexpected end of string
			if ((*src & 0xC0UL) != 0x80UL)
				break;
			c <<= 6;
			c += (unsigned long)*src++ & 0x3FUL;
			extra_bytes--;
		}

		if (c < 0x10000UL) {
			//value between 0xD800 and 0xDFFF are preserved for UTF-16 pairs
			if (c >= 0xD800UL && c <= 0xDFFFUL) return 0;
			if (dest)
				*dest++ = (uchar)c;
			len++;
		} else {
			c -= 0x10000UL;
			//value greater than 0x10FFFF, illegal UTF-16 value;
			if (c >= 0x100000UL)
				break;
			if (dest) {
				*dest++ = (uchar)(0xD800UL + (c >> 10));
				*dest++ = (uchar)(0xDC00UL + (c & 0x3FFUL));
			}
			len += 2;
			//   len++; //如果是算字数应是1
		}
	}

	if (dest)
		*dest = (uchar)'\0';

	return len * sizeof(_charw);
}

_dword anyPlatformString::Utf16ToUtf8(_chara* buffer, _dword size, const _charw* string, _dword number) {
	if (string == _null || *string == 0) {
		if (buffer != _null)
			buffer[0] = 0;

		return 0;
	}

	static unsigned long FirstByteMasks[4] = {0x00UL, 0xC0UL, 0xE0UL, 0xF0UL};

	_chara* dest = buffer;
	const _charw* src = string;

	size_t extra_bytes;
	size_t len = 0;
	while (*src) {
		unsigned long c = (unsigned long)*src++ & 0xFFFFUL;
		//convert UTF-16 literal to UCS-4
		if (c >= 0xD800UL && c <= 0xDBFFUL) {
			c &= 0x03FFUL;
			c <<= 10;
			unsigned long c1 = (unsigned long)*src++ & 0xFFFFUL;
			if (c1 >= 0xDC00UL && c1 <= 0xDFFFUL) {
				c += c1 & 0x03FFUL;
			} else {
				return 0;
			}
		} else if (c >= 0xDC00UL && c <= 0xDFFFUL) {
			return 0;
		}
		//convert UCS-4 literal to UTF-8
		if (c < 0x80UL)
			extra_bytes = 0;
		else if (c < 0x800UL)
			extra_bytes = 1;
		else if (c < 0x10000UL)
			extra_bytes = 2;
		else
			extra_bytes = 3;

		if (dest != _null) {
			dest += extra_bytes;

			switch (extra_bytes) {
				case 3:
					*dest-- = (char)((c | 0x80UL) & 0xBFUL);
					c >>= 6;
				case 2:
					*dest-- = (char)((c | 0x80UL) & 0xBFUL);
					c >>= 6;
				case 1:
					*dest-- = (char)((c | 0x80UL) & 0xBFUL);
					c >>= 6;
				case 0:
					*dest = (char)(c | FirstByteMasks[extra_bytes]);
			}
		}

		extra_bytes++;

		if (dest != _null)
			dest += extra_bytes;

		len += extra_bytes;
	}

	if (dest != _null)
		*dest = '\0';

	return len;
}

_chara* anyPlatformString::FormatStringByVAList(_chara* buffer, _dword size, const _chara* format, _va_list arguments) {
	if (buffer == _null)
		return _null;

	EGE_ASSERT(size != 0 && format != _null);

	vsnprintf(buffer, size, format, arguments);
	return buffer;
}

_charw* anyPlatformString::FormatStringByVAList(_charw* buffer, _dword size, const _charw* format, _va_list arguments) {
	if (buffer == _null)
		return _null;

	EGE_ASSERT(size != 0 && format != _null);

	uc_vsnprintf((uchar16*)buffer, size, (const uchar16*)format, arguments);
	return buffer;
}

_dword anyPlatformString::GetFormatStringLength(const _chara* format, _va_list arguments) {
	_dword length = 0;

	_va_list args;
	va_copy(args, arguments);
	{
		length = vsnprintf(_null, 0, format, args);
	}
	va_end(args);

	return length;
}

_dword anyPlatformString::GetFormatStringLength(const _charw* format, _va_list arguments) {
	_dword length = 0;

	_va_list args;
	va_copy(args, arguments);
	{
		length = uc_vsnprintf(_null, 0, (const uchar16*)format, args);
	}
	va_end(args);

	return length;
}
