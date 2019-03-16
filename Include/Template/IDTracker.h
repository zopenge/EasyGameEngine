//! @file     IDTracker.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IDTracker
//----------------------------------------------------------------------------

template< _ENUM_VALUE _MAX_NUMBER > 
class IDTracker
{
private:
	//!	The max node index
	enum { _NODE_MAX_INDEX		= _MAX_NUMBER - 1 };
	//!	The default root node index
	enum { _NODE_ROOT_INDEX		= _NODE_MAX_INDEX / 2 };
	//!	The bits pre node ( we use 2-bits pre node )
	enum { _BITS_PRE_NODE		= 2 };
	//!	The number of element in each node 
	enum { _NODE_NUMBER_IN_SLOT = 32 / _BITS_PRE_NODE };

	// Mask
	// ----------------------------------------
	// 7 | 6 | 5 | 4 | 3 | 2 | 1		| 0
	// ----------------------------------------
	// x | x | x | x | x | x | CanTrace | Free 
	// ----------------------------------------
	enum _MASK
	{
		_MASK_USED		= 0,							// Used and can not trace
		_MASK_FREE    	= 1 << 0, 						// 1: free, 0: used
		_MASK_CAN_TRACE	= 1 << 1, 						// 1: can trace, 0: can not trace
		_MASK_ID		= _MASK_FREE | _MASK_CAN_TRACE,	// The mask ID
	};

private:
	//!	The range data
	struct RangeData
	{
		_dword	mMin;
		_dword	mMid;
		_dword	mMax;

		//!	Check whether it's leaf or not.
		_ubool IsLeaf( ) const
			{ return ( mMid & 1 ) == 0; }

		//!	Check whether it reach node or not
		_ubool IsReachNode( ) const
			{ return mMin == mMid || mMid == mMax; }

		//!	Get the left node index
		_dword GetLeftNodeIndex( ) const
			{ return ( mMin + mMid ) / 2; }
		//!	Get the right node index
		_dword GetRightNodeIndex( ) const
			{ return ( ( mMid + mMax ) / 2 ) + 1; }

		RangeData( _dword min = 0, _dword mid = 0, _dword max = 0 )
			: mMin( min ), mMid( mid ), mMax( max ) { }
	};

private:
	//!	The max mask buffer length
	enum { _MAX_MASK_BUFFER_LENGTH = ( _NODE_MAX_INDEX / _NODE_NUMBER_IN_SLOT ) + 1 };

	//!	The number of free nodes
	_dword	mFreeNodeNumber;
	//!	The mask buffer of nodes
	_dword	mMaskBuffer[ _MAX_MASK_BUFFER_LENGTH ];

private:
	//!	Get the node mask.
	//!	@param		index	The index of mask buffer.
	//! @return		The node's mask.
	_dword GetNodeMask( _dword index ) const;
	//!	Check whether the node had been used or not.
	//!	@param		index	The index of mask buffer.
	//! @return		True indicates it had been used.
	_ubool IsNodeUsed( _dword index ) const;
	//!	Check whether the node had been free or not.
	//!	@param		index	The index of mask buffer.
	//! @return		True indicates it had been free.
	_ubool IsNodeFree( _dword index ) const;
	//!	Use the node.
	//!	@param		index	The index of mask buffer.
	//! @return		none.
	_void UseNode( _dword index );
	//!	Free the node.
	//!	@param		index	The index of mask buffer.
	//! @return		none.
	_void FreeNode( _dword index );
	//!	Clear the node trace flag
	//!	@param		index	The index of mask buffer.
	//! @return		none.
	_void ClearNodeTraceFlag( _dword index );
	//!	Set the node trace flag
	//!	@param		index	The index of mask buffer.
	//! @return		none.
	_void SetNodeTraceFlag( _dword index );

	//!	Fixup the node when its state changed.
	//!	@param		index	The index of mask buffer.
	//!	@return		none.
	_void Fixup( _dword index );

public:
	IDTracker( );
	IDTracker( const IDTracker< _MAX_NUMBER >& tracker );
	~IDTracker( );

public:
	//! Copy elements from another tracker.
	//! @param		tracker		The other tracker.
	//! @return		The reference of current tracker.
	IDTracker< _MAX_NUMBER >& operator = ( const IDTracker< _MAX_NUMBER >& tracker );

	//!	Get the current number of used entry.
	//!	@param		none.
	//!	@return		The current number of used entry.
	_dword GetUsedNumber( ) const;
	//!	Get the maximal number of entry.
	//!	@param		none.
	//!	@return		The maximal number of entry.
	_dword GetMaxNumber( ) const;

	//!	Allocate a new entry ID.
	//!	@param		none.
	//!	@return		The new entry ID.
	_dword AllocateEntry( );
	//!	Force allocate a new entry ID forcedly.
	//!	@param		id		The entry ID.
	//! @return		True indicates success, false indicates failure.
	_ubool ForceAllocateEntry( _dword id );
	//!	Check whether the specified entry ID has been allocated or not.
	//!	@param		id		The entry ID.
	//!	@return		True indicates it has been allocated.
	_ubool HasEntry( _dword id ) const;
	//!	Remove a entry ID.
	//!	@param		id		The entry ID.
	//!	@return		True indicates remove it successful.
	_ubool RemoveEntry( _dword id );

