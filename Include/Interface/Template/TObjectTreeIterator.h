//! @file     TObjectTreeIterator.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TObjectTreeIterator
//----------------------------------------------------------------------------

template< typename Type, typename NodeInterface >
class TObjectTreeIterator : public Type
{
protected:
	//!	The object
	RefPtr< NodeInterface >	mObject;

public:
	TObjectTreeIterator( NodeInterface* object );
	virtual ~TObjectTreeIterator( );

// IIterator Interface
public:
	virtual RefPtr< NodeInterface >	GetObject( ) override;
	virtual _ubool					HasObject( ) const override;

	virtual _ubool					MovePrev( ) override;
	virtual _ubool					MoveNext( ) override;
};

//----------------------------------------------------------------------------
// TObjectTreeIterator Implementation
//----------------------------------------------------------------------------

template< typename Type, typename NodeInterface >
TObjectTreeIterator< Type, NodeInterface >::TObjectTreeIterator( NodeInterface* object ) : mObject( object )
{
}

template< typename Type, typename NodeInterface >
TObjectTreeIterator< Type, NodeInterface >::~TObjectTreeIterator( )
{
}

template< typename Type, typename NodeInterface >
RefPtr< NodeInterface > TObjectTreeIterator< Type, NodeInterface >::GetObject( )
{
	return mObject.template cast_static< NodeInterface >( );
}

template< typename Type, typename NodeInterface >
_ubool TObjectTreeIterator< Type, NodeInterface >::HasObject( ) const
{
	return mObject.IsValid( );
}

template< typename Type, typename NodeInterface >
_ubool TObjectTreeIterator< Type, NodeInterface >::MovePrev( )
{
	if ( mObject.IsNull( ) )
		return _false;

	NodeInterface* parent_object	= mObject->ParentObject( );
	NodeInterface* prev_object		= mObject->PrevObject( );

	if ( parent_object != _null && prev_object != _null )
	{
		NodeInterface* object = prev_object->LastChildObject( );
		if ( object == _null )
		{
			mObject = prev_object;
		}
		else
		{
			NodeInterface* node = _null;
			while ( object != _null )
			{
				node	= object;
				object	= node->LastChildObject( );
			}

			mObject = node;
		}
	}
	else
	{
		mObject = mObject->ParentObject( );
		if ( mObject.IsNull( ) )
			return _false;
	}

	return _true;
}

template< typename Type, typename NodeInterface >
_ubool TObjectTreeIterator< Type, NodeInterface >::MoveNext( )
{
	if ( mObject.IsNull( ) )
		return _false;

	NodeInterface* object = _null;

	// Get the next object
	NodeInterface* child_object = mObject->FirstChildObject( );
	if ( child_object != _null )
	{
		object = child_object;
	}
	else
	{
		NodeInterface* next_object = mObject->NextObject( );
		if ( next_object != _null )
			object = next_object;	
	}

	// If the next object is empty then we try to backtrace from parent object
	if ( object == _null )
	{
		NodeInterface* parent_object = mObject->ParentObject( );
		while ( _true )
		{
			// All the next object has been reached
			if ( parent_object == _null )
			{
				mObject.Clear( );
				break;
			}

			// Find the next object
			NodeInterface* next_object = parent_object->NextObject( );
			if ( next_object == _null )
			{
				// Continue to backtrace
				parent_object = parent_object->ParentObject( );
				continue;
			}

			// Found it
			mObject = next_object;
			break;
		}
	}
	else
	{
		mObject = object;
	}

	return _true;
}

}