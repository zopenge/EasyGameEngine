//! @file     TAnimationKeyFrames.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TAnimationKeyFrames
//----------------------------------------------------------------------------

template< typename BaseInterface, typename KeyFrameInfo >
class TAnimationKeyFrames : public BaseInterface
{
public:
	typedef typename BaseInterface::KeyFrameInfoPair KeyFrameInfoPair;
	typedef typename BaseInterface::KeyFrameInfoArray KeyFrameInfoArray;

protected:
	KeyFrameInfoArray	mKeyFrames;

protected:
	TAnimationKeyFrames( );
	virtual ~TAnimationKeyFrames( );

// IAnimationKeyFrames Interface
public:
	virtual const KeyFrameInfoArray&	GetKeyFrames( ) const override;

	virtual KeyFrameInfoPair*			GetKeyFrameInfoPairByTime( _dword time ) override;
	virtual KeyFrameInfoPair*			GetKeyFrameInfoPairByTimeLowerBound( _dword time ) override;
	virtual KeyFrameInfoPair*			GetKeyFrameInfoPairByTimeUpperBound( _dword time ) override;
	virtual KeyFrameInfoPair*			GetKeyFrameInfoPairByIndex( _dword index ) override;
	virtual const KeyFrameInfoPair*		GetKeyFrameInfoPairByTime( _dword time ) const override;
	virtual const KeyFrameInfoPair*		GetKeyFrameInfoPairByTimeLowerBound( _dword time ) const override;
	virtual const KeyFrameInfoPair*		GetKeyFrameInfoPairByTimeUpperBound( _dword time ) const override;
	virtual const KeyFrameInfoPair*		GetKeyFrameInfoPairByIndex( _dword index ) const override;

	virtual KeyFrameInfo*				GetKeyFrameInfoByTime( _dword time ) override;
	virtual KeyFrameInfo*				GetKeyFrameInfoByTimeLowerBound( _dword time ) override;
	virtual KeyFrameInfo*				GetKeyFrameInfoByTimeUpperBound( _dword time ) override;
	virtual KeyFrameInfo*				GetKeyFrameInfoByIndex( _dword index ) override;
	virtual const KeyFrameInfo*			GetKeyFrameInfoByTime( _dword time ) const override;
	virtual const KeyFrameInfo*			GetKeyFrameInfoByTimeLowerBound( _dword time ) const override;
	virtual const KeyFrameInfo*			GetKeyFrameInfoByTimeUpperBound( _dword time ) const override;
	virtual const KeyFrameInfo*			GetKeyFrameInfoByIndex( _dword index ) const override;

	virtual _dword						GetKeyFrameTime( _dword index ) const override;
	virtual _void						AddKeyFrameInfo( _dword time, const KeyFrameInfo& info ) override;
	virtual _void						InsertKeyFrameInfo( _dword time, const KeyFrameInfo& info ) override;
	virtual _void						UpdateKeyFrameInfo( _dword time, const KeyFrameInfo& info ) override;
	virtual _void						RemoveKeyFrame( _dword time ) override;
	virtual _void						RemoveAllKeyFrames( ) override;
	virtual _dword						OptimizeKeyFrames( ) override;
};

//----------------------------------------------------------------------------
// TAnimationKeyFrames Implementation
//----------------------------------------------------------------------------

template< typename BaseInterface, typename KeyFrameInfo >
TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::TAnimationKeyFrames( )
{
}

template< typename BaseInterface, typename KeyFrameInfo >
TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::~TAnimationKeyFrames( )
{
}

template< typename BaseInterface, typename KeyFrameInfo >
const typename TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::KeyFrameInfoArray& TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrames( ) const
{
	return mKeyFrames;
}

template< typename BaseInterface, typename KeyFrameInfo >
typename TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::KeyFrameInfoPair* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoPairByTime( _dword time )
{
	const typename KeyFrameInfoArray::Iterator it = mKeyFrames.template SearchAscending< _dword >( time );
	if ( it.IsValid( ) == _false )
		return _null;

	return &mKeyFrames[ it.mIndex ];
}

template< typename BaseInterface, typename KeyFrameInfo >
typename TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::KeyFrameInfoPair* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoPairByTimeLowerBound( _dword time )
{
	_dword index = mKeyFrames.template LowerBoundAscending< _dword >( time );
	if ( index == -1 )
		return _null;

	return &mKeyFrames[ index ];
}

template< typename BaseInterface, typename KeyFrameInfo >
typename TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::KeyFrameInfoPair* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoPairByTimeUpperBound( _dword time )
{
	_dword index = mKeyFrames.template UpperBoundAscending< _dword >( time );
	if ( index == -1 )
		return _null;

	return &mKeyFrames[ index ];
}

template< typename BaseInterface, typename KeyFrameInfo >
typename TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::KeyFrameInfoPair* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoPairByIndex( _dword index )
{
	if ( index >= mKeyFrames.Number( ) )
		return _null;

	return &mKeyFrames[ index ];
}

template< typename BaseInterface, typename KeyFrameInfo >
const typename TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::KeyFrameInfoPair* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoPairByTime( _dword time ) const
{
	const typename KeyFrameInfoArray::Iterator it = mKeyFrames.template SearchAscending< _dword >( time );
	if ( it.IsValid( ) == _false )
		return _null;

	return &mKeyFrames[ it.mIndex ];
}

