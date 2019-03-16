//! @file     ASTCFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ASTCHeader
//----------------------------------------------------------------------------

struct ASTCHeader
{
	_dword	mFileID;
	_byte	mBlockDim_x;
	_byte	mBlockDim_y;
	_byte	mBlockDim_z;
	_byte	mXSize[3];
	_byte	mYSize[3];
	_byte	mZSize[3];
};

//----------------------------------------------------------------------------
// ASTCFile
//----------------------------------------------------------------------------

class ASTCFile : public INTERFACE_COMPRESSEDTEXFILE_IMPL( IASTCFile )
{
public:
	//!	The ASTC file ID
	enum { _FILE_ID = EGE_ID( 0x13, 0xAB, 0xA1, 0x5C ) };

private:
	typedef INTERFACE_COMPRESSEDTEXFILE_IMPL( IASTCFile ) BaseClass;

private:
	//!	The *.ASTC file header
	ASTCHeader	mASTCHeader;

private:
	//!	Read compressed buffer data.
	_ubool ReadCompressedBufferData( IStreamReader* stream_reader );

public:
	ASTCFile( );
	virtual ~ASTCFile( );
	
// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// IASTCFile Interface
public:
};

}