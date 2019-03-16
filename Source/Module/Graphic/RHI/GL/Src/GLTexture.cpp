//! @file     GLTexture.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLDrv-Texture Helpful Functions Implementation
//----------------------------------------------------------------------------

//!	Get the min filter of texture.
static GLint GetGLMinFilter( _dword mipmaps, GLint filter )
{
	if ( mipmaps == 1 )
	{
		if ( filter == GL_NEAREST_MIPMAP_LINEAR )
			return GL_NEAREST;
		else
			return GL_LINEAR;
	}

	return filter;
}

//! Create compressed surface of texture cube.
static _ubool CreateCompressedSurfaceOfTextureCube( const ICompressedTexFile* tex_file, _dword level, _dword& size_in_bytes )
{
	// Get the compressed texture info
	const ICompressedTexFile::TextureInfo& texture_info = tex_file->GetTextureInfo( );

	// Create surface with mipmaps
	for ( _dword mip_index = 0; mip_index < texture_info.mMipmapsNumber; mip_index ++ )
	{
		// Get the mipmaps info
		_dword pixel_width = 0, pixel_height = 0, image_size = 0;
		const _byte* pixel_buffer = tex_file->GetMipmapsPixelBufferData( mip_index, &pixel_width, &pixel_height, &image_size );
		if ( pixel_buffer == _null )
			return _false;

		// It's compressed texture
		if ( texture_info.mCompressedInternalFormat != 0 )
		{
			GL_CHECK_ERROR( __glCompressedTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + level, mip_index, texture_info.mCompressedInternalFormat, pixel_width, pixel_height, 0, image_size, pixel_buffer ) );
		}
		// It's uncompressed texture
		else
		{
			GL_CHECK_ERROR( __glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + level, mip_index, texture_info.mUncompressedInternalFormat, pixel_width, pixel_height, 0, texture_info.mUncompressedInternalFormat, texture_info.mDataType, pixel_buffer ) );
		}

		// Update the size in bytes of texture
		size_in_bytes += image_size;
	}

	return _true;
}

//!	Create compressed texture 2D.
static GLTexture2D* CreateCompressedTexture2D( ICompressedTexFile* tex_file, WStringPtr res_name, _ubool is_dynamic )
{
	// Get the compressed texture info
	const ICompressedTexFile::TextureInfo& texture_info = tex_file->GetTextureInfo( );

	// Show compressed texture info
	WLOG_TRACE_2( L"Create 'res: %s, type: %d' compressed texture 2D", res_name.Str( ), texture_info.mCompressedInternalFormat);

	// Generate texture ID
	GLuint textureid = 0;
	GL_CHECK_ERROR( __glGenTextures( 1, &textureid ) );

	// Active the texture slot
	GLCachedSetActiveTexture( 0 );

	// Bind the texture
	GLCachedBindTexture( GL_TEXTURE_2D, textureid );

	// Set the texture sampler state
	GLSamplerStateInfo samplerstate( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, samplerstate.mAddressU ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, samplerstate.mAddressV ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, samplerstate.mMagFilter ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetGLMinFilter( texture_info.mMipmapsNumber, samplerstate.mMinFilter ) ) );
#if (_OPENGLES_ == 0)
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, samplerstate.mAddressW ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0 ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, texture_info.mMipmapsNumber - 1 ) );
#endif

	// The size in bytes
	_dword size_in_bytes = 0;

	// Build texture images
	for ( _dword mip_index = 0; mip_index < texture_info.mMipmapsNumber; mip_index ++ )
	{
		// Get the mipmaps info
		_dword pixel_width = 0, pixel_height = 0, image_size = 0;
		const _byte* pixels = tex_file->GetMipmapsPixelBufferData( mip_index, &pixel_width, &pixel_height, &image_size );
		if ( pixels == _null )
			return _null;

		// It's compressed texture
		if ( texture_info.mCompressedInternalFormat != 0 )
		{
			GL_CHECK_ERROR( __glCompressedTexImage2D( GL_TEXTURE_2D, mip_index, texture_info.mCompressedInternalFormat, pixel_width, pixel_height, 0, image_size, pixels ) );
		}
		// It's uncompressed texture
		else
		{
			GL_CHECK_ERROR( __glTexImage2D( GL_TEXTURE_2D, mip_index, texture_info.mCompressedInternalFormat, pixel_width, pixel_height, 0, texture_info.mUncompressedInternalFormat, texture_info.mDataType, pixels ) );
		}

		// Update the size in bytes of texture
		size_in_bytes += image_size;
	}

	// Create texture 2D
	GLTexture2D* texture = new GLTexture2D( );
	texture->InitTex( res_name, textureid, GL_TEXTURE_2D, texture_info.mCompressedInternalFormat, texture_info.mDataType, size_in_bytes, texture_info.mMipmapsNumber, 
		texture_info.mCompressedPixelFormat, PointU( tex_file->GetWidth( ), tex_file->GetHeight( ) ), samplerstate, (const _byte*) _null, is_dynamic );

	// Restore the texture on stage 0
	if ( gGLCachedState.mTextures[0].mTarget != GL_NONE )
	{
		GLCachedBindTexture( gGLCachedState.mTextures[0].mTarget, gGLCachedState.mTextures[0].mResource );
	}
	// Unbind the texture
	else
	{
		GLCachedBindTexture( GL_TEXTURE_2D, 0 );
	}

	return texture;
}

