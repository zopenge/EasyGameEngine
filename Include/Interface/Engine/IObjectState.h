//! @file     IObjectState.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IObjectState
//----------------------------------------------------------------------------

class IObjectState : public IObject
{
public:
	//!	Set the object state.
	//!	@param		state		The state of object.
	//!	@return		none.
	virtual _void SetObjectState( _OBJECT_STATE state ) PURE;
	//!	Get the object state.
	//!	@param		none.
	//!	@return		The state of object.
	virtual _OBJECT_STATE GetObjectState( ) const PURE;
};

}