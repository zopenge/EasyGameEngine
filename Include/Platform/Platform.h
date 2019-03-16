//! @file     Platform.h
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Platform
//----------------------------------------------------------------------------

class Platform
{
//! Callback Functions Declaration
public:
 //! The socket connect break function.
 typedef _ubool (*OnIsBreakConnectingProc)( _dword elapse, _void* userdata );

 //! QueueUserAPC callback function.
 typedef _void (*OnAPCProc)( _void* );
 //! Thread start routine callback function.
 typedef _thread_ret (*OnThreadStartRoutine)( _void* );

 //! When enumerate resource callback function.
 //! @param type   The resource type.
 //! @param name   The resource name.
 //! @param parameter  An application-defined value passed to the callback function.
 //! @return True indicates success false indicates failure.
 typedef _ubool (*OnEnumResNameProc)( const _charw* type, const _charw* name, _void* parameter );

//! Kernel Functions
public:
 //! Initialize.
 //! @param none.
 //! @return True indicates success false indicates failure.
 static _ubool Initialize( );
 //! Finalize.
 //! @param none.
 //! @return none.
 static _void Finalize( );

 //! Get the platform type.
 //! @param none.
 //! @return The platform type.
 static _PLATFORM_TYPE GetPlatformType( );
 //! Get the platform name.
 //! @param none.
 //! @return The platform type.
 static const _charw* GetPlatformName( );
 //! Get the operation system version.
 //! @param major The major version.
 //! @param minor The minor version.
 //! @return True indicates success false indicates failure.
 static _ubool GetPlatformVersion( _dword& major, _dword& minor );

 //! Check whether it's embedded system or not.
 //! @param none.
 //! @return True indicates it's embedded system.
 static _ubool IsEmbeddedSystem( );

 //! Initializes a critical section object.
 //! @param none.
 //! @return The critical section object handle.
 static _handle InitializeCriticalSection( );
 //! Delete a critical section object.
 //! @param object   The critical section object handle.
 //! @return none.
 static _void DeleteCriticalSection( _handle object );
 //! Enter a critical section object.
 //! @param object   The critical section object handle.
 //! @return none.
 static _void EnterCriticalSection( _handle object );
 //! Leave a critical section object.
 //! @param object   The critical section object handle.
 //! @return none.
 static _void LeaveCriticalSection( _handle object );

 //! Close handle.
 //! @param handle   The handle to be closed.
 //! @return none.
 static _void CloseHandle( _handle handle );

 //! Waits until the specified object is in the signaled state or the time-out interval elapses.
 //! @param object   A handle to the object.
 //! @param milliseconds The time-out interval, in milliseconds.
 //! @return True if the object is signaled before time out, false otherwise.
 static _ubool WaitForSingleObject( _handle object, _dword milliseconds );
 //! Clone event object.
 //! @param object   A handle to the event object. 
 //! @return A handle to the event object. 
 static _handle CloneEvent( _handle object );
 //! Creates or opens a named or unnamed event object.
 //! @param manualreset  Whether the event object is manual-reset or auto-reset.
 //! @param initialstate The initial state of the event object, true means signaled.
 //! @return A handle to the event object. 
 static _handle CreateEvent( _ubool manualreset, _ubool initialstate );
 //! Sets the specified event object to the signaled state.
 //! @param object   A handle to the object.
 //! @return True indicates success false indicates failure.
 static _ubool SetEvent( _handle object );
 //! Sets the specified event object to the nonsignaled state.
 //! @param object   A handle to the object.
 //! @return True indicates success false indicates failure.
 static _ubool ResetEvent( _handle object );

 //! Create auto release pool.
 //! @param none.
 //! @return The auto release pool handle.
 static _handle CreateAutoReleasePool( );
 //! Release auto release pool.
 //! @param pool   The pool handle.
 //! @return none.
 static _void ReleaseAutoReleasePool( _handle pool );

 //! Sleep.
 //! @param milliseconds The milliseconds of sleep.
 //! @return none.
 static _void Sleep( _dword milliseconds );

//! Endian
public:
 //! Check whether it's little endian or not.
 //! @param none.
 //! @return True indicates it's little endian system.
 static _ubool IsLittleEndian( );
 //! Check whether it's big endian or not.
 //! @param none.
 //! @return True indicates it's big endian system.
 static _ubool IsBigEndian( );
 //! Get the endian type.
 //! @param none.
 //! @return The endian type.
 static _ENDIAN GetEndianType( );

//! CPU
public:
 //! Get CPU number.
 //! @param none.
 //! @return The CPU number.
 static _dword GetCPUNumber( );
 //! Get CPU family ID.
 //! @param none.
 //! @return The CPU family ID.
 static _CPU_FAMILY GetCPUFamilyID( );
 //! Get CPU family name.
 //! @param none.
 //! @return The CPU family name.
 static const _charw* GetCPUFamilyName( );
 //! Get CPU features.
 //! @param none.
 //! @return The CPU features, @see _CPU_FEATURES.
 static _dword GetCPUFeatures( );
 //! Get current CPU usage.
 //! @param none.
 //! @return The current CPU usage in [0.0, 100.0].
 static _float GetCurrentCPUUsage( );

//! GPU
public:
 //! Get GPU family name.
 //! @param none.
 //! @return The GPU family name.
 static const _charw* GetGPUFamilyName( );

//! Memory
public:
 //! Allocate ANSI string from heap.
 //! @param string   The ANSI string.
 //! @param heaphandle  The process heap handle, null indicates use the current process heap handle.
 //! @return The pointer to the allocated memory block.
 static _chara* HeapAllocStr( const _chara* string, _handle heaphandle = _null );
 //! Allocate UTF-16 string from heap.
 //! @param string   The UTF-16 string.
 //! @param heaphandle  The process heap handle, null indicates use the current process heap handle.
 //! @return The pointer to the allocated memory block.
 static _charw* HeapAllocStr( const _charw* string, _handle heaphandle = _null );
 //! Allocate memory from heap.
 //! @param size   The size of memory will be allocated in number of bytes.
 //! @param heaphandle  The process heap handle, null indicates use the current process heap handle.
 //! @return The pointer to the allocated memory block.
 static _void* HeapAlloc( _dword size, _handle heaphandle = _null );
 //! Reallocate memory from heap.
 //! @param pointer   The pointer to the memory block to be reallocated.
 //! @param size   The size of memory will be allocated in number of bytes.
 //! @param heaphandle  The process heap handle, null indicates use the current process heap handle.
 //! @return The pointer to the allocated memory block.
 static _void* HeapReAlloc( _void* pointer, _dword size, _handle heaphandle = _null );
 //! Frees a memory block allocated from heap.
 //! @param pointer   The pointer to the memory block to be freed.
 //! @param heaphandle  The process heap handle, null indicates use the current process heap handle.
 //! @return none.
 static _void HeapFree( _void* pointer, _handle heaphandle = _null );

 //! Allocate memory from global heap.
 //! @param size  The size of memory will be allocated in number of bytes.
 //! @return The pointer to the allocated memory block.
 static _void* GlobalAlloc( _dword size );
 //! Reallocate memory from global heap.
 //! @param pointer  The pointer to the memory block to be reallocated.
 //! @param size  The size of memory will be allocated in number of bytes.
 //! @return The pointer to the allocated memory block.
 static _void* GlobalReAlloc( _void* pointer, _dword size );
 //! Frees a memory block allocated from global heap.
 //! @param pointer  The pointer to the memory block to be freed.
 //! @return none.
 static _void GlobalFree( _void* pointer );

 //! Allocate memory from com global heap.
 //! @param size  The size of memory will be allocated in number of bytes.
 //! @return The pointer to the allocated memory block.
 static _void* ComAlloc( _dword size );
 //! Allocate ANSI string memory from com global heap.
 //! @param string  The string.
 //! @return The pointer to the allocated memory block.
 static _charw* ComAllocString( const _chara* string );
 //! Allocate UTF-16 string memory from com global heap.
 //! @param string  The string.
 //! @return The pointer to the allocated memory block.
 static _charw* ComAllocString( const _charw* string );
 //! Reallocate memory from com global heap.
 //! @param pointer  The pointer to the memory block to be reallocated.
 //! @param size  The size of memory will be allocated in number of bytes.
 //! @return The pointer to the allocated memory block.
 static _void* ComReAlloc( _void* pointer, _dword size );
 //! Frees a memory block allocated from com global heap.
 //! @param pointer  The pointer to the memory block to be freed.
 //! @return none.
 static _void ComFree( _void* pointer );

 //! Allocate UTF-16 string.
 //! @param string  The string.
 //! @return The pointer to the allocated memory block.
 static _charw* AllocString( const _charw* string );
 //! Free UTF-16 string.
 //! @param string  The string.
 //! @return The pointer to the allocated memory block.
 static _void FreeString( _charw* string );

 //! Reserves or commits a region of pages in the virtual address space of the calling process.
 //! @param size  The size of the region, in bytes.
 //! @return The pointer to the allocated memory block.
 static _void* VirtualAlloc( _dword size );
 //! Releases, decommits, or releases and decommits a region of pages within the virtual address space of the calling process.
 //! @param pointer  A pointer to the base address of the region of pages to be freed.
 //! @return none.
 static _void VirtualFree( _void* pointer );

//! IO
public:
 //! Open the directory.
 //! @param directory  The directory path.
 //! @return The file finder handle.
 static _handle OpenDir( const _charw* directory );
 //! Close the directory.
 //! @param handle   The file finder handle.
 //! @return none.
 static _void CloseDir( _handle handle );
 //! Read the directory to receive file or directory.
 //! @param directory  The directory path.
 //! @param finderdata  The element info.
 //! @return True indicates success false indicates failure ( no anymore elements ).
 static _ubool ReadDir( _handle handle, FileFinderData& finderdata );

