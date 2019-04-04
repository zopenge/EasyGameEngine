#include "EGEPlatform.h"

_dword Platform::GetFileVersionInfoSize(const _charw* filename) {
	if (filename == _null)
		return 0;

	return ::GetFileVersionInfoSizeW(filename, _null);
}

_ubool Platform::GetFileVersionInfo(const _charw* filename, _dword buffersize, _void* bufferdata) {
	if (filename == _null)
		return _false;

	return !!(::GetFileVersionInfoW(filename, _null, buffersize, bufferdata));
}

_ubool Platform::VerQueryBuffer(_void* block, const _charw* subblock, _void*& bufferdata, _dword& buffersize) {
	if (bufferdata == _null)
		return _false;

	return !!(::VerQueryValueW(block, subblock, &bufferdata, (PUINT)&buffersize));
}