	//!	Clear.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );
};

//----------------------------------------------------------------------------
// IDTracker Implementation
//----------------------------------------------------------------------------

template< _ENUM_VALUE _MAX_NUMBER > 
IDTracker< _MAX_NUMBER >::IDTracker( )
{
	EGE_ASSERT( _MAX_NUMBER >= _ENUM_VALUE_2 );

	Clear( );
}

template< _ENUM_VALUE _MAX_NUMBER > 
IDTracker< _MAX_NUMBER >::IDTracker( const IDTracker< _MAX_NUMBER >& tracker )
{
	mFreeNodeNumber	= tracker.mFreeNodeNumber;
	memcpy( mMaskBuffer, tracker.mMaskBuffer, sizeof( mMaskBuffer ) );
}

template< _ENUM_VALUE _MAX_NUMBER > 
IDTracker< _MAX_NUMBER >::~IDTracker( )
{
}

template< _ENUM_VALUE _MAX_NUMBER > 
IDTracker< _MAX_NUMBER >& IDTracker< _MAX_NUMBER >::operator = ( const IDTracker< _MAX_NUMBER >& tracker )
{
	Clear( );

	mFreeNodeNumber	= tracker.mFreeNodeNumber;
	memcpy( mMaskBuffer, tracker.mMaskBuffer, sizeof( mMaskBuffer ) );

	return *this;
}

template< _ENUM_VALUE _MAX_NUMBER > 
_dword IDTracker< _MAX_NUMBER >::GetNodeMask( _dword index ) const
{
	EGE_ASSERT( index <= _NODE_MAX_INDEX );

	return ( mMaskBuffer[ index / _NODE_NUMBER_IN_SLOT ] >> ( _BITS_PRE_NODE * ( index % _NODE_NUMBER_IN_SLOT ) ) ) & _MASK_ID;
}

template< _ENUM_VALUE _MAX_NUMBER > 
_ubool IDTracker< _MAX_NUMBER >::IsNodeUsed( _dword index ) const
{
	return ( GetNodeMask( index ) & _MASK_FREE ) == 0;
}

template< _ENUM_VALUE _MAX_NUMBER > 
_ubool IDTracker< _MAX_NUMBER >::IsNodeFree( _dword index ) const
{
	return ( GetNodeMask( index ) & _MASK_FREE ) != 0;
}

template< _ENUM_VALUE _MAX_NUMBER > 
_void IDTracker< _MAX_NUMBER >::UseNode( _dword index )
{
	EGE_ASSERT( index <= _NODE_MAX_INDEX );

	// -> 0
	mMaskBuffer[ index / _NODE_NUMBER_IN_SLOT ] &= 0xFFFFFFFF ^ ( _MASK_ID << ( _BITS_PRE_NODE * ( index % _NODE_NUMBER_IN_SLOT ) ) );
}

template< _ENUM_VALUE _MAX_NUMBER > 
_void IDTracker< _MAX_NUMBER >::FreeNode( _dword index )
{
	EGE_ASSERT( index <= _NODE_MAX_INDEX );

	// -> Free and can trace
	mMaskBuffer[ index / _NODE_NUMBER_IN_SLOT ] |= _MASK_ID << ( _BITS_PRE_NODE * ( index % _NODE_NUMBER_IN_SLOT ) );
}

template< _ENUM_VALUE _MAX_NUMBER > 
_void IDTracker< _MAX_NUMBER >::ClearNodeTraceFlag( _dword index )
{
	EGE_ASSERT( index <= _NODE_MAX_INDEX );

	// -> Clear can trace flag
	mMaskBuffer[ index / _NODE_NUMBER_IN_SLOT ] &= 0xFFFFFFFF ^ ( _MASK_CAN_TRACE << ( _BITS_PRE_NODE * ( index % _NODE_NUMBER_IN_SLOT ) ) );
}

template< _ENUM_VALUE _MAX_NUMBER > 
_void IDTracker< _MAX_NUMBER >::SetNodeTraceFlag( _dword index )
{
	EGE_ASSERT( index <= _NODE_MAX_INDEX );

	// -> Set can trace flag
	mMaskBuffer[ index / _NODE_NUMBER_IN_SLOT ] |= _MASK_CAN_TRACE << ( _BITS_PRE_NODE * ( index % _NODE_NUMBER_IN_SLOT ) );
}