 //! Get the file attributes.
 //! @param filename  The file path.
 //! @param attributes  The file attributes, @see _FILE_ATTRIBUTE.
 //! @return True indicates success false indicates failure.
 static _ubool GetFileAttributes( const _charw* filename, _dword& attributes );
 //! Set the file attributes.
 //! @param filename  The file path.
 //! @param attributes  The file attributes, @see _FILE_ATTRIBUTE.
 //! @return True indicates success false indicates failure.
 static _ubool SetFileAttributes( const _charw* filename, _dword attributes );

 //! Open (or create) a file.
 //! @param filename  The name of the file to open (or to create).
 //! @param createflag  Flag of how to create a file.
 //! @param operateflag  Flag of how to operate a file, @see _FILE_OPERATION_FLAG.
 //! @param shareflag  Flag of how to share the file with other processes, @see _FILE_SHARE_FLAG.
 //! @param attributes  The attributes of file.
 //! @return The file handle.
 static _handle OpenFile( const _charw* filename, _FILE_CREATE_FLAG createflag, _dword operateflag, _dword shareflag, _dword attributes );
 //! Close a file.
 //! @param handle   The file handle.
 //! @return none.
 static _void CloseFile( _handle handle );
 //! Read from a file.
 //! @param handle   The file handle.
 //! @param buffer   Pointer to the buffer that receives the data read from the file.
 //! @param size   Number of bytes to be read from the file.
 //! @param bytesread  Pointer to the number of bytes read.
 //! @return True indicates success, false indicates failure.
 static _ubool ReadFile( _handle handle, _void* buffer, _dword size, _dword* bytesread = _null );
 //! Write into a file.
 //! @param handle   The file handle.
 //! @param buffer   Pointer to the buffer containing the data to write to the file.
 //! @param size   Number of bytes to write to the file.
 //! @param byteswritten Pointer to the number of bytes written.
 //! @return True indicates success, false indicates failure.
 static _ubool WriteFile( _handle handle, const _void* buffer, _dword size, _dword* byteswritten = _null );
 //! Clears the buffers of the file and causes all buffered data to be written to the file.
 //! @param handle   The file handle.
 //! @return True indicates success, false indicates failure.
 static _ubool FlushFileBuffers( _handle handle );

 //! Move the file pointer from the begin of the file.
 //! @remarks A positive distance moves the file pointer forward in the file,
 //!    and a negative value moves the file pointer backward.
 //! @param handle   The file handle.
 //! @param flag   The seek flag.
 //! @param distance  Number of bytes to move.
 //! @return The current offset of file pointer from begin.
 static _dword SeekFilePointer( _handle handle, _SEEK flag, _int distance );

 //! Get the size, in bytes, of the file.
 //! @param handle   The file handle.
 //! @return Size of the file in bytes, or -1 indicates failure.
 static _dword GetFileSize( _handle handle );
 //! Sets the physical file size for the specified file to the current position of the file pointer.
 //! @param handle   The file handle.
 //! @return True indicates success, false indicates failure.
 static _ubool SetEndOfFile( _handle handle );

 //! Get times of file.
 //! @param handle   The file handle.
 //! @param creation  The date and time the file was created.
 //! @param lastaccess  The date and time the file was last accessed.
 //! @param lastwrite  The date and time the file was last written to.
 //! @return True indicates success, false indicates failure.
 static _ubool GetFileTime( _handle handle, FileTime* creation, FileTime* lastaccess, FileTime* lastwrite );
 //! Set times of file.
 //! @param handle   The file handle.
 //! @param creation  The date and time the file was created.
 //! @param lastaccess  The date and time the file was last accessed.
 //! @param lastwrite  The date and time the file was last written to.
 //! @return True indicates success, false indicates failure.
 static _ubool SetFileTime( _handle handle, const FileTime* creation, const FileTime* lastaccess, const FileTime* lastwrite );

 //! Delete the file.
 //! @param filename  The file path.
 //! @return True indicates success false indicates failure.
 static _ubool DeleteFile( const _charw* filename );
 //! Copies an existing file to a new file.
 //! @param desfilename  The name of the new file. 
 //! @param srcfilename  The name of an existing file.
 //! @return True indicates success false indicates failure.
 static _ubool CopyFile( const _charw* desfilename, const _charw* srcfilename );
 //! Moves an existing file or a directory, including its children.
 //! @param desfilename  The new name for the file or directory.
 //! @param srcfilename  The current name of the file or directory on the local computer.
 //! @return True indicates success false indicates failure.
 static _ubool MoveFile( const _charw* desfilename, const _charw* srcfilename );

 //! Set the absolute directory.
 //! @param path  The directory.
 //! @param abs_path The absolute directory.
 //! @param abs_path The absolute directory length.
 //! @return The absolute directory.
 static _ubool GetAbsoluteDirectory( const _charw* path, _charw* abs_path, _dword abs_path_length );

 //! Retrieves the current directory for the current process.
 //! @param path   The current directory string.
 //! @param length   The maximize directory string length.
 //! @return True indicates success false indicates failure.
 static _ubool GetCurrentDirectory( _charw* path, _dword length );
 //! Changes the current directory for the current process.
 //! @param path   The directory string.
 //! @return True indicates success false indicates failure.
 static _ubool SetCurrentDirectory( const _charw* path );
 //! Creates a new directory.
 //! @param path   The directory string.
 //! @return True indicates success false indicates failure.
 static _ubool CreateDirectory( const _charw* path );
 //! Deletes an existing empty directory.
 //! @param path   The directory string.
 //! @return True indicates success false indicates failure.
 static _ubool RemoveDirectory( const _charw* path );

 //! Creates or opens a named or unnamed file mapping object for a specified file.
 //! @param file   A handle to the file from which to create a file mapping object. 
 //! @param size   The maximum size of the file mapping object, 0 indicates is equal to the current size of the file.
 //! @param operationflag The file mapping object operation flag, @see _FILE_OPERATION_FLAG.
 //! @return The file mapping handle.
 static _handle CreateFileMapping( _handle file, _dword size, _dword operationflag );
 //! Maps a view of a file mapping into the address space of a calling process.
 //! @param handle   The file mapping handle.
 //! @param operationflag The file mapping object operation flag, @see _FILE_OPERATION_FLAG.
 //! @return The starting address of the mapped view.
 static _void* MapViewOfFile( _handle handle, _dword operationflag );
 //! Unmaps a mapped view of a file from the calling process's address space.
 //! @param pointer   A pointer to the base address of the mapped view of a file that is to be unmapped.
 //! @return none.
 static _void UnmapViewOfFile( _void* pointer );

 //! Get the internal path in domains.
 //! @param path   The internal path string.
 //! @param length   The maximize internal path string length.
 //! @return True indicates success false indicates failure.
 static _ubool GetInternalPathInDomains( _charw* path, _dword length );
 //! Get the external path in domains.
 //! @param path   The external path string.
 //! @param length   The maximize external path string length.
 //! @return True indicates success false indicates failure.
 static _ubool GetExternalPathInDomains( _charw* path, _dword length );
 //! Get the document path in domains.
 //! @param path   The document path string.
 //! @param length   The maximize document path string length.
 //! @return True indicates success false indicates failure.
 static _ubool GetDocumentPathInDomains( _charw* path, _dword length );

 //! Retrieves information about the amount of space that is available on a disk volume.
 //! @param directory  The disk path.
 //! @param freebytes  A pointer to a variable that receives the total number of free bytes on a disk that are available to the user.
 //! @param totalbytes  A pointer to a variable that receives the total number of bytes on a disk that are available to the user.
 //! @return True indicates success false indicates failure.
 static _ubool GetDiskFreeSpace( const _charw* directory, _qword* freebytes, _qword* totalbytes );

 //! Get the IO performance info.
 //! @param info   The IO performance info.
 //! @return none.
 static _void GetIOPerformanceInfo( IOPerformanceInfo& info );

//! Language
public:
 //! Get local language ID.
 //! @param none.
 //! @return The local language ID.
 static _LANG GetLocalLanguage( );

 //! Check whether character is vowel in Thai.
 //! @param code  The character code.
 //! @return True indicates it's vowel in Thai.
 static _ubool IsVowelInThai( _charw code );
 //! Check whether character is upper vowel in Thai.
 //! @param code  The character code.
 //! @return True indicates it's vowel in Thai.
 static _ubool IsUpperVowelInThai( _charw code );
 //! Check whether character is down vowel in Thai.
 //! @param code  The character code.
 //! @return True indicates it's vowel in Thai.
 static _ubool IsDownVowelInThai( _charw code );
 //! Check whether character is tone in Thai.
 //! @param code  The character code.
 //! @return True indicates it's tone in Thai.
 static _ubool IsToneInThai( _charw code );

//! Network
public:
 //! Get the IP address by URL address.
 //! @param url_address  The URL address.
 //! @return The IP address.
 static _dword GetURLIPAddress( const _chara* url_address );

 //! Get the IP address by URL address.
 //! @param url_address  The URL address.
 //! @return The IP address.
 static _DOMAIN_FAMILY_TYPE GetFamilyType( _dword port, const _chara* url_address );

