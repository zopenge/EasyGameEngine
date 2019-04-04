#include "EGEPlatform.h"

Pipe::Pipe() {
	mIsServerProcess = _false;
	mIsConnected = _false;

	mSize = 0;
	mTimeout = 0;
}

Pipe::~Pipe() {
	Disconnect();
}

WString Pipe::BuildPipeName(WStringPtr pipename) {
	_charw fixed_pipename[1024];
	return WString(Platform::FormatStringBuffer(fixed_pipename, 1024, L"\\\\.\\pipe\\%s", pipename.CStr()));
}

_ubool Pipe::CreateServer(WStringPtr pipename, _dword size, _dword timeout) {
	// Build the pipe name
	WString fixed_pipename = BuildPipeName(pipename);

	// Initialize basic info
	mName = pipename;
	mSize = size;
	mTimeout = timeout;

	// Create the named pipe
	mObjectHandle = Platform::CreateNamedPipe(fixed_pipename.CStr(), 32, size, size, timeout);
	if (mObjectHandle == _null)
		return _false;

	mIsServerProcess = _true;

	return _true;
}

_ubool Pipe::CreateClient(WStringPtr pipename, _dword timeout) {
	// Build the pipe name
	WString fixed_pipename = BuildPipeName(pipename);

	// Test connection
	if (Platform::WaitNamedPipe(fixed_pipename.CStr(), timeout) == _false)
		return _false;

	// Initialize basic info
	mName = pipename;
	mSize = 0;
	mTimeout = timeout;

	// Open named pipe connection
	mObjectHandle = Platform::OpenFile(fixed_pipename.CStr());
	if (mObjectHandle == _null)
		return _false;

	mIsServerProcess = _false;

	return _true;
}

_ubool Pipe::WaitConnection() {
	return mIsConnected = Platform::ConnectNamedPipe(mObjectHandle);
}

_ubool Pipe::IsConnected() const {
	return mIsConnected;
}

_void Pipe::Disconnect() {
	// Only for server
	if (mIsServerProcess)
		Platform::DisconnectNamedPipe(mObjectHandle);

	mIsConnected = _false;
}

_ubool Pipe::TestConnection(WStringPtr pipename, _dword timeout) {
	// Build the pipe name
	WString fixed_pipename = BuildPipeName(pipename);

	return Platform::WaitNamedPipe(fixed_pipename.CStr(), timeout);
}

_dword Pipe::GetTotalAvailableSize() const {
	_dword total_bytes_avail = 0;
	if (Platform::PeekNamedPipe(mObjectHandle, _null, 0, _null, &total_bytes_avail, _null) == _false)
		return -1;

	return total_bytes_avail;
}

_ubool Pipe::Read(_void* buffer, _dword size, _dword* bytesread) {
	return Platform::ReadFile(mObjectHandle, buffer, size, bytesread);
}

_ubool Pipe::Write(const _void* buffer, _dword size, _dword* byteswritten) {
	return Platform::WriteFile(mObjectHandle, buffer, size, byteswritten);
}