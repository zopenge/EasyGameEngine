//! @file     _networkHelper.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// _networkHelper Implementation
//----------------------------------------------------------------------------

AString _networkHelper::GetURLAddressWithoutProtocols( AStringPtr url_address )
{
	_dword index = url_address.SearchL2R( "://" );
	if ( index != -1 )
		url_address = url_address.SubString( index + 3 );

	return url_address;
}

WString _networkHelper::GetURLAddressWithoutProtocols( WStringPtr url_address )
{
	_dword index = url_address.SearchL2R( L"://" );
	if ( index != -1 )
		url_address = url_address.SubString( index + 3 );

	return url_address;
}

AString _networkHelper::BuildURLAddress( _ubool enable_ssl, const Address& remote_address, AStringPtr root_url, AStringPtr url_name )
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

AString _networkHelper::BuildFTPURLAddress( const Address& remote_address, AStringPtr root_url, AStringPtr url_name )
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