 //! Create socket.
 //! @param families  The address families.
 //! @param type   The socket type.
 //! @param block_mode  True indicates it's block mode.
 //! @return The socket handle.
 static _socket CreateSocket( _DOMAIN_FAMILY_TYPE families, _SOCKET_TYPE type, _ubool block_mode );
 //! Create listened socket.
 //! @param families    The address families.
 //! @param type     The socket type.
 //! @param block_mode    True indicates it's block mode.
 //! @param port     The bind port.
 //! @param max_connection_number The max connections number.
 //! @return The socket handle.
 static _socket CreateListenedSocket( _DOMAIN_FAMILY_TYPE families, _SOCKET_TYPE type, _ubool block_mode, _dword port, _dword max_connection_number );
 //! Close socket.
 //! @param handle   The socket handle.
 //! @return none.
 static _void CloseSocket( _socket handle );
 //! Get the socket recv time out option.
 //! @param handle   The socket handle.
 //! @return The time in milliseconds.
 static _dword GetSocketRecvTimeOutOption( _socket handle );
 //! Set the socket recv time out option.
 //! @param handle   The socket handle.
 //! @param time   The time in milliseconds.
 //! @return True indicates success false indicates failure.
 static _ubool SetSocketRecvTimeOutOption( _socket handle, _dword time );
 //! Get the socket send time out option.
 //! @param handle   The socket handle.
 //! @return The time in milliseconds.
 static _dword GetSocketSendTimeOutOption( _socket handle );
 //! Set the socket send time out option.
 //! @param handle   The socket handle.
 //! @param time   The time in milliseconds.
 //! @return True indicates success false indicates failure.
 static _ubool SetSocketSendTimeOutOption( _socket handle, _dword time );
 //! Get the last socket error ID.
 //! @param handle   The socket handle.
 //! @return The error ID.
 static _dword GetLastSocketErrorID( _socket handle );
 //! Accept socket.
 //! @param handle   The listened socket handle.
 //! @return The socket what try to connect and be accepted.
 static _socket AcceptSocket( _socket handle );
 //! Connect socket.
 //! @param handle   The socket handle.
 //! @param remote_address The remote address.
 //! @param port   The port.
 //! @param func   The break connection function.
 //! @param userdata  The user data.
 //! @return True indicates success false indicates failure.
 static _ubool ConnectSocket( _socket handle, const _chara* remote_address, _dword port, OnIsBreakConnectingProc func, _void* userdata );
 //! Receive buffer from socket.
 //! @param handle   The socket handle.
 //! @param buffer   Pointer to the buffer that receives the data read from the socket.
 //! @param size   Number of bytes to be read from the socket.
 //! @return The number of bytes read, 0 indicates finished, -1 indicates failure.
 static _dword ReadSocket( _socket handle, _void* buffer, _dword size );
 //! Send buffer from socket.
 //! @param handle   The socket handle.
 //! @param buffer   Pointer to the buffer that send the data from the socket.
 //! @param size   Number of bytes to be send from the socket.
 //! @return The number of bytes write, 0 indicates finished, -1 indicates failure.
 static _dword WriteSocket( _socket handle, const _void* buffer, _dword size );

//! Device
public:
 //! Check whether key is down or not.
 //! @param key    The key ID.
 //! @return True indicates the key is down.
 static _ubool IsKeyDown( _dword key );

 //! Get cursor position.
 //! @param window_handle The window handle, if provided then will feedback the position in the client region, otherwise feedback the screen position.
 //! @param pos    The cursor position in pixel.
 //! @return True indicates success false indicates failure.
 static _ubool GetCursorPos( _handle window_handle, PointI& pos );

 //! Get sound card name.
 //! @param name   The string buffer what would store sound card name.
 //! @param number   The max character number of buffer.
 //! @return True indicates success false indicates failure.
 static _ubool GetSoundCardName( _charw* name, _dword number );

//! Process/Thread or DLL
public:
 //! Restart current process.
 //! @param none.
 //! @return none.
 static _void RestartCurrentProcess( );
 //! Restart current process.
 //! @param none.
 //! @return none.
 static _void KillCurrentProcess( );

 //! Creates an instance of a named pipe and returns a handle for subsequent pipe operations.
 //! @param name   The unique pipe name.
 //! @param accessmode  The access mode.
 //! @param mode   The pipe mode, @see _PIPE_TYPE.
 //! @param maxnumber  The maximum number of instances that can be created for this pipe.
 //! @param outbuffersize The number of bytes to reserve for the output buffer. 
 //! @param inbuffersize The number of bytes to reserve for the input  buffer.
 //! @param timeout   The default time-out value, in milliseconds.
 //! @return The pipe handle.
 static _handle CreateNamedPipe( const _charw* name, _PIPE_ACCESS accessmode, _dword mode, _dword maxnumber, _dword outbuffersize, _dword inbuffersize, _dword timeout );
 //! Enables a named pipe server process to wait for a client process to connect to an instance of a named pipe.
 //! @param handle   The pipe handle.
 //! @return True indicates success false indicates failure.
 static _ubool ConnectNamedPipe( _handle handle );
 //! Disconnect a named pipe server process.
 //! @param handle   The pipe handle.
 //! @return none.
 static _void DisconnectNamedPipe( _handle handle );
 //! Wait a named pipe server connection.
 //! @param name   The unique pipe name.
 //! @param timeout   The default time-out value, in milliseconds.
 //! @return True indicates success false indicates failure.
 static _ubool WaitNamedPipe( const _charw* name, _dword timeout );
 //! Copies data from a named or anonymous pipe into a buffer without removing it from the pipe.
 //! @param handle    The pipe handle.
 //! @param buffer    A pointer to a buffer that receives data read from the pipe.
 //! @param size    The size of the buffer in bytes.
 //! @param bytesread   A pointer to a variable that receives the number of bytes read from the pipe.
 //! @param total_bytes_avail  A pointer to a variable that receives the total number of bytes available to be read from the pipe.
 //! @param bytes_left   A pointer to a variable that receives the number of bytes remaining in this message.
 //! @return True indicates success, false indicates failure.
 static _ubool PeekNamedPipe( _handle handle, _void* buffer, _dword size, _dword* bytesread = _null, _dword* total_bytes_avail = _null, _dword* bytes_left = _null );

 //! Get module process file name.
 //! @param module   The module handle, null indicates get the current process file name.
 //! @param name   The string buffer what would store module file name.
 //! @param length   The max size of buffer in number of characters.
 //! @return True indicates success false indicates failure.
 static _ubool GetModuleFileName( _handle dllmodule, _charw* name, _dword length );
 //! Retrieves a module handle for the specified module in ANSI mode.
 //! @param modulename  The module name.
 //! @return A handle to the specified module.
 static _handle GetModuleHandleA( const _chara* modulename );
 //! Retrieves a module handle for the specified module in UNICODE mode.
 //! @param modulename  The module name.
 //! @return A handle to the specified module.
 static _handle GetModuleHandleW( const _charw* modulename );

 //! Set a processor affinity mask for the specified process.
 //! @param processhandle The process handle.
 //! @param mask   The affinity mask.
 //! @return True indicates success false indicates failure.
 static _ubool SetProcessAffinityMask( _handle processhandle, _dword mask );
 //! Set a processor affinity mask for the specified process.
 //! @param threadhandle The thread handle.
 //! @param mask   The affinity mask.
 //! @param prevmask  The previous affinity mask.
 //! @return True indicates success false indicates failure.
 static _ubool SetThreadAffinityMask( _handle threadhandle, _dword mask, _dword* prevmask = _null );
 //! Get a processor affinity mask for the specified process.
 //! @param processhandle The process handle.
 //! @param mask   The affinity mask.
 //! @param systemmask  The system affinity mask.
 //! @return True indicates success false indicates failure.
 static _ubool GetProcessAffinityMask( _handle processhandle, _dword& mask, _dword* systemmask = _null );

 //! Get the process ID by handle.
 //! @param processhandle The process handle.
 //! @return The process ID.
 static _dword GetProcessID( _handle processhandle );
 //! Get the process handle by process ID.
 //! @param processid  The process ID.
 //! @return The process handle.
 static _handle GetProcessHandle( _dword processid );

 //! Get main thread ID.
 //! @param none.
 //! @return The main thread ID.
 static _thread_id GetMainThreadID( );
 //! Check whether is main thread.
 //! @param none.
 //! @return True indicates it's main thread.
 static _ubool IsMainThread( );

 //! Get current process ID.
 //! @param none.
 //! @return The current process ID.
 static _dword GetCurrentProcessID( );
 //! Get current thread ID.
 //! @param none.
 //! @return The current thread ID.
 static _thread_id GetCurrentThreadID( );
 //! Get current process handle.
 //! @param none.
 //! @return The current process handle.
 static _handle GetCurrentProcessHandle( );
 //! Get current thread handle.
 //! @param none.
 //! @return The current thread handle.
 static _handle GetCurrentThreadHandle( );