//----------------------------------------------------------------------------
// GLDrv-Texture Implementation
//----------------------------------------------------------------------------

const GPUTextureInfoRHI& GLDrv::GetGPUTextureInfo( )
{
	return GLInfo::GetInstance( ).GetTextureInfo( );
}

TextureCubeRHIPassRef GLDrv::CreateTextureCube( WStringPtr res_name, _dword nummips, const TextureCubeWithMipmapsRHI& mipmaps_info )
{
	// Generate texture ID
	GLuint textureid = 0;
	GL_CHECK_ERROR( __glGenTextures( 1, &textureid ) );

	// Active the texture slot
	GLCachedSetActiveTexture( 0 );

	// Bind the texture
	GLCachedBindTexture( GL_TEXTURE_CUBE_MAP, textureid );

	// Set the texture sampler state
	GLSamplerStateInfo samplerstate( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, samplerstate.mAddressU ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, samplerstate.mAddressV ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, samplerstate.mMagFilter ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GetGLMinFilter( nummips, samplerstate.mMinFilter ) ) );
#if (_OPENGLES_ == 0)
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, samplerstate.mAddressW ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, samplerstate.mTextureCompareMode ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0 ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, nummips - 1 ) );
#endif

	// The texture cube info
	_dword			width				= 0;
	_dword			height				= 0;
	_PIXEL_FORMAT	format				= _PF_UNKNOWN;
	GLenum			gl_internalformat	= GL_RGBA; 
	GLenum			gl_datatype			= GL_UNSIGNED_BYTE;
	GLenum			gl_pixel_format		= 0;

	// The size in bytes of texture
	_dword size_in_bytes = 0;

	// Create cube map images
	for ( _dword level = 0; level < 6; level ++ )
	{
		const IImageFile* image_file = mipmaps_info.mImageFiles[level];
		EGE_ASSERT( image_file != _null );

		// Get the image info
		width	= image_file->GetWidth( );
		height	= image_file->GetHeight( );

		// Process image
		switch ( image_file->GetFileID( ) )
		{
			// It's compressed texture image
			case _FF_PVR_TEX:
			case _FF_KTX:
			case _FF_ASTC:
			{
				const ICompressedTexFile* compressed_tex_file = static_cast< const ICompressedTexFile* >( image_file );
				EGE_ASSERT( compressed_tex_file != _null );

				// Create compressed texture
				if ( CreateCompressedSurfaceOfTextureCube( compressed_tex_file, level, size_in_bytes ) == _false )
					return _null;
			}
			break;

			// Common image files
			case _FF_BMP:
			case _FF_JPG:
			case _FF_PNG:
			case _FF_TGA:
			case _FF_WEBP:
			{
				// Get the image file info
				width	= image_file->GetWidth( );
				height	= image_file->GetHeight( );
				format	= image_file->GetPixelFormat( );

				// Get the internal pixel format and data type
				if ( GLHelper::FindInternalFormatAndType( format, gl_internalformat, gl_datatype ) == _false )
				{
					WLOG_ERROR_1( L"The GL texture pixel format '%d' is invalid or un-matchable when create cube texture", (_dword) format );
					return _null;
				}

				// Get the pixel format
				gl_pixel_format = gPixelFormats[ format ].mPlatformFormat;
				EGE_ASSERT( gl_pixel_format != 0 );

				// Create texture cube without mipmaps
				if ( nummips == 1 )
				{
					GL_CHECK_ERROR( __glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + level, 0, gl_internalformat, width, height, 0, gl_pixel_format, gl_datatype, image_file->GetPixelBuffer( ) ) );
				}
				// Create texture cube with mipmaps
				else if ( nummips != 0 )
				{
					// Get the pixel format info
					const PixelFormatInfo& pixel_format_info = gPixelFormats[format];

					// Get the texture info
					_dword image_width	= width;
					_dword image_height = height;
					_byte* image_pixel	= (_byte*) image_file->GetPixelBuffer( );

					// Create texture with mipmaps
					for ( _dword mipindex = 0; mipindex < nummips; mipindex ++ )
					{
						GL_CHECK_ERROR( __glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + level, mipindex, gl_internalformat, image_width, image_height, 0, gl_pixel_format, gl_datatype, image_pixel ) );

						// Scale image pixel
						if ( image_pixel != _null && mipindex != nummips - 1 )
						{
							_dword mipsize_x	= Math::Max< _dword >( image_width >> 1, pixel_format_info.mBlockSizeX );
							_dword mipsize_y	= Math::Max< _dword >( image_height >> 1, pixel_format_info.mBlockSizeY );
							_dword pitch		= (image_width / pixel_format_info.mBlockSizeX) * pixel_format_info.mBlockBytes;

							_byte* from_pixel = image_pixel;
							GetImageProcessor( )->ScaleImage( _IMAGE_FILTER_LANCZOS3, format, PointU( image_width, image_height ), pitch, from_pixel, PointU( mipsize_x, mipsize_y ), image_pixel );

							image_width		= mipsize_x;
							image_height	= mipsize_y;

							// Delete the scaled pixel buffer
							if ( mipindex != 0 )
							{
								EGE_DELETE_ARRAY( from_pixel );
							}
						}
						else
						{
							EGE_DELETE_ARRAY( image_pixel );
						}
					}
				}

				// Get the size in bytes of texture
				size_in_bytes += RenderUtils::CaluTextureSize( width, height, format, nummips );
			}
			break;

			default:
				EGE_ASSERT( 0 );
				return _null;
				break;
		}
	}

	// Create texture cube
	GLTextureCube* texture = new GLTextureCube( );
	texture->InitCubeMapTex( res_name, textureid, GL_TEXTURE_CUBE_MAP, gl_internalformat, gl_datatype, size_in_bytes, nummips, format, PointU( width, height ), samplerstate, mipmaps_info );

	// Unbind the texture
	GLCachedBindTexture( GL_TEXTURE_CUBE_MAP, 0 );

	return texture;
}

