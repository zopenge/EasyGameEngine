//! @file     RectangleUIProxy.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RectangleUIProxy
//----------------------------------------------------------------------------

class RectangleUIProxy : public TObject< IRectangleUIProxy >
{
private:
	_OP_STATUS	mOpStatus;

	_float		mBorderSize;

	RectF		mRegion;
	Vector2		mMinSize;
	Vector2		mMaxSize;

public:
	RectangleUIProxy( );
	virtual ~RectangleUIProxy( );

// IUIProxy Interface
public:
	virtual _void			HandleMessage( const MessageBase& message ) override;
	virtual _void			HandleEvent( const EventBase& event ) override;

// IRectangleUIProxy Interface
public:
	virtual _void			SetRect( const RectF& rect ) override;
	virtual const RectF&	GetRect( ) const override;

	virtual _void			SetBorderSize( _float size ) override;
	virtual _float			GetBorderSize( ) const override;

	virtual _void			SetMinSize( const Vector2& size ) override;
	virtual const Vector2&	GetMinSize( ) const override;
	virtual _void			SetMaxSize( const Vector2& size ) override;
	virtual const Vector2&	GetMaxSize( ) const override;

	virtual _OP_STATUS		GetOpStatus( ) const override;
};

}