 //! Set the thread name in ANSI mode.
 //! @param threadid  The thread ID.
 //! @param name   The thread name.
 //! @return True indicates success, false indicates failure.
 static _ubool SetThreadName( _thread_id threadid, const _chara* name );
 //! Set the thread name in UNICODE mode.
 //! @param threadid  The thread ID.
 //! @param name   The thread name.
 //! @return True indicates success, false indicates failure.
 static _ubool SetThreadName( _thread_id threadid, const _charw* name );
 //! Set the priority value for the specified thread.
 //! @param thread   A handle to the thread.
 //! @param priority  The priority value for the thread.
 //! @return True indicates success, false indicates failure.
 static _ubool SetThreadPriority( _handle thread, _PRIORITY priority );
 //! Suspends the specified thread.
 //! @param thread   A handle to the thread.
 //! @return True indicates success, false indicates failure.
 static _ubool SuspendThread( _handle thread );
 //! Decrements a thread's suspend count. When the suspend count is decremented to zero, the execution of the thread is resumed.
 //! @param thread   A handle to the thread.
 //! @return True indicates success, false indicates failure.
 static _ubool ResumeThread( _handle thread );
 //! Retrieves timing information for the specified thread.
 //! @param thread   A handle to the thread.
 //! @param creationtime A variable that receives the creation time of the thread.
 //! @param exittime  A variable that receives the exit time of the thread.
 //! @param kerneltime  A variable that receives the amount of time that the thread has executed in kernel mode.
 //! @param usertime  A variable that receives the amount of time that the thread has executed in user mode.
 //! @return True indicates success, false indicates failure.
 static _ubool GetThreadTimes( _handle thread, _qword* creationtime, _qword* exittime, _qword* kerneltime, _qword* usertime );
 //! Retrieves CPU usage for the specified thread.
 //! @param thread    A handle to the thread.
 //! @param timenow    The current time.
 //! @param last_thread_time The last thread time of CPU usage tracking.
 //! @param last_sample_time The last sample time of CPU usage tracking.
 //! @param last_sample_delta The last sample delta time of CPU usage tracking.
 //! @return The amount of CPU usage in [0.0 ~ 100.0].
 static _float GetThreadCPUUsage( _handle thread, _dword timenow, _qword& last_thread_time, _qword& last_sample_time, _qword& last_sample_delta );
 //! Adds a user-mode asynchronous procedure call (APC) object to the APC queue of the specified thread.
 //! @param thread   A handle to the thread.
 //! @param funcpointer  A pointer to the application-supplied APC function to be called when the specified thread performs an alertable wait operation. 
 //! @param parameter  A single value that is passed to the APC function pointed.
 //! @return True indicates success, false indicates failure.
 static _ubool QueueUserAPC( _handle thread, OnAPCProc funcpointer, _void* parameter );
 //! Create thread.
 //! @param funcpointer  The thread callback function pointer.
 //! @param priority  The priority (0~99).
 //! @param parameter  The thread callback function parameter.
 //! @param suspend   True indicates the thread is created in a suspended state, and does not run until the ResumeThread function is called.
 //! @param threadid  The thread ID.
 //! @return The thread handle.
 static _handle CreateThread( OnThreadStartRoutine funcpointer, _dword priority, _void* parameter, _ubool suspend, _thread_id* threadid );
 //! Close thread.
 //! @param thread   A handle to the thread.
 //! @return none.
 static _void CloseThread( _handle thread );
 //! Retrieves the termination status of the specified thread.
 //! @param thread   A handle to the thread.
 //! @param exit_code  The thread termination status.
 //! @return True indicates success, false indicates failure.
 static _ubool GetExitCodeThread( _handle thread, _dword& exit_code );
 //! Check whether the thread is alive.
 //! @param thread   A handle to the thread.
 //! @return True indicates it's active.
 static _ubool IsThreadAlive( _handle thread );
 //! Kill thread.
 //! @param thread   A handle to the thread.
 //! @return True indicates it's active.
 static _void KillThread( _handle thread );
 //! Wait thread.
 //! @param thread   A handle to the thread.
 //! @param ret_code  The thread return code.
 //! @return True indicates success, false indicates failure.
 static _ubool WaitThread( _handle thread, _dword* ret_code );

 //! Loads the specified module into the address space of the calling process.
 //! @param filename  The ANSI name of the module.
 //! @return A handle to the module.
 static _handle LoadLibrary( const _chara* filename );
 //! Loads the specified module into the address space of the calling process.
 //! @param filename  The UNICODE name of the module.
 //! @return A handle to the module.
 static _handle LoadLibrary( const _charw* filename );
 //! Frees the loaded dynamic-link library (DLL) module.
 //! @param module   A handle to the loaded library module.
 //! @return True indicates success, false indicates failure.
 static _ubool FreeLibrary( _handle module );
 //! Retrieves the address of an exported function or variable from the specified dynamic-link library (DLL).
 //! @param module   The library handle.
 //! @param procname  The function or variable name, or the function's ordinal value.
 //! @return The address of an exported function or variable.
 static _void* GetProcAddress( _handle module, const _chara* procname );

 //! Ends the calling process and all its threads.
 //! @param exitcode  The exit code for the process and all threads.
 //! @return none.
 static _void ExitProcess( _dword exitcode );
 //! Terminates the specified process and all of its threads.
 //! @param processhandle The process handle.
 //! @param exitcode  The exit code for the process and all threads.
 //! @return True indicates success false indicates failure.
 static _ubool TerminateProcess( _handle processhandle, _dword exitcode );
 //! Stops the debugger from debugging the specified process.
 //! @param process_id  The process id.
 //! @return True indicates success false indicates failure.
 static _ubool DebugActiveProcessStop( _dword process_id );
 //! Check whether the specified process is alive.
 //! @param processhandle The process handle.
 //! @return True indicates success false indicates failure.
 static _ubool IsProcessAlive( _handle processhandle );

 //! Create process in ANSI.
 //! @param modulename  The module name of launching.
 //! @param cmdline   The command line of launching.
 //! @param creationflags The creation flags, @see _PROCESS_CREATION.
 //! @param workdir   The working directory.
 //! @param processhandle The feedback process handle.
 //! @param threadhandle The feedback thread handle.
 //! @return True indicates success false indicates failure.
 static _ubool CreateProcess( const _chara* modulename, const _chara* cmdline, _dword creationflags, const _chara* workdir = _null, _handle* processhandle = _null, _handle* threadhandle = _null );
 //! Create process in UNICODE.
 //! @param modulename  The module name of launching.
 //! @param cmdline   The command line of launching.
 //! @param creationflags The creation flags, @see _PROCESS_CREATION.
 //! @param workdir   The working directory.
 //! @param processhandle The feedback process handle.
 //! @param threadhandle The feedback thread handle.
 //! @return True indicates success false indicates failure.
 static _ubool CreateProcess( const _charw* modulename, const _charw* cmdline, _dword creationflags, const _charw* workdir = _null, _handle* processhandle = _null, _handle* threadhandle = _null );
 //! Read the process memory.
 //! @param processhandle The process handle.
 //! @param baseaddress  A pointer to the base address in the specified process from which to read.
 //! @param buffer   Pointer to the buffer that receives the data read from the process.
 //! @param size   Number of bytes to be read from the process.
 //! @param bytesread  Pointer to the number of bytes read.
 //! @return True indicates success false indicates failure.
 static _ubool ReadProcessMemory( _handle processhandle, const _void* baseaddress, _void* buffer, _dword size, _dword* bytesread = _null );
 //! Check whether has specified process.
 //! @param name   The process name.
 //! @return True indicates the specified process is existing.
 static _ubool HasProcess( const _charw* name );

//! Time
public:
 //! Get current tickcount.
 //! @param none.
 //! @return The current tickcount.
 static _dword GetCurrentTickCount( );
 //! Get current cycle count.
 //! @param none.
 //! @return The current cycle count.
 static _qword GetCurrentCycleCount( );
 //! Get current cycle frequency.
 //! @param none.
 //! @return The current cycle frequency.
 static _qword GetSystemCycleFrequency( );
 //! Get the elapse time ( in millisecond ).
 //! @param cyclecount1  The first cycle count.
 //! @param cyclecount2  The second cycle count.
 //! @return The elapse time.
 static _float GetElapseTime( _qword cyclecount1, _qword cyclecount2 );
 //! Get the elapse time ( in millisecond ).
 //! @param cyclecount1  The first cycle count.
 //! @param cyclecount2  The second cycle count.
 //! @param cyclefrequency The current cycle frequency.
 //! @return The elapse time.
 static _float GetElapseTime( _qword cyclecount1, _qword cyclecount2, _qword cyclefrequency );

 //! Get the current local time.
 //! @param time   The current local time.
 //! @return True indicates success false indicates failure.
 static _ubool GetLocalTime( CalendarTime& time );
 //! Get the current local time from time in seconds.
 //! @param time   The time value.
 //! @param calendar_time The calendar time info.
 //! @return True indicates success false indicates failure.
 static _ubool GetLocalTime( _time_t time, CalendarTime& calendar_time );
 //! Get the current local time.
 //! @param none.
 //! @return The time value in seconds.
 static _time_t GetLocalTime( );
 //! Get the current system time.
 //! @param time   The current system time.
 //! @return True indicates success false indicates failure.
 static _ubool GetSystemTime( CalendarTime& time );
 //! Get the current system time from time in seconds.
 //! @param time   The time value.
 //! @param calendar_time The calendar time info.
 //! @return True indicates success false indicates failure.
 static _ubool GetSystemTime( _time_t time, CalendarTime& calendar_time );
 //! Get the current system time.
 //! @param none.
 //! @return The time value from 1970s in seconds.
 static _time_t GetSystemTime( );

 //! Returns the specified calendar time.
 //! @param calendar_time The calendar time info.
 //! @return The time value from 1970s in seconds.
 static _time_t MakeTime( const CalendarTime& calendar_time );
 //! Returns the specified calendar time.
 //! @param calendar_time The calendar time info.
 //! @return The time value from 1970s in milliseconds.
 static _time_t MakeTimeM( const CalendarTime& calendar_time );

 //! Converts a system time to file time format ( System time is based on Coordinated Universal Time (UTC) ).
 //! @param systemtime  The system time.
 //! @param filetime  The file time.
 //! @return True indicates success false indicates failure.
 static _ubool SystemTimeToFileTime( FileTime& filetime, const CalendarTime& systemtime );
 //! Converts a file time to system time format. System time is based on Coordinated Universal Time (UTC).
 //! @param filetime  The file time.
 //! @param systemtime  The system time.
 //! @return True indicates success false indicates failure.
 static _ubool FileTimeToSystemTime( CalendarTime& systemtime, const FileTime& filetime );

