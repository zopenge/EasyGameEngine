//! @file     UID.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// UID128
//----------------------------------------------------------------------------

struct UID128
{
	_dword	mData1;
	_word	mData2;
	_word	mData3;
	_byte	mData4[8];

	//! Constructor.
	UID128( );
	//! Constructor (xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx).
	UID128( const _chara* uidstring );
	UID128( const _charw* uidstring );

	//! Comparison Operators.
	_ubool operator == ( const UID128& uid ) const;
	_ubool operator != ( const UID128& uid ) const;
	_ubool operator > ( const UID128& uid ) const;
	_ubool operator >= ( const UID128& uid ) const;
	_ubool operator < ( const UID128& uid ) const;
	_ubool operator <= ( const UID128& uid ) const;

	//! Convert to string.
	AStringR ToStringA( _ubool to_upper = _false ) const;
	UStringR ToStringU( _ubool to_upper = _false ) const;
	WStringR ToStringW( _ubool to_upper = _false ) const;

	//! Convert from string.
	UID128& FromString( AStringPtr string );
	UID128& FromString( UStringPtr string );
	UID128& FromString( WStringPtr string );

	//! Get the negation UUID.
	UID128 Negation( ) const;
};

//----------------------------------------------------------------------------
// UID
//----------------------------------------------------------------------------

class UID
{
public:
	//! The standard UID128 string length
	static const _dword	cStandardUID128StringLength;
	//! The null UID 128
	static const UID128	cNullUID128;

public:
	//! Checks whether the given string matches the UID format (ANSI).
	//! @param		uid			The UID string.
	//! @return		True if the given string is a UID, false otherwise.
	static _ubool IsUUIDString( const _chara* uidstring );
	//! Checks whether the given string matches the UID format (UNICODE).
	//! @param		uid			The UID string.
	//! @return		True if the given string is a UID, false otherwise.
	static _ubool IsUUIDString( const _charw* uidstring );

	//! Generates a new UID.
	//! @param		none.
	//! @return		The new UID.
	static UID128 CreateUUID( );
	//! Generates a new UID string (ANSI).
	//! @param		uidstring	The UID string buffer.
	//! @param		length		The UID string buffer length.
	//! @return		The UID string buffer pointer.
	static _chara* CreateUUIDString( _chara* uidstring, _dword length );
	//! Generates a new UID string (UNICODE).
	//! @param		uidstring	The UID string buffer.
	//! @param		length		The UID string buffer length.
	//! @return		The UID string buffer pointer.
	static _charw* CreateUUIDString( _charw* uidstring, _dword length );

	//! Translate a uid string to a UID (ANSI).
	//! @param		uidstring	The UID string buffer.
	//! @return		The UID value.
	static UID128 String2UUID( const _chara* uidstring );
	//! Translate a uid string to a UID (UNICODE).
	//! @param		uidstring	The UID string buffer.
	//! @return		The UID value.
	static UID128 String2UUID( const _charw* uidstring );

	//! Translate a UID to a uid string (ANSI).
	//! @param		uid			The UID value.
	//! @param		uidstring	The UID string buffer.
	//! @param		length		The UID string buffer length.
	//! @return		The UID string buffer pointer.
	static _chara* UUID2String( const UID128& uid, _chara* uidstring, _dword length );
	//! Translate a UID to a uid string (UNICODE).
	//! @param		uid			The UID value.
	//! @param		uidstring	The UID string buffer.
	//! @param		length		The UID string buffer length.
	//! @return		The UID string buffer pointer.
	static _charw* UUID2String( const UID128& uid, _charw* uidstring, _dword length );

	//! Compare two UID's lexically.
	//! @param		uuid1		The UID value 1.
	//! @param		uuid2		The UID value 2.
	//! @return		-1			The uuid1 is lexically before uuid2. \n
	//! 			 0			The uuid1 is equal to uuid2. \n
	//! 			 1			The uuid1 is lexically after uuid2.
	static _int CompareUUID( const UID128& uuid1, const UID128& uuid2 );
};

}