//! @file     anyPlatformProcess.cpp
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// anyPlatformProcess Implementation
//----------------------------------------------------------------------------

_handle anyPlatformProcess::CreateNamedPipe(const _charw* name, _dword maxnumber, _dword outbuffersize, _dword inbuffersize, _dword timeout) {
	return _null;
}

_ubool anyPlatformProcess::ConnectNamedPipe(_handle handle) {
	return _true;
}

_void anyPlatformProcess::DisconnectNamedPipe(_handle handle) {
}

_ubool anyPlatformProcess::WaitNamedPipe(const _charw* name, _dword timeout) {
	return _false;
}

_ubool anyPlatformProcess::PeekNamedPipe(_handle handle, _void* buffer, _dword size, _dword* bytesread, _dword* total_bytes_avail, _dword* bytes_left) {
	return _true;
}

_ubool anyPlatformProcess::GetModuleFileName(_handle module, _charw* name, _dword length) {
	return _false;
}

_handle anyPlatformProcess::GetModuleHandleA(const _chara* modulename) {
	return (_handle)modulename;
}

_handle anyPlatformProcess::GetModuleHandleW(const _charw* modulename) {
	return (_handle)modulename;
}

_ubool anyPlatformProcess::SetProcessAffinityMask(_handle processhandle, _dword mask) {
	return _false;
}

_ubool anyPlatformProcess::SetThreadAffinityMask(_handle threadhandle, _dword mask, _dword* prevmask) {
	return _false;
}

_ubool anyPlatformProcess::GetProcessAffinityMask(_handle processhandle, _dword& mask, _dword* systemmask) {
	return _false;
}

_dword anyPlatformProcess::GetProcessID(_handle processhandle) {
	return 0;
}

_handle anyPlatformProcess::GetProcessHandle(_dword processid) {
	return _null;
}

_thread_id anyPlatformProcess::GetMainThreadID() {
	return gMainThreadID;
}

_ubool anyPlatformProcess::IsMainThread() {
	_thread_id cur_thread_id = GetCurrentThreadID();
	return gMainThreadID == cur_thread_id;
}

_dword anyPlatformProcess::GetCurrentProcessID() {
	return 0;
}

_thread_id anyPlatformProcess::GetCurrentThreadID() {
#if (USE_PTHREAD == 1)
#	if defined(_PLATFORM_WINDOWS_)
	return (_thread_id)_pthread_self().p;
#	else
	return (_thread_id)_pthread_self();
#	endif
#else
	return 0;
#endif
}

_handle anyPlatformProcess::GetCurrentProcessHandle() {
	return _null;
}

_handle anyPlatformProcess::GetCurrentThreadHandle() {
	return _null;
}

_ubool anyPlatformProcess::SetThreadName(_thread_id threadid, const _chara* name) {
#ifdef _PLATFORM_ANDROID_
	::pthread_setname_np(threadid, name);
#endif

	return _true;
}

_ubool anyPlatformProcess::SetThreadName(_thread_id threadid, const _charw* name) {
	_chara name_ansi[1024];
	Platform::Utf16ToAnsi(name_ansi, 1024, name);

	return SetThreadName(threadid, name_ansi);
}

_ubool anyPlatformProcess::SuspendThread(_handle thread) {
	return _false;
}

_ubool anyPlatformProcess::ResumeThread(_handle thread) {
	return _false;
}

_ubool anyPlatformProcess::GetThreadTimes(_handle thread, _qword* creationtime, _qword* exittime, _qword* kerneltime, _qword* usertime) {
	return _false;
}

_float anyPlatformProcess::GetThreadCPUUsage(_handle thread, _dword timenow, _qword& last_thread_time, _qword& last_sample_time, _qword& last_sample_delta) {
	return 0.0f;
}

_ubool anyPlatformProcess::QueueUserAPC(_handle thread, Platform::OnAPCProc funcpointer, _void* parameter) {
	return _false;
}

