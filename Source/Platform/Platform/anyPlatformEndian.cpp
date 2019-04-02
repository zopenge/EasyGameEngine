#include "EGEPlatform.h"

_ubool anyPlatformEndian::IsLittleEndian() {
	static _dword value = 1;
	static _ubool ret = ((_byte*)&value)[0] == 1;

	return ret;
}

_ubool anyPlatformEndian::IsBigEndian() {
	static _dword value = 1;
	static _ubool ret = ((_byte*)&value)[3] == 1;

	return ret;
}

Endian anyPlatformEndian::GetEndianType() {
	if (IsLittleEndian())
		return Endian::Little;
	else
		return Endian::Big;
}