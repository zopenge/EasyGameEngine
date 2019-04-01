//! @file     Version.h
//! @author   LiCode
//! @version  1.1.0.702
//! @date     2011/02/15
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Version
//----------------------------------------------------------------------------

class Version {
public:
	//! The zero version
	static Version cZero;
	//! The initial version
	static Version cInitial;

public:
	//! The max major version number
	enum { _MAX_MAJOR_NUMBER = 0xFFFF };
	//! The max minor version number
	enum { _MAX_MINOR_NUMBER = 0xFFFF };
	//! The max modified version number
	enum { _MAX_MODIFIED_NUMBER = 0xFFFF };
	//! The max build number
	enum { _MAX_BUILD_NUMBER = 0xFFFF };

private:
	//! The major version
	_word mMajor;
	//! The minor version
	_word mMinor;
	//! The modified version
	_word mModified;
	//! The build number
	_word mBuildNumber;

public:
	inline Version();
	inline Version(_word major, _word minor, _word modified, _word buildnumber);
	inline Version(AStringPtr versionstring);
	inline Version(UStringPtr versionstring);
	inline Version(WStringPtr versionstring);

public:
	//! Version comparison.
	inline _ubool operator==(const Version& version) const;
	inline _ubool operator!=(const Version& version) const;
	inline _ubool operator>=(const Version& version) const;
	inline _ubool operator<=(const Version& version) const;
	inline _ubool operator>(const Version& version) const;
	inline _ubool operator<(const Version& version) const;

	//! Copy from version string.
	inline const Version& operator=(AStringPtr versionstring);
	inline const Version& operator=(WStringPtr versionstring);

	//! Get version in ANSI string format.
	//! @param none.
	//! @return The version string.
	inline AString ToAString(_dword tags_number = 4) const;
	//! Get version in UTF-8 string format.
	//! @param none.
	//! @return The version string.
	inline UString ToUString(_dword tags_number = 4) const;
	//! Get version in UTF-16 string format.
	//! @param none.
	//! @return The version string.
	inline WString ToWString(_dword tags_number = 4) const;

	//! Check whether compatible or not.
	//! @param version  The version.
	//! @return True indicates it's compatible, otherwise it's not compatible.
	inline _ubool IsCompatible(const Version& version) const;

	//! Get the major/minor/modified/buildnumber version.
	inline _word GetMajorVersion() const;
	inline _word GetMinorVersion() const;
	inline _word GetModifiedVersion() const;
	inline _word GetBuildNumber() const;

	//! Set the major/minor/modified/buildnumber version.
	inline _void SetMajorVersion(_word major);
	inline _void SetMinorVersion(_word minor);
	inline _void SetModifiedVersion(_word modified);
	inline _void SetBuildNumber(_word buildnumber);

	//! Increase the major/minor/modified/buildnumber version.
	inline _word IncreaseMajorVersion();
	inline _word IncreaseMinorVersion();
	inline _word IncreaseModifiedVersion();
	inline _word IncreaseBuildNumber();

	//! Get the major/minor/modified/buildnumber next version.
	inline Version NextMajorVersion() const;
	inline Version NextMinorVersion() const;
	inline Version NextModifiedVersion() const;
	inline Version NextBuildNumber() const;
};

//----------------------------------------------------------------------------
// Version Implementation
//----------------------------------------------------------------------------

Version::Version() {
	mMajor = 0;
	mMinor = 0;
	mModified = 0;
	mBuildNumber = 0;
}

Version::Version(_word major, _word minor, _word modified, _word buildnumber)
    : mMajor(major), mMinor(minor), mModified(modified), mBuildNumber(buildnumber) {
}

Version::Version(AStringPtr versionstring) {
	// Convert string to UNICODE
	_charw versionstring_unicode[1024];
	Platform::AnsiToUtf16(versionstring_unicode, 1024, versionstring.CStr());

	*this = Version(versionstring_unicode);
}

