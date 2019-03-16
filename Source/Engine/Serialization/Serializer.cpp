//! @file     Serializer.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Serializer Implementation
//----------------------------------------------------------------------------

Serializer::Serializer( )
{

}

Serializer::~Serializer( )
{

}

_ubool Serializer::HasProperty( ISerializableNode* node, WStringPtr name ) const
{
	if ( node == _null )
		return _false;

	return node->HasProperty( name );
}

_ubool Serializer::Read( ISerializableNode* node, WStringPtr name, _byte& value ) const
{
	return TImport( node, name, value );
}

_ubool Serializer::Read( ISerializableNode* node, WStringPtr name, _word& value ) const
{
	return TImport( node, name, value );
}

_ubool Serializer::Read( ISerializableNode* node, WStringPtr name, _long& value ) const
{
	return TImport( node, name, value );
}

_ubool Serializer::Read( ISerializableNode* node, WStringPtr name, _dword& value ) const
{
	return TImport( node, name, value );
}

_ubool Serializer::Read( ISerializableNode* node, WStringPtr name, _float& value ) const
{
	return TImport( node, name, value );
}

_ubool Serializer::Read( ISerializableNode* node, WStringPtr name, _double& value ) const
{
	return TImport( node, name, value );
}

_ubool Serializer::Read( ISerializableNode* node, WStringPtr name, WString& value ) const
{
	return TImport( node, name, value );
}

_ubool Serializer::Read( ISerializableNode* node, WStringPtr name, Time& value ) const
{
	return TImport( node, name, value );
}

_ubool Serializer::Read( ISerializableNode* node, WStringPtr name, MD5Code& value ) const
{
	return TImport( node, name, value );
}

_ubool Serializer::Read( ISerializableNode* node, WStringPtr name, WStringObjRef& string )
{
	// Read property
	WString value;
	if ( TImport( node, name, value ) == _false )
		return _false;

	// Fill into string table and feedback the referenced string object
	string = GetStringTable( )->GetRefString( value );
	if ( string.IsNull( ) )
		return _false;

	return _true;
}

_ubool Serializer::Read( ISerializableNode* node, WString& text ) const
{
	if ( node == _null )
		return _false;

	return node->Read( text );
}

_ubool Serializer::Read( ISerializableNode* node, Vector3& vector ) const
{
	if ( node == _null )
		return _false;

	node->Read( L"x", vector.x );
	node->Read( L"y", vector.y );
	node->Read( L"z", vector.z );

	return _true;
}

_ubool Serializer::Read( ISerializableNode* node, Color& color ) const
{
	if ( node == _null )
		return _false;

	node->Read( L"a", color.a );
	node->Read( L"r", color.r );
	node->Read( L"g", color.g );
	node->Read( L"b", color.b );

	return _true;
}

_ubool Serializer::ReadFlag( ISerializableNode* node, WStringPtr name, FlagsObject& flags, _dword flag ) const
{
	// Read the enumeration value string
	WString string;
	if ( Read( node, name, string ) == _false )
		return _false;

	// Set the flag
	if ( string.IsEqual( L"true", _true ) )
		flags.CombineFlag( flag );
	else
		flags.ClearFlag( flag );

	return _true;
}

_ubool Serializer::ReadEnum( ISerializableNode* node, WStringPtr name, _dword& value, OnQueryEnumValue funcpointer, const VoidParameters2& parameters ) const
{
	if ( funcpointer == _null )
		return _false;

	// Read the enumeration value string
	WString string;
	if ( Read( node, name, string ) == _false )
		return _false;

	// Split the enumeration values
	const _dword cMaxNumber = 32;
	FixedArray< WRawString, cMaxNumber > string_array;
	StringFormatter::SplitString( string, string_array, L"|", L" \t" );

	// Combine enumeration values
	value = 0;
	for ( _dword i = 0; i < string_array.Number( ); i ++ )
		value |= (*funcpointer)( string_array[i].Str( ), parameters );

	return value;
}

_ubool Serializer::Write( ISerializableNode* node, WStringPtr name, _long value ) const
{
	return TExport( node, name, value );
}

_ubool Serializer::Write( ISerializableNode* node, WStringPtr name, _dword value ) const
{
	return TExport( node, name, value );
}

_ubool Serializer::Write( ISerializableNode* node, WStringPtr name, _float value ) const
{
	return TExport( node, name, value );
}

_ubool Serializer::Write( ISerializableNode* node, WStringPtr name, _double value ) const
{
	return TExport( node, name, value );
}

_ubool Serializer::Write( ISerializableNode* node, WStringPtr name, WStringPtr value ) const
{
	return TExport( node, name, value );
}

_ubool Serializer::Write( ISerializableNode* node, WStringPtr name, const Time& value ) const
{
	return TExport( node, name, value );
}

_ubool Serializer::Write( ISerializableNode* node, WStringPtr name, const MD5Code& value ) const
{
	return TExport( node, name, value );
}