//! @file     TObjectTree.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TObjectTree
//----------------------------------------------------------------------------

template< typename Type, typename NodeInterface >
class TObjectTree : public Type
{
protected:
	typedef typename ITObjectTree< Type, NodeInterface >::IObjectIteratorPassRef IObjectIteratorPassRefType;
	typedef typename ITObjectTree< Type, NodeInterface >::IObjectIterator IObjectIteratorType;

protected:
	//£¡	The iterator
	typedef TObjectTreeIterator< TObject< IObjectIteratorType >, NodeInterface > SelfIterator;

protected:
	//!	The parent object
	NodeInterface*	mParentObject;
	//!	The first child object
	NodeInterface*	mFirstChildObject;
	//!	The tail child object
	NodeInterface*	mLastChildObject;
	//!	The previous object
	NodeInterface*	mPrevObject;
	//!	The next object
	NodeInterface*	mNextObject;

protected:
	TObjectTree( );
	TObjectTree( NodeInterface* parent );
	virtual ~TObjectTree( );

// IObjectTree Interface
public:
	virtual IObject*							CloneSelfTo( ) const override;

	virtual IObjectIteratorPassRefType			GetHeadIterator( ) override;
	virtual IObjectIteratorPassRefType			GetTailIterator( ) override;

	virtual _void								SetParentObject( NodeInterface* node ) override;
	virtual _void								SetFirstChildObject( NodeInterface* node ) override;
	virtual _void								SetLastChildObject( NodeInterface* node ) override;
	virtual _void								SetPrevObject( NodeInterface* node ) override;
	virtual _void								SetNextObject( NodeInterface* node ) override;

	virtual NodeInterface*						RootObject( ) override;
	virtual NodeInterface*						ParentObject( ) override;
	virtual NodeInterface*						FirstChildObject( ) override;
	virtual NodeInterface*						LastChildObject( ) override;
	virtual NodeInterface*						PrevObject( ) override;
	virtual NodeInterface*						NextObject( ) override;

	virtual const NodeInterface*				RootObject( ) const override;
	virtual const NodeInterface*				ParentObject( ) const override;
	virtual const NodeInterface*				FirstChildObject( ) const override;
	virtual const NodeInterface*				LastChildObject( ) const override;
	virtual const NodeInterface*				PrevObject( ) const override;
	virtual const NodeInterface*				NextObject( ) const override;

	virtual _void								RemoveConnections( ) override;
	virtual _void								RemoveChildObject( NodeInterface* object ) override;
	virtual _void								RemoveAllChildObjects( ) override;
	virtual _void								RemoveAllChildObjectsExceptFirstChild( ) override;
	virtual _void								RemoveAllChildObjectsExcept( NodeInterface* object ) override;

	virtual _void 								InsertChildObject( NodeInterface* object ) override;
	virtual _void								InsertChildObject( _dword index, NodeInterface* object ) override;
	virtual _void								InsertPrevObject( NodeInterface* object ) override;
	virtual _void								InsertNextObject( NodeInterface* object ) override;

	virtual _void								MoveToHead( ) override;
	virtual _void								MoveToTail( ) override;
	virtual _ubool								MoveUp( ) override;
	virtual _ubool								MoveDown( ) override;

	virtual _dword								GetChildObjectsNumber( _ubool recursive ) const override;
	virtual Array< RefPtr< NodeInterface > >	GetChildObjects( _ubool recursive ) const override;

	virtual _dword								GetIndexOfParentNode( ) const override;

	virtual _ubool								IsChildOfIt( const NodeInterface* node ) const override;
};

//----------------------------------------------------------------------------
// TObjectTree Implementation
//----------------------------------------------------------------------------

template< typename Type, typename NodeInterface >
TObjectTree< Type, NodeInterface >::TObjectTree( ) 
{
	mFirstChildObject	= _null;
	mLastChildObject	= _null;
	mPrevObject			= _null;
	mNextObject			= _null;
	mParentObject		= _null;
}

template< typename Type, typename NodeInterface >
TObjectTree< Type, NodeInterface >::TObjectTree( NodeInterface* parent )
{
	mFirstChildObject	= _null;
	mLastChildObject	= _null;
	mPrevObject			= _null;
	mNextObject			= _null;
	mParentObject		= _null;

	// Link to parent object
	if ( parent != _null )
	{
		parent->InsertChildObject( static_cast< NodeInterface* >( this ) );
		EGE_ASSERT( mParentObject != _null );
	}
}

