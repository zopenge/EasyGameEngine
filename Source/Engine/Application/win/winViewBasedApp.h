//! @file     winViewBasedApp.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winViewBasedApp
//----------------------------------------------------------------------------

class winViewBasedApp : public INTERFACE_VIEWBASED_APP_IMPL( IViewBasedApp )
{
private:
	typedef INTERFACE_VIEWBASED_APP_IMPL( IViewBasedApp ) BaseClass;

private:
	// The touch ID counter ( only for touch pad emulator )
	_dword			mTouchID;
	// The tracing mouse flag
	_ubool			mTraceMouseFlag;

	//!	The loading times of initialize application
	_dword			mAppLoadingTimes;

	//!	The window class name
	AString			mWindowClassName;
	//!	The window application
	winApp*			mWindowApp;

	//!	The creation flag
	_CREATION_FLAG	mCreationFlag;

	//!	Unicode IME input bytes
	DwordStack		mIMEInputBytes;

private:
	//!	Handle message.
	//!	@param		message			The message.
	//!	@return		True indicates processed this message.
	static _ubool HandleEvent( EventBase& event );

	//!	Process window message.
	//! @param		window_handle	The window handle.
	//! @param		msgid			The message ID.
	//! @param		wparam			The parameter.
	//! @param		lparam			The parameter.
	//! @return		The default window process result.
	static _int __stdcall WndProc( _handle window_handle, _dword msgid, _dword wparam, _dword lparam );

public:
	winViewBasedApp( _CREATION_FLAG flag );
	virtual ~winViewBasedApp( );

public:
	//!	Initialize.
	_ubool Initialize( );

// IObserver Interface
public:
	virtual _void			Notify( const EventBase& event, const IObject* object, const IObservable* generator ) override;

// IApplication Interface
public:
	virtual _handle			GetApplicationHandle( ) const override;
	virtual _handle			GetApplicationLayerHandle( ) const override;

	virtual _void 			Show( ) override;
	virtual _void 			Hide( ) override;

	virtual _void			SetTitle( WStringPtr title ) override;

	virtual _void			EnableAlwaysOnTop( _ubool enable ) override;

	virtual _int 			Run( IAppDelegate* app_delegate, ICommandLineParser* cmd_parser ) override;

// IViewBasedApp Interface
public:
	virtual _void 			Center( ) override;
	virtual _void			Move( _int delta_x, _int delta_y ) override;

	virtual _void			LockSize( ) override;
	virtual _void			UnlockSize( ) override;

	virtual _void 			SetPos( _dword x, _dword y ) override;
	virtual PointI			GetPos( ) const override;
	virtual _void 			SetSize( _dword width, _dword height ) override;
	virtual PointU			GetSize( ) const override;
	virtual RectI			GetRect( ) const override;
	virtual _void 			SetClientSize( _dword width, _dword height, _int* deltawidth = _null, _int* deltaheight = _null ) override;
	virtual RectU			GetClientRectU( ) const override;

	virtual _ORIENTATION	GetOrientation( ) const override;

	virtual _void 			SetCapture( ) override;
	virtual _void 			ReleaseCapture( ) override;
};

}