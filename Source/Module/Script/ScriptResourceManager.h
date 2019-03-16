//! @file     ScriptResourceManager.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ScriptResourceManager
//----------------------------------------------------------------------------

class ScriptResourceManager : public INTERFACE_OBJECT_IMPL( IScriptResourceManager )
{
private:
	//!	The class info
	struct ClassInfo
	{
		AStringObj			mName;
		IScriptClassPassRef	mObject;

		operator const AStringObj&( ) const
			{ return mName; }
	};
	typedef Map< ClassInfo, AStringObj > ClassInfoMap;

private:
	//!	The class
	ClassInfoMap	mClasses;

private:
	//!	Parse argument type.
	ScriptVarDeclInfo::_TYPE ParseArgType( AStringPtr type ) const;
	// Get the argument size in bytes.
	_dword GetArgSize( const ScriptVarDeclInfo& arg ) const;
	// Get the arguments size in bytes.
	_dword GetArgsSize( const ScriptVarDeclInfoArray& args ) const;

	//!	Parse function arguments.
	_ubool ParseFuncArgs( AStringPtr declaration, ScriptVarDeclInfoArray& args ) const;
	//!	Parse function declaration.
	_ubool ParseFuncDecl( AStringPtr declaration, ScriptFuncDeclInfo& decl_info ) const;

	//!	Parse property by declaration.
	_ubool ParseNativeProperty( AStringPtr declaration, ScriptPropertyDeclInfo& property_info ) const;
	//!	Parse function by declaration.
	_ubool ParseNativeFunc( AStringPtr declaration, const ScriptFuncPtr& funcpointer, ScriptNativeFuncInfo& native_func_info ) const;
	_ubool ParseNativeFunc( const ScriptFuncDeclInfo& declaration, const ScriptFuncPtr& funcpointer, ScriptNativeFuncInfo& native_func_info ) const;

public:
	ScriptResourceManager( );
	virtual ~ScriptResourceManager( );

public:
	//!	Initialize.
	_ubool Initialize( );
	//!	Finalize.
	_void Finalize( );

// IScriptResourceManager Interface
public:
	virtual IScriptClassRef		RegisterClass( AStringPtr name, AStringPtr desc, _dword size ) override;
	virtual IScriptClassRef		GetRegisteredClassByName( AStringPtr name ) const override;
	virtual _ubool				HasRegisteredClass( AStringPtr name ) const override;

	virtual _ubool				RegisterClassFunction( AStringPtr name, AStringPtr declaration, const ScriptFuncPtr& funcpointer, AStringPtr desc ) override;

	virtual _ubool				RegisterBehaviourFunction( AStringPtr name, _SCRIPT_CLASS_BEHAVIOUR behaviour, const ScriptFuncPtr& funcpointer ) override;
	virtual _ubool				InvokeConstructorBehaviourFunc( _byte*& object, AStringPtr name ) override;
	virtual _ubool				InvokeDestructorBehaviourFunc( _byte*& object, AStringPtr name ) override;
	virtual _ubool				InvokeCopyBehaviourFunc( _byte*& object, const _byte* from_object, AStringPtr name ) override;

	virtual _ubool				ParseNativePropertyInfo( AStringPtr declaration, _dword offset, ScriptPropertyDeclInfo& decl_info ) const override;
	virtual _ubool				ParseNativeFuncInfo( AStringPtr declaration, const ScriptFuncPtr& funcpointer, ScriptFuncDeclInfo& decl_info, ScriptNativeFuncInfo& native_func_info ) const override;

	virtual IScriptVMPassRef	CreateScriptVM( ) override;

	virtual _ubool				PreloadModule( AStringPtr name, AStringPtr code ) override;
};

}