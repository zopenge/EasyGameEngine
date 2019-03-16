//! @file     _scriptHelper.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _scriptHelper
//----------------------------------------------------------------------------

class _scriptHelper
{
public:
	//!	The object behaviour function info
	struct ObjBehaviourFuncInfo
	{
		AStringObj				mName;
		ScriptNativeFuncInfo	mNativeFuncs[ _SCRIPT_CLASS_BEHAVIOUR_MAXNUMBER ];

		operator const AStringObj&( ) const
			{ return mName; }
	};
	typedef Map< ObjBehaviourFuncInfo, AStringObj > ObjBehaviourFuncInfoMap;

private:
	//!	The object behaviours
	static ObjBehaviourFuncInfoMap	sObjBehaviourFuncs;

public:
	//!	Initialize.
	static _ubool Initialize( );
	//!	Finalize.
	static _void Finalize( );

	//!	Add object behaviour function.
	static ObjBehaviourFuncInfo& AddObjBehaviourFunc( AStringPtr name );
	//!	Get object behaviour function.
	static const ObjBehaviourFuncInfo* GetObjBehaviourFunc( AStringPtr name );

	//!	Parse function return type name.
	static AString ParseFuncRetName( AStringPtr declaration );
	//!	Parse function name.
	static AString ParseFuncName( AStringPtr declaration, _ubool with_ret_type_string );
	//!	Parse function arguments.
	static AString ParseFuncArgs( AStringPtr declaration );
	//!	Parse function arguments.
	static _ubool ParseFuncArgs( AStringPtr declaration, AStringArray* types, AStringArray* names );

	//!	Translate internal call type.
	static _SCRIPT_FUNC_INTERNAL_CALL TranslateInternalCallType( const ScriptFuncPtr& funcpointer, const ScriptVarDeclInfo& decl_info );
};

}