//! @file     ITNameObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITNameObject
//----------------------------------------------------------------------------

template< typename Type >
class ITNameObject : public Type
{
public:
	//!	Set the name.
	//!	@param		name	The name.
	//!	@return		none.
	virtual _void SetName( WStringPtr name ) PURE;
	//!	Get the name.
	//!	@param		none.
	//!	@return		The name.
	virtual WStringPtr GetName( ) const PURE;
};

}