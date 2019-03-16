//! @file     NetworkProtocol.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkProtocol
//----------------------------------------------------------------------------

class NetworkProtocol
{
public:
	//!	Parse the MIME string in ANSI.
	//!	@param		string	The protocol string.
	//!	@param		key		The MIME key.
	//!	@param		value	The MIME value.
	//!	@return		True indicates successful, otherwise indicates failure.
	static _ubool ParseMIME( AStringPtr string, _NETWORK_MIME_KEY_TYPE& key, AString& value );
	//!	Parse the MIME content type.
	//!	@param		string	The content type string.
	//!	@return		The MIME content type.
	static _NETWORK_MIME_CONTENT_TYPE ParseMIMEContentType( AStringPtr string );

	//!	Parse the FTP string in ANSI.
	//!	@param		protocol_string	The protocol string.
	//!	@param		code			The FTP code.
	//!	@param		string			The FTP string.
	//!	@return		True indicates successful, otherwise indicates failure.
	static _ubool ParseFTP( AStringPtr protocol_string, _NETWORK_FTP_CODE& code, AString& string );
};	  

//----------------------------------------------------------------------------
// NetworkProtocol Implementation
//----------------------------------------------------------------------------

}