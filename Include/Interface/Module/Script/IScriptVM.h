//! @file     IScriptVM.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IScriptVM
//----------------------------------------------------------------------------

class IScriptVM : public IObject
{
public:
	//!	Get registers info.
	//!	@param		none.
	//!	@return		The registers info.
	virtual ScriptVMRegisters& GetRegisters( ) PURE;
	//!	Get registers info.
	//!	@param		none.
	//!	@return		The registers info.
	virtual const ScriptVMRegisters& GetRegisters( ) const PURE;

	//!	Set the exception info.
	//!	@param		info			The exception info.
	//!	@return		none.
	virtual _void SetExceptionInfo( const ScriptVMExceptionInfo& info ) PURE;
	//!	Get the exception info.
	//!	@param		none.
	//!	@return		The exception info.
	virtual const ScriptVMExceptionInfo& GetExceptionInfo( ) const PURE;

	//!	Load script from resource name.
	//!	@param		res_name	The resource name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool LoadFromResName( WStringPtr res_name ) PURE;

	//!	Get script function.
	//!	@param		func_name		The function name of script.
	//!	@return		The function interface.
	virtual IScriptFunctionPassRef GetScriptFunction( AStringPtr func_name ) PURE;
};

}