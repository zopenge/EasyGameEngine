//! @file     NetworkGlobals.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// The network enumerations
//----------------------------------------------------------------------------

//!	The network error ID
enum _NETWORK_ERROR_TYPE
{
	_NET_ERROR_NO,
	_NET_ERROR_UNSUPPORTED_PROTOCOL,
	_NET_ERROR_FAILED_INIT,
	_NET_ERROR_URL_MALFORMAT,
	_NET_ERROR_NOT_BUILT_IN,
	_NET_ERROR_COULDNT_RESOLVE_PROXY,
	_NET_ERROR_COULDNT_RESOLVE_HOST,
	_NET_ERROR_COULDNT_CONNECT,
	_NET_ERROR_FTP_WEIRD_SERVER_REPLY,
	_NET_ERROR_REMOTE_ACCESS_DENIED,	// A service was denied by the server due to lack of access - when login fails this is not returned. 
	_NET_ERROR_OBSOLETE10,
	_NET_ERROR_FTP_WEIRD_PASS_REPLY,
	_NET_ERROR_OBSOLETE12,
	_NET_ERROR_FTP_WEIRD_PASV_REPLY,
	_NET_ERROR_FTP_WEIRD_227_FORMAT,
	_NET_ERROR_FTP_CANT_GET_HOST,
	_NET_ERROR_OBSOLETE16,
	_NET_ERROR_FTP_COULDNT_SET_TYPE,
	_NET_ERROR_PARTIAL_FILE,
	_NET_ERROR_FTP_COULDNT_RETR_FILE,
	_NET_ERROR_OBSOLETE20,
	_NET_ERROR_QUOTE_ERROR,	// Quote command failure 
	_NET_ERROR_HTTP_RETURNED_ERROR,
	_NET_ERROR_WRITE_ERROR,
	_NET_ERROR_OBSOLETE24,
	_NET_ERROR_UPLOAD_FAILED,	// Failed upload "command" 
	_NET_ERROR_READ_ERROR,   // Couldn't open/read from file 
	_NET_ERROR_OUT_OF_MEMORY,
	_NET_ERROR_OPERATION_TIMEDOUT,   // The timeout time was reached 
	_NET_ERROR_OBSOLETE29,
	_NET_ERROR_FTP_PORT_FAILED, 	// FTP PORT operation failed 
	_NET_ERROR_FTP_COULDNT_USE_REST, 	// the REST command failed 
	_NET_ERROR_OBSOLETE32, 	
	_NET_ERROR_RANGE_ERROR, 	// RANGE "command" didn't work 
	_NET_ERROR_HTTP_POST_ERROR, 	
	_NET_ERROR_SSL_CONNECT_ERROR, 	// wrong when connecting with SSL 
	_NET_ERROR_BAD_DOWNLOAD_RESUME, 	// couldn't resume download 
	_NET_ERROR_FILE_COULDNT_READ_FILE, 
	_NET_ERROR_LDAP_CANNOT_BIND, 
	_NET_ERROR_LDAP_SEARCH_FAILED, 
	_NET_ERROR_OBSOLETE40,	
	_NET_ERROR_FUNCTION_NOT_FOUND, 
	_NET_ERROR_ABORTED_BY_CALLBACK, 
	_NET_ERROR_BAD_FUNCTION_ARGUMENT, 
	_NET_ERROR_OBSOLETE44,
	_NET_ERROR_INTERFACE_FAILED, 	// CURLOPT_INTERFACE failed 
	_NET_ERROR_OBSOLETE46,
	_NET_ERROR_TOO_MANY_REDIRECTS, 	// catch endless re//direct loops 
	_NET_ERROR_UNKNOWN_TELNET_OPTION, 	// User specified an unknown option 
	_NET_ERROR_TELNET_OPTION_SYNTAX, 	// Malformed telnet option 
	_NET_ERROR_OBSOLETE50,
	_NET_ERROR_PEER_FAILED_VERIFICATION, 	// peer's certificate or fingerprint wasn't verified fine 
	_NET_ERROR_GOT_NOTHING, 	// when this is a specified error 
	_NET_ERROR_SSL_ENGINE_NOTFOUND, 	// SSL crypto engine not found 
	_NET_ERROR_SSL_ENGINE_SETFAILED, 	// can not set SSL crypto engine as default 
	_NET_ERROR_SEND_ERROR, 	// failed sending network data 
	_NET_ERROR_RECV_ERROR, 	// failure in receiving network data 
	_NET_ERROR_OBSOLETE57,
	_NET_ERROR_SSL_CERTPROBLEM, 	// problem with the local certificate 
	_NET_ERROR_SSL_CIPHER, 	// couldn't use specified cipher 
	_NET_ERROR_SSL_CACERT, 	// problem with the CA cert (path?) 
	_NET_ERROR_BAD_CONTENT_ENCODING, 	// Unrecognized transfer encoding 
	_NET_ERROR_LDAP_INVALID_URL, 	// Invalid LDAP URL 
	_NET_ERROR_FILESIZE_EXCEEDED, 	// Maximum file size exceeded 
	_NET_ERROR_USE_SSL_FAILED, 	// Requested FTP SSL level failed 
	_NET_ERROR_SEND_FAIL_REWIND, 	// Sending the data requires a rewind that failed 
	_NET_ERROR_SSL_ENGINE_INITFAILED, 	// failed to initialise ENGINE 
	_NET_ERROR_LOGIN_DENIED, 	// user password or similar was not accepted and we failed to login 
	_NET_ERROR_TFTP_NOTFOUND, 	// file not found on server 
	_NET_ERROR_TFTP_PERM, 	// permission problem on server 
	_NET_ERROR_REMOTE_DISK_FULL, 	// out of disk space on server 
	_NET_ERROR_TFTP_ILLEGAL, 	// Illegal TFTP operation 
	_NET_ERROR_TFTP_UNKNOWNID, 	// Unknown transfer ID 
	_NET_ERROR_REMOTE_FILE_EXISTS, 	// File already exists 
	_NET_ERROR_TFTP_NOSUCHUSER, 	// No such user 
	_NET_ERROR_CONV_FAILED, 	// conversion failed 
	_NET_ERROR_CONV_REQD, 	
	_NET_ERROR_SSL_CACERT_BADFILE, 	// could not load CACERT file missing or wrong format 
	_NET_ERROR_REMOTE_FILE_NOT_FOUND, 	// remote file not found 
	_NET_ERROR_SSH, 	// error from the SSH layer somewhat generic so the error message will be of interest when this has happened 
	_NET_ERROR_SSL_SHUTDOWN_FAILED, 	// Failed to shut down the SSL connection 
	_NET_ERROR_AGAIN, 	// socket is not ready for send/recv wait till it's ready and try again
	_NET_ERROR_SSL_CRL_BADFILE, 	// could not load CRL file missing or wrong format
	_NET_ERROR_SSL_ISSUER_ERROR, 	// Issuer check failed
	_NET_ERROR_FTP_PRET_FAILED, 	// a PRET command failed 
	_NET_ERROR_RTSP_CSEQ_ERROR, 	// mismatch of RTSP CSeq numbers 
	_NET_ERROR_RTSP_SESSION_ERROR, 	// mismatch of RTSP Session Identifiers 
	_NET_ERROR_FTP_BAD_FILE_LIST, 	// unable to parse FTP file list 
	_NET_ERROR_CHUNK_FAILED, 	// chunk callback reported error 
};

