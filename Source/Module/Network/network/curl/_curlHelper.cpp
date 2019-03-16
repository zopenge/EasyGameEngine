//! @file     _curlHelper.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGENetwork.h"

#if (_USE_CRUL_SDK == 1)

//----------------------------------------------------------------------------
// _curlHelper Implementation
//----------------------------------------------------------------------------

_NETWORK_DEBUG_TYPE _curlHelper::TranslateDebugType( curl_infotype type )
{
	switch ( type )
	{
		case CURLINFO_TEXT:			return _NET_DEBUG_TEXT;
		case CURLINFO_HEADER_IN:	return _NET_DEBUG_HEADER_IN;
		case CURLINFO_HEADER_OUT:	return _NET_DEBUG_HEADER_OUT;
		case CURLINFO_DATA_IN:		return _NET_DEBUG_DATA_IN;
		case CURLINFO_DATA_OUT:		return _NET_DEBUG_DATA_OUT;
		case CURLINFO_SSL_DATA_IN:	return _NET_DEBUG_SSL_DATA_IN;
		case CURLINFO_SSL_DATA_OUT:	return _NET_DEBUG_SSL_DATA_OUT;
		default:
			return _NET_DEBUG_UNKNOWN;
	}
}

_NETWORK_ERROR_TYPE _curlHelper::TranslateErrorType( CURLcode type )
{
#define CASE_ERROR_ID( x ) case CURLE_##x: return _NET_ERROR_##x;
	switch ( type )
	{
		CASE_ERROR_ID( UNSUPPORTED_PROTOCOL )		
		CASE_ERROR_ID( FAILED_INIT )				
		CASE_ERROR_ID( URL_MALFORMAT )			
		CASE_ERROR_ID( NOT_BUILT_IN )				
		CASE_ERROR_ID( COULDNT_RESOLVE_PROXY )	
		CASE_ERROR_ID( COULDNT_RESOLVE_HOST )		
		CASE_ERROR_ID( COULDNT_CONNECT )			
		CASE_ERROR_ID( FTP_WEIRD_SERVER_REPLY )	
		CASE_ERROR_ID( REMOTE_ACCESS_DENIED )		
		CASE_ERROR_ID( OBSOLETE10 )				
		CASE_ERROR_ID( FTP_WEIRD_PASS_REPLY )		
		CASE_ERROR_ID( OBSOLETE12 )				
		CASE_ERROR_ID( FTP_WEIRD_PASV_REPLY )		
		CASE_ERROR_ID( FTP_WEIRD_227_FORMAT )		
		CASE_ERROR_ID( FTP_CANT_GET_HOST )		
		CASE_ERROR_ID( OBSOLETE16 )				
		CASE_ERROR_ID( FTP_COULDNT_SET_TYPE )		
		CASE_ERROR_ID( PARTIAL_FILE )				
		CASE_ERROR_ID( FTP_COULDNT_RETR_FILE )	
		CASE_ERROR_ID( OBSOLETE20 )				
		CASE_ERROR_ID( QUOTE_ERROR )				
		CASE_ERROR_ID( HTTP_RETURNED_ERROR )		
		CASE_ERROR_ID( WRITE_ERROR )				
		CASE_ERROR_ID( OBSOLETE24 )				
		CASE_ERROR_ID( UPLOAD_FAILED )			
		CASE_ERROR_ID( READ_ERROR )				
		CASE_ERROR_ID( OUT_OF_MEMORY )			
		CASE_ERROR_ID( OPERATION_TIMEDOUT )		
		CASE_ERROR_ID( OBSOLETE29 )				
		CASE_ERROR_ID( FTP_PORT_FAILED )         	
		CASE_ERROR_ID( FTP_COULDNT_USE_REST )    	
		CASE_ERROR_ID( OBSOLETE32 )              	
		CASE_ERROR_ID( RANGE_ERROR )             	
		CASE_ERROR_ID( HTTP_POST_ERROR )         	
		CASE_ERROR_ID( SSL_CONNECT_ERROR )       	
		CASE_ERROR_ID( BAD_DOWNLOAD_RESUME )     	
		CASE_ERROR_ID( FILE_COULDNT_READ_FILE )  	
		CASE_ERROR_ID( LDAP_CANNOT_BIND )        	
		CASE_ERROR_ID( LDAP_SEARCH_FAILED )      	
		CASE_ERROR_ID( OBSOLETE40 )              	
		CASE_ERROR_ID( FUNCTION_NOT_FOUND )      	
		CASE_ERROR_ID( ABORTED_BY_CALLBACK )     	
		CASE_ERROR_ID( BAD_FUNCTION_ARGUMENT )   	
		CASE_ERROR_ID( OBSOLETE44 )              	
		CASE_ERROR_ID( INTERFACE_FAILED )        	
		CASE_ERROR_ID( OBSOLETE46 )              	
		CASE_ERROR_ID( TOO_MANY_REDIRECTS )      	
		CASE_ERROR_ID( UNKNOWN_TELNET_OPTION )   	
		CASE_ERROR_ID( TELNET_OPTION_SYNTAX )    	
		CASE_ERROR_ID( OBSOLETE50 )              	
		CASE_ERROR_ID( PEER_FAILED_VERIFICATION ) 
		CASE_ERROR_ID( GOT_NOTHING )             	
		CASE_ERROR_ID( SSL_ENGINE_NOTFOUND )     	
		CASE_ERROR_ID( SSL_ENGINE_SETFAILED )    	
		CASE_ERROR_ID( SEND_ERROR )              	
		CASE_ERROR_ID( RECV_ERROR )              	
		CASE_ERROR_ID( OBSOLETE57 )              	
		CASE_ERROR_ID( SSL_CERTPROBLEM )         	
		CASE_ERROR_ID( SSL_CIPHER )              	
		CASE_ERROR_ID( SSL_CACERT )              	
		CASE_ERROR_ID( BAD_CONTENT_ENCODING )    	
		CASE_ERROR_ID( LDAP_INVALID_URL )        	
		CASE_ERROR_ID( FILESIZE_EXCEEDED )       	
		CASE_ERROR_ID( USE_SSL_FAILED )          	
		CASE_ERROR_ID( SEND_FAIL_REWIND )        	
		CASE_ERROR_ID( SSL_ENGINE_INITFAILED )   	
		CASE_ERROR_ID( LOGIN_DENIED )            	
		CASE_ERROR_ID( TFTP_NOTFOUND )           	
		CASE_ERROR_ID( TFTP_PERM )               	
		CASE_ERROR_ID( REMOTE_DISK_FULL )        	
		CASE_ERROR_ID( TFTP_ILLEGAL )            	
		CASE_ERROR_ID( TFTP_UNKNOWNID )          	
		CASE_ERROR_ID( REMOTE_FILE_EXISTS )      	
		CASE_ERROR_ID( TFTP_NOSUCHUSER )         	
		CASE_ERROR_ID( CONV_FAILED )             	
		CASE_ERROR_ID( CONV_REQD )               	
		CASE_ERROR_ID( SSL_CACERT_BADFILE )      	
		CASE_ERROR_ID( REMOTE_FILE_NOT_FOUND )   	
		CASE_ERROR_ID( SSH )                     	
		CASE_ERROR_ID( SSL_SHUTDOWN_FAILED )     	
		CASE_ERROR_ID( AGAIN )                   	
		CASE_ERROR_ID( SSL_CRL_BADFILE )         	
		CASE_ERROR_ID( SSL_ISSUER_ERROR )        	
		CASE_ERROR_ID( FTP_PRET_FAILED )         	
		CASE_ERROR_ID( RTSP_CSEQ_ERROR )         	
		CASE_ERROR_ID( RTSP_SESSION_ERROR )      	
		CASE_ERROR_ID( FTP_BAD_FILE_LIST )       	
		CASE_ERROR_ID( CHUNK_FAILED )
		default:
			return _NET_ERROR_NO;
	}
}

