//! @file     ScriptResourceManager.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// ScriptResourceManager Implementation
//----------------------------------------------------------------------------

ScriptResourceManager::ScriptResourceManager( )
{
}

ScriptResourceManager::~ScriptResourceManager( )
{
	Finalize( );
}

ScriptVarDeclInfo::_TYPE ScriptResourceManager::ParseArgType( AStringPtr type ) const
{
	if ( type == "void" || type == "_void" )
	{
		return ScriptVarDeclInfo::_TYPE_VOID;
	}
	else if ( type == "AStringPtr" )
	{
		return ScriptVarDeclInfo::_TYPE_ASTRING_PTR;
	}
	else if ( type == "UStringPtr" )
	{
		return ScriptVarDeclInfo::_TYPE_USTRING_PTR;
	}
	else if ( type == "WStringPtr" )
	{
		return ScriptVarDeclInfo::_TYPE_WSTRING_PTR;
	}
	else if ( type == "int" || type == "_int" || type == "_int" )
	{
		return ScriptVarDeclInfo::_TYPE_INT32;
	}
	else if ( type == "uint" || type == "_dword" )
	{
		return ScriptVarDeclInfo::_TYPE_UINT32;
	}
	else if ( type == "ubool" || type == "_ubool" )
	{
		return ScriptVarDeclInfo::_TYPE_UBOOL;
	}
	else if ( type == "float" || type == "_float" )
	{
		return ScriptVarDeclInfo::_TYPE_FLOAT;
	}
	else if ( type == "double" || type == "_double" )
	{
		return ScriptVarDeclInfo::_TYPE_DOUBLE;
	}
	else if ( type.EndsWith( "*" ) )
	{
		return ScriptVarDeclInfo::_TYPE_OBJECT;
	}

	// Check whether it's class
	IScriptClassRef script_class = GetRegisteredClassByName( type );
	if ( script_class.IsValid( ) )
	{
		// Check whether it's enum or class
		if ( script_class->GetDeclInfo( ).mSize == 0 )
			return ScriptVarDeclInfo::_TYPE_INT32;

		return ScriptVarDeclInfo::_TYPE_CLASS;
	}

	return ScriptVarDeclInfo::_TYPE_UNKNOWN;
}

_dword ScriptResourceManager::GetArgSize( const ScriptVarDeclInfo& arg ) const
{
	switch ( arg.mTypeID )
	{
		case ScriptVarDeclInfo::_TYPE_VOID:
			return 0;

		case ScriptVarDeclInfo::_TYPE_INT8:
			return sizeof( _tiny );

		case ScriptVarDeclInfo::_TYPE_INT16:
			return sizeof( _short );

		case ScriptVarDeclInfo::_TYPE_INT32:
			return sizeof( _int );

		case ScriptVarDeclInfo::_TYPE_UINT8:
			return sizeof( _byte );

		case ScriptVarDeclInfo::_TYPE_UINT16:
			return sizeof( _word );

		case ScriptVarDeclInfo::_TYPE_UBOOL:
		case ScriptVarDeclInfo::_TYPE_UINT32:
			return sizeof( _dword );

		case ScriptVarDeclInfo::_TYPE_FLOAT:
			return sizeof( _float );

		case ScriptVarDeclInfo::_TYPE_DOUBLE:
			return sizeof( _double );

		case ScriptVarDeclInfo::_TYPE_CLASS:
		{
			IScriptClassRef script_class = GetRegisteredClassByName( arg.mTypeName.Str( ) );
			EGE_ASSERT( script_class.IsValid( ) );

			_dword size = script_class->GetDeclInfo( ).mSize;
			EGE_ASSERT( size != 0 );

			return size;
		}
		break;

		case ScriptVarDeclInfo::_TYPE_OBJECT:
			return sizeof( _void* );

		case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:
		case ScriptVarDeclInfo::_TYPE_USTRING_PTR:
		case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:
			return 4;

		default:
			EGE_ASSERT( 0 );
			break;
	}

	return 0;
}

_dword ScriptResourceManager::GetArgsSize( const ScriptVarDeclInfoArray& args ) const
{
	_dword size = 0;
	for ( _dword i = 0; i < args.Number( ); i ++ )
		size += GetArgSize( args[i] );

	return size;
}

_ubool ScriptResourceManager::ParseFuncArgs( AStringPtr declaration, ScriptVarDeclInfoArray& args ) const
{
	AStringArray arg_types;
	if ( _scriptHelper::ParseFuncArgs( declaration, &arg_types, _null ) == _false )
		return _false;

	for ( _dword i = 0; i < arg_types.Number( ); i ++ )
	{
		ScriptVarDeclInfo::_TYPE arg_type = ParseArgType( arg_types[i] );
		if ( arg_type == ScriptVarDeclInfo::_TYPE_UNKNOWN )
		{
			ALOG_ERROR_1( "Parse function argument failed, '%s' is unknown type", arg_types[i].Str( ) );
			return _false;
		}

		args.Append( ScriptVarDeclInfo( arg_type, arg_types[i] ) );
	}

	return _true;
}

