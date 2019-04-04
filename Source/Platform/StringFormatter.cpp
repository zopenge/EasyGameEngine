#include "EGEPlatform.h"

_dword StringFormatter::sUnusedInteger = 0;

unsigned char ToHex(unsigned char x) {
	// Thanks for sharing code: http://blog.csdn.net/gemo/article/details/8468311
	return x > 9 ? x + 55 : x + 48;
}

unsigned char FromHex(unsigned char x) {
	// Thanks for sharing code: http://blog.csdn.net/gemo/article/details/8468311
	unsigned char y = 0;
	if (x >= 'A' && x <= 'Z')
		y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z')
		y = x - 'a' + 10;
	else if (x >= '0' && x <= '9')
		y = x - '0';
	else
		EGE_ASSERT(0);
	return y;
}

template <typename CharType, Encoding EncodingType>
static _ubool T_IsIntegerNumber(ConstString<CharType, EncodingType> string) {
	if (string.GetLength() == 0)
		return _false;

	for (_dword i = 0; i < string.GetLength(); ++i) {
		if (i == 0) {
			if (string[i] != (CharType)'-' &&
			    string[i] != (CharType)'+' &&
			    !(string[i] >= (CharType)'0' && string[i] <= (CharType)'9'))
				return _false;
		} else {
			if (!(string[i] >= (CharType)'0' && string[i] <= (CharType)'9'))
				return _false;
		}
	}

	return _true;
}

template <typename CharType, Encoding EncodingType>
static _ubool T_IsFloatPointNumber(ConstString<CharType, EncodingType> string) {
	if (string.GetLength() == 0)
		return _false;

	_dword dot_number = 0;

	for (_dword i = 0; i < string.GetLength(); ++i) {
		if (i == 0) {
			if (string[i] != (CharType)'-' &&
			    string[i] != (CharType)'+' &&
			    string[i] != (CharType)'.' &&
			    !(string[i] >= (CharType)'0' && string[i] <= (CharType)'9'))
				return _false;
		} else {
			if (string[i] != (CharType)'.' &&
			    !(string[i] >= (CharType)'0' && string[i] <= (CharType)'9'))
				return _false;
		}

		if (string[i] == (CharType)'.')
			dot_number++;

		if (dot_number > 1)
			return _false;
	}

	return _true;
}

_ubool StringFormatter::IsIntegerNumber(AStringPtr string) {
	return T_IsIntegerNumber(string);
}

_ubool StringFormatter::IsIntegerNumber(UStringPtr string) {
	return T_IsIntegerNumber(string);
}

_ubool StringFormatter::IsIntegerNumber(WStringPtr string) {
	return T_IsIntegerNumber(string);
}

_ubool StringFormatter::IsFloatPointNumber(AStringPtr string) {
	return T_IsFloatPointNumber(string);
}

_ubool StringFormatter::IsFloatPointNumber(UStringPtr string) {
	return T_IsFloatPointNumber(string);
}

_ubool StringFormatter::IsFloatPointNumber(WStringPtr string) {
	return T_IsFloatPointNumber(string);
}

_void StringFormatter::ConvertMarkupString2CString(AStringPtr markup_string, AString& c_string) {
	c_string = markup_string;

	c_string.Replace("&lt;", "<");
	c_string.Replace("&gt;", ">");
	c_string.Replace("&apos;", "&apos;");
	c_string.Replace("&quot;", "\"");
	c_string.Replace("&amp;", "&");
	c_string.Replace("&#xD;", "\r");
	c_string.Replace("&#xA;", "\n");
}

_void StringFormatter::ConvertMarkupString2CString(UStringPtr markup_string, UString& c_string) {
	c_string = markup_string;

	c_string.Replace("&#xD;", "\r");
	c_string.Replace("&#xA;", "\n");
	c_string.Replace("&lt;", "<");
	c_string.Replace("&gt;", ">");
	c_string.Replace("&apos;", "&apos;");
	c_string.Replace("&quot;", "\"");
	c_string.Replace("&amp;", "&");
}

_void StringFormatter::ConvertMarkupString2CString(WStringPtr markup_string, WString& c_string) {
	c_string = markup_string;

	c_string.Replace(L"&#xD;", L"\r");
	c_string.Replace(L"&#xA;", L"\n");
	c_string.Replace(L"&lt;", L"<");
	c_string.Replace(L"&gt;", L">");
	c_string.Replace(L"&apos;", L"&apos;");
	c_string.Replace(L"&quot;", L"\"");
	c_string.Replace(L"&amp;", L"&");
}

_void StringFormatter::ConvertString2UPrefixString(WStringPtr in_string, WString& out_string, _ubool all) {
	for (_dword i = 0; in_string[i] != 0; i++) {
		_charw code = in_string[i];

		if (all || code >= 128) {
			_charw code_string[16];
			Platform::FormatStringBuffer(code_string, 16, L"\\U%.4x", code);

			out_string += code_string;
		} else {
			out_string += code;
		}
	}
}

_void StringFormatter::ConvertUPrefixString2String(WStringPtr in_string, WString& out_string) {
	out_string = in_string;

	while (_true) {
		_dword index = out_string.SearchL2R(L"\\U");
		if (index == -1)
			break;

		// Jump '\\U' characters
		WStringPtr string = out_string.SubString(index + 2);

		// Get the HEX value string
		_charw hex_value_string[5];
		hex_value_string[0] = string[0];
		hex_value_string[1] = string[1];
		hex_value_string[2] = string[2];
		hex_value_string[3] = string[3];
		hex_value_string[4] = 0;

		// Get the HEX value
		_charw hex_value = (_charw)Platform::ConvertStringToDword(hex_value_string, 16);

		// Replace string ( '\\Uxxxx' )
		out_string.Remove(index, 6);
		out_string.Insert(index, hex_value);
	}
}

_void StringFormatter::URLEncode(WStringPtr in_string, WString& out_string) {
	// Thanks for sharing code: http://blog.csdn.net/gemo/article/details/8468311
	size_t length = in_string.GetLength();
	for (size_t i = 0; i < length; i++) {
		if (isalnum((unsigned char)in_string[i]) ||
		    (in_string[i] == '-') ||
		    (in_string[i] == '_') ||
		    (in_string[i] == '.') ||
		    (in_string[i] == '~'))
			out_string += in_string[i];
		else if (in_string[i] == ' ')
			out_string += '+';
		else {
			out_string += '%';
			out_string += ToHex((unsigned char)in_string[i] >> 4);
			out_string += ToHex((unsigned char)in_string[i] % 16);
		}
	}
}

_void StringFormatter::URLDecode(WStringPtr in_string, WString& out_string) {
	// Thanks for sharing code: http://blog.csdn.net/gemo/article/details/8468311
	size_t length = in_string.GetLength();
	for (size_t i = 0; i < length; i++) {
		if (in_string[i] == '+')
			out_string += ' ';
		else if (in_string[i] == '%') {
			EGE_ASSERT(i + 2 < length);
			unsigned char high = FromHex((unsigned char)in_string[++i]);
			unsigned char low = FromHex((unsigned char)in_string[++i]);
			out_string += high * 16 + low;
		} else
			out_string += in_string[i];
	}
}