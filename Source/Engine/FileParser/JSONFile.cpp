//! @file     JSONFile.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// JSONAttribute Implementation
//----------------------------------------------------------------------------

JSONAttribute::JSONAttribute( cJSON* json_attribute ) 
{
	mJSONAttribute = json_attribute;
}

JSONAttribute::~JSONAttribute( )
{
}

WStringR JSONAttribute::GetName( _ubool with_prefix ) const
{
	return WString( ).FromString( _ENCODING_UTF8, mJSONAttribute->string );
}

_ubool JSONAttribute::OnSetContentU( UStringPtr content )
{
	// Not support for this yet
	return _false;
}

_ubool JSONAttribute::OnSetContentW( WStringPtr content )
{
	return OnSetContentU( UString( ).FromString( content ) );
}

UStringPtr JSONAttribute::OnGetContentU( ) const
{
	return mJSONAttribute->valuestring;
}

_ubool JSONAttribute::OnGetValue( _ubool& value ) const
{
	if ( mJSONAttribute->type == cJSON_False )
	{
		value = _false;
		return _true;
	}

	if ( mJSONAttribute->type == cJSON_True )
	{
		value = _true;
		return _true;
	}

	if ( mJSONAttribute->type != cJSON_Number )
		return _false;

	value = EGE_BOOLEAN( mJSONAttribute->valueint );
	return _true;
}

_ubool JSONAttribute::OnGetValue( _int& value ) const
{
	if ( mJSONAttribute->type == cJSON_False )
	{
		value = 0;
		return _true;
	}

	if ( mJSONAttribute->type == cJSON_True )
	{
		value = 1;
		return _true;
	}
	
	if ( mJSONAttribute->type != cJSON_Number )
		return _false;

	value = mJSONAttribute->valueint;
	return _true;
}

_ubool JSONAttribute::OnGetValue( _dword& value ) const
{
	if ( mJSONAttribute->type == cJSON_False )
	{
		value = 0;
		return _true;
	}

	if ( mJSONAttribute->type == cJSON_True )
	{
		value = 1;
		return _true;
	}

	if ( mJSONAttribute->type != cJSON_Number )
		return _false;

	value = (_dword)mJSONAttribute->valueint;
	return _true;
}

_ubool JSONAttribute::OnGetValue( _large& value ) const
{
	if ( mJSONAttribute->type == cJSON_False )
	{
		value = 0;
		return _true;
	}

	if ( mJSONAttribute->type == cJSON_True )
	{
		value = 1;
		return _true;
	}

	if ( mJSONAttribute->type != cJSON_Number )
		return _false;

	value = (_large)mJSONAttribute->valueint;
	return _true;
}

_ubool JSONAttribute::OnGetValue( _qword& value ) const
{
	if ( mJSONAttribute->type == cJSON_False )
	{
		value = 0;
		return _true;
	}

	if ( mJSONAttribute->type == cJSON_True )
	{
		value = 1;
		return _true;
	}

	if ( mJSONAttribute->type != cJSON_Number )
		return _false;

	value = (_qword)mJSONAttribute->valueint;
	return _true;
}

_ubool JSONAttribute::OnGetValue( _float& value ) const
{
	if ( mJSONAttribute->type == cJSON_False )
	{
		value = 0.0f;
		return _true;
	}

	if ( mJSONAttribute->type == cJSON_True )
	{
		value = 1.0f;
		return _true;
	}

	if ( mJSONAttribute->type != cJSON_Number )
		return _false;

	value = (_float)mJSONAttribute->valuedouble;
	return _true;
}

_ubool JSONAttribute::OnGetValue( _double& value ) const
{
	if ( mJSONAttribute->type == cJSON_False )
	{
		value = 0.0;
		return _true;
	}

	if ( mJSONAttribute->type == cJSON_True )
	{
		value = 1.0;
		return _true;
	}

	if ( mJSONAttribute->type != cJSON_Number )
		return _false;

	value = mJSONAttribute->valuedouble;
	return _true;
}

