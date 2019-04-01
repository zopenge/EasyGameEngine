//! @file     MutableString.h
//! @author   LiCode
//! @version  1.0.1.804
//! @date     2011/03/10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// MutableString
//----------------------------------------------------------------------------

//! This class represents a mutable null-terminated string.
template <typename CharType, Encoding CharEncoding>
class MutableString {
protected:
	typedef ConstString<CharType, CharEncoding> ConstStringType;

protected:
	//!	The string length
	_dword mLength;
	//!	The string buffer size in (Type) mode
	_dword mSize;
	//!	The string buffer.
	CharType* mString;

protected:
	/// <summary>
	/// Initialize the string.
	/// </summary>
	_void Init();

	//!	Create string buffer.
	//!	@param		string		If we provide the string buffer then copy it when create string buffer finished.
	//!	@return		none.
	_void CreateStringBuffer(const CharType* string);
	//!	Copy string buffer.
	//!	@param		string		The source string buffer.
	//!	@return		none.
	_void CopyStringBuffer(const CharType* string);

	//!	Append string buffer.
	//!	@param		string		The string buffer.
	//!	@param		length		The string length.
	//!	@return		none.
	_void AppendStringBuffer(const CharType* string, _dword length);

public:
	//! Constructor, create a string only contains the terminal null.
	//! @param		none
	MutableString();
	//! Copy-Constructor, create a string by copy another string object.
	//! @param		string	The second string object.
	//! @param		number		The number of characters to be copy.
	MutableString(ConstStringType string, _dword number = -1);
	//! Copy-Constructor, create a string by copy another string object.
	//! @param		string	The second string object.
	MutableString(const MutableString& string);
	//! Constructor, create a string by character.
	//! @param		char_code	The character code.
	MutableString(CharType char_code);
	//! Destructor, delete the memory of the string.
	//! @param		none
	~MutableString();

public:
	//! Copy the string from character, and recreates memory to hold it.
	//! @param		character	The character.
	//! @return		The reference of current string.
	MutableString& operator=(CharType character);
	//! Copy the string from another one, and recreates memory to hold it.
	//! @param		string		Pointer to a null-terminated string.
	//! @return		The reference of current string.
	MutableString& operator=(ConstStringType string);
	//! Copy the string from another one, and recreates memory to hold it.
	//! @param		string		The string object.
	//! @return		The reference of current string.
	MutableString& operator=(const MutableString& string);

	//! Append a character to the end of the string.
	//! @param		character	The character to be append.
	//! @return		The reference of current string.
	MutableString& operator+=(CharType character);
	//! Append another string to the end of the current one.
	//! @param		string		Pointer to a null-terminated string.
	//! @return		The reference of current string.
	MutableString& operator+=(ConstStringType string);
	//! Append another string to the end of the current one.
	//! @param		string		Pointer to a null-terminated string.
	//! @return		The reference of current string.
	MutableString& operator+=(const MutableString& string);

	//! Get a character from string by index.
	//! @param		index		The index of the character in string.
	//! @return		A character specified by index
	template <typename IndexType>
	CharType& operator[](IndexType index);
	//! Get a character from string by index.
	//! @param		index		The index of the character in string.
	//! @return		A character specified by index
	template <typename IndexType>
	const CharType& operator[](IndexType index) const;

	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if two strings are same, false otherwise.
	_ubool operator==(ConstStringType string) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if two strings are not same, false otherwise.
	_ubool operator!=(ConstStringType string) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is greater than the second one, false otherwise.
	_ubool operator>(ConstStringType string) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is less than the second one, false otherwise.
	_ubool operator<(ConstStringType string) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is greater or equal than the second one, false otherwise.
	_ubool operator>=(ConstStringType string) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is less or equal than the second one, false otherwise.
	_ubool operator<=(ConstStringType string) const;

	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if two strings are same, false otherwise.
	_ubool operator==(const MutableString& string) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if two strings are not same, false otherwise.
	_ubool operator!=(const MutableString& string) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is greater than the second one, false otherwise.
	_ubool operator>(const MutableString& string) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is less than the second one, false otherwise.
	_ubool operator<(const MutableString& string) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is greater or equal than the second one, false otherwise.
	_ubool operator>=(const MutableString& string) const;
	//! Compare two strings with case sensitive.
	//! @param		string		The second string.
	//! @return		True if the first string is less or equal than the second one, false otherwise.
	_ubool operator<=(const MutableString& string) const;

public:
	//!	Convert to const null-terminated string.
	//!	@param		none.
	//!	@return		The const null-terminated string.
	operator ConstStringType() const;

