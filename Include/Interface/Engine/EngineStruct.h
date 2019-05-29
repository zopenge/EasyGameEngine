#pragma once

namespace EGE {

/// <summary>
/// The base font face code data.
/// </summary>
struct BaseFontFaceCodeData {
	_charw mCode;

	_short mCharWidth;
	_short mCharHeight;
	_short mMaxCharWidth;
	_short mMaxCharHeight;

	_short mAdvanceX;
	_short mBearingY;
	_short mOffsetX;
	_short mOffsetY;

	_short mAscender;
	_short mDescender;
	_short mBaseLine;

	BaseFontFaceCodeData() {
		mCode = 0;

		mCharWidth = 0;
		mCharHeight = 0;
		mMaxCharWidth = 0;
		mMaxCharHeight = 0;

		mAdvanceX = 0;
		mBearingY = 0;
		mOffsetX = 0;
		mOffsetY = 0;

		mAscender = 0;
		mDescender = 0;
		mBaseLine = 0;
	}
};

/// <summary>
/// The font face code with bitmap pixel buffer data.
/// </summary>
struct FontFaceCodeData : public BaseFontFaceCodeData {
	_short mBitmapLeft;
	_short mBitmapTop;
	_short mBitmapWidth;
	_short mBitmapHeight;
	const _byte* mBitmapBuffer;

	FontFaceCodeData() {
		mBitmapLeft = 0;
		mBitmapTop = 0;
		mBitmapWidth = 0;
		mBitmapHeight = 0;
		mBitmapBuffer = _null;
	}

	FontFaceCodeData& operator=(const FontFaceCodeData& info) {
		mCharWidth = info.mCharWidth;
		mCharHeight = info.mCharHeight;
		mMaxCharWidth = info.mMaxCharWidth;
		mMaxCharHeight = info.mMaxCharHeight;

		mAdvanceX = info.mAdvanceX;
		mBearingY = info.mBearingY;
		mOffsetX = info.mOffsetX;
		mOffsetY = info.mOffsetY;

		mAscender = info.mAscender;
		mDescender = info.mDescender;

		return *this;
	}
};

/// <summary>
/// The manifest item data.
/// </summary>
struct ManifestItemData {
	//!	The item name
	WString mName;
	//!	The item MD5 checksum code
	MD5Code mMD5Code;

	//!	Use the name as key
	operator WStringPtr() const {
		return mName;
	}

	_ubool operator==(const ManifestItemInfo& item_info) const {
		if (mName != item_info.mName)
			return _false;

		if (mMD5Code != item_info.mMD5Code)
			return _false;

		return _true;
	}

	_ubool operator!=(const ManifestItemInfo& item_info) const {
		if (mName != item_info.mName)
			return _true;

		if (mMD5Code != item_info.mMD5Code)
			return _true;

		return _false;
	}

	ManifestItemData() {
	}
};
typedef Array<ManifestItemData> ManifestItemDataArray;

//!	The platform device info
struct PlatformDeviceInfo {
	//!	The advertising identifier
	WString mAdvertisingIdentifier;
	//!	The identifier for vendor
	WString mIdentifierForVendor;
	//!	The device name
	WString mDeviceName;
	//!	The model name.
	WString mModelName;
	//!	The system name
	WString mSystemName;
	//!	The system version
	WString mSystemVersion;
	//! hardware unique ID
	WString mHardwareUniqueID;
};

/// <summary>
/// The string object class.
/// </summary>
template <typename CharType, Encoding CharEncoding>
class TStringObj : public ConstString<CharType, CharEncoding> {
protected:
	//!	The unique ID
	_dword mID;

public:
	TStringObj(const CharType* string);
	TStringObj(ConstString<CharType, CharEncoding> string);
	TStringObj(const MutableStringR<CharType, CharEncoding>& string);
	TStringObj() {
		static CharType sNull = 0;

		mID = -1;
		mString = &sNull;
	}
	TStringObj(_dword id, const CharType* string) {
		EGE_ASSERT(string != _null);

		mID = id;
		mString = (CharType*)string;
	}
	TStringObj(const TStringObj& obj) {
		mID = obj.mID;
		mString = obj.mString;
	}
	~TStringObj() {
	}

public:
	//!	Compare operations.
	_ubool operator==(const TStringObj& refstring) const {
		return mID == refstring.mID;
	}
	_ubool operator!=(const TStringObj& refstring) const {
		return mID != refstring.mID;
	}
	_ubool operator>(const TStringObj& refstring) const {
		return mID > refstring.mID;
	}
	_ubool operator>=(const TStringObj& refstring) const {
		return mID >= refstring.mID;
	}
	_ubool operator<(const TStringObj& refstring) const {
		return mID < refstring.mID;
	}
	_ubool operator<=(const TStringObj& refstring) const {
		return mID <= refstring.mID;
	}

	//!	Compare operations.
	_ubool operator==(const CharType* string) const {
		return Platform::CompareString(mString, string) == 0;
	}
	_ubool operator!=(const CharType* string) const {
		return Platform::CompareString(mString, string) != 0;
	}
	_ubool operator>(const CharType* string) const {
		return Platform::CompareString(mString, string) > 0;
	}
	_ubool operator>=(const CharType* string) const {
		return Platform::CompareString(mString, string) >= 0;
	}
	_ubool operator<(const CharType* string) const {
		return Platform::CompareString(mString, string) < 0;
	}
	_ubool operator<=(const CharType* string) const {
		return Platform::CompareString(mString, string) <= 0;
	}

public:
	//!	Convert to string.
	operator ConstString<CharType, CharEncoding>() const {
		return mString;
	}
	operator MutableString<CharType, CharEncoding>() const {
		return mString;
	}

	//!	Assign.
	TStringObj& operator=(const CharType* string);
	TStringObj& operator=(ConstString<CharType, CharEncoding> string);
	TStringObj& operator=(const MutableStringR<CharType, CharEncoding>& string);
	TStringObj& operator=(const TStringObj& obj) {
		mID = obj.mID;
		mString = obj.mString;

		return *this;
	}

	//!	Get the unique ID.
	_dword GetID() const {
		return mID;
	}

	//!	Get the encoding type.
	Encoding GetEncodeType() const {
		return CharEncoding;
	}
	//!	Get the string.
	const CharType* CStr() const {
		return mString;
	}

	//! Compare two strings
	_ubool IsEqual(const CharType* string, _ubool ignorecase = _false) const {
		return Platform::CompareString(mString, string, ignorecase) == 0;
	}
	//! Check whether it's empty.
	_ubool IsEmpty() const {
		return mString[0] == 0;
	}
};

} // namespace EGE