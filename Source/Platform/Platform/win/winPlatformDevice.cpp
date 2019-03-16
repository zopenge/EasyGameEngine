//! @file     winPlatformDevice.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Device Implementation
//----------------------------------------------------------------------------

_ubool Platform::IsKeyDown( _dword key )
{
	return EGE_BOOLEAN( ::GetKeyState( key ) & 0x8000 );
}

_ubool Platform::GetCursorPos( _handle window_handle, PointI& pos )
{
	// Get the cursor position
	if ( !::GetCursorPos( (POINT*) &pos ) )
		return _false;

	// Get the cursor position of window's client if we provide window handle
	if ( window_handle && (!::ScreenToClient( (HWND) window_handle, (POINT*) &pos )) )
		return _false;

	return _true;
}

_ubool Platform::GetSoundCardName( _charw* name, _dword number )
{
	// Load "winmm.dll" library
	_handle dll_module = Platform::LoadLibrary( "winmm.dll" );
	if ( dll_module == _null )
		return _false;

	// Get "waveOutGetDevCapsW" function interface
	typedef _dword (_stdcall *GetDevCaps)( _dword, WAVEOUTCAPSW*, _dword );
	GetDevCaps get_devcaps_func = (GetDevCaps) ::GetProcAddress( (HMODULE) dll_module, "waveOutGetDevCapsW" );
	if ( get_devcaps_func == _null )
		return _false;

	// Call "waveOutGetDevCapsW" function
	WAVEOUTCAPSW wavecaps = { 0 };
	if ( (*get_devcaps_func)( 0, &wavecaps, sizeof( WAVEOUTCAPSW ) ) != 0 )
		return _false;

	Platform::CopyString( name, wavecaps.szPname, number );

	return _true;
}