//----------------------------------------------------------------------------
// JSONElement Implementation
//----------------------------------------------------------------------------

JSONElement::JSONElement( cJSON* json_element, JSONElement* parent, JSONElement* prev, JSONElement* next )
	: BaseClass( parent, prev, next ), mJSONElement( json_element )
{
	// Build sub-elements of array object
	if ( json_element->type == cJSON_Array )
	{
		for ( cJSON* json_sub_element = json_element->child; json_sub_element != _null; json_sub_element = json_sub_element->next )
			mJSONSubElements.Append( new JSONElement( json_sub_element, this, _null, _null ) );
	}
	else
	{
		JSONAttribute*	last_attribute	= _null;
		JSONElement*	last_child		= _null;

		// Set child elements
		for ( cJSON* element = mJSONElement->child; element != _null; element = element->next )
		{
			// It's sub-element
			if ( element->type == cJSON_Object || element->type == cJSON_Array )
			{
				if ( mFirstChildElement == _null )
				{
					SetFirstChildElement( new JSONElement( element, this, _null, _null ) );
					last_child = static_cast< JSONElement* >( mFirstChildElement );
				}	
				else
				{
					last_child->SetNextElement( new JSONElement( element, this, last_child, _null ) );
					last_child = static_cast< JSONElement* >( last_child->mNextElement );
				}
			}
			// It's attribute
			else
			{
				JSONAttribute* attribute = new JSONAttribute( element );

				mJSONAttributes[ attribute->GetName( ) ] = attribute;
			}
		}
	}
}

JSONElement::~JSONElement( )
{
	// Release all attributes
	for ( JSONAttributesMap::Iterator it = mJSONAttributes.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		JSONAttribute* attribute = it.GetObject( );
		EGE_DELETE( attribute );
	}

	// Release all sub elements
	for ( _dword i = 0; i < mJSONSubElements.Number( ); i ++ )
	{
		EGE_DELETE( mJSONSubElements[i] );
	}

	// Release all elements
	JSONElement* child = static_cast< JSONElement* >( mFirstChildElement );
	while ( child != _null )
	{
		JSONElement* next_child = static_cast< JSONElement* >( child->GetNextElement( ) );

		EGE_DELETE( child );

		child = next_child;
	}
}

_void JSONElement::UpdateAttribute( WStringPtr name, cJSON* json_value )
{
	EGE_ASSERT( json_value != _null );

	// Get the name as key in ANSI
	AString name_ansi = AString( ).FromString( name );

	// Create JSON value object
	cJSON* existing_json_value = ::cJSON_GetObjectItem( mJSONElement, name_ansi.Str( ) );
	if ( existing_json_value == _null )
		::cJSON_AddItemToObject( mJSONElement, name_ansi.Str( ), json_value );
	else
		::cJSON_ReplaceItemInObject( mJSONElement, name_ansi.Str( ), json_value );
}

IMarkupLangElementIteratorPassRef JSONElement::OnCreateElementIterator( IMarkupLangElement* element )
{
    return new MarkupLangElementIterator( element );
}

_void JSONElement::FreeJSONElement( )
{
	if ( mJSONElement != _null )
	{
		::cJSON_Delete( mJSONElement );
		mJSONElement = _null;
	}
}

_ubool JSONElement::IsArrayObject( ) const
{
	return mJSONElement->type == cJSON_Array;
}

_ubool JSONElement::SetName( WStringPtr name )
{
	// Not support for this yet
	return _false;
}

WStringR JSONElement::GetName( ) const
{
	return WString( ).FromString( _ENCODING_ANSI, (const _chara*)mJSONElement->string );
}

