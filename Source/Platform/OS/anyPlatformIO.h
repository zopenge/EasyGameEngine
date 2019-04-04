#pragma once

namespace EGE {

/// <summary>
/// The any-platform IO.
/// </summary>
class anyPlatformIO {
public:
	static _handle OpenDir(const _charw* directory);
	static _void CloseDir(_handle handle);
	static _ubool ReadDir(_handle handle, FileFinderData& finderdata);
	static _ubool GetFileAttributes(const _charw* filename, _dword& attributes);
	static _ubool SetFileAttributes(const _charw* filename, _dword attributes);
	static _handle CreateFile(const _charw* filename);
	static _handle OpenFile(const _charw* filename);
	static _void CloseFile(_handle handle);
	static _ubool ReadFile(_handle handle, _void* buffer, _dword size, _dword* bytesread);
	static _ubool WriteFile(_handle handle, const _void* buffer, _dword size, _dword* byteswritten);
	static _ubool FlushFileBuffers(_handle handle);
	static _dword SeekFilePointer(_handle handle, SeekFlag flag, _int distance);
	static _dword GetFileSize(_handle handle);
	static _ubool SetEndOfFile(_handle handle);
	static _ubool GetFileTime(_handle handle, FileTime* creation, FileTime* lastaccess, FileTime* lastwrite);
	static _ubool SetFileTime(_handle handle, const FileTime* creation, const FileTime* lastaccess, const FileTime* lastwrite);
	static _ubool DeleteFile(const _charw* filename);
	static _ubool CopyFile(const _charw* desfilename, const _charw* srcfilename);
	static _ubool MoveFile(const _charw* desfilename, const _charw* srcfilename);
	static _ubool GetAbsoluteDirectory(const _charw* path, _charw* abs_path, _dword abs_path_length);
	static _ubool GetCurrentDirectory(_charw* path, _dword length);
	static _ubool SetCurrentDirectory(const _charw* path);
	static _ubool CreateDirectory(const _charw* path);
	static _ubool RemoveDirectory(const _charw* path);
};

} // namespace EGE