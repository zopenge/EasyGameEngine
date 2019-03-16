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

_ubool Platform::WaitForMultipleObjects( _dword number, _handle* objects, _ubool waitall, _dword milliseconds )
{
	return anyPlatformKernel::WaitForMultipleObjects( number, objects, waitall, milliseconds );
}

_handle Platform::CloneEvent( _handle object )
{
    return anyPlatformKernel::CloneEvent( object );
}

_handle Platform::CreateEvent( _ubool manualreset, _ubool initialstate, const _charw* objectname )
{
	return anyPlatformKernel::CreateEvent( manualreset, initialstate, objectname );
}

_handle Platform::OpenEvent( const _charw* objectname )
{
	return anyPlatformKernel::OpenEvent( objectname );
}

_ubool Platform::SetEvent( _handle object )
{
	return anyPlatformKernel::SetEvent( object );
}

_ubool Platform::ResetEvent( _handle object )
{
	return anyPlatformKernel::ResetEvent( object );
}

_handle Platform::CreateMutex( _ubool initialowner, const _charw* objectname )
{
	return anyPlatformKernel::CreateMutex( initialowner, objectname );
}

_handle Platform::OpenMutex( const _charw* objectname )
{
	return anyPlatformKernel::OpenMutex( objectname );
}

_ubool Platform::ReleaseMutex( _handle& object )
{
	return anyPlatformKernel::ReleaseMutex( object );
}

_handle Platform::CreateSemaphore( _dword initialcount, _dword maximumcount, const _charw* objectname )
{
	return anyPlatformKernel::CreateSemaphore( initialcount, maximumcount, objectname );
}

_handle Platform::OpenSemaphore( const _charw* objectname )
{
	return anyPlatformKernel::OpenSemaphore( objectname );
}

_ubool Platform::ReleaseSemaphore( _handle object, _dword releasecount )
{
	return anyPlatformKernel::ReleaseSemaphore( object, releasecount );
}

_handle Platform::CreateWaitableTimer( _ubool manualreset, const _charw* objectname )
{
	return anyPlatformKernel::CreateWaitableTimer( manualreset, objectname );
}

_handle Platform::OpenWaitableTimer( const _charw* objectname )
{
	return anyPlatformKernel::OpenWaitableTimer( objectname );
}

_ubool Platform::SetWaitableTimer( _handle object, _dword interval, _dword period )
{
	return anyPlatformKernel::SetWaitableTimer( object, interval, period );
}

_ubool Platform::CancelWaitableTimer( _handle& object )
{
	return anyPlatformKernel::CancelWaitableTimer( object );
}

_handle Platform::CreateAutoReleasePool( )
{
	return GetIOSResourceModule( )->CreateAutoReleasePool( );
}

_void Platform::ReleaseAutoReleasePool( _handle pool )
{
	GetIOSResourceModule( )->ReleaseAutoReleasePool( pool );
}

_void Platform::Sleep( _dword milliseconds )
{
	anyPlatformKernel::Sleep( milliseconds );
}