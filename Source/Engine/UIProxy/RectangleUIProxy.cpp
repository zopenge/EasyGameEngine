//! @file     RectangleUIProxy.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// RectangleUIProxy Implementation
//----------------------------------------------------------------------------

RectangleUIProxy::RectangleUIProxy( )
{
	mOpStatus	= _OP_STATUS_NONE;

	mBorderSize	= 0.0f;

	mRegion		= RectF::cNull;
	mMinSize	= Vector2::cOrigin;
	mMaxSize	= Vector2::cMaxVector;
}

RectangleUIProxy::~RectangleUIProxy( )
{

}

_void RectangleUIProxy::HandleMessage( const MessageBase& message )
{

}

_void RectangleUIProxy::HandleEvent( const EventBase& event )
{

}

_void RectangleUIProxy::SetRect( const RectF& rect )
{
	mRegion = rect;
}

const RectF& RectangleUIProxy::GetRect( ) const
{
	return mRegion;
}

_void RectangleUIProxy::SetBorderSize( _float size )
{
	mBorderSize = size;
}

_float RectangleUIProxy::GetBorderSize( ) const
{
	return mBorderSize;
}

_void RectangleUIProxy::SetMinSize( const Vector2& size )
{
	mMinSize = size;
}

const Vector2& RectangleUIProxy::GetMinSize( ) const
{
	return mMinSize;
}

_void RectangleUIProxy::SetMaxSize( const Vector2& size )
{
	mMaxSize = size;
}

const Vector2& RectangleUIProxy::GetMaxSize( ) const
{
	return mMaxSize;
}

IRectangleUIProxy::_OP_STATUS RectangleUIProxy::GetOpStatus( ) const
{
	return mOpStatus;
}
