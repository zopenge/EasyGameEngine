//! @file     NetworkFTPConnection.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkFTPConnection
//----------------------------------------------------------------------------

class NetworkFTPConnection : public TNetworkConnection< INetworkFTPConnection >
{
private:
	typedef TNetworkConnection< INetworkFTPConnection > BaseClass;

private:
	//!	The base info
	struct BaseInfo : public FlagsObject
	{
		enum _FLAG
		{
			//!	Indicates to stop operation
			_FLAG_ABORT = 1 << 0,
		};

		enum _TYPE
		{
			_TYPE_UNKNOWN,
			_TYPE_UPLOAD,
		};

		_TYPE					mType;
		NetworkFTPConnection*	mFTPConnection;
		QwordParameters4		mParameters;

		_curlHandle				mHandle;

		BaseInfo( )
		{
			mType			= _TYPE_UNKNOWN;
			mFTPConnection	= _null;
			mParameters		= QwordParameters4::cNull;
		}
	};

	//!	The upload info
	struct UploadInfo : public BaseInfo
	{
		WString					mLocalFileName;
		WString					mRemoteFileName;
		IFileStreamReaderRef	mStreamReader;

		UploadInfo( )
		{
			this->mType = _TYPE_UPLOAD;
		}
	};
	typedef Queue< UploadInfo* > UploadInfoQueue;

private:
	//!	The upload handles
	UploadInfoQueue						mUploads;

	//!	The user name
	AString								mUserName;
	//!	The password
	AString								mPassword;
	//!	The user name and password string for cURL
	AString								mUserNameAndPassword;

	//!	The FTP notifier
	INetworkFTPConnectionNotifierRef	mFTPNotifier;

private:
	//!	The CURLOPT_DEBUGFUNCTION callback function.
	static _dword OnDebugFunctionCallback( CURL* urlhandle, curl_infotype type, _chara* buffer, _dword size, _void* userdata );
	//!	The CURLOPT_WRITEFUNCTION callback function.
	static _dword OnWriteFunctionCallback( _chara* buffer, _dword size, _dword number, _void* userdata );
	//!	The CURLOPT_READFUNCTION callback function.
	static _dword OnReadFunctionCallback( _chara* buffer, _dword size, _dword number, _void* userdata );
	//!	The CURLOPT_HEADERFUNCTION callback function.
	static _dword OnHeaderFunctionCallback( _chara* buffer, _dword size, _dword number, _void* userdata );
	//!	The CURLOPT_PROGRESSFUNCTION callback function.
	static _dword OnProgressFunctionCallback( _void* userdata, _double dltotal, _double dlnow, _double ultotal, _double ulnow );

private:
	//!	Create upload info.
	UploadInfo* CreateUploadInfo( const QwordParameters4& parameters );

public:
	NetworkFTPConnection( INetworkConnectionThread* connection_thread );
	virtual ~NetworkFTPConnection( );

public:
	//!	Initialize by remote address.
	_ubool Initialize( const Address& remote_address );
	//!	Initialize by URL address.
	_ubool Initialize( WStringPtr url_address );

// INetworkConnection Interface
public:
	virtual _NETWORK_CONNECTION_TYPE		GetType( ) const override;

	virtual _void							Stop( ) override;

	virtual _ubool							Send( _dword size, const _byte* buffer ) override;
	virtual _ubool							SendInstant( _dword size, const _byte* buffer ) override;

	virtual _ubool							IsRemoteFileExist( WStringPtr filename ) override;
	virtual INetworkStreamReaderPassRef		OpenRemoteFile( WStringPtr filename, INetworkStreamReaderNotifier* notifier = _null ) override;

	virtual _void							ProcessDelayConnectOperations( ) override;
	virtual _void							ProcessDelaySendOperations( ) override;
	virtual _void							ProcessDelayRecvOperations( ) override;

// INetworkFTPConnection Interface
public:
	virtual _void							SetFTPNotifier( INetworkFTPConnectionNotifier* notifier ) override;
	virtual INetworkFTPConnectionNotifier*	GetFTPNotifier( ) override;

	virtual _void							SetUserName( AStringPtr username ) override;
	virtual _void							SetPassword( AStringPtr password ) override;

	virtual _ubool							UploadFile( WStringPtr local_filename, WStringPtr remote_filename, const QwordParameters4& parameters ) override;
};

//----------------------------------------------------------------------------
// NetworkFTPConnection Implementation
//----------------------------------------------------------------------------

}