//! @file     _scriptHelper.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

_scriptHelper::ObjBehaviourFuncInfoMap	_scriptHelper::sObjBehaviourFuncs;

//----------------------------------------------------------------------------
// _scriptHelper Implementation
//----------------------------------------------------------------------------

_ubool _scriptHelper::Initialize( )
{
	return _true;
}

_void _scriptHelper::Finalize( )
{
	sObjBehaviourFuncs.Clear( );
}

_scriptHelper::ObjBehaviourFuncInfo& _scriptHelper::AddObjBehaviourFunc( AStringPtr name )
{
	AStringObj name_obj = name;

	// Build behaviour info
	ObjBehaviourFuncInfo& obj_behaviour_info	= sObjBehaviourFuncs[ name_obj ];
	obj_behaviour_info.mName					= name_obj;

	return obj_behaviour_info;
}

const _scriptHelper::ObjBehaviourFuncInfo* _scriptHelper::GetObjBehaviourFunc( AStringPtr name )
{
	AStringObj name_obj = name;

	// Get the behaviour info
	return sObjBehaviourFuncs.Search( name_obj );
}

AString _scriptHelper::ParseFuncRetName( AStringPtr declaration )
{
	// Local at ' ' or '\t'
	_dword index = declaration.SearchL2R( ' ' );
	if ( index == -1 )
	{
		index = declaration.SearchL2R( '\t' );
		if ( index == -1 )
			return AString( "" );
	}

	return AString( declaration.Str( ), index );
}

AString _scriptHelper::ParseFuncName( AStringPtr declaration, _ubool with_ret_type_string )
{
	const _chara* start_decl = declaration.Str( );

	// Skip the unused symbols
	while ( start_decl[0] == '\r' || start_decl[0] == '\n' || start_decl[0] == '\t' || start_decl[0] == ' ' )
		start_decl ++;

	// Local at '('
	_dword index = Platform::SearchL2R( start_decl, '(' );
	if ( index == -1 || index == 0 )
		return AString( "" );

	// Get function name
	AString func_name( declaration.Str( ), index );

	// Remove the return type string
	if ( with_ret_type_string == _false )
	{
		while ( func_name.GetLength( ) > 0 && ( func_name[0] != '\t' && func_name[0] != ' ' ) )
			func_name.Remove( 0, 1 );
	}

	func_name.TrimBoth( " \t" );

	return func_name;
}

AString _scriptHelper::ParseFuncArgs( AStringPtr declaration )
{
	// Search for the left and right bracket
	_dword leftbracket	= declaration.SearchL2R( '(' );
	_dword rightbracket = declaration.SearchL2R( ')' );
	if ( leftbracket == -1 || rightbracket == -1 )
		return AString( "" );

	// Get function declaration length
	_dword length = rightbracket - leftbracket - 1;
	if ( length == 0 )
		return AString( "" );

	// Get the arguments
	return AString( declaration.SubString( leftbracket + 1 ).Str( ), length );
}

_ubool _scriptHelper::ParseFuncArgs( AStringPtr declaration, AStringArray* types, AStringArray* names )
{
	// Get the function arguments string
	AString func_args_string = ParseFuncArgs( declaration );
	if ( func_args_string.IsEmpty( ) )
		return _true; // no any arguments

	// Split function declaration
	AStringArray args;
	_dword args_number = StringFormatter::SplitString( func_args_string, args, ",", " \t" );

	// Feedback arguments info
	for ( _dword i = 0; i < args_number; i ++ )
	{
		AStringArray arg;
		if ( StringFormatter::SplitString( args[i], arg, " \t", " \t" ) == 0 )
			continue;

		if ( types != _null )
			types->Append( arg[0] );

		if ( names != _null )
		{
			if ( arg.Number( ) > 1 )
				names->Append( arg[1] );
			else
				names->Append( AStringPtr( "" ) );
		}
	}

	return _true;
}

_SCRIPT_FUNC_INTERNAL_CALL _scriptHelper::TranslateInternalCallType( const ScriptFuncPtr& funcpointer, const ScriptVarDeclInfo& decl_info )
{
	switch ( funcpointer.call_type )
	{
		case _SCRIPT_FUNC_CALL_CDECL:
		{
			if ( decl_info.IsReturnInMem( ) )
			{
				return _SCRIPT_FUNC_INTERNAL_CALL_CDECL_RETURN_IN_MEM;
			}
			else
			{
				return _SCRIPT_FUNC_INTERNAL_CALL_CDECL;
			}
		}
		break;

		case _SCRIPT_FUNC_CALL_STDCALL:
		{
			return _SCRIPT_FUNC_INTERNAL_CALL_STDCALL;
		}
		break;

		case _SCRIPT_FUNC_CALL_THISCALL:
		{
			if ( decl_info.IsReturnInMem( ) )
			{
#if defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_)
				_int base_offset = (_int) MULTI_BASE_OFFSET( funcpointer );
				if( base_offset & 1 )
					return _SCRIPT_FUNC_INTERNAL_CALL_VIRTUAL_THISCALL_RETURN_IN_MEM;
#endif
				return _SCRIPT_FUNC_INTERNAL_CALL_THISCALL_RETURN_IN_MEM;
			}
			else
			{
#if defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_)
				_int base_offset = (_int) MULTI_BASE_OFFSET( funcpointer );
				if( base_offset & 1 )
					return _SCRIPT_FUNC_INTERNAL_CALL_VIRTUAL_THISCALL;
#endif
				return _SCRIPT_FUNC_INTERNAL_CALL_THISCALL;
			}
		}
		break;

		default:
			break;
	}

	return _SCRIPT_FUNC_INTERNAL_CALL_UNKNOWN;
}