#include "EGEPlatform.h"

Lock* Thread::sThreadLock = _null;
Thread::ThreadPtrArray* Thread::sThreads = _null;

// Check whether enable thread exception catch feature
#if defined(_PLATFORM_WINDOWS_)
#	define _CATCH_THREAD_EXCEPTION
#endif

#ifdef _CATCH_THREAD_EXCEPTION
#	if defined(_PLATFORM_WINDOWS_)
#		define _CATCH_THREAD_EXCEPTION_BEGIN() _try {
#		define _CATCH_THREAD_EXCEPTION_END()                     \
			}                                                     \
			_except(HandleException(GetExceptionInformation())) { \
			}
#	elif defined(_PLATFORM_ANDROID_)
#		define _CATCH_THREAD_EXCEPTION_BEGIN() try {
#		define _CATCH_THREAD_EXCEPTION_END()                                                            \
			}                                                                                            \
			catch (...) {                                                                                \
				ENABLE_STRING_BUFFER_MACROS_ANSI();                                                      \
				OUTPUT_DEBUG_STRING(FORMAT_ASTRING_BUFFER_1("Thread(%d) exception", thread->mThreadID)); \
			}
#	endif
#else
#	define _CATCH_THREAD_EXCEPTION_BEGIN()
#	define _CATCH_THREAD_EXCEPTION_END()
#endif

#if defined(_PLATFORM_WINDOWS_)

//! Handle execptions.
static int HandleException(EXCEPTION_POINTERS* exception_pointers) {
	Platform::DebuggerBreak();

	CallStackFrame call_stack;
	call_stack.Create(exception_pointers);

	for (CallStackFrame::Iterator it = call_stack.GetHeadIterator(); it.IsValid(); it++) {
		const CallStackFrameData& call_stack_frame = it;

		_chara string_buffer[2048];
		Platform::FormatStringBuffer(string_buffer, 2048, "%s(%d)\n", call_stack_frame.mFileName, call_stack_frame.mLineNumber);

		Platform::OutputDebugString(string_buffer);
	}

	EGE_ASSERT(0);

	// Unless you decide to terminate your process, return EXCEPTION_EXECUTE_HANDLER, so that the execution
	// continues normally after the __except block.
	return EXCEPTION_EXECUTE_HANDLER;
}

#endif

Thread::Thread() {
	mIsReleasing = _false;

	mObjectHandle = _null;
	mThreadID = 0;

	mLastThreadTime = 0;
	mLastSampleTime = Platform::GetCurrentTickCount();
	mLastSampleDelta = 0;

	sThreadLock->Enter();
	sThreads->Append(this);
	sThreadLock->Leave();
}

Thread::~Thread() {
	Close();

	sThreadLock->Enter();
	sThreads->Remove(this);
	sThreadLock->Leave();
}

_thread_ret Thread::RunThreadProc(Thread* thread) {
	_dword exitcode = 0;

	// Sleep a while to let the signal call wait() before call set()
	Platform::Sleep(100);

	// Get the thread name in ANSI mode
	_chara thread_name_ansi[1024];
	thread_name_ansi[0] = 0;
	Platform::Utf16ToAnsi(thread_name_ansi, 1024, thread->mThreadName.CStr());

	_thread_id id = thread->GetThreadID();
	Platform::OutputDebugString(AString().Format("Begin '%s' thread, ID:0x%.16llx\n", (const _chara*)thread_name_ansi, id).CStr());

	// Create auto release pool
	_handle pool = Platform::CreateAutoReleasePool();

	// Set for the ready event signal
	thread->mReadyEvent.Set();

	// Set the thread name on IOS platform
#ifdef _PLATFORM_IOS_
	::pthread_setname_np(thread_name_ansi);
#else
	Platform::SetThreadName(thread->mThreadID, thread_name_ansi);
#endif

	// Invoke the run thread callback function
	exitcode = thread->OnRunThread(thread->mParams);

	// Invoke the close thread callback function
	thread->OnCloseThread(exitcode, thread->mParams);

	// Release auto release pool
	Platform::ReleaseAutoReleasePool(pool);

	Platform::OutputDebugString(AString().Format("Exit '%s' thread (ret:%d) OK, ID:0x%.16llx\n", (const _chara*)thread_name_ansi, exitcode, id).CStr());

	// Sleep a while to call wait() before exit()
	Platform::Sleep(100);

	// Set for the exit event signal
	thread->mExitEvent.Set();

	return (_thread_ret)exitcode;
}