TextureCubeRHIPassRef GLDrv::CreateTextureCubeWithMipmaps( WStringPtr res_name, _dword nummips, const TextureCubeWithMipmapsRHI* mipmaps_info )
{
	if ( mipmaps_info == _null )
		return _null;

	// Get the cube map info
	_dword			width	= mipmaps_info[0].mImageFiles[0]->GetWidth( );
	_dword			height	= mipmaps_info[0].mImageFiles[0]->GetHeight( );
	_PIXEL_FORMAT	format	= mipmaps_info[0].mImageFiles[0]->GetPixelFormat( );

	// Get the internal pixel format and data type
	GLenum internalformat = GL_RGBA; GLenum datatype = GL_UNSIGNED_BYTE;
	if ( GLHelper::FindInternalFormatAndType( format, internalformat, datatype ) == _false )
	{
		WLOG_ERROR_1( L"The GL texture pixel format '%d' is invalid or un-matchable when create cube texture", (_dword) format );
		return _null;
	}

	// Generate texture ID
	GLuint textureid = 0;
	GL_CHECK_ERROR( __glGenTextures( 1, &textureid ) );

	// Active the texture slot
	GLCachedSetActiveTexture( 0 );

	// Bind the texture
	GLCachedBindTexture( GL_TEXTURE_CUBE_MAP, textureid );

	// Set the texture sampler state
	GLSamplerStateInfo samplerstate( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, samplerstate.mAddressU ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, samplerstate.mAddressV ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, samplerstate.mMagFilter ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GetGLMinFilter( nummips, samplerstate.mMinFilter ) ) );
