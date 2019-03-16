//! @file     NetworkHTTPStreamReader.chrome.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkHTTPStreamReader
//----------------------------------------------------------------------------

class NetworkHTTPStreamReader : public TNetworkStreamReader< INetworkStreamReader >
{
private:
	typedef TNetworkStreamReader< INetworkStreamReader > BaseClass;

private:
	//!	The URL loader.
	PP_Resource	mURLLoader;
	//!	The URL request info.
	PP_Resource	mURLRequestInfo;

	//!	The response header info
	AString		mResponseHeaderInfo;

private:
	//!	Get response info.
	_ubool GetResponseInfo( );
	//!	Get MIME content info.
	_ubool GetMIMEContentInfo( );

	//!	Build request info.
	_ubool BuildRequestInfo( );
	//!	Build streams info.
	_ubool BuildStreamsInfo( );

	//!	Open URL.
	_ubool OpenURL( );

public:
	NetworkHTTPStreamReader( INetworkStreamReaderNotifier* notifier );
	virtual ~NetworkHTTPStreamReader( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr remote_filename );

// INetworkStreamReader Interface
public:
	virtual _float	GetDownloadSpeed( ) override;
};

//----------------------------------------------------------------------------
// NetworkHTTPStreamReader Implementation
//----------------------------------------------------------------------------

}