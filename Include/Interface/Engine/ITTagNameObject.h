//! @file     ITTagNameObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITTagNameObject
//----------------------------------------------------------------------------

template< typename Type >
class ITTagNameObject : public Type
{
public:
	//!	Set the tag name.
	//!	@param		name	The tag name.
	//!	@return		none.
	virtual _void SetTagName( WStringPtr name ) PURE;
	//!	Get the tag name.
	//!	@param		none.
	//!	@return		The tag name.
	virtual WStringPtr GetTagName( ) const PURE;
};

}