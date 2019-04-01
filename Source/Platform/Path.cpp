//! @file     Path.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Path Implementation
//----------------------------------------------------------------------------

Path::Path() {
}

Path::Path(const Path& path) {
	mSubPath = path.mSubPath;
}

Path::Path(WStringPtr path) {
	StringFormatter::SplitString(path, mSubPath, L"/\\", L" \t");
}

_ubool Path::operator==(const Path& path) const {
	if (mSubPath.Number() != path.Number())
		return _false;

	for (_dword i = 0; i < mSubPath.Number(); i++) {
		if (mSubPath[i] != path[i])
			return _false;
	}

	return _true;
}

_ubool Path::operator!=(const Path& path) const {
	if (mSubPath.Number() != path.Number())
		return _true;

	for (_dword i = 0; i < mSubPath.Number(); i++) {
		if (mSubPath[i] != path[i])
			return _true;
	}

	return _false;
}

_ubool Path::operator>(const Path& path) const {
	_dword min_number = Math::Min<_dword>(mSubPath.Number(), path.Number());

	for (_dword i = 0; i < min_number; i++) {
		if (mSubPath[i] > path[i])
			return _true;
	}

	return mSubPath.Number() > path.Number();
}

_ubool Path::operator<(const Path& path) const {
	_dword min_number = Math::Min<_dword>(mSubPath.Number(), path.Number());

	for (_dword i = 0; i < min_number; i++) {
		if (mSubPath[i] < path[i])
			return _true;
	}

	return mSubPath.Number() < path.Number();
}

_ubool Path::operator>=(const Path& path) const {
	_dword min_number = Math::Min<_dword>(mSubPath.Number(), path.Number());

	for (_dword i = 0; i < min_number; i++) {
		if (mSubPath[i] >= path[i])
			return _true;
	}

	return mSubPath.Number() >= path.Number();
}

_ubool Path::operator<=(const Path& path) const {
	_dword min_number = Math::Min<_dword>(mSubPath.Number(), path.Number());

	for (_dword i = 0; i < min_number; i++) {
		if (mSubPath[i] <= path[i])
			return _true;
	}

	return mSubPath.Number() <= path.Number();
}

WStringPtr Path::operator[](_dword index) const {
	return mSubPath[index];
}

_dword Path::Number() const {
	return mSubPath.Number();
}

WString Path::CStr() const {
	WString string;

	for (_dword i = 0; i < mSubPath.Number(); i++) {
		string += mSubPath[i];

		if (i != mSubPath.Number() - 1)
			string += L"/";
	}

	return string;
}

WString Path::GetFileName(_ubool extension) const {
	if (mSubPath.Number() == 0)
		return WString(L"");

	return Path::GetFileName<WString, WStringPtr>(mSubPath.GetTailElement(), extension);
}
