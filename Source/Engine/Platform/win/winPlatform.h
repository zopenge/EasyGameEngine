//! @file     winPlatform.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winPlatform
//----------------------------------------------------------------------------

class winPlatform : public TPlatform< IWinPlatform >
{
private:
	typedef TPlatform< IWinPlatform > BaseClass;

private:
#if (USE_GOOGLE_BREAK_PAD == 1)
	google_breakpad::ExceptionHandler*	mExceptionHandler;
#endif

private:
	//!	Initialize dumper.
	_ubool InitDumper( );

public:
	winPlatform( );
	virtual ~winPlatform( );

// IPlatform Interface
public:
	virtual _ubool						Initialize( ) override;
	virtual _void						Finalize( ) override;

	virtual _ubool						SetWorkingDirectory( WStringPtr working_dir ) override;

	virtual _ubool						AddPatchDirectory( WStringPtr patch_dir ) override;
	virtual _ubool						RemovePatchDirectory( WStringPtr patch_dir ) override;

	virtual const PlatformDeviceInfo&	GetDeviceInfo( ) override;

	virtual _qword						GetCurProcessMemSize( ) const override;
	virtual _qword						GetTotalMemSize( ) const override;

	virtual PointU						GetMainScreenSize( ) const override;
	virtual _ubool						IsScreenOn( ) const override;

	virtual _void						OpenURL( WStringPtr url ) override;

	virtual IStreamReaderPassRef		LoadSystemFont( WStringPtr name ) override;

	virtual IWebViewPassRef				CreateWebView( const PointI& pos, const PointI& size ) override;
	virtual IEditBoxPassRef				CreateEditBox( ) override;
	virtual IMessageBoxPassRef			CreateMessageBox( IMessageBoxNotifier* notifier ) const override;

	virtual IKeychainPassRef			CreateKeychain( WStringPtr identifier, WStringPtr access_group ) override;

	virtual _void						Vibrate( _dword duration ) override;
	virtual _void						CancelVibrate( ) override;

// IWinPlatform Interface
public:
	virtual _dword						GetDirectXVersion( ) override;

	virtual _ubool 						GetLocalComputerName( WString& name ) override;
	virtual _ubool 						GetCurrentUserName( WString& name ) override;
	virtual _ubool 						GetUserPath( WString& path ) override;
	virtual _ubool 						GetWindowPath( WString& path ) override;
	virtual _ubool 						GetDesktopPath( WString& path ) override;
	virtual _ubool 						GetProgramGroupPath( WString& path ) override;
	virtual _ubool 						GetProgramFilesPath( WString& path ) override;

	virtual _ubool						IsKeyDown( _dword keycode ) override;
	virtual PointI						GetMousePosition( _handle window ) override;

	virtual _handle						LoadCursorFromFile( WStringPtr filename ) override;
	virtual _ubool						DestroyCursor( _handle cursor ) override;
	virtual _handle						SetCursor( _handle cursor ) override;
	virtual PointI						GetCursorPos( ) override;

	virtual _handle						CreateCompletionPort( _handle object, _dword completionkey = 0, _dword threadnumber = 0 ) override;
	virtual _void 						CloseCompletionPort( _handle handle ) override;
	virtual _ubool 						GetQueuedCompletionStatus( _handle handle, _dword milliseconds, _dword& bytes_transferred, _dword& completionkey ) override;
	virtual _ubool 						PostQueuedCompletionStatus( _handle handle, _dword bytes_transferred, _dword completionkey ) override;
};

//----------------------------------------------------------------------------
// winPlatform Implementation
//----------------------------------------------------------------------------

}