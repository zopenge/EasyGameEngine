//! @file     ITUserDataObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITUserDataObject
//----------------------------------------------------------------------------

template< typename Type >
class ITUserDataObject : public Type
{
public:
	//!	Set the user data 1.
	//!	@param		userdata	The user data.
	//!	@return		none.
	virtual _void SetUserData1( _qword userdata ) PURE;
	//!	Get the user data 1.
	//!	@param		none.
	//!	@return		The user data.
	virtual _qword GetUserData1( ) const PURE;

	//!	Set the user data 2.
	//!	@param		userdata	The user data.
	//!	@return		none.
	virtual _void SetUserData2( _qword userdata ) PURE;
	//!	Get the user data 2.
	//!	@param		none.
	//!	@return		The user data.
	virtual _qword GetUserData2( ) const PURE;
};

}