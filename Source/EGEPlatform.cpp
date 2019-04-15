#include "EGEPlatform.h"

_thread_id EGE::gMainThreadID = 0;
PerformanceData EGE::gPerformanceData;
CPUData EGE::gCPUData;
GPUData EGE::gGPUData;
OSData EGE::gOSData;

//----------------------------------------------------------------------------
// Specified template static variables implementation
//----------------------------------------------------------------------------

template <>
const PointI PointI::cZeroPoint(0, 0);
template <>
const PointI PointI::cMaxPoint(0x7FFFFFFF, 0x7FFFFFFF);
template <>
const PointI PointI::cMinPoint(0x80000001, 0x80000001);

template <>
const PointU PointU::cZeroPoint(0, 0);
template <>
const PointU PointU::cMaxPoint(0xFFFFFFFF, 0xFFFFFFFF);
template <>
const PointU PointU::cMinPoint(0x00000001, 0x00000001);

template <>
const PointF PointF::cZeroPoint(0.0f, 0.0f);
template <>
const PointF PointF::cMaxPoint(3.402823466e+38f, 3.402823466e+38f);
template <>
const PointF PointF::cMinPoint(-3.402823466e+38f, -3.402823466e+38f);

template <>
const RectI RectI::cNull(0, 0, 0, 0);
template <>
const RectU RectU::cNull(0, 0, 0, 0);
template <>
const RectF RectF::cNull(0.0f, 0.0f, 0.0f, 0.0f);

template <>
const RectI RectI::cMax(Math::cMinInt, Math::cMinInt, Math::cMaxInt, Math::cMaxInt);
template <>
const RectU RectU::cMax(Math::cMinDword, Math::cMinDword, Math::cMaxDword, Math::cMaxDword);
template <>
const RectF RectF::cMax(Math::cMinFloat, Math::cMinFloat, Math::cMaxFloat, Math::cMaxFloat);

template <>
const WordRange WordRange::cNull(0, 0);
template <>
const DwordRange DwordRange::cNull(0, 0);
template <>
const QwordRange QwordRange::cNull(0, 0);
template <>
const FloatRange FloatRange::cNull(0.0f, 0.0f);

template <>
const WordProgression WordProgression::cNull(0, 0);
template <>
const DwordProgression DwordProgression::cNull(0, 0);
template <>
const FloatProgression FloatProgression::cNull(0.0f, 0.0f);

template <>
const DwordDataField DwordDataField::cNull(0, 0);

template <>
const QwordParams2 QwordParams2::cNull(0, 0);
template <>
const QwordParams3 QwordParams3::cNull(0, 0, 0);
template <>
const QwordParams4 QwordParams4::cNull(0, 0, 0, 0);

//----------------------------------------------------------------------------
// External Template Functions Implementation
//----------------------------------------------------------------------------

