//! @file     Expression.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPlatform.h"

INTERNAL_HANDLER_IMPL_BEGIN( Expression )
	Parser mParser;
INTERNAL_HANDLER_IMPL_END( );

//----------------------------------------------------------------------------
// Expression Implementation
//----------------------------------------------------------------------------

Expression::Expression( )
{
	INTERNAL_HANDLER_CREATE( );
}

Expression::~Expression( )
{
	INTERNAL_HANDLER_RELEASE( );
}

_void Expression::AddVariable( WStringPtr var_name, _int value )
{
	AString exp = FORMAT_ASTRING_2( "%s = %d", AString( ).FromString( var_name ).Str( ), value );
	INTERNAL_HANDLER( )->mParser.parse( exp.Str( ) );
}

_void Expression::AddVariable( WStringPtr var_name, _dword value )
{
	AString exp = FORMAT_ASTRING_2( "%s = %d", AString( ).FromString( var_name ).Str( ), value );
	INTERNAL_HANDLER( )->mParser.parse( exp.Str( ) );
}

_void Expression::AddVariable( WStringPtr var_name, _float value )
{
	AString exp = FORMAT_ASTRING_2( "%s = %f", AString( ).FromString( var_name ).Str( ), value );
	INTERNAL_HANDLER( )->mParser.parse( exp.Str( ) );
}

_void Expression::RemoveAllVariables( )
{
	INTERNAL_HANDLER( )->mParser = Parser( );
}

_float Expression::Calculate( WStringPtr exp )
{
	return (_float)INTERNAL_HANDLER( )->mParser.parse( AString( ).FromString( exp ).Str( ) );
}
