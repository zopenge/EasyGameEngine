//! @file     IScriptValue.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IScriptValue
//----------------------------------------------------------------------------

class IScriptValue : public IObject
{
public:
	//!	Get the pointer.
	//!	@param		none.
	//!	@return		The pointer.
	virtual const _void* GetPointer( ) const PURE;

	//!	Get the boolean value.
	//!	@param		none.
	//!	@return		The boolean value.
	virtual _ubool GetBool( ) const PURE;
	//!	Get the number.
	//!	@param		none.
	//!	@return		The number.
	virtual _double GetDouble( ) const PURE;

	//!	Get the ANSI string.
	//!	@param		none.
	//!	@return		The ANSI string.
	virtual AStringR GetStringA( ) const PURE;
	//!	Get the UTF-8 string.
	//!	@param		none.
	//!	@return		The UTF-8 string.
	virtual UStringR GetStringU( ) const PURE;
	//!	Get the UTF-16 string.
	//!	@param		none.
	//!	@return		The UTF-16 string.
	virtual WStringR GetStringW( ) const PURE;
};

}