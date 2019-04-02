#pragma once

namespace EGE {

/// <summary>
/// The call stack frame.
/// </summary>
class CallStackFrame : public Link<CallStackFrameData> {
private:
	typedef Link<CallStackFrameData>::Node CallStackFrameNode;

private:
	//! Create an callstack frame and insert it to tail ( ANSI mode ).
	//! @param linenumber		The line number.
	//! @param funcname		The function name.
	//! @param filename		The file name.
	//! @return none.
	_void Create(_dword linenumber, const _chara* funcname, const _chara* filename);
	//! Create an callstack frame and insert it to tail ( UNICODE mode ).
	//! @param linenumber		The line number.
	//! @param funcname		The function name.
	//! @param filename		The file name.
	//! @return none.
	_void Create(_dword linenumber, const _charw* funcname, const _charw* filename);

private:
	//! The callstack frame callback function.
	//! @param linenumber	The line number.
	//! @param funcname		The function name.
	//! @param filename		The file name.
	//! @param parameter1	The user defined parameter.
	//! @param parameter2	The user defined parameter.
	//! @return none.
	static _void OnCallStackFrameCallback(_dword linenumber, const _chara* funcname, const _chara* filename, _void* parameter1, _void* parameter2);

public:
	CallStackFrame();
	~CallStackFrame();

public:
	//! Get the current callstack.
	//! @param callstack		The callstack.
	//! @return True indicates success, false indicates failure.
	static _ubool GetCurrentCallStack(CallStackFrame& callstack);

public:
	/// <summary>
	/// Create exception and save call stack frame.
	/// </summary>
	_void Create(_void* exception);

	//! Release callstack.
	//! @param none.
	//! @return none.
	_void Release();
};

} // namespace EGE