	//! Get the length of the string, excluding the terminal null, overwrite parent class function.
	//! @param		none
	//! @return		The Length of the string.
	_dword GetLength() const;
	//! Get the size of the string.
	//! @param		none
	//! @return		The size of the string.
	_dword GetSize() const;
	//! Get the number of bytes used by string, include the terminal null, overwrite parent class function.
	//! @param		none
	//! @return		The number of bytes used by string.
	_dword SizeOfBytes() const;

	//!	Resize.
	//!	@param		size		The length of string, including the terminal null.
	//!	@none.
	_void Resize(_dword size);
	//!	Clear.
	//! @param		freememory	True indicates free the memory used by string.
	//!	@return		none.
	_void Clear(_ubool freememory = _false);
	//!	Reduce capacity.
	//!	@param		none.
	//!	@return		none.
	_void ShrinkToFit();

	//! Insert a character into the index of the string.
	//! @param		index		The index of the string
	//! @param		character	The character to be inserted.
	//! @remark		The character will be inserted before the index.<br>
	//!				For example, "Hello".Insert( 0, 'W' ) will results "WHello",
	//!				and "Hello".Insert( 5, 'W' ) will results "HelloW".
	_void Insert(_dword index, CharType character);
	//! Insert a substring into the index of the string.
	//! @param		index		The index of the string.
	//! @param		string		The substring to be inserted.
	//! @remark		The substring will be inserted before the index.<br>
	//!				For example, "Hello".Insert( 0, "World" ) will results "WorldHello",
	//!				and "Hello".Insert( 5, "World" ) will results "HelloWorld".
	_void Insert(_dword index, ConstStringType string);
	//! Remove some characters at the index of the string.
	//! @param		index		The index of the string.
	//! @param		number		The number of characters to be removed.
	//! @remark		The character will be removed start from the index.<br>
	//!				For example, "Hello".Remove( 0, 2 ) will results "llo",
	//!				"Hello".Remove( 4, 1 ) will results "Hell",
	//!				and "Hello".Remove( 4, 2 ) will failed ( return false ).
	_void Remove(_dword index, _dword number = -1);
	//! Remove some characters by range.
	//! @param		range	The range of string.
	_void Remove(const DwordRange& range);

	//! Search and replace all substring to another.
	//! @param		srcstring	The substring to be searched.
	//! @param		desstring	The substring to be replaced.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True if successfully searched & replaced, false otherwise.
	_ubool Replace(ConstStringType srcstring, ConstStringType desstring, _ubool ignorecase = _false);
	//! Search and replace a character to another one.
	//! @param		index		The index of character to be replaced.
	//! @param		character	The character to be used.
	//! @return		True if successfully searched & replaced, false otherwise.
	_ubool Replace(_dword index, CharType character);
	//! Search and replace a character to another one.
	//! @param		index		The index of character to be replaced.
	//! @param		number		The number for character to be replaced.
	//! @param		character	The character to be used.
	//! @return		True if successfully searched & replaced, false otherwise.
	_ubool Replace(_dword index, _dword number, CharType character);

	//! Copy the string from another string, and recreates memory to hold it.
	//! @param		string		Pointer to a null-terminated string.
	//! @param		length		The length of string.
	//! @return		The reference of current string.
	MutableString& CopyString(ConstStringType string, _dword length = -1);

	//! Convert the string to lowercase.
	//! @return		The pointer of the string with lowercase.
	MutableString& Lowercase();
	//! Convert the string to uppercase.
	//! @return		The pointer of the string with uppercase.
	MutableString& Uppercase();

	//!	Trim character from left to right.
	//!	@param		character	The character what you want to trim.
	//!	@return		The trimmed string.
	MutableString& TrimLeft(CharType character);
	//!	Trim character from right to left.
	//!	@param		character	The character what you want to trim.
	//!	@return		The trimmed string.
	MutableString& TrimRight(CharType character);
	//!	Trim character both left and right.
	//!	@param		character	The character what you want to trim.
	//!	@return		The trimmed string.
	MutableString& TrimBoth(CharType character);

	//!	Trim substring from left to right.
	//!	@param		charset		The substring what you want to trim.
	//!	@return		The trimmed string.
	MutableString& TrimLeft(ConstStringType charset);
	//!	Trim substring from right to left.
	//!	@param		charset		The substring what you want to trim.
	//!	@return		The trimmed string.
	MutableString& TrimRight(ConstStringType charset);
	//!	Trim substring both left and right.
	//!	@param		charset		The substring what you want to trim.
	//!	@return		The trimmed string.
	MutableString& TrimBoth(ConstStringType charset);

	//! Get the substring start from a index.
	//! @param		index		The index of the string, must be less or equal than the length of the string.
	//! @return		The substring from the index.
	MutableString SubString(_dword index) const;
	//! Get the substring start from a index.
	//! @param		start		The index of the string, must be less or equal than the length of the string.
	//! @return		The substring from the index.
	MutableString SubString(_dword start, _dword length) const;

