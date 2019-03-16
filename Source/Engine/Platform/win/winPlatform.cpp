//! @file     winPlatform.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Crash Functions Implementation
//----------------------------------------------------------------------------

#if (USE_GOOGLE_BREAK_PAD == 1)

static bool OnFilterCallback( void* context, EXCEPTION_POINTERS* exinfo, MDRawAssertionInfo* assertion )
{
	return _true;
}

static bool OnMinidumpCallback( const wchar_t* dump_path, const wchar_t* minidump_id, void* context, EXCEPTION_POINTERS* exinfo, MDRawAssertionInfo* assertion, bool succeeded )
{
	// Output the dump file path
	OUTPUT_DEBUG_STRING( FORMAT_WSTRING_2( L"CRASH ! The dump file path is '%s/%s'\n", dump_path, minidump_id ) );

	return _true;
}

#endif

//----------------------------------------------------------------------------
// winPlatform Implementation
//----------------------------------------------------------------------------

winPlatform::winPlatform( )
{
#if (USE_GOOGLE_BREAK_PAD == 1)
	mExceptionHandler	= _null;
#endif
}

winPlatform::~winPlatform( )
{
	Finalize( );
}

_ubool winPlatform::InitDumper( )
{
#if (USE_GOOGLE_BREAK_PAD == 1)
	WString root_path = GetPlatform( )->GetDocumentDirectory( );
	WString dump_path = Path::BuildFilePath( root_path, L"dump" );
	if ( FileSystem::CreateDir( dump_path ) == _false )
		return _false;

	mExceptionHandler = new google_breakpad::ExceptionHandler( dump_path.Str( ), OnFilterCallback, OnMinidumpCallback, _null, google_breakpad::ExceptionHandler::HANDLER_ALL );
#endif

	return _true;
}

_ubool winPlatform::Initialize( )
{
	if ( BaseClass::Initialize( ) == _false )
		return _false;

	if ( InitDumper( ) == _false )
		return _false;

	// Initialize web view
	if ( winWebView::Initialize( ) == _false )
	{
		OUTPUT_DEBUG_STRING( L"Initialize Win-WebView failed \n" );
		return _false;
	}

	return _true;
}

_void winPlatform::Finalize( )
{
	// Clear device info
	mDeviceInfo.mAdvertisingIdentifier.Clear( _true );
	mDeviceInfo.mIdentifierForVendor.Clear( _true );
	mDeviceInfo.mDeviceName.Clear( _true );
	mDeviceInfo.mModelName.Clear( _true );
	mDeviceInfo.mSystemName.Clear( _true );
	mDeviceInfo.mSystemVersion.Clear( _true );
	mDeviceInfo.mHardwareIDv2.Clear( _true );

	// Finalize modules
	winWebView::Finalize( );

#if (USE_GOOGLE_BREAK_PAD == 1)
	EGE_DELETE( mExceptionHandler );
#endif

	BaseClass::Finalize( );
}

_ubool winPlatform::SetWorkingDirectory( WStringPtr working_dir )
{
	// Use local archive
	LocalArchive* local_archive = new LocalArchive( );
	mWorkingArchive = local_archive;

	// Add working directory as patch
	if ( working_dir.IsEmpty( ) == _false )
	{
		// Add whole working directory path
		WString abs_working_dir_path = GetPlatform( )->GetAbsoluteDirectory( working_dir );
		local_archive->AddPatchDir( abs_working_dir_path );
	}

	// Let module to manage it
	local_archive->Release( );

	return BaseClass::SetWorkingDirectory( working_dir );
}

_ubool winPlatform::AddPatchDirectory( WStringPtr patch_dir )
{
	// Use local archive
	LocalArchive* local_archive = mWorkingArchive.cast_static< LocalArchive >( );

	// Add patch directory
	if ( local_archive->AddPatchDir( patch_dir ) == _false )
		return _false;

	return _true;
}

_ubool winPlatform::RemovePatchDirectory( WStringPtr patch_dir )
{
	// Use local archive
	LocalArchive* local_archive = mWorkingArchive.cast_static< LocalArchive >( );

	// Remove patch directory
	if ( local_archive->RemovePatchDir( patch_dir ) == _false )
		return _false;

	return _true;
}

