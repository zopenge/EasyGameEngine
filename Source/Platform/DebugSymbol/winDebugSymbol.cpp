//! @file     winDebugSymbol.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//! The symbol function declarations
typedef BOOL 	(WINAPI *_SymCleanup)( HANDLE );
typedef PVOID	(WINAPI *_SymFunctionTableAccess)( HANDLE, DWORD );
typedef PVOID	(WINAPI *_SymFunctionTableAccess64)( HANDLE, DWORD64 );
typedef BOOL	(WINAPI *_SymGetModuleInfo)( HANDLE, DWORD, PIMAGEHLP_MODULE );
typedef BOOL	(WINAPI *_SymGetModuleInfo64)( HANDLE, DWORD64, PIMAGEHLP_MODULE64 );
typedef DWORD	(WINAPI *_SymGetModuleBase)( HANDLE, DWORD );
typedef DWORD64	(WINAPI *_SymGetModuleBase64)( HANDLE, DWORD64 );
typedef BOOL 	(WINAPI *_SymGetSymFromAddr)( HANDLE, DWORD, PDWORD, PIMAGEHLP_SYMBOL );
typedef BOOL	(WINAPI *_SymGetSymFromAddr64)( HANDLE, DWORD64, PDWORD64, PIMAGEHLP_SYMBOL64 );
typedef BOOL 	(WINAPI *_SymGetLineFromAddr)( HANDLE, DWORD, PDWORD, PIMAGEHLP_LINE );
typedef BOOL	(WINAPI *_SymGetLineFromAddr64)( HANDLE, DWORD64, PDWORD, PIMAGEHLP_LINE64 );
typedef BOOL	(WINAPI *_SymFromAddr)( HANDLE, DWORD64, PDWORD64, PSYMBOL_INFO );
typedef BOOL 	(WINAPI *_SymInitialize)( HANDLE, PCSTR, BOOL );
typedef DWORD 	(WINAPI *_SymLoadModule)( HANDLE, HANDLE, PCSTR, PCSTR, DWORD, DWORD );
typedef DWORD64	(WINAPI *_SymLoadModuleEx)( HANDLE, HANDLE, PCSTR, PCSTR, DWORD64, DWORD, PMODLOAD_DATA, DWORD );
typedef BOOL 	(WINAPI *_SymUnloadModule)( HANDLE, DWORD );
typedef DWORD 	(WINAPI *_SymSetOptions)( DWORD );
typedef DWORD 	(WINAPI *_SymGetOptions)( VOID );
typedef BOOL 	(WINAPI *_StackWalk)( DWORD, HANDLE, HANDLE, LPSTACKFRAME, PVOID, PREAD_PROCESS_MEMORY_ROUTINE, PFUNCTION_TABLE_ACCESS_ROUTINE, PGET_MODULE_BASE_ROUTINE, PTRANSLATE_ADDRESS_ROUTINE );
typedef BOOL	(WINAPI *_StackWalk64)( DWORD, HANDLE, HANDLE, LPSTACKFRAME64, PVOID, PREAD_PROCESS_MEMORY_ROUTINE64, PFUNCTION_TABLE_ACCESS_ROUTINE64, PGET_MODULE_BASE_ROUTINE64, PTRANSLATE_ADDRESS_ROUTINE64 );
typedef DWORD	(WINAPI *_UnDecorateSymbolName)( PCTSTR, PTSTR, DWORD, DWORD );
typedef BOOL 	(WINAPI *_MiniDumpWriteDump)( HANDLE, DWORD, HANDLE, MINIDUMP_TYPE, CONST PMINIDUMP_EXCEPTION_INFORMATION, CONST PMINIDUMP_USER_STREAM_INFORMATION, CONST PMINIDUMP_CALLBACK_INFORMATION );

//! The debug symbol functions name
static const _chara* sSymbolFunctionNames[] = 
{
	"SymCleanup",
	"SymFunctionTableAccess",
	"SymFunctionTableAccess64",
	"SymGetModuleInfo",
	"SymGetModuleInfo64",
	"SymGetModuleBase",
	"SymGetModuleBase64",
	"SymGetSymFromAddr",
	"SymGetSymFromAddr64",
	"SymGetLineFromAddr",
	"SymGetLineFromAddr64",
	"SymFromAddr",
	"SymInitialize",
	"SymLoadModule",
	"SymLoadModuleEx",
	"SymUnloadModule",
	"SymSetOptions",
	"SymGetOptions",
	"StackWalk",
	"StackWalk64",
	"UnDecorateSymbolName",
	"MiniDumpWriteDump",
};