#if (_OPENGLES_ == 0)
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, samplerstate.mAddressW ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, samplerstate.mTextureCompareMode ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0 ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, nummips - 1 ) );
#endif

	// Get the pixel format
	GLenum pixel_format = gPixelFormats[ format ].mPlatformFormat;
	EGE_ASSERT( pixel_format != 0 );

	// Create cube map images
	for ( _dword mipindex = 0; mipindex < nummips; mipindex ++ )
	{
		const TextureCubeWithMipmapsRHI& mipmap_info = mipmaps_info[mipindex];

		for ( _dword i = 0; i < 6; i ++ )
		{
			_dword			image_width		= mipmap_info.mImageFiles[i]->GetWidth( );
			_dword			image_height	= mipmap_info.mImageFiles[i]->GetHeight( );
			const _byte*	image_pixels	= mipmap_info.mImageFiles[i]->GetPixelBuffer( );

			if ( image_width == 0 || image_height == 0 || image_pixels == _null )
				return _null;

			GL_CHECK_ERROR( __glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, mipindex, internalformat, image_width, image_height, 0, pixel_format, datatype, image_pixels ) );
		}
	}

	// Get the size in bytes of texture
	_dword size_in_bytes = RenderUtils::CaluTextureSize( width, height, format, nummips ) * 6;

	// Create texture cube
	GLTextureCube* texture = new GLTextureCube( );
	texture->InitCubeMapTex( res_name, textureid, GL_TEXTURE_CUBE_MAP, internalformat, datatype, size_in_bytes, nummips, format, PointU( width, height ), samplerstate, mipmaps_info );

	// Unbind the texture
	GLCachedBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
	
	return texture;
}

const PointU& GLDrv::GetTextureCubeSize( TextureCubeRHI* texture ) const
{
	DYNAMIC_CAST_GLRESOURCE( TextureCube, texture );

	return gl_texture->GetSize( );
}

_dword GLDrv::GetTextureCubeSizeInBytes( TextureCubeRHI* texture ) const
{
	DYNAMIC_CAST_GLRESOURCE( TextureCube, texture );

	return gl_texture->GetSizeInBytes( );
}

_dword GLDrv::GetTextureCubeMipNumber( const TextureCubeRHI* texture ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( TextureCube, texture );

	return gl_texture->GetNumMips( );
}

Texture2DRHIPassRef GLDrv::CreateTexture2D( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, const _byte* pixel, _ubool is_dynamic )
{
	// Get the internal pixel format and data type
	GLenum internalformat = GL_RGBA; GLenum datatype = GL_UNSIGNED_BYTE;
	if ( GLHelper::FindInternalFormatAndType( format, internalformat, datatype ) == _false )
	{
		WLOG_ERROR_1( L"The GL texture pixel format '%d' is invalid or un-matchable when create 2D texture", (_dword) format );
		return _null;
	}

	// Generate texture ID
	GLuint textureid = 0;
	GL_CHECK_ERROR( __glGenTextures( 1, &textureid ) );

	// Active the texture slot
	GLCachedSetActiveTexture( 0 );

	// Bind the texture
	GLCachedBindTexture( GL_TEXTURE_2D, textureid );

	// Get the pixel format info
	const PixelFormatInfo& pixel_format_info = gPixelFormats[format];

	// Get the pixel format
	GLenum pixel_format = pixel_format_info.mPlatformFormat;
	EGE_ASSERT( pixel_format != 0 );

	// Get the number of mips level 
	if ( nummips == 0 )
		nummips = Math::GetMipmapLevel( width, height );

	// Set the texture sampler state
	GLSamplerStateInfo samplerstate;
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, samplerstate.mMagFilter ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetGLMinFilter( nummips, samplerstate.mMinFilter ) ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, samplerstate.mAddressU ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, samplerstate.mAddressV ) );
#if (_OPENGLES_ == 0)
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, samplerstate.mAddressW ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, samplerstate.mTextureCompareMode ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0 ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, nummips - 1 ) );
#endif

	// Create texture without mipmaps
	if ( nummips == 1 )
	{
		// If we do not provide the pixel buffer then need to create it to make sure all pixels is 0
		MemArrayPtr< _byte > temp_pixel_buffer;
		if ( pixel == _null )
		{
			_dword pitch	= (width / pixel_format_info.mBlockSizeX) * pixel_format_info.mBlockBytes;
			_dword size		= pitch * height;

			temp_pixel_buffer.Create( size );
			EGE_MEM_SET( temp_pixel_buffer.GetPointer( ), 0, size );

			pixel = temp_pixel_buffer.GetPointer( );
		}

		GL_CHECK_ERROR( __glTexImage2D( GL_TEXTURE_2D, 0, internalformat, width, height, 0, pixel_format, datatype, pixel ) );

		pixel = _null;
	}
	// Create texture with mipmaps
	else if ( nummips != 0 )
	{
		// Get the texture info
		_dword image_width	= width;
		_dword image_height = height;
		_byte* image_pixel	= (_byte*) pixel;

		// Create texture with mipmaps
		for ( _dword mipindex = 0; mipindex < nummips; mipindex ++ )
		{
			GL_CHECK_ERROR( __glTexImage2D( GL_TEXTURE_2D, mipindex, internalformat, image_width, image_height, 0, pixel_format, datatype, image_pixel ) );

			// Scale image pixel
			if ( image_pixel != _null && mipindex != nummips - 1 )
			{
				_dword mipsize_x	= Math::Max< _dword >( image_width >> 1, pixel_format_info.mBlockSizeX );
				_dword mipsize_y	= Math::Max< _dword >( image_height >> 1, pixel_format_info.mBlockSizeY );
				_dword pitch		= ( image_width / pixel_format_info.mBlockSizeX ) * pixel_format_info.mBlockBytes;

				_byte* from_pixel = image_pixel;
				GetImageProcessor( )->ScaleImage( _IMAGE_FILTER_LANCZOS3, format, PointU( image_width, image_height ), pitch, from_pixel, PointU( mipsize_x, mipsize_y ), image_pixel );

				image_width		= mipsize_x;
				image_height	= mipsize_y;

				// Delete the scaled pixel buffer
				if ( mipindex != 0 )
				{
					EGE_DELETE_ARRAY( from_pixel );
				}
			}
			else
			{
				EGE_DELETE_ARRAY( image_pixel );
			}
		}
	}

	// Get the size in bytes of texture
	_dword size_in_bytes = RenderUtils::CaluTextureSize( width, height, format, nummips );

	// Create texture 2D
	GLTexture2D* texture = new GLTexture2D( );
	texture->InitTex( res_name, textureid, GL_TEXTURE_2D, internalformat, datatype, size_in_bytes, nummips, format, PointU( width, height ), samplerstate, pixel, is_dynamic );

	// Restore the texture on stage 0
	if ( gGLCachedState.mTextures[0].mTarget != GL_NONE )
	{
		GLCachedBindTexture( gGLCachedState.mTextures[0].mTarget, gGLCachedState.mTextures[0].mResource );
	}
	// Unbind the texture
	else
	{
		GLCachedBindTexture( GL_TEXTURE_2D, 0 );
	}

	return texture;
}

