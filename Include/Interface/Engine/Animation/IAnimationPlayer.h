//! @file     IAnimationPlayer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IAnimationPlayer
//----------------------------------------------------------------------------

template< typename Type, typename AniTrackType >
class IAnimationPlayer : public IAnimationController< Type >
{
public:
	typedef AniTrackType IAnimationTrack;
	typedef RefPtr< IAnimationTrack > IAnimationTrackRef;
	typedef Pair< WString, IAnimationTrackRef > IAnimationTrackPair;
	typedef Array< IAnimationTrackPair > IAnimationTrackArray;

public:
	//!	Get tracks.
	//!	@param		none.
	//!	@return		The tracks.
	virtual IAnimationTrackArray& GetTracks( ) PURE;
	//!	Get tracks.
	//!	@param		none.
	//!	@return		The tracks.
	virtual const IAnimationTrackArray& GetTracks( ) const PURE;
	//!	Get track.
	//!	@param		name		The track name.
	//!	@return		The track interface.
	virtual IAnimationTrackRef GetTrack( WStringPtr name ) PURE;
	//!	Add track.
	//!	@param		name		The track name.
	//!	@param		track		The track interface.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool AddTrack( WStringPtr name, IAnimationTrack* track ) PURE;
	//!	Remove track.
	//!	@param		name		The track name.
	//!	@return		none.
	virtual _void RemoveTrack( WStringPtr name ) PURE;
	//!	Remove all tracks.
	//!	@param		none.
	//!	@return		none.
	virtual _void RemoveAllTracks( ) PURE;
};

}