//! The debug symbols function pointer
struct SymbolFuncHelper
{
	_SymCleanup					mSymCleanupFunc;
	_SymFunctionTableAccess		mSymFunctionTableAccessFunc;
	_SymFunctionTableAccess64	mSymFunctionTableAccess64Func;
	_SymGetModuleInfo			mSymGetModuleInfoFunc;
	_SymGetModuleInfo64			mSymGetModuleInfo64Func;
	_SymGetModuleBase			mSymGetModuleBaseFunc;
	_SymGetModuleBase64			mSymGetModuleBase64Func;
	_SymGetSymFromAddr			mSymGetSymFromAddrFunc;
	_SymGetSymFromAddr64		mSymGetSymFromAddr64Func;
	_SymGetLineFromAddr			mSymGetLineFromAddrFunc;
	_SymGetLineFromAddr64		mSymGetLineFromAddr64Func;
	_SymFromAddr				mSymFromAddrFunc;
	_SymInitialize				mSymInitializeFunc;
	_SymLoadModule				mSymLoadModuleFunc;
	_SymLoadModuleEx			mSymLoadModuleExFunc;
	_SymUnloadModule			mSymUnloadModuleFunc;
	_SymSetOptions				mSymSetOptionsFunc;
	_SymGetOptions				mSymGetOptionsFunc;
	_StackWalk					mStackWalkFunc;
	_StackWalk64				mStackWalk64Func;
	_UnDecorateSymbolName		mUnDecorateSymbolNameFunc;
	_MiniDumpWriteDump			mMiniDumpWriteDumpFunc;
};

//!	The debug symbol helper library
static Library			sSymbolFuncLibrary;
//!	The symbol symbol helper
static SymbolFuncHelper sSymbolFuncHelper;

//----------------------------------------------------------------------------
// DebugSymbol Implementation
//----------------------------------------------------------------------------

_dword DebugSymbol::StackWalk( _void* context, _qword* addresslist, _dword number )
{
	// We must provide the address list buffer
	EGE_ASSERT( addresslist != _null && number != 0 );

	// Get the current process and thread handle
	HANDLE processhandle	= Platform::GetCurrentProcessHandle( );
	HANDLE threadhandle		= Platform::GetCurrentThreadHandle( );

	// Create a frame of stack, prepare to walk stack
	STACKFRAME64 stackframe		= {0};
	stackframe.AddrPC.Mode		= AddrModeFlat;
	stackframe.AddrStack.Mode	= AddrModeFlat;
	stackframe.AddrFrame.Mode	= AddrModeFlat;

	// Use the context, if provided
	if ( context != _null )
	{
		stackframe.AddrPC.Offset	= ( (CONTEXT*) context )->Eip;
		stackframe.AddrStack.Offset	= ( (CONTEXT*) context )->Esp;
		stackframe.AddrFrame.Offset	= ( (CONTEXT*) context )->Ebp;
	}
	// Get the current values of stack frame related x86 registers
	else
	{
		_dword reg_eip = 0;
		_dword reg_ebp = 0;
		_dword reg_esp = 0;

		__asm 
		{
			current_ip:	lea	eax, current_ip
						mov	reg_eip, eax
						mov	reg_ebp, ebp
						mov	reg_esp, esp
		}

		// Set the register values
		stackframe.AddrPC.Offset	= reg_eip;
		stackframe.AddrStack.Offset	= reg_esp;
		stackframe.AddrFrame.Offset	= reg_ebp;

		// The first result should be the return address from this function if no context was provided. We probably don't need to return that since the caller knows who he is
		(*sSymbolFuncHelper.mStackWalk64Func)( IMAGE_FILE_MACHINE_I386, processhandle, threadhandle, &stackframe, context, 
			_null, sSymbolFuncHelper.mSymFunctionTableAccess64Func, sSymbolFuncHelper.mSymGetModuleBase64Func, _null );
	}

	// The frame number
	_dword framenumber = 0;

	// Walk stack
	while ( _true )
	{
		// Get the next call stack, if cant find, exit walk
		if ( (*sSymbolFuncHelper.mStackWalk64Func)( IMAGE_FILE_MACHINE_I386, processhandle, threadhandle, &stackframe, context, 
			_null, sSymbolFuncHelper.mSymFunctionTableAccess64Func, sSymbolFuncHelper.mSymGetModuleBase64Func, _null ) == 0 )
			break;

		// Unknown callstack frame
		if ( stackframe.AddrFrame.Offset == 0 )
		{
			addresslist[ framenumber ++ ] = 0;
			continue;
		}

		// Feedback the code address
		addresslist[ framenumber ++ ] = stackframe.AddrReturn.Offset;

		// Check the code address list bounds
		if ( framenumber >= number )
			break;
	}

	return framenumber;
}

