//! @file     stdStreamPipe.cpp
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

#if _ENABLE_CAPTURE_STD_STREAM == 1

//----------------------------------------------------------------------------
// stdStreamPipe Implementation
//----------------------------------------------------------------------------

stdStreamPipe::stdStreamPipe( _dword id )
{
	mID			= id;
	mOldHandle	= ::GetStdHandle( mID );
}

stdStreamPipe::~stdStreamPipe( )
{
	::SetStdHandle( mID, mOldHandle );
}

//----------------------------------------------------------------------------
// stdTraceStreamPipe Implementation
//----------------------------------------------------------------------------

stdTraceStreamPipe::stdTraceStreamPipe( ) : BaseClass( STD_OUTPUT_HANDLE )
{
}

stdTraceStreamPipe::~stdTraceStreamPipe( )
{
}

//----------------------------------------------------------------------------
// stdErrorStreamPipe Implementation
//----------------------------------------------------------------------------

stdErrorStreamPipe::stdErrorStreamPipe( ) : BaseClass( STD_ERROR_HANDLE )
{
}

stdErrorStreamPipe::~stdErrorStreamPipe( )
{
}

#endif