Version::Version(UStringPtr versionstring) {
	// Convert string to UNICODE
	_charw versionstring_unicode[1024];
	Platform::Utf8ToUtf16(versionstring_unicode, 1024, versionstring.CStr());

	*this = Version(versionstring_unicode);
}

Version::Version(WStringPtr versionstring) {
	_charw string_buffer[1024];
	SafeCopyString(string_buffer, versionstring.CStr());

	// Split the version string
	_charw* substrings[4];
	_dword number = StringFormatter::SplitString<_charw>(string_buffer, substrings, L".", _null);

	// The [major, minor, modified, buildnumber] format
	if (number == 4) {
		mMajor = Platform::ConvertStringToLong(substrings[0], 10) & _MAX_MAJOR_NUMBER;
		mMinor = Platform::ConvertStringToLong(substrings[1], 10) & _MAX_MINOR_NUMBER;
		mModified = Platform::ConvertStringToLong(substrings[2], 10) & _MAX_MODIFIED_NUMBER;
		mBuildNumber = Platform::ConvertStringToLong(substrings[3], 10) & _MAX_BUILD_NUMBER;
	}
	// The [major, minor, modified] format
	else if (number == 3) {
		mMajor = Platform::ConvertStringToLong(substrings[0], 10) & _MAX_MAJOR_NUMBER;
		mMinor = Platform::ConvertStringToLong(substrings[1], 10) & _MAX_MINOR_NUMBER;
		mModified = Platform::ConvertStringToLong(substrings[2], 10) & _MAX_MODIFIED_NUMBER;
		mBuildNumber = 0;
	}
	// The [major, minor] format
	else if (number == 2) {
		mMajor = Platform::ConvertStringToLong(substrings[0], 10) & _MAX_MAJOR_NUMBER;
		mMinor = Platform::ConvertStringToLong(substrings[1], 10) & _MAX_MINOR_NUMBER;
		mModified = 0;
		mBuildNumber = 0;
	}
	// The [major] format
	else if (number == 1) {
		mMajor = Platform::ConvertStringToLong(substrings[0], 10) & _MAX_MAJOR_NUMBER;
		mMinor = 0;
		mModified = 0;
		mBuildNumber = 0;
	}
	// The unknown format
	else {
		mMajor = 0;
		mMinor = 0;
		mModified = 0;
		mBuildNumber = 0;
	}
}

_ubool Version::operator==(const Version& version) const {
	if (mMajor != version.mMajor)
		return _false;

	if (mMinor != version.mMinor)
		return _false;

	if (mModified != version.mModified)
		return _false;

	if (mBuildNumber != version.mBuildNumber)
		return _false;

	return _true;
}

_ubool Version::operator!=(const Version& version) const {
	if (mMajor != version.mMajor)
		return _true;

	if (mMinor != version.mMinor)
		return _true;

	if (mModified != version.mModified)
		return _true;

	if (mBuildNumber != version.mBuildNumber)
		return _true;

	return _false;
}

_ubool Version::operator>=(const Version& version) const {
	COMPARE_BIG(mMajor, version.mMajor);
	COMPARE_BIG(mMinor, version.mMinor);
	COMPARE_BIG(mModified, version.mModified);
	COMPARE_BIG(mBuildNumber, version.mBuildNumber);

	return _true;
}

_ubool Version::operator<=(const Version& version) const {
	COMPARE_LESS(mMajor, version.mMajor);
	COMPARE_LESS(mMinor, version.mMinor);
	COMPARE_LESS(mModified, version.mModified);
	COMPARE_LESS(mBuildNumber, version.mBuildNumber);

	return _true;
}

_ubool Version::operator>(const Version& version) const {
	COMPARE_BIG(mMajor, version.mMajor);
	COMPARE_BIG(mMinor, version.mMinor);
	COMPARE_BIG(mModified, version.mModified);
	COMPARE_BIG(mBuildNumber, version.mBuildNumber);

	return _false;
}

