//! @file     PKMFile.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Helpful Enumerations Implementation
//----------------------------------------------------------------------------

enum 
{ 
	ETC1_RGB_NO_MIPMAPS,
	ETC2PACKAGE_RGB_NO_MIPMAPS,
	ETC2PACKAGE_RGBA_NO_MIPMAPS_OLD,
	ETC2PACKAGE_RGBA_NO_MIPMAPS,
	ETC2PACKAGE_RGBA1_NO_MIPMAPS,
	ETC2PACKAGE_R_NO_MIPMAPS,
	ETC2PACKAGE_RG_NO_MIPMAPS,
	ETC2PACKAGE_R_SIGNED_NO_MIPMAPS,
	ETC2PACKAGE_RG_SIGNED_NO_MIPMAPS,
	ETC2PACKAGE_sRGB_NO_MIPMAPS,
	ETC2PACKAGE_sRGBA_NO_MIPMAPS,
	ETC2PACKAGE_sRGBA1_NO_MIPMAPS
};

enum 
{
	MODE_COMPRESS, 
	MODE_UNCOMPRESS, 
	MODE_PSNR
};

enum 
{
	SPEED_SLOW, 
	SPEED_FAST, 
	SPEED_MEDIUM
};

enum 
{
	METRIC_PERCEPTUAL, 
	METRIC_NONPERCEPTUAL
};

enum 
{
	CODEC_ETC, 
	CODEC_ETC2
};

//----------------------------------------------------------------------------
// PKMFile Implementation
//----------------------------------------------------------------------------

PKMFile::PKMFile( )
{
	EGE_INIT( mHeaderInfo );
}

PKMFile::~PKMFile( )
{
	Unload( );
}

_ubool PKMFile::OnSaveToFile( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, IStreamWriter* stream_writer ) const
{
	return _true;
}

_FILE_FORMAT PKMFile::GetFileID( ) const
{
	return _FF_PKM;
}

_ubool PKMFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Check the file ID
	_dword file_id = 0;
	stream_reader->ReadDword( file_id );
	if ( file_id != _FILE_ID )
		return _false;

	// Load PKM header info
	stream_reader->ReadWord( mHeaderInfo.mVersion );
	stream_reader->ReadWord( mHeaderInfo.mDataType );
	stream_reader->ReadWord( mHeaderInfo.mWidth ); 
	stream_reader->ReadWord( mHeaderInfo.mHeight ); 
	stream_reader->ReadWord( mHeaderInfo.mActivedWidth ); 
	stream_reader->ReadWord( mHeaderInfo.mActivedHeight ); 

	// Convert big endian to little endian
	mHeaderInfo.mDataType		= Math::BSwap16( mHeaderInfo.mDataType );
	mHeaderInfo.mWidth			= Math::BSwap16( mHeaderInfo.mWidth );
	mHeaderInfo.mHeight			= Math::BSwap16( mHeaderInfo.mHeight );
	mHeaderInfo.mActivedWidth	= Math::BSwap16( mHeaderInfo.mActivedWidth );
	mHeaderInfo.mActivedHeight	= Math::BSwap16( mHeaderInfo.mActivedHeight );

	// We only support the ETC1
	if ( mHeaderInfo.mVersion == 0x3031 )
	{
		if ( mHeaderInfo.mDataType != ETC1_RGB_NO_MIPMAPS )
			return _false;
	}

	// Initialize the texture info
	mTextureInfo.mMipmapsNumber				= 1;
	mTextureInfo.mCompressedInternalFormat	= 0x8D64; // #define GL_ETC1_RGB8_OES 0x8D64

	// Get the remain size of compressed buffer data
	_dword size			= stream_reader->GetSize( );
	_dword offset		= stream_reader->GetOffset( );
	_dword remain_size	= size - offset;
	if ( remain_size == 0 )
		return _false;

	// Create and read the compressed buffer data
	mMipmapsCompressedBufferData	= new _byte*[ mTextureInfo.mMipmapsNumber ];
	mMipmapsCompressedBufferData[0] = new _byte[ remain_size ];
	stream_reader->ReadBuffer( mMipmapsCompressedBufferData, remain_size );

	//GLuint height = etc_texture[1];
	//GLuint levels = etc_texture[3];
	//char* data = (char*) &etc_texture[13];
	//for (int level = 0; level < levels; ++level)
	//{
	//	// Calculate mipmap byte size based on 4x4 blocks, 8 bytes each
	//	GLuint size = 8 * ((width + 3) >> 2) * ((height + 3) >> 2);
	//	glCompressedTexImage2D(GL_TEXTURE_2D, level, GL_ETC1_RGB8_OES, width, height, 0, size, data);
	//	data += size;
	//	width = MAX(1, width >> 1);
	//	height = MAX(1, height >> 1;
	//}

	return _true;
}

_void PKMFile::Unload( )
{
	BaseClass::Unload( );

	EGE_INIT( mHeaderInfo );
}

_ubool PKMFile::Create( _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _byte* pixelbuffer )
{
	if ( width == 0 || height == 0 )
		return _false;

	return _true;
}

const IPKMFile::PKMHeaderInfo& PKMFile::GetPKMHeader( ) const
{
	return mHeaderInfo;
}