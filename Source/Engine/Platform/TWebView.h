//! @file     TWebView.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TWebView
//----------------------------------------------------------------------------

template< typename Type >
class TWebView : public TShowableObject< TObject< Type > >
{
protected:
	PointI				mPos;
	PointI				mSize;

	WString				mURLAddress;

	IWebViewNotifierRef	mNotifier;

protected:
	TWebView( );
	virtual ~TWebView( );

// IWebView Interface
public:
	virtual _void				SetNotifier( IWebViewNotifier* notifier ) override;
	virtual IWebViewNotifierRef	GetNotifier( ) override;

	virtual _void				SetRegion( const RectI& region ) override;
	virtual RectI				GetRegion( ) const override;

	virtual const PointI&		GetPosition( ) const override;
	virtual const PointI&		GetSize( ) const override;

	virtual _ubool				OpenURL( WStringPtr url_address ) override;
    virtual WStringPtr          GetURLAddress( ) const override;
};

//----------------------------------------------------------------------------
// TWebView Implementation
//----------------------------------------------------------------------------

template< typename Type >
TWebView< Type >::TWebView( )
{
	mPos		= PointI::cZeroPoint;
	mSize		= PointI::cZeroPoint;

	mNotifier	= &NullEngine::GetInstance( ).GetWebViewNotifier( );
}

template< typename Type >
TWebView< Type >::~TWebView( )
{

}

template< typename Type >
_void TWebView< Type >::SetNotifier( IWebViewNotifier* notifier )
{
	if ( notifier == _null )
		mNotifier = &NullEngine::GetInstance( ).GetWebViewNotifier( );
	else
		mNotifier = notifier;
}

template< typename Type >
IWebViewNotifierRef TWebView< Type >::GetNotifier( )
{
	return mNotifier;
}

template< typename Type >
_void TWebView< Type >::SetRegion( const RectI& region )
{
	mPos	= region.GetLeftTop( );
	mSize	= region.GetSize( );
}

template< typename Type >
RectI TWebView< Type >::GetRegion( ) const
{
	return RectI( ).InitWithSize( mPos.x, mPos.y, mSize.x, mSize.y );
}

template< typename Type >
const PointI& TWebView< Type >::GetPosition( ) const
{
	return mPos;
}

template< typename Type >
const PointI& TWebView< Type >::GetSize( ) const
{
	return mSize;
}

template< typename Type >
_ubool TWebView< Type >::OpenURL( WStringPtr url_address )
{
	if ( url_address.IsEmpty( ) )
		return _false;

	mURLAddress = url_address;

	return _true;
}
    
template< typename Type >
WStringPtr TWebView< Type >::GetURLAddress( ) const
{
    return mURLAddress;
}

}