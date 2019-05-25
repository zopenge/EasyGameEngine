//! @file     Properties.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// Properties Implementation
// --------------------------------------------------------------------------------------------------------------

Properties::Properties( )
{
}

Properties::~Properties( )
{
}

template<>
inline const Variable& Properties::SetPropertyValue< WStringPtr, WStringPtr >( const WStringPtr& name, WStringPtr value )
{
	Variable& property_value = mPropertiesWithName[name];
	property_value.SetString( GetStringTable( )->GetRefString( value ).Str( ) );

	return property_value;
}

template<>
inline const Variable& Properties::SetPropertyValue< WStringObj, WStringPtr >( const WStringObj& name, WStringPtr value )
{
	Variable& property_value = mPropertiesWithName[name];
	property_value.SetString( GetStringTable( )->GetRefString( value ).Str( ) );

	return property_value;
}

template<>
inline const Variable& Properties::SetPropertyValue< WString, WStringPtr >( const WString& name, WStringPtr value )
{
	Variable& property_value = mPropertiesWithName[(const WString&)name];
	property_value.SetString( GetStringTable( )->GetRefString( value ).Str( ) );

	return property_value;
}

template< typename KeyType, typename ValueType >
const Variable& Properties::SetPropertyValue( const KeyType& name, ValueType value )
{
	Variable& property_value = mPropertiesWithName[ name ];
	property_value = value;
	
	return property_value;
}

template< typename KeyType, typename ValueType >
ValueType Properties::GetPropertyValue( const KeyType& name ) const
{
	const Variable* value = mPropertiesWithName.Search( name );
	if ( value == _null )
		return ValueType(0);

	return *value;
}

template< typename KeyType, typename ValueType >
_ubool Properties::GetPropertyValue( const KeyType& name, ValueType& value ) const
{
	const Variable* property_value = mPropertiesWithName.Search( name );
	if ( property_value == _null )
		return _false;

	value = (ValueType)*property_value;

	return _true;
}

IObject* Properties::CloneTo( _ubool standalone ) const
{
	Properties* properties			= new Properties( );
	properties->mPropertiesWithName = mPropertiesWithName;

	return properties;
}

_ubool Properties::Import( ISerializableNode* node )
{
	if ( node == _null )
		return _false;

	ISerializableNodeRef parent_node = node->GetChildNodeByName( L"Properties" );
	if ( parent_node.IsValid( ) )
	{
		ISerializableNodeRef node = parent_node->GetChildNodeByName( L"Property" );
		if ( node.IsValid( ) ) 
		{
			do 
			{
				WString key_string, value_string;
				node->Read( L"key", key_string );
				node->Read( L"value", value_string );

				SetProperty( key_string, value_string );
			}
			while( node->MoveNext( L"Property" ) );
		}
	}

	return _true;
}

_ubool Properties::Export( ISerializableNode* node ) const
{
	if ( node == _null )
		return _false;

	ISerializableNodeRef parent_node = node->InsertChildNode( L"Properties", L"", _false );
	if ( parent_node.IsNull( ) )
		return _false;

	// Get the properties and prepare to sort it by key name
	Array< Pair< WStringPtr, Variable > > properties;
	for ( PropertyWithNameMap::Iterator it = mPropertiesWithName.GetHeadIterator( ); it.IsValid( ); ++ it )
		properties.InsertAscending< WStringPtr >( Pair< WStringPtr, Variable >( it.GetKey( ).Str( ), it.GetObject( ) ) );

	// Export properties
	for ( _dword i = 0; i < properties.Number( ); i ++ )
	{
		// Get the key string
		WStringPtr		key		= properties[i].mObject1;
		const Variable&	value	= properties[i].mObject2;

		// Create serializable node
		ISerializableNodeRef node = parent_node->InsertChildNode( L"Property", L"", _false );
		if ( node.IsNull( ) )
			return _false;

		node->Write( L"key", key );
		node->Write( L"value", value.ToString( ) );
	}

	return _true;
}

_void Properties::ClearProperties( )
{
	mPropertiesWithName.Clear( );
}

const PropertyWithNameMap& Properties::GetProperties( ) const
{
	return mPropertiesWithName;
}

