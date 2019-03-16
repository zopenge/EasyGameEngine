//! @file     ISerializer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ISerializer
//----------------------------------------------------------------------------

class ISerializer : public IObject
{
public:
	//!	The enumeration value query callback function.
	//!	@param		name			The enumeration name.
	//!	@param		parameters		The user defined parameters.
	//!	@return		The enumeration value.
	typedef _dword (*OnQueryEnumValue)( WStringPtr name, const VoidParameters2& parameters );

public:
	//!	Query properties.
	virtual _ubool HasProperty( ISerializableNode* node, WStringPtr name ) const PURE;

	//!	Read properties.
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, _byte& value ) const PURE;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, _word& value ) const PURE;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, _long& value ) const PURE;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, _dword& value ) const PURE;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, _float& value ) const PURE;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, _double& value ) const PURE;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, WString& value ) const PURE;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, Time& value ) const PURE;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, MD5Code& value ) const PURE;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, WStringObjRef& string ) PURE;
	virtual _ubool Read( ISerializableNode* node, WString& text ) const PURE;
	virtual _ubool Read( ISerializableNode* node, Vector3& vector ) const PURE;
	virtual _ubool Read( ISerializableNode* node, Color& color ) const PURE;
	virtual _ubool ReadFlag( ISerializableNode* node, WStringPtr name, FlagsObject& flags, _dword flag ) const PURE;
	virtual _ubool ReadEnum( ISerializableNode* node, WStringPtr name, _dword& value, OnQueryEnumValue funcpointer, const VoidParameters2& parameters = VoidParameters2::cNull ) const PURE;

	//!	Write properties.
	virtual _ubool Write( ISerializableNode* node, WStringPtr name, _long value ) const PURE;
	virtual _ubool Write( ISerializableNode* node, WStringPtr name, _dword value ) const PURE;
	virtual _ubool Write( ISerializableNode* node, WStringPtr name, _float value ) const PURE;
	virtual _ubool Write( ISerializableNode* node, WStringPtr name, _double value ) const PURE;
	virtual _ubool Write( ISerializableNode* node, WStringPtr name, WStringPtr value ) const PURE;
	virtual _ubool Write( ISerializableNode* node, WStringPtr name, const Time& value ) const PURE;
	virtual _ubool Write( ISerializableNode* node, WStringPtr name, const MD5Code& value ) const PURE;

public:
	//!	Read properties.
	template< typename Type, typename Key > 
	_ubool Read( ISerializableNode* node, WStringPtr name, Array< Type, Key >& array ) const;
	template< typename Type >
	_ubool ReadRange( ISerializableNode* node, Range< Type >& range ) const;

	//!	Write properties.
	template< typename Type, typename Key >
	_ubool Write( ISerializableNode* node, WStringPtr name, const Array< Type, Key >& array ) const;
};

//----------------------------------------------------------------------------
// Serializer Implementation
//----------------------------------------------------------------------------

template< typename Type, typename Key > 
_ubool ISerializer::Read( ISerializableNode* node, WStringPtr name, Array< Type, Key >& array ) const
{
	if ( node == _null )
		return _false;

	// Search for child node by name
	ISerializableNodePassRef child_node = node->GetChildNode( name );
	if ( child_node.IsNull( ) )
		return _false;

	// Create the "entry" child node
	ISerializableNodePassRef entry_node = child_node->GetChildNode( L"entry" );
	if ( entry_node.IsNull( ) )
		return _false;

	// Read all nodes
	do 
	{
		Type element;
		if ( Read( entry_node, L"value", element ) == _false )
			return _false;

		array.Append( element );

	} while ( entry_node->MoveNext( L"entry" ) );

	return _true;
}

template< typename Type >
_ubool ISerializer::ReadRange( ISerializableNode* node, Range< Type >& range ) const
{
	if ( node == _null )
		return _false;

	Type min_value;
	if ( node->Read( L"min", min_value ) )
		range.SetMinValue( min_value );

	Type max_value;
	if ( node->Read( L"max", max_value ) )
		range.SetMaxValue( max_value );

	return _true;
}

template< typename Type, typename Key >
_ubool ISerializer::Write( ISerializableNode* node, WStringPtr name, const Array< Type, Key >& array ) const
{
	if ( node == _null )
		return _false;

	// Insert for child element by name
	ISerializableNodePassRef child_node = node->InsertChildNode( name );
	if ( child_node.IsNull( ) )
		return _false;

	// Write all nodes of array
	for ( _dword i = 0; i < array.Number( ); i ++ )
	{
		ISerializableNodePassRef entry_node = child_node->InsertChildNode( L"entry" );
		if ( entry_node.IsNull( ) )
			return _false;

		// Write it
		if ( Write( entry_node, L"value", array[i] ) == _false )
			return _false;
	}

	return _true;
}

}