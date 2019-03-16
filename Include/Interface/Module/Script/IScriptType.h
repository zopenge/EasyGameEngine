//! @file     IScriptType.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IScriptType
//----------------------------------------------------------------------------

class IScriptType : public IObject
{
public:
	//!	Get the type ID.
	//! @param		none.
	//! @return		The type ID.
	virtual _SCRIPT_TYPE_ID GetTypeID( ) const PURE;
	//!	Get the type ID string.
	//! @param		none.
	//! @return		The type ID string.
	virtual WStringPtr GetTypeIDString( ) const PURE;
};

}