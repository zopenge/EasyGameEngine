//! @file     TNetworkHTTPConnection.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TNetworkHTTPConnection
//----------------------------------------------------------------------------

template< typename Type >
class TNetworkHTTPConnection : public TNetworkConnection< Type >
{
protected:
	typedef TNetworkConnection< Type > TBaseClass;

protected:
	//!	The base info
	struct BaseInfo : public FlagsObject
	{
		enum _FLAG
		{
			//!	Indicates abort operation
			_FLAG_ABORT				= 1 << 0,
			//!	Disable invoking callback functions
			_FLAG_DISABLE_NOTIFIER	= 1 << 1,
		};

		AString					mURLName;
		INetworkHTTPConnection*	mHTTPConnection;
		MemArrayPtr< _byte >	mFieldBuffer;
		IStreamWriterRef		mRecvBuffer;
		QwordParameters4		mParameters;

		_ubool IsAbort( ) const
		{
			return HasFlags( _FLAG_ABORT );
		}
		_ubool HasNotifier( ) const
		{
			return HasFlags( _FLAG_DISABLE_NOTIFIER ) == _false;
		}

		BaseInfo( )
		{
			mHTTPConnection = _null;
			mParameters		= QwordParameters4::cNull;
		}
	};

protected:
	//!	The SSL key file name
	AString	mSSLKeyFileName;
	//!	The SSL cert file name
	AString	mSSLCertFileName;
	//!	The CA cert file name
	AString	mCACertFileName;

protected:
	//!	Check whether enable SSL.
	_ubool IsEnableSSL( ) const;

protected:
	TNetworkHTTPConnection( INetworkConnectionThread* connection_thread );
	virtual ~TNetworkHTTPConnection( );

// INetworkConnection Interface
public:
	virtual _NETWORK_CONNECTION_TYPE	GetType( ) const override;

// INetworkHTTPConnection Interface
public:
	virtual _ubool						SetSSLKeyFromFile( WStringPtr filename ) override;
	virtual _ubool						SetSSLCertFromFile( WStringPtr filename ) override;
	virtual _ubool						SetSSLKeyFromStream( IStreamReader* stream_reader ) override;
	virtual _ubool						SetSSLCertFromStream( IStreamReader* stream_reader ) override;

	virtual _ubool						SetCACertFromFile( WStringPtr filename ) override;
	virtual _ubool						SetCACertFromStream( IStreamReader* stream_reader ) override;

	virtual _ubool						Get( AStringPtr url_name, AStringPtr get_field, const QwordParameters4& parameters = QwordParameters4::cNull ) override;
	virtual _ubool						Get( AStringPtr url_name, const AStringArray& header_list, AStringPtr get_field, const QwordParameters4& parameters = QwordParameters4::cNull ) override;

	virtual _ubool						Post( AStringPtr url_name, AStringPtr post_field, const QwordParameters4& parameters ) override;
	virtual _ubool						Post( AStringPtr url_name, const AStringArray& header_list, AStringPtr post_field, const QwordParameters4& parameters ) override;
	virtual _ubool						Post( AStringPtr url_name, const _byte* buffer, _dword size, const QwordParameters4& parameters = QwordParameters4::cNull ) override;
	virtual _ubool						Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters = QwordParameters4::cNull ) override;
};

//----------------------------------------------------------------------------
// TNetworkHTTPConnection Implementation
//----------------------------------------------------------------------------

template< typename Type >
TNetworkHTTPConnection< Type >::TNetworkHTTPConnection( INetworkConnectionThread* connection_thread ) : TBaseClass( connection_thread )
{
}

template< typename Type >
TNetworkHTTPConnection< Type >::~TNetworkHTTPConnection( )
{
}

template< typename Type >
_ubool TNetworkHTTPConnection< Type >::IsEnableSSL( ) const
{
	// Check optional
	{
		if ( this->HasFlags( INetworkConnection::_FLAG_WITH_CERTIFICATE ) )
			return _true;
	}

	// Check certificate
	{
		if ( mSSLKeyFileName.IsEmpty( ) == _false )
			return _true;

		if ( mSSLCertFileName.IsEmpty( ) == _false )
			return _true;

		if ( mCACertFileName.IsEmpty( ) == _false )
			return _true;
	}

	return _false;
}

template< typename Type >
_NETWORK_CONNECTION_TYPE TNetworkHTTPConnection< Type >::GetType( ) const
{
	return _NETWORK_CONNECTION_HTTP;
}

