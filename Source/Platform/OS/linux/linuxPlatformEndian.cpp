#include "EGEPlatform.h"

_ubool Platform::IsLittleEndian() {
	return anyPlatformEndian::IsLittleEndian();
}

_ubool Platform::IsBigEndian() {
	return anyPlatformEndian::IsBigEndian();
}

_ENDIAN Platform::GetEndianType() {
	return anyPlatformEndian::GetEndianType();
}