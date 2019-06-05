#pragma once

namespace EGE {

/// <summary>
/// The windows platform interface.
/// </summary>
class IWinPlatform : public IPlatform {
	//!	Environment
public:
	//!	Get local computer name.
	//!	@param		none.
	//! @return		The local computer name.
	virtual WString GetLocalComputerName() PURE;

	//!	Get current user name.
	//!	@param		none.
	//! @return		The user name.
	virtual WString GetCurrentUserName() PURE;

	//!	Get user path.
	//!	@param		none.
	//! @return		The user path.
	virtual WString GetUserPath() PURE;
	//!	Get window path.
	//!	@param		none.
	//! @return		The window path.
	virtual WString GetWindowPath() PURE;
	//!	Get desktop path.
	//!	@param		none.
	//! @return		The desktop path.
	virtual WString GetDesktopPath() PURE;
	//!	Get program group path.
	//!	@param		none.
	//! @return		The program group path.
	virtual WString GetProgramGroupPath() PURE;
	//!	Get program files path.
	//!	@param		none.
	//! @return		The program files path.
	virtual WString GetProgramFilesPath() PURE;

	//!	Device
public:
	//!	Is key down or not.
	//!	@param		keycode			The key code ID.
	//!	@return		True indicates key has been down.
	virtual _ubool IsKeyDown(_dword keycode) PURE;

	//!	Get mouse position.
	//!	@param		window			The window handle, if use null then indicates get the screen mouse position.
	//!	@return		The mouse position.
	virtual PointI GetMousePosition(_handle window) PURE;

	//!	Cursor
public:
	//!	Creates a cursor based on data contained in a file.
	//!	@param		filename		The source of the file data to be used to create the cursor.
	//!	@return		A handle to the new cursor.
	virtual _handle LoadCursorFromFile(WStringPtr filename) PURE;
	//!	Destroys a cursor and frees any memory the cursor occupied. Do not use this function to destroy a shared cursor.
	//!	@param		cursor			A handle to the cursor to be destroyed.
	//! @return		True indicates success false indicates failure.
	virtual _ubool DestroyCursor(_handle cursor) PURE;
	//!	Sets the cursor shape.
	//!	@param		cursor			A handle to the cursor.
	//!	@return		A handle to the previous cursor.
	virtual _handle SetCursor(_handle cursor) PURE;
	//!	Retrieves the cursor's position, in screen coordinates.
	//!	@param		none.
	//!	@return		The screen coordinates of the cursor.
	virtual PointI GetCursorPos() PURE;

	//!	Completion Port
public:
	//!	Create completion port.
	//!	@param		object				Handle to a file opened for I/O completion.
	//!	@param		completionkey		Per-file completion key that is included in every I/O completion packet for the specified file.
	//!	@param		threadnumber		The Maximum number of threads that the operating system can allow to concurrently process I/O completion packets for the I/O completion port. <br />
	//!									If this parameter is zero, the system allows as many concurrently running threads as there are processors in the system.
	//! @return		The completion port handle.
	virtual _handle CreateCompletionPort(_handle object, _dword completionkey = 0, _dword threadnumber = 0) PURE;
	//!	Close completion port.
	//!	@param		handle				The completion port handle.
	//!	@return		none.
	virtual _void CloseCompletionPort(_handle handle) PURE;

	//!	Get completion port queued state.
	//!	@param		handle				The completion port handle.
	//!	@param		milliseconds		The caller is willing to wait for an completion packet to appear at the completion port.
	//!	@param		bytes_transferred	The number of bytes transferred during an I/O operation that has completed
	//!	@param		completionkey		The completion key value associated with the file handle whose I/O operation has completed.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetQueuedCompletionStatus(_handle handle, _dword milliseconds, _dword& bytes_transferred, _dword& completionkey) PURE;
	//!	Posts an I/O completion packet to an I/O completion port.
	//!	@param		handle				The completion port handle.
	//!	@param		bytes_transferred	The number of bytes transferred.
	//!	@param		completionkey		The completion key value associated with the file handle whose I/O operation has completed.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool PostQueuedCompletionStatus(_handle handle, _dword bytes_transferred, _dword completionkey) PURE;
};

} // namespace EGE