namespace EGE {

_int TemplateExternal::CompareString(const _chara* string1, const _chara* string2, _ubool ignorecase) {
	return Platform::CompareString(string1, string2, ignorecase);
}

_dword TemplateExternal::StringLength(const _chara* string) {
	return Platform::StringLength(string);
}

_chara* TemplateExternal::ConvertLongToString(_int value, _dword radix, _chara* string, _dword length) {
	return Platform::ConvertLongToString(value, radix, string, length);
}

_chara* TemplateExternal::ConvertDwordToString(_dword value, _dword radix, _chara* string, _dword length) {
	return Platform::ConvertDwordToString(value, radix, string, length);
}

_chara* TemplateExternal::ConvertLargeToString(_large value, _dword radix, _chara* string, _dword length) {
	return Platform::ConvertLargeToString(value, radix, string, length);
}

_chara* TemplateExternal::ConvertQwordToString(_qword value, _dword radix, _chara* string, _dword length) {
	return Platform::ConvertQwordToString(value, radix, string, length);
}

_chara* TemplateExternal::ConvertFloatToString(_float value, _chara* string, _dword length, _dword precision) {
	return Platform::ConvertFloatToString(value, string, length, precision);
}

_chara* TemplateExternal::ConvertDoubleToString(_double value, _chara* string, _dword length, _dword precision) {
	return Platform::ConvertDoubleToString(value, string, length, precision);
}

_ubool TemplateExternal::ConvertStringToBool(const _chara* string) {
	return Platform::ConvertStringToBool(string);
}

_int TemplateExternal::ConvertStringToLong(const _chara* string, _dword radix) {
	return Platform::ConvertStringToLong(string, radix);
}

_dword TemplateExternal::ConvertStringToDword(const _chara* string, _dword radix) {
	return Platform::ConvertStringToDword(string, radix);
}

_large TemplateExternal::ConvertStringToLarge(const _chara* string, _dword radix) {
	return Platform::ConvertStringToLarge(string, radix);
}

_qword TemplateExternal::ConvertStringToQword(const _chara* string, _dword radix) {
	return Platform::ConvertStringToQword(string, radix);
}

_float TemplateExternal::ConvertStringToFloat(const _chara* string) {
	return Platform::ConvertStringToFloat(string);
}

_double TemplateExternal::ConvertStringToDouble(const _chara* string) {
	return Platform::ConvertStringToDouble(string);
}

_dword TemplateExternal::SearchL2R(const _chara* string, _chara character, _ubool ignorecase) {
	return Platform::SearchL2R(string, character, ignorecase);
}

_dword TemplateExternal::SearchL2R(const _chara* string, const _chara* substring, _ubool ignorecase, _dword* endindex) {
	return Platform::SearchL2R(string, substring, ignorecase, endindex);
}

_dword TemplateExternal::SearchR2L(const _chara* string, _chara character, _ubool ignorecase) {
	return Platform::SearchR2L(string, character, ignorecase);
}

_dword TemplateExternal::SearchR2L(const _chara* string, const _chara* substring, _ubool ignorecase, _dword* startindex) {
	return Platform::SearchR2L(string, substring, ignorecase, startindex);
}

_ubool TemplateExternal::CompareWildcard(const _chara* string, const _chara* matchstring, _ubool ignorecase) {
	return Platform::CompareWildcard(string, matchstring, ignorecase);
}

_ubool TemplateExternal::IsBlank(const _chara* string) {
	return Platform::IsBlank(string);
}

_ubool TemplateExternal::IsFullpath(const _chara* path) {
	return Platform::IsFullpath(path);
}

_chara* TemplateExternal::LowercaseString(_chara* string, _dword number) {
	return Platform::LowercaseString(string, number);
}

_chara* TemplateExternal::UppercaseString(_chara* string, _dword number) {
	return Platform::UppercaseString(string, number);
}

_chara* TemplateExternal::TrimStringLeft(_chara* string, _dword& stringlength, _chara character, _ubool ignorecase) {
	return Platform::TrimStringLeft(string, stringlength, character, ignorecase);
}

_chara* TemplateExternal::TrimStringRight(_chara* string, _dword& stringlength, _chara character, _ubool ignorecase) {
	return Platform::TrimStringRight(string, stringlength, character, ignorecase);
}

_chara* TemplateExternal::TrimStringBoth(_chara* string, _dword& stringlength, _chara character, _ubool ignorecase) {
	return Platform::TrimStringBoth(string, stringlength, character, ignorecase);
}

_chara* TemplateExternal::TrimStringLeft(_chara* string, _dword& stringlength, const _chara* charset, _ubool ignorecase) {
	return Platform::TrimStringLeft(string, stringlength, charset, ignorecase);
}

_chara* TemplateExternal::TrimStringRight(_chara* string, _dword& stringlength, const _chara* charset, _ubool ignorecase) {
	return Platform::TrimStringRight(string, stringlength, charset, ignorecase);
}

_chara* TemplateExternal::TrimStringBoth(_chara* string, _dword& stringlength, const _chara* charset, _ubool ignorecase) {
	return Platform::TrimStringBoth(string, stringlength, charset, ignorecase);
}

_dword TemplateExternal::GetFormatStringLength(const _chara* format, _va_list arguments) {
	return Platform::GetFormatStringLength(format, arguments);
}

_chara* TemplateExternal::FormatStringByVAList(_chara* buffer, _dword size, const _chara* format, _va_list arguments) {
	return Platform::FormatStringByVAList(buffer, size, format, arguments);
}

_int TemplateExternal::CompareString(const _charw* string1, const _charw* string2, _ubool ignorecase) {
	return Platform::CompareString(string1, string2, ignorecase);
}

_dword TemplateExternal::StringLength(const _charw* string) {
	return Platform::StringLength(string);
}

_charw* TemplateExternal::ConvertLongToString(_int value, _dword radix, _charw* string, _dword length) {
	return Platform::ConvertLongToString(value, radix, string, length);
}

_charw* TemplateExternal::ConvertDwordToString(_dword value, _dword radix, _charw* string, _dword length) {
	return Platform::ConvertDwordToString(value, radix, string, length);
}

_charw* TemplateExternal::ConvertLargeToString(_large value, _dword radix, _charw* string, _dword length) {
	return Platform::ConvertLargeToString(value, radix, string, length);
}

_charw* TemplateExternal::ConvertQwordToString(_qword value, _dword radix, _charw* string, _dword length) {
	return Platform::ConvertQwordToString(value, radix, string, length);
}

_charw* TemplateExternal::ConvertFloatToString(_float value, _charw* string, _dword length, _dword precision) {
	return Platform::ConvertFloatToString(value, string, length, precision);
}

_charw* TemplateExternal::ConvertDoubleToString(_double value, _charw* string, _dword length, _dword precision) {
	return Platform::ConvertDoubleToString(value, string, length, precision);
}

_ubool TemplateExternal::ConvertStringToBool(const _charw* string) {
	return Platform::ConvertStringToBool(string);
}

_int TemplateExternal::ConvertStringToLong(const _charw* string, _dword radix) {
	return Platform::ConvertStringToLong(string, radix);
}

_dword TemplateExternal::ConvertStringToDword(const _charw* string, _dword radix) {
	return Platform::ConvertStringToDword(string, radix);
}

_large TemplateExternal::ConvertStringToLarge(const _charw* string, _dword radix) {
	return Platform::ConvertStringToLarge(string, radix);
}

_qword TemplateExternal::ConvertStringToQword(const _charw* string, _dword radix) {
	return Platform::ConvertStringToQword(string, radix);
}

_float TemplateExternal::ConvertStringToFloat(const _charw* string) {
	return Platform::ConvertStringToFloat(string);
}

_double TemplateExternal::ConvertStringToDouble(const _charw* string) {
	return Platform::ConvertStringToDouble(string);
}

_dword TemplateExternal::SearchL2R(const _charw* string, _charw character, _ubool ignorecase) {
	return Platform::SearchL2R(string, character, ignorecase);
}

_dword TemplateExternal::SearchL2R(const _charw* string, const _charw* substring, _ubool ignorecase, _dword* endindex) {
	return Platform::SearchL2R(string, substring, ignorecase, endindex);
}

_dword TemplateExternal::SearchR2L(const _charw* string, _charw character, _ubool ignorecase) {
	return Platform::SearchR2L(string, character, ignorecase);
}

_dword TemplateExternal::SearchR2L(const _charw* string, const _charw* substring, _ubool ignorecase, _dword* startindex) {
	return Platform::SearchR2L(string, substring, ignorecase, startindex);
}

_ubool TemplateExternal::CompareWildcard(const _charw* string, const _charw* matchstring, _ubool ignorecase) {
	return Platform::CompareWildcard(string, matchstring, ignorecase);
}

_ubool TemplateExternal::IsBlank(const _charw* string) {
	return Platform::IsBlank(string);
}

_ubool TemplateExternal::IsFullpath(const _charw* path) {
	return Platform::IsFullpath(path);
}

_charw* TemplateExternal::LowercaseString(_charw* string, _dword number) {
	return Platform::LowercaseString(string, number);
}

_charw* TemplateExternal::UppercaseString(_charw* string, _dword number) {
	return Platform::UppercaseString(string, number);
}

_charw* TemplateExternal::TrimStringLeft(_charw* string, _dword& stringlength, _charw character, _ubool ignorecase) {
	return Platform::TrimStringLeft(string, stringlength, character, ignorecase);
}

_charw* TemplateExternal::TrimStringRight(_charw* string, _dword& stringlength, _charw character, _ubool ignorecase) {
	return Platform::TrimStringRight(string, stringlength, character, ignorecase);
}

_charw* TemplateExternal::TrimStringBoth(_charw* string, _dword& stringlength, _charw character, _ubool ignorecase) {
	return Platform::TrimStringBoth(string, stringlength, character, ignorecase);
}

_charw* TemplateExternal::TrimStringLeft(_charw* string, _dword& stringlength, const _charw* charset, _ubool ignorecase) {
	return Platform::TrimStringLeft(string, stringlength, charset, ignorecase);
}

_charw* TemplateExternal::TrimStringRight(_charw* string, _dword& stringlength, const _charw* charset, _ubool ignorecase) {
	return Platform::TrimStringRight(string, stringlength, charset, ignorecase);
}

_charw* TemplateExternal::TrimStringBoth(_charw* string, _dword& stringlength, const _charw* charset, _ubool ignorecase) {
	return Platform::TrimStringBoth(string, stringlength, charset, ignorecase);
}

_dword TemplateExternal::GetFormatStringLength(const _charw* format, _va_list arguments) {
	return Platform::GetFormatStringLength(format, arguments);
}

_charw* TemplateExternal::FormatStringByVAList(_charw* buffer, _dword size, const _charw* format, _va_list arguments) {
	return Platform::FormatStringByVAList(buffer, size, format, arguments);
}

_dword TemplateExternal::AnsiToUtf16(_charw* buffer, _dword size, const _chara* string, _dword number) {
	return Platform::AnsiToUtf16(buffer, size, string, number);
}

_dword TemplateExternal::Utf16ToAnsi(_chara* buffer, _dword size, const _charw* string, _dword number) {
	return Platform::Utf16ToAnsi(buffer, size, string, number);
}

_dword TemplateExternal::Utf8ToUtf16(_charw* buffer, _dword size, const _chara* string, _dword number) {
	return Platform::Utf8ToUtf16(buffer, size, string, number);
}

_dword TemplateExternal::Utf16ToUtf8(_chara* buffer, _dword size, const _charw* string, _dword number) {
	return Platform::Utf16ToUtf8(buffer, size, string, number);
}

_dword TemplateExternal::BuildFromString(const _chara* string, _dword oldcrc) {
	return CRC::BuildFromString(string, oldcrc);
}

_dword TemplateExternal::BuildFromString(const _charw* string, _dword oldcrc) {
	return CRC::BuildFromString(string, oldcrc);
}

} // namespace EGE

