//! @file     TAnimationTrack.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TAnimationTrackBase
//----------------------------------------------------------------------------

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
class TAnimationTrackBase : public TObject< BaseType >
{
protected:
	typedef BaseType TBaseClass;

protected:
	typedef typename BaseInterface::KeyFrameInfoPair	KeyFrameInfoPair;
	typedef typename BaseInterface::OnUpdateCurKeyFrame OnUpdateCurKeyFrame;

	typedef CallbackFunc< OnUpdateCurKeyFrame, _void, QwordParameters2 > OnUpdateCurKeyFrameFunc;

protected:
	//!	The current key frame index
	_dword					mCurKeyFrameIndex;
	//!	The next key frame index
	_dword					mNextKeyFrameIndex;

	//!	The callback functions
	OnUpdateCurKeyFrameFunc	mUpdateCurKeyFrameFunc;

protected:
	//!	When update current key frame index.
	virtual _void OnUpdateCurrentKeyFrameIndex( _dword prev_index ) { }

protected:
	//!	Update current key frame index.
	_void UpdateCurrentKeyFrameIndex( _dword prev_index, _dword index );
	//!	Update frame.
	_void UpdateFrame( );

	//!	Update key frame index by last tickcount.
	_void UpdateKeyFrameIndex( );

protected:
	TAnimationTrackBase( );
	virtual ~TAnimationTrackBase( );

// IObject Interface
public:
	virtual _void					Tick( _dword limited_elapse, _dword elapse ) override;

// IAnimationController Interface
public:
	virtual _void					SetCurrentFrameTime( _dword time ) override;

	virtual _void					SetCurrentFrameNumber( _dword number ) override;

	virtual _void					SetFPS( _float fps ) override;

	virtual _void					SetInterval( _dword interval ) override;

	virtual _void					Play( ) override;
	virtual _void					Reset( ) override;
	virtual _void					Stop( ) override;

// IAnimationTrack Interface
public:
	virtual _void					SetUpdateCurKeyFrameFunc( OnUpdateCurKeyFrame funcpointer, const QwordParameters2& parameters ) override;

	virtual _void					UpdateFrame( _time_t tick, _dword elapse ) override;

	virtual _dword					GetCurrentKeyFrameTime( ) const override;
	virtual _dword					GetNextKeyFrameTime( ) const override;

	virtual KeyFrameInfo*			GetCurrentKeyFrameInfo( ) override;
	virtual KeyFrameInfoPair*		GetCurrentKeyFrameInfoPair( ) override;
	virtual const KeyFrameInfo*		GetCurrentKeyFrameInfo( ) const override;
	virtual const KeyFrameInfoPair* GetCurrentKeyFrameInfoPair( ) const override;

	virtual KeyFrameInfo*			GetNextKeyFrameInfo( ) override;
	virtual KeyFrameInfoPair*		GetNextKeyFrameInfoPair( ) override;
	virtual const KeyFrameInfo*		GetNextKeyFrameInfo( ) const override;
	virtual const KeyFrameInfoPair* GetNextKeyFrameInfoPair( ) const override;

	virtual _float					GetCurAlphaFactor( ) const override;
};