IMarkupLangElement* JSONElement::InsertChildElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj )
{
	// Create JSON object
	cJSON* json_object = is_array_obj ? ::cJSON_CreateArray( ) : ::cJSON_CreateObject( );
	if ( json_object == _null )
		return _null;

	// Add JSON object item
	::cJSON_AddItemToObject( mJSONElement, AString( ).FromString( name ).Str( ), json_object );

	// Update the first child element
	if ( mFirstChildElement == _null )
	{
		return mFirstChildElement = new JSONElement( json_object, this, _null, _null );
	}
	// Link as tail child element
	else
	{
		// Get the last child element
		JSONElement* last_child_element = static_cast< JSONElement* >( mFirstChildElement );
		while ( last_child_element->mNextElement != _null )
			last_child_element = static_cast< JSONElement* >( last_child_element->mNextElement );

		return last_child_element->mNextElement = new JSONElement( json_object, this, last_child_element, _null );
	}
}

IMarkupLangElement* JSONElement::InsertChildElementW( WStringPtr name, WStringPtr text, _ubool is_array_obj )
{
	return InsertChildElementU( name, UString( ).FromString( text ), is_array_obj );
}

IMarkupLangElement*	JSONElement::InsertChildArrayObj( WStringPtr name )
{
	// Create JSON array object 
	cJSON* json_object = ::cJSON_CreateArray( );
	if ( json_object == _null )
		return _null;

	// Add JSON object item
	::cJSON_AddItemToObject( mJSONElement, AString( ).FromString( name ).Str( ), json_object );

	// Update the first child element
	if ( mFirstChildElement == _null )
	{
		return mFirstChildElement = new JSONElement( json_object, this, _null, _null );
	}
	// Link as tail child element
	else
	{
		// Get the last child element
		JSONElement* last_child_element = static_cast< JSONElement* >( mFirstChildElement );
		while ( last_child_element->mNextElement != _null )
			last_child_element = static_cast< JSONElement* >( last_child_element->mNextElement );

		return last_child_element->mNextElement = new JSONElement( json_object, this, last_child_element, _null );
	}
}

IMarkupLangElement* JSONElement::AppendElementOfArrayObj( )
{
	// Create JSON object 
	cJSON* json_object = ::cJSON_CreateObject( );
	if ( json_object == _null )
		return _null;

	// Create temporary JSON element
	JSONElement json_element( json_object, _null, _null, _null );

	// Insert JSON element
	_dword index = AppendElementOfArrayObj( &json_element );
	if ( index != -1 )
		return mJSONSubElements[index];
	else
		return _null;
}

_dword JSONElement::AppendElementOfArrayObj( IMarkupLangElement* element )
{
	if ( element == _null )
		return -1;

	// Dump to string
	WString dump_string = element->DumpToString( );

	// Create the JSON element object
	cJSON* json_object = ::cJSON_Parse( AString( ).FromString( dump_string ).Str( ) );
	if ( json_object == _null )
		return -1;

	// Add element into array object
	::cJSON_AddItemToArray( mJSONElement, json_object );

	// Create wrapped JSON element 
	JSONElement* json_object_wrapped = new JSONElement( json_object, this, _null, _null );
	_dword index = mJSONSubElements.Append( json_object_wrapped );

	return index;
}

_dword JSONElement::AppendValueUOfArrayObj( _dword value )
{
	IMarkupLangElement* element = AppendElementOfArrayObj( );
	if ( element == _null )
		return -1;

	element->SetValueU( value );

	return mJSONSubElements.Number( ) - 1;
}

_dword JSONElement::AppendValueIOfArrayObj( _int value )
{
	IMarkupLangElement* element = AppendElementOfArrayObj( );
	if ( element == _null )
		return -1;

	element->SetValueI( value );

	return mJSONSubElements.Number( ) - 1;
}

_dword JSONElement::AppendValueFOfArrayObj( _float value )
{
	IMarkupLangElement* element = AppendElementOfArrayObj( );
	if ( element == _null )
		return -1;

	element->SetValueF( value );

	return mJSONSubElements.Number( ) - 1;
}

