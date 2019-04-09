#include "EGEPlatform.h"

//!	The base referenced object
struct BaseRefObject {
	_dword mRefCount;

	BaseRefObject()
	    : mRefCount(1) {
	}
	virtual ~BaseRefObject() {
		EGE_ASSERT(mRefCount == 1);
	}

	virtual _dword AddRef() {
		return INTERLOCKED_INC(mRefCount);
	}
	virtual _dword Release() {
		if (INTERLOCKED_DEC(mRefCount) == 0) {
			delete this;
			return 0;
		}

		return mRefCount;
	}
};

//!	The signal object
struct SignalObject : public BaseRefObject {
	pthread_cond_t mCondition;
	pthread_mutex_t mMutex;

	_void Lock() {
		::pthread_mutex_lock(&mMutex);
	}
	_void Unlock() {
		::pthread_mutex_unlock(&mMutex);
	}
	_void Wait(_dword milliseconds) {
		if (milliseconds == -1) {
			::pthread_cond_wait(&mCondition, &mMutex);
		} else {
			::timespec time;
			time.tv_sec = ::time(0) + milliseconds / 1000;
			time.tv_nsec = (milliseconds % 1000) * 1000;

			::pthread_cond_timedwait(&mCondition, &mMutex, &time);
		}
	}
	_void Signal() {
		::pthread_cond_signal(&mCondition);
	}

	SignalObject() {
		::pthread_cond_init(&mCondition, 0);
		::pthread_mutex_init(&mMutex, 0);
	}
	virtual ~SignalObject() {
		::pthread_cond_destroy(&mCondition);
		::pthread_mutex_destroy(&mMutex);
	}
};

//!	The base kernel object
struct anyPlatformKernelObject {
	anyPlatformKernelObject() {
	}
	virtual ~anyPlatformKernelObject() {
	}
};

//!	The event kernel condition
struct anyPlatformKernelCondition : public anyPlatformKernelObject {
	_ubool mIsManualReset;
	_ubool mState;

	SignalObject* mSignalObject;

	_void Lock() {
		mSignalObject->Lock();
	}
	_void Unlock() {
		mSignalObject->Unlock();
	}
	_void Wait(_dword milliseconds) {
		mSignalObject->Wait(milliseconds);
	}
	_void Signal() {
		mSignalObject->Signal();
	}

	anyPlatformKernelCondition(_ubool manualreset, _ubool initialstate) {
		mIsManualReset = manualreset;
		mState = initialstate;

		mSignalObject = new SignalObject();
	}
	anyPlatformKernelCondition(anyPlatformKernelCondition* condition) {
		mIsManualReset = condition->mIsManualReset;
		mState = condition->mState;

		mSignalObject = condition->mSignalObject;
		mSignalObject->AddRef();
	}
	virtual ~anyPlatformKernelCondition() {
		mSignalObject->Release();
	}
};

_handle anyPlatformKernel::InitializeCriticalSection() {
	pthread_mutex_t* mutex = (pthread_mutex_t*)Platform::HeapAlloc(sizeof(pthread_mutex_t));
	if (mutex == _null)
		return _null;

	::pthread_mutex_init(mutex, 0);

	return mutex;
}

_void anyPlatformKernel::DeleteCriticalSection(_handle object) {
	pthread_mutex_t* mutex = (pthread_mutex_t*)object;
	if (mutex == _null)
		return;

	::pthread_mutex_destroy(mutex);

	Platform::HeapFree(mutex);
}

_void anyPlatformKernel::EnterCriticalSection(_handle object) {
	pthread_mutex_t* mutex = (pthread_mutex_t*)object;
	if (mutex == _null)
		return;

	::pthread_mutex_lock(mutex);
}

_void anyPlatformKernel::LeaveCriticalSection(_handle object) {
	pthread_mutex_t* mutex = (pthread_mutex_t*)object;
	if (mutex == _null)
		return;

	::pthread_mutex_unlock(mutex);
}

_void anyPlatformKernel::CloseHandle(_handle handle) {
	anyPlatformKernelObject* object = (anyPlatformKernelObject*)handle;
	if (object == _null)
		return;

	delete object;
}

_ubool anyPlatformKernel::WaitForSingleObject(_handle object, _dword milliseconds) {
	anyPlatformKernelCondition* section = (anyPlatformKernelCondition*)object;
	if (section == _null)
		return _false;

	section->Lock();
	{
		// Skip for triggered status
		if (section->mState == _false)
			section->Wait(milliseconds);

		// If it's manual mode then we change it to triggered status
		if (section->mIsManualReset)
			section->mState = _true;
		else
			section->mState = _false;
	}
	section->Unlock();

	return _true;
}

_handle anyPlatformKernel::CloneEvent(_handle object) {
	anyPlatformKernelCondition* section = (anyPlatformKernelCondition*)object;
	if (section == _null)
		return _null;

	return new anyPlatformKernelCondition(section);
}

_handle anyPlatformKernel::CreateEvent(_ubool manualreset, _ubool initialstate) {
	return new anyPlatformKernelCondition(manualreset, initialstate);
}

_ubool anyPlatformKernel::SetEvent(_handle object) {
	anyPlatformKernelCondition* section = (anyPlatformKernelCondition*)object;
	if (section == _null)
		return _false;

	section->Lock();
	{
		section->mState = _true;
		section->Signal();
	}
	section->Unlock();

	return _true;
}

_ubool anyPlatformKernel::ResetEvent(_handle object) {
	anyPlatformKernelCondition* section = (anyPlatformKernelCondition*)object;
	if (section == _null)
		return _false;

	// Clear the triggered status
	section->Lock();
	{
		section->mState = _false;
	}
	section->Unlock();

	return _true;
}

_void anyPlatformKernel::Sleep(_dword milliseconds) {
#if defined(_PLATFORM_WINDOWS_)
	::SleepEx(milliseconds, _true);
#else
	// milliseconds -> microseconds
	::usleep(milliseconds * 1000);
#endif
}
