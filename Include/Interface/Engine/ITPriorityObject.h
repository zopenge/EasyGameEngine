//! @file     ITPriorityObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITPriorityObject
//----------------------------------------------------------------------------

template< typename Type >
class ITPriorityObject : public Type
{
public:
	//!	Set the priority.
	//!	@param		priority	The priority.
	//!	@return		none.
	virtual _void SetPriority( _int priority ) PURE;
	//!	Get the priority.
	//!	@param		none.
	//!	@return		The priority.
	virtual _int GetPriority( ) const PURE;
};

}