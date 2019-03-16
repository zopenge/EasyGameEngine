//! @file     NetworkModule.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkModule
//----------------------------------------------------------------------------

class NetworkModule : public INTERFACE_MODULE_IMPL( INetworkModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( INetworkModule ) BaseClass;

private:
	//!	The network options
	FlagsObject				mNetworkOptions;

	//!	The total download bytes
	_qword					mTotalDownloadBytes;
	//!	The total upload bytes
	_qword					mTotalUploadBytes;

	//!	The simulating lag range
	DwordRange				mSimulatingLagRange;

	//!	The resource manager
	NetworkResourceManager*	mNetworkResourceManager;

private:
	//!	Initialize/Finalize URL SDK.
	_ubool InitializeURLSDK( );
	_void FinalizeURLSDK( );

	//!	Create resource manager.
	_ubool CreateResourceManager( );

public:
	NetworkModule( );
	virtual ~NetworkModule( );

public:
	//!	Initialize.
	_ubool Initialize( );
	//!	Finalize.
	_void Finalize( );
	
// IObject Interface
public:
	virtual _void				Tick( _dword limited_elapse, _dword elapse ) override;

// IPowerable Interface
public:
	virtual _ubool				PowerOn( ) override;
	virtual _void				PowerOff( ) override;

// IModule Interface
public:
	virtual _void				HandleEvent( EventBase& event ) override;

// INetworkModule Interface
public:
	virtual _void				EnableOptions( _dword options, _ubool enable ) override;
	virtual _ubool				IsEnableOptions( _dword options ) const override;

	virtual _ubool				GetRemoteSiteTime( WStringPtr url, _dword time_out, Time& time ) override;

	virtual _void				UpdateTotalDownloadBytes( _qword size ) override;
	virtual _void				UpdateTotalUploadBytes( _qword size ) override;

	virtual _qword				GetTotalDownloadBytes( ) const override;
	virtual _qword				GetTotalUploadBytes( ) const override;

	virtual _void				SetSimulatingLag( _dword min_lag, _dword max_lag ) override;
	virtual const DwordRange&	GetSimulatingLag( ) const override;
};

}