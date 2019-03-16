//! @file     NetworkProtocol.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// The MIME type string table
//----------------------------------------------------------------------------

static const _chara* sMIMETypeTable[ _MIME_KEY_TYPE_MAXNUMBER ] = 
{
	"UNKNOWN",

	// Content
	"Content-Type: ",
	"Content-Length: ",
	"Content-MD5: ",
};

//----------------------------------------------------------------------------
// NetworkProtocol Implementation
//----------------------------------------------------------------------------

_ubool NetworkProtocol::ParseMIME( AStringPtr string, _NETWORK_MIME_KEY_TYPE& key, AString& value )
{
	for ( _dword i = 1; i < _MIME_KEY_TYPE_MAXNUMBER; i ++ )
	{
		// Try to match the keyword string
		if ( string.StartsWith( sMIMETypeTable[i] ) == _false )
			continue;

		// Feedback the key
		key = (_NETWORK_MIME_KEY_TYPE) i;

		// Jump the keyword string to get the content string
		value = string.SubString( Platform::StringLength( sMIMETypeTable[i] ) );
		value.TrimRight( " \t\r\n" );

		return _true;
	}

	// Unknown MIME key
	key = _MIME_KEY_TYPE_UNKNOWN;

	return _false;
}

_NETWORK_MIME_CONTENT_TYPE NetworkProtocol::ParseMIMEContentType( AStringPtr string )
{
	// It's text content
	if ( string.StartsWith( "text/" ) )
	{
		if ( string.EndsWith( "/plain" ) )
			return _MIME_CONTENT_TYPE_TEXT_PLAIN;
		if ( string.EndsWith( "/html" ) )
			return _MIME_CONTENT_TYPE_TEXT_HTML;
		if ( string.EndsWith( "/xml" ) )
			return _MIME_CONTENT_TYPE_TEXT_XML;

		return _MIME_CONTENT_TYPE_TEXT_UNKNOWN;
	}
	// It's image content
	else if ( string.StartsWith( "image/" ) )
	{
		if ( string.EndsWith( "/png" ) )
			return _MIME_CONTENT_TYPE_IMAGE_PNG;
		if ( string.EndsWith( "/tga" ) )
			return _MIME_CONTENT_TYPE_IMAGE_TGA;
		if ( string.EndsWith( "/jpg" ) )
			return _MIME_CONTENT_TYPE_IMAGE_JPG;

		return _MIME_CONTENT_TYPE_IMAGE_UNKNOWN;
	}
	// It's application content
	else if ( string.StartsWith( "application/" ) )
	{
		if ( string.EndsWith( "/octet-stream" ) )
			return _MIME_CONTENT_TYPE_APPLICATION_OCTET_STREAM;

		return _MIME_CONTENT_TYPE_APPLICATION_UNKNOWN;
	}

	return _MIME_CONTENT_TYPE_UNKNOWN;
}

_ubool NetworkProtocol::ParseFTP( AStringPtr protocol_string, _NETWORK_FTP_CODE& code, AString& string )
{
	_dword ftp_code = 0;
	if ( StringFormatter::ParseString( protocol_string.Str( ), "%d %s", ftp_code, string ) != 2 )
		return _false;

	code = (_NETWORK_FTP_CODE) ftp_code;
	string.TrimBoth( " \t\r\n" );

	return _true;
}