template< _ENUM_VALUE _MAX_NUMBER > 
_void IDTracker< _MAX_NUMBER >::Fixup( _dword index )
{
	RangeData range( 0, _NODE_ROOT_INDEX, _NODE_MAX_INDEX );

	// Build the range data from provided index to the root index
	RangeData rangebuffer[ 256 ]; _int depth = 0;
	while ( index != range.mMid )
	{
		// Save the range of the current depth
		rangebuffer[ depth ++ ] = range;

		// Go left
		if ( index <= range.mMid )
		{
			range.mMax = range.mMid - 1;
			range.mMid = range.GetLeftNodeIndex( );
		}
		// Go right
		else
		{
			range.mMin = range.mMid + 1;
			range.mMid = range.GetRightNodeIndex( );
		}
	}

	// Update the mask of node from provide node to root node
	while ( -- depth >= 0 )
	{
		const RangeData& current_range = rangebuffer[ depth ];

		// Get the left and right node index
		_dword leftindex	= current_range.GetLeftNodeIndex( );
		_dword rightindex	= current_range.GetRightNodeIndex( );

		// Get the left and right node mask
		_dword leftmask		= GetNodeMask( leftindex );
		_dword rightmask	= GetNodeMask( rightindex );
		if ( ( leftmask & _MASK_CAN_TRACE ) || ( rightmask & _MASK_CAN_TRACE ) )
		{
			// We can trace by left or right node
			SetNodeTraceFlag( current_range.mMid );
		}
		// Clear the trace flag if all links have been used both and it's used node
		else if ( IsNodeUsed( current_range.mMid ) )
		{
			ClearNodeTraceFlag( current_range.mMid );
		}
	}
}

template< _ENUM_VALUE _MAX_NUMBER > 
_dword IDTracker< _MAX_NUMBER >::GetUsedNumber( ) const
{
	return _MAX_NUMBER - mFreeNodeNumber;
}

template< _ENUM_VALUE _MAX_NUMBER > 
_dword IDTracker< _MAX_NUMBER >::GetMaxNumber( ) const
{
	return _MAX_NUMBER;
}

template< _ENUM_VALUE _MAX_NUMBER > 
_dword IDTracker< _MAX_NUMBER >::AllocateEntry( )
{
	if ( mFreeNodeNumber == 0 )
		return _null;

	// The free node index
	_dword index = -1;

	// Start to get the free node by tracing the complete binary tree
	RangeData range( 0, _NODE_ROOT_INDEX, _NODE_MAX_INDEX );
	while ( _true )
	{
		// We found the free node index
		if ( range.IsReachNode( ) )
		{
			UseNode( index = range.mMid );
			break;
		}

		// Get the left node index
		_dword leftindex	= range.GetLeftNodeIndex( );
		_dword leftmask		= GetNodeMask( leftindex );
		if ( leftmask & _MASK_CAN_TRACE )
		{
			// Continue to find the node index by left node connection
			range.mMax = range.mMid - 1;
			range.mMid = leftindex;
			continue;
		}

		// Get the right node index
		_dword rightindex	= range.GetRightNodeIndex( );
		_dword rightmask	= GetNodeMask( rightindex );
		if ( rightmask & _MASK_CAN_TRACE )
		{
			// Continue to find the node index by right node connection
			range.mMin = range.mMid + 1;
			range.mMid = rightindex;
			continue;
		}

		// If the left node is free then use it
		if ( leftmask & _MASK_FREE )
		{
			UseNode( index = leftindex );
			break;
		}

		// If the right node is free then use it
		if ( rightmask & _MASK_FREE )
		{
			UseNode( index = rightindex );
			break;
		}

		// Use the root node index
		UseNode( index = range.mMid );
		break;
	}

	// Fixup the nodes mask
	Fixup( index );

	// Decrease the number of free nodes
	mFreeNodeNumber --;

	return index;
}

template< _ENUM_VALUE _MAX_NUMBER > 
_ubool IDTracker< _MAX_NUMBER >::ForceAllocateEntry( _dword id )
{
	if ( id >= _MAX_NUMBER )
		return _false;

	// We can't allocate the used node
	if ( IsNodeUsed( id ) )
		return _false;

	// Use this node
	UseNode( id );

	// Fixup the nodes mask
	Fixup( id );

	// Decrease the number of free nodes
	mFreeNodeNumber --;

	return _true;
}

template< _ENUM_VALUE _MAX_NUMBER > 
_ubool IDTracker< _MAX_NUMBER >::HasEntry( _dword id ) const
{
	if ( id >= _MAX_NUMBER )
		return _false;

	return IsNodeUsed( id );
}

template< _ENUM_VALUE _MAX_NUMBER > 
_ubool IDTracker< _MAX_NUMBER >::RemoveEntry( _dword id )
{
	if ( id >= _MAX_NUMBER )
		return _false;

	// We can't free the unused node
	if ( IsNodeFree( id ) )
		return _false;

	// Free this node
	FreeNode( id );

	// Fixup the nodes mask
	Fixup( id );

	// Increase the number of free nodes
	mFreeNodeNumber ++;

	return _true;
}

template< _ENUM_VALUE _MAX_NUMBER > 
_void IDTracker< _MAX_NUMBER >::Clear( )
{
	mFreeNodeNumber = _MAX_NUMBER;

	// Initialize the mask buffer
	memset( mMaskBuffer, 0xFF, sizeof( mMaskBuffer ) );
}

}