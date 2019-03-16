//! @file     D2DTexture.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D2DDrv-Texture Implementation
//----------------------------------------------------------------------------

const TextureStatsRHI& D2DDrv::GetTextureStats( )
{
	static TextureStatsRHI sNull;

	return sNull;
}

TextureCubeRHIPassRef D2DDrv::CreateTextureCube( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, _dword flags, const _byte** pixel, WStringPtr* res_name_table )
{
	return _null;
}

TextureCubeRHIPassRef D2DDrv::CreateTextureCubeFromImageFiles( WStringPtr res_name, IImageFile** image_files, _dword nummips, _dword flags, WStringPtr* res_name_table, _ubool auto_rotate )
{
	return _null;
}

const PointU& D2DDrv::GetTextureCubeSize( TextureCubeRHI* texture ) const
{
	return PointU::cZeroPoint;
}

_dword D2DDrv::GetTextureCubeSizeInBytes( TextureCubeRHI* texture ) const
{
	return 0;
}

Texture2DRHIPassRef D2DDrv::CreateTexture2D( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, _dword flags, const _byte* pixel )
{
	return _null;
}

Texture2DRHIPassRef D2DDrv::CreateTexture2DFromImageFile( WStringPtr res_name, IImageFile* image_file, _dword nummips, _dword flags )
{
	return _null;
}

Texture2DRHIPassRef D2DDrv::CreateTexture2DWithMipmaps( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, _dword flags, const _byte** pixels )
{
	return _null;
}

_ubool D2DDrv::UpdateTexture2D( Texture2DRHI* texture, _dword mipindex, const RectU& rect, const _byte* pixel )
{
	return _true;
}

_void* D2DDrv::LockTexture2D( Texture2DRHI* texture, _dword mipindex, _dword& stride, _RESOURCE_LOCK_FLAG flag )
{
	DYNAMIC_CAST_D2DRESOURCE( Texture2D, texture );
	return _null;
}

_void D2DDrv::UnlockTexture2D( Texture2DRHI* texture, _dword mipindex )
{
	DYNAMIC_CAST_D2DRESOURCE( Texture2D, texture );
	return;
}

_ubool D2DDrv::ReadTexture2DMipPixel( const Texture2DRHI* texture, _dword mipindex, _byte* pixel_buffer )
{
	DYNAMIC_CAST_D2DRESOURCE_CONST( Texture2D, texture );

	return _false;
}

_dword D2DDrv::GetTexture2DResID( const Texture2DRHI* texture ) const
{
	return 0;
}

const PointU& D2DDrv::GetTexture2DSize( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_D2DRESOURCE_CONST( Texture2D, texture );

	return d2d_texture->GetSize( );
}

_dword D2DDrv::GetTexture2DMipNumber( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_D2DRESOURCE_CONST( Texture2D, texture );

	return 0;
}

_dword D2DDrv::GetTexture2DMipSize( const Texture2DRHI* texture, _dword mipindex ) const
{
	DYNAMIC_CAST_D2DRESOURCE_CONST( Texture2D, texture );

	return 0;
}

_dword D2DDrv::GetTexture2DStride( const Texture2DRHI* texture, _dword mipindex ) const
{
	DYNAMIC_CAST_D2DRESOURCE_CONST( Texture2D, texture );

	return 0;
}

const FlagsObject& D2DDrv::GetTexture2DFlags( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_D2DRESOURCE_CONST( Texture2D, texture );

	return FlagsObject::cNull;
}

_PIXEL_FORMAT D2DDrv::GetTexture2DPixelFormat( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_D2DRESOURCE_CONST( Texture2D, texture );

	return _PF_UNKNOWN;
}

_dword D2DDrv::GetTexture2DSizeInBytes( Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_D2DRESOURCE( Texture2D, texture );

	return 0;
}

SamplerStateInitializerRHI D2DDrv::GetTexture2DSamplerStateInfo( Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_D2DRESOURCE( Texture2D, texture );

	return SamplerStateInitializerRHI( _SF_NEAREST );
}