template< typename BaseInterface, typename KeyFrameInfo >
const typename TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::KeyFrameInfoPair* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoPairByTimeLowerBound( _dword time ) const
{
	_dword index = mKeyFrames.template LowerBoundAscending< _dword >( time );
	if ( index == -1 )
		return _null;

	return &mKeyFrames[ index ];
}

template< typename BaseInterface, typename KeyFrameInfo >
const typename TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::KeyFrameInfoPair* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoPairByTimeUpperBound( _dword time ) const
{
	_dword index = mKeyFrames.template UpperBoundAscending< _dword >( time );
	if ( index == -1 )
		return _null;

	return &mKeyFrames[ index ];
}

template< typename BaseInterface, typename KeyFrameInfo >
const typename TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::KeyFrameInfoPair* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoPairByIndex( _dword index ) const
{
	if ( index >= mKeyFrames.Number( ) )
		return _null;

	return &mKeyFrames[ index ];
}

template< typename BaseInterface, typename KeyFrameInfo >
KeyFrameInfo* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoByTime( _dword time )
{
	KeyFrameInfoPair* pair = GetKeyFrameInfoPairByTime( time );
	if ( pair == _null )
		return _null;

	return &pair->mObject2;
}

template< typename BaseInterface, typename KeyFrameInfo >
KeyFrameInfo* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoByTimeLowerBound( _dword time )
{
	KeyFrameInfoPair* pair = GetKeyFrameInfoPairByTimeLowerBound( time );
	if ( pair == _null )
		return _null;

	return &pair->mObject2;
}

template< typename BaseInterface, typename KeyFrameInfo >
KeyFrameInfo* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoByTimeUpperBound( _dword time )
{
	KeyFrameInfoPair* pair = GetKeyFrameInfoPairByTimeUpperBound( time );
	if ( pair == _null )
		return _null;

	return &pair->mObject2;
}

template< typename BaseInterface, typename KeyFrameInfo >
KeyFrameInfo* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoByIndex( _dword index )
{
	KeyFrameInfoPair* pair = GetKeyFrameInfoPairByIndex( index );
	if ( pair == _null )
		return _null;

	return &pair->mObject2;
}

template< typename BaseInterface, typename KeyFrameInfo >
const KeyFrameInfo* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoByTime( _dword time ) const
{
	const KeyFrameInfoPair* pair = GetKeyFrameInfoPairByTime( time );
	if ( pair == _null )
		return _null;

	return &pair->mObject2;
}

template< typename BaseInterface, typename KeyFrameInfo >
const KeyFrameInfo* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoByTimeLowerBound( _dword time ) const 
{
	const KeyFrameInfoPair* pair = GetKeyFrameInfoPairByTimeLowerBound( time );
	if ( pair == _null )
		return _null;

	return &pair->mObject2;
}

template< typename BaseInterface, typename KeyFrameInfo >
const KeyFrameInfo* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoByTimeUpperBound( _dword time ) const 
{
	const KeyFrameInfoPair* pair = GetKeyFrameInfoPairByTimeUpperBound( time );
	if ( pair == _null )
		return _null;

	return &pair->mObject2;
}

template< typename BaseInterface, typename KeyFrameInfo >
const KeyFrameInfo* TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameInfoByIndex( _dword index ) const
{
	const KeyFrameInfoPair* pair = GetKeyFrameInfoPairByIndex( index );
	if ( pair == _null )
		return _null;

	return &pair->mObject2;
}

template< typename BaseInterface, typename KeyFrameInfo >
_dword TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::GetKeyFrameTime( _dword index ) const
{
	if ( index >= mKeyFrames.Number( ) )
		return -1;

	return mKeyFrames[ index ].mObject1;
}

template< typename BaseInterface, typename KeyFrameInfo >
_void TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::AddKeyFrameInfo( _dword time, const KeyFrameInfo& info )
{
	const typename KeyFrameInfoArray::Iterator it = mKeyFrames.template SearchAscending< _dword >( time );
	if ( it.IsValid( ) == _false )
	{
		mKeyFrames.template InsertAscending< _dword >( KeyFrameInfoPair( time, info ) );
	}
	else
	{
		mKeyFrames[ it.mIndex ].mObject2 = info;
	}
}

template< typename BaseInterface, typename KeyFrameInfo >
_void TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::InsertKeyFrameInfo( _dword time, const KeyFrameInfo& info )
{
	// Move all other key frames back
	for ( _dword i = 0; i < mKeyFrames.Number( ); i ++ )
	{
		if ( mKeyFrames[i].mObject1 < time )
			continue;

		mKeyFrames[i].mObject1 ++;
	}

	// Insert key frame
	mKeyFrames.template InsertAscending< _dword >( KeyFrameInfoPair( time, info ) );
}

template< typename BaseInterface, typename KeyFrameInfo >
_void TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::UpdateKeyFrameInfo( _dword time, const KeyFrameInfo& info )
{
	const typename KeyFrameInfoArray::Iterator it = mKeyFrames.template SearchAscending< _dword >( time );
	if ( it.IsValid( ) )
	{
		mKeyFrames[ it.mIndex ].mObject2 = info;
	}
}

template< typename BaseInterface, typename KeyFrameInfo >
_void TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::RemoveKeyFrame( _dword time )
{
	mKeyFrames.template RemoveAscending< _dword >( time );
}

template< typename BaseInterface, typename KeyFrameInfo >
_void TAnimationKeyFrames< BaseInterface, KeyFrameInfo >::RemoveAllKeyFrames( )
{
	mKeyFrames.Clear( );
}

}
