//! @file     stdCapture.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// stdCapture
//----------------------------------------------------------------------------

class stdCapture
{
private:
	std::streambuf* mOldStdOut;
	std::streambuf* mOldStdErr;

public:
	stdCapture( std::streambuf* std_out_stream_buf, std::streambuf* std_err_stream_buf );
	~stdCapture( );
};

//----------------------------------------------------------------------------
// stdCapture Implementation
//----------------------------------------------------------------------------

}