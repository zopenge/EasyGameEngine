//! @file     IWindowsPlatform.h
//! @author   LiCode
//! @version  1.0.0.547
//! @date     2011/01/07
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// The windows platform enumerations
//----------------------------------------------------------------------------

//! The DirectX Version
enum _DIRECTX_VERSION
{
	_DIRECTX_UNKNOWN,
	_DIRECTX_81,
	_DIRECTX_90,
	_DIRECTX_90a,
	_DIRECTX_90b,
	_DIRECTX_90c,
	_DIRECTX_100,
};
	
//----------------------------------------------------------------------------
// IWindowsPlatform
//----------------------------------------------------------------------------

class IWindowsPlatform
{
//!	Kernel
public:
	//!	Get DirectX version.
	//!	@param		none.
	//!	@return		The DirectX version.
	virtual _dword GetDirectXVersion( ) PURE;

//!	Environment
public:
	//!	Get local computer name.
	//!	@param		name			The local computer name.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetLocalComputerName( WString& name ) PURE;

	//!	Get current user name.
	//!	@param		name			The user name.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetCurrentUserName( WString& name ) PURE;

	//!	Get user path.
	//!	@param		path			The user path.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetUserPath( WString& path ) PURE;
	//!	Get window path.
	//!	@param		path			The window path.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetWindowPath( WString& path ) PURE;
	//!	Get desktop path.
	//!	@param		path			The desktop path.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetDesktopPath( WString& path ) PURE;
	//!	Get program group path.
	//!	@param		path			The program group path.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetProgramGroupPath( WString& path ) PURE;
	//!	Get program files path.
	//!	@param		path			The program files path.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetProgramFilesPath( WString& path ) PURE;

//!	Device
public:
	//!	Is key down or not.
	//!	@param		keycode			The key code ID.
	//!	@return		True indicates key has been down.
	virtual _ubool IsKeyDown( _dword keycode ) PURE;

	//!	Get mouse position.
	//!	@param		window			The window handle, if use null then indicates get the screen mouse position.
	//!	@return		The mouse position.
	virtual PointI GetMousePosition( _handle window ) PURE;

//!	Cursor
public:
	//!	Creates a cursor based on data contained in a file.
	//!	@param		filename		The source of the file data to be used to create the cursor. 
	//!	@return		A handle to the new cursor.
	virtual _handle LoadCursorFromFile( WStringPtr filename ) PURE;
	//!	Destroys a cursor and frees any memory the cursor occupied. Do not use this function to destroy a shared cursor.
	//!	@param		cursor			A handle to the cursor to be destroyed.
	//! @return		True indicates success false indicates failure.
	virtual _ubool DestroyCursor( _handle cursor ) PURE;
	//!	Sets the cursor shape. 
	//!	@param		cursor			A handle to the cursor.
	//!	@return		A handle to the previous cursor.
	virtual _handle SetCursor( _handle cursor ) PURE;
	//!	Retrieves the cursor's position, in screen coordinates.
	//!	@param		none.
	//!	@return		The screen coordinates of the cursor.
	virtual PointI GetCursorPos( ) PURE;

//!	Completion Port
public:
	//!	Create completion port.
	//!	@param		object				Handle to a file opened for overlapped I/O completion.
	//!	@param		completionkey		Per-file completion key that is included in every I/O completion packet for the specified file.
	//!	@param		threadnumber		The Maximum number of threads that the operating system can allow to concurrently process I/O completion packets for the I/O completion port. <br />
	//!									If this parameter is zero, the system allows as many concurrently running threads as there are processors in the system.
	//! @return		The completion port handle.
	virtual _handle CreateCompletionPort( _handle object, _dword completionkey = 0, _dword threadnumber = 0 ) PURE;
	//!	Close completion port.
	//!	@param		handle				The completion port handle.
	//!	@return		none.
	virtual _void CloseCompletionPort( _handle handle ) PURE;

	//!	Get completion port queued state.
	//!	@param		handle				The completion port handle.
	//!	@param		milliseconds		The caller is willing to wait for an completion packet to appear at the completion port.
	//!	@param		bytes_transferred	The number of bytes transferred during an I/O operation that has completed
	//!	@param		completionkey		The completion key value associated with the file handle whose I/O operation has completed.
	//!	@param		overlapped			The address of the OVERLAPPED structure that was specified when the completed I/O operation was started.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetQueuedCompletionStatus( _handle handle, _dword milliseconds, _dword& bytes_transferred, _dword& completionkey, Overlapped*& overlapped ) PURE;
	//!	Posts an I/O completion packet to an I/O completion port.
	//!	@param		handle				The completion port handle.
	//!	@param		bytes_transferred	The number of bytes transferred.
	//!	@param		completionkey		The completion key value associated with the file handle whose I/O operation has completed.
	//!	@param		overlapped			The address of the OVERLAPPED structure that was specified when the completed I/O operation was started.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool PostQueuedCompletionStatus( _handle handle, _dword bytes_transferred, _dword completionkey, Overlapped* overlapped ) PURE;
};

}