//----------------------------------------------------------------------------
// Memory Overload Implementation
//----------------------------------------------------------------------------

#ifndef _USE_STANDARD_MEM_OPERATOR_

#	ifndef _USE_STANDARD_MALLOC_OPERATOR_

void _ege_free(void* pointer, const char* filename, int linenumber) {
	EGE::Memory::GetInstance().Free(pointer, filename, linenumber);
}

void* _ege_malloc(size_t size, const char* filename, int linenumber) {
	return EGE::Memory::GetInstance().Alloc((_dword)size, filename, linenumber);
}

void* _ege_calloc(size_t number, size_t size, const char* filename, int linenumber) {
	EGE::_void* buffer = EGE::Memory::GetInstance().Alloc((_dword)(number * size), filename, linenumber);
	if (buffer != _null) {
		EGE_MEM_SET(buffer, 0, number * size);
	}

	return buffer;
}

void* _ege_realloc(void* pointer, size_t size, const char* filename, int linenumber) {
	return EGE::Memory::GetInstance().Realloc(pointer, (_dword)size, filename, linenumber);
}

#	endif

#	undef new

// Overload New And Delete Operations
void* operator new(size_t size) {
	return EGE::Memory::GetInstance().Alloc((EGE::_dword)size, _null, 0);
}

void* operator new(size_t size, const char* filename, int linenumber) {
	return EGE::Memory::GetInstance().Alloc((EGE::_dword)size, filename, linenumber);
}

void* operator new[](size_t size) {
	return EGE::Memory::GetInstance().Alloc((EGE::_dword)size, _null, 0);
}

void* operator new[](size_t size, const char* filename, int linenumber) {
	return EGE::Memory::GetInstance().Alloc((EGE::_dword)size, filename, linenumber);
}

void operator delete(void* pointer) {
	return EGE::Memory::GetInstance().Free(pointer, _null, 0);
}

void operator delete(void* pointer, const char* filename, int linenumber) {
	return EGE::Memory::GetInstance().Free(pointer, filename, linenumber);
}

void operator delete[](void* pointer) {
	return EGE::Memory::GetInstance().Free(pointer, _null, 0);
}

void operator delete[](void* pointer, const char* filename, int linenumber) {
	return EGE::Memory::GetInstance().Free(pointer, filename, linenumber);
}

#endif // _USE_STANDARD_MEM_OPERATOR_