	//! Get the substring from left to right.
	//! @param		delimiter	The delimiter character what substring will be end there.
	//! @return		The substring.
	MutableString LeftSubString(CharType delimiter) const;
	//! Get the substring from left to right.
	//! @param		delimiter	The delimiter string what substring will be end there.
	//! @return		The substring.
	MutableString LeftSubString(ConstStringType delimiter) const;
	//! Get the substring from right to left.
	//! @param		delimiter	The delimiter character what substring will be end there.
	//! @return		The substring.
	MutableString RightSubString(CharType delimiter) const;
	//! Get the substring from right to left.
	//! @param		delimiter	The delimiter string what substring will be end there.
	//! @return		The substring.
	MutableString RightSubString(ConstStringType delimiter) const;

	//! Copy from signed value.
	//! @param		value		The integer value.
	//! @param		radix		The base of value, which must be in the range 2每36.
	//! @return		The referenced string.
	MutableString& FromValue(_int value, _dword radix = 10);
	//! Copy from unsigned value.
	//! @param		value		The integer value.
	//! @param		radix		The base of value, which must be in the range 2每36.
	//! @return		The referenced string.
	MutableString& FromValue(_dword value, _dword radix = 10);
	//! Copy from 64-bits unsigned value.
	//! @param		value		The integer value.
	//! @param		radix		The base of value, which must be in the range 2每36.
	//! @return		The referenced string.
	MutableString& FromValue(_large value, _dword radix = 10);
	//! Copy from 64-bits unsigned value.
	//! @param		value		The integer value.
	//! @param		radix		The base of value, which must be in the range 2每36.
	//! @return		The referenced string.
	MutableString& FromValue(_qword value, _dword radix = 10);
	//! Copy from float value.
	//! @param		value		The float value.
	//! @param		precision	The floating point precision after decimal point.
	//! @return		The referenced string.
	MutableString& FromValue(_float value, _dword precision = 6);
	//! Copy from double value.
	//! @param		value		The double value.
	//! @param		precision	The floating point precision after decimal point.
	//! @return		The referenced string.
	MutableString& FromValue(_double value, _dword precision = 15);

	//! Copy from another string ( auto convert encode type ).
	//! @param		string		The another string object.
	//! @return		The referenced string.
	template <class FromStringType>
	MutableString& FromString(const FromStringType& string);
	//! Copy from another string ( auto convert encode type ).
	//! @param		encode		The another string encode type.
	//! @param		string		The another string pointer.
	//! @return		The referenced string.
	template <typename FromCharType>
	MutableString& FromString(Encoding encode, const FromCharType* string);

	//!	Format string to bytes style.
	//! @param		bytes		The total bytes.
	//! @return		The referenced string.
	MutableString& FormatBytes(_qword bytes);
	//!	Format string to currency style.
	//! @param		currency	The currency.
	//! @return		The referenced string.
	MutableString& FormatCurrency(_qword currency);
	//!	Format string to time style.
	//! @param		millisecond	The millisecond.
	//! @return		The referenced string.
	MutableString& FormatTime(_qword millisecond);

	//!	Format string.
	//!	@param		format		The format of string.
	//!	@param		...			The optional arguments.
	//! @return		none.
	_void FormatStringByArguments(const CharType* format, ...);
	//!	Format string.
	//!	@param		format		The format of string.
	//!	@param		arguments	The optional arguments.
	//! @return		none.
	_void FormatStringByVAList(const CharType* format, _va_list arguments);
};

//----------------------------------------------------------------------------
// MutableString Implementation
//----------------------------------------------------------------------------

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>::MutableString() {
	Init();
}