const PlatformDeviceInfo& winPlatform::GetDeviceInfo( )
{
	if ( mDeviceInfo.mDeviceName.IsEmpty( ) )
	{
		AString mac_address;
		GetNet( )->GetLocalMACAddress( mac_address );

		GetPlatform( )->GetLocalComputerName( mDeviceInfo.mDeviceName );
		mDeviceInfo.mIdentifierForVendor	= L"MSWindows";
		mDeviceInfo.mModelName				= L"x86";
		mDeviceInfo.mHardwareIDv2.FromString( mac_address );
	}

	return BaseClass::GetDeviceInfo( );
}

_qword winPlatform::GetCurProcessMemSize( ) const
{
	PROCESS_MEMORY_COUNTERS mem_status	= {0};
	mem_status.cb						= sizeof( mem_status );
	::GetProcessMemoryInfo( ::GetCurrentProcess( ), &mem_status, mem_status.cb );

	return mem_status.WorkingSetSize;
}

_qword winPlatform::GetTotalMemSize( ) const
{
	static _qword total_mem_size = 0;
	if ( total_mem_size == 0 )
	{
		MEMORYSTATUSEX mem_status	= {0};
		mem_status.dwLength			= sizeof( mem_status );
		::GlobalMemoryStatusEx( &mem_status );

		total_mem_size = mem_status.ullTotalPhys;
	}

	return total_mem_size;
}

PointU winPlatform::GetMainScreenSize( ) const
{
	RECT rect;
	::GetClientRect( (HWND)gMainWindowHandle, (RECT*)&rect );

	PointU size( rect.right - rect.left, rect.bottom - rect.top );
	return size;
}

_ubool winPlatform::IsScreenOn( ) const
{
	return _true;
}

_void winPlatform::OpenURL( WStringPtr url )
{
	::ShellExecuteW( _null, L"open", url.Str( ), _null, _null, SW_SHOWNORMAL );
}

IStreamReaderPassRef winPlatform::LoadSystemFont( WStringPtr name )
{
	_charw font_path[1024];
	if ( Platform::GetSystemFontPath( font_path, 1024 ) == _false )
		return _null;

	// Get the font full path in system folder
	WString font_fullpath = Path::BuildFilePath( font_path, name );

	// Load font file
	IStreamReaderPassRef stream_reader = GetInterfaceFactory( )->CreateFileStreamReader( font_fullpath );
	if ( stream_reader.IsNull( ) )
	{
		WLOG_ERROR_1( L"The '%s' font is not existing in system", font_fullpath.Str( ) );
		return _null;
	}

	return stream_reader;
}

IWebViewPassRef	winPlatform::CreateWebView( const PointI& pos, const PointI& size )
{
	winWebView* web_view = new winWebView( );
	if  ( web_view->Initialize( pos, size ) == _false )
		{ EGE_RELEASE( web_view ); return _null; }

	return web_view;
}

IEditBoxPassRef	winPlatform::CreateEditBox( )
{
	return new winEditBox( );
}

IMessageBoxPassRef winPlatform::CreateMessageBox( IMessageBoxNotifier* notifier ) const
{
	winMessageBox* message_box = new winMessageBox( );
	message_box->SetNotifier( notifier );

	return message_box;
}

IKeychainPassRef winPlatform::CreateKeychain( WStringPtr identifier, WStringPtr access_group )
{
	return _null;
}

_void winPlatform::Vibrate( _dword duration )
{

}

_void winPlatform::CancelVibrate( )
{

}

_dword winPlatform::GetDirectXVersion( )
{
	// Open the registry to read the DirectX info
	winRegistry registry;
	if ( registry.Initialize( IRegistry::_KEY_LOCAL_MACHINE, L"Software\\Microsoft\\DirectX" ) == _false )
		return _DIRECTX_UNKNOWN;

	// Read the DirectX version string
	WString dx_version_string;
	if ( registry.ReadValueString( registry.GetRootKey( ), L"Version", dx_version_string ) == _false )
		return _DIRECTX_UNKNOWN;

	// DirectX 8.1
	if ( dx_version_string == L"4.08.01.0881" )
		return _DIRECTX_81;

	// DirectX 9.0
	if ( dx_version_string == L"4.09.00.0900" )
		return _DIRECTX_90;

	// DirectX 9.0a
	if ( dx_version_string == L"4.09.00.0901" )
		return _DIRECTX_90a;

	// DirectX 9.0b
	if ( dx_version_string == L"4.09.00.0902" )
		return _DIRECTX_90b;

	// DirectX 9.0c
	if ( dx_version_string == L"4.09.00.0904" )
		return _DIRECTX_90c;

	// DirectX 10.0
	if ( dx_version_string.StartsWith( L"4.10." ) )
		return _DIRECTX_100;

	// Unknown DirectX version
	return _DIRECTX_UNKNOWN;
}

