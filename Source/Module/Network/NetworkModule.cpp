//! @file     NetworkModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGENetwork.h"

//----------------------------------------------------------------------------
// NetworkModule Implementation
//----------------------------------------------------------------------------

NetworkModule::NetworkModule( ) : BaseClass( L"Network", Version( NETWORK_FILEVER ) )
{
	mTotalDownloadBytes		= 0;
	mTotalUploadBytes		= 0;

	mSimulatingLagRange		= DwordRange::cNull;

	mNetworkResourceManager = _null;
}

NetworkModule::~NetworkModule( )
{
	Finalize( );

	GetModuleManager( )->UnregisterModule( this );
}

_ubool NetworkModule::InitializeURLSDK( )
{
#if (_USE_CRUL_SDK == 1)
	if ( ::curl_global_init( CURL_GLOBAL_ALL ) != CURLE_OK )
	{
		ALOG_ERROR_1( "Initialize 'v%s' cURL SDK failed", (const _chara*) LIBCURL_VERSION );
		return _false;
	}

	// Easy to check cURL features
	#define CHECK_CURL_FEATURE( x, name ) \
		if ( curl_version_info( CURLVERSION_NOW )->features & x ) \
			{ ALOG_TRACE_1( "cURL [%s] OK", (const _chara*)name ); } \
		else \
			{ ALOG_WARNING_1( "cURL [%s] FAILED", (const _chara*)name ); }

	// Check cURL features
	CHECK_CURL_FEATURE( CURL_VERSION_IPV6, "IPv6-enabled" );
	CHECK_CURL_FEATURE( CURL_VERSION_SSL, "SSL options are present" );
	CHECK_CURL_FEATURE( CURL_VERSION_LIBZ, "libz features are present" );
	CHECK_CURL_FEATURE( CURL_VERSION_NTLM, "NTLM auth is supported" );
	CHECK_CURL_FEATURE( CURL_VERSION_DEBUG, "Built with debug capabilities" );
	CHECK_CURL_FEATURE( CURL_VERSION_ASYNCHDNS, "Asynchronous DNS resolves" );
	CHECK_CURL_FEATURE( CURL_VERSION_SPNEGO, "SPNEGO auth is supported" );
	CHECK_CURL_FEATURE( CURL_VERSION_LARGEFILE, "Supports files larger than 2GB" );
	CHECK_CURL_FEATURE( CURL_VERSION_IDN, "Internationized Domain Names are supported" );
	CHECK_CURL_FEATURE( CURL_VERSION_SSPI, "Built against Windows SSPI" );
	CHECK_CURL_FEATURE( CURL_VERSION_CONV, "Character conversions supported" );
	CHECK_CURL_FEATURE( CURL_VERSION_CURLDEBUG, "Debug memory tracking supported" );
	CHECK_CURL_FEATURE( CURL_VERSION_TLSAUTH_SRP, "TLS-SRP auth is supported" );
	CHECK_CURL_FEATURE( CURL_VERSION_NTLM_WB, "NTLM delegation to winbind helper is supported" );
	CHECK_CURL_FEATURE( CURL_VERSION_HTTP2, "HTTP2 support built-in" );
	CHECK_CURL_FEATURE( CURL_VERSION_GSSAPI, "Built against a GSS-API library" );
	CHECK_CURL_FEATURE( CURL_VERSION_KERBEROS5, "Kerberos V5 auth is supported" );
	CHECK_CURL_FEATURE( CURL_VERSION_UNIX_SOCKETS, "Unix domain sockets support" );
	CHECK_CURL_FEATURE( CURL_VERSION_PSL, "Mozilla's Public Suffix List, used for cookie domain verification" );
	CHECK_CURL_FEATURE( CURL_VERSION_HTTPS_PROXY, "HTTPS-proxy support built-in" );

	ALOG_TRACE_1( "Initialize 'v%s' cURL SDK OK", (const _chara*) LIBCURL_VERSION );
#elif (_USE_CHROME_SDK == 1)

#endif

	return _true;
}

_void NetworkModule::FinalizeURLSDK( )
{
#if (_USE_CRUL_SDK == 1)
	::curl_global_cleanup( );
#elif (_USE_CHROME_SDK == 1)

#endif
}