AString _curlHelper::GetURLAddressWithoutProtocols( AStringPtr url_address )
{
	_dword index = url_address.SearchL2R( "://" );
	if ( index != -1 )
		url_address = url_address.SubString( index + 3 );

	return url_address;
}

WString _curlHelper::GetURLAddressWithoutProtocols( WStringPtr url_address )
{
	_dword index = url_address.SearchL2R( L"://" );
	if ( index != -1 )
		url_address = url_address.SubString( index + 3 );

	return url_address;
}

AString _curlHelper::BuildURLAddress( _ubool enable_ssl, const Address& remote_address, AStringPtr root_url, AStringPtr url_name )
{
	AString url_address;

	if ( enable_ssl )
		url_address += "https://";

	// Add root URL
	if ( root_url.IsEmpty( ) )
		url_address += remote_address.ToStringA( _false );
	else
		url_address += root_url;

	// Add sub URL
	if ( url_name.IsEmpty( ) == _false )
		url_address += "/" + url_name;

	return url_address;
}

AString _curlHelper::BuildFTPURLAddress( const Address& remote_address, AStringPtr root_url, AStringPtr url_name )
{
	AString url_address;

	// Add FTP protocol header
	url_address += "ftp://";

	// Add root URL
	if ( root_url.IsEmpty( ) )
		url_address += remote_address.ToStringA( _true );
	else
		url_address += root_url;

	// Add sub URL
	if ( url_name.IsEmpty( ) == _false )
		url_address += "/" + url_name;

	return url_address;
}

#endif