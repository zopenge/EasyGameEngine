//! @file     _luaModule.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _luaModule
//----------------------------------------------------------------------------

class _luaModule : public TObject< _scriptModule >
{
public:
	//!	The property info
	struct PropertyInfo
	{
		//!	The property declaration info
		ScriptPropertyDeclInfo	mDeclInfo;
	};
	typedef Array< PropertyInfo* > PropertyInfoArray;

	//!	The function info
	struct FuncInfo
	{
		//!	The function declaration info
		ScriptFuncDeclInfo		mDeclInfo;
		//!	The native function info
		ScriptNativeFuncInfo	mNativeFuncInfo;
		//!	The module
		_luaModule*				mModule;

		FuncInfo( )
		{
			mModule = _null;
		}
	};
	typedef Array< FuncInfo* > FuncInfoArray;

private:
	//!	The module name
	AStringObj			mName;
	//!	The module description
	AStringObj			mDesc;

	//!	The declaration
	PropertyInfoArray	mProperties;
	//!	The functions
	FuncInfoArray		mFunctions;

private:
	//!	The global new.
	static int GlobalNew( lua_State* l );
	//!	The local new.
	static int LocalNew( lua_State* l );
	//!	The destructor.
	static int Destructor( lua_State* l );

	//!	The getter.
	static int Getter( lua_State* l );
	//!	The setter.
	static int Setter( lua_State* l );

	//!	Call lua function.
	static _int Call( lua_State* l );

private:
	//!	Push return value.
	_ubool PushRetValue( lua_State* l, const ScriptVarDeclInfo& var_decl_info, const ScriptVMRegisters& registers );

	//!	Invoke function.
	_ubool InvokeFunc( lua_State* l, const FuncInfo* func_info, _void* obj );

public:
	_luaModule( );
	virtual ~_luaModule( );

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr name, AStringPtr desc );

// _scriptModule Interface
public:
	virtual AStringPtr			GetName( ) const override;
	virtual const AStringObj&	GetNameObj( ) const override;

	virtual _ubool				RegisterEnumValue( AStringPtr name, _dword value ) override;
	virtual _ubool				RegisterProperty( const ScriptPropertyDeclInfo& decl_info ) override;
	virtual _ubool				RegisterFunction( const ScriptFuncDeclInfo& decl_info, const ScriptNativeFuncInfo& native_func_info ) override;
};

}