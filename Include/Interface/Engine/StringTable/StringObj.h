//! @file     StringObj.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TStringObj
//----------------------------------------------------------------------------

template< typename CharType, _ENCODING _ENCODING_TYPE >
class TStringObj : public ConstString< CharType, _ENCODING_TYPE >
{
protected:
	//!	The unique ID
	_dword	mID;

public:
	TStringObj( const CharType* string );
	TStringObj( ConstString< CharType, _ENCODING_TYPE > string );
	TStringObj( const MutableStringR< CharType, _ENCODING_TYPE >& string );
	TStringObj( )
	{
		static CharType sNull = 0;

		mID		= -1;
		mString	= &sNull;
	}
	TStringObj( _dword id, const CharType* string )
	{
		EGE_ASSERT( string != _null );

		mID		= id;
		mString	= (CharType*)string;
	}
	TStringObj( const TStringObj& obj )
	{
		mID		= obj.mID;
		mString = obj.mString;
	}
	~TStringObj( )
	{
	}

public:
	//!	Compare operations.
	_ubool operator == ( const TStringObj& refstring ) const
		{ return mID == refstring.mID; }
	_ubool operator != ( const TStringObj& refstring ) const
		{ return mID != refstring.mID; }
	_ubool operator > ( const TStringObj& refstring ) const
		{ return mID > refstring.mID; }
	_ubool operator >= ( const TStringObj& refstring ) const
		{ return mID >= refstring.mID; }
	_ubool operator < ( const TStringObj& refstring ) const
		{ return mID < refstring.mID; }
	_ubool operator <= ( const TStringObj& refstring ) const
		{ return mID <= refstring.mID; }

	//!	Compare operations.
	_ubool operator == ( const CharType* string ) const
		{ return Platform::CompareString( mString, string ) == 0; }
	_ubool operator != ( const CharType* string ) const
		{ return Platform::CompareString( mString, string ) != 0; }
	_ubool operator > ( const CharType* string ) const
		{ return Platform::CompareString( mString, string ) > 0; }
	_ubool operator >= ( const CharType* string ) const
		{ return Platform::CompareString( mString, string ) >= 0; }
	_ubool operator < ( const CharType* string ) const
		{ return Platform::CompareString( mString, string ) < 0; }
	_ubool operator <= ( const CharType* string ) const
		{ return Platform::CompareString( mString, string ) <= 0; }

public:
	//!	Access the unique ID.
	EGE_GET_ACCESSOR_CONST( _dword, ID )

public:
	//!	Convert to string.
	operator ConstString< CharType, _ENCODING_TYPE >( ) const
		{ return mString; }
	operator MutableString< CharType, _ENCODING_TYPE >( ) const
		{ return mString; }

	//!	Assign.
	TStringObj& operator = ( const CharType* string );
	TStringObj& operator = ( ConstString< CharType, _ENCODING_TYPE > string );
	TStringObj& operator = ( const MutableStringR< CharType, _ENCODING_TYPE >& string );
	TStringObj& operator = ( const TStringObj& obj )
	{
		mID		= obj.mID;
		mString	= obj.mString;

		return *this;
	}

	//!	Get the encoding type.
	_ENCODING GetEncodeType( ) const
		{ return _ENCODING_TYPE; }
	//!	Get the string.
	const CharType* Str( ) const
		{ return mString; }

	//! Compare two strings
	_ubool IsEqual( const CharType* string, _ubool ignorecase = _false ) const
		{ return Platform::CompareString( mString, string, ignorecase ) == 0; }
	//! Check whether it's empty.
	_ubool IsEmpty( ) const
		{ return mString[0] == 0; }
};

//----------------------------------------------------------------------------
// (A/U/W)StringObj
//----------------------------------------------------------------------------

typedef TStringObj< _chara, _ENCODING_ANSI >	AStringObj;
typedef TStringObj< _chara, _ENCODING_UTF8 >	UStringObj;
typedef TStringObj< _charw, _ENCODING_UTF16 >	WStringObj;

}