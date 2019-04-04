#include "EGEPlatform.h"

/// <summary>
/// The thread name data.
/// </summary>
struct ThreadNameData {
	_dword mType; // Must be 0x1000.
	const _chara* mName; // Pointer to name (in user addr space).
	_thread_id mThreadID; // Thread ID (-1=caller thread).
	_dword mFlags; // Reserved for future use, must be zero.
};

//----------------------------------------------------------------------------
// Platform-Process Implementation
//----------------------------------------------------------------------------

_void Platform::RestartCurrentProcess() {
	_charw module_file_name[2048];
	Platform::GetModuleFileName(_null, module_file_name, 2048);

	AString cmd_string = "start " + AString().FromString(Encoding::Utf16, module_file_name);
	system(cmd_string.CStr());

	KillCurrentProcess();
}

_void Platform::KillCurrentProcess() {
	::ExitProcess(-1);
}

_handle Platform::CreateNamedPipe(const _charw* name, _dword maxnumber, _dword outbuffersize, _dword inbuffersize, _dword timeout) {
	return ::CreateNamedPipeW(name, PIPE_ACCESS_DUPLEX, 0, maxnumber, outbuffersize, inbuffersize, timeout, _null);
}

_ubool Platform::ConnectNamedPipe(_handle handle) {
	if (handle == _null)
		return _false;

	if (!::ConnectNamedPipe(handle, _null)) {
		// Check whether it's already connected
		if (::GetLastError() != ERROR_PIPE_CONNECTED)
			return _false;
	}

	return _true;
}

_void Platform::DisconnectNamedPipe(_handle handle) {
	if (handle == _null)
		return;

	::DisconnectNamedPipe(handle);
}

_ubool Platform::WaitNamedPipe(const _charw* name, _dword timeout) {
	return !!(::WaitNamedPipeW(name, timeout));
}

_ubool Platform::PeekNamedPipe(_handle handle, _void* buffer, _dword size, _dword* bytesread, _dword* total_bytes_avail, _dword* bytes_left) {
	if (handle == _null)
		return _false;

	DWORD pipe_read_bytes = 0, pipe_total_bytes_avail = 0, pipe_bytes_left = 0;
	_ubool ret = !!(::PeekNamedPipe(handle, buffer, size, &pipe_read_bytes, &pipe_total_bytes_avail, &pipe_bytes_left));
	if (ret) {
		if (bytesread != _null)
			*bytesread = pipe_read_bytes;

		if (total_bytes_avail != _null)
			*total_bytes_avail = pipe_total_bytes_avail;

		if (bytes_left != _null)
			*bytes_left = pipe_bytes_left;
	}

	return ret;
}

_ubool Platform::GetModuleFileName(_handle module, _charw* name, _dword length) {
	if (name == _null || length == 0)
		return _false;

	if (::GetModuleFileNameW((HMODULE)module, name, length) == 0)
		return _false;

	return _true;
}

_handle Platform::GetModuleHandleA(const _chara* modulename) {
	return ::GetModuleHandleA(modulename);
}

_handle Platform::GetModuleHandleW(const _charw* modulename) {
	return ::GetModuleHandleW(modulename);
}

_ubool Platform::SetProcessAffinityMask(_handle processhandle, _dword mask) {
	return ::SetProcessAffinityMask(processhandle, mask) == TRUE;
}

_ubool Platform::SetThreadAffinityMask(_handle threadhandle, _dword mask, _dword* prevmask) {
	_dword prevmaskbackup = ::SetThreadAffinityMask(threadhandle, mask);
	if (prevmaskbackup == 0)
		return _false;

	if (prevmask != _null)
		*prevmask = prevmaskbackup;

	return _true;
}

_ubool Platform::GetProcessAffinityMask(_handle processhandle, _dword& mask, _dword* systemmask) {
	DWORD process_mask = 0, process_system_mask = 0;
	_ubool ret = !!(::GetProcessAffinityMask(processhandle, &process_mask, &process_system_mask));
	if (ret) {
		mask = process_mask;

		if (systemmask != _null)
			*systemmask = process_system_mask;
	}

	return ret;
}

_dword Platform::GetProcessID(_handle processhandle) {
	return ::GetProcessId(processhandle);
}

_handle Platform::GetProcessHandle(_dword processid) {
	return ::OpenProcess(PROCESS_ALL_ACCESS, _false, processid);
}

_thread_id Platform::GetMainThreadID() {
	return gMainThreadID;
}

_ubool Platform::IsMainThread() {
	return gMainThreadID == GetCurrentThreadID();
}

_dword Platform::GetCurrentProcessID() {
	return ::GetCurrentProcessId();
}

_thread_id Platform::GetCurrentThreadID() {
#if (USE_PTHREAD == 1)
	return anyPlatformProcess::GetCurrentThreadID();
#else
	return ::GetCurrentThreadId();
#endif
}

_handle Platform::GetCurrentProcessHandle() {
	return ::GetCurrentProcess();
}

_handle Platform::GetCurrentThreadHandle() {
	return ::GetCurrentThread();
}