Texture2DRHIPassRef GLDrv::CreateTexture2DFromImageFile( WStringPtr res_name, IImageFile* image_file, _dword nummips )
{
	switch ( image_file->GetFileID( ) )
	{
		// It's compressed texture image
		case _FF_PVR_TEX:
		case _FF_KTX:
		case _FF_ASTC:
		{
			ICompressedTexFile* compressed_tex_file = static_cast< ICompressedTexFile* >( image_file );
			EGE_ASSERT( compressed_tex_file != _null );

			// Create compressed texture 2D
			GLTexture2D* texture = CreateCompressedTexture2D( compressed_tex_file, res_name, _false );
			if ( texture == _null )
				return _null;

			return texture;
		}
		break;

		// Common image files
		case _FF_BMP:
		case _FF_JPG:
		case _FF_PNG:
		case _FF_TGA:
		case _FF_WEBP:
		case _FF_GIF:
			return CreateTexture2D( res_name, image_file->GetWidth( ), image_file->GetHeight( ), image_file->GetPixelFormat( ), nummips, image_file->GetPixelBuffer( ), _false );

		default:
			EGE_ASSERT( 0 );
			break;
	}

	return _null;
}

Texture2DRHIPassRef GLDrv::CreateTexture2DWithMipmaps( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, const _byte** pixels )
{
	// Get the internal pixel format and data type
	GLenum internalformat = GL_RGBA; GLenum datatype = GL_UNSIGNED_BYTE;
	if ( GLHelper::FindInternalFormatAndType( format, internalformat, datatype ) == _false )
	{
		WLOG_ERROR_1( L"The GL texture pixel format '%d' is invalid or un-matchable when create 2D texture", (_dword) format );
		return _null;
	}

	// Generate texture ID
	GLuint textureid = 0;
	GL_CHECK_ERROR( __glGenTextures( 1, &textureid ) );

	// Active the texture slot
	GLCachedSetActiveTexture( 0 );

	// Bind the texture
	GLCachedBindTexture( GL_TEXTURE_2D, textureid );

	// Set the texture sampler state
	GLSamplerStateInfo samplerstate;
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, samplerstate.mMagFilter ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetGLMinFilter( nummips, samplerstate.mMinFilter ) ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, samplerstate.mAddressU ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, samplerstate.mAddressV ) );
#if (_OPENGLES_ == 0)
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, samplerstate.mAddressW ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, samplerstate.mTextureCompareMode ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0 ) );
	GL_CHECK_ERROR( __glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, nummips - 1 ) );