 //! Converts a file time to a local file time.
 //! @param localfiletime The local file time.
 //! @param filetime  The file time.
 //! @return True indicates success false indicates failure.
 static _ubool FileTimeToLocalFileTime( FileTime& localfiletime, const FileTime& filetime );
 //! Converts a local file time to a file time based on the Coordinated Universal Time (UTC). 
 //! @param filetime  The file time.
 //! @param localfiletime The local file time.
 //! @return True indicates success false indicates failure.
 static _ubool LocalFileTimeToFileTime( FileTime& filetime, const FileTime& localfiletime );

//! Debugging
public:
 //! Report error in a dialog.
 //! @param error  The error string, that is the parameter of the macro. <br/>
 //!       For example, EGE_ASSERT( "cant reach here" ) will create error string as "cant reach here".
 //! @param filename The name of the source file that throw the error.
 //! @param linenumber The line number of the source file where the assert failed.
 //! @return none.
 static _void AssertReport( const _charw* error, const _charw* filename, _dword linenumber );

 //! Output debug string in ANSI mode.
 //! @param string   The string what you want to output.
 //! @return none.
 static _void OutputDebugString( const _chara* string );
 //! Output debug string in ANSI mode in line.
 //! @param string   The string what you want to output.
 //! @return none.
 static _void OutputDebugStringInLine( const _chara* string );
 //! Output debug string in UNICODE mode.
 //! @param string   The string what you want to output.
 //! @return none.
 static _void OutputDebugString( const _charw* string );
 //! Output debug string in UNICODE mode in line.
 //! @param string   The string what you want to output.
 //! @return none.
 static _void OutputDebugStringInLine( const _charw* string );
 //! Determines whether the calling process is being debugged by a user-mode debugger.
 //! @param none.
 //! @return True indicates the current process is running in the context of a debugger.
 static _ubool IsDebuggerPresent( );
 //! Signals a breakpoint to an attached debugger.
 //! @param none.
 //! @return none.
 static _void DebuggerBreak( );
 //! Wait to attached by debugger.
 //! @param time  The time out in milliseconds.
 //! @return none.
 static _void WaitForAttach( _dword time );

//! Environment
public:
 //! Get system path.
 //! @param path   The string buffer what would store system temp path.
 //! @param length   The max size of buffer in number of characters.
 //! @return True indicates success false indicates failure.
 static _ubool GetSystemPath( _charw* path, _dword length );
 //! Get system font path.
 //! @param path   The string buffer what would store system temp path.
 //! @param length   The max size of buffer in number of characters.
 //! @return True indicates success false indicates failure.
 static _ubool GetSystemFontPath( _charw* path, _dword length );
 //! Get system temp path.
 //! @param path   The string buffer what would store system temp path.
 //! @param length   The max size of buffer in number of characters.
 //! @return True indicates success false indicates failure.
 static _ubool GetSystemTempPath( _charw* path, _dword length );

 //! Set environment variable.
 //! @param name   The variable name.
 //! @param value   The variable value.
 //! @return True indicates success false indicates failure.
 static _ubool SetEnvironment( const _charw* name, const _charw* value );
 //! Set environment variable.
 //! @param name   The variable name.
 //! @param value   The variable value.
 //! @return True indicates success false indicates failure.
 static _ubool SetEnvironment( const _charw* name, _dword value );
 //! Set environment variable.
 //! @param name   The variable name.
 //! @param value   The variable value.
 //! @return True indicates success false indicates failure.
 static _ubool SetEnvironment( const _charw* name, _void* value );
 //! Get environment variable.
 //! @param name   The variable name.
 //! @param value   The variable string.
 //! @param length   The max size of buffer in number of characters.
 //! @return True indicates success false indicates failure.
 static _ubool GetEnvironment( const _charw* name, _charw* value, _dword length );
 //! Get environment variable.
 //! @param name   The variable name.
 //! @param value   The variable value.
 //! @return True indicates success false indicates failure.
 static _ubool GetEnvironment( const _charw* name, _dword& value );
 //! Get environment variable.
 //! @param name   The variable name.
 //! @param value   The variable value.
 //! @return True indicates success false indicates failure.
 static _ubool GetEnvironment( const _charw* name, _void*& value );

//! Resource
public:
 //! Determines the location of a resource with the specified type and name in the specified module.
 //! @param module   A handle to the module whose portable executable file.
 //! @param name   The name of resource.
 //! @param type   The type of resource.
 //! @return A handle to the specified resource's information block.
 static _handle FindResource( _handle module, const _charw* name, const _charw* type );
 //! Retrieves a handle that can be used to obtain a pointer to the first byte of the specified resource in memory.
 //! @param module   A handle to the module whose portable executable file.
 //! @param resinfo   A handle to the resource.
 //! @return A handle to the data associated with the resource. 
 static _handle LoadResource( _handle module, _handle resinfo );
 //! Free a resource handle.
 //! @param module   A handle to the module whose portable executable file.
 //! @param resinfo   A handle to the resource.
 //! @return none.
 static _void FreeResource( _handle module, _handle resinfo );
 //! Retrieves a pointer to the specified resource in memory.
 //! @param resdata   A handle to the resource to be accessed.
 //! @return A pointer to the first byte of the resource.
 static const _byte* LockResource( _handle resdata );
 //! Retrieves the size, in bytes, of the specified resource.
 //! @param module   A handle to the module whose portable executable file.
 //! @param resinfo   A handle to the resource.
 //! @return The number of bytes in the resource.
 static _dword SizeOfResource( _handle module, _handle resinfo );
 //! Enumerates resources of a specified type within a binary module. 
 //! @param module   A handle to the module whose portable executable file.
 //! @param funcpointer  A pointer to the callback function to be called for each enumerated resource name or ID.
 //! @param parameter  An application-defined value passed to the callback function.
 //! @return True indicates success false indicates failure.
 static _ubool EnumResourceNames( _handle module, const _charw* type, OnEnumResNameProc funcpointer, _void* parameter );

//! Version
public:
 //! Determines whether the operating system can retrieve version information for a specified file.
 //! @param filename  The name of the file.
 //! @return The size, in bytes, of the file's version information.
 static _dword GetFileVersionInfoSize( const _charw* filename );
 //! Retrieves version information for the specified file.
 //! @param filename  The name of the file.
 //! @param buffersize  The size, in bytes, of the buffer pointed to by the bufferdata parameter. 
 //! @param bufferdata  Pointer to a buffer that receives the file-version information.
 //! @return True indicates success false indicates failure.
 static _ubool GetFileVersionInfo( const _charw* filename, _dword buffersize, _void* bufferdata );
 //! Retrieves specified version information buffer from the specified version-information resource.
 //! @param block   The version-information resource returned by the GetFileVersionInfo function.
 //! @param subblock  The version-information value to be retrieved.
 //! @param bufferdata  When this method returns, contains the address of a pointer to the requested version information in the buffer pointed to by block.
 //! @param buffersize  When this method returns, contains a pointer to the size of the requested data pointed to by bufferdata.
 //! @return True indicates success false indicates failure.
 static _ubool VerQueryBuffer( _void* block, const _charw* subblock, _void*& bufferdata, _dword& buffersize );

//! Console
public:
 //! Read a ANSI character from the standard input stream.
 //! @param none
 //! @return The character read.
 static _chara GetAChar( );
 //! Read a UNICODE character from the standard input stream.
 //! @param none
 //! @return The character read.
 static _charw GetWChar( );

 //! Print ANSI string output to the standard output stream.
 //! @param string  The string what you want to print.
 //! @return none.
 static _void WriteConsole( const _chara* string );
 //! Print UNICODE string output to the standard output stream.
 //! @param string  The string what you want to print.
 //! @return none.
 static _void WriteConsole( const _charw* string );

//! Clipboard
public:
 //! Open the clipboard.
 //! @param none.
 //! @return True indicates success false indicates failure.
 static _ubool OpenClipboard( );
 //! Close the clipboard.
 //! @param none.
 //! @return none.
 static _void CloseClipboard( );

 //! Open/Get data from clipboard.
 //! @remark  Just feedback  the buffer data pointer without copy.
 //! @param flag  The clipboard buffer data flag.
 //! @return buffer  The clipboard buffer data pointer.
 //! @param size  The clipboard buffer data size.
 //! @return The clipboard buffer data handle.
 static _handle GetClipboardData( _CLIPBOARD_FLAG flag, _byte*& pointer, _dword* size = _null );
 //! Close data from clipboard.
 //! @param pointer  The clipboard buffer data handle.
 //! @return none.
 static _void CloseClipboardData( _handle handle );

