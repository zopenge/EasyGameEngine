//! @file     IScriptGeneric.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IScriptGeneric
//----------------------------------------------------------------------------

class IScriptGeneric : public IObject
{
public:
	//!	Get the object.
	//!	@param		none.
	//!	@return		The object pointer.
	virtual _void* GetObject( ) PURE;
	//!	Get the object.
	//!	@param		none.
	//!	@return		The object pointer.
	virtual const _void* GetObject( ) const PURE;

	//!	Set the return value.
	//!	@param		value		The value.
	//!	@return		none.
	virtual _void SetRetValue( const Variable& value ) PURE;
	//!	Get the return value.
	//!	@param		none.
	//!	@return		The value.
	virtual const Variable& GetRetValue( ) const PURE;

	//!	Get the arguments number.
	//!	@param		none.
	//! @return		The arguments number.
	virtual _dword GetArgsNumber( ) const PURE;
	//!	Get the argument by index.
	//! @param		index		The index of arguments.
	//! @return		The value.
	virtual const Variable& GetArgByIndex( _dword index ) const PURE;
};

}