_ubool NetworkModule::CreateResourceManager( )
{
	mNetworkResourceManager = new NetworkResourceManager( );
	if ( mNetworkResourceManager->Initialize( 1024 ) == _false )
		return _false;

	gNetworkResourceManager = mNetworkResourceManager;

	return _true;
}

_ubool NetworkModule::Initialize( )
{
	WLOG_TRACE( L"Create network module ..." );

	// Initialize URL SDK
	if ( InitializeURLSDK( ) == _false )
		return _false;

	// Create the resource manager
	if ( CreateResourceManager( ) == _false )
	{
		WLOG_ERROR( L"Create network resource manager failed" );
		return _false;
	}

	// Register as observer
	GetModuleManager( )->RegisterObserver( this );

	WLOG_TRACE( L"Create network module DONE" );

	return _true;
}

_void NetworkModule::Finalize( )
{
	WLOG_TRACE( L"Release network module ..." );

	// Finalize the resource manager
	EGE_RELEASE( mNetworkResourceManager );

	WLOG_TRACE( L"Release network module DONE" );

	// Clear global modules
	gNetworkResourceManager	= &NullNetwork::GetInstance( ).GetNetworkResourceManager( );
	gNetworkModule			= &NullNetwork::GetInstance( ).GetNetworkModule( );

	// Finalize URL SDK
	FinalizeURLSDK( );
}

_void NetworkModule::Tick( _dword limited_elapse, _dword elapse )
{
	mNetworkResourceManager->Tick( limited_elapse, elapse );
}

_ubool NetworkModule::PowerOn( )
{
	if ( BaseClass::PowerOn( ) == _false )
		return _false;

	return _true;
}

_void NetworkModule::PowerOff( )
{
	BaseClass::PowerOff( );

	// Unregister as observer
	GetModuleManager( )->UnregisterObserver( this );
}

_void NetworkModule::HandleEvent( EventBase& event )
{
	switch ( event.mEventID )
	{
		case _EVENT_ACTIVITY_PAUSE:
		{
			if ( IsEnableOptions( _NETWORK_OPTION_PAUSE_ALL_WHEN_APP_PAUSE ) )
				mNetworkResourceManager->Pause( );
		}
		break;

		case _EVENT_ACTIVITY_RESUME:
		{
			if ( IsEnableOptions( _NETWORK_OPTION_PAUSE_ALL_WHEN_APP_PAUSE ) )
				mNetworkResourceManager->Resume( );
		}
		break;

		default:
			break;
	}
}

_void NetworkModule::EnableOptions( _dword options, _ubool enable )
{
	mNetworkOptions.EnableFlags( options, enable );
}

_ubool NetworkModule::IsEnableOptions( _dword options ) const
{
	return mNetworkOptions.HasFlags( options, _true );
}

_ubool NetworkModule::GetRemoteSiteTime( WStringPtr url, _dword time_out, Time& time )
{
	// Initialize HTTP connection
	INetworkHTTPConnectionRef http_connection = GetNetworkResourceManager( )->CreateHTTPConnection( url, _null );
	if ( http_connection.IsNull( ) )
		return _false;

	// Set time out
	http_connection->SetConnectTimeout( time_out );

	// Post the url request command
	http_connection->SetFlags( INetworkConnection::_FLAG_BLOCK_MODE );
	if ( http_connection->GetWithNoBody( "" ) == _false )
		return _false;

	// Get the request time
	time = http_connection->GetRequestTime( );

	return _true;
}

_void NetworkModule::UpdateTotalDownloadBytes( _qword size )
{
	mTotalDownloadBytes += size;
}

_void NetworkModule::UpdateTotalUploadBytes( _qword size )
{
	mTotalUploadBytes += size;
}

_qword NetworkModule::GetTotalDownloadBytes( ) const
{
	return mTotalDownloadBytes;
}

_qword NetworkModule::GetTotalUploadBytes( ) const
{
	return mTotalUploadBytes;
}

_void NetworkModule::SetSimulatingLag( _dword min_lag, _dword max_lag )
{
	mSimulatingLagRange = DwordRange( min_lag, max_lag );
}

const DwordRange& NetworkModule::GetSimulatingLag( ) const
{
	return mSimulatingLagRange;
}
