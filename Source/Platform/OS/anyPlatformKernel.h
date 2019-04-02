//! @file     anyPlatformKernel.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// anyPlatformKernel
//----------------------------------------------------------------------------

class anyPlatformKernel
{
public:
	static _handle InitializeCriticalSection( );
	static _void DeleteCriticalSection( _handle object );
	static _void EnterCriticalSection( _handle object );
	static _void LeaveCriticalSection( _handle object );
	static _void CloseHandle( _handle handle );
	static _ubool WaitForSingleObject( _handle object, _dword milliseconds );
	static _handle CloneEvent( _handle object );
	static _handle CreateEvent( _ubool manualreset, _ubool initialstate );
	static _ubool SetEvent( _handle object );
	static _ubool ResetEvent( _handle object );
	static _void Sleep( _dword milliseconds );
};

//----------------------------------------------------------------------------
// anyPlatformKernel Implementation
//----------------------------------------------------------------------------

}