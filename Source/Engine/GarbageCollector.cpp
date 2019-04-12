//! @file     GarbageCollector.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// GarbageCollector Implementation
//----------------------------------------------------------------------------

GarbageCollector::GarbageCollector() {
	mIsReleasing = _false;

	mIsEnable = _false;

	mCleanupMaxTime = -1;
}

GarbageCollector::~GarbageCollector() {
	mIsReleasing = _true;

	// Release all GC objects
	Cleanup(-1);
}

_void GarbageCollector::Tick(_dword limited_elapse, _dword elapse) {
	if (mIsEnable == _false)
		return;

	Cleanup(mCleanupMaxTime);
}

_dword GarbageCollector::Release() {
	// We overload this interface to ignore the GC collect self
	if (mIsReleasing)
		return 0;

	// We won't let the GC to manage it
	if (INTERLOCKED_DEC(mRefCount) == 0) {
		delete this;
		return 0;
	} else {
		return mRefCount;
	}
}

_void GarbageCollector::Enable(_ubool enable) {
	mIsEnable = enable;
}

_ubool GarbageCollector::IsEnabled() const {
	return mIsEnable;
}

_void GarbageCollector::Cleanup(_dword timeout) {
	// Get the max time
	_dword tick = Platform::GetCurrentTickCount();
	_dword max_time = timeout == -1 ? -1 : tick + timeout;

	// The total deleted objects number
	_dword del_numbers = 0;

	// Delete all objects without GC
	IObject* gc_object = _null;
	while (mGCObjects.Dequeue(gc_object)) {
		// Delete it
		gc_object->DeleteThis();

		// Increase the delete object numbers
		del_numbers++;

		// Check whether it's time out by limited cleanup time
		if (max_time != -1 && Platform::GetCurrentTickCount() > max_time)
			break;
	}

#if defined(_DEBUG)
	if (del_numbers != 0) {
		_dword elapsed_time = Platform::GetCurrentTickCount() - tick;

		WLOG_DEBUG_2(L"GC: Released (%d) objects, elapsed time: %d ms", del_numbers, elapsed_time);
	}
#endif
}

_void GarbageCollector::SetCleanupMaxTime(_dword time) {
	mCleanupMaxTime = time;
}

_void GarbageCollector::AddObject(IObject* object) {
	// Uninitialize before delete
	object->Uninitialize();

	// If we are in the self releasing mode then delete it immediately
	if (mIsReleasing || mIsEnable == _false) {
		object->DeleteThis();
	} else {
		// Add to GC objects array and wait to delete
		mLock.Enter();
		mGCObjects.Enqueue(object);
		mLock.Leave();
	}
}
