//! @file     XMLFile.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// XMLAttribute Implementation
//----------------------------------------------------------------------------

XMLAttribute::XMLAttribute( xmlAttrPtr xml_attribute )
{
	mXMLAttribute = xml_attribute;
}

XMLAttribute::~XMLAttribute( )
{
}

WString XMLAttribute::GetName( _ubool with_prefix ) const
{
	// Get the attribute key name
#ifdef _USE_TINY_XML2_
	const _chara* key_name		= mXMLAttribute->Name( );
	const _chara* prefix_name	= _null;
#else
	const _chara* key_name		= (const _chara*) (mXMLAttribute->name);
	const _chara* prefix_name	= (const _chara*) (mXMLAttribute->ns != _null ? mXMLAttribute->ns->prefix : _null);
#endif
	
	WString name;
	if ( with_prefix && prefix_name != _null )
	{
		name.FromString( _ENCODING_UTF8, prefix_name );
		name += L":";
		name += WString( ).FromString( _ENCODING_UTF8, key_name );
	}
	else
	{
		name = WString( ).FromString( _ENCODING_UTF8, key_name );
	}

	return name;
}

_ubool XMLAttribute::OnSetContentU( UStringPtr content )
{
#ifdef _USE_TINY_XML2_
	mXMLAttribute->SetAttribute( content.Str( ) );
#else
	::xmlNodeSetContent( mXMLAttribute->children, (const xmlChar*) content.Str( ) );
#endif

	return _true;
}

_ubool XMLAttribute::OnSetContentW( WStringPtr content )
{
	return OnSetContentU( UString( ).FromString( content ) );
}

UStringPtr XMLAttribute::OnGetContentU( ) const
{
#ifdef _USE_TINY_XML2_
	return mXMLAttribute->Value( );
#else
	return (const _chara*) mXMLAttribute->children->content;
#endif
}

_ubool XMLAttribute::OnGetValue( _ubool& value ) const
{
	UString content = OnGetContentU( );

	if ( content.IsEqual( "true", _true ) )
	{
		value = _true;
	}
	else if ( content.IsEqual( "false", _true ) )
	{
		value = _false;
	}
	else
	{
		value = EGE_BOOLEAN( content.ToDword( 10 ) );
	}

	return _true;
}

_ubool XMLAttribute::OnGetValue( _int& value ) const
{
	UString content = OnGetContentU( );

	_dword radix = 10;
	if ( content.StartsWith( "0x", _true ) )
	{
		radix	= 16;
		content = content.SubString( 2 );
	}

	value = content.ToLong( radix );

	return _true;
}

_ubool XMLAttribute::OnGetValue( _dword& value ) const
{
	UString content = OnGetContentU( );

	_dword radix = 10;
	if ( content.StartsWith( "0x", _true ) )
	{
		radix	= 16;
		content = content.SubString( 2 );
	}

	value = content.ToDword( radix );

	return _true;
}

_ubool XMLAttribute::OnGetValue( _large& value ) const
{
	UString content = OnGetContentU( );

	_dword radix = 10;
	if ( content.StartsWith( "0x", _true ) )
	{
		radix = 16;
		content = content.SubString( 2 );
	}

	value = content.ToLarge( radix );

	return _true;
}

_ubool XMLAttribute::OnGetValue( _qword& value ) const
{
	UString content = OnGetContentU( );

	_dword radix = 10;
	if ( content.StartsWith( "0x", _true ) )
	{
		radix = 16;
		content = content.SubString( 2 );
	}

	value = content.ToQword( radix );

	return _true;
}

_ubool XMLAttribute::OnGetValue( _float& value ) const
{
	value = OnGetContentU( ).ToFloat( );

	return _true;
}

_ubool XMLAttribute::OnGetValue( _double& value ) const
{
	value = OnGetContentU( ).ToDouble( );

	return _true;
}

//----------------------------------------------------------------------------
// XMLElement Implementation
//----------------------------------------------------------------------------