//!	The network debug type
enum _NETWORK_DEBUG_TYPE
{
	_NET_DEBUG_UNKNOWN		= 0,
	_NET_DEBUG_TEXT			= 1,
	_NET_DEBUG_HEADER_IN	= 2,
	_NET_DEBUG_HEADER_OUT	= 3,
	_NET_DEBUG_DATA_IN		= 4,
	_NET_DEBUG_DATA_OUT		= 5,
	_NET_DEBUG_SSL_DATA_IN	= 6,
	_NET_DEBUG_SSL_DATA_OUT	= 7,
};

//!	The Network HTTP Return Codes
//! @see http://www.helpwithpcs.com/courses/html/html_http_status_codes.htm
enum _NETWORK_HTTP_RET_CODE
{
	//!	@defgroup SuccessCodes
	//!	@{

	//!	The request sent by the client was successful.
	_HTTP_RET_CODE_SUCCESS							= 200,
	//!	The request was successful and a new resource was created. 
	_HTTP_RET_CODE_CREATED							= 201,
	//!	The request has been accepted for processing, but has not yet been processed. 
	_HTTP_RET_CODE_ACCEPTED							= 202,
	//!	The returned meta information in the entity-header is not the definitive set as available from the origin server.
	_HTTP_RET_CODE_NON_AUTHORITATIVE_INFORMATION 	= 203,
	//!	The request was successful but does not require the return of an entity-body. 
	_HTTP_RET_CODE_NO_CONTENT 						= 204,
	//!	The request was successful but the User-Agent should reset the document view that caused the request.
	_HTTP_RET_CODE_RESET_CONTENT 					= 205,
	//!	The partial GET request has been successful. 
	_HTTP_RET_CODE_PARTIAL_CONTENT 					= 206,

