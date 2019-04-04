#include "EGEPlatform.h"

_dword Platform::AnsiToUtf16(_charw* buffer, _dword size, const _chara* string, _dword number) {
	if (string == _null || *string == 0) {
		if (buffer != _null)
			buffer[0] = 0;

		return 0;
	}

	// Get the number of bytes required to store the UNICODE string
	_dword unicode_string_size = number;
	if (unicode_string_size == -1) {
		unicode_string_size = ::MultiByteToWideChar(CP_ACP, 0, string, number, _null, 0) * sizeof(_charw);
		unicode_string_size -= sizeof(_charw);
	} else {
		unicode_string_size *= sizeof(_charw);
	}

	// Convert to UNICODE string
	if (buffer != _null) {
		EGE_ASSERT(unicode_string_size != 0);

		::MultiByteToWideChar(CP_ACP, 0, string, unicode_string_size, buffer, size - 1);
		buffer[Math::Min(size - 1, unicode_string_size / sizeof(_charw))] = 0;
	}

	return unicode_string_size;
}

_dword Platform::Utf16ToAnsi(_chara* buffer, _dword size, const _charw* string, _dword number) {
	if (string == _null || *string == 0) {
		if (buffer != _null)
			buffer[0] = 0;

		return 0;
	}

	// Get the number of bytes required to store the ANSI string
	_dword ansi_string_size = number;
	if (ansi_string_size == -1) {
		ansi_string_size = ::WideCharToMultiByte(CP_ACP, 0, string, number, _null, 0, _null, _null);
		ansi_string_size -= sizeof(_chara);
	}

	// Convert to ANSI string
	if (buffer != _null) {
		EGE_ASSERT(ansi_string_size != 0);

		::WideCharToMultiByte(CP_ACP, 0, string, ansi_string_size, buffer, size - 1, _null, _null);
		buffer[Math::Min(size - 1, ansi_string_size)] = 0;
	}

	return ansi_string_size;
}

_dword Platform::Utf8ToUtf16(_charw* buffer, _dword size, const _chara* string, _dword number) {
	if (string == _null || *string == 0) {
		if (buffer != _null)
			buffer[0] = 0;

		return 0;
	}

	// Get the number of bytes required to store the UNICODE string
	_dword unicode_string_size = number;
	if (unicode_string_size == -1) {
		unicode_string_size = ::MultiByteToWideChar(CP_UTF8, 0, string, number, _null, 0) * sizeof(_charw);
		unicode_string_size -= sizeof(_charw);
	} else {
		unicode_string_size *= sizeof(_charw);
	}

	// Convert to UNICODE string
	if (buffer != _null) {
		EGE_ASSERT(unicode_string_size != 0);

		::MultiByteToWideChar(CP_UTF8, 0, string, unicode_string_size, buffer, size - 1);
		buffer[Math::Min(size - 1, unicode_string_size / sizeof(_charw))] = 0;
	}

	return unicode_string_size;
}

_dword Platform::Utf16ToUtf8(_chara* buffer, _dword size, const _charw* string, _dword number) {
	if (string == _null || *string == 0) {
		if (buffer != _null)
			buffer[0] = 0;

		return 0;
	}

	// Get the number of bytes required to store the UNICODE string
	_dword utf8_string_size = number;
	if (utf8_string_size == -1) {
		utf8_string_size = ::WideCharToMultiByte(CP_UTF8, 0, string, number, _null, 0, _null, _null);
		utf8_string_size -= sizeof(_chara);
	}

	// Convert to UTF-8 string
	if (buffer != _null) {
		EGE_ASSERT(utf8_string_size != 0);

		::WideCharToMultiByte(CP_UTF8, 0, string, utf8_string_size, buffer, size - 1, _null, _null);
		buffer[Math::Min(size - 1, utf8_string_size)] = 0;
	}

	return utf8_string_size;
}

_chara* Platform::FormatStringByArguments(_chara* buffer, _dword size, const _chara* format, ...) {
	BEGIN_VA_LIST(args, format);
	Platform::FormatStringByVAList(buffer, size, format, args);
	END_VA_LIST(args);

	return buffer;
}

_charw* Platform::FormatStringByArguments(_charw* buffer, _dword size, const _charw* format, ...) {
	BEGIN_VA_LIST(args, format);
	Platform::FormatStringByVAList(buffer, size, format, args);
	END_VA_LIST(args);

	return buffer;
}

_chara* Platform::FormatStringByVAList(_chara* buffer, _dword size, const _chara* format, _va_list arguments) {
	return anyPlatformString::FormatStringByVAList(buffer, size, format, arguments);
}

_charw* Platform::FormatStringByVAList(_charw* buffer, _dword size, const _charw* format, _va_list arguments) {
	return anyPlatformString::FormatStringByVAList(buffer, size, format, arguments);
}

_dword Platform::GetFormatStringLength(const _chara* format, _va_list arguments) {
	return anyPlatformString::GetFormatStringLength(format, arguments);
}

_dword Platform::GetFormatStringLength(const _charw* format, _va_list arguments) {
	return anyPlatformString::GetFormatStringLength(format, arguments);
}