_dword JSONElement::AppendValueDOfArrayObj( _double value )
{
	IMarkupLangElement* element = AppendElementOfArrayObj( );
	if ( element == _null )
		return -1;

	element->SetValueD( value );

	return mJSONSubElements.Number( ) - 1;
}

_dword JSONElement::GetSubElementsNumber( ) const
{
	return mJSONSubElements.Number( );
}

IMarkupLangElement* JSONElement::GetSubElementByIndex( _dword index ) const
{
	if ( index >= mJSONSubElements.Number( ) )
		return _null;

	return mJSONSubElements[ index ];
}

_dword JSONElement::GetAttributesNumber( ) const
{
	return mJSONAttributes.Number( );
}

IMarkupLangAttribute* JSONElement::GetAttributeByIndex( _dword index ) const
{
	if ( mJSONAttributes.Number( ) == 0 )
		return _null;

	JSONAttributesMap::Iterator it = mJSONAttributes.GetHeadIterator( );
	for ( _dword i = 0; i < index; i ++ )
		++ it;

	return it.GetObject( );
}

_ubool JSONElement::HasAttribute( WStringPtr name, _ubool ignorecase ) const
{
	if ( ignorecase )
	{
		for ( JSONAttributesMap::Iterator it = mJSONAttributes.GetHeadIterator( ); it.IsValid( ); ++ it )
		{
			JSONAttribute* attribute = it.GetObject( );
			EGE_ASSERT( attribute != _null );

			WString attribute_name = attribute->GetName( );

			if ( attribute_name.IsEqual( name, ignorecase ) )
				return _true;
		}
	}
	else
	{
		if ( mJSONAttributes.HasKey( name ) )
			return _true;
	}

	return _false;
}

IMarkupLangAttribute* JSONElement::SearchAttribute( WStringPtr name, _ubool ignorecase ) const 
{
	if ( ignorecase )
	{
		for ( JSONAttributesMap::Iterator it = mJSONAttributes.GetHeadIterator( ); it.IsValid( ); ++ it )
		{
			JSONAttribute* attribute = it.GetObject( );
			EGE_ASSERT( attribute != _null );

			WString attribute_name = attribute->GetName( );

			if ( attribute_name.IsEqual( name, ignorecase ) )
				return attribute;
		}
	}
	else
	{
		const JSONAttribute* const* attribute = mJSONAttributes.Search( name );
		if ( attribute != _null )
			return (IMarkupLangAttribute*)*attribute;
	}

	return _null;
}

_dword JSONElement::GetValueU( ) const
{
	if ( mJSONElement->type == cJSON_Number )
		return mJSONElement->valueint;

	return 0;
}

_int JSONElement::GetValueI( ) const
{
	if ( mJSONElement->type == cJSON_Number )
		return mJSONElement->valueint;

	return 0;
}

_float JSONElement::GetValueF( ) const
{
	if ( mJSONElement->type == cJSON_Number )
		return (_float)mJSONElement->valuedouble;

	return 0.0f;
}

_double JSONElement::GetValueD( ) const
{
	if ( mJSONElement->type == cJSON_Number )
		return mJSONElement->valuedouble;

	return 0.0;
}

_ubool JSONElement::SetValueU( _dword value )
{
	if ( mJSONElement->type != cJSON_Number )
		return _false;

	mJSONElement->valueint = value;
	return _true;
}

_ubool JSONElement::SetValueI( _int value )
{
	if ( mJSONElement->type != cJSON_Number )
		return _false;

	mJSONElement->valueint = value;
	return _true;
}

_ubool JSONElement::SetValueF( _float value )
{
	if ( mJSONElement->type != cJSON_Number )
		return _false;

	mJSONElement->valuedouble = (_double)value;
	return _true;
}

_ubool JSONElement::SetValueD( _double value )
{
	if ( mJSONElement->type != cJSON_Number )
		return _false;

	mJSONElement->valuedouble = value;
	return _true;
}

