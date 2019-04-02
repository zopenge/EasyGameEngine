//! @file     winPlatformKernel.cpp
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform-Kernel Implementation
//----------------------------------------------------------------------------

const OSData& Platform::GetOSData() {
	if (gOSData.mName) {
		return gOSData;
	}

	gOSData.mName = L"Windows";

	LPBYTE info;
	if (::NetWkstaGetInfo(_null, 100, &info) == NERR_Success) {
		const WKSTA_INFO_100* work_station_info = (const WKSTA_INFO_100*)info;
		gOSData.mMajor = work_station_info->wki100_ver_major;
		gOSData.mMinor = work_station_info->wki100_ver_minor;
		::NetApiBufferFree(info);
	}

	return gOSData;
}

_ubool Platform::IsEmbeddedSystem() {
	return _false;
}

_handle Platform::InitializeCriticalSection() {
	CRITICAL_SECTION* critical_section = (CRITICAL_SECTION*)Platform::GlobalAlloc(sizeof(CRITICAL_SECTION));
	if (critical_section == _null)
		return _null;

	::InitializeCriticalSection(critical_section);

	return critical_section;
}

_void Platform::DeleteCriticalSection(_handle object) {
	CRITICAL_SECTION* critical_section = (CRITICAL_SECTION*)object;
	if (critical_section == _null)
		return;

	::DeleteCriticalSection(critical_section);

	Platform::GlobalFree(object);
}

_void Platform::EnterCriticalSection(_handle object) {
	CRITICAL_SECTION* critical_section = (CRITICAL_SECTION*)object;
	if (critical_section == _null)
		return;

		// Make sure do not lock more than 2 times in the same thread
#ifdef _DEBUG
	if (critical_section->OwningThread != _null) {
		EGE_ASSERT((_dword)critical_section->OwningThread != Platform::GetCurrentThreadID());
	}
#endif

	::EnterCriticalSection(critical_section);
}

_void Platform::LeaveCriticalSection(_handle object) {
	CRITICAL_SECTION* critical_section = (CRITICAL_SECTION*)object;
	if (critical_section == _null)
		return;

	::LeaveCriticalSection(critical_section);
}

_void Platform::CloseHandle(_handle handle) {
	if (handle != _null && handle != INVALID_HANDLE_VALUE)
		::CloseHandle(handle);
}

_ubool Platform::WaitForSingleObject(_handle object, _dword milliseconds) {
	if (object == _null)
		return _false;

	return ::WaitForSingleObject(object, milliseconds) != WAIT_FAILED;
}

_handle Platform::CloneEvent(_handle object) {
	HANDLE out_event = _null;
	::DuplicateHandle(GetCurrentProcess(), GetCurrentProcess(), GetCurrentProcess(), &out_event, 0, _false, DUPLICATE_SAME_ACCESS);

	return out_event;
}

_handle Platform::CreateEvent(_ubool manualreset, _ubool initialstate) {
	return ::CreateEventW(_null, manualreset, initialstate, L"");
}

_ubool Platform::SetEvent(_handle object) {
	return !!(::SetEvent(object));
}

_ubool Platform::ResetEvent(_handle object) {
	return !!(::ResetEvent(object));
}

_handle Platform::CreateAutoReleasePool() {
	// Windows not support this pool, we just return a static variable as handle
	static _dword dummy_pool = 1;
	return (_handle)dummy_pool;
}

_void Platform::ReleaseAutoReleasePool(_handle pool) {
	// Do nothing with pool
}

_void Platform::Sleep(_dword milliseconds) {
	// Use SleepEx to make sure can be woken up
	::SleepEx(milliseconds, _true);
}