//! @file     anyPlatformProcess.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// anyPlatformProcess
//----------------------------------------------------------------------------

class anyPlatformProcess {
public:
	static _handle CreateNamedPipe(const _charw* name, _dword maxnumber, _dword outbuffersize, _dword inbuffersize, _dword timeout);
	static _ubool ConnectNamedPipe(_handle handle);
	static _void DisconnectNamedPipe(_handle handle);
	static _ubool WaitNamedPipe(const _charw* name, _dword timeout);
	static _ubool PeekNamedPipe(_handle handle, _void* buffer, _dword size, _dword* bytesread, _dword* total_bytes_avail, _dword* bytes_left);
	static _ubool GetModuleFileName(_handle module, _charw* name, _dword length);
	static _handle GetModuleHandleA(const _chara* modulename);
	static _handle GetModuleHandleW(const _charw* modulename);
	static _ubool SetProcessAffinityMask(_handle processhandle, _dword mask);
	static _ubool SetThreadAffinityMask(_handle threadhandle, _dword mask, _dword* prevmask);
	static _ubool GetProcessAffinityMask(_handle processhandle, _dword& mask, _dword* systemmask);
	static _dword GetProcessID(_handle processhandle);
	static _handle GetProcessHandle(_dword processid);
	static _thread_id GetMainThreadID();
	static _ubool IsMainThread();
	static _dword GetCurrentProcessID();
	static _thread_id GetCurrentThreadID();
	static _handle GetCurrentProcessHandle();
	static _handle GetCurrentThreadHandle();
	static _ubool SetThreadName(_thread_id threadid, const _chara* name);
	static _ubool SetThreadName(_thread_id threadid, const _charw* name);
	static _ubool SuspendThread(_handle thread);
	static _ubool ResumeThread(_handle thread);
	static _ubool GetThreadTimes(_handle thread, _qword* creationtime, _qword* exittime, _qword* kerneltime, _qword* usertime);
	static _float GetThreadCPUUsage(_handle thread, _dword timenow, _qword& last_thread_time, _qword& last_sample_time, _qword& last_sample_delta);
	static _ubool QueueUserAPC(_handle thread, Platform::OnAPCProc funcpointer, _void* parameter);
	static _handle CreateThread(Platform::OnThreadStartRoutine funcpointer, _dword priority, _void* parameter, _ubool suspend, _qword* threadid);
	static _void CloseThread(_handle thread);
	static _ubool GetExitCodeThread(_handle thread, _dword& exit_code);
	static _ubool IsThreadAlive(_handle thread);
	static _void KillThread(_handle thread);
	static _ubool WaitThread(_handle thread, _dword* ret_code);
	static _handle LoadLibrary(const _charw* filename);
	static _ubool FreeLibrary(_handle module);
	static _void ExitProcess(_dword exitcode);
	static _ubool TerminateProcess(_handle processhandle, _dword exitcode);
	static _ubool DebugActiveProcessStop(_dword process_id);
	static _ubool IsProcessAlive(_handle processhandle);
	static _ubool CreateProcess(const _chara* modulename, const _chara* cmdline, _dword creationflags, const _chara* workdir, _handle* processhandle, _handle* threadhandle);
	static _ubool CreateProcess(const _charw* modulename, const _charw* cmdline, _dword creationflags, const _charw* workdir, _handle* processhandle, _handle* threadhandle);
	static _ubool ReadProcessMemory(_handle processhandle, const _void* baseaddress, _void* buffer, _dword size, _dword* bytesread);
};

//----------------------------------------------------------------------------
// anyPlatformProcess Implementation
//----------------------------------------------------------------------------

} // namespace EGE