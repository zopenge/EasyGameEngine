//! @file     IMediaDecoder.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IMediaDecoder
//----------------------------------------------------------------------------

class IMediaDecoder : public IDecoder
{
public:
	//!	Process buffer.
	//!	@param		block_entry		The media block entry.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ProcessBlockEntry( const IMediaFileBlockEntry* block_entry ) PURE;
};

}