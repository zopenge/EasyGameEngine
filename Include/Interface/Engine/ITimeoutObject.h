//! @file     ITimeoutObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITimeoutObject
//----------------------------------------------------------------------------

template< typename Type >
class ITimeoutObject : public Type
{
public:
	//!	Set the timeout.
	//!	@param		timeout		The timeout of task in milliseconds, -1 indicates never timeout.
	//!	@return		none.
	virtual _void SetTimeout( _dword timeout ) PURE;
	//!	Get the timeout in milliseconds.
	//!	@param		none.
	//!	@return		The timeout of task in milliseconds, -1 indicates never timeout.
	virtual _dword GetTimeout( ) const PURE;
	//!	Check whether it's timeout or not.
	//!	@param		none.
	//!	@return		True indicates it's timeout.
	virtual _ubool IsTimeout( ) const PURE;
};

}