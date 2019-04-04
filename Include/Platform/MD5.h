#pragma once

namespace EGE {

/// <summary>
/// This class represents a unsigned 128-bits integer.
/// </summary>
class MD5Code {
public:
	static MD5Code cNull;

public:
	//! The unsigned 128-bits integer.
	_dword mCode[4];

private:
	//! Get the section number from MD5 string.
	template <typename StringPtrType>
	static _dword GetSectionNumber(StringPtrType string) {
		_dword number = 0;

		for (_dword i = 0; string[i] != 0; i++) {
			if (string[i] == '-')
				number++;
		}

		return number;
	}

public:
	//! Constructor.
	MD5Code();
	//! Constructor, create an object from four dwords.
	//! @param dword1  The 1st dword of the oword.
	//! @param dword2  The 2nd dword of the oword.
	//! @param dword3  The 3rd dword of the oword.
	//! @param dword4  The 4th dword of the oword.
	MD5Code(_dword dword1, _dword dword2, _dword dword3, _dword dword4);
	//! Constructor, create an object from MD5 code.
	MD5Code(const MD5Code& code);

public:
	//! Compare two 128-bits integer.
	//! @param oword  The second 128-bits integer.
	//! @return True if two 128-bits integer are same, false otherwise.
	inline _ubool operator==(const MD5Code& oword) const {
		return mCode[0] == oword.mCode[0] && mCode[1] == oword.mCode[1] && mCode[2] == oword.mCode[2] && mCode[3] == oword.mCode[3];
	}
	//! Compare two 128-bits integer.
	//! @param oword  The second 128-bits integer.
	//! @return True if two 128-bits integer are not same, false otherwise.
	inline _ubool operator!=(const MD5Code& oword) const {
		return mCode[0] != oword.mCode[0] || mCode[1] != oword.mCode[1] || mCode[2] != oword.mCode[2] || mCode[3] != oword.mCode[3];
	}

	//! Comparison operations.
	_ubool operator>=(const MD5Code& oword) const;
	_ubool operator>(const MD5Code& oword) const;
	_ubool operator<=(const MD5Code& oword) const;
	_ubool operator<(const MD5Code& oword) const;

	//! Parse from a ANSI string.
	//! @param string  The string contains the hex integer.
	//! @return True indicates success, false indicates failure.
	_ubool ParseFromString(AStringPtr string);
	//! Parse from a UTF-8 string.
	//! @param string  The string contains the hex integer.
	//! @return True indicates success, false indicates failure.
	_ubool ParseFromString(UStringPtr string);
	//! Parse from a UTF-16 string.
	//! @param string  The string contains the hex integer.
	//! @return True indicates success, false indicates failure.
	_ubool ParseFromString(WStringPtr string);

	//! Convert to a ANSI string.
	//! @param format  True indicates format MD5 with 'x-x-x-x' string style.
	//! @return The string presentation of the integer in hex.
	AString ToAString(_ubool format) const;
	//! Convert to a ANSI string.
	//! @param buffer  The buffer used to copy string.
	//! @param size  The max size of buffer in number of characters.
	//! @param format  True indicates format MD5 with 'x-x-x-x' string style.
	//! @return The string presentation of the integer in hex.
	AStringPtr ToAString(_chara* buffer, _dword size, _ubool format) const;

	//! Convert to a UTF-16 string.
	//! @param format  True indicates format MD5 with 'x-x-x-x' string style.
	//! @return The string presentation of the integer in hex.
	WString ToWString(_ubool format) const;
	//! Convert to a UTF-16 string.
	//! @param buffer  The buffer used to copy string.
	//! @param size  The max size of buffer in number of characters.
	//! @param format  True indicates format MD5 with 'x-x-x-x' string style.
	//! @return The string presentation of the integer in hex.
	WStringPtr ToWString(_charw* buffer, _dword size, _ubool format) const;
};

/// <summary>
/// The MD5 code builder.
/// </summary>
class MD5 {
private:
	//! The md5 state
	struct MD5State {
		_dword count[2]; /* message length in bits, lsw first */
		_dword abcd[4]; /* digest buffer */
		_byte buf[64]; /* accumulate block */
	};

private:
	MD5State mState;
	_byte mDigest[16];
	_ubool mFinished;

private:
	//! Initialize MD5 state.
	EGE_INTERNAL static _void Initialize(MD5State& state);

	//! Process/Calculate MD5 code from buffer data in MD5 state.
	EGE_INTERNAL static _void Process(MD5State& state, const _byte* data /*[64]*/);
	//! Append buffer data to MD5 state.
	EGE_INTERNAL static _void Append(MD5State& state, const _byte* data, _dword nbytes);
	//! Finish the message and return the digest.
	EGE_INTERNAL static _void Finish(MD5State& state, _byte digest[16]);

public:
	EGE_INTERNAL MD5();
	EGE_INTERNAL ~MD5();

public:
	//! Clear.
	EGE_INTERNAL _void Clear();

	//! Append buffer data.
	EGE_INTERNAL _void AppendBuffer(const _void* buffer, _dword size);

	//! Call finish and update digest code.
	EGE_INTERNAL _void Digest();

	//! Get MD5 code.
	//! @remark  You must call Digest( ) to end up it first.
	EGE_INTERNAL MD5Code GetCode() const;

public:
	//! Build the MD5 value from buffer.
	//! @param buffer  The buffer data.
	//! @param size  The buffer size.
	//! @return The MD5 128-bits checksum.
	EGE_INTERNAL static MD5Code BuildFromBuffer(const _byte* buffer, _dword size);
	//! Build the MD5 value from string.
	//! @param string  The string buffer.
	//! @return The MD5 128-bits checksum.
	EGE_INTERNAL static MD5Code BuildFromString(AStringPtr string);
	//! Build the MD5 value from string.
	//! @param string  The string buffer.
	//! @return The MD5 128-bits checksum.
	EGE_INTERNAL static MD5Code BuildFromString(WStringPtr string);
};

} // namespace EGE