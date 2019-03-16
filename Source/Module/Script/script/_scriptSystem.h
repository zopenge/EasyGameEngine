//! @file     _scriptSystem.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _scriptValue
//----------------------------------------------------------------------------

class _scriptValue : public IObject
{
public:
	//!	Get the pointer.
	//!	@param		none.
	//!	@return		The pointer.
	virtual const _void* GetPointer( ) const PURE;

	//!	Get the number.
	//!	@param		none.
	//!	@return		The number.
	virtual _double GetDouble( ) const PURE;
	
	//!	Get the string.
	//!	@param		none.
	//!	@return		The string.
	virtual WStringR GetStringW( ) const PURE;
};

//----------------------------------------------------------------------------
// _scriptFunction
//----------------------------------------------------------------------------

class _scriptFunction : public IObject
{
public:
	//!	Get the name.
	//!	@param		none.
	//!	@return		The name.
	virtual AStringPtr GetName( ) const PURE;

	//!	Invoke.
	//!	@param		none.
	//! @return		The return variable.
	virtual _scriptValuePassRef Invoke( ) PURE;
	//!	Invoke.
	//!	@param		vars	The parameters.
	//! @return		The return variable.
	virtual _scriptValuePassRef Invoke( const VariableArray& vars ) PURE;
};

//----------------------------------------------------------------------------
// _scriptModule
//----------------------------------------------------------------------------

class _scriptModule : public IObject
{
public:
	//!	Get the name.
	//!	@param		none.
	//!	@return		The name.
	virtual AStringPtr GetName( ) const PURE;
	//!	Get the name object.
	//!	@param		none.
	//!	@return		The name object.
	virtual const AStringObj& GetNameObj( ) const PURE;

	//!	Register enumeration value.
	//!	@param		name			The enumeration name.
	//!	@param		value			The enumeration value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RegisterEnumValue( AStringPtr name, _dword value ) PURE;
	//!	Register native property.
	//!	@param		decl_info			The property declaration info.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RegisterProperty( const ScriptPropertyDeclInfo& decl_info ) PURE;
	//!	Register native function.
	//!	@param		decl_info			The function declaration info.
	//!	@param		native_func_info	The function native info.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RegisterFunction( const ScriptFuncDeclInfo& decl_info, const ScriptNativeFuncInfo& native_func_info ) PURE;
};

//----------------------------------------------------------------------------
// _scriptVM
//----------------------------------------------------------------------------

class _scriptVM : public IObject
{
public:
	//!	Get script function.
	//!	@param		func_name	The function name of script.
	//!	@return		The function interface.
	virtual _scriptFunctionPassRef GetScriptFunction( AStringPtr func_name ) PURE;

	//!	Load script from buffer.
	//!	@param		buffer		The buffer data.
	//!	@param		size		The buffer size.
	//!	@param		filename	The file name, just for debugger usage, can be empty.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool LoadFromBuffer( const _byte* buffer, _dword size, AStringPtr filename ) PURE;
};

//----------------------------------------------------------------------------
// _scriptSystem
//----------------------------------------------------------------------------

class _scriptSystem : public IObject
{
public:
	//!	Initialize.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Initialize( ) PURE;

	//!	Get the total memory size in bytes.
	//!	@param		none.
	//!	@return		The memory size in bytes.
	virtual _dword GetTotalMemSize( ) const PURE;

	//!	Set the remote debugger.
	//!	@param		address		The remote address.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool SetRemoteDebugger( const Address& address ) PURE;
	//!	Get the remote debugger.
	//!	@param		none.
	//!	@return		The remote address.
	virtual const Address& GetRemoteDebugger( ) const PURE;

	//!	Preload module.
	//!	@param		name	The module name.
	//!	@param		code	The script code.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool PreloadModule( AStringPtr name, AStringPtr code ) PURE;

	//!	Create script module.
	//!	@param		name	The module name.
	//!	@param		desc	The module description.
	//!	@return		The script module interface.
	virtual _scriptModuleRef CreateScriptModule( AStringPtr name, AStringPtr desc ) PURE;

	//!	Create script VM.
	//!	@param		none.
	//!	@return		The script VM interface.
	virtual _scriptVMPassRef CreateScriptVM( ) PURE;
};

}