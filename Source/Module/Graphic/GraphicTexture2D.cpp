//! @file     GraphicTexture2D.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicTexture2D Implementation
//----------------------------------------------------------------------------

GraphicTexture2D::GraphicTexture2D( Texture2DRHI* resource ) : mResource( resource )
{
}

GraphicTexture2D::~GraphicTexture2D( )
{
}

_ubool GraphicTexture2D::CopyFrom( const IObject* obj )
{
	const IGraphicTexture2D* src_obj = GetObjPtr< IGraphicTexture2D >( obj );
	if ( src_obj == _null )
	{
		WLOG_ERROR_2( L"We can not copy from '%s' object to '%s'", src_obj->GetInterfaceTypeNameW( ).Str( ), GetInterfaceTypeNameW( ).Str( ) );
		return _false;
	}

	mTransparentLayer	= src_obj->GetTransparentLayer( );
	mResource			= src_obj->GetResource( );

	return _true;
}

_ubool GraphicTexture2D::IsDynamicTexture( ) const
{
	return gDynamicRHI->IsTexture2DDynamic( mResource.GetPtr( ) );
}

_dword GraphicTexture2D::GetMipmaps( ) const
{
	return gDynamicRHI->GetTexture2DMipNumber( mResource.GetPtr( ) );
}

_dword GraphicTexture2D::GetSizeInBytes( ) const
{
	return gDynamicRHI->GetTexture2DSizeInBytes( mResource.GetPtr( ) );
}

_dword GraphicTexture2D::GetWidth( ) const
{
	return gDynamicRHI->GetTexture2DSize( mResource.GetPtr( ) ).x;
}

_dword GraphicTexture2D::GetHeight( ) const
{
	return gDynamicRHI->GetTexture2DSize( mResource.GetPtr( ) ).y;
}

const PointU& GraphicTexture2D::GetSize( ) const
{
	return gDynamicRHI->GetTexture2DSize( mResource.GetPtr( ) );
}

_dword GraphicTexture2D::GetPixelSize( ) const
{
	return gPixelFormats[ GetPixelFormat( ) ].mBlockBytes;
}

_PIXEL_FORMAT GraphicTexture2D::GetPixelFormat( ) const
{
	return gDynamicRHI->GetTexture2DPixelFormat( mResource.GetPtr( ) );
}

SamplerStateInitializerRHI GraphicTexture2D::GetSamplerStateInfo( ) const
{
	return gDynamicRHI->GetTexture2DSamplerStateInfo( mResource.GetPtr( ) );
}

RectU GraphicTexture2D::GetRect( ) const
{
	return RectU( ).InitWithSize( PointU::cZeroPoint, PointU( GetWidth( ), GetHeight( ) ) );
}

const OneBitArray& GraphicTexture2D::GetTransparentLayer( ) const
{
	return mTransparentLayer;
}

Texture2DRHI* GraphicTexture2D::GetResource( ) const
{
	return mResource.GetPtr( );
}

_void GraphicTexture2D::SetResource( Texture2DRHI* texture )
{
	mResource = texture;
}

_void GraphicTexture2D::SetUV( const Vector2& uv1, const Vector2& uv2 )
{
	// Do nothing ...
}

_void GraphicTexture2D::GetUV( Vector2& uv1, Vector2& uv2 ) const
{
	// Do nothing ...
}

Vector2 GraphicTexture2D::FixUV( const Vector2& uv ) const
{
	// We don't need to fix it
	return uv;
}

Vector2 GraphicTexture2D::FixUV( const PointU& pos ) const
{
	Vector2 uv;
	uv.x = EGE_RATIO( pos.x, GetWidth( ) );
	uv.y = EGE_RATIO( pos.y, GetHeight( ) );

	return FixUV( uv );
}

