//! @file     ITShowableObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITShowableObject
//----------------------------------------------------------------------------

template< typename Type >
class ITShowableObject : public Type
{
public:
	//!	Show/Hide.
	//!	@param		show		True indicates show it, otherwise hide it.
	//!	@return		none.
	virtual _void Show( _ubool show ) PURE;
	//!	Check whether it is showing or not.
	//!	@param		none.
	//!	@return		True indicates showing.
	virtual _ubool IsShow( ) const PURE;
};

}