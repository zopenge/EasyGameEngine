//! @file     Address.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

Address	Address::cNullAddress;

//----------------------------------------------------------------------------
// Address Implementation
//----------------------------------------------------------------------------

Address& Address::FromString( WStringPtr address )
{
	WString address_temp = address;

	// Set the port
	_dword port_index = address_temp.SearchL2R( ':' );
	if ( port_index != -1 )
	{
		// The address with port info ( Jump ':' character )
		mPort = (_word) Platform::ConvertStringToDword( address.SubString( port_index ).SubString( 1 ).Str( ), 10 ); 

		// Remove port string
		address_temp.Remove( port_index );
	}

	// Get the local IP
	if ( address_temp == L"localhost" )
	{
		mIP1 = 127;
		mIP2 = 0;
		mIP3 = 0;
		mIP4 = 1;
	}
	else
	{
		// Analyze the IP address
		Array< WString > ip_address_string;
		StringFormatter::SplitString( address_temp, ip_address_string, L".", L" \t" );
	
		// Set the IP address
		if ( ip_address_string.Number( ) == 4 )
		{
			mIP1 = (_byte) ip_address_string[0].ToDword( 10 );
			mIP2 = (_byte) ip_address_string[1].ToDword( 10 );
			mIP3 = (_byte) ip_address_string[2].ToDword( 10 );
			mIP4 = (_byte) ip_address_string[3].ToDword( 10 );
		}
	}

	return *this;
}

AString Address::ToStringA( _ubool with_port ) const
{
	_chara string_buffer[1024];

	if ( with_port )
		Platform::FormatStringBuffer( string_buffer, 1024, "%d.%d.%d.%d:%d", mIP1, mIP2, mIP3, mIP4, mPort ); 
	else
		Platform::FormatStringBuffer( string_buffer, 1024, "%d.%d.%d.%d", mIP1, mIP2, mIP3, mIP4 ); 

	return AString( string_buffer );
}

WString Address::ToStringW( _ubool with_port ) const
{
	return WString( ).FromString( ToStringA( with_port ) );
}