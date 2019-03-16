//! @file     ITPowerable.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITPowerable
//----------------------------------------------------------------------------

template< typename Type >
class ITPowerable : public Type
{
public:
	//!	Power on.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool PowerOn( ) PURE;
	//!	Power off.
	//!	@param		none.
	//! @return		none.
	virtual _void PowerOff( ) PURE;

	//!	Check whether it's power on.
	//!	@param		none.
	//! @return		True indicates power on, otherwise indicates power off.
	virtual _ubool IsPowerOn( ) const PURE;
	//!	Check whether it's power off.
	//!	@param		none.
	//! @return		True indicates power off, otherwise indicates power on.
	virtual _ubool IsPowerOff( ) const PURE;
};

}