//! @file     Timer.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Timer Implementation
//----------------------------------------------------------------------------

Timer::Timer() {
	mIsPaused = _false;

	mElapsedTime = 0;
	mIntervalTime = Math::cMaxDword;
}

Timer::~Timer() {
}

_void Timer::RegisterOverdueFunc(OnOverdue funcpointer, const QwordParams2& parameters) {
	mOverdueFunc.Init(funcpointer, parameters);
}

_void Timer::Init(_dword interval_time) {
	mIsPaused = _false;

	mElapsedTime = 0;
	mIntervalTime = interval_time;
}

_void Timer::Resume() {
	mIsPaused = _false;
}

_void Timer::Pause() {
	mIsPaused = _true;
}

_dword Timer::GetElapsedTime() const {
	return mElapsedTime;
}

_dword Timer::GetIntervalTime() const {
	return mIntervalTime;
}

_ubool Timer::IsPaused() const {
	return mIsPaused;
}

_ubool Timer::IsOverdue(_dword elapse, _ubool auto_pause) {
	if (mIsPaused)
		return _false;

	mElapsedTime += elapse;

	_ubool overdue = mElapsedTime >= mIntervalTime;
	if (overdue) {
		// Reset elapsed time
		if (auto_pause)
			mElapsedTime = 0;

		// Invoke the overdue callback function
		if (mOverdueFunc.IsValid())
			mOverdueFunc.Invoke();
	}

	return overdue;
}