#include "EGEPlatform.h"

KernelObject::KernelObject(_handle objecthandle)
    : mObjectHandle(objecthandle) {
}

KernelObject::~KernelObject() {
	Close();
}

_ubool KernelObject::IsValid() const {
	return mObjectHandle != _null;
}

_void KernelObject::Close() {
	Platform::CloseHandle(mObjectHandle);
	mObjectHandle = _null;
}