_ubool DebugSymbol::Initialize( )
{
	// Load the debug helper library
	if ( sSymbolFuncLibrary.IsLoaded( ) == _false )
	{
		if ( sSymbolFuncLibrary.Load( L"dbghelp.dll" ) == _false )
			return _false;

		// Get the function pointers
		_dword* funcpointer = (_dword*) &sSymbolFuncHelper;
		for ( _dword i = 0; i < EGE_ARRAY_NUMBER( sSymbolFunctionNames ); i ++, funcpointer ++ )
		{
			*funcpointer = (_dword) sSymbolFuncLibrary.GetFunction( sSymbolFunctionNames[i] );
			if ( funcpointer == _null )
				return _false;
		}

		// Set symbols options
		(*sSymbolFuncHelper.mSymSetOptionsFunc)( (*sSymbolFuncHelper.mSymGetOptionsFunc)( ) | SYMOPT_CASE_INSENSITIVE | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES );

		// Initialize symbols
		if ( !(*sSymbolFuncHelper.mSymInitializeFunc)( Platform::GetCurrentProcessHandle( ), _null, _true ) )
			return _false;
	}

	return _true;
}

_void DebugSymbol::Finalize( )
{
	if ( sSymbolFuncLibrary.IsLoaded( ) )
	{
		// Cleanup symbol system
		if ( sSymbolFuncHelper.mSymCleanupFunc != _null )
			(*sSymbolFuncHelper.mSymCleanupFunc)( Platform::GetCurrentProcessHandle( ) );

		// Unload the debug helper library
		sSymbolFuncLibrary.Free( );
	}
}

_ubool DebugSymbol::StackWalk( _void* context, WString& string, _dword max_frame_number )
{
	ASrcFileLineInfo call_stack[256];
	_dword number = StackWalk( context, call_stack, max_frame_number );
	if ( number == 0 )
		return _false;

	for ( _dword i = 0; i < number; i ++ )
	{
		const ASrcFileLineInfo& line_info = call_stack[i];

		// Feedback the callstack frame
		_chara string_buffer_ansi[1024];
		Platform::FormatStringBuffer( string_buffer_ansi, 1024, "%.8X\t%s:%d\n", line_info.mAddress, line_info.mFileName, line_info.mLinenumber );

		// Update callstack string
		string += WString( ).FromString( _ENCODING_ANSI, string_buffer_ansi );
	}

	return _true;
}

_dword DebugSymbol::StackWalk( _void* context, ASrcFileLineInfo* call_stack, _dword max_frame_number )
{
	// Initialize debug symbol
	if ( Initialize( ) == _false )
		return 0;

	// Get the code address list
	_qword addresslist[ 256 ];
	_dword framenumber = StackWalk( context, addresslist, EGE_ARRAY_NUMBER( addresslist ) );
	if ( framenumber == 0 )
		return 0;

	// Limit max frame number
	framenumber = Math::Min( framenumber, max_frame_number );

	// Get the current process and thread handle
	HANDLE processhandle = Platform::GetCurrentProcessHandle( );

	// Walk stack
	for ( _dword i = 0; i < framenumber; i ++ )
	{
		ASrcFileLineInfo& line_info = call_stack[i];

		// Unknown callstack frame
		if ( addresslist[i] == 0 )
		{
			SafeCopyString( line_info.mFileName, "Unknown" );
			continue;
		}

		//// DebugSymbol buffer
		//_byte symbolbuffer[ sizeof( IMAGEHLP_SYMBOL64 ) + CallStackFrame::_MAX_STRING_LENGTH ];

		//// Initialize symbol 
		//IMAGEHLP_SYMBOL64* symbol	= (IMAGEHLP_SYMBOL64*) symbolbuffer;
		//symbol->SizeOfStruct		= sizeof( symbolbuffer );
		//symbol->MaxNameLength		= CallStackFrame::_MAX_STRING_LENGTH;

		//// The function name string buffer
		//_charw funcname[ CallStackFrame::_MAX_STRING_LENGTH ];

		//// Get function symbol from address
		//_qword offset = 0;
		//if ( (*sSymbolFuncHelper.mSymGetSymFromAddr64Func)( processhandle, addresslist[i], &offset, symbol ) == _false )
		//{
		//	// Get symbol failed
		//	SafeCopyString( funcname, L"Unknown" );
		//}
		//else
		//{
		//	// The symbol->Name is ansi, so convert it to unicode
		//	Platform::AnsiToUtf16( funcname, CallStackFrame::_MAX_STRING_LENGTH, symbol->Name );
		//}

		// Get line number from address
		DWORD offset = 0; IMAGEHLP_LINE64 lineinfo = {0};
		if ( !(*sSymbolFuncHelper.mSymGetLineFromAddr64Func)( processhandle, addresslist[i], &offset, &lineinfo ) )
		{
			lineinfo.LineNumber = 0;
			lineinfo.FileName	= "Unknown";
		}

		line_info.mAddress		= (_dword) addresslist[i];
		line_info.mLinenumber	= lineinfo.LineNumber;
		SafeCopyString( line_info.mFileName, lineinfo.FileName );
	}

	return framenumber;
}

