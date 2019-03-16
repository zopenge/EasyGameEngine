//! @file     TAnimationPlayer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TAnimationPlayer
//----------------------------------------------------------------------------

template< typename Type >
class TAnimationPlayer : public TAnimationController< Type >
{
protected:
	typedef TAnimationController< Type > TBaseClass;

protected:
	typedef typename Type::IAnimationTrack IAnimationTrack;
	typedef typename Type::IAnimationTrackRef IAnimationTrackRef;
	typedef typename Type::IAnimationTrackArray IAnimationTrackArray;
    typedef typename Type::IAnimationTrackPair IAnimationTrackPair;

protected:
	//!	The animation tracks
	IAnimationTrackArray	mAniTracks;

// TAnimationController Interface
protected:
	virtual _void						OnPlayed( ) override;
	virtual _void						OnStopped( ) override;
	virtual _void						OnPaused( ) override;
	virtual _void						OnResumed( ) override;
	virtual _void						OnReset( ) override;
	virtual _void						OnTick( _time_t tick, _dword elapse ) override;

protected:
	TAnimationPlayer( );
	virtual ~TAnimationPlayer( );

// IAnimationController Interface
public:
	virtual _void						SetCurrentFrameTime( _dword time ) override;

	virtual _void						SetCurrentFrameNumber( _dword number ) override;

	virtual _void						SetFPS( _float fps ) override;

	virtual _void						SetInterval( _dword interval ) override;

// IAnimationPlayer Interface
public:
	virtual IAnimationTrackArray&		GetTracks( ) override;
	virtual const IAnimationTrackArray& GetTracks( ) const override;
	virtual IAnimationTrackRef			GetTrack( WStringPtr name ) override;
	virtual _ubool						AddTrack( WStringPtr name, IAnimationTrack* track ) override;
	virtual _void						RemoveTrack( WStringPtr name ) override;
	virtual _void						RemoveAllTracks( ) override;
};

//----------------------------------------------------------------------------
// TAnimationPlayer Implementation
//----------------------------------------------------------------------------

template< typename Type >
TAnimationPlayer< Type >::TAnimationPlayer( )
{
}

template< typename Type >
TAnimationPlayer< Type >::~TAnimationPlayer( )
{
}

template< typename Type >
_void TAnimationPlayer< Type >::OnPlayed( )
{
	for ( _dword i = 0; i < mAniTracks.Number( ); i ++ )
		mAniTracks[i].mObject2->Play( );
}

template< typename Type >
_void TAnimationPlayer< Type >::OnStopped( )
{
	for ( _dword i = 0; i < mAniTracks.Number( ); i ++ )
	{
		IAnimationTrack* track = mAniTracks[i].mObject2;

		if ( track->GetAniStatus( ) != _ANIMATION_STATUS_STOPPED )
			track->Stop( );
	}
}

template< typename Type >
_void TAnimationPlayer< Type >::OnPaused( )
{
	for ( _dword i = 0; i < mAniTracks.Number( ); i ++ )
		mAniTracks[i].mObject2->Pause( );
}

template< typename Type >
_void TAnimationPlayer< Type >::OnResumed( )
{
	for ( _dword i = 0; i < mAniTracks.Number( ); i ++ )
		mAniTracks[i].mObject2->Resume( );
}

template< typename Type >
_void TAnimationPlayer< Type >::OnReset( )
{
	for ( _dword i = 0; i < mAniTracks.Number( ); i ++ )
		mAniTracks[i].mObject2->Reset( );
}

template< typename Type >
_void TAnimationPlayer< Type >::OnTick( _time_t tick, _dword elapse )
{
	for ( _dword i = 0; i < mAniTracks.Number( ); i ++ )
		mAniTracks[i].mObject2->Tick( tick, elapse );
}

template< typename Type >
_void TAnimationPlayer< Type >::SetCurrentFrameTime( _dword time )
{
	TBaseClass::SetCurrentFrameTime( time );

	for ( _dword i = 0; i < mAniTracks.Number( ); ++ i )
	{
		IAnimationTrack* track = mAniTracks[i].mObject2;

		track->SetCurrentFrameTime( time );
		track->UpdateFrame( Platform::GetCurrentTickCount( ), 0 );
	}
}

template< typename Type >
_void TAnimationPlayer< Type >::SetCurrentFrameNumber( _dword number )
{
	TBaseClass::SetCurrentFrameNumber( number );

	for ( _dword i = 0; i < mAniTracks.Number( ); ++ i )
	{
		IAnimationTrack* track = mAniTracks[i].mObject2;

		track->SetCurrentFrameNumber( number );
		track->UpdateFrame( Platform::GetCurrentTickCount( ), 0 );
	}
}

template< typename Type >
_void TAnimationPlayer< Type >::SetFPS( _float fps )
{
	if ( fps == 0.0f )
		return;

	_dword old_total_frame_number = this->GetTotalFramesNumber( );

	TBaseClass::SetFPS( fps );

	for ( _dword i = 0; i < mAniTracks.Number( ); ++ i )
	{
		IAnimationTrack* track = mAniTracks[i].mObject2;

		track->SetFPS( fps );
	}

	this->mDuration = this->mInterval * old_total_frame_number;
}

template< typename Type >
_void TAnimationPlayer< Type >::SetInterval( _dword interval )
{
	EGE_ASSERT( interval != 0 );

	SetFPS( 1000.0f / ((_float) interval) );
}

template< typename Type >
typename TAnimationPlayer< Type >::IAnimationTrackArray& TAnimationPlayer< Type >::GetTracks( )
{
	return mAniTracks;
}

template< typename Type >
const typename TAnimationPlayer< Type >::IAnimationTrackArray& TAnimationPlayer< Type >::GetTracks( ) const
{
	return mAniTracks;
}

template< typename Type >
typename TAnimationPlayer< Type >::IAnimationTrackRef TAnimationPlayer< Type >::GetTrack( WStringPtr name )
{
	typename IAnimationTrackArray::Iterator it = mAniTracks.template SearchAscending< WStringPtr >( name );
	if ( it.IsValid( ) == _false )
		return _null;

	return ((const IAnimationTrackPair&) it).mObject2;
}

template< typename Type >
_ubool TAnimationPlayer< Type >::AddTrack( WStringPtr name, IAnimationTrack* track )
{
	mAniTracks.template InsertAscending< WStringPtr >( IAnimationTrackPair( name, track ) );

	return _true;
}

template< typename Type >
_void TAnimationPlayer< Type >::RemoveTrack( WStringPtr name )
{
	mAniTracks.template RemoveAscending< WStringPtr >( name );
}

template< typename Type >
_void TAnimationPlayer< Type >::RemoveAllTracks( )
{
	mAniTracks.Clear( );
}

}
