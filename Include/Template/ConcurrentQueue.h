//! @file     ConcurrentQueue.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ConcurrentQueue
//----------------------------------------------------------------------------

template< typename Type > 
class ConcurrentQueue : public Queue< Type >
{
private:
	Lock	mLock;

public:
	//! Constructor, create an empty queue.
	//! @param		none.
	ConcurrentQueue( );
	//! Copy-Constructor, create a queue by copy from another one.
	//! @param		queue	The other queue.
	ConcurrentQueue( const ConcurrentQueue< Type >& queue );
	//! Destructor, delete the queue, and release the elements memory.
	//! @param		none
	~ConcurrentQueue( );

public:
	template<typename U>
	_ubool try_dequeue( U& item )
	{
		LockOwner lock_owner( mLock );

		return Dequeue( item );
	}

	_void enqueue( const Type& item )
	{
		LockOwner lock_owner( mLock );

		Enqueue( item );
	}
};

//----------------------------------------------------------------------------
// ConcurrentQueue Implementation
//----------------------------------------------------------------------------

template< typename Type >
ConcurrentQueue< Type >::ConcurrentQueue( )
{
}

template< typename Type >
ConcurrentQueue< Type >::ConcurrentQueue( const ConcurrentQueue< Type >& queue )
{
}

template< typename Type >
ConcurrentQueue< Type >::~ConcurrentQueue( )
{
}

}