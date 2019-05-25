//! @file     PVRTexFile.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//!	The PVR pixel format ID.
const _dword cPVRTC_2bpp_RGB	= 0;
const _dword cPVRTC_2bpp_RGBA	= 1;
const _dword cPVRTC_4bpp_RGB	= 2;
const _dword cPVRTC_4bpp_RGBA	= 3;
//!	The ETC pixel format ID.
const _dword cETC1_RGB8			= 6;
const _dword cETC2_RGBA8		= 23;

//----------------------------------------------------------------------------
// PVRTexFile Implementation
//----------------------------------------------------------------------------

PVRTexFile::PVRTexFile( )
{
	EGE_INIT( mHeaderInfo );
}

PVRTexFile::~PVRTexFile( )
{
	Unload( );
}

_dword PVRTexFile::GetGLCompressedImageType( _qword pixel_format )
{
	static const _dword cGL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG		= 0x8C00;
	static const _dword cGL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG		= 0x8C01;
	static const _dword cGL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG	= 0x8C02;
	static const _dword cGL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG	= 0x8C03;
	
	static const _dword cGL_ETC1_RGB8_OES						= 0x8D64;
	static const _dword cGL_COMPRESSED_RGBA8_ETC2_EAC			= 0x9278;

	_dword pvrtc_type = pixel_format & 0x00000000FFFFFFFFull;
	switch ( pvrtc_type )
	{
		// PVRTC
		case cPVRTC_2bpp_RGB:	return cGL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
		case cPVRTC_2bpp_RGBA:	return cGL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
		case cPVRTC_4bpp_RGB:	return cGL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
		case cPVRTC_4bpp_RGBA:	return cGL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;

		// ETC
		case cETC1_RGB8:		return cGL_ETC1_RGB8_OES;
		case cETC2_RGBA8:		return cGL_COMPRESSED_RGBA8_ETC2_EAC;

		default:
			break;
	}
	
	return 0;
}

_PIXEL_FORMAT PVRTexFile::GetCompressedPixelFormat( _qword pixel_format )
{
	_dword pvrtc_type = pixel_format & 0x00000000FFFFFFFFull;
	switch ( pvrtc_type )
	{
		// PVRTC
		case cPVRTC_2bpp_RGB:	return _PF_RGB_PVRTC_2BPP;
		case cPVRTC_2bpp_RGBA:	return _PF_RGBA_PVRTC_2BPP;
		case cPVRTC_4bpp_RGB:	return _PF_RGB_PVRTC_4BPP;
		case cPVRTC_4bpp_RGBA:	return _PF_RGBA_PVRTC_4BPP;

		// ETC
		case cETC1_RGB8:		return _PF_ETC1_RGB8;
		case cETC2_RGBA8:		return _PF_ETC2_RGBA8;

		default:
			break;
	}
	
	return _PF_UNKNOWN;
}

_dword PVRTexFile::GetBitsPerPixel( _qword pixel_format )
{
	switch ( pixel_format )
	{
		case cPVRTC_4bpp_RGB:
		case cPVRTC_4bpp_RGBA:
		case cETC1_RGB8:
			return 4;

		case cETC2_RGBA8:
			return 8;

		case cPVRTC_2bpp_RGB:
		case cPVRTC_2bpp_RGBA:
			return 2;

		default:
			EGE_ASSERT( 0 );
			break;
	}

	return 0;
}

_void PVRTexFile::GetMinDims( _qword pixel_format, _dword& min_x, _dword& min_y, _dword& min_z )
{
	switch ( pixel_format )
	{
		case cPVRTC_4bpp_RGB:
		case cPVRTC_4bpp_RGBA:
			min_x = 8;
			min_y = 8;
			min_z = 1;
			break;

		case cPVRTC_2bpp_RGB:
		case cPVRTC_2bpp_RGBA:
			min_x = 16;
			min_y = 8;
			min_z = 1;
			break;

		case cETC1_RGB8:
		case cETC2_RGBA8:
			min_x = 4;
			min_y = 4;
			min_z = 1;
			break;

		default:
			EGE_ASSERT( 0 );
			break;
	}
}

_ubool PVRTexFile::ReadHeaderInfo( IStreamReader* stream_reader )
{
	// Load the version
	stream_reader->ReadDword( mHeaderInfo.mVersion );
	if ( mHeaderInfo.mVersion != _FILE_ID )
		return _false;

	// Load the flags
	stream_reader->ReadDword( mHeaderInfo.mFlags );
	
	// Load the pixel format
	stream_reader->ReadQword( mHeaderInfo.mPixelFormat );

	// Load the color space
	stream_reader->ReadDword( mHeaderInfo.mColourSpace );

	// Load the channel type
	stream_reader->ReadDword( mHeaderInfo.mChannelType );

	// Load the height, width and depth
	stream_reader->ReadDword( mHeaderInfo.mHeight );
	stream_reader->ReadDword( mHeaderInfo.mWidth );
	stream_reader->ReadDword( mHeaderInfo.mDepth );
	if ( mHeaderInfo.mHeight == 0 || mHeaderInfo.mWidth == 0 || mHeaderInfo.mDepth == 0 )
		return _false;

	// Load the surfaces and faces number
	stream_reader->ReadDword( mHeaderInfo.mNumSurfaces );
	stream_reader->ReadDword( mHeaderInfo.mNumFaces );
	if ( mHeaderInfo.mNumSurfaces == 0 || mHeaderInfo.mNumFaces == 0 )
		return _false;

	// Load the mipmaps count
	stream_reader->ReadDword( mHeaderInfo.mMipmapCount );
	if ( mHeaderInfo.mMipmapCount == 0 )
		return _false;

	// Load the meta-size
	stream_reader->ReadDword( mHeaderInfo.mMetaDataSize );
	
	return _true;
}