	//!	@}

	//!	@defgroup ErrorCodes
	//!	@{

	//!	The syntax of the request was not understood by the server.
	_HTTP_RET_CODE_BAD_REQUEST						= 400,
	//!	The request needs user authentication 
	_HTTP_RET_CODE_NOT_AUTHORISED 					= 401,
	//!	Reserved for future use. 
	_HTTP_RET_CODE_PAYMENT_REQUIRED					= 402,
	//!	The server has refused to fulfill the request. 
	_HTTP_RET_CODE_FORBIDDEN						= 403,
	//!	The document/file requested by the client was not found. 
	_HTTP_RET_CODE_NOT_FOUND						= 404,

	//!	The request was unsuccessful due to an unexpected condition encountered by the server. 
	_HTTP_RET_CODE_INTERNAL_SERVER_ERROR			= 500,
	//!	The request was unsuccessful because the server can not support the functionality needed to fulfill the request.
	_HTTP_RET_CODE_NOT_IMPLEMENTED					= 501,

	//!	@}
};

//!	The Network FTP Return Codes
//! @see http://www.theegglestongroup.com/writing/ftp_error_codes.php
enum _NETWORK_FTP_RET_CODE
{
	//!	@defgroup	100 Codes
	//!	@remark		The requested action is being taken. Expect a reply before proceeding with a new command.
	//!	@{

	_FTP_RET_CODE_RESTART_MARKER_REPLY	= 110, //!	Restart marker reply.
	_FTP_RET_CODE_SERVER_READY			= 120, //!	Service ready in (n) minutes.
	_FTP_RET_CODE_ALREADY_OPEN			= 125, //!	Data connection already open, transfer starting.
	_FTP_RET_CODE_FILE_STATUS_OK		= 150, //!	File status okay, about to open data connection.

	//!	@}

	//!	@defgroup	200 Codes
	//!	@remark		The requested action has been successfully completed.
	//!	@{

	_FTP_RET_CODE_COMMAND_OK					= 200, //!	Command okay.
	_FTP_RET_CODE_COMMAND_NOT_IMPLEMENTED_1		= 202, //!	Command not implemented
	_FTP_RET_CODE_SYSTEM_HELP_REPLY				= 211, //!	System status, or system help reply.
	_FTP_RET_CODE_DIRECTORY_STATUS				= 212, //!	Directory status.
	_FTP_RET_CODE_FILE_STATUS					= 213, //!	File status.
	_FTP_RET_CODE_HELP_MESSAGE					= 214, //!	Help message.
	_FTP_RET_CODE_NAME_SYSTEM_TYPE				= 215, //!	NAME system type. (NAME is an official system name from the list in the Assigned Numbers document.)
	_FTP_RET_CODE_SERVER_READY_FOR_NEW_USER		= 220, //!	Service ready for new user.
	_FTP_RET_CODE_SERVICE_CLOSING_CONNECTION	= 221, //!	Service closing control connection. (Logged out if appropriate.)
	_FTP_RET_CODE_OPEN_DATA_CONNECTION			= 225, //!	Data connection open, no transfer in progress.
	_FTP_RET_CODE_CLOSING_DATA_CONNECTION		= 226, //!	Closing data connection. Requested file action successful (file transfer, abort, etc.).
	_FTP_RET_CODE_ENTERING_PASSIVE_MODE			= 227, //!	Entering Passive Mode
	_FTP_RET_CODE_USER_LOGGED_IN				= 230, //!	User logged in, proceed.
	_FTP_RET_CODE_REQUEST_FILE_ACTION_OK		= 250, //!	Requested file action okay, completed.
	_FTP_RET_CODE_PATHNAME_CREATED				= 257, //!	"PATHNAME" created.

