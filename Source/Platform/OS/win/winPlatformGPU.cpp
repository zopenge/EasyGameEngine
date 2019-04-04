#include "EGEPlatform.h"

const GPUData& Platform::GetGPUData() {
	if (gGPUData.mFamilyName) {
		return gGPUData;
	}

	static DISPLAY_DEVICEW device = {0};

	// Get the primary device name
	device.cb = sizeof(device);
	if (::EnumDisplayDevicesW(_null, 1, &device, EDD_GET_DEVICE_INTERFACE_NAME)) {
		// Make sure it's active
		if (device.StateFlags & DISPLAY_DEVICE_ACTIVE)
			gGPUData.mFamilyName = device.DeviceString;
	}

	return gGPUData;
}