XMLElement::XMLElement( xmlDocPtr xml_doc, xmlNodePtr xml_element, XMLElement* parent, XMLElement* prev, XMLElement* next )
	: BaseClass( parent, prev, next ), mXMLDocument( xml_doc ), mXMLElement( xml_element )
{
	// Set attributes
#ifdef _USE_TINY_XML2_
	for ( xmlAttrPtr attribute = (xmlAttrPtr)mXMLElement->FirstAttribute( ); attribute != _null; attribute = (xmlAttrPtr)attribute->Next( ) )
	{
#else
	for ( xmlAttrPtr attribute = mXMLElement->properties; attribute != _null; attribute = attribute->next )
	{
		// Only works for attribute type
		if ( attribute->type != XML_ATTRIBUTE_NODE )
			continue;
#endif

		XMLAttribute* xml_attribute = new XMLAttribute( attribute );

		// Update XML attributes
		mXMLAttributes[ xml_attribute->GetName( ) ] = xml_attribute;
	}

	XMLElement*	 last_child = _null;

	// Set child elements
#ifdef _USE_TINY_XML2_
	for ( xmlNodePtr element = mXMLElement->FirstChildElement( ); element != _null; element = element->NextSiblingElement( ) )
	{
#else
	for ( xmlNodePtr element = ::xmlFirstElementChild( mXMLElement ); element != _null; element = element->next )
	{
		// Only works for element type
		if ( element->type != XML_ELEMENT_NODE )
			continue;
#endif

		if ( mFirstChildElement == _null )
		{
			SetFirstChildElement( new XMLElement( xml_doc, element, this, _null, _null ) );
			last_child = static_cast< XMLElement* >( mFirstChildElement );
		}	
		else
		{
			last_child->SetNextElement( new XMLElement( xml_doc, element, this, last_child, _null ) );
			last_child = static_cast< XMLElement* >( last_child->mNextElement );
		}
	}
}

XMLElement::~XMLElement( )
{
	// Release all attributes
	for ( XMLAttributesMap::Iterator it = mXMLAttributes.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		XMLAttribute* attribute = it.GetObject( );
		EGE_DELETE( attribute );
	}

	// Release all elements
	XMLElement* child = static_cast< XMLElement* >( mFirstChildElement );
	while ( child != _null )
	{
		XMLElement* next_child = static_cast< XMLElement* >( child->GetNextElement( ) );

		EGE_DELETE( child );

		child = next_child;
	}
}

_int XMLElement::OnXMLOutputWriteFunc( _void* context, const _chara* buffer, _int len )
{
	if ( buffer == _null || len == 0 )
		return 0;

	WString& xml_string = *(WString*) context;

	// Convert UTF-8 to UTF-16 string
	UString utf8_string( buffer, len );
	xml_string += WString( ).FromString( utf8_string );

	return len;
}

IMarkupLangElementIteratorPassRef XMLElement::OnCreateElementIterator( IMarkupElement* element )
{
    return new MarkupLangElementIterator( element );
}

_ubool XMLElement::SetName( WStringPtr name )
{
	UString name_utf8;
	name_utf8.FromString( _ENCODING_UTF16, name.Str( ) );

#ifdef _USE_TINY_XML2_
	mXMLElement->SetName( name_utf8.Str( ) );
#else
	::xmlNodeSetName( mXMLElement, (const xmlChar*) name_utf8.Str( ) );
#endif

	return _true;
}

WString XMLElement::GetName( ) const
{
	// Get the XML name
	WString name;
#ifdef _USE_TINY_XML2_
	name.FromString( _ENCODING_UTF8, (const _chara*)mXMLElement->Name( ) );
#else
	name.FromString( _ENCODING_UTF8, (const _chara*)mXMLElement->name );
#endif

	return name;
}

IMarkupElement* XMLElement::InsertChildElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj )
{
	// Get the name in UTF-8 mode
	UString name_utf8;
	name_utf8.FromString( _ENCODING_UTF16, name.Str( ) );

#ifdef _USE_TINY_XML2_
	tinyxml2::XMLElement* tiny_element = mXMLDocument->NewElement( name_utf8.Str( ) );
	if ( tiny_element == _null )
		return _null;

	if ( text.IsEmpty( ) == _false )
		tiny_element->InsertFirstChild( mXMLDocument->NewText( text.Str( ) ) );  

	xmlNodePtr xml_child_element = (xmlNodePtr) mXMLElement->InsertEndChild( tiny_element );
#else
	// Insert a child XML node (the libxml2 use NULL as empty text, if we don't use NULL then the node will link together without new line tag)
	xmlNodePtr xml_child_element = ::xmlNewChild( mXMLElement, _null, (const xmlChar*) name_utf8.Str( ), text.IsEmpty( ) ? NULL : (const xmlChar*) text.Str( ) );
#endif
	if ( xml_child_element == _null )
		return _null;

	// Update the child element
	if ( mFirstChildElement == _null )
	{
		return mFirstChildElement = new XMLElement( mXMLDocument, xml_child_element, this, _null, _null );
	}
	else
	{
		// Get the last child element
		XMLElement* last_child_element = static_cast< XMLElement* >( mFirstChildElement );
		while ( last_child_element->mNextElement != _null )
			last_child_element = static_cast< XMLElement* >( last_child_element->mNextElement );

		return last_child_element->mNextElement = new XMLElement( mXMLDocument, xml_child_element, this, last_child_element, _null );
	}
}

IMarkupElement* XMLElement::InsertNextElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj )
{
	// Get the name in UTF-8 mode
	UString name_utf8;
	name_utf8.FromString( _ENCODING_UTF16, name.Str( ) );

#ifdef _USE_TINY_XML2_
	tinyxml2::XMLElement* tiny_element = mXMLDocument->NewElement( name_utf8.Str( ) );
	if ( tiny_element == _null )
		return _null;

	xmlNodePtr xml_next_element = (xmlNodePtr) mXMLElement->Parent( )->InsertAfterChild( mXMLElement, tiny_element );
#else
	// Insert a child XML node (the libxml2 use NULL as empty text, if we don't use NULL then the node will link together without new line tag)
	xmlNodePtr xml_next_element = ::xmlNewNode( _null, (const xmlChar*) name_utf8.Str( ) );
	xmlAddNextSibling( mXMLElement, xml_next_element );
#endif
	if ( xml_next_element == _null )
		return _null;

	// Update the next element
	if ( mNextElement == _null )
	{
		mNextElement = new XMLElement( mXMLDocument, xml_next_element, (XMLElement*) mParentElement, this, _null );
	}
	else
	{
		XMLElement* next_element = (XMLElement*) mNextElement; next_element->mPrevElement = _null;
		mNextElement = new XMLElement( mXMLDocument, xml_next_element, (XMLElement*) mParentElement, this, next_element );
	}

	mNextElement->SetText( text );

	return mNextElement;
}

