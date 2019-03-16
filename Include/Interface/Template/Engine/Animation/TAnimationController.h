//! @file     TAnimationController.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TAnimationController
//----------------------------------------------------------------------------

template< typename Type >
class TAnimationController : public Type
{
protected:
	//!	The last tickcount in milliseconds
	_dword					mLastTickcount;
	//!	The duration in milliseconds
	_dword					mDuration;

	//!	The FPS
	_float					mFPS;
	//!	The interval in milliseconds
	_dword					mInterval;

	//!	The animation status/direction/mode
	_ANIMATION_STATUS		mAniStatus;
	_ANIMATION_DIRECTION	mAniDirection;
	_ANIMATION_MODE			mAniMode;

protected:
	//!	Update last tickcount.
	_void UpdateLastTickcount( _dword& elapse );
	//!	Update direction.
	_void UpdateDirection( _dword& elapse );

	//!	Copy from player.
	_void CopyFrom( const TAnimationController* src_object );

protected:
	//!	When played.
	virtual _void OnPlayed( ) PURE;
	//!	When stopped.
	virtual _void OnStopped( ) PURE;
	//!	When paused.
	virtual _void OnPaused( ) PURE;
	//!	When resumed.
	virtual _void OnResumed( ) PURE;
	//! When reset
	virtual _void OnReset( ) PURE;
	//!	When update.
	virtual _void OnTick( _time_t tick, _dword elapse ) PURE;

protected:
	TAnimationController( );
	virtual ~TAnimationController( );

// IObject Interface
public:
	virtual _void					Tick( _dword limited_elapse, _dword elapse ) override;

// IAnimationController Interface
public:
	virtual _dword					GetCurrentFrameTime( ) const override;
	virtual _void					SetCurrentFrameTime( _dword time ) override;

	virtual _dword					GetCurrentFrameNumber( ) const override;
	virtual _void					SetCurrentFrameNumber( _dword number ) override;

// IAnimationTrack Interface
public:
	virtual _ANIMATION_STATUS		GetAniStatus( ) const override;
	virtual _dword					GetLastTickcount( ) const override;

	virtual _ANIMATION_DIRECTION	GetAniDirection( ) const override;
	virtual _void					SetAniDirection( _ANIMATION_DIRECTION direction ) override;

	virtual _ANIMATION_MODE			GetAniMode( ) const override;
	virtual _void					SetAniMode( _ANIMATION_MODE mode ) override;

	virtual _dword					GetDuration( ) const override;
	virtual _void					SetDuration( _dword duration ) override;
	virtual _dword					GetTotalFramesNumber( ) const override;
	virtual _void					SetTotalFramesNumber( _dword frames_number ) override;

	virtual _float					GetFPS( ) const override;
	virtual _void					SetFPS( _float fps ) override;

	virtual _dword					GetInterval( ) const override;
	virtual _void					SetInterval( _dword interval ) override;

	virtual _void					Play( ) override;
	virtual _void					Stop( ) override;
	virtual _void					Pause( ) override;
	virtual _void					Resume( ) override;
	virtual _void					Reset( ) override;
};

//----------------------------------------------------------------------------
// TAnimationController Implementation
//----------------------------------------------------------------------------

template< typename Type >
TAnimationController< Type >::TAnimationController( )
{
	mLastTickcount	= 0;
	mDuration		= 0;

	mFPS			= 1000.0f;
	mInterval		= 1;

	mAniStatus		= _ANIMATION_STATUS_STOPPED;
	mAniDirection	= _ANIMATION_DIRECTION_FORWARD;
	mAniMode		= _ANIMATION_MODE_ONCE;
}

template< typename Type >
TAnimationController< Type >::~TAnimationController( )
{
}

template< typename Type >
_void TAnimationController< Type >::UpdateLastTickcount( _dword& elapse )
{
	if ( mLastTickcount + elapse >= mDuration )
	{
		UpdateDirection( elapse );
	}
	else
	{
		mLastTickcount += elapse;
	}
}

template< typename Type >
_void TAnimationController< Type >::UpdateDirection( _dword& elapse )
{
	_dword tick = mDuration - mLastTickcount;

	// forward -> backward
	if ( mAniDirection == _ANIMATION_DIRECTION_FORWARD )
	{
		switch ( mAniMode )
		{
			case _ANIMATION_MODE_ONCE:
				// When update animation
				OnTick( Platform::GetCurrentTickCount( ), tick );
				elapse = 0;

				mLastTickcount = mDuration;
				Stop( );
				break;

			case _ANIMATION_MODE_REPEAT:
				// When update animation
				OnTick( Platform::GetCurrentTickCount( ), tick );
				elapse -= tick;

				Play( );
				break;

			case _ANIMATION_MODE_PINGPONG:
				mLastTickcount = 0;
				SetAniDirection( _ANIMATION_DIRECTION_BACKWARD );
				break;

			default:
				break;
		}
	}
	// backward -> forward
	else
	{
		switch ( mAniMode )
		{
			case _ANIMATION_MODE_ONCE:
				mLastTickcount = mDuration;
				Stop( );
				break;

			case _ANIMATION_MODE_REPEAT:
				Play( );
				break;

			case _ANIMATION_MODE_PINGPONG:
				mLastTickcount = 0;
				SetAniDirection( _ANIMATION_DIRECTION_FORWARD );
				break;

			default:
				break;
		}
	}
}

