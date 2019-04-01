//! @file     Thread.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Thread
//----------------------------------------------------------------------------

//! This class represents a lite thread in a process
class Thread {
protected:
	typedef Array<Thread*> ThreadPtrArray;

protected:
	//! The Params
	QwordParams2 mParams;

	//! True indicates it's releasing
	_ubool mIsReleasing;

	//! The thread handle.
	_handle mObjectHandle;
	//! Thread ID
	_thread_id mThreadID;

	//! Thread name
	WString mThreadName;

	//! The last thread time of CPU usage tracking
	_qword mLastThreadTime;
	//! The last sample time of CPU usage tracking
	_qword mLastSampleTime;
	//! The last sample delta time of CPU usage tracking
	_qword mLastSampleDelta;

	//! Thread ready event
	EventObject mReadyEvent;
	//! Thread exit event
	EventObject mExitEvent;

protected:
	//! The thread lock to make sure that we access threads info safely
	static Lock* sThreadLock;
	//! The threads
	static ThreadPtrArray* sThreads;

protected:
	//! The thread work function.
	//! @param parameter  The user defined parameter.
	//! @return The exit code of the thread.
	static _thread_ret ThreadProc(_void* parameter);

protected:
	//! When thread run function.
	//! @param Params  The user defined Params.
	//! @return The exit code of the thread.
	virtual _dword OnRunThread(const QwordParams2& Params) PURE;
	//! When thread close function.
	//! @param exitcode  The exit code of the thread.
	//! @param Params  The user defined Params.
	//! @return none.
	virtual _void OnCloseThread(_dword exitcode, const QwordParams2& Params) PURE;

public:
	Thread();
	virtual ~Thread();

public:
	//! Check whether it has exit or not.
	//! @param none.
	//! @return True indicates it has exit.
	_ubool HasExit() const;
	//! Check whether it's releasing or not.
	//! @param none.
	//! @return True indicates it's releasing now.
	_ubool IsReleasing() const;
	//! Get the thread ID.
	//! @param none.
	//! @return The thread ID.
	_thread_id GetThreadID() const;

	//! Set the thread name.
	//! @param name  The thread name.
	//! @return True indicates success, false indicates failure.
	_ubool SetThreadName(WStringPtr name);
	//! Get the thread name.
	//! @param none.
	//! @return The thread name.
	WStringPtr GetThreadName() const;

	//! Get the amount of CPU usage.
	//! @param timenow  The current time.
	//! @return The amount of CPU usage in [0.0 ~ 100.0].
	_float GetCPUUsage(_dword timenow);

	//! Create the thread.
	//! @param priority The priority (0~99).
	//! @param suspend  If it is true, thread is created in a suspended state and does not run until Resume is called.
	//! @param name  The thread name.
	//! @param Params The user defined Params.
	//! @return True indicates success, false indicates failure.
	_ubool Create(_dword priority, _ubool suspend, WStringPtr name, const QwordParams2& Params);
	//! Close the thread in a safe way.
	//! @param none.
	//! @return none.
	_void Close();
	//! Suspend the thread, ( suspend count is incremented ).
	//! @param none
	//! @return True indicates success, false indicates failure.
	_ubool Suspend();
	//! Decrements suspend count. When it is decremented to zero, the thread is resumed.
	//! @param none
	//! @return True indicates success, false indicates failure.
	_ubool Resume();

public:
	//! Initialize.
	//! @param none.
	//! @return True indicates success, false indicates failure.
	static _ubool Initialize();
	//! Finalize.
	//! @param none.
	//! @return none.
	static _void Finalize();

	//! Get the total threads number.
	//! @param none.
	//! @return The total threads number.
	static _dword GetThreadsNumber();
	//! Get the thread info by index.
	//! @param index  The index of threads.
	//! @param name  The thread name.
	//! @param cpu_usage The CPU usage.
	//! @return The thread ID.
	static _thread_id GetThreadInfoByIndex(_dword index, WString* name, _float* cpu_usage);
};

} // namespace EGE