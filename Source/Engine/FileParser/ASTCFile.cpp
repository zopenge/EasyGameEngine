//! @file     ASTCFile.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

#ifndef _EGE_DISABLE_ASTC_FILE_

//----------------------------------------------------------------------------
// ASTCFile Implementation
//----------------------------------------------------------------------------

ASTCFile::ASTCFile( )
{
	EGE_INIT( mASTCHeader );
}

ASTCFile::~ASTCFile( )
{
	Unload( );
}

_ubool ASTCFile::ReadCompressedBufferData( IStreamReader* stream_reader )
{
	static const _dword cGL_COMPRESSED_RGBA_ASTC_4x4_KHR    = 0x93B0;
	static const _dword cGL_COMPRESSED_RGBA_ASTC_5x4_KHR    = 0x93B1;
	static const _dword cGL_COMPRESSED_RGBA_ASTC_5x5_KHR    = 0x93B2;
	static const _dword cGL_COMPRESSED_RGBA_ASTC_6x5_KHR    = 0x93B3;
	static const _dword cGL_COMPRESSED_RGBA_ASTC_6x6_KHR    = 0x93B4;
	static const _dword cGL_COMPRESSED_RGBA_ASTC_8x5_KHR    = 0x93B5;
	static const _dword cGL_COMPRESSED_RGBA_ASTC_8x6_KHR    = 0x93B6;
	static const _dword cGL_COMPRESSED_RGBA_ASTC_8x8_KHR    = 0x93B7;
	static const _dword cGL_COMPRESSED_RGBA_ASTC_10x5_KHR   = 0x93B8;
	static const _dword cGL_COMPRESSED_RGBA_ASTC_10x6_KHR   = 0x93B9;
	static const _dword cGL_COMPRESSED_RGBA_ASTC_10x8_KHR   = 0x93BA;
	static const _dword cGL_COMPRESSED_RGBA_ASTC_10x10_KHR  = 0x93BB;
	static const _dword cGL_COMPRESSED_RGBA_ASTC_12x10_KHR  = 0x93BC;
	static const _dword cGL_COMPRESSED_RGBA_ASTC_12x12_KHR  = 0x93BD;

	// Get the block sizes
	_dword xsize	= mASTCHeader.mXSize[0] + ( mASTCHeader.mXSize[1] << 8 ) + ( mASTCHeader.mXSize[2] << 16 );
	_dword ysize	= mASTCHeader.mYSize[0] + ( mASTCHeader.mYSize[1] << 8 ) + ( mASTCHeader.mYSize[2] << 16 );
	_dword zsize	= mASTCHeader.mZSize[0] + ( mASTCHeader.mZSize[1] << 8 ) + ( mASTCHeader.mZSize[2] << 16 );
	_dword xblocks	= ( xsize + mASTCHeader.mBlockDim_x - 1 ) / mASTCHeader.mBlockDim_x;
	_dword yblocks	= ( ysize + mASTCHeader.mBlockDim_y - 1 ) / mASTCHeader.mBlockDim_y;
	_dword zblocks	= ( zsize + mASTCHeader.mBlockDim_z - 1 ) / mASTCHeader.mBlockDim_z;

	// Each block is encoded on 16 bytes, so calculate total compressed image data size.
	_dword n_bytes_to_read = xblocks * yblocks * zblocks << 4;

	// Use only 1 mipmaps
	mTextureInfo.mMipmapsNumber = 1;

	// Set the internal format
	_dword dim_x = mASTCHeader.mBlockDim_x;
	_dword dim_y = mASTCHeader.mBlockDim_y;
	if ( dim_x == 4 && dim_y == 4 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_4x4_KHR;
	else if ( dim_x == 5 && dim_y == 4 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_5x4_KHR;
	else if ( dim_x == 5 && dim_y == 5 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_5x5_KHR;
	else if ( dim_x == 6 && dim_y == 5 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_6x5_KHR;
	else if ( dim_x == 6 && dim_y == 6 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_6x6_KHR;
	else if ( dim_x == 8 && dim_y == 5 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_8x5_KHR;
	else if ( dim_x == 8 && dim_y == 6 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_8x6_KHR;
	else if ( dim_x == 8 && dim_y == 8 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_8x8_KHR;
	else if ( dim_x == 10 && dim_y == 5 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_10x5_KHR;
	else if ( dim_x == 10 && dim_y == 6 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_10x6_KHR;
	else if ( dim_x == 10 && dim_y == 8 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_10x8_KHR;
	else if ( dim_x == 10 && dim_y == 10 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_10x10_KHR;
	else if ( dim_x == 12 && dim_y == 10 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_12x10_KHR;
	else if ( dim_x == 12 && dim_y == 12 )
		mTextureInfo.mCompressedInternalFormat = cGL_COMPRESSED_RGBA_ASTC_12x12_KHR;
	else
		return _false;

//	mTextureInfo.mCompressedInternalFormat += 0x20;

	// Create decompressed buffers
	mMipmapsCompressedBufferData	= new _byte*[1];
	mFaceLODSize					= new _dword[1];

	// Set the LOD size
	mFaceLODSize[0] = n_bytes_to_read;

	// Create and load buffer data
	mMipmapsCompressedBufferData[0] = new _byte[ n_bytes_to_read ];
	stream_reader->ReadBuffer( mMipmapsCompressedBufferData[0], n_bytes_to_read );

	return _true;
}

_FILE_FORMAT ASTCFile::GetFileID( ) const
{
	return _FF_ASTC;
}

_ubool ASTCFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Read the ASTC header
	stream_reader->ReadBuffer( &mASTCHeader, sizeof( ASTCHeader ) );

	// Check the ASTC file ID
	if ( mASTCHeader.mFileID != _FILE_ID )
		return _false;

	// Decode the image pixel
	if ( HasFlags( _FLAG_HEADER_ONLY ) == _false )
	{
		if ( ReadCompressedBufferData( stream_reader ) == _false )
			return _false;
	}

	// Set the image info
	mImageWidth		= mASTCHeader.mXSize[0] + ( mASTCHeader.mXSize[1] << 8 ) + ( mASTCHeader.mXSize[2] << 16 );
	mImageHeight	= mASTCHeader.mYSize[0] + ( mASTCHeader.mYSize[1] << 8 ) + ( mASTCHeader.mYSize[2] << 16 );

	return _true;
}

_void ASTCFile::Unload( )
{
	BaseClass::Unload( );
}

#endif