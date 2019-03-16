//! @file     MeasurableObject.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// MeasurableObject Implementation
//----------------------------------------------------------------------------

MeasurableObject::MeasurableObject( const Vector2& size )
{
	mLineNumber	= 0;
	mSize		= size;
	mPosition	= Vector2::cOrigin;
}

MeasurableObject::~MeasurableObject( )
{
}

_void MeasurableObject::SetLineNumber( _dword number )
{
	mLineNumber = number;
}

_dword MeasurableObject::GetLineNumber( ) const
{
	return mLineNumber;
}

RectF MeasurableObject::GetRegion( ) const
{
	return RectF( ).InitWithSize( 0.0f, 0.0f, mSize.x, mSize.y );
}

_float MeasurableObject::GetLeft( ) const
{
	return 0.0f;
}

_float MeasurableObject::GetBottom( ) const
{
	return 0.0f;
}

_float MeasurableObject::GetBaseLineHeight( ) const
{
	return 0;
}

Vector2 MeasurableObject::GetPosition( ) const
{
	return mPosition;
}

_void MeasurableObject::SetPosition( const Vector2& pos )
{
	mPosition = pos;
}

_float MeasurableObject::GetSpace( ) const
{
	return 0.0f;
}

_ubool MeasurableObject::IsWordSeparatorTag( ) const
{
	return _false;
}

_ubool MeasurableObject::IsNewLineTag( ) const
{
	return _false;
}