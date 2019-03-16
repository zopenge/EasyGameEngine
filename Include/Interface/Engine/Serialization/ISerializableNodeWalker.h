//! @file     ISerializableNodeWalker.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ISerializableNodeWalker
//----------------------------------------------------------------------------

class ISerializableNodeWalker : public IObject
{
public:
	//!	Start to walk.
	//!	@param		none.
	//! @return		True indicates there are some files or directories what need to walk, otherwise indicates walk finished.
	virtual _ubool Walk( ) PURE;

	//!	Get the node.
	//!	@param		none.
	//! @return		The node.
	virtual ISerializableNodeRef GetNode( ) PURE;
};

}