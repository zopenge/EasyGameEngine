//! @file     IDDSFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IDDSFile
//----------------------------------------------------------------------------

class IDDSFile : public ICompressedTexFile
{
public:
	//!	DXT version
	enum _DXT_VERSION
	{
		_DXT_VERSION_UNKNOWN,
		_DXT_VERSION_1,
		_DXT_VERSION_3,
		_DXT_VERSION_5,
	};

public:
	//!	Get the DXT version.
	//!	@param		none.
	//!	@return		The DXT version.
	virtual _DXT_VERSION GetDXTVersion( ) const PURE;
	//!	Get the mip-maps level.
	//!	@param		none.
	//!	@return		The mip-maps level.
	virtual _dword GetMipmapLevel( ) const PURE;

	//!	Get the compressed image buffer.
	//!	@param		none.
	//!	@return		The compressed image buffer.
	virtual const _byte* GetCompressedImageBuffer( ) const PURE;
};

}