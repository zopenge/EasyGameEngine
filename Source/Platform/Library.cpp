#include "EGEPlatform.h"

Library::Library() {
	mLibInMemory = _false;
	mModule = _null;
	mNTHeader = _null;
	mDllMainFunc = _null;
}

Library::~Library() {
	Free();
}

_ubool Library::Load(WStringPtr filename) {
	// Free the previous DLL module
	Free();

	// It's loaded from the file
	mLibInMemory = _false;

	// Load DLL module
	mModule = Platform::LoadLibrary(filename.CStr());
	if (mModule == _null)
		return _false;

	return _true;
}

_void* Library::GetFunction(WStringPtr functionname) const {
	_chara funcname_ansi[1024];
	Platform::Utf16ToAnsi(funcname_ansi, 1024, functionname.CStr());

	return GetFunction(funcname_ansi);
}

_ubool Library::IsLoaded() const {
	return mModule != _null;
}

WStringPtr Library::GetInternalName() const {
	return mInternalName.CStr();
}

WStringPtr Library::GetCopyright() const {
	return mCopyright.CStr();
}

const Version& Library::GetVersion() const {
	return mVersion;
}

AStringPtr Library::GetEmbeddedManifest() const {
	return mEmbeddedManifest.CStr();
}