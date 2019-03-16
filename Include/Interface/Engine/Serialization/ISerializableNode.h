//! @file     ISerializableNode.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

class IMarkupLangElement;

//----------------------------------------------------------------------------
// ISerializableNode
//----------------------------------------------------------------------------

class ISerializableNode : public IObject
{
public:
	//!	The enumeration value query callback function.
	//!	@param		name			The enumeration name.
	//!	@return		The enumeration value.
	typedef _dword (*OnQueryEnumValue)( WStringPtr name );
	//!	The enumeration name query callback function.
	//!	@param		value			The enumeration value.
	//!	@return		The enumeration name.
	typedef WStringPtr (*OnQueryEnumName)( _dword value );

public:
	//!	Check whether it's array object.
	//!	@param		none.
	//!	@return		True indicates it's array object.
	virtual _ubool IsArrayObject( ) const PURE;

	//!	Get the markup language node.
	//!	@remark		This node must be created by markup language file.
	//!	@param		none.
	//!	@return		The markup language node interface.
	virtual IMarkupLangElement* GetMarkupLangElement( ) PURE;
	//!	Get the markup language node.
	//!	@remark		This node must be created by markup language file.
	//!	@param		none.
	//!	@return		The markup language node interface.
	virtual const IMarkupLangElement* GetMarkupLangElement( ) const PURE;

	//!	Get the markup language file.
	//!	@remark		This node must be created by markup language file.
	//!	@param		none.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFile* GetMarkupLangFile( ) PURE;
	//!	Get the markup language file.
	//!	@remark		This node must be created by markup language file.
	//!	@param		none.
	//!	@return		The markup language file interface.
	virtual const IMarkupLangFile* GetMarkupLangFile( ) const PURE;

	//!	Get the node name.
	//!	@param		none.
	//!	@return		The node name.
	virtual WStringR GetNodeName( ) const PURE;
	//!	Set the node name.
	//!	@param		name			The node name.
	//!	@return		none.
	virtual _ubool SetNodeName( WStringPtr name ) PURE;

	//!	Check whether it's valid.
	//!	@param		none.
	//!	@return		True indicates it's valid.
	virtual _ubool HasObject( ) const PURE;
	//!	Check whether has property or not.
	//!	@param		name	The property name.
	//!	@return		True indicates has property with specified name.
	virtual _ubool HasProperty( WStringPtr name ) const PURE;

	//!	Get the child nodes number.
	//!	@param		none.
	//!	@return		The number of child nodes.
	virtual _dword GetChildNodesNumber( ) const PURE;
	//!	Get the child nodes number.
	//!	@param		name	The child name.
	//!	@return		The number of child nodes.
	virtual _dword GetChildNodesNumber( WStringPtr name ) const PURE;

	//!	Append child node as array object to the end.
	//!	@param		node		The node.
	//! @return		The index of appended element.
	virtual _dword AppendElementOfArrayObj( ISerializableNode* node ) PURE;
	//!	Append child element/value as array object to the end.
	//!	@param		value		The element's value.
	//! @return		The index of appended element, -1 indicates failure.
	virtual _dword AppendValueUOfArrayObj( _dword value ) PURE;
	//!	Append child element/value as array object to the end.
	//!	@param		value		The element's value.
	//! @return		The index of appended element, -1 indicates failure.
	virtual _dword AppendValueIOfArrayObj( _int value ) PURE;
	//!	Append child element/value as array object to the end.
	//!	@param		value		The element's value.
	//! @return		The index of appended element, -1 indicates failure.
	virtual _dword AppendValueFOfArrayObj( _float value ) PURE;
	//!	Append child element/value as array object to the end.
	//!	@param		value		The element's value.
	//! @return		The index of appended element, -1 indicates failure.
	virtual _dword AppendValueDOfArrayObj( _double value ) PURE;
	//!	Get the number of array object's sub-elements.
	//!	@param		none.
	//!	@return		The number of array object's sub-elements.
	virtual _dword GetSubElementsNumber( ) const PURE;
	//!	Get the sub-element of array object.
	//!	@param		index		The index of sub-elements.
	//!	@return		The element of array object.
	virtual ISerializableNodePassRef GetSubElementByIndex( _dword index ) PURE;