_handle anyPlatformProcess::CreateThread(
    Platform::OnThreadStartRoutine funcpointer, _dword priority,
    _void* parameter, _ubool suspend, _qword* threadid) {
#if (USE_PTHREAD == 1)
	// Create thread info
	pthread_t* thread_info = new pthread_t;

	// Initialize the thread attribute
	pthread_attr_t attr;
	_pthread_attr_init(&attr);
	_pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	// Set attribute parameters
	// Processes scheduled under one of the real-time policies (SCHED_FIFO,
	// SCHED_RR) have a sched_priority value in the range 1 (low) to 99 (high).
	// (As the numbers imply, real-time threads always have higher priority than
	// normal threads.)
	if (priority != 0) {
		sched_param param;
		param.sched_priority = priority;
		_pthread_attr_setschedparam(&attr, &param);
	}

	// The callback function declaration
	typedef void* (*OnFuncPointer)(void*);

	// Create thread
	int err = _pthread_create(thread_info, &attr, (OnFuncPointer)funcpointer,
	                          parameter);
	if (err != 0) {
		EGE_DELETE(thread_info);
		_pthread_attr_destroy(&attr);

		OUTPUT_DEBUG_STRING(
		    FORMAT_ASTRING_1("Create thread failed, err: %d\n", err));
		return _null;
	}

	// Free thread attributes
	_pthread_attr_destroy(&attr);

	// Feedback the thread ID
#	ifdef _PLATFORM_WINDOWS_
	_qword thread_id = (_qword)thread_info->p;
#	else
	_qword thread_id = (_qword)thread_info;
#	endif

	OUTPUT_DEBUG_STRING(
	    FORMAT_ASTRING_1("Create thread OK, ID: 0x%.16llx\n", thread_id));

	// Feedback the thread ID
	if (threadid != _null) *threadid = thread_id;

	return (_handle)thread_info;
#else
	return _null;
#endif
}

_void anyPlatformProcess::CloseThread(_handle thread) {
#if (USE_PTHREAD == 1)
	pthread_t* thread_info = (pthread_t*)thread;
	if (thread_info == _null) return;

	_pthread_detach(*thread_info);

	EGE_DELETE(thread_info);
#else
#endif
}

_ubool anyPlatformProcess::GetExitCodeThread(_handle thread, _dword& exit_code) {
	return _false;
}

_ubool anyPlatformProcess::IsThreadAlive(_handle thread) {
#if (USE_PTHREAD == 1)
	pthread_t* thread_info = (pthread_t*)thread;
	if (thread_info == _null) return _false;

	_dword ret = _pthread_kill(*thread_info, 0);

	// It's dead
	if (ret == ESRCH || ret == EINVAL) return _false;

	// It's alive
	return _true;
#else
	return _false;
#endif
}

_void anyPlatformProcess::KillThread(_handle thread) {
#if (USE_PTHREAD == 1)
	pthread_t* thread_info = (pthread_t*)thread;
	if (thread_info == _null) return;

	_pthread_kill(*thread_info, 3 /*SIGQUIT*/);
#else
#endif
}

_ubool anyPlatformProcess::WaitThread(_handle thread, _dword* ret_code) {
#if (USE_PTHREAD == 1)
	pthread_t* thread_info = (pthread_t*)thread;
	if (thread_info == _null) return _false;

	_dword exit_code = 0;
	if (_pthread_join(*thread_info, (_void**)&exit_code) != 0) return _false;

	if (ret_code != _null) *ret_code = exit_code;
#else
	return _false;
#endif

	return _true;
}

_handle anyPlatformProcess::LoadLibrary(const _charw* filename) {
	return _null;
}

_ubool anyPlatformProcess::FreeLibrary(_handle module) {
	return _false;
}

_void anyPlatformProcess::ExitProcess(_dword exitcode) {
}

_ubool anyPlatformProcess::TerminateProcess(_handle processhandle, _dword exitcode) {
	return _false;
}

_ubool anyPlatformProcess::DebugActiveProcessStop(_dword process_id) {
	return _false;
}

_ubool anyPlatformProcess::IsProcessAlive(_handle processhandle) {
	return _false;
}

_ubool anyPlatformProcess::CreateProcess(const _chara* modulename, const _chara* cmdline, _dword creationflags, const _chara* workdir, _handle* processhandle, _handle* threadhandle) {
	return _false;
}

_ubool anyPlatformProcess::CreateProcess(const _charw* modulename, const _charw* cmdline, _dword creationflags, const _charw* workdir, _handle* processhandle, _handle* threadhandle) {
	return _false;
}

_ubool anyPlatformProcess::ReadProcessMemory(_handle processhandle, const _void* baseaddress, _void* buffer, _dword size, _dword* bytesread) {
	return _false;
}