_void XMLElement::RemoveElement( IMarkupElement* element )
{
	XMLElement* xml_element = static_cast< XMLElement* >( element );
	if ( xml_element == _null )
		return;

#ifdef _USE_TINY_XML2_
	xml_element->mXMLElement->Parent( )->DeleteChild( xml_element->mXMLElement );
#else
	xmlUnlinkNode( xml_element->mXMLElement );
	xmlFreeNode( xml_element->mXMLElement );
#endif

	EGE_DELETE( xml_element );
}

IMarkupLangElementIteratorPassRef XMLElement::RemoveElement( IMarkupLangElementIterator* it )
{
	if ( it == _null )
		return _null;

	IMarkupElement* markup_lang_element = it->GetObject( );
	if ( markup_lang_element == _null )
		return _null;

	// Get the next element
	IMarkupElement* next_xml_element = markup_lang_element->GetNextElement( );

	RemoveElement( markup_lang_element );

	// Feedback the next element
	return new MarkupLangElementIterator( next_xml_element );
}

_dword XMLElement::GetAttributesNumber( ) const
{
	return mXMLAttributes.Number( );
}

IMarkupAttribute* XMLElement::GetAttributeByIndex( _dword index ) const
{
	if ( mXMLAttributes.Number( ) == 0 )
		return _null;

	XMLAttributesMap::Iterator it = mXMLAttributes.GetHeadIterator( );
	for ( _dword i = 0; i < index; i ++ )
		++ it;

	return it.GetObject( );
}

_ubool XMLElement::HasAttribute( WStringPtr name, _ubool ignorecase ) const
{
	if ( ignorecase )
		return BaseClass::HasAttribute( name, ignorecase );
	else
		return mXMLAttributes.HasKey( name );
}

IMarkupAttribute* XMLElement::SearchAttribute( WStringPtr name, _ubool ignorecase ) const
{
	if ( ignorecase )
	{
		return BaseClass::SearchAttribute( name, ignorecase );
	}
	else
	{
		XMLAttribute*const* xml_attribute = mXMLAttributes.Search( name );
		if ( xml_attribute == _null )
			return _null;

		return *xml_attribute;
	}
}

_dword XMLElement::GetValueU( ) const
{
	UString text = GetTextU( );

	return text.ToDword( 10 );
}

_int XMLElement::GetValueI( ) const
{
	UString text = GetTextU( );

	return text.ToLong( 10 );
}

_float XMLElement::GetValueF( ) const
{
	UString text = GetTextU( );

	return text.ToFloat( );
}

_double XMLElement::GetValueD( ) const
{
	UString text = GetTextU( );

	return text.ToDouble( );
}

_ubool XMLElement::SetValueU( _dword value )
{
	return SetText( WString( ).FromValue( value, 10 ) );
}

_ubool XMLElement::SetValueI( _int value )
{
	return SetText( WString( ).FromValue( value, 10 ) );
}