const Variable& Properties::SetProperty( WStringPtr name, _int value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( WStringPtr name, _dword value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( WStringPtr name, _float value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( WStringPtr name, _double value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( WStringPtr name, WStringPtr value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( WStringPtr name, const WString& value )
{
	WString value_string = value;

	return SetPropertyValue( name, value_string );
}

const Variable& Properties::SetProperty( WStringPtr name, const Variable& value )
{
	return SetPropertyValue( name, value );
}

_ubool Properties::GetPropertyBool( WStringPtr name ) const
{
	return GetPropertyString( name ).IsEqual( L"true", _true );
}

_int Properties::GetPropertyLong( WStringPtr name ) const
{
	return GetPropertyValue< WStringPtr, _int >( name );
}

_dword Properties::GetPropertyDword( WStringPtr name ) const
{
	return GetPropertyValue< WStringPtr, _dword >( name );
}

_float Properties::GetPropertyFloat( WStringPtr name ) const
{
	return GetPropertyValue< WStringPtr, _float >( name );
}

_double Properties::GetPropertyDouble( WStringPtr name ) const
{
	return GetPropertyValue< WStringPtr, _double >( name );
}

WStringPtr Properties::GetPropertyString( WStringPtr name ) const
{
	const Variable* value = mPropertiesWithName.Search( name );
	if ( value == _null )
		return L"";

	return value->GetString( );
}

_ubool Properties::GetPropertyBool( WStringPtr name, _ubool& value ) const
{
	_boolean value_bool = _false;
	if ( GetPropertyValue< WStringPtr, _boolean >( name, value_bool ) == _false )
		return _false;

	value = value_bool;

	return _true;
}

_ubool Properties::GetPropertyLong( WStringPtr name, _int& value ) const
{
	return GetPropertyValue< WStringPtr, _int >( name, value );
}

_ubool Properties::GetPropertyDword( WStringPtr name, _dword& value ) const
{
	return GetPropertyValue< WStringPtr, _dword >( name, value );
}

_ubool Properties::GetPropertyFloat( WStringPtr name, _float& value ) const
{
	return GetPropertyValue< WStringPtr, _float >( name, value );
}

_ubool Properties::GetPropertyDouble( WStringPtr name, _double& value ) const
{
	return GetPropertyValue< WStringPtr, _double >( name, value );
}

_ubool Properties::GetPropertyString( WStringPtr name, WString& value ) const
{
	const Variable* property_value = mPropertiesWithName.Search( name );
	if ( property_value == _null )
		return _false;

	value = property_value->GetString( );

	return _true;
}

_ubool Properties::GetPropertyString( WStringPtr name, WStringObj& value ) const
{
	const Variable* property_value = mPropertiesWithName.Search( name );
	if ( property_value == _null )
		return _false;

	value = property_value->GetString( );

	return _true;
}

_void Properties::RemoveProperty( WStringPtr name )
{
	mPropertiesWithName.Remove( name );
}

_ubool Properties::HasProperty( WStringPtr name ) const
{
	return mPropertiesWithName.Search( name ) != _null;
}

const Variable& Properties::SetProperty( const WStringObj& name, _int value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( const WStringObj& name, _dword value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( const WStringObj& name, _float value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( const WStringObj& name, WStringPtr value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( const WStringObj& name, const WString& value )
{
	WString value_string = value;

	return SetPropertyValue( name, value_string );
}

const Variable& Properties::SetProperty( const WStringObj& name, const Variable& value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( const WString& name, _int value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( const WString& name, _dword value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( const WString& name, _float value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( const WString& name, WStringPtr value )
{
	return SetPropertyValue( name, value );
}

const Variable& Properties::SetProperty( const WString& name, const WString& value )
{
	WString value_string = value;

	return SetPropertyValue( name, value_string );
}

const Variable& Properties::SetProperty( const WString& name, const Variable& value )
{
	return SetPropertyValue( name, value );
}

_ubool Properties::GetPropertyBool( const WStringObj& name ) const
{
	return GetPropertyString( name ).IsEqual( L"true", _true );
}

_int Properties::GetPropertyLong( const WStringObj& name ) const
{
	return GetPropertyValue< WStringObj, _int >( name );
}

_dword Properties::GetPropertyDword( const WStringObj& name ) const
{
	return GetPropertyValue< WStringObj, _dword >( name );
}

_float Properties::GetPropertyFloat( const WStringObj& name ) const
{
	return GetPropertyValue< WStringObj, _float >( name );
}

_double Properties::GetPropertyDouble( const WStringObj& name ) const
{
	return GetPropertyValue< WStringObj, _double >( name );
}

WStringPtr Properties::GetPropertyString( const WStringObj& name ) const
{
	const Variable* value = mPropertiesWithName.Search( name );
	if ( value == _null )
		return L"";

	return value->GetString( );
}

_ubool Properties::GetPropertyBool( const WStringObj& name, _ubool& value ) const
{
	_boolean bool_value = _false;
	if ( GetPropertyValue< WStringObj, _boolean >( name, bool_value ) == _false )
		return _false;

	value = bool_value;

	return _true;
}

_ubool Properties::GetPropertyLong( const WStringObj& name, _int& value ) const
{
	return GetPropertyValue< WStringObj, _int >( name, value );
}

_ubool Properties::GetPropertyDword( const WStringObj& name, _dword& value ) const
{
	return GetPropertyValue< WStringObj, _dword >( name, value );
}

_ubool Properties::GetPropertyFloat( const WStringObj& name, _float& value ) const
{
	return GetPropertyValue< WStringObj, _float >( name, value );
}

_ubool Properties::GetPropertyDouble( const WStringObj& name, _double& value ) const
{
	return GetPropertyValue< WStringObj, _double >( name, value );
}

_ubool Properties::GetPropertyString( const WStringObj& name, WString& value ) const
{
	const Variable* property_value = mPropertiesWithName.Search( name );
	if ( property_value == _null )
		return _false;

	value = property_value->GetString( );

	return _true;
}

_ubool Properties::GetPropertyString( const WStringObj& name, WStringObj& value ) const
{
	const Variable* property_value = mPropertiesWithName.Search( name );
	if ( property_value == _null )
		return _false;

	value = property_value->GetString( );

	return _true;
}

_void Properties::RemoveProperty( const WStringObj& name )
{
	mPropertiesWithName.Remove( name );
}

_ubool Properties::HasProperty( const WStringObj& name ) const
{
	return mPropertiesWithName.Search( name ) != _null;
}

_void Properties::Combine( const IProperties* properties )
{
	// Combine properties with name
	Combine( properties->GetProperties( ) );
}

_void Properties::Combine( const PropertyWithNameMap& properties )
{
	// Combine properties with name
	for ( PropertyWithNameMap::Iterator it = properties.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		const WStringObj&	key		= it.GetKey( );
		const Variable&		value	= it.GetObject( );

		SetProperty( key, value );
	}
}
