#include "EGEPlatform.h"

_ubool Platform::GetSystemPath(_charw* path, _dword length) {
	Platform::CopyString(path, L"/system", length);

	return _true;
}

_ubool Platform::GetSystemFontPath(_charw* path, _dword length) {
	Platform::CopyString(path, L"/system/fonts", length);

	return _true;
}

_ubool Platform::GetSystemTempPath(_charw* path, _dword length) {
	Platform::CopyString(path, L"/system/temp", length);

	return _true;
}