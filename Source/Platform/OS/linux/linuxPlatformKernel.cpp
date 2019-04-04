#include "EGEPlatform.h"

_PLATFORM_TYPE Platform::GetPlatformType() {
	return _PLATFORM_TYPE_ANDROID;
}

const _charw* Platform::GetPlatformName() {
	return L"android";
}

_ubool Platform::GetPlatformVersion(_dword& major, _dword& minor) {
	return _false;
}

_ubool Platform::IsEmbeddedSystem() {
	return _true;
}

_handle Platform::InitializeCriticalSection() {
	return anyPlatformKernel::InitializeCriticalSection();
}

_void Platform::DeleteCriticalSection(_handle object) {
	return anyPlatformKernel::DeleteCriticalSection(object);
}

_void Platform::EnterCriticalSection(_handle object) {
	anyPlatformKernel::EnterCriticalSection(object);
}

_void Platform::LeaveCriticalSection(_handle object) {
	anyPlatformKernel::LeaveCriticalSection(object);
}

_handle Platform::CloneEvent(_handle object) {
	return anyPlatformKernel::CloneEvent(object);
}

_void Platform::CloseHandle(_handle handle) {
	anyPlatformKernel::CloseHandle(handle);
}

_ubool Platform::WaitForSingleObject(_handle object, _dword milliseconds) {
	return anyPlatformKernel::WaitForSingleObject(object, milliseconds);
}

_handle Platform::CreateEvent(_ubool manualreset, _ubool initialstate) {
	return anyPlatformKernel::CreateEvent(manualreset, initialstate);
}

_ubool Platform::SetEvent(_handle object) {
	return anyPlatformKernel::SetEvent(object);
}

_ubool Platform::ResetEvent(_handle object) {
	return anyPlatformKernel::ResetEvent(object);
}

_handle Platform::CreateAutoReleasePool() {
	return _null;
}

_void Platform::ReleaseAutoReleasePool(_handle pool) {
}

_void Platform::Sleep(_dword milliseconds) {
	anyPlatformKernel::Sleep(milliseconds);
}