_thread_ret Thread::ThreadProc(_void* parameter) {
	Thread* thread = (Thread*)parameter;
	EGE_ASSERT(thread != _null);

	_thread_ret exitcode;

	_CATCH_THREAD_EXCEPTION_BEGIN() {
		exitcode = RunThreadProc(thread);
	}
	_CATCH_THREAD_EXCEPTION_END()

	return exitcode;
}

_ubool Thread::HasExit() const {
	return Platform::IsThreadAlive(mObjectHandle);
}

_ubool Thread::IsReleasing() const {
	return mIsReleasing;
}

_thread_id Thread::GetThreadID() const {
	return mThreadID;
}

_ubool Thread::SetThreadName(WStringPtr name) {
	if (name.IsEmpty())
		return _false;

	mThreadName = name;

	return Platform::SetThreadName(mThreadID, mThreadName.CStr());
}

WStringPtr Thread::GetThreadName() const {
	return mThreadName;
}

_float Thread::GetCPUUsage(_dword timenow) {
	// TODO: 1. Thread ID and last thread times in info structure
	// Remove this function from it and add it for GetThreadInfoByIndex( )
	// Add Get Thread CPU usage to Platform class : arguments is thread ID and last times.

	return Platform::GetThreadCPUUsage(mObjectHandle, timenow, mLastThreadTime, mLastSampleTime, mLastSampleDelta);
}

_ubool Thread::Create(_dword priority, _ubool suspend, WStringPtr name, const QwordParams2& params) {
	Close();

	// Set the params
	mParams = params;

	// Set the thread name
	mThreadName = name;

	// Create the thread ready event
	if (mReadyEvent.Create(_true, _false) == _false) {
		Close();
		return _false;
	}

	// Create the thread exit event
	if (mExitEvent.Create(_true, _false) == _false) {
		Close();
		return _false;
	}

	// Create the thread
	mObjectHandle = Platform::CreateThread(ThreadProc, priority, this, suspend, &mThreadID);
	if (mObjectHandle == _null) {
		Close();
		return _false;
	}

	// Wait for thread to finish making itself
	if (suspend == _false)
		mReadyEvent.Wait();

	return _true;
}

_void Thread::Close() {
	if (mObjectHandle == _null)
		return;

	// We are releasing now
	mIsReleasing = _true;

	// Wait for the thread exit
	if (Platform::IsThreadAlive(mObjectHandle))
		mExitEvent.Wait();

	// Close the thread kernel object
	Platform::CloseThread(mObjectHandle);
	mObjectHandle = _null;

	// Close the thread events
	mReadyEvent.Close();
	mExitEvent.Close();

	// Releasing done
	mIsReleasing = _false;
}

_ubool Thread::Suspend() {
	return Platform::SuspendThread(mObjectHandle);
}

_ubool Thread::Resume() {
	return Platform::ResumeThread(mObjectHandle);
}

_ubool Thread::Initialize() {
	sThreadLock = new Lock();
	sThreads = new ThreadPtrArray();

	return _true;
}

_void Thread::Finalize() {
	EGE_DELETE(sThreadLock);
	EGE_DELETE(sThreads);
}

_dword Thread::GetThreadsNumber() {
	LockOwner lock_owner(*sThreadLock);

	return sThreads->Number();
}

_thread_id Thread::GetThreadInfoByIndex(_dword index, WString* name, _float* cpu_usage) {
	LockOwner lock_owner(*sThreadLock);

	if (index >= sThreads->Number())
		return 0;

	Thread* thread = (*sThreads)[index];
	EGE_ASSERT(thread != _null);

	if (name != _null)
		*name = thread->mThreadName;

	if (cpu_usage != _null)
		*cpu_usage = thread->GetCPUUsage(Platform::GetCurrentTickCount());

	return thread->mThreadID;
}
