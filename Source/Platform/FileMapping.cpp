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
	mObjectHandle = Platform::CreateFileMapping(mFileHandle, mSize, _FILE_OPERATION_READ);
	if (mObjectHandle == _null)
		return _false;

	// Map whole file
	mBuffer = (_byte*)Platform::MapViewOfFile(mObjectHandle, _FILE_OPERATION_READ);
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

_ubool FileMapping::Open(WStringPtr filename) {
	Close();

	// Open the file
	mFileHandle = Platform::OpenFile(filename.CStr(), _FILE_OPEN_EXISTING, _FILE_OPERATION_READ, _FILE_SHARE_READ | _FILE_SHARE_WRITE, _FILE_ATTRIBUTE_NORMAL);
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