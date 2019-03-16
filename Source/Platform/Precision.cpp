//! @file     Precision.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Precision Implementation
//----------------------------------------------------------------------------

Precision::Precision( )
{
	mIntPrecision	= 5;
	mFloatPrecision	= 2;
}

Precision::Precision( _word int_precision, _word float_precision )
{
	mIntPrecision	= int_precision;
	mFloatPrecision	= float_precision;
}

_void Precision::Clear( )
{
	mIntPrecision	= 0xFFFF;
	mFloatPrecision	= 0xFFFF;
}

_void Precision::EnableIntergerPrecision( _ubool enable, _word precision )
{
	if ( enable )
		mIntPrecision = precision;
	else
		mIntPrecision = 0xFFFF;
}

_void Precision::EnableFloatPrecision( _ubool enable, _word precision )
{
	if ( enable )
		mFloatPrecision = precision;
	else
		mFloatPrecision = 0xFFFF;
}

_ubool Precision::IsEnableIntergerPrecision( ) const
{
	return mIntPrecision != 0xFFFF;
}

_ubool Precision::IsEnableFloatPrecision( ) const
{
	return mFloatPrecision != 0xFFFF;
}

WString Precision::BuildIntergerValueString( _int value ) const
{
	WString formatter( L"%%" );
	if ( mIntPrecision != 0xFFFF )
	{
		formatter += L"0";
		formatter += WString( ).FromValue( mIntPrecision );
	}
	formatter += L"d";

	_charw string_buffer[1024];
	return WString( Platform::FormatStringBuffer( string_buffer, 1024, formatter.Str( ), value ) );
}

WString Precision::BuildFloatValueString( _float value ) const
{
	WString formatter( L"%%" );
	if ( mIntPrecision != 0xFFFF )
	{
		formatter += L"0";
		formatter += WString( ).FromValue( mIntPrecision );
	}

	formatter += L".";
	if ( mFloatPrecision != 0xFFFF )
	{
		formatter += WString( ).FromValue( mFloatPrecision );
	}	
	formatter += L"f";

	_charw string_buffer[1024];
	return WString( Platform::FormatStringBuffer( string_buffer, 1024, formatter.Str( ), value ) );
}