	//!	Get parent node.
	//!	@param		none.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef GetParentNode( ) PURE;
	//!	Get first child node.
	//!	@param		none.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef GetFirstChildNode( ) PURE;
	//!	Get last child node.
	//!	@param		none.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef GetLastChildNode( ) PURE;
	//!	Get previous node.
	//!	@param		none.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef GetPrevNode( ) PURE;
	//!	Get previous node by name.
	//!	@param		name		The node's name.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef GetPrevNode( WStringPtr name, _ubool ignorecase = _false ) PURE;
	//!	Get next node.
	//!	@param		none.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef GetNextNode( ) PURE;
	//!	Get next node by name.
	//!	@param		name		The node's name.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef GetNextNode( WStringPtr name, _ubool ignorecase = _false ) PURE;
	//!	Get head node.
	//!	@param		none.
	//!	@return		The serializable noe.
	virtual ISerializableNodePassRef GetHeadNode( ) PURE;
	//!	Get tail node.
	//!	@param		none.
	//!	@return		The serializable noe.
	virtual ISerializableNodePassRef GetTailNode( ) PURE;

	//!	Get child node's text by name.
	//!	@param		name	The child name.
	//!	@return		The child node's text.
	virtual WStringR GetChildTextByNameW( WStringPtr name ) PURE;
	//!	Get child node's text by name.
	//!	@param		name			The child name.
	//!	@param		attribute_name	The attribute name.
	//!	@return		The child node's text.
	virtual WStringR GetChildValueByNameW( WStringPtr name, WStringPtr attribute_name ) PURE;
	//!	Get child node by name.
	//!	@param		name	The child name.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef GetChildNodeByName( WStringPtr name ) PURE;
	//!	Get child node by index.
	//!	@param		index	The child index, start from 0.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef GetChildNodeByIndex( _dword index ) PURE;

	//!	Insert child node.
	//!	@param		name			The child name.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef InsertChildNode( WStringPtr name ) PURE;
	//!	Insert child node.
	//!	@param		name			The child name.
	//!	@param		text			The element text.
	//!	@return		is_array_obj	True indicates it's array object.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef InsertChildNode( WStringPtr name, WStringPtr text, _ubool is_array_obj ) PURE;
	//!	Insert brother node.
	//!	@param		name			The brother name.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef InsertBrotherNode( WStringPtr name ) PURE;
	//!	Insert brother node.
	//!	@param		name			The brother name.
	//!	@param		text			The element text.
	//!	@return		is_array_obj	True indicates it's array object.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef InsertBrotherNode( WStringPtr name, WStringPtr text, _ubool is_array_obj ) PURE;

	//!	Insert child node.
	//!	@param		node		The node will insert as child node.
	//!	@param		recursive	True indicates insert in recursive mode.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef InsertChildNode( ISerializableNode* node, _ubool recursive ) PURE;
	//!	Insert brother node.
	//!	@param		node		The node will insert as brother node.
	//!	@param		recursive	True indicates insert in recursive mode.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef InsertBrotherNode( ISerializableNode* node, _ubool recursive ) PURE;

	//!	Create walker.
	//!	@param		none.
	//!	@return		The walker.
	virtual ISerializableNodeWalkerPassRef CreateWalker( ) PURE;

	//!	Get the node's value.
	//!	@param		none.
	//! @return		The value.
	virtual _dword GetValueU( ) const PURE;
	//!	Get the node's value.
	//!	@param		none.
	//! @return		The value.
	virtual _int GetValueI( ) const PURE;
	//!	Get the node's value.
	//!	@param		none.
	//! @return		The value.
	virtual _float GetValueF( ) const PURE;
	//!	Get the node's value.
	//!	@param		none.
	//! @return		The value.
	virtual _double GetValueD( ) const PURE;

	//!	Get the node's text.
	//!	@param		none.
	//! @return		The text.
	virtual AStringR GetTextA( ) const PURE;
	//!	Get the node's text.
	//!	@param		none.
	//! @return		The text.
	virtual UStringR GetTextU( ) const PURE;
	//!	Get the node's text.
	//!	@param		none.
	//! @return		The text.
	virtual WStringR GetTextW( ) const PURE;
	//!	Set the node's text.
	//!	@param		text	The text.
	//! @return		none.
	virtual _void SetText( AStringPtr text ) PURE;
	//!	Set the node's text.
	//!	@param		text	The text.
	//! @return		none.
	virtual _void SetText( UStringPtr text ) PURE;
	//!	Set the node's text.
	//!	@param		text	The text.
	//! @return		none.
	virtual _void SetText( WStringPtr text ) PURE;