_ubool XMLElement::SetValueF( _float value )
{
	return SetText( WString( ).FromValue( value ) );
}

_ubool XMLElement::SetValueD( _double value )
{
	return SetText( WString( ).FromValue( value ) );
}

_ubool XMLElement::GetText( AString& text ) const
{
	UString text_utf8;
	if ( GetText( text_utf8 ) == _false )
		return _false;

	text.FromString( text_utf8 );

	return _true;
}

_ubool XMLElement::GetText( UString& text ) const 
{
#ifdef _USE_TINY_XML2_
	text = mXMLElement->GetText( );
#else
	const _xmlNode* child_node = mXMLElement->children;
	if ( child_node == _null )
		return _false;

	const _chara* text_utf8 = _null;

	// It's CDATA string
	if ( child_node->next != _null && child_node->next->type == XML_CDATA_SECTION_NODE )
	{
		text_utf8 = (const _chara*) child_node->next->content;
	}
	// It's normal string
	else
	{
		text_utf8 = (const _chara*) child_node->content;
	}

	if ( text_utf8 == _null )
		return _false;

	// Feedback the text
	text = text_utf8;
#endif

	return _true;
}

_ubool XMLElement::GetText( WString& text ) const 
{
#ifdef _USE_TINY_XML2_
	// Feedback the text
	text.FromString( _ENCODING_UTF8, mXMLElement->GetText( ) );
#else
	const _xmlNode* text_node = mXMLElement->children;
	if ( text_node == _null )
		return _false;

	// It's text node
	if ( text_node->type == XML_TEXT_NODE )
	{
		// It's CDATA section
		if ( text_node->next != _null && text_node->next->type == XML_CDATA_SECTION_NODE )
			text_node = text_node->next;
	}

	// Get the element text
	const _chara* text_utf8 = (const _chara*) text_node->content;
	if ( text_utf8 == _null )
		return _false;

	// Feedback the text
	text.FromString( _ENCODING_UTF8, text_utf8 );
#endif

	return _true;
}

AString XMLElement::GetTextA( ) const
{
	AString text;
	if ( GetText( text ) == _false )
		return AString( "" );

	return text;
}

UString XMLElement::GetTextU( ) const
{
	UString text;
	if ( GetText( text ) == _false )
		return UString( "" );

	return text;
}

WString XMLElement::GetTextW( ) const
{
	WString text;
	if ( GetText( text ) == _false )
		return WString( L"" );

	return text;
}

_ubool XMLElement::SetText( AStringPtr text )
{
#ifdef _USE_TINY_XML2_
	mXMLElement->SetText( text.Str( ) );
#else
	::xmlNodeSetContent( mXMLElement, (const xmlChar*)text.Str( ) );
#endif

	return _true;
}

_ubool XMLElement::SetText( UStringPtr text )
{
#ifdef _USE_TINY_XML2_
	mXMLElement->SetText( text.Str( ) );
#else
	::xmlNodeSetContent( mXMLElement, (const xmlChar*) text.Str( ) );
#endif

	return _true;
}

_ubool XMLElement::SetText( WStringPtr text )
{
	return SetText( UString( ).FromString( text ) );
}