template <typename CharType, Encoding CharEncoding>
void MutableString<CharType, CharEncoding>::Init() {
	mLength = 0;
	mSize = 0;

	static _dword sNull = 0;
	mString = (const CharType*)&sNull;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>::MutableString(ConstStringType string, _dword number) {
	if (string.IsEmpty()) {
		Init();
	} else {
		// Get the string length
		if (number == -1)
			mLength = string.GetLength();
		else
			mLength = number;

		// Create and copy the string buffer
		CreateStringBuffer(string);
	}
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>::MutableString(const MutableString& string) {
	if (string.IsEmpty()) {
		Init();
	} else {
		// Get the string length
		mLength = string.GetLength();

		// Create and copy the string buffer
		CreateStringBuffer(string.CStr());
	}
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>::MutableString(CharType char_code) {
	if (char_code == 0) {
		Init();
	} else {
		mLength = 1;
		mSize = mLength + 1;
		this->mString = new CharType[mSize];

		// Copy string
		this->mString[0] = char_code;
		this->mString[mLength] = 0;
	}
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>::~MutableString() {
	Clear(_true);
}

template <typename CharType, Encoding CharEncoding>
_void MutableString<CharType, CharEncoding>::CreateStringBuffer(const CharType* string) {
	// Create string buffer
	mSize = mLength + 1;
	this->mString = new CharType[mSize];

	// Copy string
	if (string != _null)
		CopyStringBuffer(string);
}

template <typename CharType, Encoding CharEncoding>
_void MutableString<CharType, CharEncoding>::CopyStringBuffer(const CharType* string) {
	// Copy string
	EGE_MEM_CPY(this->mString, string, mLength * sizeof(CharType));

	// Set null-terminated
	this->mString[mLength] = 0;
}

template <typename CharType, Encoding CharEncoding>
_void MutableString<CharType, CharEncoding>::AppendStringBuffer(const CharType* string, _dword length) {
	// Get the string length
	_dword length1 = mLength;
	_dword length2 = length;

	// Get the total string length
	mLength = length1 + length2;

	// Create more memory if necessary
	if (mSize < mLength + 1) {
		CharType* oldstring = this->mString;
		_ubool olddelete = mSize > 0;

		// Create new memory to save both string
		mSize = mLength + 1;
		this->mString = new CharType[mSize];

		// Copy old string back to buffer
		EGE_MEM_CPY(this->mString, oldstring, length1 * sizeof(CharType));

		// Delete the old memory
		if (olddelete) {
			delete[] oldstring;
		}
	}

	// Append new string
	EGE_MEM_CPY(this->mString + length1, string, length2 * sizeof(CharType));

	// Set null-terminated
	this->mString[mLength] = 0;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::operator=(CharType character) {
	CharType string[] = {character, 0};
	return operator=(string);
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::operator=(ConstStringType string) {
	// Get the string length
	mLength = string.GetLength();

	// It's empty string
	if (mLength == 0) {
		if (mSize > 0)
			this->mString[0] = 0;
	}
	// Create more memory if necessary
	else if (mSize < mLength + 1) {
		// Free the old string buffer
		if (mSize > 0) {
			delete[] this->mString;
		}

		// Create and copy the string buffer
		CreateStringBuffer(string);
	} else {
		// Copy the string buffer
		CopyStringBuffer(string);
	}

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::operator=(const MutableString& string) {
	// Get the string length
	mLength = string.GetLength();

	// It's empty string
	if (mLength == 0) {
		if (mSize > 0)
			this->mString[0] = 0;
	}
	// Create more memory if necessary
	else if (mSize < mLength + 1) {
		// Free the old string buffer
		if (mSize > 0) {
			delete[] this->mString;
		}

		// Create and copy the string buffer
		CreateStringBuffer(string.CStr());
	} else {
		// Copy the string buffer
		CopyStringBuffer(string.CStr());
	}

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::operator+=(CharType character) {
	if (character == 0)
		return *this;

	_dword oldlength = mLength;

	// Increase the string length
	mLength++;

	// Create more memory if necessary.
	if (mSize < mLength + 1) {
		CharType* oldstring = this->mString;
		_ubool olddelete = mSize > 0;

		// Create new memory to save both string
		mSize = mLength + 1;
		this->mString = new CharType[mSize];

		// Copy old string back to buffer
		EGE_MEM_CPY(this->mString, oldstring, oldlength * sizeof(CharType));

		// Delete the old memory
		if (olddelete) {
			delete[] oldstring;
		}
	}

	// Append character
	this->mString[oldlength] = character;

	// Set null-terminated
	this->mString[mLength] = 0;

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::operator+=(ConstStringType string) {
	if (string.IsEmpty())
		return *this;

	AppendStringBuffer(string, string.GetLength());

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::operator+=(const MutableString& string) {
	if (string.IsEmpty())
		return *this;

	AppendStringBuffer(string.CStr(), string.GetLength());

	return *this;
}

template <typename CharType, Encoding CharEncoding>
template <typename IndexType>
CharType& MutableString<CharType, CharEncoding>::operator[](IndexType index) {
	return this->mString[index];
}

template <typename CharType, Encoding CharEncoding>
template <typename IndexType>
const CharType& MutableString<CharType, CharEncoding>::operator[](IndexType index) const {
	return this->mString[index];
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::operator==(ConstStringType string) const {
	return Platform::CompareString(this->mString, string.CStr()) == 0;
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::operator!=(ConstStringType string) const {
	return Platform::CompareString(this->mString, string.CStr()) != 0;
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::operator>(ConstStringType string) const {
	return Platform::CompareString(this->mString, string.CStr()) > 0;
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::operator<(ConstStringType string) const {
	return Platform::CompareString(this->mString, string.CStr()) < 0;
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::operator>=(ConstStringType string) const {
	return Platform::CompareString(this->mString, string.CStr()) >= 0;
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::operator<=(ConstStringType string) const {
	return Platform::CompareString(this->mString, string.CStr()) <= 0;
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::operator==(const MutableString& string) const {
	if (mLength != string.GetLength())
		return _false;

	return Platform::CompareString(this->mString, string.CStr()) == 0;
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::operator!=(const MutableString& string) const {
	if (mLength != string.GetLength())
		return _true;

	return Platform::CompareString(this->mString, string.CStr()) != 0;
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::operator>(const MutableString& string) const {
	return Platform::CompareString(this->mString, string.CStr()) > 0;
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::operator<(const MutableString& string) const {
	return Platform::CompareString(this->mString, string.CStr()) < 0;
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::operator>=(const MutableString& string) const {
	return Platform::CompareString(this->mString, string.CStr()) >= 0;
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::operator<=(const MutableString& string) const {
	return Platform::CompareString(this->mString, string.CStr()) <= 0;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>::operator ConstStringType() const {
	return ConstStringType(mString);
}

template <typename CharType, Encoding CharEncoding>
_dword MutableString<CharType, CharEncoding>::GetLength() const {
	return mLength;
}

template <typename CharType, Encoding CharEncoding>
_dword MutableString<CharType, CharEncoding>::GetSize() const {
	return mSize;
}

template <typename CharType, Encoding CharEncoding>
_dword MutableString<CharType, CharEncoding>::SizeOfBytes() const {
	return (mLength + 1) * sizeof(CharType);
}

template <typename CharType, Encoding CharEncoding>
_void MutableString<CharType, CharEncoding>::Resize(_dword size) {
	// Free string buffer
	if (size == 0) {
		Clear(_true);
	}
	// Create string buffer
	else if (mSize == 0) {
		// Create new memory to save string
		mSize = size;
		this->mString = new CharType[mSize];

		// Set the null-terminated character
		this->mString[mLength] = 0;
	}
	// Grow the string buffer size
	else if (mSize < size) {
		CharType* oldstring = this->mString;
		_ubool olddelete = mSize > 0;

		// Create new memory to save both string
		mSize = size;
		this->mString = new CharType[mSize];

		// Copy old string back to buffer
		if (oldstring != _null && oldstring[0] != 0)
			EGE_MEM_CPY(this->mString, oldstring, mLength * sizeof(CharType));

		// Delete the old memory
		if (olddelete) {
			delete[] oldstring;
		}

		// Set the null-terminated character
		this->mString[mLength] = 0;
	}
}

template <typename CharType, Encoding CharEncoding>
_void MutableString<CharType, CharEncoding>::Clear(_ubool freememory) {
	mLength = 0;

	// Not allocated any string buffer
	if (mSize == 0) {
		TBaseClass::Clear();
	}
	// Free the string buffer
	else if (freememory) {
		if (mSize > 0) {
			delete[] this->mString;
			mSize = 0;
		}

		TBaseClass::Clear();
	}
	// Not free the string buffer
	else {
		this->mString[0] = 0;
	}
}

template <typename CharType, Encoding CharEncoding>
_void MutableString<CharType, CharEncoding>::ShrinkToFit() {
	if (mLength < mSize - 1) {
		CharType* oldstring = this->mString;
		EGE_ASSERT(oldstring != _null);

		// Check whether need to delete old string buffer
		_ubool olddelete = mSize > 0;

		// Create new memory to save both string
		mSize = mLength + 1;
		this->mString = new CharType[mSize];

		// Copy old string back to buffer
		EGE_MEM_CPY(this->mString, oldstring, mLength * sizeof(CharType));

		// Delete the old memory
		if (olddelete)
			delete[] oldstring;

		// Set the null-terminated character
		this->mString[mLength] = 0;
	}
}

template <typename CharType, Encoding CharEncoding>
_void MutableString<CharType, CharEncoding>::Insert(_dword index, CharType character) {
	EGE_ASSERT(index <= mLength);

	_dword oldlength = mLength;

	// Increase the string length
	mLength++;

	// Create more memory if necessary
	if (mSize < mLength + 1) {
		CharType* oldstring = this->mString;
		_ubool olddelete = mSize > 0;

		// Create new memory to save both string
		mSize = mLength + 1;
		this->mString = new CharType[mSize];

		// Copy old string back to buffer
		EGE_MEM_CPY(this->mString, oldstring, index * sizeof(CharType));
		EGE_MEM_CPY(this->mString + index + 1, oldstring + index, (oldlength - index) * sizeof(CharType));

		// Delete the old memory
		if (olddelete) {
			delete[] oldstring;
		}
	} else {
		for (_dword i = index; i < oldlength; i++)
			this->mString[mLength - i + index - 1] = this->mString[oldlength - i + index - 1];
	}

	// Insert character
	this->mString[index] = character;

	// Set null-terminated
	this->mString[mLength] = 0;
}

template <typename CharType, Encoding CharEncoding>
_void MutableString<CharType, CharEncoding>::Insert(_dword index, ConstStringType string) {
	EGE_ASSERT(index <= mLength);

	// Get the string length
	_dword length1 = mLength;
	_dword length2 = string.GetLength();

	// Get the total string length
	mLength = length1 + length2;

	// Create more memory if necessary
	if (mSize < mLength + 1) {
		CharType* oldstring = this->mString;
		_ubool olddelete = mSize > 0;

		// Create new memory to save both string
		mSize = mLength + 1;
		this->mString = new CharType[mSize];

		// Copy old string back to buffer
		EGE_MEM_CPY(this->mString, oldstring, index * sizeof(CharType));
		EGE_MEM_CPY(this->mString + index + length2, oldstring + index, (length1 - index) * sizeof(CharType));

		// Delete the old memory
		if (olddelete) {
			delete[] oldstring;
		}
	} else {
		for (_dword i = index; i < length1; i++)
			this->mString[mLength - i + index - 1] = this->mString[length1 - i + index - 1];
	}

	// Insert string
	EGE_MEM_CPY(this->mString + index, string.CStr(), length2 * sizeof(CharType));

	// Set null-terminated
	this->mString[mLength] = 0;
}

template <typename CharType, Encoding CharEncoding>
_void MutableString<CharType, CharEncoding>::Remove(_dword index, _dword number) {
	if (number == 0)
		return;

	if (number == -1) {
		this->mString[index] = 0;

		mLength = index;
	} else {
		EGE_ASSERT(index + number <= mLength);

		for (_dword i = index + number; i <= mLength; i++)
			this->mString[i - number] = this->mString[i];

		mLength -= number;
	}
}

template <typename CharType, Encoding CharEncoding>
_void MutableString<CharType, CharEncoding>::Remove(const DwordRange& range) {
	Remove(range.mStartIndex, range.GetLength());
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::Replace(ConstStringType srcstring, ConstStringType desstring, _ubool ignorecase) {
	_ubool replaced = _false;

	// Get the sub-string length
	_dword srcstringlength = Platform::StringLength(srcstring);
	_dword desstringlength = Platform::StringLength(desstring);

	// The start index of substring
	_dword startindex = 0;

	// Start to replace sub-string
	_StringPtr string = *this;
	while (string.IsEmpty() == _false) {
		// Search for the source sub-string
		_dword index = string.SearchL2R(srcstring, ignorecase);
		if (index == -1)
			break;

		// Replace the sub-string
		Remove(startindex + index, srcstringlength);
		Insert(startindex + index, desstring);

		// Continue to search sub-string
		startindex += index + desstringlength;
		string = SubString(startindex);

		// We have replaced it
		replaced = _true;
	}

	return replaced;
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::Replace(_dword index, CharType character) {
	if (index >= mLength)
		return _false;

	this->mString[index] = character;

	return _true;
}

template <typename CharType, Encoding CharEncoding>
_ubool MutableString<CharType, CharEncoding>::Replace(_dword index, _dword number, CharType character) {
	_dword end = index + number;
	if (end > mLength)
		return _false;

	for (_dword i = index; i < end; i++)
		this->mString[i] = character;

	return _true;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::CopyString(ConstStringType string, _dword length) {
	// Get string length
	if (length == -1)
		mLength = string.GetLength();
	else
		mLength = length;

	// It's empty string
	if (mLength == 0 && mSize > 0) {
		this->mString[0] = 0;
	}
	// Create more memory if necessary.
	else if (mSize < mLength + 1) {
		// Free the old string buffer
		if (mSize > 0) {
			delete[] this->mString;
		}

		// Create and copy the string buffer
		CreateStringBuffer(string);
	} else {
		// Copy the string buffer
		CopyStringBuffer(string);
	}

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::Lowercase() {
	if (mLength > 0)
		Platform::LowercaseString(this->mString);

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::Uppercase() {
	if (mLength > 0)
		Platform::UppercaseString(this->mString);

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::TrimLeft(CharType character) {
	Platform::TrimStringLeft(this->mString, mLength, character);

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::TrimRight(CharType character) {
	Platform::TrimStringRight(this->mString, mLength, character);

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::TrimBoth(CharType character) {
	Platform::TrimStringBoth(this->mString, mLength, character);

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::TrimLeft(ConstStringType charset) {
	Platform::TrimStringLeft(this->mString, mLength, charset.CStr());

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::TrimRight(ConstStringType charset) {
	Platform::TrimStringRight(this->mString, mLength, charset.CStr());

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::TrimBoth(ConstStringType charset) {
	Platform::TrimStringBoth(this->mString, mLength, charset.CStr());

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding> MutableString<CharType, CharEncoding>::SubString(_dword index) const {
	return SubString(index, mLength - index);
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding> MutableString<CharType, CharEncoding>::SubString(_dword start, _dword length) const {
	if (start >= mLength)
		return MutableString();

	if (start + length > mLength)
		length = -1;

	return MutableString(this->mString + start, length);
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding> MutableString<CharType, CharEncoding>::LeftSubString(CharType delimiter) const {
	_dword index = this->SearchL2R(delimiter);
	if (index == -1)
		return *this;

	return MutableString(this->mString, index);
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding> MutableString<CharType, CharEncoding>::LeftSubString(ConstStringType delimiter) const {
	_dword index = this->SearchL2R(delimiter);
	if (index == -1)
		return *this;

	return MutableString(this->mString, index);
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding> MutableString<CharType, CharEncoding>::RightSubString(CharType delimiter) const {
	_dword index = TBaseClass::SearchR2L(delimiter);
	if (index == -1)
		return *this;

	return MutableString(this->mString + index + 1, mLength - index - 1);
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding> MutableString<CharType, CharEncoding>::RightSubString(ConstStringType delimiter) const {
	_dword index = TBaseClass::SearchR2L(delimiter);
	if (index == -1)
		return *this;

	return MutableString(this->mString + index + delimiter.GetLength(), mLength - index - delimiter.GetLength());
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::FromValue(_int value, _dword radix) {
	CharType string[1024];
	Platform::ConvertLongToString(value, radix, string, 1024);

	CopyString(string);

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::FromValue(_dword value, _dword radix) {
	CharType string[1024];
	Platform::ConvertDwordToString(value, radix, string, 1024);

	CopyString(string);

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::FromValue(_large value, _dword radix) {
	CharType string[1024];
	Platform::ConvertLargeToString(value, radix, string, 1024);

	CopyString(string);

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::FromValue(_qword value, _dword radix) {
	CharType string[1024];
	Platform::ConvertQwordToString(value, radix, string, 1024);

	CopyString(string);

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::FromValue(_float value, _dword precision) {
	CharType string[1024];
	Platform::ConvertFloatToString(value, string, 1024, precision);

	CopyString(string);

	return *this;
}

template <typename CharType, Encoding CharEncoding>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::FromValue(_double value, _dword precision) {
	CharType string[1024];
	Platform::ConvertDoubleToString(value, string, 1024, precision);

	CopyString(string);

	return *this;
}

template <typename CharType, Encoding CharEncoding>
template <class FromStringType>
MutableString<CharType, CharEncoding>& MutableString<CharType, CharEncoding>::FromString(const FromStringType& string) {
	return FromString(string.GetEncodeType(), string.CStr());
}

template <>
template <typename FromCharType>
MutableString<_chara, Encoding::Ansi>& MutableString<_chara, Encoding::Ansi>::FromString(Encoding encode, const FromCharType* string) {
	Clear();

	// Skip for empty string
	if (string == _null || string[0] == 0)
		return *this;

	// Start to convert string
	switch (encode) {
		case Encoding::Ansi: {
			CopyString((const _chara*)string, -1);
		} break;

		case Encoding::Utf8: {
			// Get the UNICODE string ansi_string_size in bytes
			_dword utf16_string_size = Platform::Utf8ToUtf16(_null, 0, (const _chara*)string, -1);
			if (utf16_string_size > 0) {
				// Convert to number of characters of UNICODE
				utf16_string_size /= sizeof(_charw);

				// Get the UTF-16 string size in 2 bytes ( contains '\0' )
				_dword size = utf16_string_size + 1;

				// Convert UTF-8 string to UNICODE
				MemArrayPtr<_charw> string_unicode(size);
				Platform::Utf8ToUtf16(string_unicode, size, (const _chara*)string, utf16_string_size);

				// Import from UNICODE string
				return FromString(Encoding::Utf16, (const _charw*)string_unicode);
			}
		} break;

		case Encoding::Utf16: {
			// Get the ANSI string size in bytes
			_dword ansi_string_size = Platform::Utf16ToAnsi(_null, 0, (const _charw*)string, -1);
			if (ansi_string_size > 0) {
				mLength = ansi_string_size;

				// Get the ANSI string size in 1 byte ( contains '\0' )
				_dword size = mLength + 1;

				// Grow the ANSI string buffer if needed
				if (mSize < size)
					Resize(size);

				// Convert UNICODE string to ANSI
				Platform::Utf16ToAnsi((_chara*)this->mString, size, (const _charw*)string, ansi_string_size);
			}
		} break;

		default: {
		} break;
	}

	return *this;
}

template <>
template <typename FromCharType>
MutableString<_chara, Encoding::Utf8>& MutableString<_chara, Encoding::Utf8>::FromString(Encoding encode, const FromCharType* string) {
	Clear();

	// Skip for empty string
	if (string == _null || string[0] == 0)
		return *this;

	// Start to convert string
	switch (encode) {
		case Encoding::Ansi: {
			// Get the UNICODE string size in bytes
			_dword utf16_string_size = Platform::AnsiToUtf16(_null, 0, (const _chara*)string);
			if (utf16_string_size > 0) {
				// Convert to number of characters of UNICODE
				utf16_string_size /= sizeof(_charw);

				// Get the UTF-16 string size in 2 bytes ( contains '\0' )
				_dword size = utf16_string_size + 1;

				// Convert ANSI string to UNICODE
				MemArrayPtr<_charw> string_unicode(size);
				Platform::AnsiToUtf16(string_unicode, size, (const _chara*)string, utf16_string_size);

				// Import from UNICODE string
				return FromString(Encoding::Utf16, (const _charw*)string_unicode);
			}
		} break;

		case Encoding::Utf8: {
			CopyString((const _chara*)string, -1);
		} break;

		case Encoding::Utf16: {
			// Get the UTF-8 string size in bytes
			_dword utf8_string_size = Platform::Utf16ToUtf8(_null, 0, (const _charw*)string, -1);
			if (utf8_string_size > 0) {
				mLength = utf8_string_size;

				// Get the UTF-16 string size in 1 byte ( contains '\0' )
				_dword size = mLength + 1;

				// Grow the UTF-8 string buffer if needed
				if (mSize < size)
					Resize(size);

				// Convert UNICODE string to UTF-8
				Platform::Utf16ToUtf8((_chara*)this->mString, size, (const _charw*)string, utf8_string_size);
			}
		} break;

		default: {
		} break;
	}

	return *this;
}

template <>
template <typename FromCharType>
MutableString<_charw, Encoding::Utf16>& MutableString<_charw, Encoding::Utf16>::FromString(Encoding encode, const FromCharType* string) {
	Clear();

	// Skip for empty string
	if (string == _null || string[0] == 0)
		return *this;

	// Start to convert string
	switch (encode) {
		case Encoding::Ansi: {
			// Get the UNICODE string size in bytes
			_dword utf16_string_size = Platform::AnsiToUtf16(_null, 0, (const _chara*)string, -1);
			if (utf16_string_size > 0) {
				// Convert to number of characters of UNICODE
				mLength = utf16_string_size / sizeof(_charw);

				// Get the UTF-16 string size in 2 bytes ( contains '\0' )
				_dword size = mLength + 1;

				// Grow the UNICODE string buffer if needed
				if (mSize < size)
					Resize(size);

				// Convert ANSI string to UNICODE
				Platform::AnsiToUtf16((_charw*)this->mString, size, (const _chara*)string, utf16_string_size);
			}
		} break;

		case Encoding::Utf8: {
			// Get the UNICODE string size in bytes
			_dword utf16_string_size = Platform::Utf8ToUtf16(_null, 0, (const _chara*)string, -1);
			if (utf16_string_size > 0) {
				// Convert to number of characters of UNICODE
				mLength = (utf16_string_size / sizeof(_charw));

				// Get the UTF-16 string size in 2 bytes ( contains '\0' )
				_dword size = mLength + 1;

				// Grow the UNICODE string buffer if needed
				if (mSize < size)
					Resize(size);

				// Convert UTF-8 string to UNICODE
				Platform::Utf8ToUtf16((_charw*)this->mString, size, (const _chara*)string, utf16_string_size);
			}
		} break;

		case Encoding::Utf16: {
			CopyString((const _charw*)string, -1);
		} break;

		default: {
		} break;
	}

	return *this;
}

template <typename CharType, Encoding CharEncoding>
_void MutableString<CharType, CharEncoding>::FormatStringByArguments(const CharType* format, ...) {
	BEGIN_VA_LIST(args, format);
	FormatStringByVAList(format, args);
	END_VA_LIST(args);
}

template <typename CharType, Encoding CharEncoding>
_void MutableString<CharType, CharEncoding>::FormatStringByVAList(const CharType* format, _va_list arguments) {
	mLength = Platform::GetFormatStringLength(format, arguments);

	// Create more memory if necessary
	if (mSize < mLength + 1) {
		CharType* oldstring = this->mString;
		_ubool olddelete = mSize > 0;

		// Create new memory to save both string
		mSize = mLength + 1;
		this->mString = new CharType[mSize];

		// Delete the old memory
		if (olddelete) {
			delete[] oldstring;
		}
	}

	// Format string
	Platform::FormatStringByVAList(this->mString, mSize, format, arguments);

	// Set null-terminated
	this->mString[mLength] = 0;
}

} // namespace EGE
