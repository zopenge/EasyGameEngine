//! @file     MarkupLangSerializableNodeWalker.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MarkupLangSerializableNodeWalker
//----------------------------------------------------------------------------

class MarkupLangSerializableNodeWalker : public INTERFACE_OBJECT_IMPL( ISerializableNodeWalker )
{
private:
	typedef Stack< ISerializableNodeRef > NodeStack;

private:
	NodeStack	mNodeStack;

public:
	MarkupLangSerializableNodeWalker( ISerializableNode* node );
	virtual ~MarkupLangSerializableNodeWalker( );

// ISerializableNodeWalker Interface
public:
	virtual _ubool					Walk( ) override;

	virtual ISerializableNodeRef	GetNode( ) override;
};

}