_ubool XMLElement::SetAttributeString( WStringPtr name, UStringPtr string )
{
	// Get the name in UTF8 format
	_chara name_utf8[256];
	Platform::Utf16ToUtf8( name_utf8, 256, name.Str( ) );

	// Get the name in UTF8 format without prefix
	_chara name_without_prefix_utf8[256];
	_dword index = name.SearchL2R( ':' );
	if ( index != -1 )
		Platform::Utf16ToUtf8( name_without_prefix_utf8, 256, name.SubString( index + 1 ).Str( ) );
	else
		Platform::Utf16ToUtf8( name_without_prefix_utf8, 256, name.Str( ) );

	// The XML attribute
	XMLAttribute* new_xml_attribute = _null;

#ifdef _USE_TINY_XML2_
	// First try to find attribute
	const xmlAttrPtr exist_xml_attribute = (const xmlAttrPtr)((const tinyxml2::XMLElement*) mXMLElement)->FindAttribute( name_without_prefix_utf8 );

	// It's new attribute
	if ( exist_xml_attribute == _null )
	{
		// Create XML attribute
		mXMLElement->SetAttribute( name_utf8, string.Str( ) );
		xmlAttrPtr xml_attribute = (xmlAttrPtr)((const tinyxml2::XMLElement*) mXMLElement)->FindAttribute( name_utf8 );
		EGE_ASSERT( xml_attribute != _null );

		// Link to XML element
		new_xml_attribute = new XMLAttribute( xml_attribute );
	}
	// Update the existing attribute
	else
	{
		mXMLElement->SetAttribute( name_utf8, string.Str( ) );
	}
#else
	// It's new attribute
	if ( ::xmlHasProp( mXMLElement, (const xmlChar*) name_without_prefix_utf8 ) == _null )
	{
		// Create XML attribute
		xmlAttrPtr xml_attribute = ::xmlNewProp( mXMLElement, (const xmlChar*) name_utf8, (const xmlChar*) string.Str( ) );
		if ( xml_attribute == _null )
			return _false;

		// Link to XML element
		if ( mFirstAttribute == _null )
		{
			new_xml_attribute	= new XMLAttribute( xml_attribute, _null, _null );
			mFirstAttribute		= new_xml_attribute;
		}
		else
		{
			XMLAttribute* attribute = static_cast< XMLAttribute* >( mFirstAttribute );
			while ( attribute->NextAttribute( ) != _null )
				attribute = static_cast< XMLAttribute* >( attribute->NextAttribute( ) );

			new_xml_attribute = new XMLAttribute( xml_attribute, attribute, _null );
			attribute->SetNextAttribute( new_xml_attribute );
		}
	}
	// Update the existing attribute
	else
	{
		::xmlSetProp( mXMLElement, (const xmlChar*) name_utf8, (const xmlChar*) string.Str( ) );
	}
#endif

	// Update XML attributes
	if ( new_xml_attribute != _null )
		mXMLAttributes[ new_xml_attribute->GetName( ) ] = new_xml_attribute;

	return _true;
}

_ubool XMLElement::SetAttributeString( WStringPtr name, WStringPtr string )
{
	// Get the name in UTF-8 mode
	UString string_utf8;
	string_utf8.FromString( _ENCODING_UTF16, string.Str( ) );

	return SetAttributeString( name, string_utf8 );
}

WString XMLElement::DumpToString( ) const
{
#ifdef _USE_TINY_XML2_
	tinyxml2::XMLPrinter tiny_printer;
	mXMLElement->Accept( &tiny_printer );

	return WString( ).FromString( _ENCODING_UTF8, tiny_printer.CStr( ) );
#else
	// Allocate the output buffer
	xmlOutputBufferPtr xml_output_buffer = ::xmlAllocOutputBuffer( _null );
	if ( xml_output_buffer == _null )
		return WString( L"" );

	// Initialize the output buffer
	WString xml_string;
	xml_output_buffer->context			= &xml_string;
	xml_output_buffer->writecallback	= OnXMLOutputWriteFunc;
	xml_output_buffer->closecallback	= _null;

	// Dump string
	::xmlNodeDumpOutput( xml_output_buffer, _null, mXMLElement, 0, 1, _null );

	// Close output buffer
	::xmlOutputBufferClose( xml_output_buffer );

	return xml_string;
#endif
}

WString XMLElement::DumpToSchemaString( ) const
{
	return WString( L"" );
}

//----------------------------------------------------------------------------
// XMLFileDeclaration Implementation
//----------------------------------------------------------------------------

XMLFileDeclaration::XMLFileDeclaration( xmlDocPtr document )
	: BaseClass( _ENCODING_UNKNOWN, Version::cZero )
{
	mXmlDocument = document;

#ifdef _USE_TINY_XML2_
	if ( mXmlDocument->FirstChild( )->ToDeclaration( ) == _null )
		mXmlDocument->InsertFirstChild( mXmlDocument->NewDeclaration( "xml version=\"1.0\" encoding=\"utf-8\"" ) );
#else
	SetVersion( Version( AStringPtr( (const _chara*) document->version ) ) );
	SetEncoding( (const _chara*) document->encoding ); 
#endif
}

XMLFileDeclaration::~XMLFileDeclaration( )
{

}

_void XMLFileDeclaration::SetDocVersion( UStringPtr version )
{
#ifdef _USE_TINY_XML2_
#else
	// We just need major and minor version ( we can use ANSI to fix it )
	AString fixed_version = Path::GetFileName( Path::GetFileName( version.Str( ), _false ), _false );

	// Create version string buffer
	xmlChar* version_string_buffer = (xmlChar*) ::xmlMalloc( fixed_version.SizeOfBytes( ) );
	EGE_MEM_CPY( version_string_buffer, fixed_version.Str( ), fixed_version.SizeOfBytes( ) );

	// Update document version
	::xmlFree( (_void*) mXmlDocument->version );
	mXmlDocument->version = version_string_buffer;
#endif
}