_void PVRTexFile::JumpMetaDataSection( IStreamReader* stream_reader )
{
	if ( mHeaderInfo.mMetaDataSize > 0 )
		stream_reader->Seek( _SEEK_CURRENT, mHeaderInfo.mMetaDataSize );
}

_ubool PVRTexFile::BuildTextureInfo( )
{
	// Get the GL compressed internal format
	mTextureInfo.mCompressedInternalFormat = GetGLCompressedImageType( mHeaderInfo.mPixelFormat );
	if ( mTextureInfo.mCompressedInternalFormat == 0 )
		return _false;

	// Get the compressed pixel format
	mTextureInfo.mCompressedPixelFormat = GetCompressedPixelFormat( mHeaderInfo.mPixelFormat );
	if ( mTextureInfo.mCompressedPixelFormat == _PF_UNKNOWN )
		return _false;

	// Get the mipmaps number
	mTextureInfo.mMipmapsNumber	= mHeaderInfo.mMipmapCount;
	EGE_ASSERT( mTextureInfo.mMipmapsNumber != 0 );

	return _true;
}

_ubool PVRTexFile::ReadCompressedBufferData( IStreamReader* stream_reader )
{
	// Get the bits per pixel
	_dword bits_per_pixel = GetBitsPerPixel( mHeaderInfo.mPixelFormat );
	EGE_ASSERT( bits_per_pixel != 0 );
	
	// The smallest divisible sizes for a pixel format
	_dword smallest_width	= 1;
	_dword smallest_height	= 1;
	_dword smallest_depth	= 1;
	
	// Check whether it's compressed texture
	_ubool is_compressed_texture = EGE_BOOLEAN( !(mHeaderInfo.mPixelFormat & 0xFFFFFFFF00000000ull) );
	
	// If the pixel format is compressed, get the pixel format's minimum dimensions
	if ( is_compressed_texture )
		GetMinDims( mHeaderInfo.mPixelFormat, smallest_width, smallest_height, smallest_depth );
	
	// Allocate texture data and size for mipmaps
	mMipmapsCompressedBufferData	= new _byte*[mHeaderInfo.mMipmapCount];
	mFaceLODSize					= new _dword[mHeaderInfo.mMipmapCount];

	// Get the texture data size from mipmaps
	for ( _dword i = 0; i < mHeaderInfo.mMipmapCount; i ++ )
	{
		// Get the dimensions of the current MIP Map level.
		_dword width	= Math::Max< _dword >( 1, mHeaderInfo.mWidth >> i );
		_dword height	= Math::Max< _dword >( 1, mHeaderInfo.mHeight >> i );
		_dword depth	= Math::Max< _dword >( 1, mHeaderInfo.mDepth >> i );
		
		// If pixel format is compressed, the dimensions need to be padded.
		if ( is_compressed_texture )
		{
			width	+= ((-1 * width) % smallest_width);
			height	+= ((-1 * height) % smallest_height);
			depth	+= ((-1 * depth) % smallest_depth);
		}
		
		// Add the current MIP Map's data size to the total.
		mFaceLODSize[i] = (bits_per_pixel * width * height * depth) / 8;
		if ( mFaceLODSize[i] == 0 )
			return _false;

		// Create and load buffer data
		mMipmapsCompressedBufferData[i] = new _byte[ mFaceLODSize[i] ];
		stream_reader->ReadBuffer( mMipmapsCompressedBufferData[i], mFaceLODSize[i] );
	}

	return _true;
}

_ubool PVRTexFile::OnSaveToFile( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, IStreamWriter* stream_writer ) const
{
	return _true;
}

_FILE_FORMAT PVRTexFile::GetFileID( ) const
{
	return _FF_PVR_TEX;
}

_ubool PVRTexFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );
	
	// Read header info
	if ( ReadHeaderInfo( stream_reader ) == _false )
		return _false;

	// Jump the meta data section
	JumpMetaDataSection( stream_reader );
	
	// Build texture info
	if ( BuildTextureInfo( ) == _false )
		return _false;

	// Decode the image pixel
	if ( HasFlags( _FLAG_HEADER_ONLY ) == _false )
	{
		if ( ReadCompressedBufferData( stream_reader ) == _false )
			return _false;
	}

	// Set the image info
	mImageWidth		= mHeaderInfo.mWidth;
	mImageHeight	= mHeaderInfo.mHeight;

	return _true;
}

_void PVRTexFile::Unload( )
{
	EGE_INIT( mHeaderInfo );

	BaseClass::Unload( );
}

_ubool PVRTexFile::Create( _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _byte* pixelbuffer )
{
	if ( width == 0 || height == 0 )
		return _false;

	return _true;
}

const IPVRTCFile::PVRTexHeaderInfo& PVRTexFile::GetPVRTexHeader( ) const
{
	return mHeaderInfo;
}