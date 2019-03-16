//! @file     _pyVM.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _pyVM
//----------------------------------------------------------------------------

class _pyVM : public TObject< _scriptVM >
{
private:
	//!	The module name ( use the unique UID128 as module name )
	AString		mModuleName;

	//!	The python module object
	PyObject*	mPyModuleObject;
	//! The python compiled code object (bytecode)
	PyObject*	mPyCodeObject;

public:
	_pyVM( );
	virtual ~_pyVM( );

public:
	//!	Initialize.
	_ubool Initialize( );

// _scriptVM Interface
public:
	virtual _scriptFunctionPassRef	GetScriptFunction( AStringPtr func_name ) override;

	virtual _ubool					LoadFromBuffer( const _byte* buffer, _dword size, AStringPtr filename ) override;
};

}