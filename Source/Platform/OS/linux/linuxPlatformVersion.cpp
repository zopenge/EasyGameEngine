#include "EGEPlatform.h"

_dword Platform::GetFileVersionInfoSize(const _charw* filename) {
	return 0;
}

_ubool Platform::GetFileVersionInfo(const _charw* filename, _dword buffersize, _void* bufferdata) {
	return _false;
}

_ubool Platform::VerQueryBuffer(_void* block, const _charw* subblock, _void*& bufferdata, _dword& buffersize) {
	return _false;
}