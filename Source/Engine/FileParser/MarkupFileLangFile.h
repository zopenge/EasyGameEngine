//! @file     MarkupFileLangFile.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MarkupLangElementIterator
//----------------------------------------------------------------------------

class MarkupLangElementIterator : public INTERFACE_OBJECT_IMPL( IMarkupLangElementIterator )
{
private:
	//!	The current element
	IMarkupElement*	mCurElement;

public:
	MarkupLangElementIterator( IMarkupElement* element );
	virtual ~MarkupLangElementIterator( );

// IIterator Interface
public:
	virtual IMarkupElement*	GetObject( ) override;
	virtual _ubool				HasObject( ) const override;

	virtual _ubool				MovePrev( ) override;
	virtual _ubool				MoveNext( ) override;
};

}