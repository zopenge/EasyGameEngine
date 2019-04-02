//! @file     Pipe.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Pipe
//----------------------------------------------------------------------------

class Pipe : public KernelObject {
private:
	NO_COPY_OPERATIONS(Pipe);

private:
	//! True indicates it's server process
	_ubool mIsServerProcess;
	//! True indicates has connected
	_ubool mIsConnected;

	//! The pipe name.
	WString mName;
	//! The pipe size.
	_dword mSize;
	//! The pipe timeout in milliseconds.
	_dword mTimeout;

private:
	//! Build pipe name.
	static WString BuildPipeName(WStringPtr pipename);

public:
	Pipe();
	~Pipe();

public:
	//! Create the named pipe as server process.
	//! @param name The unique pipe name.
	//! @param size The number of bytes to reserve for the output and input buffer.
	//! @param timeout The default time-out value, in milliseconds.
	//! @return True indicates success false indicates failure.
	_ubool CreateServer(WStringPtr pipename, _dword size, _dword timeout);
	//! Create the named pipe as client process.
	//! @param name The unique pipe name.
	//! @param timeout The default time-out value, in milliseconds.
	//! @return True indicates success false indicates failure.
	_ubool CreateClient(WStringPtr pipename, _dword timeout);
	//! Wait for a client process to connect to an instance of a named pipe.
	//! @param none.
	//! @return True indicates success false indicates failure.
	_ubool WaitConnection();
	//! Check whether has connected or not.
	//! @param none.
	//! @return True indicates has connected.
	_ubool IsConnected() const;
	//! Disconnect for a client process.
	//! @param none.
	//! @return none.
	_void Disconnect();
	//! Test for a server process to connect to an instance of a named pipe.
	//! @param name The unique pipe name.
	//! @param timeout The default time-out value, in milliseconds.
	//! @return True indicates success false indicates failure.
	_ubool TestConnection(WStringPtr pipename, _dword timeout);

	//! Get the available buffer size in bytes.
	//! @param none.
	//! @return The total number of bytes available to be read from the pipe.
	_dword GetTotalAvailableSize() const;

	//! Read the buffer data from named pipe.
	//! @param buffer   Pointer to the buffer that receives the data read from the pipe.
	//! @param size   Number of bytes to be read from the pipe.
	//! @param bytesread  Pointer to the number of bytes read.
	//! @return True indicates success false indicates failure.
	_ubool Read(_void* buffer, _dword size, _dword* bytesread = _null);
	//! Write the buffer data into named pipe.
	//! @param buffer   Pointer to the buffer containing the data to write to the pipe.
	//! @param size   Number of bytes to write to the pipe.
	//! @param byteswritten Pointer to the number of bytes written.
	//! @return True indicates success false indicates failure.
	_ubool Write(const _void* buffer, _dword size, _dword* byteswritten = _null);
};

} // namespace EGE