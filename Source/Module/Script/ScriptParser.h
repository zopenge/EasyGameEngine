//! @file     ScriptParser.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ScriptParser
//----------------------------------------------------------------------------

class ScriptParser
{
private:

public:
	ScriptParser( );
	~ScriptParser( );

public:
	//!	Build native function info by declaration and function pointer.
	static _ubool BuildNativeFuncInfo( WStringPtr decl, const ScriptFuncPtr& func, ScriptNativeFuncInfo& native_func_info );
	//!	Build native function unique ID (with its declaration info).
	static _dword BuildNativeFuncID( const ScriptNativeFuncInfo& info );
	//!	Build native function by class unique ID (with its declaration info).
	static _dword BuildNativeFuncID( IScriptClass* script_class, const ScriptNativeFuncInfo& info );
	//!	Build native function by class's behaviour unique ID (with its declaration info).
	static _dword BuildNativeFuncID( IScriptClass* script_class, _SCRIPT_CLASS_BEHAVIOUR behaviour, const ScriptNativeFuncInfo& info );
};

}