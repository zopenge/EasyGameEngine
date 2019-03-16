//! @file     IMIDIFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IMIDIFile
//----------------------------------------------------------------------------

class IMIDIFile : public ISoundFile
{
public:
	//!	Get the buffer data.
	//!	@param		none.
	//!	@return		The buffer data.
	virtual const _byte* GetBufferData( ) const PURE;
	//!	Get the buffer size.
	//!	@param		none.
	//!	@return		The buffer size.
	virtual _dword GetBufferSize( ) const PURE;
};

}