 //! Read data from clipboard.
 //! @param flag  The clipboard buffer data flag.
 //! @param buffer  The clipboard buffer data.
 //! @param size  The clipboard buffer size.
 //! @return True indicates success false indicates failure.
 static _ubool ReadClipboard( _CLIPBOARD_FLAG flag, _byte* buffer, _dword size );
 //! Write data to clipboard.
 //! @remark  This operation will clean and overwrite the clipboard previous data.
 //! @param flag  The clipboard buffer data flag.
 //! @param buffer  The clipboard buffer data.
 //! @param size  The clipboard buffer size.
 //! @return True indicates success false indicates failure.
 static _ubool WriteClipboard( _CLIPBOARD_FLAG flag, const _void* buffer, _dword size );
 
//! Converter
public:
 //! Convert the signed 32-bits integer to string.
 //! @param value  The value.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @param string  The string presentation of the integer in decimal.
 //! @param length  The max size of buffer in number of characters.
 //! @return The string buffer pointer.
 static _chara* ConvertLongToString( _int value, _dword radix, _chara* string, _dword length );
 //! Convert the signed 32-bits integer to string.
 //! @param value  The value.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @param string  The string presentation of the integer in decimal.
 //! @param length  The max size of buffer in number of characters.
 //! @return The string buffer pointer.
 static _chara* ConvertDwordToString( _dword value, _dword radix, _chara* string, _dword length );
 //! Convert the signed 64-bits integer to string.
 //! @param value  The value.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @param string  The string presentation of the integer in decimal.
 //! @param length  The max size of buffer in number of characters.
 //! @return The string buffer pointer.
 static _chara* ConvertLargeToString( _large value, _dword radix, _chara* string, _dword length );
 //! Convert the unsigned 64-bits integer to string.
 //! @param value  The value.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @param string  The string presentation of the integer in decimal.
 //! @param length  The max size of buffer in number of characters.
 //! @return The string buffer pointer.
 static _chara* ConvertQwordToString( _qword value, _dword radix, _chara* string, _dword length );
 //! Convert the float to string.
 //! @param value  The value.
 //! @param string  The string presentation of the integer in floating point.
 //! @param length  The max size of buffer in number of characters.
 //! @param precision The floating point precision after decimal point.
 //! @return The string buffer pointer.
 static _chara* ConvertFloatToString( _float value, _chara* string, _dword length, _dword precision = 6 );
 //! Convert the double to string.
 //! @param value  The value.
 //! @param string  The string presentation of the integer in double point.
 //! @param length  The max size of buffer in number of characters.
 //! @param precision The floating point precision after decimal point.
 //! @return The string buffer pointer.
 static _chara* ConvertDoubleToString( _double value, _chara* string, _dword length, _dword precision = 15 );

 //! Convert the signed 32-bits integer to string.
 //! @param value  The value.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @param string  The string presentation of the integer in decimal.
 //! @param length  The max size of buffer in number of characters.
 //! @return The string buffer pointer.
 static _charw* ConvertLongToString( _int value, _dword radix, _charw* string, _dword length );
 //! Convert the signed 32-bits integer to string.
 //! @param value  The value.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @param string  The string presentation of the integer in decimal.
 //! @param length  The max size of buffer in number of characters.
 //! @return The string buffer pointer.
 static _charw* ConvertDwordToString( _dword value, _dword radix, _charw* string, _dword length );
 //! Convert the signed 64-bits integer to string.
 //! @param value  The value.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @param string  The string presentation of the integer in decimal.
 //! @param length  The max size of buffer in number of characters.
 //! @return The string buffer pointer.
 static _charw* ConvertLargeToString( _large value, _dword radix, _charw* string, _dword length );
 //! Convert the unsigned 64-bits integer to string.
 //! @param value  The value.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @param string  The string presentation of the integer in decimal.
 //! @param length  The max size of buffer in number of characters.
 //! @return The string buffer pointer.
 static _charw* ConvertQwordToString( _qword value, _dword radix, _charw* string, _dword length );
 //! Convert the float to string.
 //! @param value  The value.
 //! @param string  The string presentation of the integer in floating point.
 //! @param length  The max size of buffer in number of characters.
 //! @param precision The floating point precision after decimal point.
 //! @return The string buffer pointer.
 static _charw* ConvertFloatToString( _float value, _charw* string, _dword length, _dword precision = 6 );
 //! Convert the double to string.
 //! @param value  The value.
 //! @param string  The string presentation of the integer in double point.
 //! @param length  The max size of buffer in number of characters.
 //! @param precision The floating point precision after decimal point.
 //! @return The string buffer pointer.
 static _charw* ConvertDoubleToString( _double value, _charw* string, _dword length, _dword precision = 15 );

 //! Convert the string to bool.
 //! @param string  The string.
 //! @return The value in bool.
 static _boolean ConvertStringToBool( const _chara* string );
 //! Convert the string to signed 32-bits integer.
 //! @param string  The string.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @return The value in decimal.
 static _int ConvertStringToLong( const _chara* string, _dword radix );
 //! Convert the string to unsigned 32-bits integer.
 //! @param string  The string.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @return The value in decimal.
 static _dword ConvertStringToDword( const _chara* string, _dword radix );
 //! Convert the string to signed 64-bits integer.
 //! @param string  The string.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @return The value in decimal.
 static _large ConvertStringToLarge( const _chara* string, _dword radix );
 //! Convert the string to unsigned 64-bits integer.
 //! @param string  The string.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @return The value in decimal.
 static _qword ConvertStringToQword( const _chara* string, _dword radix );
 //! Convert the string to float.
 //! @param string  The string.
 //! @return The value in floating point.
 static _float ConvertStringToFloat( const _chara* string );
 //! Convert the string to double.
 //! @param string  The string.
 //! @return The value in floating point.
 static _double ConvertStringToDouble( const _chara* string );

 //! Convert the string to bool.
 //! @param string  The string.
 //! @return The value in bool.
 static _boolean ConvertStringToBool( const _charw* string );
 //! Convert the string to signed 32-bits integer.
 //! @param string  The string.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @return The value in decimal.
 static _int ConvertStringToLong( const _charw* string, _dword radix );
 //! Convert the string to unsigned 32-bits integer.
 //! @param string  The string.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @return The value in decimal.
 static _dword ConvertStringToDword( const _charw* string, _dword radix );
 //! Convert the string to signed 64-bits integer.
 //! @param string  The string.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @return The value in decimal.
 static _large ConvertStringToLarge( const _charw* string, _dword radix );
 //! Convert the string to unsigned 64-bits integer.
 //! @param string  The string.
 //! @param radix  The base of value, which must be in the range 2每36.
 //! @return The value in decimal.
 static _qword ConvertStringToQword( const _charw* string, _dword radix );
 //! Convert the string to float.
 //! @param string  The string.
 //! @return The value in floating point.
 static _float ConvertStringToFloat( const _charw* string );
 //! Convert the string to double.
 //! @param string  The string.
 //! @return The value in floating point.
 static _double ConvertStringToDouble( const _charw* string );
 
//! String
public:
 //! Determine if string is empty, or looks like blank.
 //! @param string  The string.
 //! @return True if blank, false otherwise.
 static _ubool IsBlank( const _chara* string );
 //! Determine if string is empty, or looks like blank.
 //! @param string  The string.
 //! @return True if blank, false otherwise.
 static _ubool IsBlank( const _charw* string ); 
 //! Determine the path is a full path or not, a full path will begin with "X:" or "\\"
 //! @param path  The path.
 //! @return True if full path, false otherwise.
 static _ubool IsFullpath( const _chara* path );
 //! Determine the path is a full path or not, a full path will begin with "X:" or "\\"
 //! @param path  The path.
 //! @return True if full path, false otherwise.
 static _ubool IsFullpath( const _charw* path );

 //! Trim an ANSI string from left to right.
 //! @param string   The string buffer. 
 //! @param stringlength The string buffer length.
 //! @param character  The character what you want to trim.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The trimmed string.
 static _chara* TrimStringLeft( _chara* string, _dword& stringlength, _chara character, _ubool ignorecase = _false );
 //! Trim an UNICODE string from left to right.
 //! @param string   The string buffer. 
 //! @param stringlength The string buffer length.
 //! @param character  The character what you want to trim.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The trimmed string.
 static _charw* TrimStringLeft( _charw* string, _dword& stringlength, _charw character , _ubool ignorecase = _false );
 //! Trim an ANSI string from right to left.
 //! @param string   The string buffer. 
 //! @param stringlength The string buffer length.
 //! @param character  The character what you want to trim.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The trimmed string.
 static _chara* TrimStringRight( _chara* string, _dword& stringlength, _chara character, _ubool ignorecase = _false );
 //! Trim an UNICODE string from right to left.
 //! @param string   The string buffer. 
 //! @param stringlength The string buffer length.
 //! @param character  The character what you want to trim.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The trimmed string.
 static _charw* TrimStringRight( _charw* string, _dword& stringlength, _charw character, _ubool ignorecase = _false );
 //! Trim an ANSI string both left and right.
 //! @param string   The string buffer. 
 //! @param stringlength The string buffer length.
 //! @param character  The character what you want to trim.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The trimmed string.
 static _chara* TrimStringBoth( _chara* string, _dword& stringlength, _chara character, _ubool ignorecase = _false );
 //! Trim an UNICODE string both left and right.
 //! @param string   The string buffer. 
 //! @param stringlength The string buffer length.
 //! @param character  The character what you want to trim.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The trimmed string.
 static _charw* TrimStringBoth( _charw* string, _dword& stringlength, _charw character, _ubool ignorecase = _false );

 //! Trim an ANSI string from left to right.
 //! @param string   The string buffer. 
 //! @param stringlength The string buffer length.
 //! @param charset   The substring what you want to trim.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The trimmed string.
 static _chara* TrimStringLeft( _chara* string, _dword& stringlength, const _chara* charset, _ubool ignorecase = _false );
 //! Trim an UNICODE string from left to right.
 //! @param string   The string buffer. 
 //! @param stringlength The string buffer length.
 //! @param charset   The substring what you want to trim.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The trimmed string.
 static _charw* TrimStringLeft( _charw* string, _dword& stringlength, const _charw* charset, _ubool ignorecase = _false );
 //! Trim an ANSI string from right to left.
 //! @param string   The string buffer. 
 //! @param stringlength The string buffer length.
 //! @param charset   The substring what you want to trim.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The trimmed string.
 static _chara* TrimStringRight( _chara* string, _dword& stringlength, const _chara* charset, _ubool ignorecase = _false );
 //! Trim an UNICODE string from right to left.
 //! @param string   The string buffer. 
 //! @param stringlength The string buffer length.
 //! @param charset   The substring what you want to trim.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The trimmed string.
 static _charw* TrimStringRight( _charw* string, _dword& stringlength, const _charw* charset, _ubool ignorecase = _false );
 //! Trim an ANSI string both left and right.
 //! @param string   The string buffer. 
 //! @param stringlength The string buffer length.
 //! @param charset   The substring what you want to trim.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The trimmed string.
 static _chara* TrimStringBoth( _chara* string, _dword& stringlength, const _chara* charset, _ubool ignorecase = _false );
 //! Trim an UNICODE string both left and right.
 //! @param string   The string buffer. 
 //! @param stringlength The string buffer length.
 //! @param charset   The substring what you want to trim.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The trimmed string.
 static _charw* TrimStringBoth( _charw* string, _dword& stringlength, const _charw* charset, _ubool ignorecase = _false );