_ubool winPlatform::GetLocalComputerName( WString& name )
{
	_charw string[1024]; DWORD length = 1024;
	if ( !::GetComputerNameW( string, &length ) )
		return _false;

	name = string;

	return _true;
}

_ubool winPlatform::GetCurrentUserName( WString& name )
{
	_charw string[1024]; DWORD length = 1024;
	if ( !::GetUserNameW( string, &length ) )
		return _false;

	name = string;

	return _true;
}

_ubool winPlatform::GetUserPath( WString& path )
{
	WString desktop_path;
	if ( GetDesktopPath( desktop_path ) == _false )
		return _false;

	_dword index = desktop_path.SearchR2L( '\\' );
	if ( index == -1 )
		path = desktop_path;
	else
		path = desktop_path.SubString( index );

	return _true;
}

_ubool winPlatform::GetWindowPath( WString& path )
{
	_charw string[1024]; _dword length = 1024;
	if ( !::GetWindowsDirectoryW( string, length ) )
		return _false;

	path = string;

	return _true;
}

_ubool winPlatform::GetDesktopPath( WString& path )
{
	winRegistry registry;
	if ( registry.Initialize( IRegistry::_KEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders" ) == _false )
		return _false;

	if ( registry.ReadValueString( registry.GetRootKey( ), L"Desktop", path ) == _false )
		return _false;

	return _true;
}

_ubool winPlatform::GetProgramGroupPath( WString& path )
{
	winRegistry registry;
	if ( registry.Initialize( IRegistry::_KEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders" ) == _false )
		return _false;

	if ( registry.ReadValueString( registry.GetRootKey( ), L"Programs", path ) == _false )
		return _false;

	return _true;
}

_ubool winPlatform::GetProgramFilesPath( WString& path )
{
	winRegistry registry;
	if ( registry.Initialize( IRegistry::_KEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion" ) == _false )
		return _false;

	if ( registry.ReadValueString( registry.GetRootKey( ), L"ProgramFilesDir", path ) == _false )
		return _false;

	return _true;
}

_ubool winPlatform::IsKeyDown( _dword keycode )
{
	return ( ::GetKeyState( keycode ) & 0x80 ) != 0;
}

PointI winPlatform::GetMousePosition( _handle window )
{
	PointI mouse = PointI::cZeroPoint;
	::GetCursorPos( (POINT*) &mouse );

	if ( window != _null )
		::ScreenToClient( (HWND) window, (POINT*) &mouse );

	return mouse;
}

_handle winPlatform::LoadCursorFromFile( WStringPtr filename )
{
	return ::LoadCursorFromFileW( filename.Str( ) );
}

_ubool winPlatform::DestroyCursor( _handle cursor )
{
	return EGE_BOOLEAN( ::DestroyCursor( (HCURSOR) cursor ) );
}

_handle winPlatform::SetCursor( _handle cursor )
{
	return ::SetCursor( (HCURSOR) cursor );
}

PointI winPlatform::GetCursorPos( )
{
	PointI pos;
	::GetCursorPos( (POINT*) &pos );

	return pos;
}

_handle winPlatform::CreateCompletionPort( _handle object, _dword completionkey, _dword threadnumber )
{
	_handle handle = ::CreateIoCompletionPort( INVALID_HANDLE_VALUE, _null, 0, threadnumber );
	if ( handle == _null )
		return _null;

	// Attach completion port to the object
	if ( object != _null && ::CreateIoCompletionPort( object, handle, completionkey, 0 ) == _null )
		{ ::CloseHandle( handle ); }

	return handle;
}

_void winPlatform::CloseCompletionPort( _handle handle )
{
	Platform::CloseHandle( handle );
}

_ubool winPlatform::GetQueuedCompletionStatus( _handle handle, _dword milliseconds, _dword& bytes_transferred, _dword& completionkey )
{
	DWORD queued_bytes_transferred = 0, queued_completionkey = 0;
	_ubool ret = EGE_BOOLEAN( ::GetQueuedCompletionStatus( handle, &queued_bytes_transferred, &queued_completionkey, _null, milliseconds ) );
	if ( ret )
	{
		bytes_transferred	= queued_bytes_transferred;
		completionkey		= queued_completionkey;
	}

	return ret;
}

_ubool winPlatform::PostQueuedCompletionStatus( _handle handle, _dword bytes_transferred, _dword completionkey )
{
	return ::PostQueuedCompletionStatus( handle, bytes_transferred, completionkey, _null ) != 0;
}