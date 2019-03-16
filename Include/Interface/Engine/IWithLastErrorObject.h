//! @file     IWithLastErrorObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IWithLastErrorObject
//----------------------------------------------------------------------------

template< typename Type >
class IWithLastErrorObject : public Type
{
public:
	//!	Set the last error ID.
	//!	@param		errorid		The last error ID of task.
	//! @return		none.
	virtual _void SetLastErrorID( _dword errorid ) PURE;
	//!	Get the last error ID.
	//!	@param		none.
	//! @return		The last error ID of task.
	virtual _dword GetLastErrorID( ) PURE;
};

}