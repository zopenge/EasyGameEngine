#include "EGEPlatform.h"

_ubool anyPlatformLanguage::IsVowelInThai(_charw code) {
	if (IsUpperVowelInThai(code))
		return _true;

	if (IsDownVowelInThai(code))
		return _true;

	return _false;
}

_ubool anyPlatformLanguage::IsUpperVowelInThai(_charw code) {
	switch (code) {
		case 0x0E34:
		case 0x0E35:
		case 0x0E36:
		case 0x0E37:
			return _true;

		default:
			return _false;
	}
}

_ubool anyPlatformLanguage::IsDownVowelInThai(_charw code) {
	switch (code) {
		case 0x0E38:
		case 0x0E39:
			return _true;

		default:
			return _false;
	}
}

_ubool anyPlatformLanguage::IsToneInThai(_charw code) {
	switch (code) {
		case 0x0E48:
		case 0x0E49:
		case 0x0E4A:
		case 0x0E4B:
			return _true;

		default:
			return _false;
	}
}