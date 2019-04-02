#include "EGEPlatform.h"

static _dword TranslateFileSeekFlag(SeekFlag flag) {
	switch (flag) {
		case SeekFlag::Begin:
			return FILE_BEGIN;
		case SeekFlag::Current:
			return FILE_CURRENT;
		case SeekFlag::End:
			return FILE_END;
		default:
			return 0;
	}
}

static _void CopyFileFinderData(FileFinderData& finderdata, const WIN32_FIND_DATAW& win32_find_data) {
	// Feedback find data
	finderdata.mFileAttributes = win32_find_data.dwFileAttributes;
	finderdata.mCreationTime = *(const FileTime*)&win32_find_data.ftCreationTime;
	finderdata.mLastAccessTime = *(const FileTime*)&win32_find_data.ftLastAccessTime;
	finderdata.mLastWriteTime = *(const FileTime*)&win32_find_data.ftLastWriteTime;
	finderdata.mFileSize = (_qword(win32_find_data.nFileSizeHigh) << 32) | win32_find_data.nFileSizeLow;
	SafeCopyString(finderdata.mFileName, win32_find_data.cFileName);
	SafeCopyString(finderdata.mAlternateFileName, win32_find_data.cAlternateFileName);
}

_handle Platform::OpenDir(const _charw* directory) {
	if (directory == _null)
		return _null;

	// The find data on Win32 platform
	WIN32_FIND_DATAW win32_find_data;

	// Build the directory path
	_charw path[1024];
	Platform::FormatStringBuffer(path, 1024, L"%s/*.*", directory);

	// Open the directory
	_handle handle = ::FindFirstFileW(path, &win32_find_data);
	if (handle == INVALID_HANDLE_VALUE)
		return _null;

	// Skip for the '.' and '..' files
	do {
		if (win32_find_data.cFileName[0] == '.' && win32_find_data.cFileName[1] == '.' && win32_find_data.cFileName[2] == 0)
			break;
	} while (::FindNextFileW(handle, &win32_find_data));

	return handle;
}

_void Platform::CloseDir(_handle handle) {
	::FindClose(handle);
}

_ubool Platform::ReadDir(_handle handle, FileFinderData& finderdata) {
	WIN32_FIND_DATAW win32_find_data;
	if (!::FindNextFileW(handle, &win32_find_data))
		return _false;

	// Copy file find data
	CopyFileFinderData(finderdata, win32_find_data);

	return _true;
}

_ubool Platform::GetFileAttributes(const _charw* filename, _dword& attributes) {
	if (filename == _null)
		return _false;

	attributes = ::GetFileAttributesW(filename);
	if (attributes == -1)
		return _false;

	return _true;
}

_ubool Platform::SetFileAttributes(const _charw* filename, _dword attributes) {
	if (filename == _null)
		return _false;

	return !!::SetFileAttributesW(filename, attributes);
}

_handle Platform::CreateFile(const _charw* filename) {
	if (filename == _null)
		return _null;

	// Create or open file
	_handle handle = ::CreateFileW(filename, 0, 0, _null, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, _null);
	if (handle == INVALID_HANDLE_VALUE)
		return _null;

	// Update IO performance info
	sPerformanceData.mFileOpenCount++;

	return handle;
}

_handle Platform::OpenFile(const _charw* filename) {
	if (filename == _null)
		return _null;

	// Create or open file
	_handle handle = ::CreateFileW(filename, 0, 0, _null, OPEN_EXISTING, 0, _null);
	if (handle == INVALID_HANDLE_VALUE)
		return _null;

	// Update IO performance info
	sPerformanceData.mFileOpenCount++;

	return handle;
}

_void Platform::CloseFile(_handle handle) {
	if (handle != _null)
		::CloseHandle(handle);
}

_ubool Platform::ReadFile(_handle handle, _void* buffer, _dword size, _dword* bytesread) {
	if (handle == _null || buffer == _null || size == 0)
		return _false;

	DWORD bytes = 0;
	if (::ReadFile(handle, buffer, size, &bytes, _null) == 0)
		return _false;

	// If doesn't need bytes read, and the bytes read is less than request, then return false.
	if (bytesread == _null && bytes < size)
		return _false;

	if (bytesread != _null)
		*bytesread = bytes;

	// Update IO performance info
	sPerformanceData.mFileReadCount++;
	sPerformanceData.mFileReadBytes += bytes;

	return _true;
}

_ubool Platform::WriteFile(_handle handle, const _void* buffer, _dword size, _dword* byteswritten) {
	if (handle == _null || buffer == _null || size == 0)
		return _false;

	DWORD bytes = 0;
	if (::WriteFile(handle, buffer, size, &bytes, _null) == 0)
		return _false;

	// If doesn't need bytes written, and the bytes written is less than request, then return false.
	if (byteswritten == _null && bytes < size)
		return _false;

	if (byteswritten != _null)
		*byteswritten = bytes;

	// Update IO performance info
	sPerformanceData.mFileWriteCount++;
	sPerformanceData.mFileWriteBytes += bytes;

	return _true;
}

