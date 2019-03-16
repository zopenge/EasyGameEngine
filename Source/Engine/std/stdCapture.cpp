//! @file     stdCapture.cpp
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

#if _ENABLE_CAPTURE_STD_STREAM == 1

//----------------------------------------------------------------------------
// stdCapture Implementation
//----------------------------------------------------------------------------

stdCapture::stdCapture( std::streambuf* std_out_stream_buf, std::streambuf* std_err_stream_buf )
{
	EGE_ASSERT( std_out_stream_buf != _null );
	EGE_ASSERT( std_err_stream_buf != _null );

	mOldStdOut = std::cout.rdbuf( std_out_stream_buf );
	mOldStdErr = std::cerr.rdbuf( std_err_stream_buf );
}

stdCapture::~stdCapture( )
{
	std::cout.rdbuf( mOldStdOut );
	std::cerr.rdbuf( mOldStdErr );
}

#endif