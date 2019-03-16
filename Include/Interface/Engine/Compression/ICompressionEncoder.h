//! @file     ICompressionEncoder.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ICompressionEncoder
//----------------------------------------------------------------------------

class ICompressionEncoder : public IStreamProcessor
{
public:
	//!	Compression level
	enum _LEVEL
	{
		_LEVEL_DEFAULT			= 0,
		_LEVEL_BEST_SPEED		= 1,
		_LEVEL_BEST_COMPRESSION	= 2,
	};

public:
	//!	Set the compression level.
	//!	@param		level	The compression level.
	//! @return		True indicates success, false indicates failure.
	virtual _void SetLevel( _LEVEL level ) PURE;
};

}