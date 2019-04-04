#include "EGEPlatform.h"

const Variable Variable::cNull;

_dword Variable::GetTypeID(WStringPtr typestring) {
	if (typestring == L"_chara" || typestring == L"_tiny")
		return _TYPE_ID_INT8;
	else if (typestring == L"_short" || typestring == L"_charw")
		return _TYPE_ID_INT16;
	else if (typestring == L"_int")
		return _TYPE_ID_INT32;
	else if (typestring == L"_large")
		return _TYPE_ID_INT32;
	else if (typestring == L"_byte")
		return _TYPE_ID_UINT8;
	else if (typestring == L"_word")
		return _TYPE_ID_UINT16;
	else if (typestring == L"_dword")
		return _TYPE_ID_UINT32;
	else if (typestring == L"_qword")
		return _TYPE_ID_UINT64;
	else if (typestring == L"_float")
		return _TYPE_ID_FLOAT;
	else if (typestring == L"_double")
		return _TYPE_ID_DOUBLE;
	else if (typestring == L"WString")
		return _TYPE_ID_WSTRING;
	else if (typestring == L"_void*")
		return _TYPE_ID_POINTER;

	return _TYPE_ID_UNKNOWN;
}

WStringPtr Variable::GetTypeIDString(_dword type) {
	switch (type) {
		case _TYPE_ID_INT8:
			return L"_tiny";
		case _TYPE_ID_INT16:
			return L"_short";
		case _TYPE_ID_INT32:
			return L"_int";
		case _TYPE_ID_INT64:
			return L"_large";
		case _TYPE_ID_UINT8:
			return L"_byte";
		case _TYPE_ID_UINT16:
			return L"_word";
		case _TYPE_ID_UINT32:
			return L"_dword";
		case _TYPE_ID_UINT64:
			return L"_qword";
		case _TYPE_ID_FLOAT:
			return L"_float";
		case _TYPE_ID_DOUBLE:
			return L"_double";
		case _TYPE_ID_WSTRING:
			return L"String";
		case _TYPE_ID_POINTER:
			return L"_void*";
		default:
			return L"";
	}
}

_dword Variable::GetTypeIDSize(_dword type) {
	switch (type) {
		case _TYPE_ID_INT8:
			return 1;
		case _TYPE_ID_INT16:
			return 2;
		case _TYPE_ID_INT32:
			return 4;
		case _TYPE_ID_INT64:
			return 8;
		case _TYPE_ID_UINT8:
			return 1;
		case _TYPE_ID_UINT16:
			return 2;
		case _TYPE_ID_UINT32:
			return 4;
		case _TYPE_ID_UINT64:
			return 8;
		case _TYPE_ID_FLOAT:
			return 4;
		case _TYPE_ID_DOUBLE:
			return 8;
		case _TYPE_ID_WSTRING:
			return 4;
		case _TYPE_ID_POINTER:
			return 4;
		default:
			return 0;
	}
}