_ubool Platform::SetThreadName(_thread_id threadid, const _chara* name) {
#if (USE_PTHREAD == 1)
	return anyPlatformProcess::SetThreadName(threadid, name);
#else
	// Build the thread name info
	ThreadNameData threadnameinfo;
	threadnameinfo.mType = 0x1000;
	threadnameinfo.mName = name;
	threadnameinfo.mThreadID = threadid;
	threadnameinfo.mFlags = 0;

	// Raise a exception to set the thread name
	__try {
		::RaiseException(MS_VC_EXCEPTION, 0, sizeof(threadnameinfo) / sizeof(_dword), (ULONG_PTR*)&threadnameinfo);

	} __except (EXCEPTION_CONTINUE_EXECUTION) {
	}
#endif

	return _true;
}

_ubool Platform::SetThreadName(_thread_id threadid, const _charw* name) {
	_chara name_ansi[1024];
	Platform::Utf16ToAnsi(name_ansi, 1024, name);

	return SetThreadName(threadid, name_ansi);
}

_ubool Platform::SuspendThread(_handle thread) {
	return ::SuspendThread(thread) != -1;
}

_ubool Platform::ResumeThread(_handle thread) {
	return ::ResumeThread(thread) != -1;
}

_ubool Platform::GetThreadTimes(_handle thread, _qword* creationtime, _qword* exittime, _qword* kerneltime, _qword* usertime) {
	return ::GetThreadTimes(thread, (LPFILETIME)creationtime, (LPFILETIME)exittime, (LPFILETIME)kerneltime, (LPFILETIME)usertime) != 0;
}

_float Platform::GetThreadCPUUsage(_handle thread, _dword timenow, _qword& last_thread_time, _qword& last_sample_time, _qword& last_sample_delta) {
	// Get the thread time info
	_qword creationtime, exittime, kerneltime, usertime;
	if (Platform::GetThreadTimes(thread, &creationtime, &exittime, &kerneltime, &usertime) == _false)
		return 0.0f;

	// Get the current thread time so far
	_qword currentthreadtime = kerneltime + usertime;
	// Get the elapsed thread time ( expressed in 100 nanosecond intervals to make it in [0.0 ~ 100.0] bounds )
	_qword elapsedthreadtime = (currentthreadtime - last_thread_time) / 10000;

	// Update the last sample delta of thread
	if (timenow != last_sample_time)
		last_sample_delta = timenow - last_sample_time;

	// Get the CPU usage percent
	_float cpuusage = ((_float)elapsedthreadtime) / ((_float)last_sample_delta);

	// Update the thread time info of tracking CPU usage
	last_thread_time = currentthreadtime;
	last_sample_time = timenow;

	// Feedback the CPU usage percent
	return Math::Min(100.0f, cpuusage * 100.0f);
}

_ubool Platform::QueueUserAPC(_handle thread, OnAPCProc funcpointer, _void* parameter) {
	return ::QueueUserAPC((PAPCFUNC)funcpointer, thread, (ULONG_PTR)parameter) != 0;
}

_handle Platform::CreateThread(OnThreadStartRoutine funcpointer, _dword priority, _void* parameter, _ubool suspend, _thread_id* threadid) {
	if (funcpointer == _null)
		return _null;

#if (USE_PTHREAD == 1)
	return anyPlatformProcess::CreateThread(funcpointer, priority, parameter, suspend, threadid);
#else
	// The thread id
	DWORD feedback_thread_id = 0;

	// Create thread
	_handle thread_handle = ::CreateThread(_null, 0, (LPTHREAD_START_ROUTINE)funcpointer, parameter, suspend ? CREATE_SUSPENDED : 0, &feedback_thread_id);
	if (thread_handle == _null)
		return _null;

	// Set thread priority
	::SetThreadPriority(thread_handle, Math::Clamp<_dword>(priority, 0, THREAD_PRIORITY_TIME_CRITICAL));

	// Feedback the thread ID
	if (threadid != _null)
		*threadid = feedback_thread_id;

	return thread_handle;
#endif
}

_void Platform::CloseThread(_handle thread) {
	if (thread == _null)
		return;

#if (USE_PTHREAD == 1)
	anyPlatformProcess::CloseThread(thread);
#else
	::CloseHandle(thread);
#endif
}

_ubool Platform::GetExitCodeThread(_handle thread, _dword& exit_code) {
	DWORD thread_exit_code = 0;
	_ubool ret = !!(::GetExitCodeThread(thread, &thread_exit_code));
	if (ret) {
		exit_code = thread_exit_code;
	}

	return ret;
}

_ubool Platform::IsThreadAlive(_handle thread) {
#if (USE_PTHREAD == 1)
	return anyPlatformProcess::IsThreadAlive(thread);
#else
	_dword exit_code = 0;
	if (GetExitCodeThread(thread, exit_code) == _false)
		return _false;

	return exit_code == STILL_ACTIVE;
#endif
}

_void Platform::KillThread(_handle thread) {
#if (USE_PTHREAD == 1)
	anyPlatformProcess::KillThread(thread);
#else
	::TerminateThread(thread, -1);
#endif
}