template< typename Type >
_void TAnimationController< Type >::CopyFrom( const TAnimationController* src_object )
{
	mLastTickcount	= src_object->mLastTickcount;
	mDuration		= src_object->mDuration;
	mFPS			= src_object->mFPS;
	mInterval		= src_object->mInterval;
	mAniStatus		= src_object->mAniStatus;
	mAniDirection	= src_object->mAniDirection;
	mAniMode		= src_object->mAniMode;
}

template< typename Type >
_void TAnimationController< Type >::Tick( _dword limited_elapse, _dword elapse )
{
	// Only update animation on playing mode
	if ( GetAniStatus( ) != _ANIMATION_STATUS_PLAYING )
		return;

	// Update last tickcount
	UpdateLastTickcount( elapse );

	// When update animation
	OnTick( tick, elapse );
}

template< typename Type >
_dword TAnimationController< Type >::GetCurrentFrameTime( ) const
{
	return mLastTickcount;
}

template< typename Type >
_void TAnimationController< Type >::SetCurrentFrameTime( _dword time )
{
	mLastTickcount = time;
}

template< typename Type >
_dword TAnimationController< Type >::GetCurrentFrameNumber( ) const
{
	EGE_ASSERT( mInterval != 0 );

	return mLastTickcount / mInterval;
}

template< typename Type >
_void TAnimationController< Type >::SetCurrentFrameNumber( _dword number )
{
	mLastTickcount = number * mInterval;
}

template< typename Type >
_ANIMATION_STATUS TAnimationController< Type >::GetAniStatus( ) const
{
	return mAniStatus;
}

template< typename Type >
_dword TAnimationController< Type >::GetLastTickcount( ) const
{
	return mLastTickcount;
}

template< typename Type >
_ANIMATION_DIRECTION TAnimationController< Type >::GetAniDirection( ) const
{
	return mAniDirection;
}

template< typename Type >
_void TAnimationController< Type >::SetAniDirection( _ANIMATION_DIRECTION direction )
{
	mAniDirection = direction;
}

template< typename Type >
_ANIMATION_MODE TAnimationController< Type >::GetAniMode( ) const
{
	return mAniMode;
}

template< typename Type >
_void TAnimationController< Type >::SetAniMode( _ANIMATION_MODE mode )
{
	mAniMode = mode;
}

template< typename Type >
_dword TAnimationController< Type >::GetDuration( ) const
{
	return mDuration;
}

template< typename Type >
_void TAnimationController< Type >::SetDuration( _dword duration )
{
	mDuration = duration;
}

template< typename Type >
_dword TAnimationController< Type >::GetTotalFramesNumber( ) const
{
	if ( mInterval == 0 )
		return 1;

	return mDuration / mInterval;
}

template< typename Type >
_void TAnimationController< Type >::SetTotalFramesNumber( _dword frames_number )
{
	mDuration = frames_number * mInterval;
}

template< typename Type >
_float TAnimationController< Type >::GetFPS( ) const
{
	return mFPS;
}

template< typename Type >
_void TAnimationController< Type >::SetFPS( _float fps )
{
	mFPS		= fps;
	mInterval	= Math::GetIntervalTimeByFPS( fps );
}

template< typename Type >
_dword TAnimationController< Type >::GetInterval( ) const
{
	return mInterval;
}

template< typename Type >
_void TAnimationController< Type >::SetInterval( _dword interval )
{
	mInterval	= interval;
	mFPS		= Math::GetFPSByIntervalTime( interval );
}

template< typename Type >
_void TAnimationController< Type >::Play( )
{
	mLastTickcount	= 0;
	mAniStatus		= _ANIMATION_STATUS_PLAYING;

	OnPlayed( );
}

template< typename Type >
_void TAnimationController< Type >::Stop( )
{
	mLastTickcount	= mDuration;
	mAniStatus		= _ANIMATION_STATUS_STOPPED;

	OnStopped( ); 
}

template< typename Type >
_void TAnimationController< Type >::Pause( )
{
	if ( mAniStatus != _ANIMATION_STATUS_PLAYING || mAniStatus == _ANIMATION_STATUS_PAUSING )
		return;

	mAniStatus = _ANIMATION_STATUS_PAUSING;

	OnPaused( );
}

template< typename Type >
_void TAnimationController< Type >::Resume( )
{
	if ( mAniStatus != _ANIMATION_STATUS_PAUSING )
		return;

	mAniStatus = _ANIMATION_STATUS_PLAYING;

	OnResumed( );
}

template< typename Type >
_void TAnimationController< Type >::Reset( )
{
	mLastTickcount	= 0;
	mAniStatus		= _ANIMATION_STATUS_STOPPED;

	OnReset( );
}

}