//----------------------------------------------------------------------------
// TAnimationTrackBase Implementation
//----------------------------------------------------------------------------

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::TAnimationTrackBase( )
{
	mCurKeyFrameIndex	= -1;
	mNextKeyFrameIndex	= -1;
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::~TAnimationTrackBase( )
{
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_void TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::UpdateCurrentKeyFrameIndex( _dword prev_index, _dword index )
{
	mCurKeyFrameIndex = index;

	mUpdateCurKeyFrameFunc.Invoke( prev_index, mCurKeyFrameIndex );

	OnUpdateCurrentKeyFrameIndex( prev_index );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_void TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::SetUpdateCurKeyFrameFunc( OnUpdateCurKeyFrame funcpointer, const QwordParameters2& parameters )
{
	mUpdateCurKeyFrameFunc.Init( funcpointer, parameters );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_void TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::UpdateFrame( )
{
	// Check whether we have the next key frame or not
	if ( mNextKeyFrameIndex == -1 )
		return;

	// forward -> backward
	if ( this->mAniDirection == _ANIMATION_DIRECTION_FORWARD )
	{
		while ( this->mLastTickcount >= GetNextKeyFrameTime( ) && mNextKeyFrameIndex != -1 )
		{
			UpdateCurrentKeyFrameIndex( mCurKeyFrameIndex, mNextKeyFrameIndex );

			// Check whether has next key frame
			if ( this->GetKeyFrameTime( mNextKeyFrameIndex + 1 ) != -1 )
				mNextKeyFrameIndex ++;
			else
				mNextKeyFrameIndex = -1;
		}
	}
	// backward -> forward
	else
	{
		while ( this->mDuration - this->mLastTickcount <= GetNextKeyFrameTime( ) && mNextKeyFrameIndex != -1 )
		{
			UpdateCurrentKeyFrameIndex( mCurKeyFrameIndex, mNextKeyFrameIndex );

			// Check whether has next key frame
			if ( this->GetKeyFrameTime( mNextKeyFrameIndex - 1 ) != -1 )
				mNextKeyFrameIndex --;
			else
				mNextKeyFrameIndex = -1;
		}
	}
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_void TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::UpdateKeyFrameIndex( )
{
	// Reset the current and next key frame index
	if ( this->GetKeyFramesList( ).Number( ) == 0 )
	{
		mCurKeyFrameIndex	= -1;
		mNextKeyFrameIndex	= -1;
	}
	else
	{
		_dword key_frame_index = this->GetKeyFramesList( ).LowerBoundAscending( this->mLastTickcount );
		if ( key_frame_index == -1 )
		{
			// Seek to the first frame
			mNextKeyFrameIndex = -1;
			UpdateCurrentKeyFrameIndex( mCurKeyFrameIndex, 0 );
		}
		else
		{
			// Seek to the lower bound of last tickcount (TODO: ?)
			mNextKeyFrameIndex = key_frame_index + 1;
			if ( mNextKeyFrameIndex >= this->GetKeyFramesList( ).Number( ) )
				mNextKeyFrameIndex = -1;

			UpdateCurrentKeyFrameIndex( mCurKeyFrameIndex, key_frame_index );
		}
	}
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_void TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::Tick( _dword limited_elapse, _dword elapse )
{
	// Only update animation on playing mode
	if ( this->GetAniStatus( ) != _ANIMATION_STATUS_PLAYING )
		return;

	// Update last tickcount
	this->UpdateLastTickcount( elapse );

	if ( this->GetAniStatus( ) != _ANIMATION_STATUS_STOPPED )
	{
		// Update frame
		UpdateFrame( );

		// When update animation
		this->OnTick( tick, elapse );
	}
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_void TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::SetCurrentFrameTime( _dword time )
{
	TBaseClass::SetCurrentFrameTime( time );

	UpdateKeyFrameIndex( );

	this->OnTick( Platform::GetCurrentTickCount( ), 0 );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_void TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::SetCurrentFrameNumber( _dword number )
{
	TBaseClass::SetCurrentFrameNumber( number );

	UpdateKeyFrameIndex( );

	this->OnTick( Platform::GetCurrentTickCount( ), 0 );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_void TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::SetFPS( _float fps )
{
	if ( fps == 0.0f )
		return;

	_dword old_interval				= this->mInterval;
	_dword old_total_frame_number	= this->GetTotalFramesNumber( );

	TBaseClass::SetFPS( fps );
	if ( old_interval == 0 )
		old_interval = this->mInterval;

	for ( _dword i = 0; i < this->GetKeyFramesList( ).Number( ); i ++ )
	{
		_dword cur_key_frame_number = this->GetKeyFrameInfoPairByIndex( i )->mObject1 / old_interval;

		this->GetKeyFrameInfoPairByIndex( i )->mObject1 = cur_key_frame_number * this->mInterval;
	}

	this->mDuration = this->mInterval * old_total_frame_number;
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_void TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::SetInterval( _dword interval )
{
	EGE_ASSERT( interval != 0 );

	SetFPS( 1000.0f / ((_float) interval) );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_void TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::Play( )
{
	TBaseClass::Play( );

	if ( this->GetKeyFramesList( ).Number( ) == 0 )
	{
		TBaseClass::Stop( );
		mCurKeyFrameIndex	= -1;
		mNextKeyFrameIndex	= -1;
	}
	else
	{
		mNextKeyFrameIndex	= 0;
		mCurKeyFrameIndex	= -1;
	}
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_void TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::Reset( )
{
	TBaseClass::Reset( );

	if ( this->GetKeyFramesList( ).Number( ) == 0 )
	{
		mCurKeyFrameIndex	= -1;
		mNextKeyFrameIndex	= -1;
	}
	else
	{
		mNextKeyFrameIndex	= 0;
		mCurKeyFrameIndex	= -1;
	}
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_void TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::Stop( )
{
	if ( this->GetKeyFramesList( ).Number( ) == 0 )
	{
		mCurKeyFrameIndex	= -1;
		mNextKeyFrameIndex	= -1;
	}
	else
	{
		_dword prev_index = mCurKeyFrameIndex;
		mNextKeyFrameIndex	= -1;
		mCurKeyFrameIndex	= this->GetKeyFramesList( ).Number( ) - 1;
		if ( this->GetKeyFramesList( ).GetTailElement( ).mObject1 == this->mDuration )
			UpdateCurrentKeyFrameIndex( prev_index, this->GetKeyFramesList( ).Number( ) - 1 );
	}
	TBaseClass::Stop( );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_void TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::UpdateFrame( _time_t tick, _dword elapse )
{
	// Update track
	TBaseClass::Tick( tick, elapse );

	// Update frame
	UpdateFrame( );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_dword TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::GetCurrentKeyFrameTime( ) const
{
	if ( mCurKeyFrameIndex == -1 )
		return -1;

	return this->GetKeyFrameTime( mCurKeyFrameIndex );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_dword TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::GetNextKeyFrameTime( ) const
{
	if ( mNextKeyFrameIndex == -1 )
		return -1;

	return this->GetKeyFrameTime( mNextKeyFrameIndex );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
KeyFrameInfo* TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::GetCurrentKeyFrameInfo( )
{
	if ( mCurKeyFrameIndex == -1 )
		return _null;

	return this->GetKeyFrameInfoByIndex( mCurKeyFrameIndex );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
typename BaseInterface::KeyFrameInfoPair* TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::GetCurrentKeyFrameInfoPair( )
{
	if ( mCurKeyFrameIndex == -1 )
		return _null;

	return this->GetKeyFrameInfoPairByIndex( mCurKeyFrameIndex );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
const KeyFrameInfo* TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::GetCurrentKeyFrameInfo( ) const
{
	if ( mCurKeyFrameIndex == -1 )
		return _null;

	return this->GetKeyFrameInfoByIndex( mCurKeyFrameIndex );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
const typename BaseInterface::KeyFrameInfoPair* TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::GetCurrentKeyFrameInfoPair( ) const
{
	if ( mCurKeyFrameIndex == -1 )
		return _null;

	return this->GetKeyFrameInfoPairByIndex( mCurKeyFrameIndex );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
KeyFrameInfo* TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::GetNextKeyFrameInfo( )
{
	if ( mNextKeyFrameIndex == -1 )
		return _null;

	return this->GetKeyFrameInfoByIndex( mNextKeyFrameIndex );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
typename BaseInterface::KeyFrameInfoPair* TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::GetNextKeyFrameInfoPair( )
{
	if ( mNextKeyFrameIndex == -1 )
		return _null;

	return this->GetKeyFrameInfoPairByIndex( mNextKeyFrameIndex );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
const KeyFrameInfo* TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::GetNextKeyFrameInfo( ) const
{
	if ( mNextKeyFrameIndex == -1 )
		return _null;

	return this->GetKeyFrameInfoByIndex( mNextKeyFrameIndex );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
const typename BaseInterface::KeyFrameInfoPair* TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::GetNextKeyFrameInfoPair( ) const
{
	if ( mNextKeyFrameIndex == -1 )
		return _null;

	return this->GetKeyFrameInfoPairByIndex( mNextKeyFrameIndex );
}

template< typename BaseInterface, typename KeyFrameInfo, typename BaseType >
_float TAnimationTrackBase< BaseInterface, KeyFrameInfo, BaseType >::GetCurAlphaFactor( ) const
{
	const KeyFrameInfoPair* cur_key_frame	= GetCurrentKeyFrameInfoPair( );
	const KeyFrameInfoPair* next_key_frame	= GetNextKeyFrameInfoPair( );
	if ( cur_key_frame == _null || next_key_frame == _null )
		return 0.0f;

	_float alpha = EGE_RATIO( this->mLastTickcount - cur_key_frame->mObject1, next_key_frame->mObject1 - cur_key_frame->mObject1 );
	return alpha;
}

//----------------------------------------------------------------------------
// TAnimationTrack
//----------------------------------------------------------------------------

template< typename BaseInterface, typename KeyFrameInfo >
class TAnimationTrack : public TAnimationTrackBase< BaseInterface, KeyFrameInfo, TAnimationController< TAnimationKeyFrames< BaseInterface, KeyFrameInfo > > >
{
protected:
	typedef TAnimationController< TAnimationKeyFrames< BaseInterface, KeyFrameInfo > > TBaseClass;

protected:
	_void CopyFrom( const TAnimationTrack* src_object )
	{
		TBaseClass::CopyFrom( src_object );
	}
};

}