//! @file		ScriptSerialization.cpp
//! @author		Deen
//! @copyright	...
//! @version	1.0.0.0
//! @date		2017/09/12

#include "EGEScript.h"
namespace EGE
{

_dword OnQueryScriptTypeEnumCallback( WStringPtr name )
{
	if ( name == L"UNKNOWN" ) return _SCRIPT_UNKNOWN;
	else if ( name == L"PYTHON" ) return _SCRIPT_PYTHON;
	else if ( name == L"JAVA_SCRIPT" ) return _SCRIPT_JAVA_SCRIPT;
	else if ( name == L"LUA" ) return _SCRIPT_LUA;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryScriptTypeEnumCallback( _dword value )
{
	switch ( value )
	{
		case _SCRIPT_UNKNOWN: return L"UNKNOWN";
		case _SCRIPT_PYTHON: return L"PYTHON";
		case _SCRIPT_JAVA_SCRIPT: return L"JAVA_SCRIPT";
		case _SCRIPT_LUA: return L"LUA";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}

}

