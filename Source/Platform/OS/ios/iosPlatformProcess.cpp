//! @file     iosPlatformProcess.cpp
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Process Implementation
//----------------------------------------------------------------------------

_handle Platform::CreateNamedPipe( const _charw* name, _PIPE_ACCESS accessmode, _dword mode, _dword maxnumber, _dword outbuffersize, _dword inbuffersize, _dword timeout )
{
	return anyPlatformProcess::CreateNamedPipe( name, accessmode, mode, maxnumber, outbuffersize, inbuffersize, timeout );
}

_ubool Platform::ConnectNamedPipe( _handle handle )
{
	return anyPlatformProcess::ConnectNamedPipe( handle );
}

_void Platform::DisconnectNamedPipe( _handle handle )
{
}

_ubool Platform::WaitNamedPipe( const _charw* name, _dword timeout )
{
	return anyPlatformProcess::WaitNamedPipe( name, timeout );
}

_ubool Platform::PeekNamedPipe( _handle handle, _void* buffer, _dword size, _dword* bytesread, _dword* total_bytes_avail, _dword* bytes_left )
{
	return anyPlatformProcess::PeekNamedPipe( handle, buffer, size, bytesread, total_bytes_avail, bytes_left );
}

_ubool Platform::GetModuleFileName( _handle module, _charw* name, _dword length )
{
	return anyPlatformProcess::GetModuleFileName( module, name, length );
}

_handle Platform::GetModuleHandleA( const _chara* modulename )
{
	return anyPlatformProcess::GetModuleHandleA( modulename );
}

_handle Platform::GetModuleHandleW( const _charw* modulename )
{
	return anyPlatformProcess::GetModuleHandleW( modulename );
}

_ubool Platform::SetProcessAffinityMask( _handle processhandle, _dword mask )
{
	return anyPlatformProcess::SetProcessAffinityMask( processhandle, mask );
}

_ubool Platform::SetThreadAffinityMask( _handle threadhandle, _dword mask, _dword* prevmask )
{
	return anyPlatformProcess::SetThreadAffinityMask( threadhandle, mask, prevmask );
}

_ubool Platform::GetProcessAffinityMask( _handle processhandle, _dword& mask, _dword* systemmask )
{
	return anyPlatformProcess::GetProcessAffinityMask( processhandle, mask, systemmask );
}

_dword Platform::GetProcessID( _handle processhandle )
{
	return anyPlatformProcess::GetProcessID( processhandle );
}

_handle Platform::GetProcessHandle( _dword processid )
{
	return anyPlatformProcess::GetProcessHandle( processid );
}

_thread_id Platform::GetMainThreadID( )
{
	return anyPlatformProcess::GetMainThreadID( );
}

_ubool Platform::IsMainThread( )
{
	return anyPlatformProcess::IsMainThread( );
}

_dword Platform::GetCurrentProcessID( )
{
	return anyPlatformProcess::GetCurrentProcessID( );
}

_thread_id Platform::GetCurrentThreadID( )
{
	return anyPlatformProcess::GetCurrentThreadID( );
}

_handle Platform::GetCurrentProcessHandle( )
{
	return anyPlatformProcess::GetCurrentProcessHandle( );
}

_handle Platform::GetCurrentThreadHandle( )
{
	return anyPlatformProcess::GetCurrentThreadHandle( );
}

_ubool Platform::SetThreadName( _thread_id threadid, const _chara* name )
{
	return anyPlatformProcess::SetThreadName( threadid, name );
}

_ubool Platform::SetThreadName( _thread_id threadid, const _charw* name )
{
	return anyPlatformProcess::SetThreadName( threadid, name );
}

_ubool Platform::SetThreadPriority( _handle thread, _PRIORITY priority )
{
	return anyPlatformProcess::SetThreadPriority( thread, priority );
}

_ubool Platform::SuspendThread( _handle thread )
{
	return anyPlatformProcess::SuspendThread( thread );
}

_ubool Platform::ResumeThread( _handle thread )
{
	return anyPlatformProcess::ResumeThread( thread );
}

_ubool Platform::GetThreadTimes( _handle thread, _qword* creationtime, _qword* exittime, _qword* kerneltime, _qword* usertime )
{
	return anyPlatformProcess::GetThreadTimes( thread, creationtime, exittime, kerneltime, usertime );
}

_float Platform::GetThreadCPUUsage( _handle thread, _dword timenow, _qword& last_thread_time, _qword& last_sample_time, _qword& last_sample_delta )
{
	return anyPlatformProcess::GetThreadCPUUsage( thread, timenow, last_thread_time, last_sample_time, last_sample_delta );
}

_ubool Platform::QueueUserAPC( _handle thread, OnAPCProc funcpointer, _void* parameter )
{
	return anyPlatformProcess::QueueUserAPC( thread, funcpointer, parameter );
}

_handle Platform::CreateThread( OnThreadStartRoutine funcpointer, _dword priority, _void* parameter, _ubool suspend, _qword* threadid )
{
	return anyPlatformProcess::CreateThread( funcpointer, priority, parameter, suspend, threadid );
}

_void Platform::CloseThread( _handle thread )
{
	anyPlatformProcess::CloseThread( thread );
}

_ubool Platform::GetExitCodeThread( _handle thread, _dword& exit_code )
{
	return anyPlatformProcess::GetExitCodeThread( thread, exit_code );
}

_ubool Platform::IsThreadAlive( _handle thread )
{
	return anyPlatformProcess::IsThreadAlive( thread );
}

_void Platform::KillThread( _handle thread )
{
    anyPlatformProcess::KillThread( thread );
}

_ubool Platform::WaitThread( _handle thread, _dword* ret_code )
{
	return anyPlatformProcess::WaitThread( thread, ret_code );
}

_handle Platform::LoadLibrary( const _charw* filename )
{
	return anyPlatformProcess::LoadLibrary( filename );
}

_ubool Platform::FreeLibrary( _handle module )
{
	return anyPlatformProcess::FreeLibrary( module );
}

_void Platform::ExitProcess( _dword exitcode )
{
	anyPlatformProcess::ExitProcess( exitcode );
}

_ubool Platform::TerminateProcess( _handle processhandle, _dword exitcode )
{
	return anyPlatformProcess::TerminateProcess( processhandle, exitcode );
}

_ubool Platform::DebugActiveProcessStop( _dword process_id )
{
	return anyPlatformProcess::DebugActiveProcessStop( process_id );
}

_ubool Platform::IsProcessAlive( _handle processhandle )
{
	return anyPlatformProcess::IsProcessAlive( processhandle );
}

_ubool Platform::CreateProcess( const _chara* modulename, const _chara* cmdline, _dword creationflags, const _chara* workdir, _handle* processhandle, _handle* threadhandle )
{
	return anyPlatformProcess::CreateProcess( modulename, cmdline, creationflags, workdir, processhandle, threadhandle );
}

_ubool Platform::CreateProcess( const _charw* modulename, const _charw* cmdline, _dword creationflags, const _charw* workdir, _handle* processhandle, _handle* threadhandle )
{
	return anyPlatformProcess::CreateProcess( modulename, cmdline, creationflags, workdir, processhandle, threadhandle );
}

_ubool Platform::ReadProcessMemory( _handle processhandle, const _void* baseaddress, _void* buffer, _dword size, _dword* bytesread )
{
	return anyPlatformProcess::ReadProcessMemory( processhandle, baseaddress, buffer, size, bytesread );
}

_ubool Platform::HasProcess( const _charw* name )
{
	return _false;
}
