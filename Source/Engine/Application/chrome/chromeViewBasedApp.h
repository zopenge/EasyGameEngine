//! @file     chromeViewBasedApp.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// chromeViewBasedApp
//----------------------------------------------------------------------------

class chromeViewBasedApp : public INTERFACE_VIEWBASED_APP_IMPL( IViewBasedApp )
{
private:
	typedef INTERFACE_VIEWBASED_APP_IMPL( IViewBasedApp ) BaseClass;

public:
	//!	The application status
	enum _APP_STATUS
	{
		_APP_STATUS_UNKNOWN,
		_APP_STATUS_INITIALIZED_FILE_SYSTEM,
		_APP_STATUS_INITIALIZED,
	};

private:
	_APP_STATUS				mAppStatus;

	chromeAppThread			mAppThread;

	ICommandLineParserRef	mCmdLineParser;

public:
	chromeViewBasedApp( );
	virtual ~chromeViewBasedApp( );

public:
	EGE_SET_ACCESSOR( _APP_STATUS, AppStatus )
	EGE_GET_ACCESSOR_CONST( _APP_STATUS, AppStatus )

public:
	//!	Initialize.
	EGE_INTERNAL _ubool Initialize( _dword argc, const _chara* argn[], const _chara* argv[] );
	//!	Finalize.
	EGE_INTERNAL _void Finalize( );

	//!	Process messages.
	EGE_INTERNAL _void ProcessLoadMessage( );
	EGE_INTERNAL _void ProcessChangedViewMessage( const ChromeMessageChangedView& message );
	EGE_INTERNAL _void ProcessChangedFocusMessage( const ChromeMessageChangedFocus& message );

	//!	Render.
	EGE_INTERNAL _void Render( IAppDelegate* app_delegate );

// IObserver Interface
public:
	virtual _void						Notify( const EventBase& event, const IObject* object, const IObservable* generator ) override;
	virtual _void 						Notify( const EventBase& event, const IObject* object, const IObservable* generator ) override;

// IApplication Interface
public:
	virtual _handle						GetApplicationHandle( ) const override;
	virtual _handle						GetApplicationLayerHandle( ) const override;

	virtual _void 						Show( ) override;
	virtual _void 						Hide( ) override;

	virtual _void						Quit( ) override;

	virtual _int						Run( IAppDelegate* app_delegate, const ICommandLineParser* cmd_parser ) override;

	virtual _ubool						OnBeforeLoadModules( ) override;
	virtual _ubool						OnAfterLoadModules( ) override;

// IViewBasedApp Interface
public:
	virtual _ubool						SetIcon( _dword id, IStreamReader* stream_reader ) override;

	virtual _void 						Center( ) override;
	virtual _void						Move( _int delta_x, _int delta_y ) override;

	virtual _void 						SetPos( _dword x, _dword y ) override;
	virtual PointI						GetPos( ) const override;
	virtual _void 						SetSize( _dword width, _dword height ) override;
	virtual PointU						GetSize( ) const override;
	virtual RectI 						GetRect( ) const override;
	virtual _void 						SetClientSize( _dword width, _dword height, _int* deltawidth = _null, _int* deltaheight = _null ) override;
	virtual RectU 						GetClientRectU( ) const override;

	virtual _dword						GetAttributes( ) const override;
	virtual _void						SetAttributes( _dword attributes ) override;

	virtual _VIEWBASED_APP_ORIENTATION	GetOrientation( ) const override;

	virtual _void 						SetCapture( ) override;
	virtual _void 						ReleaseCapture( ) override;

	virtual _void						LoadGameCenter( AStringPtr leader_board_id ) override;
	virtual _void						ShowLeaderBoardDialog( _ubool show ) override;
	virtual _void						ShowAchievementDialog( _ubool show ) override;

	virtual _void						LoadAdCenter( AStringPtr app_id, IAdView::_TYPE type ) override;
	virtual IAdViewRef					GetAdView( ) override;

	virtual _void						ShowAlertDialog( WStringPtr title, WStringPtr message ) override;
};

// --------------------------------------------------------------------------------------------------------------
// chromeViewBasedApp Implementation
// --------------------------------------------------------------------------------------------------------------

}