 //! Search a character in the ANSI string from left to right.
 //! @param string   The string buffer.
 //! @param character  The character to be searched.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The index of the first occurrence of the character or -1 indicates cant find.
 static _dword SearchL2R( const _chara* string, _chara character, _ubool ignorecase = _false );
 //! Search a character in the UNICODE string from left to right.
 //! @param string   The string buffer.
 //! @param character  The character to be searched.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The index of the first occurrence of the character or -1 indicates cant find.
 static _dword SearchL2R( const _charw* string, _charw character, _ubool ignorecase = _false );
 //! Search a character in the ANSI string from right to left.
 //! @param string   The string buffer.
 //! @param character  The character to be searched.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The index of the first occurrence of the character or -1 indicates cant find.
 static _dword SearchR2L( const _chara* string, _chara character, _ubool ignorecase = _false );
 //! Search a character in the UNICODE string from right to left.
 //! @param string   The string buffer.
 //! @param character  The character to be searched.
 //! @param ignorecase  True indicates case insensitive.
 //! @return The index of the first occurrence of the character or -1 indicates cant find.
 static _dword SearchR2L( const _charw* string, _charw character, _ubool ignorecase = _false );

 //! Search a substring in the ANSI string from left to right.
 //! @param string   The string buffer.
 //! @param substring  The substring to be searched.
 //! @param ignorecase  True indicates case insensitive.
 //! @param endindex  The end index of searching.
 //! @return The index of the first occurrence of the substring or -1 indicates cant find.
 static _dword SearchL2R( const _chara* string, const _chara* substring, _ubool ignorecase = _false, _dword* endindex = _null );
 //! Search a substring in the UNICODE string from left to right.
 //! @param string   The string buffer.
 //! @param substring  The substring to be searched.
 //! @param ignorecase  True indicates case insensitive.
 //! @param endindex  The end index of searching.
 //! @return The index of the first occurrence of the substring or -1 indicates cant find.
 static _dword SearchL2R( const _charw* string, const _charw* substring, _ubool ignorecase = _false, _dword* endindex = _null );
 //! Search a substring in the ANSI string from right to left.
 //! @param string   The string buffer.
 //! @param substring  The substring to be searched.
 //! @param ignorecase  True indicates case insensitive.
 //! @param startindex  The start index of searching.
 //! @return The index of the first occurrence of the substring or -1 indicates cant find.
 static _dword SearchR2L( const _chara* string, const _chara* substring, _ubool ignorecase = _false, _dword* startindex = _null );
 //! Search a substring in the UNICODE string from right to left.
 //! @param string   The string buffer.
 //! @param substring  The substring to be searched.
 //! @param ignorecase  True indicates case insensitive.
 //! @param startindex  The start index of searching.
 //! @return The index of the first occurrence of the substring or -1 indicates cant find.
 static _dword SearchR2L( const _charw* string, const _charw* substring, _ubool ignorecase = _false, _dword* startindex = _null );

 //! Copy an ANSI string.
 //! @param desbuffer  The dest ANSI string buffer. 
 //! @param srcbuffer  The src ANSI string buffer. 
 //! @param number   The number of characters to be copied, -1 indicates auto-detected. 
 //! @return The dest ANSI string buffer.
 static _chara* CopyString( _chara* desbuffer, const _chara* srcbuffer, _dword number = -1 );
 //! Copy an UNICODE string.
 //! @param desbuffer  The dest UNICODE string buffer. 
 //! @param srcbuffer  The src UNICODE string buffer. 
 //! @param number   The number of characters to be copied, -1 indicates auto-detected. 
 //! @return The dest UNICODE string buffer.
 static _charw* CopyString( _charw* desbuffer, const _charw* srcbuffer, _dword number = -1 );

 //! Append an ANSI string.
 //! @param desbuffer  The dest ANSI string buffer. 
 //! @param srcbuffer  The src ANSI string buffer.
 //! @return The dest ANSI string buffer.
 static _chara* AppendString( _chara* desbuffer, const _chara* srcbuffer );
 //! Append an UNICODE string.
 //! @param desbuffer  The dest UNICODE string buffer. 
 //! @param srcbuffer  The src UNICODE string buffer.
 //! @return The dest UNICODE string buffer.
 static _charw* AppendString( _charw* desbuffer, const _charw* srcbuffer );

 //! Compare two ANSI string.
 //! @param string1   The ANSI string 1.
 //! @param string2   The ANSI string 2.
 //! @param ignorecase  True indicates case insensitive.
 //! @return -1    The string 1 is smaller than string 2. <br>
 //!     0    The string 1 is equal to string 2. <br>
 //!     1    The string 1 is bigger than string 2.
 static _int CompareString( const _chara* string1, const _chara* string2, _ubool ignorecase = _false );
 //! Compare two UNICODE string.
 //! @param string1   The UNICODE string 1.
 //! @param string2   The UNICODE string 2.
 //! @param ignorecase  True indicates case insensitive.
 //! @return -1    The string 1 is smaller than string 2. <br>
 //!     0    The string 1 is equal to string 2. <br>
 //!     1    The string 1 is bigger than string 2.
 static _int CompareString( const _charw* string1, const _charw* string2, _ubool ignorecase = _false );
 //! Compare two ANSI characters in case insensitive mode.
 //! @param c1    The ANSI character 1.
 //! @param c2    The ANSI character 2.
 //! @param ignorecase  True indicates case insensitive.
 //! @return -1    The character 1 is smaller than character 2. <br>
 //!     0    The character 1 is equal to character 2. <br>
 //!     1    The character 1 is bigger than character 2.
 static _int CompareCase( _chara c1, _chara c2, _ubool ignorecase = _false );
 //! Compare two UNICODE characters in case insensitive mode.
 //! @param c1    The UNICODE character 1.
 //! @param c2    The UNICODE character 2.
 //! @param ignorecase  True indicates case insensitive.
 //! @return -1    The character 1 is smaller than character 2. <br>
 //!     0    The character 1 is equal to character 2. <br>
 //!     1    The character 1 is bigger than character 2.
 static _int CompareCase( _charw c1, _charw c2, _ubool ignorecase = _false );
 //! Compare two ANSI strings with wildcards.
 //! @param string   The first string will to be searched.
 //! @param matchstring  The second string with wildcards to search.
 //! @param ignorecase  True indicates case insensitive.
 //! @return True if the string meets the wildcard, false otherwise.
 //! @remarks Wildcards must in the second string, otherwise it will be normal character.<br>
 //!    <b>'*'</b> meets zero or more character.<br>
 //!    <b>'?'</b> meets exactly one character.<br>
 //!    '*' must not adjacent with other wildcards together, otherwise will get wrong result.
 //!    For example, "Hello" will meets "He??o" or "H*o" or "*Hello".
 static _ubool CompareWildcard( const _chara* string, const _chara* matchstring, _ubool ignorecase = _false );
 //! Compare two UNICODE strings with wildcards.
 //! @param string   The first string will to be searched.
 //! @param matchstring  The second string with wildcards to search.
 //! @param ignorecase  True indicates case insensitive.
 //! @return True if the string meets the wildcard, false otherwise.
 //! @remarks Wildcards must in the second string, otherwise it will be normal character.<br>
 //!    <b>'*'</b> meets zero or more character.<br>
 //!    <b>'?'</b> meets exactly one character.<br>
 //!    '*' must not adjacent with other wildcards together, otherwise will get wrong result.
 //!    For example, "Hello" will meets "He??o" or "H*o" or "*Hello".
 static _ubool CompareWildcard( const _charw* string, const _charw* matchstring, _ubool ignorecase = _false );

 //! Get an ANSI string length.
 //! @param string   The ANSI string.
 //! @return The string length of ANSI string.
 static _dword StringLength( const _chara* string );
 //! Get an UNICODE string length.
 //! @param string   The UNICODE string.
 //! @return The string length of UNICODE string.
 static _dword StringLength( const _charw* string );

 //! Convert an ANSI string to lowercase.
 //! @param string   The ANSI string.
 //! @param number   The number of characters to convert.
 //! @return The converted ANSI string.
 static _chara* LowercaseString( _chara* string, _dword number = -1 );
 //! Convert an ANSI string to uppercase.
 //! @param string   The ANSI string.
 //! @param number   The number of characters to convert.
 //! @return The converted ANSI string.
 static _chara* UppercaseString( _chara* string, _dword number = -1 );
 //! Convert an UNICODE string to lowercase.
 //! @param string   The UNICODE string.
 //! @param number   The number of characters to convert.
 //! @return The converted UNICODE string.
 static _charw* LowercaseString( _charw* string, _dword number = -1 );
 //! Convert an UNICODE string to lowercase.
 //! @param string   The UNICODE string.
 //! @param number   The number of characters to convert.
 //! @return The converted UNICODE string.
 static _charw* UppercaseString( _charw* string, _dword number = -1 );

 //! Check whether it's UTF-8 encoding string.
 //! @param buffer   The buffer string to test.
 //! @param size   The size of buffer in bytes, -1 indicates it's end with '\0' character.
 //! @return True indicates it's UTF-8 encoding string.
 static _ubool IsUtf8String( const _chara* buffer, _dword size = -1 );

