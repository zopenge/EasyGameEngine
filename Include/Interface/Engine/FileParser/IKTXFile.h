//! @file     IKTXFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IKTXFile
//----------------------------------------------------------------------------

class IKTXFile : public ICompressedTexFile
{
public:
	//!	The KTX header info
	//!	http://www.khronos.org/opengles/sdk/tools/KTX/file_format_spec/#2.14
	struct KTXHeaderInfo
	{
		// Header
		_byte	mIdentifier[12];
		_dword	mEndianness;
		_dword	mGLType;
		_dword	mGLTypeSize;
		_dword	mGLFormat;
		_dword	mGLInternalFormat;
		_dword	mGLBaseInternalFormat;
		_dword	mPixelWidth;
		_dword	mPixelHeight;
		_dword	mPixelDepth;
		_dword	mNumberOfArrayElements;
		_dword	mNumberOfFaces;
		_dword	mNumberOfMipmapLevels;
		_dword	mBytesOfKeyValueData;
	};

public:
	//!	Get the header info.
	//!	@param		none.
	//!	@return		The header info.
	virtual const KTXHeaderInfo& GetKTXHeader( ) const PURE;
};

}