_ubool JSONElement::GetText( AString& text ) const
{
	UString text_utf8;
	if ( GetText( text_utf8 ) == _false )
		return _false;

	text.FromString( text_utf8 );

	return _true;
}

_ubool JSONElement::GetText( UString& text ) const 
{
	if ( mJSONElement->type == cJSON_String )
	{
		text = mJSONElement->valuestring;
	}
	else if ( mJSONElement->string != _null )
	{
		text = mJSONElement->string;
	}
	else
	{
		// Find the "Text" attribute
		cJSON* json_text = ::cJSON_GetObjectItem( mJSONElement, "Text" );
		if ( json_text == _null )
			return _false;

		// Get the element text
		const _chara* text_utf8 = json_text->valuestring;
		if ( text_utf8 == _null )
			return _false;

		// Feedback the text
		text = text_utf8;
	}

	return _true;
}

_ubool JSONElement::GetText( WString& text ) const 
{
	UString text_utf8;
	if ( GetText( text_utf8 ) == _false )
		return _false;

	// Feedback the text
	text.FromString( text_utf8 );

	return _true;
}

AStringR JSONElement::GetTextA( ) const
{
	AString text;
	if ( GetText( text ) == _false )
		return AString( "" );

	return text;
}

UStringR JSONElement::GetTextU( ) const
{
	UString text;
	if ( GetText( text ) == _false )
		return UString( "" );

	return text;
}

WStringR JSONElement::GetTextW( ) const
{
	WString text;
	if ( GetText( text ) == _false )
		return WString( L"" );

	return text;
}

_ubool JSONElement::SetText( AStringPtr text )
{
	// Not support for this yet
	return _false;
}

_ubool JSONElement::SetText( UStringPtr text )
{
	// Not support for this yet
	return _false;
}

_ubool JSONElement::SetText( WStringPtr text )
{
	return SetText( UString( ).FromString( text ) );
}

_ubool JSONElement::SetAttributeBool( WStringPtr name, _ubool value )
{
	// Create JSON object
	cJSON* json_value = ::cJSON_CreateBool( EGE_BOOLEAN( value ) );
	if ( json_value == _null )
		return _false;

	UpdateAttribute( name, json_value );

	return _true;
}

_ubool JSONElement::SetAttributeLong( WStringPtr name, _int value )
{
	// Create JSON object
	cJSON* json_value = ::cJSON_CreateNumber( (_double)value );
	if ( json_value == _null )
		return _false;

	UpdateAttribute( name, json_value );

	return _true;
}

_ubool JSONElement::SetAttributeDword( WStringPtr name, _dword value )
{
	// Create JSON object
	cJSON* json_value = ::cJSON_CreateNumber( (_double)value );
	if ( json_value == _null )
		return _false;

	UpdateAttribute( name, json_value );

	return _true;
}

_ubool JSONElement::SetAttributeQword( WStringPtr name, _qword value )
{
	// Create JSON object
	cJSON* json_value = ::cJSON_CreateNumber( (_double)value );
	if ( json_value == _null )
		return _false;

	UpdateAttribute( name, json_value );

	return _true;
}

_ubool JSONElement::SetAttributeDouble( WStringPtr name, _double value )
{
	// Create JSON object
	cJSON* json_value = ::cJSON_CreateNumber( value );
	if ( json_value == _null )
		return _false;

	UpdateAttribute( name, json_value );

	return _true;
}

_ubool JSONElement::SetAttributeString( WStringPtr name, UStringPtr string )
{
	// Create JSON string object
	cJSON* json_value = ::cJSON_CreateString( string.Str( ) );
	if ( json_value == _null )
		return _false;

	UpdateAttribute( name, json_value );

	return _true;
}

_ubool JSONElement::SetAttributeString( WStringPtr name, WStringPtr string )
{
	return SetAttributeString( name, UString( ).FromString( string ) );
}

