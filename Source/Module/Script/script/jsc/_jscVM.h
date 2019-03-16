//! @file     _jscVM.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _jscVM
//----------------------------------------------------------------------------

class _jscVM : public TObject< _scriptVM >
{
private:
	//!	The JS script execution result
	JSValueRef	mJSResult;

public:
	_jscVM( );
	virtual ~_jscVM( );

public:
	//!	Initialize.
	_ubool Initialize( );

// _scriptVM Interface
public:
	virtual _scriptFunctionPassRef	GetScriptFunction( AStringPtr func_name ) override;

	virtual _ubool					LoadFromBuffer( const _byte* buffer, _dword size, AStringPtr filename ) override;
};

}