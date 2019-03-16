//! @file     winProcessDebugger.cpp
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// winProcessDebugger Implementation
//----------------------------------------------------------------------------

winProcessDebugger::winProcessDebugger( )
{
	mExitCode		= 0;

	mProcessID		= 0;
	mProcessHandle	= _null;
}

winProcessDebugger::~winProcessDebugger( )
{
	// Stop debug the process
	if ( mProcessID != 0 )
		Platform::DebugActiveProcessStop( mProcessID );
}

_ubool winProcessDebugger::RunProcess( )
{
	// Start to process debug events
	while ( ::WaitForDebugEvent( &mDebugEvent, INFINITE ) )
	{
		// The debug continue status
		_dword continue_status = DBG_CONTINUE;

		// Process the debug event
		switch ( mDebugEvent.dwDebugEventCode )
		{
			// Create process
			case CREATE_PROCESS_DEBUG_EVENT:
			{
				// Get the sub-process ID
				_dword processid = Platform::GetProcessID( mDebugEvent.u.CreateProcessInfo.hProcess );
				if ( processid == 0 )
					return _false;

				// We are creating the process
				EventCreateProcess event;
				event.mID			= processid;
				event.mHandle		= mDebugEvent.u.CreateProcessInfo.hProcess;
				event.mImageBase	= mDebugEvent.u.CreateProcessInfo.lpBaseOfImage;
				NotifyObservers( this, event );

				// Close the sub-process's image file
				Platform::CloseHandle( mDebugEvent.u.CreateProcessInfo.hFile );
			}
			break;

			// Exit the process
			case EXIT_PROCESS_DEBUG_EVENT:
			{
				// We are exiting the process
				EventExitProcess event;
				event.mID		= mDebugEvent.dwProcessId;
				event.mExitCode = mDebugEvent.u.ExitProcess.dwExitCode;
				NotifyObservers( this, event );

				// Exit the debugger when the main process exit
				if ( mDebugEvent.dwProcessId == mProcessID )
				{
					// Save the exit code of main process
					mExitCode = mDebugEvent.u.ExitProcess.dwExitCode;

					// Stop to debug process
					Platform::DebugActiveProcessStop( mProcessID );

					// Clear the main process info
					mProcessID		= 0;
					mProcessHandle	= _null;

					return _true;
				}
			}
			break;

			// Create thread
			case CREATE_THREAD_DEBUG_EVENT:
			{
				// We are creating the thread
				EventCreateThread event;
				event.mID		= mDebugEvent.dwThreadId;
				event.mHandle	= mDebugEvent.u.CreateThread.hThread;
				NotifyObservers( this, event );
			}
			break;

			// Exit thread
			case EXIT_THREAD_DEBUG_EVENT:
			{
				// We are exiting the thread
				EventExitProcess event;
				event.mID		= mDebugEvent.dwThreadId;
				event.mExitCode = mDebugEvent.u.ExitThread.dwExitCode;
				NotifyObservers( this, event );
			}
			break;

			// Load DLL
			case LOAD_DLL_DEBUG_EVENT:
			{
				// The DLL image name buffer
				_charw imagenamebuffer_unicode[512]; imagenamebuffer_unicode[0] = 0;

				// Get the image name base address
				_void* imagenameaddress = mDebugEvent.u.LoadDll.lpImageName;
				if ( imagenameaddress != _null )
				{
					// Get the process handle
					_handle processhandle = Platform::GetProcessHandle( mDebugEvent.dwProcessId );
					if ( processhandle == _null )
						return _false;

					// Get the image name string address
					_void* imagename = _null;
					if ( Platform::ReadProcessMemory( processhandle, imagenameaddress, &imagename, sizeof( _void* ) ) == _false )
						return _false;

					// Read the image name
					if ( imagename != _null )
						Platform::ReadProcessMemory( processhandle, imagename, imagenamebuffer_unicode, 512 );
				}

				// We are loading DLL
				EventLoadDLL event;
				event.mProcessID	= mDebugEvent.dwProcessId;
				event.mBaseAddress	= mDebugEvent.u.LoadDll.lpBaseOfDll;
				event.mFileName		= imagenamebuffer_unicode;
				NotifyObservers( this, event );

				// Close the DLL image file
				Platform::CloseHandle( mDebugEvent.u.LoadDll.hFile );
			}
			break;

			// Unload DLL
			case UNLOAD_DLL_DEBUG_EVENT:
			{
				// We are unloading DLL
				EventUnloadDLL event;
				event.mProcessID	= mDebugEvent.dwProcessId;
				event.mBaseAddress	= mDebugEvent.u.UnloadDll.lpBaseOfDll;
				NotifyObservers( this, event );
			}
			break;

			// Output debug string
			case OUTPUT_DEBUG_STRING_EVENT:
			{
				// Get the process handle
				_handle processhandle = Platform::GetProcessHandle( mDebugEvent.dwProcessId );
				if ( processhandle == _null )
					return _false;

				// The string buffer for output string
				_charw stringbuffer_unicode[512];

				// It's UNICODE string
				if ( mDebugEvent.u.DebugString.fUnicode )
				{
					// Get the output string bytes size in UNICODE
					_dword size = mDebugEvent.u.DebugString.nDebugStringLength * sizeof( _charw );
					if ( size == 0 )
						return _false;

					// Read the output string info
					if ( Platform::ReadProcessMemory( processhandle, mDebugEvent.u.DebugString.lpDebugStringData, stringbuffer_unicode, size ) == _false )
						return _false;
				}
				// It's ANSI string
				else
				{
					// Get the output string bytes size in ANSI
					_dword size = mDebugEvent.u.DebugString.nDebugStringLength;
					if ( size == 0 )
						return _false;

					// Read the output string info
					_chara stringbuffer_ansi[512];
					if ( Platform::ReadProcessMemory( processhandle, mDebugEvent.u.DebugString.lpDebugStringData, stringbuffer_ansi, size ) == _false )
						return _false;

					// Convert it to UNICODE string
					Platform::AnsiToUtf16( stringbuffer_unicode, 512, stringbuffer_ansi );
				}

				// We are outputting the string
				EventOutputString event;
				event.mType			= _LOG_TRACE;
				event.mString		= stringbuffer_unicode;
				event.mFileName		= L"";
				event.mLineNumber	= 0;
				NotifyObservers( this, event );
			}
			break;

			// Exception
			case EXCEPTION_DEBUG_EVENT:
			{
				// Skip for the breakpoint exception
				if ( mDebugEvent.u.Exception.ExceptionRecord.ExceptionCode != EXCEPTION_BREAKPOINT )
				{
					// If the dwFirstChance member is nonzero, this is the first time the debugger has encountered the exception. 
					// Debuggers typically handle breakpoint and single-step exceptions when they are first encountered.
					if ( mDebugEvent.u.Exception.dwFirstChance == 0 )
					{
						// We occurred exception
						EGE::Events::EventException event;
						event.mCodeID = mDebugEvent.u.Exception.ExceptionRecord.ExceptionCode;
						NotifyObservers( this, event );
					}
				}

				// Update the debug continue status
				continue_status = DBG_EXCEPTION_NOT_HANDLED;
			}
			break;
		}

		// Continue to debug event
		if ( !::ContinueDebugEvent( mDebugEvent.dwProcessId, mDebugEvent.dwThreadId, continue_status ) )
			return _false;
	}

	return _true;
}

