//! @file     ScriptFunction.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ScriptFunction
//----------------------------------------------------------------------------

class ScriptFunction : public TObject< IScriptFunction >
{
private:
	//!	The script function
	_scriptFunctionRef	mFunction;

public:
	ScriptFunction( _scriptFunction* function );
	virtual ~ScriptFunction( );

// IScriptFunction Interface
public:
	virtual AStringPtr			GetName( ) const override;

	virtual IScriptValuePassRef	Invoke( ) override;
	virtual IScriptValuePassRef	InvokeByVars( const VariableArray& vars ) override;
};

}