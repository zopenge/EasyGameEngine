//! @file     ScriptParser.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// ScriptParser Implementation
//----------------------------------------------------------------------------

ScriptParser::ScriptParser( )
{

}

ScriptParser::~ScriptParser( )
{

}

_ubool ScriptParser::BuildNativeFuncInfo( WStringPtr decl, const ScriptFuncPtr& func, ScriptNativeFuncInfo& native_func_info )
{
	return _true;
}

_dword ScriptParser::BuildNativeFuncID( const ScriptNativeFuncInfo& info )
{
	return 0;
}

_dword ScriptParser::BuildNativeFuncID( IScriptClass* script_class, const ScriptNativeFuncInfo& info )
{
	return 0;
}

_dword ScriptParser::BuildNativeFuncID( IScriptClass* script_class, _SCRIPT_CLASS_BEHAVIOUR behaviour, const ScriptNativeFuncInfo& info )
{
	return 0;
}