_dword winProcessDebugger::GetExitCode( ) const
{
	return mExitCode;
}

_ubool winProcessDebugger::Run( AStringPtr modulename, AStringPtr cmdline, _dword creationflags, AStringPtr workdir, _ubool nodebugheap, _ubool fastmode )
{
	if ( nodebugheap )
	{
		// The NT kernel has a "feature" that if a process is launched under the control of a debugger it automatically switches to use debug heap routines (regardless of compiler options and etc.).
		// To prevent this, which kills our frame rate, we set the magical "_NO_DEBUG_HEAP" environment variable.
		if ( Platform::SetEnvironment( L"_NO_DEBUG_HEAP", L"1" ) == _false )
			return _false;
	}

	// Build the process creation flags
	creationflags |= _PROCESS_CREATION_DEBUG_PROCESS;

	// Get the module name
	const _chara* fixed_module_name = _null;
	if ( modulename.IsEmpty( ) == _false )
		fixed_module_name = modulename.Str( );

	// Get the working directory
	const _chara* fixed_workdir = _null;
	if ( workdir.IsEmpty( ) == _false )
		fixed_workdir = workdir.Str( );

	// Create process in ANSI mode
	if ( Platform::CreateProcess( fixed_module_name, cmdline.Str( ), creationflags, fixed_workdir, &mProcessHandle ) == _false )
		return _false;

	// Get the process ID
	mProcessID = Platform::GetProcessID( mProcessHandle );
	if ( mProcessID == 0 )
		return _false;

	// Run the process
	return RunProcess( );
}

_ubool winProcessDebugger::Run( WStringPtr modulename, WStringPtr cmdline, _dword creationflags, WStringPtr workdir, _ubool nodebugheap, _ubool fastmode )
{
	if ( nodebugheap )
	{
		// The NT kernel has a "feature" that if a process is launched under the control of a debugger it automatically switches to use debug heap routines (regardless of compiler options and etc.).
		// To prevent this, which kills our frame rate, we set the magical "_NO_DEBUG_HEAP" environment variable.
		if ( Platform::SetEnvironment( L"_NO_DEBUG_HEAP", L"1" ) == _false )
			return _false;
	}

	// Build the process creation flags
	creationflags |= _PROCESS_CREATION_DEBUG_PROCESS;

	// Get the module name
	const _charw* fixed_modulename = _null;
	if ( modulename.IsEmpty( ) == _false )
		fixed_modulename = modulename.Str( );

	// Get the working directory
	const _charw* fixed_workdir = _null;
	if ( workdir.IsEmpty( ) == _false )
		fixed_workdir = workdir.Str( );

	// Create process in UNICODE mode
	if ( Platform::CreateProcess( fixed_modulename, cmdline.Str( ), creationflags, fixed_workdir, &mProcessHandle ) == _false )
		return _false;

	// Get the process ID
	mProcessID = Platform::GetProcessID( mProcessHandle );
	if ( mProcessID == 0 )
		return _false;

	// Run the process
	return RunProcess( );
}