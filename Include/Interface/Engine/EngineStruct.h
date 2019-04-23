#pragma once

namespace EGE {

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