//! @file     RHIStatsTexture2D.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RHIStatsTexture2D
//----------------------------------------------------------------------------

class RHIStatsTexture2D : public RHIStatsBase< Texture2DRHI >
{
private:
	typedef RHIStatsBase< Texture2DRHI > BaseClass;

private:
	_ubool	mIsCompressedTexture;
	_dword	mTextureSizeInBytes;

public:
	RHIStatsTexture2D( Texture2DRHI* resource );
	virtual ~RHIStatsTexture2D( );
};

}