//! @file     ScriptValue.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// ScriptValue Implementation
//----------------------------------------------------------------------------

ScriptValue::ScriptValue( _scriptValue* value )
{
	mValue = value;
}

ScriptValue::~ScriptValue( )
{

}

const _void* ScriptValue::GetPointer( ) const
{
	return mValue->GetPointer( );
}

_ubool ScriptValue::GetBool( ) const
{
	return EGE_BOOLEAN( mValue->GetDouble( ) );
}

_double ScriptValue::GetDouble( ) const 
{
	return mValue->GetDouble( );
}

AStringR ScriptValue::GetStringA( ) const
{
	WString value = mValue->GetStringW( );

	return AString( ).FromString( value );
}

UStringR ScriptValue::GetStringU( ) const
{
	WString value = mValue->GetStringW( );

	return UString( ).FromString( value );
}

WStringR ScriptValue::GetStringW( ) const
{
	return mValue->GetStringW( );
}