//! @file     stdStreamBuf.cpp
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

#if _ENABLE_CAPTURE_STD_STREAM == 1

//----------------------------------------------------------------------------
// stdStreamBuf Implementation
//----------------------------------------------------------------------------

stdStreamBuf::stdStreamBuf( int buffer_size )
{
	if ( buffer_size > 0 )
	{
		char *ptr = new char[ buffer_size ];
		setp( ptr, ptr + buffer_size );
	}
	else
	{
		setp( 0, 0 );
	}
}

stdStreamBuf::~stdStreamBuf( )
{
	sync( );
	delete[] pbase();
}

stdStreamBuf::int_type stdStreamBuf::overflow( int_type c )
{
	sync( );

	if ( c != EOF )
	{
		if ( pbase() == epptr() )
		{
			std::string temp;
			temp += char(c);
			WriteString(temp);
		}
		else
		{
			sputc(c);
		}
	}

	return 0;
}

int stdStreamBuf::sync( )
{
	if ( pbase() != pptr() )
	{
		int len = int(pptr() - pbase());
		std::string temp(pbase(), len);
		WriteString(temp);
		setp(pbase(), epptr());
	}

	return 0;
}

//----------------------------------------------------------------------------
// stdTraceStreamBuf Implementation
//----------------------------------------------------------------------------

stdTraceStreamBuf::stdTraceStreamBuf( int buffer_size ) : BaseClass( buffer_size )
{
}

stdTraceStreamBuf::~stdTraceStreamBuf( )
{
}

_void stdTraceStreamBuf::WriteString( const std::string& message )
{
	ALOG_TRACE( message.c_str( ) );
}

//----------------------------------------------------------------------------
// stdErrorStreamBuf Implementation
//----------------------------------------------------------------------------

stdErrorStreamBuf::stdErrorStreamBuf( int buffer_size ) : BaseClass( buffer_size )
{
}

stdErrorStreamBuf::~stdErrorStreamBuf( )
{
}

_void stdErrorStreamBuf::WriteString( const std::string& message )
{
	ALOG_ERROR( message.c_str( ) );
}

#endif