template< typename Type >
_ubool TNetworkHTTPConnection< Type >::SetSSLKeyFromFile( WStringPtr filename )
{
	if ( FileSystem::IsFileExist( filename ) == _false )
	{
		WLOG_ERROR_1( L"The '%s' SSL key file is not existing", filename.Str( ) );
		return _false;
	}

	mSSLKeyFileName.FromString( filename );

	return _true;
}

template< typename Type >
_ubool TNetworkHTTPConnection< Type >::SetSSLCertFromFile( WStringPtr filename )
{
	if ( FileSystem::IsFileExist( filename ) == _false )
	{
		WLOG_ERROR_1( L"The '%s' SSL cert file is not existing", filename.Str( ) );
		return _false;
	}

	mSSLCertFileName.FromString( filename );

	return _true;
}

template< typename Type >
_ubool TNetworkHTTPConnection< Type >::SetSSLKeyFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	WString filename;
	if ( GetPlatform( )->CreateTempFileInTempDirectory( L"", L"ssl_key", stream_reader->GetBuffer( ), stream_reader->GetSize( ), filename ) == _false )
	{
		WLOG_ERROR_1( L"Create '%s' temporary SSL key file failed", filename.Str( ) );
		return _false;
	}

	WLOG_TRACE_1( L"Create '%s' temporary SSL key file OK", filename.Str( ) );

	return SetSSLKeyFromFile( filename );
}

template< typename Type >
_ubool TNetworkHTTPConnection< Type >::SetSSLCertFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	WString filename;
	if ( GetPlatform( )->CreateTempFileInTempDirectory( L"", L"ssl_cert", stream_reader->GetBuffer( ), stream_reader->GetSize( ), filename ) == _false )
	{
		WLOG_ERROR_1( L"Create '%s' temporary SSL cert file failed", filename.Str( ) );
		return _false;
	}

	WLOG_TRACE_1( L"Create '%s' temporary SSL cert file OK", filename.Str( ) );

	return SetSSLCertFromFile( filename );
}

template< typename Type >
_ubool TNetworkHTTPConnection< Type >::SetCACertFromFile( WStringPtr filename )
{
	if ( FileSystem::IsFileExist( filename ) == _false )
	{
		WLOG_ERROR_1( L"The '%s' CA cert file is not existing", filename.Str( ) );
		return _false;
	}

	mCACertFileName.FromString( filename );

	return _true;
}

template< typename Type >
_ubool TNetworkHTTPConnection< Type >::SetCACertFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	WString filename;
	if ( GetPlatform( )->CreateTempFileInTempDirectory( L"", L"ca_cert", stream_reader->GetBuffer( ), stream_reader->GetSize( ), filename ) == _false )
	{
		WLOG_ERROR_1( L"Create '%s' temporary CA cert file failed", filename.Str( ) );
		return _false;
	}

	WLOG_TRACE_1( L"Create '%s' temporary CA cert file OK", filename.Str( ) );

	return SetCACertFromFile( filename );
}

template< typename Type >
_ubool TNetworkHTTPConnection< Type >::Get( AStringPtr url_name, AStringPtr get_field, const QwordParameters4& parameters )
{
	static AStringArray sNullHeaderList;
	return Get( url_name, sNullHeaderList, get_field, parameters );
}

template< typename Type >
_ubool TNetworkHTTPConnection< Type >::Get( AStringPtr url_name, const AStringArray& header_list, AStringPtr get_field, const QwordParameters4& parameters )
{
	EGE_ASSERT( 0 );
	return _false;
}

template< typename Type >
_ubool TNetworkHTTPConnection< Type >::Post( AStringPtr url_name, AStringPtr post_field, const QwordParameters4& parameters )
{
	static AStringArray sNullHeaderList;
	return Post( url_name, sNullHeaderList, post_field, parameters );
}

template< typename Type >
_ubool TNetworkHTTPConnection< Type >::Post( AStringPtr url_name, const AStringArray& header_list, AStringPtr post_field, const QwordParameters4& parameters )
{
	EGE_ASSERT( 0 );
	return _false;
}

template< typename Type >
_ubool TNetworkHTTPConnection< Type >::Post( AStringPtr url_name, const _byte* buffer, _dword size, const QwordParameters4& parameters )
{
	if ( buffer == _null || size == 0 )
		return _false;

	static AStringArray sNullHeaderList;
	return Post( url_name, sNullHeaderList, buffer, size, parameters );
}

template< typename Type >
_ubool TNetworkHTTPConnection< Type >::Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters )
{
	EGE_ASSERT( 0 );
	return _false;
}

}