#include "EGEPlatform.h"

FPSTimer::FPSTimer() {
	mInterval = _DEFAULT_INTERVAL_TIME;

	mFrameTickcount = 0;
	mTotalFrameTickcount = 0;

	mFrameNumber = 0;
	mTotalFrameNumber = 0;

	mFPS = 0.0f;
}

FPSTimer::~FPSTimer() {
}

_ubool FPSTimer::Tick(_dword elapse) {
	// Increase the frame number
	mFrameNumber++;
	mTotalFrameNumber++;

	// Update the total frame tickcount
	mTotalFrameTickcount += elapse;

	// Flush FPS
	_dword frame_elapse = mTotalFrameTickcount - mFrameTickcount;
	if (frame_elapse >= mInterval) {
		mFPS = EGE_RATIO(mFrameNumber * 1000.0f, frame_elapse);

		mFrameTickcount += frame_elapse;
		mFrameNumber = 0;

		return _true;
	}

	return _false;
}

_void FPSTimer::SetInterval(_dword time) {
	mInterval = Math::Max(1U, time);
}

_dword FPSTimer::GetInterval() const {
	return mInterval;
}

_float FPSTimer::GetFPS() const {
	return mFPS;
}

_float FPSTimer::GetAvgFPS() const {
	if (mTotalFrameTickcount == 0)
		return 0.0f;

	return EGE_RATIO(mTotalFrameNumber, mTotalFrameTickcount) * 1000.0f;
}
