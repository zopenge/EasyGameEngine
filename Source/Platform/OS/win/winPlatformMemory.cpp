#include "EGEPlatform.h"

//! The global memory block info
struct GlobalMemBlockInfo {
	_dword mSize;
};

//! The total global memory allocated size in bytes
static _dword gGlobalMemAllocatedSize = 0;

_chara* Platform::HeapAllocStr(const _chara* string, _handle heaphandle) {
	_dword size = AStringPtr(string).SizeOfBytes();
	_chara* buffer = (_chara*)Platform::HeapAlloc(size);
	EGE_MEM_CPY(buffer, AStringPtr(string).CStr(), size);

	return buffer;
}

_charw* Platform::HeapAllocStr(const _charw* string, _handle heaphandle) {
	_dword size = WStringPtr(string).SizeOfBytes();
	_charw* buffer = (_charw*)Platform::HeapAlloc(size);
	EGE_MEM_CPY(buffer, WStringPtr(string).CStr(), size);

	return buffer;
}

_void* Platform::HeapAlloc(_dword size, _handle heaphandle) {
	EGE_ASSERT(size > 0);

	return nedmalloc(size);
}

_void* Platform::HeapReAlloc(_void* pointer, _dword size, _handle heaphandle) {
	EGE_ASSERT(size > 0);

	if (pointer == _null)
		return nedmalloc(size);
	else
		return nedrealloc(pointer, size);
}

_void Platform::HeapFree(_void* pointer, _handle heaphandle) {
	if (pointer == _null) return;

	nedfree(pointer);
}

_void* Platform::GlobalAlloc(_dword size) {
	EGE_ASSERT(size > 0);

	// Allocate buffer
	_byte* buffer =
	    (_byte*)::GlobalAlloc(GMEM_FIXED, size + sizeof(GlobalMemBlockInfo));
	EGE_ASSERT(buffer != _null);

	// Set the global memory block info
	GlobalMemBlockInfo* info = (GlobalMemBlockInfo*)buffer;
	info->mSize = size;

	// Update the total global memory allocated size
	INTERLOCKED_ADD(gGlobalMemAllocatedSize, size);

	// Feedback the pointer
	return buffer + sizeof(GlobalMemBlockInfo);
}

_void* Platform::GlobalReAlloc(_void* pointer, _dword size) {
	EGE_ASSERT(size > 0);

	GlobalFree(pointer);

	return GlobalAlloc(size);
}

_void Platform::GlobalFree(_void* pointer) {
	if (pointer == _null) return;

	// Get the global memory block info
	GlobalMemBlockInfo* info =
	    (GlobalMemBlockInfo*)((_byte*)pointer - sizeof(GlobalMemBlockInfo));
	EGE_ASSERT(info != _null);

	// Update the total global memory allocated size
	EGE_ASSERT(gGlobalMemAllocatedSize >= info->mSize);
	INTERLOCKED_SUB(gGlobalMemAllocatedSize, info->mSize);

	// Free buffer
	::GlobalFree(info);
}

_void* Platform::ComAlloc(_dword size) {
	EGE_ASSERT(size > 0);

	return ::CoTaskMemAlloc(size);
}

_charw* Platform::ComAllocString(const _chara* string) {
	if (string == _null) return _null;

	_dword size = (Platform::AnsiToUtf16(_null, 0, string) + 1) * sizeof(_charw);
	_charw* buffer = (_charw*)::CoTaskMemAlloc(size);
	Platform::AnsiToUtf16(buffer, size, string);

	return buffer;
}

_charw* Platform::ComAllocString(const _charw* string) {
	if (string == _null) return _null;

	_dword size = (Platform::StringLength(string) + 1) * sizeof(_charw);
	_charw* buffer = (_charw*)::CoTaskMemAlloc(size);
	EGE_MEM_CPY(buffer, string, size);

	return buffer;
}

_void* Platform::ComReAlloc(_void* pointer, _dword size) {
	EGE_ASSERT(size > 0);

	if (pointer == _null)
		return ::CoTaskMemAlloc(size);
	else
		return ::CoTaskMemRealloc(pointer, size);
}

_void Platform::ComFree(_void* pointer) {
	if (pointer == _null) return;

	::CoTaskMemFree(pointer);
}

_charw* Platform::AllocString(const _charw* string) {
	if (string == _null) return _null;

	return ::SysAllocString(string);
}

_void Platform::FreeString(_charw* string) {
	if (string == _null) return;

	::SysFreeString(string);
}

_void* Platform::VirtualAlloc(_dword size) {
	if (size == 0) return _null;

	return ::VirtualAlloc(_null, size, MEM_COMMIT | MEM_RESERVE,
	                      PAGE_EXECUTE_READWRITE);
}

_void Platform::VirtualFree(_void* pointer) {
	if (pointer == _null) return;

	::VirtualFree(pointer, 0, MEM_RELEASE);
}