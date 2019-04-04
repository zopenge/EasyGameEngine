#include "EGEPlatform.h"

_ubool EventObject::Create(_ubool manualreset, _ubool initialstate) {
	KernelObject::Close();

	mObjectHandle = Platform::CreateEvent(manualreset, initialstate);
	if (mObjectHandle == _null)
		return _false;

	return _true;
}

_ubool EventObject::Wait(_dword milliseconds) {
	return Platform::WaitForSingleObject(mObjectHandle, milliseconds);
}

_ubool EventObject::IsSignaled() const {
	return Platform::WaitForSingleObject(mObjectHandle, 0);
}

_ubool EventObject::Set() {
	return Platform::SetEvent(mObjectHandle);
}

_ubool EventObject::Reset() {
	return Platform::ResetEvent(mObjectHandle);
}

EventObject* EventObject::Clone() const {
	EventObject* event = new EventObject();
	event->mObjectHandle = Platform::CloneEvent(mObjectHandle);

	return event;
}