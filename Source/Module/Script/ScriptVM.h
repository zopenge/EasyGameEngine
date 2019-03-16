//! @file     ScriptVM.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ScriptVM
//----------------------------------------------------------------------------

class ScriptVM : public TObject< IScriptVM >
{
private:
	//!	The registers info
	ScriptVMRegisters		mRegistersInfo;
	//!	The exception info
	ScriptVMExceptionInfo	mExceptionInfo;

	//!	The script VM
	_scriptVMRef			mVM;

public:
	ScriptVM( );
	virtual ~ScriptVM( );

public:
	//!	Initialize.
	_ubool Initialize( );

// IScriptVM Interface
public:
	virtual ScriptVMRegisters&				GetRegisters( ) override;
	virtual const ScriptVMRegisters&		GetRegisters( ) const override;

	virtual _void							SetExceptionInfo( const ScriptVMExceptionInfo& info ) override;
	virtual const ScriptVMExceptionInfo&	GetExceptionInfo( ) const override;

	virtual _ubool							LoadFromResName( WStringPtr res_name ) override;

	virtual IScriptFunctionPassRef			GetScriptFunction( AStringPtr func_name ) override;
};

}