_ubool Version::operator<(const Version& version) const {
	COMPARE_LESS(mMajor, version.mMajor);
	COMPARE_LESS(mMinor, version.mMinor);
	COMPARE_LESS(mModified, version.mModified);
	COMPARE_LESS(mBuildNumber, version.mBuildNumber);

	return _false;
}

const Version& Version::operator=(AStringPtr versionstring) {
	*this = Version(versionstring);

	return *this;
}

const Version& Version::operator=(WStringPtr versionstring) {
	*this = Version(versionstring);

	return *this;
}

AString Version::ToAString(_dword tags_number) const {
	// Build the version string
	_chara buffer[1024];
	buffer[0] = 0;

	switch (tags_number) {
	case 1:
		Platform::FormatStringBuffer(buffer, EGE_ARRAY_NUMBER(buffer), "%d", mMajor);
		break;
	case 2:
		Platform::FormatStringBuffer(buffer, EGE_ARRAY_NUMBER(buffer), "%d.%d", mMajor, mMinor);
		break;
	case 3:
		Platform::FormatStringBuffer(buffer, EGE_ARRAY_NUMBER(buffer), "%d.%d.%d", mMajor, mMinor, mModified);
		break;
	case 4:
		Platform::FormatStringBuffer(buffer, EGE_ARRAY_NUMBER(buffer), "%d.%d.%d.%d", mMajor, mMinor, mModified, mBuildNumber);
		break;
	default:
		break;
	}

	return buffer;
}

UString Version::ToUString(_dword tags_number) const {
	return UString().FromString(ToAString(tags_number));
}

WString Version::ToWString(_dword tags_number) const {
	return WString().FromString(ToAString(tags_number));
}

_ubool Version::IsCompatible(const Version& version) const {
	if (mMajor != version.mMajor)
		return _false;

	if (mMinor != version.mMinor)
		return _false;

	return _true;
}

_word Version::GetMajorVersion() const {
	return mMajor;
}

_word Version::GetMinorVersion() const {
	return mMinor;
}

_word Version::GetModifiedVersion() const {
	return mModified;
}

_word Version::GetBuildNumber() const {
	return mBuildNumber;
}

_void Version::SetMajorVersion(_word major) {
	mMajor = major;
}

_void Version::SetMinorVersion(_word minor) {
	mMinor = minor;
}

_void Version::SetModifiedVersion(_word modified) {
	mModified = modified;
}

_void Version::SetBuildNumber(_word buildnumber) {
	mBuildNumber = buildnumber;
}

_word Version::IncreaseMajorVersion() {
	if (mMajor != _MAX_MAJOR_NUMBER)
		mMajor++;

	return mMajor;
}

_word Version::IncreaseMinorVersion() {
	if (mMinor == _MAX_MINOR_NUMBER) {
		mMajor++;
		mMinor = 0;
	} else {
		mMinor++;
	}

	return mMinor;
}

_word Version::IncreaseModifiedVersion() {
	if (mModified == _MAX_MODIFIED_NUMBER) {
		NextMinorVersion();
		mModified = 0;
	} else {
		mModified++;
	}

	return mModified;
}

_word Version::IncreaseBuildNumber() {
	if (mBuildNumber != _MAX_BUILD_NUMBER)
		mBuildNumber++;

	return mBuildNumber;
}

Version Version::NextMajorVersion() const {
	Version version = *this;
	version.IncreaseMajorVersion();

	return version;
}

Version Version::NextMinorVersion() const {
	Version version = *this;
	version.IncreaseMinorVersion();

	return version;
}

Version Version::NextModifiedVersion() const {
	Version version = *this;
	version.IncreaseModifiedVersion();

	return version;
}

Version Version::NextBuildNumber() const {
	Version version = *this;
	version.IncreaseBuildNumber();

	return version;
}

} // namespace EGE
