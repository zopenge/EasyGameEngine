//! @file     GDITexture.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GDIDrv-Texture Implementation
//----------------------------------------------------------------------------

const TextureStatsRHI& GDIDrv::GetTextureStats( )
{
	static TextureStatsRHI sNull;

	return sNull;
}

TextureCubeRHIPassRef GDIDrv::CreateTextureCube( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, _dword flags, const _byte** pixel, WStringPtr* res_name_table )
{
	return _null;
}

TextureCubeRHIPassRef GDIDrv::CreateTextureCubeFromImageFiles( WStringPtr res_name, IImageFile** image_files, _dword nummips, _dword flags, WStringPtr* res_name_table, _ubool auto_rotate )
{
	return _null;
}

const PointU& GDIDrv::GetTextureCubeSize( TextureCubeRHI* texture ) const
{
	return PointU::cZeroPoint;
}

_dword GDIDrv::GetTextureCubeSizeInBytes( TextureCubeRHI* texture ) const
{
	return 0;
}

Texture2DRHIPassRef GDIDrv::CreateTexture2D( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, _dword flags, const _byte* pixel )
{
	// Get the stride
	_dword stride = 0;
	switch ( format )
	{
		case _PF_R8G8B8:	stride = width * 3; break;
		case _PF_A8R8G8B8:	stride = width * 4; break;
		default:
			return _null;
	}

	// Create GDI bitmap 
	Gdiplus::GpBitmap* bitmap = _null;
	if ( GDI::GdipCreateBitmapFromScan0( width, height, stride, gPixelFormats[ format ].mPlatformFormat, _null, &bitmap ) != Gdiplus::Ok )
		return _null;

	// Create GDI texture
	GDITexture2D* texture = new GDITexture2D( bitmap, format, PointU( width, height ) );

	// Copy pixel buffer
	if ( pixel != _null )
	{
		// Lock the texture to get pixel buffer pointer
		_void* scan_buffer = texture->Lock( stride, _RLF_WRITE_ONLY );
		if ( scan_buffer == _null )
			{ EGE_RELEASE( texture ); return _null; }

		// Fill pixel buffer into bitmap
		EGE_MEM_CPY( scan_buffer, pixel, stride * height );

		// Unlock texture
		texture->Unlock( );
	}

	return texture;
}

Texture2DRHIPassRef GDIDrv::CreateTexture2DFromImageFile( WStringPtr res_name, IImageFile* image_file, _dword nummips, _dword flags )
{
	return _null;
}

Texture2DRHIPassRef GDIDrv::CreateTexture2DWithMipmaps( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, _dword flags, const _byte** pixels )
{
	return _null;
}

_ubool GDIDrv::UpdateTexture2D( Texture2DRHI* texture, _dword mipindex, const RectU& rect, const _byte* pixel )
{
	return _true;
}

_void* GDIDrv::LockTexture2D( Texture2DRHI* texture, _dword mipindex, _dword& stride, _RESOURCE_LOCK_FLAG flag )
{
	DYNAMIC_CAST_GDIRESOURCE( Texture2D, texture );

	return gdi_texture->Lock( stride, flag );
}

_void GDIDrv::UnlockTexture2D( Texture2DRHI* texture, _dword mipindex )
{
	DYNAMIC_CAST_GDIRESOURCE( Texture2D, texture );

	gdi_texture->Unlock( );
}

_ubool GDIDrv::ReadTexture2DMipPixel( const Texture2DRHI* texture, _dword mipindex, _byte* pixel_buffer )
{
	DYNAMIC_CAST_GDIRESOURCE_CONST( Texture2D, texture );

	return _false;
}

_dword GDIDrv::GetTexture2DResID( const Texture2DRHI* texture ) const
{
	return 0;
}

const PointU& GDIDrv::GetTexture2DSize( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_GDIRESOURCE_CONST( Texture2D, texture );

	return gdi_texture->GetSize( );
}

_dword GDIDrv::GetTexture2DMipNumber( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_GDIRESOURCE_CONST( Texture2D, texture );

	return 0;
}

_dword GDIDrv::GetTexture2DMipSize( const Texture2DRHI* texture, _dword mipindex ) const
{
	DYNAMIC_CAST_GDIRESOURCE_CONST( Texture2D, texture );

	return 0;
}

_dword GDIDrv::GetTexture2DStride( const Texture2DRHI* texture, _dword mipindex ) const
{
	DYNAMIC_CAST_GDIRESOURCE_CONST( Texture2D, texture );

	return 0;
}

const FlagsObject& GDIDrv::GetTexture2DFlags( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_GDIRESOURCE_CONST( Texture2D, texture );

	return FlagsObject::cNull;
}

_PIXEL_FORMAT GDIDrv::GetTexture2DPixelFormat( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_GDIRESOURCE_CONST( Texture2D, texture );

	return gdi_texture->GetPixelFormat( );
}

_dword GDIDrv::GetTexture2DSizeInBytes( Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_GDIRESOURCE( Texture2D, texture );

	return 0;
}

SamplerStateInitializerRHI GDIDrv::GetTexture2DSamplerStateInfo( Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_D2DRESOURCE( Texture2D, texture );

	return SamplerStateInitializerRHI( _SF_NEAREST );
}
