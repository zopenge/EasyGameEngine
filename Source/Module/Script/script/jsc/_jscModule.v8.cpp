//! @file     _jscModule.v8.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_GOOGLE_V8_ == 1)

//----------------------------------------------------------------------------
// _jscModule Helpful Functions Implementation
//----------------------------------------------------------------------------

static _void OnCallJSFunctionCallback( const v8::FunctionCallbackInfo< v8::Value >& args )
{

}

//----------------------------------------------------------------------------
// _jscModule Implementation
//----------------------------------------------------------------------------

_ubool _jscModule::OnInitialize( )
{
	return _true;
}

_void _jscModule::OnFinalize( )
{
}

_ubool _jscModule::OnCreateJSObject( JSObjectRef js_object )
{
	return _true;
}

JSObjectCallAsFunctionCallback _jscModule::OnGetJSFunctionCallbackPtr( ) const
{
	return OnCallJSFunctionCallback;
}

#endif