_ubool DebugSymbol::StackWalk( _void* context, OnCallStackFrame funcpointer, _void* parameter1, _void* parameter2 )
{
	if ( funcpointer == _null )
		return _false;

	// Initialize debug symbol
	if ( Initialize( ) == _false )
		return _false;

	// Get the code address list
	_qword addresslist[ 256 ];
	_dword framenumber = StackWalk( context, addresslist, EGE_ARRAY_NUMBER( addresslist ) );
	if ( framenumber == 0 )
		return _false;

	// Get the current process and thread handle
	HANDLE processhandle = Platform::GetCurrentProcessHandle( );

	// Walk stack
	for ( _dword i = 0; i < framenumber; i ++ )
	{
		// Unknown callstack frame
		if ( addresslist[i] == 0 )
		{
			// Invoke callback function
			(*funcpointer)( 0, "Unknown", "Unknown", parameter1, parameter2 );
			continue;
		}

		// DebugSymbol buffer
		_byte symbolbuffer[ sizeof( IMAGEHLP_SYMBOL64 ) + CallStackFrame::_MAX_STRING_LENGTH ];

		// Initialize symbol 
		IMAGEHLP_SYMBOL64* symbol	= (IMAGEHLP_SYMBOL64*) symbolbuffer;
		symbol->SizeOfStruct		= sizeof( symbolbuffer );
		symbol->MaxNameLength		= CallStackFrame::_MAX_STRING_LENGTH;

		// Get function symbol from address
		DWORD64 offset = 0;
		if ( !(*sSymbolFuncHelper.mSymGetSymFromAddr64Func)( processhandle, addresslist[i], &offset, symbol ) )
			Platform::CopyString( symbol->Name, "Unknown", CallStackFrame::_MAX_STRING_LENGTH );

		// Get file name and line number from address
		IMAGEHLP_LINE64 lineinfo = {0};
		if ( !(*sSymbolFuncHelper.mSymGetLineFromAddr64Func)( processhandle, addresslist[i], (DWORD*) &offset, &lineinfo ) )
		{
			lineinfo.LineNumber = 0;
			lineinfo.FileName	= "Unknown";
		}

		// Invoke callback function
		(*funcpointer)( lineinfo.LineNumber, symbol->Name, lineinfo.FileName, parameter1, parameter2 );
	}

	return _true;
}

_ubool DebugSymbol::WriteMiniDumpFile( WStringPtr filename, _void* exception )
{
	// Create dump file to save exception info
	File dumpfile;
	if ( dumpfile.Open( filename, _FILE_CREATE_ALWAYS, _FILE_OPERATION_WRITE ) == _false )
		return _false;

	// Dump exception to the file
	MINIDUMP_EXCEPTION_INFORMATION expinfo;
	expinfo.ThreadId			= (DWORD) Platform::GetCurrentThreadID( );
	expinfo.ExceptionPointers	= (EXCEPTION_POINTERS*) exception;
	expinfo.ClientPointers		= 0;

	// The dump file flags
	_dword dumpflags = MiniDumpNormal | MiniDumpWithDataSegs | MiniDumpWithProcessThreadData | MiniDumpWithThreadInfo;

	// Initialize debug symbol
	if ( Initialize( ) == _false )
		return _false;

	// Write mini dump file
	if ( (*sSymbolFuncHelper.mMiniDumpWriteDumpFunc)( Platform::GetCurrentProcessHandle( ), Platform::GetCurrentProcessID( ), (_handle) dumpfile, (_MINIDUMP_TYPE) dumpflags, &expinfo, _null, _null ) == 0 )
		return _false;

	return _true;
}