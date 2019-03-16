//! @file     CallStack.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// CallStackFrame
//----------------------------------------------------------------------------

struct CallStackFrame {
  enum { _MAX_STRING_LENGTH = 512 };

  _dword mLineNumber;
  _chara* mFuncName;
  _chara* mFileName;
};

//----------------------------------------------------------------------------
// CallStack
//----------------------------------------------------------------------------

class CallStack : public Link<CallStackFrame> {
 private:
  typedef Link<CallStackFrame>::Node CallStackFrameNode;

 private:
  //! The callstack frame callback function.
  //! @param linenumber		The line number.
  //! @param funcname		The function name.
  //! @param filename		The file name.
  //! @param parameter1		The user defined parameter.
  //! @param parameter2		The user defined parameter.
  //! @return none.
  static _void OnCallStackFrameCallback(_dword linenumber,
                                        const _chara* funcname,
                                        const _chara* filename,
                                        _void* parameter1, _void* parameter2);

 public:
  //! Get the current callstack.
  //! @param callstack		The callstack.
  //! @return True indicates success, false indicates failure.
  static _ubool GetCurrentCallStack(CallStack& callstack);

 public:
  //! Create an exception and catch it.
  //! @param exception		The exception handle.
  //! @return none.
  _void Create(_void* exception);
  //! Create an callstack frame and insert it to tail ( ANSI mode ).
  //! @param linenumber		The line number.
  //! @param funcname		The function name.
  //! @param filename		The file name.
  //! @return none.
  _void Create(_dword linenumber, const _chara* funcname,
               const _chara* filename);
  //! Create an callstack frame and insert it to tail ( UNICODE mode ).
  //! @param linenumber		The line number.
  //! @param funcname		The function name.
  //! @param filename		The file name.
  //! @return none.
  _void Create(_dword linenumber, const _charw* funcname,
               const _charw* filename);

  //! Release callstack.
  //! @param none.
  //! @return none.
  _void Release();
};

//----------------------------------------------------------------------------
// CallStack Implementation
//----------------------------------------------------------------------------

}  // namespace EGE