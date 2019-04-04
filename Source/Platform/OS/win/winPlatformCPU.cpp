#include "EGEPlatform.h"

//! Subtract times.
ULONGLONG SubtractTimes(const FILETIME& t1, const FILETIME& t2) {
	LARGE_INTEGER a;
	a.LowPart = t1.dwLowDateTime;
	a.HighPart = t1.dwHighDateTime;

	LARGE_INTEGER b;
	b.LowPart = t2.dwLowDateTime;
	b.HighPart = t2.dwHighDateTime;

	return a.QuadPart - b.QuadPart;
}

//! Check whether we have enough time to get the cpu usage.
bool EnoughTimePassed(ULONGLONG last_tickcount) {
	const int minElapsedMS = 250; //milliseconds

	ULONGLONG dwCurrentTickCount = GetTickCount64();
	return (dwCurrentTickCount - last_tickcount) > minElapsedMS;
}

const CPUData& Platform::GetCPUData() {
	if (gCPUData.mNumber) {
		return gCPUData;
	}

	SYSTEM_INFO systeminfo;
	::GetSystemInfo(&systeminfo);

	gCPUData.mNumber = systeminfo.dwNumberOfProcessors;

	switch (systeminfo.wProcessorArchitecture) {
		case PROCESSOR_ARCHITECTURE_UNKNOWN:
			gCPUData.mFamilyName = L"Unknown";
			break;

		case PROCESSOR_ARCHITECTURE_ARM:
			gCPUData.mFamilyName = L"ARM";
			break;

		case PROCESSOR_ARCHITECTURE_MIPS:
			gCPUData.mFamilyName = L"MIPS";
			break;

		default:
			gCPUData.mFamilyName = L"X86";
			break;
	}

	return gCPUData;
}

_float Platform::GetCurrentCPUUsage() {
	static _float sCpuUsage = 0.0f;
	static ULONGLONG sLastTickcount = 0;

	// System total times
	static FILETIME sPrevSysKernel;
	static FILETIME sPrevSysUser;
	// Process times
	static FILETIME sPrevProcKernel;
	static FILETIME sPrevProcUser;

	// If this is called too often, the measurement itself will greatly affect the results.
	if (EnoughTimePassed(sLastTickcount) == _false)
		return sCpuUsage;

	// Get the system and process times
	FILETIME ftSysIdle, ftSysKernel, ftSysUser;
	FILETIME ftProcCreation, ftProcExit, ftProcKernel, ftProcUser;
	if (!GetSystemTimes(&ftSysIdle, &ftSysKernel, &ftSysUser) ||
	    !GetProcessTimes(GetCurrentProcess(), &ftProcCreation, &ftProcExit, &ftProcKernel, &ftProcUser)) {
		return sCpuUsage;
	}

	// Skip for the first time call
	if (sLastTickcount != 0) {
		// CPU usage is calculated by getting the total amount of time the system has operated since the last measurement (made up of kernel + user) and the total amount of time the process has run (kernel + user).
		ULONGLONG ftSysKernelDiff = SubtractTimes(ftSysKernel, sPrevSysKernel);
		ULONGLONG ftSysUserDiff = SubtractTimes(ftSysUser, sPrevSysUser);

		ULONGLONG ftProcKernelDiff = SubtractTimes(ftProcKernel, sPrevProcKernel);
		ULONGLONG ftProcUserDiff = SubtractTimes(ftProcUser, sPrevProcUser);

		ULONGLONG nTotalSys = ftSysKernelDiff + ftSysUserDiff;
		ULONGLONG nTotalProc = ftProcKernelDiff + ftProcUserDiff;

		if (nTotalSys > 0)
			sCpuUsage = (short)((100.0 * nTotalProc) / nTotalSys);
	}

	sPrevSysKernel = ftSysKernel;
	sPrevSysUser = ftSysUser;
	sPrevProcKernel = ftProcKernel;
	sPrevProcUser = ftProcUser;

	sLastTickcount = GetTickCount64();

	return sCpuUsage;
}