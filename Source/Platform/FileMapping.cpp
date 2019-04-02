//! @file     FileMapping.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// FileMapping Implementation
//----------------------------------------------------------------------------

FileMapping::FileMapping()
    : mFileHandle(_null), mSize(0), mBuffer(_null) {
}

FileMapping::~FileMapping() {
	Close();
}

_ubool FileMapping::Initialize() {
	// Get file mapping size
	mSize = Platform::GetFileSize(mFileHandle);

	// Create file mapping
	mObjectHandle = Platform::CreateFileMapping(mFileHandle, mSize);
	if (mObjectHandle == _null)
		return _false;

	// Map whole file
	mBuffer = (_byte*)Platform::MapViewOfFile(mObjectHandle);
	if (mBuffer == _null)
		return _false;

	return _true;
}

_byte* FileMapping::GetBuffer() const {
	return mBuffer;
}

_dword FileMapping::GetSize() const {
	return mSize;
}

_ubool FileMapping::Create(WStringPtr filename) {
	Close();

	// Open the file
	mFileHandle = Platform::CreateFile(filename.CStr());
	if (mFileHandle == _null)
		return _false;

	// Initialize the file mapping
	return Initialize();
}

_void FileMapping::Close() {
	if (mBuffer != _null)
		Platform::UnmapViewOfFile(mBuffer);

	Platform::CloseHandle(mObjectHandle);
	Platform::CloseHandle(mFileHandle);

	mObjectHandle = _null;
	mFileHandle = _null;
	mBuffer = _null;
	mSize = 0;
}