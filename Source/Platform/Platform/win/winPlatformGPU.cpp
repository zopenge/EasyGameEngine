//! @file     winPlatformGPU.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform GPU Implementation
//----------------------------------------------------------------------------

const _charw* Platform::GetGPUFamilyName() {
	static DISPLAY_DEVICEW device = {0};

	// Get the primary device name
	if (device.cb == 0) {
		device.cb = sizeof(device);
		if (!::EnumDisplayDevicesW(_null, 1, &device, EDD_GET_DEVICE_INTERFACE_NAME))
			return L"";

		// Make sure it's active
		if (EGE_BOOLEAN(device.StateFlags & DISPLAY_DEVICE_ACTIVE) == _false)
			return L"";
	}

	return device.DeviceString;
}