_ubool Platform::FlushFileBuffers(_handle handle) {
	if (handle == _null)
		return _false;

	return ::FlushFileBuffers(handle) != 0;
}

_dword Platform::SeekFilePointer(_handle handle, SeekFlag flag, _int distance) {
	if (handle == _null)
		return -1;

	return ::SetFilePointer(handle, distance, _null, TranslateFileSeekFlag(flag));
}

_dword Platform::GetFileSize(_handle handle) {
	if (handle == _null)
		return 0;

	return ::GetFileSize(handle, _null);
}

_ubool Platform::SetEndOfFile(_handle handle) {
	if (handle == _null)
		return _false;

	return ::SetEndOfFile(handle) != 0;
}

_ubool Platform::GetFileTime(_handle handle, FileTime* creation, FileTime* lastaccess, FileTime* lastwrite) {
	if (handle == _null)
		return _false;

	return !!::GetFileTime(handle, (::FILETIME*)creation, (::FILETIME*)lastaccess, (::FILETIME*)lastwrite);
}

_ubool Platform::SetFileTime(_handle handle, const FileTime* creation, const FileTime* lastaccess, const FileTime* lastwrite) {
	if (handle == _null)
		return _false;

	return !!::SetFileTime(handle, (const ::FILETIME*)creation, (const ::FILETIME*)lastaccess, (const ::FILETIME*)lastwrite);
}

_ubool Platform::DeleteFile(const _charw* filename) {
	if (filename == _null)
		return _false;

	return !!::DeleteFileW(filename);
}

_ubool Platform::CopyFile(const _charw* desfilename, const _charw* srcfilename) {
	if (desfilename == _null || srcfilename == _null)
		return _false;

	return !!::CopyFileW(srcfilename, desfilename, _false);
}

_ubool Platform::MoveFile(const _charw* desfilename, const _charw* srcfilename) {
	if (desfilename == _null || srcfilename == _null)
		return _false;

	return !!::MoveFileExW(srcfilename, desfilename, MOVEFILE_REPLACE_EXISTING);
}

_ubool Platform::GetAbsoluteDirectory(const _charw* path, _charw* abs_path, _dword abs_path_length) {
	if (_wfullpath(abs_path, path, abs_path_length) == _null)
		return _false;

	return _true;
}

_ubool Platform::GetCurrentDirectory(_charw* path, _dword length) {
	if (path == _null || length == 0)
		return _false;

	return ::GetCurrentDirectoryW(length, (LPWSTR)path) != 0;
}

_ubool Platform::SetCurrentDirectory(const _charw* path) {
	if (path == _null)
		return _false;

	return ::SetCurrentDirectoryW(path) != 0;
}

_ubool Platform::CreateDirectory(const _charw* path) {
	if (path == _null)
		return _false;

	// Create directory
	if (::CreateDirectoryW(path, _null) == 0) {
		// Skip for the existing error
		if (::GetLastError() != ERROR_ALREADY_EXISTS)
			return _false;
	}

	return _true;
}

_ubool Platform::RemoveDirectory(const _charw* path) {
	if (path == _null)
		return _false;

	return !!::RemoveDirectoryW(path);
}

_handle Platform::CreateFileMapping(_handle file, _dword size) {
	return ::CreateFileMapping(file, _null, PAGE_READWRITE, 0, size, _null);
}

_void* Platform::MapViewOfFile(_handle handle) {
	return ::MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
}

_void Platform::UnmapViewOfFile(_void* pointer) {
	::UnmapViewOfFile(pointer);
}

_ubool Platform::GetInternalPathInDomains(_charw* path, _dword length) {
	if (path == _null || length == 0)
		return _false;

	Platform::CopyString(path, L"./Internal", length);

	return _true;
}

_ubool Platform::GetExternalPathInDomains(_charw* path, _dword length) {
	if (path == _null || length == 0)
		return _false;

	Platform::CopyString(path, L"./External", length);

	return _true;
}

_ubool Platform::GetDocumentPathInDomains(_charw* path, _dword length) {
	if (path == _null || length == 0)
		return _false;

	Platform::CopyString(path, L"./Document", length);

	return _true;
}

_ubool Platform::GetDiskFreeSpace(const _charw* directory, _qword* freebytes, _qword* totalbytes) {
	return !!::GetDiskFreeSpaceExW(directory, (ULARGE_INTEGER*)freebytes, (ULARGE_INTEGER*)totalbytes, _null);
}

const PerformanceData& Platform::GetPerformanceData() {
	return sPerformanceData;
}
