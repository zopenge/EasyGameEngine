// Exclude rarely-used stuff from Windows headers
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#include "windows.h"

HINSTANCE gModuleHandle = 0;

//----------------------------------------------------------------------------
// DllMain Implementation
//----------------------------------------------------------------------------

LONG __stdcall DllMain( HINSTANCE instance, DWORD reason, VOID* /*reserved*/ )
{
	if ( reason == DLL_PROCESS_ATTACH )
		gModuleHandle = instance;

	return 1;
}

//----------------------------------------------------------------------------
// SelfDelete Implementation
//----------------------------------------------------------------------------

VOID SelfDelete( )
{
	TCHAR dllname[1024];
	::GetModuleFileName( (HMODULE) gModuleHandle, dllname, 1024 );

	__asm
	{
		lea		eax, dllname
		push	0
		push	0
		push	eax
		push	ExitProcess
		push	gModuleHandle
		push	DeleteFile
		push	FreeLibrary
		ret
	}
}

//----------------------------------------------------------------------------
// Delete Implementation
//----------------------------------------------------------------------------

extern "C" __declspec( dllexport ) VOID __stdcall Delete( HINSTANCE, HINSTANCE, TCHAR* filename, LONG )
{
	while ( ::GetFileAttributes( filename ) != -1 )
	{
		::SetFileAttributes( filename, FILE_ATTRIBUTE_NORMAL );
		::DeleteFile( filename );
	}

	SelfDelete( );
}

//----------------------------------------------------------------------------
// Move Implementation
//----------------------------------------------------------------------------

extern "C" __declspec( dllexport ) VOID __stdcall Move( HINSTANCE, HINSTANCE, TCHAR* filename, LONG )
{
	TCHAR* srcfilename = 0;
	TCHAR* desfilename = 0;

	for ( LONG i = 0; filename[i] != 0; i ++ )
	{
		if ( filename[i] == '|' )
		{
			filename[i] = 0;

			srcfilename = filename;
			desfilename = filename + i + 1;
		}
	}

	while ( ::GetFileAttributes( desfilename ) != -1 )
	{
		::SetFileAttributes( desfilename, FILE_ATTRIBUTE_NORMAL );
		::DeleteFile( desfilename );
	}

	if ( ::MoveFile( srcfilename, desfilename ) == 0 )
		::CopyFile( srcfilename, desfilename, 0 );

	SelfDelete( );
}

//----------------------------------------------------------------------------
// Run Implementation
//----------------------------------------------------------------------------

extern "C" __declspec( dllexport ) VOID __stdcall Run( HINSTANCE, HINSTANCE, TCHAR* filename, LONG )
{
	PROCESS_INFORMATION	processinfo = { 0 };
	STARTUPINFOA		startupinfo = { sizeof( STARTUPINFO ) };

	startupinfo.dwFlags = STARTF_FORCEOFFFEEDBACK;

	::CreateProcessA( 0, filename, 0, 0, 0, 0, 0, 0, &startupinfo, &processinfo );

	SelfDelete( );
}

//----------------------------------------------------------------------------
// MoveAndRun Implementation
//----------------------------------------------------------------------------

extern "C" __declspec( dllexport ) VOID __stdcall MoveAndRun( HINSTANCE, HINSTANCE, TCHAR* filename, LONG )
{
	TCHAR* srcfilename = 0;
	TCHAR* desfilename = 0;

	for ( LONG i = 0; filename[i] != 0; i ++ )
	{
		if ( filename[i] == '|' )
		{
			filename[i] = 0;

			srcfilename = filename;
			desfilename = filename + i + 1;
		}
	}

	while ( ::GetFileAttributes( desfilename ) != -1 )
	{
		::SetFileAttributes( desfilename, FILE_ATTRIBUTE_NORMAL );
		::DeleteFile( desfilename );
	}

	if ( ::MoveFile( srcfilename, desfilename ) == 0 )
		::CopyFile( srcfilename, desfilename, 0 );

	PROCESS_INFORMATION	processinfo = { 0 };
	STARTUPINFOA		startupinfo = { sizeof( STARTUPINFO ) };

	startupinfo.dwFlags = STARTF_FORCEOFFFEEDBACK;

	::CreateProcessA( 0, desfilename, 0, 0, 0, 0, 0, 0, &startupinfo, &processinfo );

	SelfDelete( );
}
