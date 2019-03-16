//! @file     _jscModule.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _jscModule
//----------------------------------------------------------------------------

class _jscModule : public TObject< _scriptModule >
{
private:
	//!	The module name
	AStringObj			mName;
	//!	The module description
	AStringObj			mDesc;

	//!	The JS class 
	JSClassRef			mJSClass;
	//!	The JS class without create wrapped resource object
	JSClassRef			mJSClassWithoutCreateWrappedResObj;
	//!	The JS object
	JSObjectRef			mJSObject;

	//!	The global JS context
	JSGlobalContextRef	mJSContext;

private:
	//!	When initialize.
	_ubool OnInitialize( );
	//!	When finalize.
	_void OnFinalize( );

	//!	When create JS object.
	_ubool OnCreateJSObject( JSObjectRef js_object );

	//!	When get call JS function callback pointer.
	JSObjectCallAsFunctionCallback OnGetJSFunctionCallbackPtr( ) const;

public:
	_jscModule( JSGlobalContextRef js_context );
	virtual ~_jscModule( );

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr name, AStringPtr desc );

	//!	Get the JS global context.
	JSGlobalContextRef GetJSGlobalContext( );
	//!	Get the JS global object.
	JSObjectRef GetJSGlobalObject( );

	//!	Create JS object by class.
	JSObjectRef CreateJSObject( JSContextRef js_context, _byte* wrapped_class, _ubool skip_create_wrapped_res_obj );

// _scriptModule Interface
public:
	virtual AStringPtr			GetName( ) const override;
	virtual const AStringObj&	GetNameObj( ) const override;

	virtual _ubool				RegisterEnumValue( AStringPtr name, _dword value ) override;
	virtual _ubool				RegisterProperty( const ScriptPropertyDeclInfo& decl_info ) override;
	virtual _ubool				RegisterFunction( const ScriptFuncDeclInfo& decl_info, const ScriptNativeFuncInfo& native_func_info ) override;
};

}