	//!	@}

	//!	@defgroup	300 Codes
	//!	@remark		The command has been accepted, but the requested action is being held pending receipt of further information.
	//!	@{

	_FTP_RET_CODE_USER_NAME_OK					= 331, //!	User name okay, need password.
	_FTP_RET_CODE_NEED_ACCOUNT_FOR_LOGIN		= 332, //!	Need account for login.
	_FTP_RET_CODE_REQUESTED_FILE_ACTION_PENDING	= 350, //!	Requested file action pending further information.

	//!	@}

	//!	@defgroup	400 Codes
	//!	@remark		The command was not accepted and the requested action did not take place. \n
	//!				The error condition is temporary, however, and the action may be requested again.
	//!	@{
	
	_FTP_RET_CODE_SERVICE_NOT_AVAILABLE			= 421, //!	Service not available, closing control connection. (May be a reply to any command if the service knows it must shut down.)`
	_FTP_RET_CODE_CAN_NOT_OPEN_DATA_CONNECTION	= 425, //!	Can't open data connection.
	_FTP_RET_CODE_TRANSFER_ABORTED				= 426, //!	Connection closed, transfer aborted.
	_FTP_RET_CODE_FILE_UNAVAILABLE_DUE_TO_BUSY	= 450, //!	Requested file action not taken. File unavailable (e.g., file busy).
	_FTP_RET_CODE_LOCAL_ERROR					= 451, //!	Requested action aborted, local error in processing.
	_FTP_RET_CODE_INSUFFICIENT_STORAGE_SPACE	= 452, //!	Requested action not taken. Insufficient storage space in system.

	//!	@}

	//!	@defgroup	500 Codes
	//!	@remark		The command was not accepted and the requested action did not take place.
	//!	@{

	_FTP_RET_CODE_SYNTAX_ERROR						= 500, //!	Syntax error, command unrecognized. This may include errors such as command line too long.
	_FTP_RET_CODE_SYNTAX_ERROR_IN_ARGUMENTS			= 501, //!	Syntax error in parameters or arguments.
	_FTP_RET_CODE_COMMAND_NOT_IMPLEMENTED_2			= 502, //!	Command not implemented.
	_FTP_RET_CODE_BAT_SEQUENCE						= 503, //!	Bad sequence of commands.
	_FTP_RET_CODE_COMMAND_NOT_IMPLEMENTED_3			= 504, //!	Command not implemented for that parameter.
	_FTP_RET_CODE_USER_NOT_LOGGED_IN				= 530, //!	User not logged in.
	_FTP_RET_CODE_NEED_ACCOUNT_FOR_STORING_FILES	= 532, //!	Need account for storing files.
	_FTP_RET_CODE_FILE_UNAVAILABLE_DUE_TO_NO_ACCESS	= 550, //!	Requested action not taken. File unavailable (e.g., file not found, no access).
	_FTP_RET_CODE_STORAGE_ALLOCATION_EXCEEDED		= 552, //!	Requested file action aborted, storage allocation exceeded
	_FTP_RET_CODE_ILLEGAL_FILE_NAME					= 553, //!	Requested action not taken. Illegal file name.

	//!	@}
};

//!	The Network MIME Key Type
enum _NETWORK_MIME_KEY_TYPE
{
	_MIME_KEY_TYPE_UNKNOWN,

	//!	Content
	_MIME_KEY_TYPE_CONTENT_TYPE,
	_MIME_KEY_TYPE_CONTENT_LENGTH,
	_MIME_KEY_TYPE_CONTENT_MD5CODE,

	//!	The max number of MIME types
	_MIME_KEY_TYPE_MAXNUMBER,
};

//!	The Network MIME Content Type
enum _NETWORK_MIME_CONTENT_TYPE
{
	_MIME_CONTENT_TYPE_UNKNOWN, // Unknown

	// Text
	_MIME_CONTENT_TYPE_TEXT_BEGIN,
		_MIME_CONTENT_TYPE_TEXT_UNKNOWN,	// Unknown Text
		_MIME_CONTENT_TYPE_TEXT_PLAIN,		// Plain
		_MIME_CONTENT_TYPE_TEXT_HTML,		// HTML
		_MIME_CONTENT_TYPE_TEXT_XML,		// XML
	_MIME_CONTENT_TYPE_TEXT_END,

