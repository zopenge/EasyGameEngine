//! @file     ScriptNullClasses.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NullScriptSystem
//----------------------------------------------------------------------------

class NullScriptSystem : public TObject< _scriptSystem >
{
public:
	NullScriptSystem( ) { }
	virtual ~NullScriptSystem( ) { }

// _scriptSystem Interface
public:
	virtual _ubool				Initialize( ) { return _false; }

	virtual _dword				GetTotalMemSize( ) const { return 0; }

	virtual _ubool				SetRemoteDebugger( const Address& address ) { return _false; }
	virtual const Address&		GetRemoteDebugger( ) const { return Address::cNullAddress; }

	virtual _ubool				PreloadModule( AStringPtr name, AStringPtr code ) { return _false; }

	virtual _scriptModuleRef	CreateScriptModule( AStringPtr name, AStringPtr desc ) { return _null; }

	virtual _scriptVMPassRef	CreateScriptVM( ) { return _null; }
};

//----------------------------------------------------------------------------
// NullScriptResourceManager
//----------------------------------------------------------------------------

class NullScriptResourceManager : public INTERFACE_OBJECT_IMPL( IScriptResourceManager )
{
public:
	NullScriptResourceManager( ) { }
	virtual ~NullScriptResourceManager( ) { }

// IScriptResourceManager Interface
public:
	virtual IScriptClassRef		RegisterClass( AStringPtr name, AStringPtr desc, _dword size ) { return _null; }
	virtual IScriptClassRef		GetRegisteredClassByName( AStringPtr name ) const { return _null; }
	virtual _ubool				HasRegisteredClass( AStringPtr name ) const { return _false; }

	virtual _ubool				RegisterClassFunction( AStringPtr name, AStringPtr decl, const ScriptFuncPtr& funcpointer, AStringPtr desc ) { return _false; }

	virtual _ubool				RegisterBehaviourFunction( AStringPtr name, _SCRIPT_CLASS_BEHAVIOUR behaviour, const ScriptFuncPtr& funcpointer ) { return _false; }
	virtual _ubool				InvokeConstructorBehaviourFunc( _byte*& object, AStringPtr name ) { return _false; }
	virtual _ubool				InvokeDestructorBehaviourFunc( _byte*& object, AStringPtr name ) { return _false; }
	virtual _ubool				InvokeCopyBehaviourFunc( _byte*& object, const _byte* from_object, AStringPtr name ) { return _false; }

	virtual _ubool				ParseNativePropertyInfo( AStringPtr declaration, _dword offset, ScriptPropertyDeclInfo& decl_info ) const { return _false; }
	virtual _ubool				ParseNativeFuncInfo( AStringPtr declaration, const ScriptFuncPtr& funcpointer, ScriptFuncDeclInfo& decl_info, ScriptNativeFuncInfo& native_func_info ) const { return _false; }

	virtual IScriptVMPassRef	CreateScriptVM( ) { return _null; }

	virtual _ubool				PreloadModule( AStringPtr name, AStringPtr code ) { return _false; }
};

//----------------------------------------------------------------------------
// NullScriptModule
//----------------------------------------------------------------------------

class NullScriptModule : public INTERFACE_MODULE_IMPL( IScriptModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( IScriptModule ) BaseClass;

public:
	NullScriptModule( ) : BaseClass( L"", Version::cZero ) { }
	virtual ~NullScriptModule( ) { }

// IScriptModule Interface
public:
	virtual _dword			GetTotalMemSize( ) const { return 0; }

	virtual _ubool			SetRemoteDebugger( const Address& address ) { return _false; }
	virtual const Address&	GetRemoteDebugger( ) const { return Address::cNullAddress; }
};

//----------------------------------------------------------------------------
// NullScript
//----------------------------------------------------------------------------

class NullScript
{
	SINGLETON( NullScript )

private:
	NullScriptSystem			mScriptSystem;
	NullScriptResourceManager	mScriptResourceManager;
	NullScriptModule			mScriptModule;

public:
	EGE_GETR_ACCESSOR( NullScriptSystem, ScriptSystem )
	EGE_GETR_ACCESSOR( NullScriptResourceManager, ScriptResourceManager )
	EGE_GETR_ACCESSOR( NullScriptModule, ScriptModule )
};

}