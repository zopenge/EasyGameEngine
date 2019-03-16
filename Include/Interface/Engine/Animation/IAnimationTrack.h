//! @file     IAnimationTrack.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IAnimationTrack
//----------------------------------------------------------------------------

template< typename BaseInterface, typename KeyFrameInfo >
class IAnimationTrack : public IAnimationController< IAnimationKeyFrames< BaseInterface, KeyFrameInfo > >
{
public:
	typedef typename IAnimationKeyFrames< BaseInterface, KeyFrameInfo >::KeyFrameInfoPair KeyFrameInfoPair;

public:
	//!	When update current key frame.
	//!	@param		prev_key_frame_index	The prev key frame index.
	//!	@param		curr_key_frame_index	The current key frame index.
	//!	@param		parameters		The use defined parameters.
	//!	@return		none.
	typedef _void (*OnUpdateCurKeyFrame)( _dword prev_key_frame_index, _dword curr_key_frame_index, const QwordParameters2& parameters );

public:	
	//!	Set the update current key frame callback function.
	//!	@param		funcpointer	The function pointer.
	//!	@param		parameters	The user parameters.
	//!	@return		none.
	virtual _void SetUpdateCurKeyFrameFunc( OnUpdateCurKeyFrame funcpointer, const QwordParameters2& parameters ) PURE;

	//!	Update frame.
	//! @param		tick		The tickcount in milliseconds.
	//!	@param		elapse		The elapse time in milliseconds.
	//!	@return		none.
	virtual _void UpdateFrame( _time_t tick, _dword elapse ) PURE;

	//!	Get the current key frame time in milliseconds.
	//!	@param		none.
	//!	@return		The current key frame time in milliseconds.
	virtual _dword GetCurrentKeyFrameTime( ) const PURE;
	//!	Get the next key frame time in milliseconds.
	//!	@param		none.
	//!	@return		The next key frame time in milliseconds.
	virtual _dword GetNextKeyFrameTime( ) const PURE;

	//!	Get the current key frame info.
	//!	@param		none.
	//!	@return		The key frame info.
	virtual KeyFrameInfo* GetCurrentKeyFrameInfo( ) PURE;
	//!	Get the current key frame pair info.
	//!	@param		none.
	//!	@return		The key frame pair info.
	virtual KeyFrameInfoPair* GetCurrentKeyFrameInfoPair( ) PURE;
	//!	Get the current key frame info.
	//!	@param		none.
	//!	@return		The key frame info.
	virtual const KeyFrameInfo* GetCurrentKeyFrameInfo( ) const PURE;
	//!	Get the current key frame pair info.
	//!	@param		none.
	//!	@return		The key frame pair info.
	virtual const KeyFrameInfoPair* GetCurrentKeyFrameInfoPair( ) const PURE;

	//!	Get the next key frame info.
	//!	@param		none.
	//!	@return		The key frame info.
	virtual KeyFrameInfo* GetNextKeyFrameInfo( ) PURE;
	//!	Get the next key frame pair info.
	//!	@param		none.
	//!	@return		The key frame pair info.
	virtual KeyFrameInfoPair* GetNextKeyFrameInfoPair( ) PURE;
	//!	Get the next key frame info.
	//!	@param		none.
	//!	@return		The key frame info.
	virtual const KeyFrameInfo* GetNextKeyFrameInfo( ) const PURE;
	//!	Get the next key frame pair info.
	//!	@param		none.
	//!	@return		The key frame pair info.
	virtual const KeyFrameInfoPair* GetNextKeyFrameInfoPair( ) const PURE;

	//!	Get the alpha between current to next key frame.
	//!	@param		none.
	//!	@return		The alpha factor in [0.0, 1.0] bounds.
	virtual _float GetCurAlphaFactor( ) const PURE;
};

}