	// Image
	_MIME_CONTENT_TYPE_IMAGE_BEGIN,
		_MIME_CONTENT_TYPE_IMAGE_UNKNOWN,	// Unknown Image
		_MIME_CONTENT_TYPE_IMAGE_PNG,		// PNG
		_MIME_CONTENT_TYPE_IMAGE_TGA,		// TGA
		_MIME_CONTENT_TYPE_IMAGE_JPG,		// JPG
	_MIME_CONTENT_TYPE_IMAGE_END,

	// Application
	_MIME_CONTENT_TYPE_APPLICATION_BEGIN,
		_MIME_CONTENT_TYPE_APPLICATION_UNKNOWN,			// Unknown Application
		_MIME_CONTENT_TYPE_APPLICATION_OCTET_STREAM,	// Octet-Stream
	_MIME_CONTENT_TYPE_APPLICATION_END,
};

//!	The network connection type
enum _NETWORK_CONNECTION_TYPE
{
	_NETWORK_CONNECTION_UNKNOWN,
	_NETWORK_CONNECTION_TCP,
	_NETWORK_CONNECTION_UDP,
	_NETWORK_CONNECTION_HTTP,
	_NETWORK_CONNECTION_FTP,
	_NETWORK_CONNECTION_NAMED_PIPE,
	_NETWORK_CONNECTION_BLUETOOTH,
};

//!	The network operation type
enum _NETWORK_OPERATION_TYPE
{
	_NETWORK_OPERATION_UNKNOWN,
	_NETWORK_OPERATION_CONNECT,
	_NETWORK_OPERATION_RECV,
	_NETWORK_OPERATION_SEND,
};

//!	The network options ( it can be changed any time )
enum _NETWORK_OPTIONS
{
	//!	Indicates auto pause all network when application pause
	_NETWORK_OPTION_PAUSE_ALL_WHEN_APP_PAUSE	= 1 << 0,
	//!	Indicates enable simulating lag
	_NETWORK_OPTION_ENABLE_SIMULATING_LAG		= 1 << 1,
};

//----------------------------------------------------------------------------
// The network structures
//----------------------------------------------------------------------------

//!	The network error description
struct NetworkErrorDesc
{
	//!	The error ID
	_NETWORK_ERROR_TYPE	mErrID;
	//!	The error description
	AStringPtr			mErrDesc;

	NetworkErrorDesc( )
	{
		mErrID	= _NET_ERROR_NO;
	}
};

//----------------------------------------------------------------------------
// The network functions
//----------------------------------------------------------------------------

//!	Check whether it's MIME text type.
inline _ubool IsMIMETextType( _NETWORK_MIME_CONTENT_TYPE type ) { return type > _MIME_CONTENT_TYPE_TEXT_BEGIN && type < _MIME_CONTENT_TYPE_TEXT_END; }
//!	Check whether it's MIME application type.
inline _ubool IsMIMEApplicationType( _NETWORK_MIME_CONTENT_TYPE type ) { return type > _MIME_CONTENT_TYPE_APPLICATION_BEGIN && type < _MIME_CONTENT_TYPE_APPLICATION_END; }

//!	Check whether it's error HTTP code.
inline _ubool IsErrorHTTPCode( _dword code ) { return !(code >= _HTTP_RET_CODE_SUCCESS && code <= _HTTP_RET_CODE_PARTIAL_CONTENT); }
//!	Check whether it's file closed FTP code.
inline _ubool IsFileClosedFTPCode( _dword code ) { return code == _FTP_RET_CODE_CLOSING_DATA_CONNECTION || code == _FTP_RET_CODE_REQUEST_FILE_ACTION_OK; }
//!	Check whether it's error FTP code.
inline _ubool IsErrorFTPCode( _dword code ) 
{
	switch ( code )
	{
		case _FTP_RET_CODE_LOCAL_ERROR:
		case _FTP_RET_CODE_SYNTAX_ERROR:
		case _FTP_RET_CODE_SYNTAX_ERROR_IN_ARGUMENTS:
			return _true;

		default:
			break;
	}

	return _false;
}

}