_ubool ScriptResourceManager::ParseFuncDecl( AStringPtr declaration, ScriptFuncDeclInfo& decl_info ) const
{
	// Get the function return name
	AString ret_name = _scriptHelper::ParseFuncRetName( declaration );
	if ( ret_name.IsEmpty( ) )
		return _false;

	// Parse return type 
	decl_info.mRetDecl.mTypeID = ParseArgType( ret_name );
	if ( decl_info.mRetDecl.mTypeID == ScriptVarDeclInfo::_TYPE_UNKNOWN )
	{
		ALOG_ERROR_1( "The function's return type '%s' is unknown type", ret_name.Str( ) );
		return _false;
	}

	// Get the return type name
	decl_info.mRetDecl.mTypeName = ret_name.TrimRight( '*' );
	if ( decl_info.mRetDecl.mTypeName.IsEmpty( ) )
	{
		ALOG_ERROR( "The function's return type is missing" );
		return _false;
	}

	// Parse function name
	AString func_name = _scriptHelper::ParseFuncName( declaration, _false );
	if ( func_name.IsEmpty( ) )
		return _false;

	decl_info.mName = func_name;

	// Parse function arguments
	if ( ParseFuncArgs( declaration, decl_info.mParametersDecls ) == _false )
		return _false;

	return _true;
}

_ubool ScriptResourceManager::ParseNativeProperty( AStringPtr declaration, ScriptPropertyDeclInfo& property_info ) const
{
	AStringArray string_list;
	if ( StringFormatter::SplitString( declaration, string_list, " \t", " \t" ) != 2 )
		return _false; // The property must be have both type and name

	property_info.mTypeID		= ParseArgType( string_list[0] );
	property_info.mTypeName		= string_list[0];
	property_info.mPropertyName	= string_list[1];

	return _true;
}

_ubool ScriptResourceManager::ParseNativeFunc( AStringPtr declaration, const ScriptFuncPtr& funcpointer, ScriptNativeFuncInfo& native_func_info ) const
{
	ScriptFuncDeclInfo decl_info;
	if ( ParseFuncDecl( declaration, decl_info ) == _false )
		return _false;

	return ParseNativeFunc( declaration, funcpointer, native_func_info );
}

_ubool ScriptResourceManager::ParseNativeFunc( const ScriptFuncDeclInfo& decl_info, const ScriptFuncPtr& funcpointer, ScriptNativeFuncInfo& native_func_info ) const
{
	if ( decl_info.mRetDecl.HasObj( ) )
		native_func_info.mRetFlags.CombineFlags( ScriptNativeFuncInfo::_RET_FLAG_AS_OBJECT_HANDLE );
	else if ( decl_info.mRetDecl.mTypeID == ScriptVarDeclInfo::_TYPE_FLOAT )
		native_func_info.mRetFlags.CombineFlags( ScriptNativeFuncInfo::_RET_FLAG_AS_FLOAT );

	native_func_info.mBaseOffset		= (_dword) MULTI_BASE_OFFSET( funcpointer );
	native_func_info.mParamSize			= GetArgsSize( decl_info.mParametersDecls );
	native_func_info.mFuncPointer		= (size_t) funcpointer.ptr.f.func;
	native_func_info.mHostReturnSize	= GetArgSize( decl_info.mRetDecl );
	native_func_info.mCallConv			= _scriptHelper::TranslateInternalCallType( funcpointer, decl_info.mRetDecl );

	return _true;
}

_ubool ScriptResourceManager::Initialize( )
{
	return _true;
}

_void ScriptResourceManager::Finalize( )
{
	mClasses.Clear( );
}

IScriptClassRef ScriptResourceManager::RegisterClass( AStringPtr name, AStringPtr desc, _dword size )
{
	// Create virtual machine
	ScriptClass* script_class = new ScriptClass( );
	if ( script_class->Initialize( name, desc, size ) == _false )
		{ EGE_RELEASE( script_class ); return _null; }

	// Get the name object
	AStringObj name_obj = name;

	// Update class info
	ClassInfo& class_info	= mClasses[ name_obj ];
	class_info.mName		= name_obj;
	class_info.mObject		= script_class;

	return script_class;
}

IScriptClassRef ScriptResourceManager::GetRegisteredClassByName( AStringPtr name ) const
{
	AStringObj name_obj = name;

	const ClassInfo* class_info = mClasses.Search( name_obj );
	if ( class_info == _null )
		return _null;

	return class_info->mObject;
}

_ubool ScriptResourceManager::RegisterClassFunction( AStringPtr name, AStringPtr decl, const ScriptFuncPtr& funcpointer, AStringPtr desc )
{
	IScriptClassRef script_class = GetRegisteredClassByName( name );
	if ( script_class.IsNull( ) )
		return _false;

	return script_class->RegisterFunction( decl, funcpointer, desc );
}