 //! Convert an ANSI string to UNICODE.
 //! @param buffer   The buffer used to copy string.
 //! @param size   The max size of buffer in number of characters.
 //! @param string   The ANSI string.
 //! @param number   The number of characters to convert.
 //! @return The number of characters in bytes (not containers '\0' character bytes).
 static _dword AnsiToUtf16( _charw* buffer, _dword size, const _chara* string, _dword number = -1 );
 //! Convert an UNICODE string to ANSI.
 //! @param buffer   The buffer used to copy string.
 //! @param size   The max size of buffer in number of characters.
 //! @param string   The UNICODE string.
 //! @param number   The number of characters to convert.
 //! @return The number of characters in bytes (not containers '\0' character bytes).
 static _dword Utf16ToAnsi( _chara* buffer, _dword size, const _charw* string, _dword number = -1 );

 //! Convert an UTF-8 string to UNICODE.
 //! @param buffer   The buffer used to copy string.
 //! @param size   The max size of buffer in number of characters.
 //! @param string   The UTF-8 string.
 //! @param number   The number of characters to convert.
 //! @return The number of characters in bytes (not containers '\0' character bytes).
 static _dword Utf8ToUtf16( _charw* buffer, _dword size, const _chara* string, _dword number = -1 );
 //! Convert an UNICODE string to UTF-8.
 //! @param buffer   The buffer used to copy string.
 //! @param size   The max size of buffer in number of characters.
 //! @param string   The UNICODE string.
 //! @param number   The number of characters to convert.
 //! @return The number of characters in bytes (not containers '\0' character bytes).
 static _dword Utf16ToUtf8( _chara* buffer, _dword size, const _charw* string, _dword number = -1 );

 //! Format ANSI string by format.
 //! @param buffer   The buffer used to copy string.
 //! @param size   The max size of buffer in number of characters.
 //! @param format   The string format.
 //! @return The formatted string.
 static _chara* FormatStringByArguments( _chara* buffer, _dword size, const _chara* format, ... );
 //! Format UTF-16 string by format.
 //! @param buffer   The buffer used to copy string.
 //! @param size   The max size of buffer in number of characters.
 //! @param format   The string format.
 //! @return The formatted string.
 static _charw* FormatStringByArguments( _charw* buffer, _dword size, const _charw* format, ... );

 //! Format ANSI string by arguments.
 //! @param buffer   The buffer used to copy string.
 //! @param size   The max size of buffer in number of characters.
 //! @param format   The string format.
 //! @param arguments  The arguments.
 //! @return The formatted string.
 static _chara* FormatStringByVAList( _chara* buffer, _dword size, const _chara* format, _va_list arguments );
 //! Format UTF-16 string by arguments.
 //! @param buffer   The buffer used to copy string.
 //! @param size   The max size of buffer in number of characters.
 //! @param format   The string format.
 //! @param arguments  The arguments.
 //! @return The formatted string.
 static _charw* FormatStringByVAList( _charw* buffer, _dword size, const _charw* format, _va_list arguments );

 //! Get the format ANSI string length.
 //! @param format   The string format.
 //! @param arguments  The arguments.
 //! @return The formatted string length.
 static _dword GetFormatStringLength( const _chara* format, _va_list arguments );
 //! Get the format UTF-16 string length.
 //! @param format   The string format.
 //! @param arguments  The arguments.
 //! @return The formatted string length.
 static _dword GetFormatStringLength( const _charw* format, _va_list arguments );

 //! Format string with different number of parameter (ANSI version).
 template< class T1 >
 static _chara* FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1 );

 template< class T1, class T2 >
 static _chara* FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2 );

 template< class T1, class T2, class T3 >
 static _chara* FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3 );

 template< class T1, class T2, class T3, class T4 >
 static _chara* FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4 );

 template< class T1, class T2, class T3, class T4, class T5 >
 static _chara* FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5 );

 template< class T1, class T2, class T3, class T4, class T5, class T6 >
 static _chara* FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6 );

 template< class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
 static _chara* FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7 );

 template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
 static _chara* FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8 );

 template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
 static _chara* FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9 );

 template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10 >
 static _chara* FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10 );

 //! Format string with different number of parameter (UNICODE version).
 template< class T1 >
 static _charw* FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1 );

 template< class T1, class T2 >
 static _charw* FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2 );

 template< class T1, class T2, class T3 >
 static _charw* FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3 );

 template< class T1, class T2, class T3, class T4 >
 static _charw* FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4 );

 template< class T1, class T2, class T3, class T4, class T5 >
 static _charw* FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5 );

 template< class T1, class T2, class T3, class T4, class T5, class T6 >
 static _charw* FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6 );

 template< class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
 static _charw* FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7 );

 template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
 static _charw* FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8 );

 template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
 static _charw* FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9 );

 template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10 >
 static _charw* FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10 );
};

//----------------------------------------------------------------------------
// Platform Implementation
//----------------------------------------------------------------------------

template< class T1 >
_chara* Platform::FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_1( p1 );
 return buffer;
}

template< class T1, class T2 >
_chara* Platform::FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_2( p1, p2 );
 return buffer;
}

template< class T1, class T2, class T3 >
_chara* Platform::FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_3( p1, p2, p3 );
 return buffer;
}

template< class T1, class T2, class T3, class T4 >
_chara* Platform::FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_4( p1, p2, p3, p4 );
 return buffer;
}

template< class T1, class T2, class T3, class T4, class T5 >
_chara* Platform::FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
  _EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_5( p1, p2, p3, p4, p5 );
 return buffer;
}

template< class T1, class T2, class T3, class T4, class T5, class T6 >
_chara* Platform::FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
  _EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
  _EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_6( p1, p2, p3, p4, p5, p6 );
 return buffer;
}

template< class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
_chara* Platform::FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
  _EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
  _EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
  _EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_7( p1, p2, p3, p4, p5, p6, p7 );
 return buffer;
}

template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
_chara* Platform::FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
  _EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
  _EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
  _EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
  _EGE_BUILD_ARG_WITH_INDEX( 8, p8 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_8( p1, p2, p3, p4, p5, p6, p7, p8 );
 return buffer;
}

template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
_chara* Platform::FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
  _EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
  _EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
  _EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
  _EGE_BUILD_ARG_WITH_INDEX( 8, p8 );
  _EGE_BUILD_ARG_WITH_INDEX( 9, p9 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_9( p1, p2, p3, p4, p5, p6, p7, p8, p9 );
 return buffer;
}

template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10 >
_chara* Platform::FormatStringBuffer( _chara* buffer, _dword size, const _chara* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
  _EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
  _EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
  _EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
  _EGE_BUILD_ARG_WITH_INDEX( 8, p8 );
  _EGE_BUILD_ARG_WITH_INDEX( 9, p9 );
  _EGE_BUILD_ARG_WITH_INDEX( 10, p10 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_ASTRING_WITH_ARGUMENTS_10( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 );
 return buffer;
}

template< class T1 >
_charw* Platform::FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_1( p1 );
 return buffer;
}

template< class T1, class T2 >
_charw* Platform::FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_2( p1, p2 );
 return buffer;
}

template< class T1, class T2, class T3 >
_charw* Platform::FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_3( p1, p2, p3 );
 return buffer;
}

template< class T1, class T2, class T3, class T4 >
_charw* Platform::FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_4( p1, p2, p3, p4 );
 return buffer;
}

template< class T1, class T2, class T3, class T4, class T5 >
_charw* Platform::FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
  _EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_5( p1, p2, p3, p4, p5 );
 return buffer;
}

template< class T1, class T2, class T3, class T4, class T5, class T6 >
_charw* Platform::FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
  _EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
  _EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_6( p1, p2, p3, p4, p5, p6 );
 return buffer;
}

template< class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
_charw* Platform::FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
  _EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
  _EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
  _EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_7( p1, p2, p3, p4, p5, p6, p7 );
 return buffer;
}

template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
_charw* Platform::FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
  _EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
  _EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
  _EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
  _EGE_BUILD_ARG_WITH_INDEX( 8, p8 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_8( p1, p2, p3, p4, p5, p6, p7, p8 );
 return buffer;
}

template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
_charw* Platform::FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
  _EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
  _EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
  _EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
  _EGE_BUILD_ARG_WITH_INDEX( 8, p8 );
  _EGE_BUILD_ARG_WITH_INDEX( 9, p9 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_9( p1, p2, p3, p4, p5, p6, p7, p8, p9 );
 return buffer;
}

template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10 >
_charw* Platform::FormatStringBuffer( _charw* buffer, _dword size, const _charw* format, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10 )
{
 _EGE_BUILD_ARGS_BEGIN( );
  _EGE_BUILD_ARG_WITH_INDEX( 1, p1 );
  _EGE_BUILD_ARG_WITH_INDEX( 2, p2 );
  _EGE_BUILD_ARG_WITH_INDEX( 3, p3 );
  _EGE_BUILD_ARG_WITH_INDEX( 4, p4 );
  _EGE_BUILD_ARG_WITH_INDEX( 5, p5 );
  _EGE_BUILD_ARG_WITH_INDEX( 6, p6 );
  _EGE_BUILD_ARG_WITH_INDEX( 7, p7 );
  _EGE_BUILD_ARG_WITH_INDEX( 8, p8 );
  _EGE_BUILD_ARG_WITH_INDEX( 9, p9 );
  _EGE_BUILD_ARG_WITH_INDEX( 10, p10 );
 _EGE_BUILD_ARGS_END( );

 _EGE_FORMAT_WSTRING_WITH_ARGUMENTS_10( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 );
 return buffer;
}

}