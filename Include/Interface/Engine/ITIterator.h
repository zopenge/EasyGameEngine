//! @file     ITIterator.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITIterator
//----------------------------------------------------------------------------

template< typename ObjectType, typename Type >
class ITIterator : public Type
{
public:
	//!	Get the object interface.
	//!	@param		none.
	//!	@return		The object interface.
	virtual ObjectType GetObject( ) PURE;
	//!	Check whether has object or not.
	//!	@param		none.
	//!	@return		True indicates has object.
	virtual _ubool HasObject( ) const PURE;

	//!	Move to the previous element.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool MovePrev( ) PURE;
	//!	Move to the next element.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool MoveNext( ) PURE;
};

}