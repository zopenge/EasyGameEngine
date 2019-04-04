#include "EGEPlatform.h"

PersistenceThread::PersistenceThread() {
	mInterval = 100;

	mCurUpdatersNumber = 0;
	mMaxUpdatersNumber = 0;
	mUpdaters = _null;
}

PersistenceThread::~PersistenceThread() {
	Close();
}

_dword PersistenceThread::OnRunThread(const QwordParams2& parameters) {
	_dword index = 0;

	while (IsReleasing() == _false && mMaxUpdatersNumber != 0) {
		// nothing to do
		if (mCurUpdatersNumber == 0) {
			// Wait for thread wake event
			mWakeEvent.Wait();
			continue;
		}

		// Copy the update thread callback function
		UpdateFunc update_func = mUpdaters[index];
		if (update_func.IsValid()) {
			// Check whether we suspend it
			mWakeEvent.Wait();

			// Invoke the update thread callback function
			_ACTION action = (_ACTION)update_func.InvokeR();

			// Remote update callback function
			if (action == _ACTION_REMOVE) {
				mUpdaters[index].Clear();

				// If no-any thread callback functions in the queue then we should wait for the new update callback coming
				if (INTERLOCKED_DEC(mCurUpdatersNumber) == 0) {
					// Wait for thread wake event
					mWakeEvent.Reset();
					continue;
				}
			}

			// Sleep for a while
			if (mInterval != -1)
				Platform::Sleep(mInterval);
		}

		// Go to the next updater
		index = (index + 1) % mMaxUpdatersNumber;
	}

	// Exit the thread
	return EXIT_SUCCESS;
}

_void PersistenceThread::OnCloseThread(_dword exitcode, const QwordParams2& parameters) {
}

_dword PersistenceThread::GetInterval() const {
	return mInterval;
}

_ubool PersistenceThread::IsThreadBusy() const {
	return mCurUpdatersNumber != 0;
}

_ubool PersistenceThread::Create(_dword max_updaters_number, _dword priority, _ubool suspend, _dword interval, WStringPtr name) {
	if (max_updaters_number == 0)
		return _false;

	// Update info
	mInterval = interval;
	mCurUpdatersNumber = 0;
	mMaxUpdatersNumber = max_updaters_number;
	mUpdaters = new UpdateFunc[max_updaters_number];

	// Create the thread wake event
	if (mWakeEvent.Create(_true, _false) == _false)
		return _false;

	// Create the inner-thread object
	if (Thread::Create(priority, suspend, name, QwordParams2::cNull) == _false)
		return _false;

	return _true;
}

_void PersistenceThread::Close() {
	// Set the wake event to terminate thread
	mWakeEvent.Set();

	// Close inner-thread data
	Thread::Close();

	// Clear max updaters number
	mMaxUpdatersNumber = 0;

	// Delete updaters
	EGE_DELETE_ARRAY(mUpdaters);
}

_ubool PersistenceThread::Suspend() {
	mWakeEvent.Reset();

	return _true;
}

_ubool PersistenceThread::Resume() {
	mWakeEvent.Set();

	return _true;
}

_ubool PersistenceThread::AddUpdaterFunc(OnUpdateFunction func, const QwordParams2& parameters) {
	if (mCurUpdatersNumber >= mMaxUpdatersNumber)
		return _false;

	// Add the updater info
	for (_dword i = 0; i < mMaxUpdatersNumber; i++) {
		if (mUpdaters[i].IsNull()) {
			mUpdaters[i].Init(func, parameters);
			break;
		}
	}

	// Done
	INTERLOCKED_INC(mCurUpdatersNumber);

	// Wakeup the thread to perform the update function queue
	mWakeEvent.Set();

	return _true;
}

_void PersistenceThread::RemoveAllUpdaterFuncs() {
	mCurUpdatersNumber = 0;

	for (_dword i = 0; i < mMaxUpdatersNumber; i++)
		mUpdaters[i].Clear();
}