_ubool ScriptResourceManager::RegisterBehaviourFunction( AStringPtr name, _SCRIPT_CLASS_BEHAVIOUR behaviour, const ScriptFuncPtr& funcpointer )
{
	// Add behaviour info
	_scriptHelper::ObjBehaviourFuncInfo& obj_behaviour_info = _scriptHelper::AddObjBehaviourFunc( name );

	// Build function declaration info
	ScriptFuncDeclInfo decl_info;
	decl_info.mRetDecl.mTypeName = name;

	if ( behaviour == _SCRIPT_CLASS_CONSTRUCTOR )
	{
		decl_info.mRetDecl.mTypeID = ScriptVarDeclInfo::_TYPE_CLASS;
	}
	else if ( behaviour == _SCRIPT_CLASS_DESTRUCTOR )
	{
		decl_info.mParametersDecls.Append( ScriptVarDeclInfo( ScriptVarDeclInfo::_TYPE_OBJECT, name ) );
		decl_info.mRetDecl.mTypeID = ScriptVarDeclInfo::_TYPE_VOID;
	}

	// Parse native function
	if ( ParseNativeFunc( decl_info, funcpointer, obj_behaviour_info.mNativeFuncs[ behaviour ] ) == _false )
		return _false;

	return _true;
}

_ubool ScriptResourceManager::HasRegisteredClass( AStringPtr name ) const
{
	if ( mClasses.HasKey( name ) == _false )
		return _false;

	return _true;
}

_ubool ScriptResourceManager::InvokeConstructorBehaviourFunc( _byte*& object, AStringPtr name )
{
	// Get the behaviour info
	const _scriptHelper::ObjBehaviourFuncInfo* obj_behaviour_info = _scriptHelper::GetObjBehaviourFunc( name );
	if ( obj_behaviour_info == _null )
		return _false;

	// Invoke behaviour function
	ScriptVMRegisters registers;
	_scriptCallFunc::CallFunction( registers, _null, obj_behaviour_info->mNativeFuncs[ _SCRIPT_CLASS_CONSTRUCTOR ] );

	// Feedback the object
	object = (_byte*) registers.mObjectRegister;

	return _true;
}

_ubool ScriptResourceManager::InvokeDestructorBehaviourFunc( _byte*& object, AStringPtr name )
{
	// Get the behaviour info
	const _scriptHelper::ObjBehaviourFuncInfo* obj_behaviour_info = _scriptHelper::GetObjBehaviourFunc( name );
	if ( obj_behaviour_info == _null )
		return _false;

	ScriptVMRegisters registers;

	// Invoke behaviour function
	_scriptCallFunc::CallFunction( registers, _null, obj_behaviour_info->mNativeFuncs[ _SCRIPT_CLASS_DESTRUCTOR ], object );

	// Clear object
	object = _null;

	return _true;
}

_ubool ScriptResourceManager::InvokeCopyBehaviourFunc( _byte*& object, const _byte* from_object, AStringPtr name )
{
	// Get the object class
	IScriptClassRef obj_class = GetRegisteredClassByName( name );
	if ( obj_class.IsNull( ) )
		return _false;

	// Copy the object info
	EGE_MEM_CPY( object, from_object, obj_class->GetDeclInfo( ).mSize );

	return _true;
}

_ubool ScriptResourceManager::ParseNativePropertyInfo( AStringPtr declaration, _dword offset, ScriptPropertyDeclInfo& decl_info ) const
{
	// Initialize property declaration
	decl_info.mOffset = offset;

	// Parse property declaration
	if ( ParseNativeProperty( declaration, decl_info ) == _false )
		return _false;

	return _true;
}

_ubool ScriptResourceManager::ParseNativeFuncInfo( AStringPtr declaration, const ScriptFuncPtr& funcpointer, ScriptFuncDeclInfo& decl_info, ScriptNativeFuncInfo& native_func_info ) const
{
	// Initialize function declaration
	decl_info.mCallType = (_SCRIPT_FUNC_CALL) funcpointer.call_type;

	// Parse function declaration
	if ( ParseFuncDecl( declaration, decl_info ) == _false )
		return _false;

	// Parse native function
	if ( ParseNativeFunc( decl_info, funcpointer, native_func_info ) == _false )
		return _false;

	return _true;
}

IScriptVMPassRef ScriptResourceManager::CreateScriptVM( )
{
	// Create virtual machine
	ScriptVM* script_vm = new ScriptVM( );
	if ( script_vm->Initialize( ) == _false )
		{ EGE_RELEASE( script_vm ); return _null; }

	return script_vm;
}

_ubool ScriptResourceManager::PreloadModule( AStringPtr name, AStringPtr code )
{
	return gInternalScriptSystem->PreloadModule( name, code );
}