_void XMLFileDeclaration::SetDocEncoding( UStringPtr encoding )
{
#ifdef _USE_TINY_XML2_
#else
	// Create encoding string buffer
	xmlChar* encoding_string_buffer = (xmlChar*) ::xmlMalloc( encoding.SizeOfBytes( ) );
	EGE_MEM_CPY( encoding_string_buffer, encoding.Str( ), encoding.SizeOfBytes( ) );

	// Update document encoding
	::xmlFree( (_void*) mXmlDocument->encoding );
	mXmlDocument->encoding = encoding_string_buffer;
#endif
}

_void XMLFileDeclaration::SetVersion( const Version& version )
{
	BaseClass::SetVersion( version );

	SetDocVersion( version.ToUString( ) );
}

_void XMLFileDeclaration::SetEncoding( _ENCODING encoding )
{
	BaseClass::SetEncoding( encoding );

	SetDocEncoding( UString( ).FromString( OnQueryEncodingEnumCallback( encoding ) ) );
}

//----------------------------------------------------------------------------
// XMLFile Implementation
//----------------------------------------------------------------------------

XMLFile::XMLFile( )
{
	mXmlDocument	= _null;

	mDeclaration	= _null;
	mRootElement	= _null;

	// Set the error callback functions
#ifndef _USE_TINY_XML2_
	::xmlSetStructuredErrorFunc( this, OnXMLStructuredErrorFunc );
	::xmlThrDefSetStructuredErrorFunc( this, OnXMLStructuredErrorFunc );
	::xmlSetGenericErrorFunc( this, OnXMLGenericErrorFunc );
	::xmlThrDefSetGenericErrorFunc( this, OnXMLGenericErrorFunc );
#endif
}

XMLFile::~XMLFile( )
{
	Unload( );
}

void XMLFile::OnXMLFreeFunc( void* mem )
{
	Memory::GetInstance( ).Free( mem, _FILENAME_A, _LINENUMBER );
}

void* XMLFile::OnXMLMallocFunc( size_t size )
{
	return Memory::GetInstance( ).Alloc( size, _FILENAME_A, _LINENUMBER );
}

void* XMLFile::OnXMLReallocFunc( void* mem, size_t size )
{
	return Memory::GetInstance( ).Realloc( mem, size, _FILENAME_A, _LINENUMBER );
}

char* XMLFile::OnXMLStrdupFunc( const char* str )
{
	return Memory::GetInstance( ).AllocStr( str, _FILENAME_A, _LINENUMBER );
}

#ifndef _USE_TINY_XML2_

_void XMLFile::OnXMLGenericErrorFunc( _void* ctx, const _chara* msg, ... )
{
	XMLFile* xml_file = (XMLFile*) ctx;
	EGE_ASSERT( xml_file != _null );

	_chara buffer[8192];

	// Build the error message
#ifdef __GNUC__
	va_list args;
	va_start( args, msg );
	vsnprintf( buffer, 8192, msg, args );
	va_end( args );
#else
	::_vsnprintf_s( buffer, 8192, _TRUNCATE, msg, (_chara*)( &msg ) + sizeof( msg ) );
#endif

	// Output the error string
	ALOG_ERROR_1( "Generic XML Error: %s", (const _chara*) buffer );
}

_void XMLFile::OnXMLStructuredErrorFunc( _void* userdata, xmlErrorPtr error )
{
	XMLFile* xml_file = (XMLFile*) userdata;
	EGE_ASSERT( xml_file != _null );
	
	// Remove the '\r\n' characters, we let the user to determine the error text format
	AString error_message( error->message );
	error_message.TrimRight( "\r\n" );

	// Output message
	if ( error->level == XML_ERR_WARNING )
	{
		ALOG_WARNING_2( "Structured XML Warning: (%d)%s", error->line, error_message.Str( ) );
	}
	else
	{
		ALOG_ERROR_2( "Structured XML Error: (%d)%s", error->line, error_message.Str( ) );
	}
}

_int XMLFile::OnXMLOutputWriteFunc( _void* context, const _chara* buffer, _int len )
{
	if ( buffer == _null || len == 0 )
		return 0;

	IStreamWriter* stream_writer = (IStreamWriter*) context;
	EGE_ASSERT( stream_writer != _null );

	_dword write_bytes = stream_writer->WriteBuffer( buffer, len );
	if ( write_bytes == 0 )
		return 0;

	return (_int)write_bytes;
}

#endif

#ifndef _USE_TINY_XML2_

