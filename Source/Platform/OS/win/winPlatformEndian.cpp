#include "EGEPlatform.h"

_ubool Platform::IsLittleEndian() {
	return anyPlatformEndian::IsLittleEndian();
}

_ubool Platform::IsBigEndian() {
	return anyPlatformEndian::IsBigEndian();
}

Endian Platform::GetEndianType() {
	return anyPlatformEndian::GetEndianType();
}