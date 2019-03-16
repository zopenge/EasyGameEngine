//! @file     winShell.cpp
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// winShellTaskbar Implementation
//----------------------------------------------------------------------------

winShellTaskbar::winShellTaskbar( )
{
	EGE_INIT( mData );
}

winShellTaskbar::~winShellTaskbar( )
{
	// Delete the tray icon
	if ( mData.hIcon != _null )
		::Shell_NotifyIconW( NIM_DELETE, &mData );
}

_ubool winShellTaskbar::AddIcon( IApplication* application, _dword item_id, _dword item_icon, WStringPtr tip_message )
{
	if ( application == _null )
		return _false;

	// We have already created it
	if ( mData.hIcon != _null )
		return _false;

	// Initialize the tray notification data
	mData.cbSize			= sizeof( NOTIFYICONDATAW );
	mData.uID				= item_id;
	mData.uFlags			= NIF_ICON | NIF_MESSAGE | NIF_TIP;
	mData.hIcon				= ::LoadIconW( ::GetModuleHandleA( _null ), MAKEINTRESOURCEW( item_icon ) );
	mData.hWnd				= (HWND) application->GetApplicationHandle( );
	mData.uCallbackMessage	= _MESSAGE_TRAY;
	SafeCopyString( mData.szTip, tip_message.Str( ) );

	// Add the tray icon
	if ( ::Shell_NotifyIconW( NIM_ADD, &mData ) == _false )
		return _false;

	return _true;
}

//----------------------------------------------------------------------------
// winShell Implementation
//----------------------------------------------------------------------------

winShell::winShell( )
{
}

winShell::~winShell( )
{
}

_ubool winShell::Initialize( )
{
	return _true;
}

IShellTaskbar* winShell::GetTaskbar( )
{
	return &mTaskbar;
}

_ubool winShell::CreateFileLink( WStringPtr linktarget, WStringPtr workdir, WStringPtr linkpath, WStringPtr linkdesc, WStringPtr cmdline )
{
	//!	The shell link and persist file interface
	RefPtr< IShellLinkW >	shell_link;
	RefPtr< IPersistFile >	persist_file;

	// Get a pointer to the IShellLink interface
	if ( FAILED( ::CoCreateInstance( __uuidof( ShellLink ), _null, CLSCTX_INPROC_SERVER, __uuidof( ::IShellLink ), (_void**) &shell_link.GetRawRef( ) ) ) )
		return _false;

	// Query IShellLink for the IPersistFile interface
	if ( FAILED( shell_link->QueryInterface( __uuidof( IPersistFile ), (_void**) &persist_file.GetRawRef( ) ) ) )
		return _false;

	// Set the path to the shortcut target
	if ( FAILED( shell_link->SetPath( linktarget.Str( ) ) ) )
		return _false;

	// Set the command line of the shortcut target and add the description
	if ( FAILED( shell_link->SetArguments( cmdline.Str( ) ) ) )
		return _false;

	// Set the description of the shortcut target
	if ( FAILED( shell_link->SetDescription( linkdesc.Str( ) ) ) )
		return _false;

	// Set the working directory of the shortcut target
	if ( FAILED( shell_link->SetWorkingDirectory( workdir.Str( ) ) ) )
		return _false;

	// Save the file link
	if ( FAILED( persist_file->Save( linkpath.Str( ), _true ) ) )
		return _false;

	return _true;
}