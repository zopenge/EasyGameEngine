//! @file     iosPlatformKernel.cpp
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Kernel Implementation
//----------------------------------------------------------------------------

_PLATFORM_TYPE Platform::GetPlatformType( )
{
	return _PLATFORM_TYPE_IOS;
}

const _charw* Platform::GetPlatformName( )
{
	return L"ios";
}

_ubool Platform::GetPlatformVersion( _dword& major, _dword& minor )
{
    return _true;
}

_ubool Platform::IsEmbeddedSystem( )
{
	return _true;
}

_handle Platform::InitializeCriticalSection( )
{
	return anyPlatformKernel::InitializeCriticalSection( );
}

_void Platform::DeleteCriticalSection( _handle object )
{
	return anyPlatformKernel::DeleteCriticalSection( object );
}

_void Platform::EnterCriticalSection( _handle object )
{
	anyPlatformKernel::EnterCriticalSection( object );
}

_void Platform::LeaveCriticalSection( _handle object )
{
	anyPlatformKernel::LeaveCriticalSection( object );
}

_void Platform::CloseHandle( _handle handle )
{
	anyPlatformKernel::CloseHandle( handle );
}

_ubool Platform::WaitForSingleObject( _handle object, _dword milliseconds )
{
	return anyPlatformKernel::WaitForSingleObject( object, milliseconds );
}

_handle Platform::CloneEvent( _handle object )
{
    return anyPlatformKernel::CloneEvent( object );
}

_handle Platform::CreateEvent( _ubool manualreset, _ubool initialstate )
{
	return anyPlatformKernel::CreateEvent( manualreset, initialstate );
}

_ubool Platform::SetEvent( _handle object )
{
	return anyPlatformKernel::SetEvent( object );
}

_ubool Platform::ResetEvent( _handle object )
{
	return anyPlatformKernel::ResetEvent( object );
}

_handle Platform::CreateAutoReleasePool( )
{
	return GetIOSPlatformModule( )->CreateAutoReleasePool( );
}

_void Platform::ReleaseAutoReleasePool( _handle pool )
{
	GetIOSPlatformModule( )->ReleaseAutoReleasePool( pool );
}

_void Platform::Sleep( _dword milliseconds )
{
	anyPlatformKernel::Sleep( milliseconds );
}