_ubool XMLFile::SchemaValidate( xmlSchemaParserCtxtPtr parser_context )
{
	EGE_ASSERT( parser_context != _null );

	xmlSchemaValidCtxtPtr	schema_valid_context	= _null;
	_ubool					result					= _false;

	// Parse the XSD file
	xmlSchemaPtr schema = ::xmlSchemaParse( parser_context );
	if ( schema != _null )
	{
		// Create the XSD validation context
		schema_valid_context = ::xmlSchemaNewValidCtxt( schema );
		if ( schema_valid_context == _null )
			return _false;

		// Perform the XSD validation
		result = ::xmlSchemaValidateDoc( schema_valid_context, mXmlDocument ) == 0;
	}

	// Free contexts
	{
		if ( schema_valid_context )
			::xmlSchemaFreeValidCtxt( schema_valid_context );

		if ( schema )
			::xmlSchemaFree( schema );
	}

	// Feedback the validation result
	return result;
}

#endif

_ubool XMLFile::ParseXMLDocument( const _chara* string, _dword size )
{
	EGE_ASSERT( string != _null );
	EGE_ASSERT( size != 0 );

	// Skip the UTF-8 header if needed
	SKIP_UTF_CODE( string, size );
	if ( size == 0 )
		return _false;

	// Skip all '\0' characters at the tail
	while ( string[ size - 1 ] == 0 )
	{
		size --;
		if ( size == 0 )
		{
			WLOG_ERROR( L"The XML document parse failed, due to all string is '\0' characters" );
			return _false;
		}
	}

	// Parse the XML file
#ifdef _USE_TINY_XML2_
	mXmlDocument = new tinyxml2::XMLDocument( );
	tinyxml2::XMLError err_id = mXmlDocument->Parse( string, size );
	if ( err_id != tinyxml2::XML_NO_ERROR )
	{
		ALOG_ERROR_3( "Parse XML document failed(err_id: %d, err_msg: '%s[%s]')", 
			(_dword)err_id, AStringPtr( mXmlDocument->GetErrorStr1( ) ).Str( ), AStringPtr( mXmlDocument->GetErrorStr2( ) ).Str( ) );

		return _false;
	}
#else
	//	mXmlDocument = ::xmlReadDoc( (const xmlChar*) string, _null, "utf8", XML_PARSE_RECOVER );
	//	mXmlDocument = ::xmlReadMemory( string, size, _null, "utf8", XML_PARSE_RECOVER );
	mXmlDocument = ::xmlParseMemory( string, (int)size );
	if ( mXmlDocument == _null )
	{
		ALOG_ERROR_1( "Parse XML document failed(size: %d)", size );
		return _false;
	}
#endif

	// Initialize XML document
	InitXMLDocument( );

	return _true;
}

_ubool XMLFile::Initialize( )
{
#ifdef _USE_TINY_XML2_
#else
	if ( ::xmlGcMemSetup( OnXMLFreeFunc, OnXMLMallocFunc, OnXMLMallocFunc, OnXMLReallocFunc, OnXMLStrdupFunc ) == -1 )
		return _false;

	::xmlInitParser( );

	// Keep to output the format XML file
	xmlKeepBlanksDefault( 0 );
	xmlIndentTreeOutput = 1;
#endif

	return _true;
}

_void XMLFile::Finalize( )
{
#ifdef _USE_TINY_XML2_
#else
	::xmlCleanupParser( );
#endif
}

_void XMLFile::InitXMLDocument( )
{
#ifdef _USE_TINY_XML2_
	if ( mXmlDocument == _null )
		mXmlDocument = new tinyxml2::XMLDocument( );

	// Get the root element of XML document
	if ( mRootElement == _null )
	{
		xmlNodePtr xml_element = mXmlDocument->FirstChildElement( );
		if ( xml_element == _null )
		{
			xml_element = mXmlDocument->NewElement( "" );
			EGE_ASSERT( xml_element != _null );

			mXmlDocument->InsertEndChild( xml_element );
		}

		mRootElement = new XMLElement( mXmlDocument, xml_element, _null, _null, _null );
	}
#else
	if ( mXmlDocument == _null )
	{
		mXmlDocument			= ::xmlNewDoc( (const xmlChar*) "1.0" );
		mXmlDocument->encoding	= ::xmlStrdup( (const xmlChar*) "utf-8" );
	}

	// Get the root element of XML document
	if ( mRootElement == _null )
	{
		xmlNodePtr xml_element = ::xmlDocGetRootElement( mXmlDocument );
		if ( xml_element == _null )
		{
			// XML has not any root element, now create a new one
			xml_element = ::xmlNewNode( _null, (const xmlChar*) "" );
			EGE_ASSERT( xml_element != _null );

			// Set the root element of XML document
			::xmlDocSetRootElement( mXmlDocument, xml_element );
		}

		mRootElement = new XMLElement( mXmlDocument, xml_element, _null, _null, _null, this );
	}
#endif

	// Create declaration
	if ( mDeclaration == _null )
		mDeclaration = new XMLFileDeclaration( mXmlDocument );
}

