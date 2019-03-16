//! @file     TApplication.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TApplication
//----------------------------------------------------------------------------

template< typename Type >
class TApplication : public INTERFACE_OBSERVER_IMPL( Type )
{
protected:
	//!	The application status
	enum _STATUS
	{
		//!	True Indicates the application will quit soon
		_STATUS_IS_QUIT				= 1 << 0,
		//!	True indicates the application will restart soon
		_STATUS_IS_RESTART			= 1 << 1,
		//!	True indicates the application is always on top
		_STATUS_IS_ALWAYS_ON_TOP	= 1 << 2,
	};

	//!	The application status, @see _STATUS
	FlagsObject	mStatus;
	//!	The sleep time in milliseconds
	_dword		mSleepTime;
	//!	The max limited elapsed time
	_dword		mMaxLimitedElapsedTime;
	//!	The total elapsed time in milliseconds
	_dword		mTotalElapsedTime;

	//!	The title name
	WString		mTitle;

protected:
	TApplication( );
	virtual ~TApplication( );

// IObject Interface
public:
	virtual _void		Tick( _dword limited_elapse, _dword elapse ) override;

// IApplication Interface
public:
	virtual _void		SetMaxLimitedElapsedTime( _dword elapse ) override;
	virtual _dword		GetMaxLimitedElapsedTime( ) const override;

	virtual _dword		GetTotalElapsedTime( ) const;

	virtual _ubool		Verify( AStringPtr key, IStreamReader* stream_reader ) override;

	virtual _void		Quit( ) override;
	virtual _ubool		IsQuit( ) const override;

	virtual _void		Restart( ) override;
	virtual _ubool		IsRestart( ) const override;

	virtual _void		SetSleepTime( _dword time ) override;
	virtual _dword		GetSleepTime( ) const override;

	virtual _void		SetTitle( WStringPtr title ) override;
	virtual WStringPtr	GetTitle( ) const override;

	virtual _void		EnableAlwaysOnTop( _ubool enable ) override;
	virtual _ubool		IsEnableAlwaysOnTop( ) const override;

	virtual _ubool		OnBeforeLoadModules( ) override;
	virtual _ubool		OnAfterLoadModules( ) override;
};

//----------------------------------------------------------------------------
// TApplication Implementation
//----------------------------------------------------------------------------

template< typename Type >
TApplication< Type >::TApplication( )
{
	mSleepTime				= 10;
	mMaxLimitedElapsedTime	= 20;
	mTotalElapsedTime		= 0;
}

template< typename Type >
TApplication< Type >::~TApplication( )
{
}

template< typename Type >
_void TApplication< Type >::Tick( _dword limited_elapse, _dword elapse )
{
	mTotalElapsedTime += elapse;
}

template< typename Type >
_void TApplication< Type >::SetMaxLimitedElapsedTime( _dword elapse )
{
	mMaxLimitedElapsedTime = elapse;
}

template< typename Type >
_dword TApplication< Type >::GetMaxLimitedElapsedTime( ) const
{
	return mMaxLimitedElapsedTime;
}

template< typename Type >
_dword TApplication< Type >::GetTotalElapsedTime( ) const
{
	return mTotalElapsedTime;
}

template< typename Type >
_ubool TApplication< Type >::Verify( AStringPtr key, IStreamReader* stream_reader )
{
	return _true;
}

template< typename Type >
_void TApplication< Type >::Quit( )
{
	mStatus.CombineFlags( _STATUS_IS_QUIT );
}

template< typename Type >
_ubool TApplication< Type >::IsQuit( ) const
{
	return mStatus.HasFlags( _STATUS_IS_QUIT );
}

template< typename Type >
_void TApplication< Type >::Restart( )
{
	mStatus.CombineFlags( _STATUS_IS_RESTART );
}

template< typename Type >
_ubool TApplication< Type >::IsRestart( ) const
{
	return mStatus.HasFlags( _STATUS_IS_RESTART );
}

template< typename Type >
_void TApplication< Type >::SetSleepTime( _dword time )
{
	mSleepTime = time;
}

template< typename Type >
_dword TApplication< Type >::GetSleepTime( ) const
{
	return mSleepTime;
}

template< typename Type >
_void TApplication< Type >::SetTitle( WStringPtr title )
{
	mTitle = title;
}

template< typename Type >
WStringPtr TApplication< Type >::GetTitle( ) const
{
	return mTitle;
}

template< typename Type >
_void TApplication< Type >::EnableAlwaysOnTop( _ubool enable )
{
	mStatus.EnableFlags( _STATUS_IS_ALWAYS_ON_TOP, enable );
}

template< typename Type >
_ubool TApplication< Type >::IsEnableAlwaysOnTop( ) const
{
	return mStatus.HasFlags( _STATUS_IS_ALWAYS_ON_TOP );
}

template< typename Type >
_ubool TApplication< Type >::OnBeforeLoadModules( )
{
	return _true;
}

template< typename Type >
_ubool TApplication< Type >::OnAfterLoadModules( )
{
	return _true;
}

}