#pragma once

namespace EGE {

/// <summary>
/// The any-platform converter.
/// </summary>
class anyPlatformConverter {
public:
	static _chara* ConvertLongToString(_int value, _dword radix, _chara* string, _dword length);
	static _chara* ConvertDwordToString(_dword value, _dword radix, _chara* string, _dword length);
	static _chara* ConvertLargeToString(_large value, _dword radix, _chara* string, _dword length);
	static _chara* ConvertQwordToString(_qword value, _dword radix, _chara* string, _dword length);
	static _chara* ConvertFloatToString(_float value, _chara* string, _dword length, _dword precision);
	static _chara* ConvertDoubleToString(_double value, _chara* string, _dword length, _dword precision);
	static _charw* ConvertLongToString(_int value, _dword radix, _charw* string, _dword length);
	static _charw* ConvertDwordToString(_dword value, _dword radix, _charw* string, _dword length);
	static _charw* ConvertLargeToString(_large value, _dword radix, _charw* string, _dword length);
	static _charw* ConvertQwordToString(_qword value, _dword radix, _charw* string, _dword length);
	static _charw* ConvertFloatToString(_float value, _charw* string, _dword length, _dword precision);
	static _charw* ConvertDoubleToString(_double value, _charw* string, _dword length, _dword precision);
	static _boolean ConvertStringToBool(const _chara* string);
	static _int ConvertStringToLong(const _chara* string, _dword radix);
	static _dword ConvertStringToDword(const _chara* string, _dword radix);
	static _large ConvertStringToLarge(const _chara* string, _dword radix);
	static _qword ConvertStringToQword(const _chara* string, _dword radix);
	static _float ConvertStringToFloat(const _chara* string);
	static _double ConvertStringToDouble(const _chara* string);
	static _boolean ConvertStringToBool(const _charw* string);
	static _int ConvertStringToLong(const _charw* string, _dword radix);
	static _dword ConvertStringToDword(const _charw* string, _dword radix);
	static _large ConvertStringToLarge(const _charw* string, _dword radix);
	static _qword ConvertStringToQword(const _charw* string, _dword radix);
	static _float ConvertStringToFloat(const _charw* string);
	static _double ConvertStringToDouble(const _charw* string);
};

} // namespace EGE