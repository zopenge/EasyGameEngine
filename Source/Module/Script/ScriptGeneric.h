//! @file     ScriptGeneric.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ScriptGeneric
//----------------------------------------------------------------------------

class ScriptGeneric : public TObject< IScriptGeneric >
{
private:
	typedef Array< Variable > VariableArray;

private:
	//!	The object
	_void*			mObject;

	//!	The return value of function
	Variable		mRetValue;
	//!	The arguments of string to keep memory alive
	WStringArray	mStringArgs;
	//!	The arguments of function
	VariableArray	mParameters;

private:
	//!	Initialize parameters.
	_void InitPars( const ScriptVMRegisters& vm_registers, const ScriptFuncDeclInfo& decl_info );

public:
	ScriptGeneric( );
	virtual ~ScriptGeneric( );

public:
	//!	Invoke.
	_ubool Invoke( ScriptVMRegisters& vm_registers, const ScriptFuncDeclInfo* decl_info, const ScriptNativeFuncInfo& func_info, _void* object );

// IScriptGeneric Interface
public:
	virtual _void*			GetObject( ) override;
	virtual const _void*	GetObject( ) const override;

	virtual _void			SetRetValue( const Variable& value ) override;
	virtual const Variable& GetRetValue( ) const override;

	virtual _dword			GetArgsNumber( ) const override;
	virtual const Variable& GetArgByIndex( _dword index ) const override;
};

}