	//!	Has prev brother.
	//!	@param		none.
	//!	@return		True indicates has prev brother.
	virtual _ubool HasPrev( ) const PURE;
	//!	Has prev brother by name.
	//!	@param		name	The node name.
	//!	@return		True indicates has prev brother with specified name.
	virtual _ubool HasPrev( WStringPtr name ) const PURE;
	//!	Move to prev brother.
	//!	@param		none.
	//!	@return		True indicates move successful, otherwise indicates we don't have prev brother.
	virtual _ubool MovePrev( ) PURE;
	//!	Move to prev brother by name.
	//!	@param		name	The node name.
	//!	@return		True indicates move successful, otherwise indicates we don't have prev brother with specified name.
	virtual _ubool MovePrev( WStringPtr name ) PURE;

	//!	Has next brother.
	//!	@param		none.
	//!	@return		True indicates has next brother.
	virtual _ubool HasNext( ) const PURE;
	//!	Has next brother by name.
	//!	@param		name	The node name.
	//!	@return		True indicates has next brother with specified name.
	virtual _ubool HasNext( WStringPtr name ) const PURE;
	//!	Move to next brother.
	//!	@param		none.
	//!	@return		True indicates move successful, otherwise indicates we don't have next brother.
	virtual _ubool MoveNext( ) PURE;
	//!	Move to next brother by name.
	//!	@param		name	The node name.
	//!	@return		True indicates move successful, otherwise indicates we don't have next brother with specified name.
	virtual _ubool MoveNext( WStringPtr name ) PURE;

