//! @file     MarkupLangSerializableNodeWalker.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// MarkupLangSerializableNodeWalker Implementation
//----------------------------------------------------------------------------

MarkupLangSerializableNodeWalker::MarkupLangSerializableNodeWalker( ISerializableNode* node )
{
	EGE_ASSERT( node );

	mNodeStack.Push( node );
}

MarkupLangSerializableNodeWalker::~MarkupLangSerializableNodeWalker( )
{

}

_ubool MarkupLangSerializableNodeWalker::Walk( )
{
	ISerializableNodeRef child_node = mNodeStack.Top( )->GetFirstChildNode( );
	if ( child_node.IsValid( ) )
	{
		mNodeStack.Push( child_node );
		return _true;
	}

	ISerializableNodeRef next_node = mNodeStack.Top( )->GetNextNode( );
	if ( next_node.IsValid( ) )
	{
		mNodeStack.Top( ) = next_node;
		return _true;
	}

	while ( _true )
	{
		mNodeStack.Pop( );
		if ( mNodeStack.Number( ) == 0 )
			break;

		next_node = mNodeStack.Top( )->GetNextNode( );
		if ( next_node.IsValid( ) )
		{
			mNodeStack.Top( ) = next_node;
			return _true;
		}
	} 

	return _false;
}

ISerializableNodeRef MarkupLangSerializableNodeWalker::GetNode( )
{
	if ( mNodeStack.Number( ) == 0 )
		return _null;

	return mNodeStack.Top( );
}