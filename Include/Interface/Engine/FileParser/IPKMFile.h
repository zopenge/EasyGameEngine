//! @file     IPKMFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IPKMFile
//----------------------------------------------------------------------------

class IPKMFile : public ICompressedTexFile
{
public:
	//!	The PKM header info
	struct PKMHeaderInfo
	{
		_word	mVersion;
		_word	mDataType;
		_word	mWidth;
		_word	mHeight;
		_word	mActivedWidth;
		_word	mActivedHeight;
	};

public:
	//!	Get the header info.
	//!	@param		none.
	//!	@return		The header info.
	virtual const PKMHeaderInfo& GetPKMHeader( ) const PURE;
};

}