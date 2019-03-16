//! @file     WEBPFile.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// WEBPFile Helpful Structures Implementation
//----------------------------------------------------------------------------

struct WebPFilePars
{
	WebPDecoderConfig	mConfig;
	WebPData			mData;

	WebPFilePars( )
	{
	}
	~WebPFilePars( )
	{
	}
};

//----------------------------------------------------------------------------
// WEBPFile Implementation
//----------------------------------------------------------------------------

WEBPFile::WEBPFile( )
{
}

WEBPFile::~WEBPFile( )
{
	Unload( );
}

_FILE_FORMAT WEBPFile::GetFileID( ) const
{
	return _FF_WEBP;
}

_ubool WEBPFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Initialize decode configure
	WebPFilePars webp_pars;
	if ( !::WebPInitDecoderConfig( &webp_pars.mConfig ) )
	{
		WLOG_ERROR( L"Initialize WebP decoder configure failed" );
		return _false;
	}

	// Read image buffer
	webp_pars.mData.bytes	= stream_reader->GetBuffer( );
	webp_pars.mData.size	= stream_reader->GetSize( );

	// Get the image info
	if ( !::WebPGetInfo( webp_pars.mData.bytes, webp_pars.mData.size, (int*) &mImageWidth, (int*) &mImageHeight ) )
	{
		WLOG_ERROR( L"Get WebP image info failed" );
		return _false;
	}

	// Get the image feature
	WebPBitstreamFeatures* const webp_bitstream = &webp_pars.mConfig.input;
	if ( ::WebPGetFeatures( webp_pars.mData.bytes, webp_pars.mData.size, webp_bitstream ) != VP8_STATUS_OK )
	{
		WLOG_ERROR( L"Get WebP feature info failed" );
		return _false;
	}

	// We can not support the animation image
	if ( webp_bitstream->has_animation )
	{
		WLOG_ERROR( L"We can not support the animation WebP image" );
		return _false;
	}

	// Get the decode output buffer
	WebPDecBuffer* const webp_output_buffer = &webp_pars.mConfig.output;
	EGE_ASSERT( webp_output_buffer != _null );

	// Set the color space and channels
	_dword channels = 0;
	if ( webp_bitstream->has_alpha )
	{
		mImagePixelFormat				= _PF_A8R8G8B8;
		webp_output_buffer->colorspace	= MODE_RGBA;
		channels						= 4;
	}
	else
	{
		mImagePixelFormat				= _PF_R8G8B8;
		webp_output_buffer->colorspace	= MODE_RGB;
		channels						= 3;
	}

	// Get the image pitch
	mImagePitch = Math::UpperArrange( mImageWidth * channels, channels );

	// Check whether decode pixel buffer
	if ( HasFlags( _FLAG_HEADER_ONLY ) == _false )
	{
		// Create pixel buffer
		mImagePixelBuffer = new _byte[ mImagePitch * mImageHeight ];

		// Initialize output buffer
		webp_output_buffer->is_external_memory	= _true;
		webp_output_buffer->private_memory		= mImagePixelBuffer;
		webp_output_buffer->u.RGBA.rgba			= mImagePixelBuffer;
		webp_output_buffer->u.RGBA.stride		= (int)mImagePitch;
		webp_output_buffer->u.RGBA.size			= mImagePitch * mImageHeight;

		// Start to decode
		VP8StatusCode webp_status_code = ::WebPDecode( webp_pars.mData.bytes, webp_pars.mData.size, &webp_pars.mConfig );
		if ( webp_status_code != VP8_STATUS_OK )
		{
			WLOG_ERROR_1( L"Image decode failed(err:%d)", (_dword) webp_status_code );
			return _false;
		}
	}

	return _true;
}

_void WEBPFile::Unload( )
{
	BaseClass::Unload( );
}