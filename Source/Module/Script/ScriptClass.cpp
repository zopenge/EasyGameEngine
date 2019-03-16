//! @file     ScriptClass.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// ScriptClass Implementation
//----------------------------------------------------------------------------

ScriptClass::ScriptClass( )
{
}

ScriptClass::~ScriptClass( )
{
}

_ubool ScriptClass::Initialize( AStringPtr name, AStringPtr desc, _dword size )
{
	if ( name.IsEmpty( ) )
		return _false;

	mDeclInfo.mName = name;
	mDeclInfo.mDesc = desc;
	mDeclInfo.mSize	= size;

	mScriptModule = gInternalScriptSystem->CreateScriptModule( name, desc );
	if ( mScriptModule.IsNull( ) )
		return _false;

	return _true;
}

_ubool ScriptClass::RegisterEnumValue( AStringPtr name, _dword value, AStringPtr desc )
{
	if ( mScriptModule->RegisterEnumValue( name, value ) == _false )
		return _false;

	return _true;
}

_ubool ScriptClass::RegisterProperty( AStringPtr decl, _dword offset, AStringPtr desc )
{
	ScriptPropertyDeclInfo decl_info;
	if ( GetScriptResourceManager( )->ParseNativePropertyInfo( decl, offset, decl_info ) == _false )
		return _false;

	if ( mScriptModule->RegisterProperty( decl_info ) == _false )
		return _false;

	return _true;
}

const ScriptClassDeclInfo& ScriptClass::GetDeclInfo( ) const
{
	return mDeclInfo;
}

_ubool ScriptClass::RegisterFunction( AStringPtr decl, const ScriptFuncPtr& funcpointer, AStringPtr desc )
{
	ScriptFuncDeclInfo		decl_info;
	ScriptNativeFuncInfo	native_func_info;
	if ( GetScriptResourceManager( )->ParseNativeFuncInfo( decl, funcpointer, decl_info, native_func_info ) == _false )
		return _false;

	if ( mScriptModule->RegisterFunction( decl_info, native_func_info ) == _false )
		return _false;

	return _true;
}