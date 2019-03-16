//! @file     IAnimationKeyFrames.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IAnimationKeyFrames
//----------------------------------------------------------------------------

template< typename BaseInterface, typename KeyFrameInfo >
class IAnimationKeyFrames : public BaseInterface
{
public:
	//!	The key frame array (time in milliseconds as key)
	typedef Pair< _dword, KeyFrameInfo > KeyFrameInfoPair;
	typedef Array< KeyFrameInfoPair > KeyFrameInfoArray;

public:
	//!	Get the key frames list.
	//!	@param		none.
	//!	@return		The key frames list (milliseconds list).
	virtual const KeyFrameInfoArray& GetKeyFrames( ) const PURE;

	//!	Get the key frame info.
	//!	@param		time			The time of key frame in milliseconds.
	//!	@return		The key frame info.
	virtual KeyFrameInfoPair* GetKeyFrameInfoPairByTime( _dword time ) PURE;
	//!	Get the key frame info by lower bound.
	//!	@param		time			The time of key frame in milliseconds.
	//!	@return		The key frame info.
	virtual KeyFrameInfoPair* GetKeyFrameInfoPairByTimeLowerBound( _dword time ) PURE;
	//!	Get the key frame info by upper bound.
	//!	@param		time			The time of key frame in milliseconds.
	//!	@return		The key frame info.
	virtual KeyFrameInfoPair* GetKeyFrameInfoPairByTimeUpperBound( _dword time ) PURE;
	//!	Get the key frame info.
	//!	@param		index			The index of key frames.
	//!	@return		The key frame info.
	virtual KeyFrameInfoPair* GetKeyFrameInfoPairByIndex( _dword index ) PURE;
	//!	Get the key frame info.
	//!	@param		time			The time of key frame in milliseconds.
	//!	@return		The key frame info.
	virtual const KeyFrameInfoPair* GetKeyFrameInfoPairByTime( _dword time ) const PURE;
	//!	Get the key frame info by lower bound.
	//!	@param		time			The time of key frame in milliseconds.
	//!	@return		The key frame info.
	virtual const KeyFrameInfoPair* GetKeyFrameInfoPairByTimeLowerBound( _dword time ) const PURE;
	//!	Get the key frame info by upper bound.
	//!	@param		time			The time of key frame in milliseconds.
	//!	@return		The key frame info.
	virtual const KeyFrameInfoPair* GetKeyFrameInfoPairByTimeUpperBound( _dword time ) const PURE;
	//!	Get the key frame info.
	//!	@param		index			The index of key frames.
	//!	@return		The key frame info.
	virtual const KeyFrameInfoPair* GetKeyFrameInfoPairByIndex( _dword index ) const PURE;

	//!	Get the key frame info.
	//!	@param		index		The key frame index.
	//!	@return		The key frame info.
	virtual KeyFrameInfo* GetKeyFrameInfoByTime( _dword time ) PURE;
	//!	Get the key frame info by lower bound.
	//!	@param		index		The key frame index.
	//!	@return		The key frame info.
	virtual KeyFrameInfo* GetKeyFrameInfoByTimeLowerBound( _dword time ) PURE;
	//!	Get the key frame info by upper bound.
	//!	@param		index		The key frame index.
	//!	@return		The key frame info.
	virtual KeyFrameInfo* GetKeyFrameInfoByTimeUpperBound( _dword time ) PURE;
	//!	Get the key frame info.
	//!	@param		index		The key frame index.
	//!	@return		The key frame info.
	virtual KeyFrameInfo* GetKeyFrameInfoByIndex( _dword index ) PURE;
	//!	Get the key frame info.
	//!	@param		index		The key frame index.
	//!	@return		The key frame info.
	virtual const KeyFrameInfo* GetKeyFrameInfoByTime( _dword time ) const PURE;
	//!	Get the key frame info by lower bound.
	//!	@param		index		The key frame index.
	//!	@return		The key frame info.
	virtual const KeyFrameInfo* GetKeyFrameInfoByTimeLowerBound( _dword time ) const PURE;
	//!	Get the key frame info by upper bound.
	//!	@param		index		The key frame index.
	//!	@return		The key frame info.
	virtual const KeyFrameInfo* GetKeyFrameInfoByTimeUpperBound( _dword time ) const PURE;
	//!	Get the key frame info.
	//!	@param		index		The key frame index.
	//!	@return		The key frame info.
	virtual const KeyFrameInfo* GetKeyFrameInfoByIndex( _dword index ) const PURE;

	//!	Get the key frame time in milliseconds.
	//!	@param		index			The index of key frames.
	//!	@return		The key frame time in milliseconds, -1 indicates failure.
	virtual _dword GetKeyFrameTime( _dword index ) const PURE;
	//!	Add the key frame.
	//!	@param		time			The time of key frame in milliseconds.
	//!	@param		info			The key frame info.
	//!	@return		none.
	virtual _void AddKeyFrameInfo( _dword time, const KeyFrameInfo& info ) PURE;
	//!	Insert the key frame.
	//!	@param		The other back key frames will move to the end by 1 frame.
	//!	@param		time			The time of key frame in milliseconds.
	//!	@param		info			The key frame info.
	//!	@return		none.
	virtual _void InsertKeyFrameInfo( _dword time, const KeyFrameInfo& info ) PURE;
	//!	Update the key frame.
	//!	@param		time			The time of key frame in milliseconds.
	//!	@param		info			The key frame info.
	//!	@return		none.
	virtual _void UpdateKeyFrameInfo( _dword time, const KeyFrameInfo& info ) PURE;
	//!	Remove key frame.
	//!	@param		time			The time of key frame in milliseconds.
	//!	@return		none.
	virtual _void RemoveKeyFrame( _dword time ) PURE;
	//!	Remove all key frames.
	//!	@param		none.
	//!	@return		none.
	virtual _void RemoveAllKeyFrames( ) PURE;
};

}