	//!	Read properties.
	virtual _ubool Read( WStringPtr name, _byte& value ) PURE;
	virtual _ubool Read( WStringPtr name, _word& value ) PURE;
	virtual _ubool Read( WStringPtr name, _int& value ) PURE;
	virtual _ubool Read( WStringPtr name, _dword& value ) PURE;
	virtual _ubool Read( WStringPtr name, _large& value ) PURE;
	virtual _ubool Read( WStringPtr name, _qword& value ) PURE;
	virtual _ubool Read( WStringPtr name, _ubool& value ) PURE;
	virtual _ubool Read( WStringPtr name, _float& value ) PURE;
	virtual _ubool Read( WStringPtr name, _double& value ) PURE;
	virtual _ubool Read( WStringPtr name, _charw& value ) PURE;
	virtual _ubool Read( WStringPtr name, AString& value ) PURE;
	virtual _ubool Read( WStringPtr name, UString& value ) PURE;
	virtual _ubool Read( WStringPtr name, WString& value ) PURE;
	virtual _ubool Read( WStringPtr name, AStringObj& value ) PURE;
	virtual _ubool Read( WStringPtr name, UStringObj& value ) PURE;
	virtual _ubool Read( WStringPtr name, WStringObj& value ) PURE;
	virtual _ubool Read( WStringPtr name, Time& value ) PURE;
	virtual _ubool Read( WStringPtr name, MD5Code& value ) PURE;
	virtual _ubool Read( WStringPtr name, Version& value ) PURE;
	virtual _ubool Read( WStringPtr name, Color& value ) PURE;
	virtual _ubool Read( WStringPtr name, SafeInt& value ) PURE;
	virtual _ubool Read( WStringPtr name, SafeDword& value ) PURE;
	virtual _ubool Read( WStringPtr name, SafeFloat& value ) PURE;
	virtual _ubool Read( WStringPtr name, SafeBool& value ) PURE;
	virtual _ubool Read( WStringPtr name, SafeDouble& value ) PURE;
	virtual _ubool Read( WStringPtr name, SafeLarge& value ) PURE;
	virtual _ubool Read( WStringPtr name, SafeQword& value ) PURE;
	virtual _ubool Read( WStringPtr x_name, WStringPtr y_name, Vector2& vector ) PURE;
	virtual _ubool Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, Vector3& vector ) PURE;
	virtual _ubool Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, Vector4& vec4 ) PURE;
	virtual _ubool Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, Quaternion& quaternion ) PURE;
	virtual _ubool Read( WStringPtr px_name, WStringPtr py_name, WStringPtr sx_name, WStringPtr sy_name, WStringPtr rotation_name, Transform2D& transform ) PURE;
	virtual _ubool Read( WStringPtr min_name, WStringPtr max_name, DwordRange& bounds ) PURE;
	virtual _ubool Read( WStringPtr min_name, WStringPtr max_name, FloatRange& bounds ) PURE;
	virtual _ubool Read( WStringPtr r, WStringPtr g, WStringPtr b, WStringPtr a, Color& color ) PURE;
	virtual _ubool ReadTime( WStringPtr name, _time_t& value ) PURE;
	virtual _ubool ReadFlag( WStringPtr name, _dword flag_value_to_combine, FlagsObject& flags ) PURE;
	virtual _ubool ReadFlags( WStringPtr name, FlagsObject& flags ) PURE;
	virtual _ubool ReadFlags( WStringPtr name, FlagsObject& flags, OnQueryEnumValue funcpointer ) PURE;

	//!	Write properties.
	virtual _ubool Write( WStringPtr name, _int value ) PURE;
	virtual _ubool Write( WStringPtr name, _dword value ) PURE;
	virtual _ubool Write( WStringPtr name, _large value ) PURE;
	virtual _ubool Write( WStringPtr name, _qword value ) PURE;
	virtual _ubool Write( WStringPtr name, _boolean value ) PURE;
	virtual _ubool Write( WStringPtr name, _float value ) PURE;
	virtual _ubool Write( WStringPtr name, _double value ) PURE;
	virtual _ubool Write( WStringPtr name, _charw value ) PURE;
	virtual _ubool Write( WStringPtr name, const _chara* value ) PURE;
	virtual _ubool Write( WStringPtr name, const _charw* value ) PURE;
	virtual _ubool Write( WStringPtr name, AStringPtr value ) PURE;
	virtual _ubool Write( WStringPtr name, UStringPtr value ) PURE;
	virtual _ubool Write( WStringPtr name, WStringPtr value ) PURE;
	virtual _ubool Write( WStringPtr name, const AStringR& value ) PURE;
	virtual _ubool Write( WStringPtr name, const UStringR& value ) PURE;
	virtual _ubool Write( WStringPtr name, const WStringR& value ) PURE;
	virtual _ubool Write( WStringPtr name, const AStringObj& value ) PURE;
	virtual _ubool Write( WStringPtr name, const UStringObj& value ) PURE;
	virtual _ubool Write( WStringPtr name, const WStringObj& value ) PURE;
	virtual _ubool Write( WStringPtr name, const Time& value ) PURE; 
	virtual _ubool Write( WStringPtr name, const MD5Code& value ) PURE;
	virtual _ubool Write( WStringPtr name, const Version& value ) PURE;
	virtual _ubool Write( WStringPtr name, const Color& value ) PURE;
	virtual _ubool Write( WStringPtr x_name, WStringPtr y_name, const Vector2& vector ) PURE;
	virtual _ubool Write( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, const Vector3& vector ) PURE;
	virtual _ubool Write( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, const Vector4& vec4 ) PURE;
	virtual _ubool Write( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, const Quaternion& quaternion ) PURE;
	virtual _ubool Write( WStringPtr px_name, WStringPtr py_name, WStringPtr sx_name, WStringPtr sy_name, WStringPtr rotation_name, const Transform2D& transform ) PURE;
	virtual _ubool Write( WStringPtr min_name, WStringPtr max_name, const DwordRange& bounds ) PURE;
	virtual _ubool Write( WStringPtr min_name, WStringPtr max_name, const FloatRange& bounds ) PURE;
	virtual _ubool Write( WStringPtr r, WStringPtr g, WStringPtr b, WStringPtr a, const Color& color ) PURE;
	virtual _ubool WriteTime( WStringPtr name, _time_t value ) PURE;
	virtual _ubool WriteFlag( WStringPtr name, _dword flag_value_to_check, const FlagsObject& flags ) PURE;
	virtual _ubool WriteFlags( WStringPtr name, const FlagsObject& flags ) PURE;
	virtual _ubool WriteFlags( WStringPtr name, const FlagsObject& flags, OnQueryEnumName funcpointer ) PURE;

	//!	Dump to string.
	//!	@param		none.
	//!	@return		The formatted string contains all child nodes.
	virtual WStringR DumpToString( ) const PURE;
	//!	Dump to schema string.
	//!	@param		none.
	//!	@return		The schema string contains all child nodes.
	virtual WStringR DumpToSchemaString( ) const PURE;

public:
	//!	Read properties.
	template< typename Type > 
	_ubool Read( WStringPtr name, Array< Type >& array );
	template< typename Type >
	_ubool ReadRange( Range< Type >& range );

	// Read flags.
	template< typename Type >
	_ubool ReadFlags( WStringPtr name, Type& flags_obj, OnQueryEnumValue funcpointer );

	//!	Write properties.
	template< typename Type >
	_ubool Write( WStringPtr name, const Array< Type >& array );

	template< typename ValueType >
	_ubool ReadEnum( WStringPtr name, ValueType& value, _ubool bits_mode, OnQueryEnumValue funcpointer );
	template< typename ValueType >
	_ubool WriteEnum( WStringPtr name, ValueType value, _ubool bits_mode, OnQueryEnumName funcpointer );
};