_ubool GraphicTexture2D::UpdatePixelBuffer( const RectU& rect, const _byte* buffer )
{
	if ( gDynamicRHI->UpdateTexture2D( mResource, rect, buffer ) == _false )
		return _false;

	// Update transparent layer buffer
	if ( HasTransparentLayer( ) )
	{
		// Create transparent layer buffer
		OneBitArray transparent_layer;
		transparent_layer.Create( rect.GetWidth( ) * rect.GetHeight( ) );

		// Get the transparent from pixel buffer
		BitmapInfoReadOnly bitmap_info( GetPixelFormat( ), 4, rect.GetWidth( ) * sizeof( _dword ), rect.GetWidth( ), rect.GetHeight( ), buffer );
		if ( GetImageProcessor( )->GetTransparentLayer( bitmap_info, transparent_layer ) == _false )
			return _false;

		for ( _dword y = rect.t; y < rect.b; y ++ )
		{
			_dword to_index		= y * GetWidth( );
			_dword from_index	= (y - rect.t) * rect.GetWidth( );

			for ( _dword x = rect.l; x < rect.r; x ++ )
				mTransparentLayer.Set( to_index + x, transparent_layer.Get( from_index + (x - rect.l) ) );
		}
	}

	return _true;
}

_ubool GraphicTexture2D::IsTransparentPixel( _dword x, _dword y ) const
{
	_dword index = y * GetWidth( ) + x;
	if ( index >= mTransparentLayer.Number( ) )
		return _false;

	return EGE_BOOLEAN( mTransparentLayer[ index ] );
}

_ubool GraphicTexture2D::HasTransparentLayer( ) const
{
	return mTransparentLayer.Number( ) != 0;
}

_ubool GraphicTexture2D::SetTransparentLayer( _dword width, _dword height, const OneBitArray& layer )
{
	if ( width != GetWidth( ) )
		return _false;

	if ( height != GetHeight( ) )
		return _false;

	mTransparentLayer = layer;

	return _true;
}

_void GraphicTexture2D::UnloadResource( )
{
	mResource.Clear( );
}

_ubool GraphicTexture2D::SaveToFile( _FILE_FORMAT fileformat, WStringPtr filename, _ubool is_vert_flip, _ubool swap_r_and_b ) const
{
	// Get the size of texture
	_dword width	= GetWidth( );
	_dword height	= GetHeight( );
	if ( width == 0 || height == 0 )
		return _false;

	// Get the pixel format
	_PIXEL_FORMAT pixel_format = GetPixelFormat( );
	if ( pixel_format == _PF_UNKNOWN )
		return _false;

	// Create temporary pixel buffer
	MemArrayPtr< _byte > pixel_buffer( gDynamicRHI->GetTexture2DMipSize( mResource, 0 ) );

	// Lock the texture to get the pixel buffer
	if ( gDynamicRHI->ReadTexture2DMipPixel( mResource, pixel_buffer ) == _false )
		return _false;

	// Get the pitch
	_dword pitch = gDynamicRHI->GetTexture2DStride( mResource, 0 );
	if ( pitch == 0 )
		return _false;

	// Change whether we need to swap BGR mode -> RGB mode
	if ( swap_r_and_b )
	{
		switch ( pixel_format ) 
		{
			case _PF_R8G8B8:
				if ( GetImageProcessor( )->SwapRBChannel( pixel_buffer, pitch, width, height ) == _false )
					return _false;
				break;

			case _PF_A8R8G8B8:
				if ( GetImageProcessor( )->SwapRBChannelWithAlpha( pixel_buffer, pitch, width, height ) == _false )
					return _false;
				break;

			default:
				break;
		}
	}

	// Flip the vert
	if ( is_vert_flip )
		GetImageProcessor( )->Flip( pixel_buffer, pitch, height );

	// Create image file by pixel buffer from texture
	IImageFileRef image_file = GetInterfaceFactory( )->CreateImageFile( fileformat, width, height, pixel_format, pixel_buffer );
	if ( image_file.IsNull( ) )
		return _false;

	// Save to file
	return image_file->SaveToFile( filename );
}