//! @file     ScriptValue.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ScriptValue
//----------------------------------------------------------------------------

class ScriptValue : public TObject< IScriptValue >
{
private:
	//!	The script value
	_scriptValueRef	mValue;

public:
	ScriptValue( _scriptValue* value );
	virtual ~ScriptValue( );

// IScriptValue Interface
public:
	virtual const _void*	GetPointer( ) const override;

	virtual _ubool			GetBool( ) const override;
	virtual _double			GetDouble( ) const override;

	virtual AStringR		GetStringA( ) const override;
	virtual UStringR		GetStringU( ) const override;
	virtual WStringR		GetStringW( ) const override;
};

}