//----------------------------------------------------------------------------
// ISerializableNode Implementation
//----------------------------------------------------------------------------

template< typename Type > 
_ubool ISerializableNode::Read( WStringPtr name, Array< Type >& array )
{
	// Search for child node by name
	ISerializableNodePassRef child_node = GetChildNodeByName( name );
	if ( child_node.IsNull( ) )
		return _false;

	// Create the "entry" child node
	ISerializableNodePassRef entry_node = child_node->GetChildNodeByName( L"entry" );
	if ( entry_node.IsNull( ) )
		return _false;

	// Read all nodes
	do 
	{
		Type element;
		if ( entry_node->Read( L"value", element ) == _false )
			return _false;

		array.Append( element );

	} while ( entry_node->MoveNext( L"entry" ) );

	return _true;
}

template< typename Type >
_ubool ISerializableNode::ReadRange( Range< Type >& range )
{
	Type min_value;
	if ( Read( L"min", min_value ) )
		range.SetMinValue( min_value );

	Type max_value;
	if ( Read( L"max", max_value ) )
		range.SetMaxValue( max_value );

	return _true;
}

template< typename Type >
_ubool ISerializableNode::ReadFlags( WStringPtr name, Type& flags_obj, OnQueryEnumValue funcpointer )
{
	FlagsObject flags;
	if ( ReadFlags( name, flags, funcpointer ) )
	{
		flags_obj.SetFlags( flags );
		return _true;
	}
	else
	{
		return _false;
	}
}

template< typename Type >
_ubool ISerializableNode::Write( WStringPtr name, const Array< Type >& array )
{
	// Insert for child element by name
	ISerializableNodePassRef child_node = InsertChildNode( name, L"", _false );
	if ( child_node.IsNull( ) )
		return _false;

	// Write all nodes of array
	for ( _dword i = 0; i < array.Number( ); i ++ )
	{
		ISerializableNodePassRef entry_node = child_node->InsertChildNode( L"entry", L"", _false );
		if ( entry_node.IsNull( ) )
			return _false;

		// Write it
		if ( entry_node->Write( L"value", array[i] ) == _false )
			return _false;
	}

	return _true;
}

template< typename ValueType >
_ubool ISerializableNode::ReadEnum( WStringPtr name, ValueType& value, _ubool bits_mode, ISerializableNode::OnQueryEnumValue funcpointer )
{
	if ( funcpointer == _null )
		return _false;

	// Read the enumeration value string
	WString string;
	if ( Read( name, string ) == _false )
		return _false;

	// It's bits mode
	if ( bits_mode )
	{
		// Split the enumeration values
		WStringArray strings;
		StringFormatter::SplitString( string, strings, L"|", L" \t" );

		// Combine enumeration values
		_dword values = 0;
		for ( _dword i = 0; i < strings.Number( ); i ++ )
			values |= (*funcpointer)( strings[i].Str( ) );

		value = (ValueType)values;
	}
	// It's single value mode
	else
	{
		value = (ValueType)(*funcpointer)( string );
	}

	return _true;
}

template< typename ValueType >
_ubool ISerializableNode::WriteEnum( WStringPtr name, ValueType value, _ubool bits_mode, OnQueryEnumName funcpointer )
{
	if ( funcpointer == _null )
		return _false;

	// It's bits mode
	if ( bits_mode )
	{
		// Build the enumeration string
		WString string;
		for ( _dword i = 0; i < 32 && value != 0; i ++, value >>= 1 )
		{
			if ( ( value & 1 ) == 0 )
				continue;

			// Query the enumeration name
			WStringPtr enum_name = (*funcpointer)( 1 << i );
			if ( enum_name.IsEmpty( ) )
				return _false;

			// Update the enumeration string
			string += enum_name;
			string += L"|";
		}

		// Cleanup the enumeration string
		string.TrimRight( L"|" );

		// Write it
		return Write( name, string );
	}
	// It's single value mode
	else
	{
		// Query the enumeration name
		WStringPtr enum_name = (*funcpointer)( value );
		if ( enum_name.IsEmpty( ) )
			return _false;

		// Write it
		return Write( name, enum_name );
	}
}

}