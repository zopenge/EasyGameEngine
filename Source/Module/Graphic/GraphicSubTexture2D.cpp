//! @file     GraphicTexture2D.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicTexture2D Implementation
//----------------------------------------------------------------------------

GraphicSubTexture2D::GraphicSubTexture2D( const Vector2& uv1, const Vector2& uv2, IGraphicTexture2D* texture )
{
	EGE_ASSERT( texture != _null );

	mUV1 		= uv1;
	mUV2 		= uv2;
	mSize.x		= _dword( ( mUV2.x - mUV1.x ) * texture->GetWidth( ) );
	mSize.y		= _dword( ( mUV2.y - mUV1.y ) * texture->GetHeight( ) );
	mTexture2D	= texture;
}

GraphicSubTexture2D::~GraphicSubTexture2D( )
{
}

_dword GraphicSubTexture2D::GetLeft( ) const
{
	return _dword( mUV1.x * mTexture2D->GetWidth( ) );
}

_dword GraphicSubTexture2D::GetTop( ) const
{
	return _dword( mUV1.y * mTexture2D->GetHeight( ) );
}

RectU GraphicSubTexture2D::GetSubRect( const RectU& rect ) const
{
	return RectU( ).InitWithSize( GetLeft( ) + rect.l, GetTop( ) + rect.t, rect.GetWidth( ), rect.GetHeight( ) );
}

_ubool GraphicSubTexture2D::Initialize( )
{
	return _true;
}

_ubool GraphicSubTexture2D::IsDynamicTexture( ) const
{
	return mTexture2D->IsDynamicTexture( );
}

_dword GraphicSubTexture2D::GetMipmaps( ) const
{
	return mTexture2D->GetMipmaps( );
}

_dword GraphicSubTexture2D::GetSizeInBytes( ) const
{
	return mTexture2D->GetSizeInBytes( );
}

_dword GraphicSubTexture2D::GetWidth( ) const
{
	return mSize.x;
}

_dword GraphicSubTexture2D::GetHeight( ) const
{
	return mSize.y;
}

const PointU& GraphicSubTexture2D::GetSize( ) const
{
	return mSize;
}

_dword GraphicSubTexture2D::GetPixelSize( ) const
{
	return mTexture2D->GetPixelSize( );
}

_PIXEL_FORMAT GraphicSubTexture2D::GetPixelFormat( ) const
{
	return mTexture2D->GetPixelFormat( );
}

SamplerStateInitializerRHI GraphicSubTexture2D::GetSamplerStateInfo( ) const
{
	return mTexture2D->GetSamplerStateInfo( );
}

RectU GraphicSubTexture2D::GetRect( ) const
{
	return RectU( ).InitWithSize( GetLeft( ), GetTop( ), mSize.x, mSize.y );
}

const OneBitArray& GraphicSubTexture2D::GetTransparentLayer( ) const
{
	return mTransparentLayer;
}

Texture2DRHI* GraphicSubTexture2D::GetResource( ) const
{
	return mTexture2D->GetResource( );
}

_void GraphicSubTexture2D::SetResource( Texture2DRHI* texture )
{
	mTexture2D->SetResource( texture );
}

_void GraphicSubTexture2D::SetUV( const Vector2& uv1, const Vector2& uv2 )
{
	mUV1 = uv1;
	mUV2 = uv2;
}

_void GraphicSubTexture2D::GetUV( Vector2& uv1, Vector2& uv2 ) const
{
	uv1 = mUV1;
	uv2 = mUV2;
}

Vector2 GraphicSubTexture2D::FixUV( const Vector2& uv ) const
{
	_float x = mUV1.x + ( uv.x * ( mUV2.x - mUV1.x ) );
	_float y = mUV1.y + ( uv.y * ( mUV2.y - mUV1.y ) );

	return Vector2( x, y );
}

Vector2 GraphicSubTexture2D::FixUV( const PointU& pos ) const
{
	Vector2 uv;
	uv.x = EGE_RATIO( pos.x, mTexture2D->GetWidth( ) );
	uv.y = EGE_RATIO( pos.y, mTexture2D->GetHeight( ) );

	return FixUV( uv );
}

_ubool GraphicSubTexture2D::UpdatePixelBuffer( const RectU& rect, const _byte* buffer )
{
	// Build the sub-image rect
	RectU sub_rect = GetSubRect( rect );

	// Update pixel buffer of texture 2D
	return mTexture2D->UpdatePixelBuffer( sub_rect, buffer );
}

_ubool GraphicSubTexture2D::IsTransparentPixel( _dword x, _dword y ) const
{
	_dword index = y * GetWidth( ) + x;
	if ( index >= mTransparentLayer.Number( ) )
		return _false;

	return EGE_BOOLEAN( mTransparentLayer[index] );
}

_ubool GraphicSubTexture2D::HasTransparentLayer( ) const
{
	return mTransparentLayer.Number( ) != 0;
}

_ubool GraphicSubTexture2D::SetTransparentLayer( _dword width, _dword height, const OneBitArray& layer )
{
	if ( width != GetWidth( ) )
		return _false;

	if ( height != GetHeight( ) )
		return _false;

	mTransparentLayer = layer;

	return _true;
}

_void GraphicSubTexture2D::UnloadResource( )
{
	mTexture2D->UnloadResource( );
}

_ubool GraphicSubTexture2D::SaveToFile( _FILE_FORMAT fileformat, WStringPtr filename, _ubool is_vert_flip, _ubool swap_r_and_b ) const
{
	// We are not support to this operation
	return _false;
}