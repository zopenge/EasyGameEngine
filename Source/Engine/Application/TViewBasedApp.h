//! @file     TViewBasedApp.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{


//----------------------------------------------------------------------------
// TViewBasedApp
//----------------------------------------------------------------------------

template< typename Type >
class TViewBasedApp : public TApplication< Type >
{
protected:
	typedef TApplication< Type > TBaseClass;

protected:
	//!	The last tickcount
	_dword				mLastTickcount;

	//!	True indicates it's lock size
	_ubool				mIsLockSize;
	//!	The locked size
	PointU				mLockedSize;

	//!	The options
	FlagsObject			mAppOptions;

	//!	The key down deferred processor
	DeferredProcessor	mKeyDownDeferredProcessor;

protected:
	TViewBasedApp( );
	virtual ~TViewBasedApp( );

// IApplication Interface
public:
	virtual _APPLICATION_TYPE			GetApplicationType( ) const override;

// IViewBasedApp Interface
public:
	virtual _void						LockSize( ) override;
	virtual _void						UnlockSize( ) override;

	virtual RectU						GetClientRectU( ) const override;
    virtual RectF						GetClientRectF( ) const override;
	virtual PointU						GetClientSize( ) const override;

	virtual _void						EnableOptions( _dword options, _ubool enable ) override;
	virtual _ubool						IsEnableOptions( _dword options ) const override;

	virtual DeferredProcessor&			GetKeyDownDeferredProcessor( ) override;
	virtual const DeferredProcessor&	GetKeyDownDeferredProcessor( ) const override;
};

//----------------------------------------------------------------------------
// TViewBasedApp Implementation
//----------------------------------------------------------------------------

template< typename Type >
TViewBasedApp< Type >::TViewBasedApp( )
{
	mLastTickcount	= 0;

	mIsLockSize		= _false;
	mLockedSize		= PointU::cZeroPoint;
}

template< typename Type >
TViewBasedApp< Type >::~TViewBasedApp( )
{
}

template< typename Type >
_APPLICATION_TYPE TViewBasedApp< Type >::GetApplicationType( ) const
{
	return _APPLICATION_TYPE_VIEWBASED;
}

template< typename Type >
_void TViewBasedApp< Type >::LockSize( )
{
	mIsLockSize = _true;
	mLockedSize	= GetClientSize( );
}

template< typename Type >
_void TViewBasedApp< Type >::UnlockSize( )
{
	mIsLockSize = _false;
}

template< typename Type >
RectU TViewBasedApp< Type >::GetClientRectU( ) const
{
    return RectU::cNull;
}
    
template< typename Type >
RectF TViewBasedApp< Type >::GetClientRectF( ) const
{
    return ConvertRectU2RectF( GetClientRectU( ) );
}

template< typename Type >
PointU TViewBasedApp< Type >::GetClientSize( ) const
{
	RectU rect = this->GetClientRectU( );

	return PointU( rect.GetWidth( ), rect.GetHeight( ) );
}

template< typename Type >
_void TViewBasedApp< Type >::EnableOptions( _dword options, _ubool enable )
{
	mAppOptions.EnableFlags( options, enable );
}

template< typename Type >
_ubool TViewBasedApp< Type >::IsEnableOptions( _dword options ) const
{
	return mAppOptions.HasFlags( options, _true );
}

template< typename Type >
DeferredProcessor& TViewBasedApp< Type >::GetKeyDownDeferredProcessor( )
{
	return mKeyDownDeferredProcessor;
}

template< typename Type >
const DeferredProcessor& TViewBasedApp< Type >::GetKeyDownDeferredProcessor( ) const
{
	return mKeyDownDeferredProcessor;
}

}