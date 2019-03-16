//! @file     ITEnable.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITEnable
//----------------------------------------------------------------------------

template< typename Type >
class ITEnable : public Type
{
public:
	//!	Enable.
	//!	@param		enable		enable or not.
	//!	@return		none.
	virtual _void Enable( _ubool enable ) PURE;
	//!	Check whether it's active or not.
	//!	@param		none.
	//!	@return		True indicates it's active.
	virtual _ubool IsEnable( ) const PURE;
};

}