WStringR JSONElement::DumpToString( ) const
{
	_chara* json_string = ::cJSON_Print( mJSONElement );
	EGE_ASSERT( json_string != _null );

	WString json_string_utf16;
	json_string_utf16.FromString( _ENCODING_UTF8, json_string );

	JSONFile::OnFreeFunc( json_string );

	return json_string_utf16;
}

WStringR JSONElement::DumpToSchemaString( ) const
{
	return WString( L"" );
}

//----------------------------------------------------------------------------
// JSONFile Implementation
//----------------------------------------------------------------------------

JSONFile::JSONFile( )
{
	mRootElement = _null;
}

JSONFile::~JSONFile( )
{
	Unload( );
}

void* JSONFile::OnMallocFunc( size_t size )
{
	return Memory::GetInstance( ).Alloc( size, _FILENAME_A, _LINENUMBER );
}

void JSONFile::OnFreeFunc( void* pointer )
{
	Memory::GetInstance( ).Free( pointer, _FILENAME_A, _LINENUMBER );
}

_ubool JSONFile::Initialize( )
{
	cJSON_Hooks hooks;
	hooks.malloc_fn = OnMallocFunc;
	hooks.free_fn	= OnFreeFunc;

	::cJSON_InitHooks( &hooks );

	return _true;
}

_void JSONFile::Finalize( )
{

}

_FILE_FORMAT JSONFile::GetFileID( ) const
{
	return _FF_JSON;
}

_ubool JSONFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Get the stream size in bytes
	_dword size = stream_reader->GetSize( );
	if ( size == 0 )
		return _false;

	// Create the JSON string buffer ( the last slot is '\0' )
	MemArrayPtr< _chara > json_string_buffer( size + 1 ); json_string_buffer[ size ] = 0;
	stream_reader->ReadBuffer( json_string_buffer, size );

	// Skip the UTF-8 header if needed
	const _chara* json_string = json_string_buffer;
	SKIP_UTF_CODE( json_string, size );

	// Parse the JSON file
	cJSON* json_root_element = ::cJSON_Parse( json_string );
	if ( json_root_element == _null )
	{
		// Output the json parse error location of string
		const _chara* err_json_string_location = cJSON_GetErrorPtr( );
		if ( err_json_string_location != _null )
		{
			const _dword cMaxErrorStringLength = 256;
			_chara err_string_info[ cMaxErrorStringLength ];
			SafeCopyString( err_string_info, err_json_string_location );

			ALOG_ERROR_2( "Parse json string failed, err index: %d, err string start from: %s", 
				(_dword)(size_t)(err_json_string_location - json_string), (const _chara*) err_string_info );
		}

		return _false;
	}

	// Build the root element
	mRootElement = new JSONElement( json_root_element, _null, _null, _null );

	return _true;
}

_void JSONFile::Unload( )
{
	// Free JSON element
	if ( mRootElement != _null )
		mRootElement->FreeJSONElement( );

	// Delete root element
	EGE_DELETE( mRootElement );
}

_ubool JSONFile::SaveToStream( IStreamWriter* stream_writer, _dword flags ) const
{
	if ( stream_writer == _null )
		return _false;

	// Make sure the root element is existing
	if ( mRootElement == _null )
		return _false;

	// Dump to string
	WString dump_string = mRootElement->DumpToString( );

	// Save the JSON string from root element
	AString string = AString( ).FromString( dump_string );
	stream_writer->WriteBuffer( string.Str( ), string.GetLength( ) );

	return _true;
}

IMarkupLangDeclaration*	JSONFile::GetDeclaration( )
{
	// Not support for this yet
	return _null;
}

IMarkupLangElement*	JSONFile::GetRootElement( )
{
	if ( mRootElement == _null )
		mRootElement = new JSONElement( cJSON_CreateObject( ), _null, _null, _null );

	return mRootElement;
}

_ubool JSONFile::SchemaValidate( WStringPtr filename )
{
	// Not support for this yet
	return _false;
}

_ubool JSONFile::SchemaValidate( IStreamReader* stream_reader )
{
	// Not support for this yet
	return _false;
}