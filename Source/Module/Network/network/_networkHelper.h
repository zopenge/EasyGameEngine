//! @file     _networkHelper.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _networkHelper
//----------------------------------------------------------------------------

class _networkHelper
{
public:
	//!	Build URL address without protocols.
	static AString GetURLAddressWithoutProtocols( AStringPtr url_address );
	static WString GetURLAddressWithoutProtocols( WStringPtr url_address );

	//!	Build URL address.
	static AString BuildURLAddress( _ubool enable_ssl, const Address& remote_address, AStringPtr root_url, AStringPtr url_name );
	//!	Build FTP URL address.
	static AString BuildFTPURLAddress( const Address& remote_address, AStringPtr root_url, AStringPtr url_name );
};

}