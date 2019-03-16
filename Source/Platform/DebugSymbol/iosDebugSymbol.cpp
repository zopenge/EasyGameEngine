//! @file     iosDebugSymbol.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// DebugSymbol Implementation
//----------------------------------------------------------------------------

_dword DebugSymbol::StackWalk( _void* context, _qword* addresslist, _dword number )
{
	return 0;
}

_ubool DebugSymbol::Initialize( )
{
	return _false;
}

_void DebugSymbol::Finalize( )
{
}

_ubool DebugSymbol::StackWalk( _void* context, WString& string, _dword max_frame_number )
{
	return _false;
}

_dword DebugSymbol::StackWalk( _void* context, ASrcFileLineInfo* call_stack, _dword max_frame_number )
{
	return 0;
}

_ubool DebugSymbol::StackWalk( _void* context, OnCallStackFrame funcpointer, _void* parameter1, _void* parameter2 )
{
	return _false;
}

_ubool DebugSymbol::WriteMiniDumpFile( WStringPtr filename, _void* exception )
{
	return _false;
}