_FILE_FORMAT XMLFile::GetFileID( ) const
{
	return _FF_XML;
}

_ubool XMLFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Get the stream size in bytes
	_dword size = stream_reader->GetRemainBytes( );
	if ( size == 0 )
	{
		WLOG_ERROR( L"The XML buffer is empty" );
		return _false;
	}

	// Read XML file string info
	MemArrayPtr< _chara > string( size );
	_dword read_size = stream_reader->ReadBuffer( string, size );
	if ( read_size != size )
	{
		WLOG_ERROR_2( L"The XML buffer size is invalid (read_size:%d, size:%d)", read_size, size );
		return _false;
	}

	// Start to parse XML 
	if ( ParseXMLDocument( (const _chara*) string, size ) == _false )
	{
		WLOG_ERROR( L"The XML document parse failed" );
		return _false;
	}

	return _true;
}

_void XMLFile::Unload( )
{
	EGE_DELETE( mDeclaration );
	EGE_DELETE( mRootElement );

	if ( mXmlDocument != _null )
	{
#ifdef _USE_TINY_XML2_
		EGE_DELETE( mXmlDocument );
#else
		::xmlFreeDoc( mXmlDocument );
#endif
		mXmlDocument = _null;
	}
}

_ubool XMLFile::SaveToStream( IStreamWriter* stream_writer, _dword flags ) const
{
	if ( mXmlDocument == _null )
		return _false;

#ifdef _USE_TINY_XML2_
	tinyxml2::XMLPrinter tiny_printer;
	if ( mXmlDocument->Accept( &tiny_printer ) == _false )
		return _false;

	AString string = tiny_printer.CStr( );
	stream_writer->WriteBuffer( string.Str( ), string.SizeOfBytes( ) - 1 );

	return _true;
#else
	// Allocate the output buffer
	xmlOutputBufferPtr xml_output_buffer = ::xmlAllocOutputBuffer( _null );
	if ( xml_output_buffer == _null )
		return _false;

	// Initialize the output buffer
	xml_output_buffer->context			= stream_writer;
	xml_output_buffer->writecallback	= OnXMLOutputWriteFunc;
	xml_output_buffer->closecallback	= _null;

	// Save XML to output buffer ( The output buffer will be deleted in the save file function )
	_ubool ret = ::xmlSaveFormatFileTo( xml_output_buffer, mXmlDocument, _null, 1 ) != -1;

	// The output buffer has been released in 'xmlSaveFormatFileTo()' function, so we do not to close it
	// ::xmlOutputBufferClose( xml_output_buffer );

	return ret;
#endif
}

IMarkupDeclaration* XMLFile::GetDeclaration( )
{
	return mDeclaration;
}

IMarkupElement* XMLFile::GetRootElement( )
{
	return mRootElement;
}

_ubool XMLFile::SchemaValidate( WStringPtr filename )
{
#ifndef _USE_TINY_XML2_
	// Convert file name to ANSI
	_chara filename_ansi[1024];
	Platform::Utf16ToAnsi( filename_ansi, 1024, filename.Str( ) );

	// Create schema parser context
	xmlSchemaParserCtxtPtr parser_context = ::xmlSchemaNewParserCtxt( filename_ansi );
	if ( parser_context == _null )
		return _false;

	// Perform the XSD validation
	_ubool result = SchemaValidate( parser_context );

	// Free contexts
	if ( parser_context )
		::xmlSchemaFreeParserCtxt( parser_context );

	// Feedback the validation result
	return result;
#else
	return _false;
#endif
}

_ubool XMLFile::SchemaValidate( IStreamReader* stream_reader )
{
#ifndef _USE_TINY_XML2_
	// Read the XSD buffer
	MemArrayPtr< _chara > xsd_file_buffer( stream_reader->GetSize( ) );
	stream_reader->ReadBuffer( xsd_file_buffer, stream_reader->GetSize( ) );

	// Create schema parser context
	xmlSchemaParserCtxtPtr parser_context = ::xmlSchemaNewMemParserCtxt( (const _chara*) xsd_file_buffer, (int)stream_reader->GetSize( ) );
	if ( parser_context == _null )
		return _false;

	// Perform the XSD validation
	_ubool result = SchemaValidate( parser_context );

	// Free contexts
	if ( parser_context )
		::xmlSchemaFreeParserCtxt( parser_context );

	// Feedback the validation result
	return result;
#else
	return _false;
#endif
}