//! @file     HTMLFile.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

#ifndef _EGE_DISABLE_HTML_FILE_

// The HTML parse options
const GumboOptions HTMLFile::sGumboDefaultOptions = 
{
	HTMLFile::OnGumboAlloc, 
	HTMLFile::OnGumboFree, 
	_null,
	8, 
	_false, 
	-1, 
	GUMBO_TAG_LAST, 
	GUMBO_NAMESPACE_HTML
};

//----------------------------------------------------------------------------
// HTMLAttribute Implementation
//----------------------------------------------------------------------------

HTMLAttribute::HTMLAttribute( GumboAttribute* gumbo_attribute )
{
	mGumboAttribute = gumbo_attribute;
}

HTMLAttribute::~HTMLAttribute( )
{
}

WStringR HTMLAttribute::GetName( _ubool with_prefix ) const
{
	return WString( L"" );
}

_ubool HTMLAttribute::OnSetContentU( UStringPtr content )
{
	return _true;
}

_ubool HTMLAttribute::OnSetContentW( WStringPtr content )
{
	return OnSetContentU( UString( ).FromString( content ) );
}

UStringPtr HTMLAttribute::OnGetContentU( ) const
{
	return "";
}

_ubool HTMLAttribute::OnGetValue( _ubool& value ) const
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

_ubool HTMLAttribute::OnGetValue( _int& value ) const
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

_ubool HTMLAttribute::OnGetValue( _dword& value ) const
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

_ubool HTMLAttribute::OnGetValue( _double& value ) const
{
	value = OnGetContentU( ).ToDouble( );

	return _true;
}

//----------------------------------------------------------------------------
// HTMLElement Implementation
//----------------------------------------------------------------------------

HTMLElement::HTMLElement( GumboElement* gumbo_element, HTMLElement* parent, HTMLElement* prev, HTMLElement* next )
	: BaseClass( parent, prev, next ), mGumboElement( gumbo_element )
{
}

HTMLElement::~HTMLElement( )
{
}

IMarkupLangElementIteratorPassRef HTMLElement::OnCreateElementIterator( IMarkupLangElement* element )
{
    return _null;
}

_ubool HTMLElement::SetName( WStringPtr name )
{
	return _true;
}

WStringR HTMLElement::GetName( ) const
{
	return WString( L"" );
}

IMarkupLangElement* HTMLElement::InsertChildElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj )
{
	return _null;
}

IMarkupLangElement* HTMLElement::InsertNextElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj )
{
	return _null;
}

_void HTMLElement::RemoveElement( IMarkupLangElement* element )
{
}

IMarkupLangElementIteratorPassRef HTMLElement::RemoveElement( IMarkupLangElementIterator* it )
{
	return _null;
}

_ubool HTMLElement::HasAttribute( WStringPtr name, _ubool ignorecase ) const
{
	return _false;
}

IMarkupLangAttribute* HTMLElement::SearchAttribute( WStringPtr name, _ubool ignorecase ) const
{
	return _null;
}

_dword HTMLElement::GetValueU( ) const
{
	UString text = GetTextU( );

	return text.ToDword( 10 );
}

_int HTMLElement::GetValueI( ) const
{
	UString text = GetTextU( );

	return text.ToLong( 10 );
}

_float HTMLElement::GetValueF( ) const
{
	UString text = GetTextU( );

	return text.ToFloat( );
}

_double HTMLElement::GetValueD( ) const
{
	UString text = GetTextU( );

	return text.ToDouble( );
}

_ubool HTMLElement::GetText( UString& text ) const 
{
	return _true;
}

_ubool HTMLElement::GetText( WString& text ) const 
{
	return _true;
}

UStringR HTMLElement::GetTextU( ) const
{
	UString text;
	if ( GetText( text ) == _false )
		return UString( "" );

	return text;
}

WStringR HTMLElement::GetTextW( ) const
{
	WString text;
	if ( GetText( text ) == _false )
		return WString( L"" );

	return text;
}

_ubool HTMLElement::SetText( UStringPtr text )
{
	return _true;
}

_ubool HTMLElement::SetText( WStringPtr text )
{
	return _true;
}

_ubool HTMLElement::SetAttributeString( WStringPtr name, UStringPtr string )
{
	return _true;
}

_ubool HTMLElement::SetAttributeString( WStringPtr name, WStringPtr string )
{
	// Get the name in UTF-8 mode
	UString string_utf8;
	string_utf8.FromString( _ENCODING_UTF16, string.Str( ) );

	return SetAttributeString( name, string_utf8 );
}

WStringR HTMLElement::DumpToString( ) const
{
	return L"";
}

WStringR HTMLElement::DumpToSchemaString( ) const
{
	return WString( L"" );
}

//----------------------------------------------------------------------------
// HTMLFile Implementation
//----------------------------------------------------------------------------

HTMLFile::HTMLFile( )
{
	mGumboOutput = _null;
}

HTMLFile::~HTMLFile( )
{
	Unload( );
}

_void* HTMLFile::OnGumboAlloc( _void* userdata, size_t size )
{
	return Memory::GetInstance( ).Alloc( size, _FILENAME_A, _LINENUMBER );
}

_void HTMLFile::OnGumboFree( _void* userdata, _void* ptr )
{
	Memory::GetInstance( ).Free( ptr, _FILENAME_A, _LINENUMBER );
}

_FILE_FORMAT HTMLFile::GetFileID( ) const
{
	return _FF_HTML;
}

_ubool HTMLFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Get the stream size in bytes
	_dword size = stream_reader->GetRemainBytes( );
	if ( size == 0 )
	{
		WLOG_ERROR( L"The HTML buffer is empty" );
		return _false;
	}

	// Read HTML file string info
	MemArrayPtr< _chara > string( size );
	_dword read_size = stream_reader->ReadBuffer( string, size );
	if ( read_size != size )
	{
		WLOG_ERROR_2( L"The HTML buffer size is invalid (read_size:%d, size:%d)", read_size, size );
		return _false;
	}

	// Parse HTML file
	mGumboOutput = gumbo_parse_with_options( &sGumboDefaultOptions, string.GetPointer( ), size );
	if ( mGumboOutput == _null )
		return _false;

	return _true;
}

_void HTMLFile::Unload( )
{
	if ( mGumboOutput != _null )
	{
		gumbo_destroy_output( &sGumboDefaultOptions, mGumboOutput );
		mGumboOutput = _null;
	}
}

_ubool HTMLFile::SaveToStream( IStreamWriter* stream_writer, _dword flags ) const
{
	return _false;
}

IMarkupLangDeclaration* HTMLFile::GetDeclaration( )
{
	return _null;
}

IMarkupLangElement* HTMLFile::GetRootElement( )
{
	return _null;
}

_ubool HTMLFile::SchemaValidate( WStringPtr filename )
{
	return _false;
}

_ubool HTMLFile::SchemaValidate( IStreamReader* stream_reader )
{
	return _false;
}

#endif