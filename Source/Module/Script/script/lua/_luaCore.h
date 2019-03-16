//! @file     _luaCore.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _luaCore
//----------------------------------------------------------------------------

class _luaCore
{
	SINGLETON( _luaCore )

private:
	//!	The required files list
	AStringArray	mRequiredFiles;

private:
	//!	Load script file as string.
	_ubool ReadScriptString( AStringPtr filename, AString& string );

private:
	//!	Require other lua file.
	static _int OnRequireCallback( lua_State* l );

	//!	Print log.
	static _int OnPrintCallback( lua_State* l );

public:
	//!	Initialize.
	_ubool Initialize( );
	//!	Finalize.
	_void Finalize( );

	//!	Add required file.
	_void AddRequiredFile( AStringPtr filename );
};

}