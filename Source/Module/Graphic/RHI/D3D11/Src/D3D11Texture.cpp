//! @file     D3D11Texture.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D3D11Drv-Texture Implementation
//----------------------------------------------------------------------------

const TextureStatsRHI& D3D11Drv::GetTextureStats( )
{
	static TextureStatsRHI sNull;

	return sNull;
}

TextureCubeRHIPassRef D3D11Drv::CreateTextureCube( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, _dword flags, const _byte** pixel, WStringPtr* res_name_table )
{
	return _null;
}

TextureCubeRHIPassRef D3D11Drv::CreateTextureCubeFromImageFiles( WStringPtr res_name, IImageFile** image_files, _dword nummips, _dword flags, WStringPtr* res_name_table, _ubool auto_rotate )
{
	return _null;
}

const PointU& D3D11Drv::GetTextureCubeSize( TextureCubeRHI* texture ) const
{
	return PointU::cZeroPoint;
}

_dword D3D11Drv::GetTextureCubeSizeInBytes( TextureCubeRHI* texture ) const
{
	return 0;
}

Texture2DRHIPassRef D3D11Drv::CreateTexture2D( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, _dword flags, const _byte* pixel )
{
	return _null;
}

Texture2DRHIPassRef D3D11Drv::CreateTexture2DFromImageFile( WStringPtr res_name, IImageFile* image_file, _dword nummips, _dword flags )
{
	return _null;
}

Texture2DRHIPassRef D3D11Drv::CreateTexture2DWithMipmaps( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, _dword flags, const _byte** pixels )
{
	return _null;
}

_ubool D3D11Drv::UpdateTexture2D( Texture2DRHI* texture, _dword mipindex, const RectU& rect, const _byte* pixel )
{
	return _true;
}

_void* D3D11Drv::LockTexture2D( Texture2DRHI* texture, _dword mipindex, _dword& stride, _RESOURCE_LOCK_FLAG flag )
{
	return _null;
}

_void D3D11Drv::UnlockTexture2D( Texture2DRHI* texture, _dword mipindex )
{

}

_ubool D3D11Drv::ReadTexture2DMipPixel( const Texture2DRHI* texture, _dword mipindex, _byte* pixel_buffer )
{
	DYNAMIC_CAST_D3D11RESOURCE_CONST( Texture2D, texture );

	return _false;
}

_dword D3D11Drv::GetTexture2DResID( const Texture2DRHI* texture ) const
{
	return 0;
}

const PointU& D3D11Drv::GetTexture2DSize( const Texture2DRHI* texture ) const
{
	return PointU::cZeroPoint;
}

_dword D3D11Drv::GetTexture2DMipNumber( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_D3D11RESOURCE_CONST( Texture2D, texture );

	return 0;
}

_dword D3D11Drv::GetTexture2DMipSize( const Texture2DRHI* texture, _dword mipindex ) const
{
	DYNAMIC_CAST_D3D11RESOURCE_CONST( Texture2D, texture );

	return 0;
}

_dword D3D11Drv::GetTexture2DStride( const Texture2DRHI* texture, _dword mipindex ) const
{
	DYNAMIC_CAST_D3D11RESOURCE_CONST( Texture2D, texture );

	return 0;
}

const FlagsObject& D3D11Drv::GetTexture2DFlags( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_D3D11RESOURCE_CONST( Texture2D, texture );

	return FlagsObject::cNull;
}

_PIXEL_FORMAT D3D11Drv::GetTexture2DPixelFormat( const Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_D3D11RESOURCE_CONST( Texture2D, texture );

	return _PF_UNKNOWN;
}

_dword D3D11Drv::GetTexture2DSizeInBytes( Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_D3D11RESOURCE( Texture2D, texture );

	return 0;
}

SamplerStateInitializerRHI D3D11Drv::GetTexture2DSamplerStateInfo( Texture2DRHI* texture ) const
{
	DYNAMIC_CAST_D2DRESOURCE( Texture2D, texture );

	return SamplerStateInitializerRHI( _SF_NEAREST );
}
