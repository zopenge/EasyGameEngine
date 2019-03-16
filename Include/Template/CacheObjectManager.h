//! @file     CacheObjectManager.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// CacheObjectManager
//----------------------------------------------------------------------------

template< typename Type, typename Key, typename CompareFunc = Compare< Key > >
class CacheObjectManager
{
protected:
	//!	The cache object
	struct CacheObject
	{
		//!	The expired tick count
		_dword	mExpiredTickCount;
		//!	The current tick count
		_dword	mCurrentTickCount;

		//!	The object element
		Type	mElement;

		//!	Check whether it's stable object or not.
		_ubool IsStable( ) const
		{
			return mExpiredTickCount == -1;
		}
		//!	Update the object.
		_void Tick( _dword elapse )
		{
			// The stable object won't update the tickcount
			if ( IsStable( ) )
				return;

			mCurrentTickCount += elapse;
		}
		//!	Reset the live time.
		_void Reset( _dword live_time, _dword tickcount )
		{
			mCurrentTickCount = tickcount;

			if ( live_time == -1 )
				mExpiredTickCount = -1;
			else
				mExpiredTickCount = mCurrentTickCount + live_time;
		}
		//!	Get the live time.
		_dword GetLiveTime( ) const
		{
			// The stable object is alive always
			if ( IsStable( ) )
				return -1;

			// The object has been dead
			if ( mCurrentTickCount >= mExpiredTickCount )
				return 0;

			return mExpiredTickCount - mCurrentTickCount;
		}

		CacheObject( )
		{
			mExpiredTickCount	= 0;
			mCurrentTickCount	= 0;
		}
		CacheObject( const Type& element, _dword live_time, _dword tickcount )
		{
			mExpiredTickCount	= 0;
			mCurrentTickCount	= 0;
			mElement			= element;

			Reset( live_time, tickcount );
		}
	};

public:
	typedef Map< CacheObject, Key >				CachedObjectMap;
	typedef typename CachedObjectMap::PairType	MapPairType;
	typedef typename CachedObjectMap::Iterator	MapIterator;

protected:
	//!	The increased time of hitting in milliseconds
	_dword			mIncreasedTimeOfHittingMS;

	//!	The cached objects
	CachedObjectMap	mObjectMap;

protected:
	//!	When remove cache object.
	virtual _void OnRemoveCacheObject( const Key& key, CacheObject& object ) { }

protected:
	CacheObjectManager( );
	~CacheObjectManager( );

public:
	//!	Access increased time of hitting in milliseconds.
	EGE_GET_SET_ACCESSOR( _dword, IncreasedTimeOfHittingMS );

public:
	//!	Add cache object with key.
	//!	@param		element		The cache object.
	//!	@param		key			The key of cache object.
	//!	@param		tickcount	The current time tickcount in millisecond.
	//!	@param		live_time	The live time of cache object in millisecond.
	//!	@return		none.
	_void AddObject( const Type& element, const Key& key, _dword tickcount, _dword live_time = -1 );
	//!	Remove cache object.
	//!	@param		key			The key of cache object.
	//!	@return		none.
	_void RemoveObject( const Key& key );
	//!	Clear caches.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );

	//!	Check whether contains specified object or not.
	//!	@param		key			The key of cache object.
	//!	@return		True indicates manager contains the object with provided key.
	_ubool HasObject( const Key& key ) const;
	//!	Obtain the cached object by key.
	//!	@param		key			The key of cache object.
	//!	@return		The object.
	Type* ObtainObject( const Key& key );
	//!	Get the cached object by key.
	//!	@param		key			The key of cache object.
	//!	@return		The object.
	const Type* SearchObject( const Key& key ) const;

	//!	Update the manager.
	//! @param		elapse		The millisecond time of the update interval.
	//! @return		none.
	_void Tick( _dword elapse );
};

//----------------------------------------------------------------------------
// CacheObjectManager Implementation
//----------------------------------------------------------------------------

template< typename Type, typename Key, typename CompareFunc >
CacheObjectManager< Type, Key, CompareFunc >::CacheObjectManager( )
{
	mIncreasedTimeOfHittingMS = 60 SEC;
}

template< typename Type, typename Key, typename CompareFunc >
CacheObjectManager< Type, Key, CompareFunc >::~CacheObjectManager( )
{
}

template< typename Type, typename Key, typename CompareFunc >
_void CacheObjectManager< Type, Key, CompareFunc >::AddObject( const Type& element, const Key& key, _dword tickcount, _dword live_time )
{
	mObjectMap.Insert( CacheObject( element, live_time, tickcount ), key );
}

template< typename Type, typename Key, typename CompareFunc >
_void CacheObjectManager< Type, Key, CompareFunc >::RemoveObject( const Key& key )
{
	MapIterator it = mObjectMap.GetIterator( key );
	if ( it.IsValid( ) == _false )
		return;

	MapPairType& pair = it;

	OnRemoveCacheObject( pair.mObject1, pair.mObject2 );

	mObjectMap.Remove( it );
}

template< typename Type, typename Key, typename CompareFunc >
_void CacheObjectManager< Type, Key, CompareFunc >::Clear( )
{
	mObjectMap.Clear( );
}

template< typename Type, typename Key, typename CompareFunc >
_ubool CacheObjectManager< Type, Key, CompareFunc >::HasObject( const Key& key ) const
{
	return mObjectMap.Search( key ) != _null;
}

template< typename Type, typename Key, typename CompareFunc >
Type* CacheObjectManager< Type, Key, CompareFunc >::ObtainObject( const Key& key )
{
	CacheObject* object = mObjectMap.Search( key );
	if ( object == _null )
		return _null;

	// If it's not stable object then increase the live time
	if ( object->IsStable( ) == _false )
		object->mExpiredTickCount += mIncreasedTimeOfHittingMS;

	return &object->mElement;
}

template< typename Type, typename Key, typename CompareFunc >
const Type* CacheObjectManager< Type, Key, CompareFunc >::SearchObject( const Key& key ) const
{
	const CacheObject* object = mObjectMap.Search( key );
	if ( object == _null )
		return _null;

	return &object->mElement;
}

template< typename Type, typename Key, typename CompareFunc >
_void CacheObjectManager< Type, Key, CompareFunc >::Tick( _dword elapse )
{
	for ( MapIterator it = mObjectMap.GetHeadIterator( ); it.IsValid( ); )
	{
		MapPairType& pair	= (MapPairType&) it;
		CacheObject& object = pair.mObject2;

		// If the cached object is dead then remove it
		if ( object.GetLiveTime( ) == 0 )
		{
			OnRemoveCacheObject( pair.mObject1, pair.mObject2 );

			it = mObjectMap.Remove( it );
			continue;
		}

		// Update the cached object
		object.Tick( elapse );

		// Jump to the next cached object
		it ++;
	}
}

}