//! @file     ITObjectTree.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITObjectTree
//----------------------------------------------------------------------------

template< typename Type, typename NodeInterface >
class ITObjectTree : public Type
{
public:
	typedef ITIterator< RefPtr< NodeInterface >, IObject > IObjectIterator;
	typedef RefPtr< IObjectIterator > IObjectIteratorRef;
	typedef PassRefPtr< IObjectIterator > IObjectIteratorPassRef;

public:
	//!	Clone self only.
	//!	@param		none.
	//!	@return		The new object.
	virtual IObject* CloneSelfTo( ) const PURE;

	//!	Get the head iterator.
	//!	@param		none.
	//!	@return		The head iterator.
	virtual IObjectIteratorPassRef GetHeadIterator( ) PURE;
	//!	Get the tail iterator.
	//!	@param		none.
	//!	@return		The tail iterator.
	virtual IObjectIteratorPassRef GetTailIterator( ) PURE;

	//!	Set the parent object.
	//!	@param		node		The node interface.
	//!	@return		The parent object.
	virtual _void SetParentObject( NodeInterface* node ) PURE;
	//!	Set the first child object.
	//!	@param		node		The node interface.
	//!	@return		The child object.
	virtual _void SetFirstChildObject( NodeInterface* node ) PURE;
	//!	Set the last child object.
	//!	@param		node		The node interface.
	//!	@return		The child object.
	virtual _void SetLastChildObject( NodeInterface* node ) PURE;
	//!	Set the previous object.
	//!	@param		node		The node interface.
	//!	@return		The previous object.
	virtual _void SetPrevObject( NodeInterface* node ) PURE;
	//!	Set the next object.
	//!	@param		node		The node interface.
	//!	@return		The next object.
	virtual _void SetNextObject( NodeInterface* node ) PURE;

	//!	Get the root object.
	//!	@param		none.
	//!	@return		The root object.
	virtual NodeInterface* RootObject( ) PURE;
	//!	Get the parent object.
	//!	@param		none.
	//!	@return		The parent object.
	virtual NodeInterface* ParentObject( ) PURE;
	//!	Get the first child object.
	//!	@param		none.
	//!	@return		The child object.
	virtual NodeInterface* FirstChildObject( ) PURE;
	//!	Get the last child object.
	//!	@param		none.
	//!	@return		The child object.
	virtual NodeInterface* LastChildObject( ) PURE;
	//!	Get the previous object.
	//!	@param		none.
	//!	@return		The previous object.
	virtual NodeInterface* PrevObject( ) PURE;
	//!	Get the next object.
	//!	@param		none.
	//!	@return		The next object.
	virtual NodeInterface* NextObject( ) PURE;

	//!	Get the root object.
	//!	@param		none.
	//!	@return		The root object.
	virtual const NodeInterface* RootObject( ) const PURE;
	//!	Get the parent object.
	//!	@param		none.
	//!	@return		The parent object.
	virtual const NodeInterface* ParentObject( ) const PURE;
	//!	Get the first child object.
	//!	@param		none.
	//!	@return		The child object.
	virtual const NodeInterface* FirstChildObject( ) const PURE;
	//!	Get the last child object.
	//!	@param		none.
	//!	@return		The child object.
	virtual const NodeInterface* LastChildObject( ) const PURE;
	//!	Get the previous object.
	//!	@param		none.
	//!	@return		The previous object.
	virtual const NodeInterface* PrevObject( ) const PURE;
	//!	Get the next object.
	//!	@param		none.
	//!	@return		The next object.
	virtual const NodeInterface* NextObject( ) const PURE;

	//!	Remove self connections.
	//!	@param		none.
	//! @return		none.
	virtual _void RemoveConnections( ) PURE;
	//!	Remove child object.
	//!	@param		object		The node object.
	//!	@return		none.
	virtual _void RemoveChildObject( NodeInterface* object ) PURE;
	//!	Remove all child objects.
	//!	@param		none.
	//!	@return		none.
	virtual _void RemoveAllChildObjects( ) PURE;
	//!	Remove all child objects except the first child node.
	//!	@param		none.
	//!	@return		none.
	virtual _void RemoveAllChildObjectsExceptFirstChild( ) PURE;
	//!	Remove all child objects except the specified child node.
	//!	@param		none.
	//!	@return		none.
	virtual _void RemoveAllChildObjectsExcept( NodeInterface* object ) PURE;

	//!	Insert as child object at the tail.
	//!	@param		object		The node object.
	//!	@return		none.
	virtual _void InsertChildObject( NodeInterface* object ) PURE;
	//!	Insert as child object by the index.
	//!	@param		index		The node index.
	//!	@param		object		The node object.
	//! @return		none.
	virtual _void InsertChildObject( _dword index, NodeInterface* object ) PURE;
	//!	Insert a prev object.
	//!	@param		object		The node object.
	//!	@return		none.
	virtual _void InsertPrevObject( NodeInterface* object ) PURE;
	//!	Insert a next object.
	//!	@param		object		The node object.
	//!	@return		none.
	virtual _void InsertNextObject( NodeInterface* object ) PURE;

	//! Move to head.
	//! @param		none.
	//! @return		none.
	virtual _void MoveToHead( ) PURE;
	//! Move to tail.
	//! @param		none.
	//! @return		none.
	virtual _void MoveToTail( ) PURE;
	//!	Move up.
	//!	@param		none.
	//!	@return		True indicates move successful.
	virtual _ubool MoveUp( ) PURE;
	//!	Move down.
	//!	@param		none.
	//!	@return		True indicates move successful.
	virtual _ubool MoveDown( ) PURE;

	//!	Get child objects number.
	//!	@param		recursive	True indicates get all child objects number recursively.
	//!	@return		The number of child objects.
	virtual _dword GetChildObjectsNumber( _ubool recursive ) const PURE;
	//!	Get child objects.
	//!	@param		recursive	True indicates get all child objects number recursively.
	//!	@return		The child objects.
	virtual Array< RefPtr< NodeInterface > > GetChildObjects( _ubool recursive ) const PURE;

	//!	Get the index of parent node.
	//!	@param		none.
	//!	@return		The index of parent node, start from 0, if the parent node is null then return -1.
	virtual _dword GetIndexOfParentNode( ) const PURE;

	//!	Check whether it's child of it.
	//!	@param		node	The node to test.
	//!	@return		True indicates it's child of node.
	virtual _ubool IsChildOfIt( const NodeInterface* node ) const PURE;
};

}