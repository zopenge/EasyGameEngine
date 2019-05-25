//! @file     MarkupFileLangFile.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// MarkupLangElementIterator Implementation
//----------------------------------------------------------------------------

MarkupLangElementIterator::MarkupLangElementIterator( IMarkupElement* element ) 
	: mCurElement( element )
{

}

MarkupLangElementIterator::~MarkupLangElementIterator( )
{

}

IMarkupElement*	MarkupLangElementIterator::GetObject( )
{
	return mCurElement;
}

_ubool MarkupLangElementIterator::HasObject( ) const
{
	return mCurElement != _null;
}

_ubool MarkupLangElementIterator::MovePrev( )
{
	if ( HasObject( ) == _false )
		return _false;

	// Find the XML element with the same name
	for ( IMarkupElement* xml_element = mCurElement->GetPrevElement( ); xml_element != _null; xml_element = xml_element->GetPrevElement( ) )
	{
		if ( xml_element->GetName( ) == mCurElement->GetName( ) )
		{
			mCurElement = xml_element;
			return _true;
		}
	}

	// Found nothing
	mCurElement = _null;
	return _false;
}

_ubool MarkupLangElementIterator::MoveNext( )
{
	if ( HasObject( ) == _false )
		return _false;

	// Find the XML element with the same name
	for ( IMarkupElement* xml_element = mCurElement->GetNextElement( ); xml_element != _null; xml_element = xml_element->GetNextElement( ) )
	{
		if ( xml_element->GetName( ) == mCurElement->GetName( ) )
		{
			mCurElement = xml_element;
			return _true;
		}
	}

	// Found nothing
	mCurElement = _null;
	return _false;
}