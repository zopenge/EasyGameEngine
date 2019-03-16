//! @file     KTXFile.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// KTXFile Implementation
//----------------------------------------------------------------------------

KTXFile::KTXFile( )
{
	EGE_INIT( mHeaderInfo );
}

KTXFile::~KTXFile( )
{
	Unload( );
}

_ubool KTXFile::CheckKTXHeaderInfo( ) const
{
	// Compare identifier, is this a KTX file?
	_byte identifier_reference[12] = { 0xAB, 0x4B, 0x54, 0x58, 0x20, 0x31, 0x31, 0xBB, 0x0D, 0x0A, 0x1A, 0x0A };
	if ( EGE_MEM_CMP( mHeaderInfo.mIdentifier, identifier_reference, sizeof( identifier_reference ) ) != 0 )
		return _false;

	// Check size and depth
	if ( (mHeaderInfo.mPixelWidth == 0) || (mHeaderInfo.mPixelDepth > 0 && mHeaderInfo.mPixelHeight == 0 ) )
	{
		// Texture must have width
		// Texture must have height if it has depth
		return _false; 
	}

	// We only support one face texture
	if ( mHeaderInfo.mNumberOfFaces != 1 )
		return _false;

	// We only support 1 texture
	if ( mHeaderInfo.mNumberOfArrayElements > 0 )
		return _false;

	// Check mip levels
	_dword max_dim = MAX( MAX( mHeaderInfo.mPixelWidth, mHeaderInfo.mPixelHeight ), mHeaderInfo.mPixelDepth );
	if ( max_dim < ((_dword)1 << (mHeaderInfo.mNumberOfMipmapLevels - 1)) )
	{
		// Can't have more mip levels than 1 + log2(max(width, height, depth))
		return _false;
	}

	return _true;
}

_ubool KTXFile::BuildTextureHeader( )
{
	// Set the compressed flag
	if ( mHeaderInfo.mGLType == 0 || mHeaderInfo.mGLFormat == 0 )
	{
		if ( mHeaderInfo.mGLType + mHeaderInfo.mGLFormat != 0 )
		{
			// Either both or none of glType, glFormat must be zero
			return _false;
		}

		// It's compressed texture
		mTextureInfo.mCompressedInternalFormat = mHeaderInfo.mGLInternalFormat;
	}
	else
	{
		// It's un-compressed texture
		mTextureInfo.mUncompressedInternalFormat = mHeaderInfo.mGLBaseInternalFormat;
	}

	// Set the data type
	mTextureInfo.mDataType = mHeaderInfo.mGLType;

	// Set the mipmaps number
	mTextureInfo.mMipmapsNumber	= mHeaderInfo.mNumberOfMipmapLevels;

	// Set the pixel format
	mTextureInfo.mCompressedPixelFormat = _PF_ETC1_RGB8;

	return _true;
}

_ubool KTXFile::ReadMipmapsCompressedBufferData( IStreamReader* stream_reader )
{
	mMipmapsCompressedBufferData	= new _byte*[ mHeaderInfo.mNumberOfMipmapLevels ];
	mFaceLODSize					= new _dword[ mHeaderInfo.mNumberOfMipmapLevels ];

	// Read the compressed buffer data
	for ( _dword level = 0; level < mHeaderInfo.mNumberOfMipmapLevels; level ++ )
	{
//		_dword pixel_width  = MAX(1, mHeaderInfo.mPixelWidth  >> level);
//		_dword pixel_height = MAX(1, mHeaderInfo.mPixelHeight >> level);
//		_dword pixel_depth  = MAX(1, mHeaderInfo.mPixelDepth  >> level);

		// Read the face LOD size
		stream_reader->ReadDword( mFaceLODSize[level] );
		//if (header.endianness == KTX_ENDIAN_REF_REV) {
		//	_ktxSwapEndian32(&faceLodSize, 1);
		//}
		
		// Calculate the LOD size
		_dword face_lod_size_rounded = (mFaceLODSize[level] + 3) & ~(_dword)3;

		// Create and load buffer data
		mMipmapsCompressedBufferData[level] = new _byte[ face_lod_size_rounded ];
		stream_reader->ReadBuffer( mMipmapsCompressedBufferData[level], face_lod_size_rounded );

		///* Perform endianness conversion on texture data */
		//if (header.endianness == KTX_ENDIAN_REF_REV && header.glTypeSize == 2) {
		//	_ktxSwapEndian16((khronos_uint16_t*)data, faceLodSize / 2);
		//}
		//else if (header.endianness == KTX_ENDIAN_REF_REV && header.glTypeSize == 4) {
		//	_ktxSwapEndian32((khronos_uint32_t*)data, faceLodSize / 4);
		//}
	}

	return _true;
}

_ubool KTXFile::OnSaveToFile( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, IStreamWriter* stream_writer ) const
{
	return _true;
}

_FILE_FORMAT KTXFile::GetFileID( ) const
{
	return _FF_KTX;
}

_ubool KTXFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Load KTX header info
	stream_reader->ReadBuffer( &mHeaderInfo, sizeof( KTXHeaderInfo ) );

	// Check KTX header info
	if ( CheckKTXHeaderInfo( ) == _false )
		return _false;

	// Build texture header info
	if ( BuildTextureHeader( ) == _false )
		return _false;

	// Skip key/value metadata
	stream_reader->Seek( _SEEK_CURRENT, (_int)mHeaderInfo.mBytesOfKeyValueData );

	// Decode the image pixel
	if ( HasFlags( _FLAG_HEADER_ONLY ) == _false )
	{
		if ( ReadMipmapsCompressedBufferData( stream_reader ) == _false )
			return _false;
	}

	// Set the image info
	mImageWidth		= mHeaderInfo.mPixelWidth;
	mImageHeight	= mHeaderInfo.mPixelHeight;

	return _true;
}

_void KTXFile::Unload( )
{
	EGE_INIT( mHeaderInfo );

	BaseClass::Unload( );
}

_ubool KTXFile::Create( _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _byte* pixelbuffer )
{
	if ( width == 0 || height == 0 )
		return _false;

	return _true;
}

const IKTXFile::KTXHeaderInfo& KTXFile::GetKTXHeader( ) const
{
	return mHeaderInfo;
}