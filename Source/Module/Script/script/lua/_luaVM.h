//! @file     _luaVM.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _luaVM
//----------------------------------------------------------------------------

class _luaVM : public TObject< _scriptVM >
{
private:

public:
	_luaVM( );
	virtual ~_luaVM( );

public:
	//!	Initialize.
	_ubool Initialize( );

// _scriptVM Interface
public:
	virtual _scriptFunctionPassRef	GetScriptFunction( AStringPtr func_name ) override;

	virtual _ubool					LoadFromBuffer( const _byte* buffer, _dword size, AStringPtr filename ) override;
};

}