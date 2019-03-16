//! @file     DebugSymbol.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// DebugSymbol
//----------------------------------------------------------------------------

class DebugSymbol
{
public:
 //! The callstack frame callback function.
 //! @param linenumber  The line number.
 //! @param funcname  The function name.
 //! @param filename  The file name.
 //! @param parameter1  The user defined parameter.
 //! @param parameter2  The user defined parameter.
 //! @return none.
 typedef _void (*OnCallStackFrame)( _dword linenumber, const _chara* funcname, const _chara* filename, _void* parameter1, _void* parameter2 );

private:
 //! Walk the callstack frame from specified context to get the code address list.
 //! @param context   The context pointer.
 //! @param addresslist  Pointer to list of addresses.
 //! @param number   Number of times to step up the stack.
 //! @return The Number of return addresses.
 static _dword StackWalk( _void* context, _qword* addresslist, _dword number );

public:
 //! Initialize.
 //! @param none.
 //! @return True indicates success, false indicates failure.
 static _ubool Initialize( );
 //! Finalize.
 //! @param none.
 //! @return none.
 static _void Finalize( );

 //! Walk the callstack frame from specified context with string.
 //! @param context   The context pointer.
 //! @param string   The string what receive the callstack frame info.
 //! @param max_frame_number The max frame number of callstack, -1 indicates unlimited.
 //! @return True indicates success, false indicates failure.
 static _ubool StackWalk( _void* context, WString& string, _dword max_frame_number = -1 );
 //! Walk the callstack frame from specified context with string.
 //! @param context    The context pointer.
 //! @param call_stack   The callstack frame info.
 //! @param max_frame_number The max frame number of callstack, -1 indicates unlimited.
 //! @return The frame number of callstack.
 static _dword StackWalk( _void* context, ASrcFileLineInfo* call_stack, _dword max_frame_number = -1 );
 //! Walk the callstack frame from specified context with callback function.
 //! @param context   The context pointer.
 //! @param funcpointer  The callstack frame callback function pointer.
 //! @param parameter1  The user defined parameter.
 //! @param parameter2  The user defined parameter.
 //! @return True indicates success, false indicates failure.
 static _ubool StackWalk( _void* context, OnCallStackFrame funcpointer, _void* parameter1 = _null, _void* parameter2 = _null );

 //! Write mini dump file.
 //! @param filename  The file name.
 //! @param exception  The exception pointer.
 //! @return True indicates success, false indicates failure.
 static _ubool WriteMiniDumpFile( WStringPtr filename, _void* exception );
};

//----------------------------------------------------------------------------
// DebugSymbol Implementation
//----------------------------------------------------------------------------

}