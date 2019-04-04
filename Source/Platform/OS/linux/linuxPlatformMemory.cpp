#include "EGEPlatform.h"

_chara* Platform::HeapAllocStr(const _chara* string, _handle heaphandle) {
	_dword size = AStringPtr(string).SizeOfBytes();
	_chara* buffer = (_chara*)Platform::HeapAlloc(size);
	EGE_MEM_CPY(buffer, AStringPtr(string).Str(), size);

	return buffer;
}

_charw* Platform::HeapAllocStr(const _charw* string, _handle heaphandle) {
	_dword size = WStringPtr(string).SizeOfBytes();
	_charw* buffer = (_charw*)Platform::HeapAlloc(size);
	EGE_MEM_CPY(buffer, WStringPtr(string).Str(), size);

	return buffer;
}

_void* Platform::HeapAlloc(_dword size, _handle heaphandle) {
	// We use the same allocation method on iPhone as global allocation
	return GlobalAlloc(size);
}

_void* Platform::HeapReAlloc(_void* pointer, _dword size, _handle heaphandle) {
	// We use the same allocation method on iPhone as global allocation
	return GlobalReAlloc(pointer, size);
}

_void Platform::HeapFree(_void* pointer, _handle heaphandle) {
	// We use the same allocation method on iPhone as global allocation
	GlobalFree(pointer);
}

_void* Platform::GlobalAlloc(_dword size) {
	return ::malloc(size);
}

_void* Platform::GlobalReAlloc(_void* pointer, _dword size) {
	return ::realloc(pointer, size);
}

_void Platform::GlobalFree(_void* pointer) {
	if (pointer == _null)
		return;

	::free(pointer);
}

_void* Platform::ComAlloc(_dword size) {
	return _null;
}

_charw* Platform::ComAllocString(const _charw* string) {
	return _null;
}

_void* Platform::ComReAlloc(_void* pointer, _dword size) {
	return _null;
}

_void Platform::ComFree(_void* pointer) {
}

_charw* Platform::AllocString(const _charw* string) {
	return _null;
}

_void Platform::FreeString(_charw* string) {
}