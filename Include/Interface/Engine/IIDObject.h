//! @file     IIDObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IIDObject
//----------------------------------------------------------------------------

template< typename Type >
class IIDObject : public Type
{
public:
	//!	Get ID.
	//!	@param		none.
	//!	@return		The ID.
	virtual _dword GetID( ) const PURE;
	//!	Set ID.
	//!	@param		id		The ID.
	//!	@return		none.
	virtual _void SetID( _dword id ) PURE;
};

}