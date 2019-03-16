//! @file     ScriptFunction.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// ScriptFunction Implementation
//----------------------------------------------------------------------------

ScriptFunction::ScriptFunction( _scriptFunction* function )
{
	mFunction = function;
}

ScriptFunction::~ScriptFunction( )
{

}

AStringPtr ScriptFunction::GetName( ) const
{
	return mFunction->GetName( );
}

IScriptValuePassRef ScriptFunction::Invoke( )
{
	_scriptValueRef value = mFunction->Invoke( );
	if ( value.IsNull( ) )
		return _null;

	return new ScriptValue( value );
}

IScriptValuePassRef ScriptFunction::InvokeByVars( const VariableArray& vars )
{
	_scriptValueRef value = mFunction->Invoke( vars );
	if ( value.IsNull( ) )
		return _null;

	return new ScriptValue( value );
}