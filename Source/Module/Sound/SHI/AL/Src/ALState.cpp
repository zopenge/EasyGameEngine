//! @file     ALState.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2011 LiCode's Union.

#include "EGESound.h"

//----------------------------------------------------------------------------
// AL-Error Check Implementation
//----------------------------------------------------------------------------

_ubool EGE::CheckALError( )
{
	ALenum error = alGetError( );
	if ( error == AL_NO_ERROR )
		return _true;

	// Get the error type string
	WStringPtr string;
	switch ( error )
	{
		case AL_INVALID_NAME:		string = L"Invalid Name"; break;
		case AL_INVALID_ENUM:		string = L"Invalid Enum"; break;
		case AL_INVALID_VALUE:		string = L"Invalid Value"; break;
		case AL_INVALID_OPERATION:	string = L"Invalid Operation"; break;
		case AL_OUT_OF_MEMORY:		string = L"Out Of Memory"; break;
		default:
			string = L"Error";
			break;
	}

	// Output the error string
	ENABLE_STRINGBUFFER_MACROS_UNICODE( );
	gSoundModule->OutputString( _MESSAGE_ERROR, FORMAT_WSTRING_2( L"AL error code: 0x%x[%s]", (_dword) error, string.Str( ) ) );
	EGE_ASSERT( 0 );

	return _false;
}