template< typename Type, typename NodeInterface >
TObjectTree< Type, NodeInterface >::~TObjectTree( )
{
	// Remove all children
	if ( mFirstChildObject != _null )
	{
		NodeInterface* child_object = mFirstChildObject;
		while ( child_object != _null )
		{
			// Get the next child object
			NodeInterface* next_child_object = child_object->NextObject( );

			// Remove the link of parent object
			if ( child_object->ParentObject( ) != _null )
				child_object->ParentObject( )->RemoveChildObject( child_object );

			// Release children
			child_object->Release( );

			// Continue to remove children
			child_object = next_child_object;
		}

		mFirstChildObject = _null;
	}

	// Remove self connections
	RemoveConnections( );
}

template< typename Type, typename NodeInterface >
IObject* TObjectTree< Type, NodeInterface >::CloneSelfTo( ) const
{
	EGE_ASSERT2( 0, L"Please implement it in the inherit class" );

	return _null;
}

template< typename Type, typename NodeInterface >
typename TObjectTree< Type, NodeInterface >::IObjectIteratorPassRefType TObjectTree< Type, NodeInterface >::GetHeadIterator( )
{
	return new SelfIterator( this );
}

template< typename Type, typename NodeInterface >
typename TObjectTree< Type, NodeInterface >::IObjectIteratorPassRefType TObjectTree< Type, NodeInterface >::GetTailIterator( )
{
	NodeInterface* last_child = LastChildObject( );
	NodeInterface* node = _null;

	while ( last_child != _null )
	{
		node = last_child;
		last_child = last_child->LastChildObject( );
	}

	if ( node == _null )
		node = this;

	return new SelfIterator( node );
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::SetParentObject( NodeInterface* node )
{
	mParentObject = node;
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::SetFirstChildObject( NodeInterface* node )
{
	mFirstChildObject = node;
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::SetLastChildObject( NodeInterface* node )
{
	mLastChildObject = node;
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::SetPrevObject( NodeInterface* node )
{
	mPrevObject = node;
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::SetNextObject( NodeInterface* node )
{
	mNextObject = node;
}

template< typename Type, typename NodeInterface >
NodeInterface* TObjectTree< Type, NodeInterface >::RootObject( ) 
{
	NodeInterface* root = mParentObject;
	if ( root == _null )
		return root;

	while ( root->ParentObject( ) != _null )
		root = root->ParentObject( );

	return root;
}

template< typename Type, typename NodeInterface >
NodeInterface* TObjectTree< Type, NodeInterface >::ParentObject( ) 
{
	return mParentObject;
}

template< typename Type, typename NodeInterface >
NodeInterface* TObjectTree< Type, NodeInterface >::FirstChildObject( ) 
{
	return mFirstChildObject;
}

template< typename Type, typename NodeInterface >
NodeInterface* TObjectTree< Type, NodeInterface >::LastChildObject( ) 
{
	return mLastChildObject;
}

template< typename Type, typename NodeInterface >
NodeInterface* TObjectTree< Type, NodeInterface >::PrevObject( ) 
{
	return mPrevObject;
}

template< typename Type, typename NodeInterface >
NodeInterface* TObjectTree< Type, NodeInterface >::NextObject( ) 
{
	return mNextObject;
}

template< typename Type, typename NodeInterface >
const NodeInterface* TObjectTree< Type, NodeInterface >::RootObject( ) const
{
	const NodeInterface* root = mParentObject;
	if ( root == _null )
		return root;

	while ( root->ParentObject( ) != _null )
		root = root->ParentObject( );

	return root;
}

template< typename Type, typename NodeInterface >
const NodeInterface* TObjectTree< Type, NodeInterface >::ParentObject( ) const
{
	return mParentObject;
}

template< typename Type, typename NodeInterface >
const NodeInterface* TObjectTree< Type, NodeInterface >::FirstChildObject( ) const
{
	return mFirstChildObject;
}

template< typename Type, typename NodeInterface >
const NodeInterface* TObjectTree< Type, NodeInterface >::LastChildObject( ) const
{
	return mLastChildObject;
}

template< typename Type, typename NodeInterface >
const NodeInterface* TObjectTree< Type, NodeInterface >::PrevObject( ) const
{
	return mPrevObject;
}

template< typename Type, typename NodeInterface >
const NodeInterface* TObjectTree< Type, NodeInterface >::NextObject( ) const
{
	return mNextObject;
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::RemoveConnections( )
{
	// Remove it from brothers
	if ( mNextObject != _null )
	{
		NodeInterface* next_object = mNextObject;
		next_object->SetPrevObject( mPrevObject );
	}
	if ( mPrevObject != _null )
	{
		NodeInterface* prev_object = mPrevObject;
		prev_object->SetNextObject( mNextObject );
	}

	// Remove it from parent
	if ( mParentObject != _null )
		mParentObject->RemoveChildObject( static_cast<NodeInterface*>(this) );

	// Clear connections
	mNextObject = _null;
	mPrevObject = _null;
	mParentObject = _null;
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::RemoveChildObject( NodeInterface* object )
{
	if ( object == _null )
		return;

	// Check whether it's child or not
	EGE_ASSERT( object->ParentObject( ) == this );

	// Remove self linking
	NodeInterface* self_prev_object = object->PrevObject( );
	NodeInterface* self_next_object = object->NextObject( );
	if ( self_prev_object != _null )
		self_prev_object->SetNextObject( object->NextObject( ) );
	if ( self_next_object != _null )
		self_next_object->SetPrevObject( object->PrevObject( ) );

	// Remove parent linking
	object->SetParentObject( _null );
	if ( mFirstChildObject == object )
		mFirstChildObject = object->NextObject( );
	if ( mLastChildObject == object )
		mLastChildObject = object->PrevObject( );

	// Remove brother linking
	object->SetNextObject( _null );
	object->SetPrevObject( _null );
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::RemoveAllChildObjects( )
{
	while ( mFirstChildObject != _null )
	{
		NodeInterface* object = mFirstChildObject;
		RemoveChildObject( object );

		EGE_RELEASE( object );
	}
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::RemoveAllChildObjectsExceptFirstChild( )
{
	if ( mFirstChildObject == _null )
		return;

	NodeInterface* next_object = mFirstChildObject->NextObject( );
	while ( next_object != _null )
	{
		RemoveChildObject( next_object );
		EGE_RELEASE( next_object );
		next_object = mFirstChildObject->NextObject( );
	}
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::RemoveAllChildObjectsExcept( NodeInterface* object )
{
	Array< NodeInterface* > nodes;
	for ( NodeInterface* node = mFirstChildObject; node != _null; node = node->NextObject( ) )
	{
		if ( node != object )
			nodes.Append( node );
	}

	for ( _dword i = 0; i < nodes.Number( ); ++ i )
	{
		RemoveChildObject( nodes[i] );
		EGE_RELEASE( nodes[i] );
	}
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::InsertChildObject( NodeInterface* object )
{
	if ( object == _null )
		return;

	// Check whether it's child or not
	EGE_ASSERT( object->ParentObject( ) != this );

	// Remove parent object link
	object->RemoveConnections( );

	// The first child node to insert
	if ( mFirstChildObject == _null )
	{
		EGE_ASSERT( mLastChildObject == _null );

		mFirstChildObject	= object;
		mLastChildObject	= object;
		object->SetParentObject( static_cast< NodeInterface* >( this ) );
	}
	// Add the child to tail
	else
	{
		// The tail object
		NodeInterface* self_tail_object = mLastChildObject;

		// Link to the tail object
		self_tail_object->SetNextObject( object );
		object->SetPrevObject( self_tail_object );
		object->SetNextObject( _null );

		// Link to the parent object
		object->SetParentObject( static_cast< NodeInterface* >( this ) );

		// Update the tail object
		mLastChildObject = object;
	}
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::InsertChildObject( _dword index, NodeInterface* object )
{
	if ( index == -1 || object == _null )
		return;

	for ( NodeInterface* child_node = mFirstChildObject; child_node != _null; child_node = child_node->NextObject( ), index -- )
	{
		if ( index == 0 )
		{
			child_node->InsertPrevObject( object );
			return;
		}
	}

	// Add object as tail object
	if ( index == 0 )
	{
		if ( mLastChildObject != _null )
			mLastChildObject->InsertNextObject( object );
		else
			InsertChildObject( object );
	}
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::InsertPrevObject( NodeInterface* object )
{
	if ( object == _null )
		return;

	// Remove self linking
	object->RemoveConnections( );

	// Bind new link
	NodeInterface* prev_object = mPrevObject;
	object->SetPrevObject( mPrevObject );
	object->SetNextObject( this );
	object->SetParentObject( mParentObject );

	if ( prev_object != _null )
		prev_object->SetNextObject( object );
	mPrevObject = object;

	if ( mParentObject != _null )
	{
		NodeInterface* parent = mParentObject;
		if ( parent->FirstChildObject( ) == this )
			parent->SetFirstChildObject( object );
	}
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::InsertNextObject( NodeInterface* object )
{
	if ( object == _null )
		return;

	// Remove self linking
	object->RemoveConnections( );

	// Bind new link
	NodeInterface* next_object = mNextObject;
	object->SetPrevObject( this );
	object->SetNextObject( mNextObject );
	object->SetParentObject( mParentObject );
	
	if ( next_object != _null )
		next_object->SetPrevObject( object );
	mNextObject = object;

	if ( mParentObject != _null )
	{
		NodeInterface* parent = mParentObject;
		if ( parent->LastChildObject( ) == this )
			parent->SetLastChildObject( object );
	}
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::MoveToHead( )
{
	NodeInterface* parent = mParentObject;
	if ( parent->FirstChildObject( ) == this )
		return;

	RemoveConnections( );

	NodeInterface* child_object = parent->FirstChildObject( );
	if ( child_object == _null )
		return;

	child_object->SetPrevObject( this );
	this->SetNextObject( child_object );
	this->SetParentObject( static_cast< NodeInterface* >( parent ) );

	parent->SetFirstChildObject( this );
}

template< typename Type, typename NodeInterface >
_void TObjectTree< Type, NodeInterface >::MoveToTail( )
{
	NodeInterface* parent = mParentObject;
	if ( parent->LastChildObject( ) == this )
		return;

	RemoveConnections( );

	NodeInterface* child_object = parent->LastChildObject( );
	if ( child_object == _null )
		return;

	child_object->SetNextObject( this );
	this->SetPrevObject( child_object );
	this->SetParentObject( static_cast< NodeInterface* >( parent ) );

	parent->SetLastChildObject( this );
}

template< typename Type, typename NodeInterface >
_ubool TObjectTree< Type, NodeInterface >::MoveUp( )
{
	// Get the previous node
	NodeInterface* prev_node = this->mPrevObject;
	if ( prev_node == _null )
		return _false;

	RemoveConnections( );
	prev_node->InsertPrevObject( this );

	return _true;
}

template< typename Type, typename NodeInterface >
_ubool TObjectTree< Type, NodeInterface >::MoveDown( )
{
	// Get the next node
	NodeInterface* next_node = this->mNextObject;
	if ( next_node == _null )
		return _false;

	RemoveConnections( );
	next_node->InsertNextObject( this );

	return _true;
}

template< typename Type, typename NodeInterface >
_dword TObjectTree< Type, NodeInterface >::GetChildObjectsNumber( _ubool recursive ) const
{
	NodeInterface* child_object = mFirstChildObject;
	if ( child_object == _null )
		return 0;

	_dword number = 0;
	for ( ; child_object != _null; child_object = child_object->NextObject( ) )
	{
		if ( recursive && child_object->FirstChildObject( ) != _null )
			number += child_object->GetChildObjectsNumber( recursive );

		number ++;
	}

	return number;
}

template< typename Type, typename NodeInterface >
Array< RefPtr< NodeInterface > > TObjectTree< Type, NodeInterface >::GetChildObjects( _ubool recursive ) const
{
	Array< RefPtr< NodeInterface > > objects;

	for ( NodeInterface* object = mFirstChildObject; object != _null; object = object->NextObject( ) )
	{
		objects.Append( object );

		// Keep to search recursively
		if ( recursive )
			objects += object->GetChildObjects( recursive );
	}

	return objects;
}

template< typename Type, typename NodeInterface >
_dword TObjectTree< Type, NodeInterface >::GetIndexOfParentNode( ) const
{
	if ( mParentObject == _null )
		return -1;

	NodeInterface* node = mParentObject->FirstChildObject( );
	EGE_ASSERT( node != _null );

	_dword index = 0;
	for ( ; node != _null; node = node->NextObject( ), index ++ )
	{
		if ( node == this )
			return index;
	}

	return -1;
}

template< typename Type, typename NodeInterface >
_ubool TObjectTree< Type, NodeInterface >::IsChildOfIt( const NodeInterface* node ) const
{
	for ( const NodeInterface* self = this; self != _null; self = self->ParentObject( ) )
	{
		if ( self == node )
			return _true;
	}

	return _false;
}

}