_ubool Platform::WaitThread(_handle thread, _dword* ret_code) {
	if (thread == _null)
		return _false;

#if (USE_PTHREAD == 1)
	return anyPlatformProcess::WaitThread(thread, ret_code);
#else
	::WaitForSingleObject(thread, -1);

	if (ret_code != _null) {
		if (GetExitCodeThread(thread, *ret_code) == _false)
			return _false;
	}
#endif

	return _true;
}

_handle Platform::LoadLibrary(const _chara* filename) {
	if (filename == _null)
		return _null;

	return ::LoadLibraryA(filename);
}

_handle Platform::LoadLibrary(const _charw* filename) {
	if (filename == _null)
		return _null;

	return ::LoadLibraryW(filename);
}

_ubool Platform::FreeLibrary(_handle module) {
	return !!(::FreeLibrary((HMODULE)module));
}

_void* Platform::GetProcAddress(_handle module, const _chara* procname) {
	if (procname == _null)
		return _null;

	return ::GetProcAddress((HMODULE)module, procname);
}

_void Platform::ExitProcess(_dword exitcode) {
	::ExitProcess(exitcode);
}

_ubool Platform::TerminateProcess(_handle processhandle, _dword exitcode) {
	return !!(::TerminateProcess(processhandle, exitcode));
}

_ubool Platform::DebugActiveProcessStop(_dword process_id) {
	return !!(::DebugActiveProcessStop(process_id));
}

_ubool Platform::IsProcessAlive(_handle processhandle) {
	DWORD exit_code = 0;
	if (!::GetExitCodeProcess(processhandle, &exit_code))
		return _false;

	if (exit_code != STILL_ACTIVE)
		return _false;

	return _true;
}

_ubool Platform::CreateProcess(const _chara* modulename, const _chara* cmdline, _dword creationflags, const _chara* workdir, _handle* processhandle, _handle* threadhandle) {
	// Initialize the startup info
	STARTUPINFOA startupinfo = {0};
	startupinfo.cb = sizeof(STARTUPINFOA);
	startupinfo.dwFlags = STARTF_FORCEOFFFEEDBACK;

	// Create process module (http://www.baike.com/wiki/CreateProcess)
	PROCESS_INFORMATION processinfo = {0};
	_ubool retval = !!(::CreateProcessA(modulename, (LPSTR)cmdline, _null, _null, _false, creationflags, _null, workdir, &startupinfo, &processinfo));

	// Feedback the thread handle
	if (threadhandle != _null)
		*threadhandle = (_handle)processinfo.hThread;
	else
		::CloseHandle(processinfo.hThread);

	// Feedback the process handle
	if (processhandle != _null)
		*processhandle = (_handle)processinfo.hProcess;
	else
		::CloseHandle(processinfo.hProcess);

	return retval;
}

_ubool Platform::CreateProcess(const _charw* modulename, const _charw* cmdline, _dword creationflags, const _charw* workdir, _handle* processhandle, _handle* threadhandle) {
	// Initialize the startup info
	STARTUPINFOW startupinfo = {0};
	startupinfo.cb = sizeof(STARTUPINFOW);
	startupinfo.dwFlags = STARTF_FORCEOFFFEEDBACK;

	// Create process module (http://www.baike.com/wiki/CreateProcess)
	PROCESS_INFORMATION processinfo = {0};
	_ubool retval = !!(::CreateProcessW(modulename, (LPWSTR)cmdline, _null, _null, _false, creationflags | CREATE_UNICODE_ENVIRONMENT, _null, workdir, &startupinfo, &processinfo));

	// Feedback the thread handle
	if (threadhandle != _null)
		*threadhandle = (_handle)processinfo.hThread;
	else
		::CloseHandle(processinfo.hThread);

	// Feedback the process handle
	if (processhandle != _null)
		*processhandle = (_handle)processinfo.hProcess;
	else
		::CloseHandle(processinfo.hProcess);

	return retval;
}

_ubool Platform::ReadProcessMemory(_handle processhandle, const _void* baseaddress, _void* buffer, _dword size, _dword* bytesread) {
	DWORD process_bytes_read = 0;
	_ubool ret = !!(::ReadProcessMemory(processhandle, baseaddress, buffer, size, &process_bytes_read));
	if (ret) {
		if (bytesread != _null)
			*bytesread = process_bytes_read;
	}

	return ret;
}

_ubool Platform::HasProcess(const _charw* name) {
	// Take a snapshot of all processes in the system.
	HANDLE process_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (process_snap == INVALID_HANDLE_VALUE)
		return _false;

	// Found flag
	_ubool found = _false;

	// Fill in the size of the structure before using it.
	PROCESSENTRY32 pe32 = {0};
	pe32.dwSize = sizeof(PROCESSENTRY32);

	//  Walk the snapshot of the processes, and for each process, display information.
	if (Process32First(process_snap, &pe32)) {
		do {
			if (Platform::CompareString((const _charw*)pe32.szExeFile, name) == 0) {
				found = _true;
				break;
			}
		} while (Process32Next(process_snap, &pe32));
	}

	CloseHandle(process_snap);

	return found;
}