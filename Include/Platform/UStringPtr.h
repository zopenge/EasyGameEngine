//! @file     UStringPtr.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

class AString;

//----------------------------------------------------------------------------
// UStringPtr
//----------------------------------------------------------------------------

//! This class represents a const null-terminated UTF-8 string.
class UStringPtr : public StringPtr< const _chara >
{
public:
	//! Constructor, create a string points to "".
	//! @param		none
	inline UStringPtr( );
	//! Constructor, create a string points to the specified string.
	//! @param		string		The string pointer.
	inline UStringPtr( const _chara* string );
	//! Destructor.
	//! @param		none.
	inline ~UStringPtr( );

public:
	//! Convert an UTF-8 string to ANSI.
	//! @param		string		The ANSI string.
	//! @return		True indicates success false indicates failure.
	_bool ToAnsiString( AString& string ) const;
};

//----------------------------------------------------------------------------
// UStringPtr Implementation
//----------------------------------------------------------------------------

UStringPtr::UStringPtr( )
{
}

UStringPtr::UStringPtr( const _chara* string ) : StringPtr( string )
{
}

UStringPtr::~UStringPtr( )
{

}

}