#endif

	// Get the pixel format
	GLenum pixel_format = gPixelFormats[ format ].mPlatformFormat;
	EGE_ASSERT( pixel_format != 0 );

	// Get the texture info
	_dword image_width	= width;
	_dword image_height = height;

	// Create texture with mipmaps
	for ( _dword mipindex = 0; mipindex < nummips; mipindex ++ )
	{
		_dword mipsize_x = Math::Max< _dword >( image_width, 1 );
		_dword mipsize_y = Math::Max< _dword >( image_height, 1 );

		GL_CHECK_ERROR( __glTexImage2D( GL_TEXTURE_2D, mipindex, internalformat, mipsize_x, mipsize_y, 0, pixel_format, datatype, pixels[mipindex] ) );

		image_width >>= 1;
		image_height >>= 1;
	}

	// Get the size in bytes of texture
	_dword size_in_bytes = RenderUtils::CaluTextureSize( width, height, format, nummips );

	// Create texture 2D
	GLTexture2D* texture = new GLTexture2D( );
	texture->InitTex( res_name, textureid, GL_TEXTURE_2D, internalformat, datatype, size_in_bytes, nummips, format, PointU( width, height ), samplerstate, (const _byte*) _null, _true );

	// Restore the texture on stage 0
	if ( gGLCachedState.mTextures[0].mTarget != GL_NONE )
	{
		GLCachedBindTexture( gGLCachedState.mTextures[0].mTarget, gGLCachedState.mTextures[0].mResource );
	}
	// Unbind the texture
	else
	{
		GLCachedBindTexture( GL_TEXTURE_2D, 0 );
	}

	return texture;
}

_ubool GLDrv::UpdateTexture2D( Texture2DRHI* texture, const RectU& rect, const _byte* pixel )
{
	if ( pixel == _null )
		return _false;

	DYNAMIC_CAST_GLRESOURCE( Texture2D, texture );

	gl_texture->UpdateSubTexture( rect, pixel );

	return _true;
}

_ubool GLDrv::ReadTexture2DMipPixel( const Texture2DRHI* texture, _byte* pixel_buffer )
{
	DYNAMIC_CAST_GLRESOURCE_CONST( Texture2D, texture );

	return gl_texture->ReadMipPixel( pixel_buffer );
}

_dword GLDrv::GetTexture2DResID( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( Texture2D, texture );

	return gl_texture->GetResource( );
}

const PointU& GLDrv::GetTexture2DSize( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( Texture2D, texture );

	return gl_texture->GetSize( );
}

_dword GLDrv::GetTexture2DMipNumber( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( Texture2D, texture );

	return gl_texture->GetNumMips( );
}

_dword GLDrv::GetTexture2DMipSize( const Texture2DRHI* texture, _dword mipindex ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( Texture2D, texture );

	return gl_texture->GetMipSize( mipindex, _null );
}

_dword GLDrv::GetTexture2DStride( const Texture2DRHI* texture, _dword mipindex ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( Texture2D, texture );

	return gl_texture->GetStride( mipindex );
}

_ubool GLDrv::IsTexture2DDynamic( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( Texture2D, texture );

	return gl_texture->IsDynamic( );
}

_PIXEL_FORMAT GLDrv::GetTexture2DPixelFormat( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( Texture2D, texture );

	return gl_texture->GetPixelFormat( );
}

_dword GLDrv::GetTexture2DSizeInBytes( Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( Texture2D, texture );

	return gl_texture->GetSizeInBytes( );
}

SamplerStateInitializerRHI GLDrv::GetTexture2DSamplerStateInfo( Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( Texture2D, texture );

	return GetSamplerStateFromGL( gl_texture->GetSamplerState( ) );
}

_void GLDrv::LockTexture2DSamplerState( Texture2DRHI* texture, _ubool lock )
{
	DYNAMIC_CAST_GLRESOURCE( Texture2D, texture );

	return gl_texture->LockSamplerState( lock );
}

_ubool GLDrv::IsTexture2DCompressed( Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_GLRESOURCE( Texture2D, texture );

	return gl_texture->IsCompressed( );
}
