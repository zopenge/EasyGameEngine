//! @file     IStreamingPCMFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IStreamingPCMFile
//----------------------------------------------------------------------------

class IStreamingPCMFile : public ISoundFile
{
public:
	//!	Write PCM buffer data.
	//!	@param		size	The buffer size.
	//!	@param		buffer	The buffer data.
	//!	@return		none.
	virtual _void WriteBuffer( _dword size, const _byte* buffer ) PURE;
};

}