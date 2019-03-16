//! @file     GraphicTexture2DImageFiller.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicTexture2DImageFiller Implementation
//----------------------------------------------------------------------------

GraphicTexture2DImageFiller::GraphicTexture2DImageFiller( _ubool stand_alone_mode )
{
	mIsStandAloneMode	= stand_alone_mode;

	mPixelFormat		= _PF_UNKNOWN;
}

GraphicTexture2DImageFiller::~GraphicTexture2DImageFiller( )
{
}

_ubool GraphicTexture2DImageFiller::Initialize( _PIXEL_FORMAT format, const PointU& size, const PointU& space )
{
	if ( size.x == 0 || size.y == 0 )
		return _false;

	mPixelFormat = format;

	// Create texture filler
	mImageFiller = GetInterfaceFactory( )->CreateImageFiller( _IMAGE_FILLER_BINARY_TREE, size, space );
	if ( mImageFiller.IsNull( ) )
		return _false;

	// Create texture
	mTexture = gGraphicResourceManager->CreateTexture2D( L"", size.x, size.y, format, 1, _null, _false );
	if ( mTexture.IsNull( ) )
		return _false;

	return _true;
}

_void GraphicTexture2DImageFiller::Cleanup( )
{
	for ( _dword i = 0; i < mSubTextures.Number( ); i ++ )
	{
		IGraphicTexture2D* sub_texture = mSubTextures[i].mSubTexture;
		EGE_ASSERT( sub_texture != _null );

		// Skip for used sub texture
		if ( sub_texture->GetRefCount( ) > 1 )
			continue;

		// No any other modules use it, so remove it
		mImageFiller->FreeImage( sub_texture->GetRect( ) );

		// Remove it from array
		mSubTextures.RemoveByIndex( i -- );
	}
}

_dword GraphicTexture2DImageFiller::GetSubTexturesNumber( ) const
{
	return mSubTextures.Number( );
}

IGraphicTexture2DPassRef GraphicTexture2DImageFiller::CreateSubTexture2D( WStringPtr name, _dword width, _dword height, const _byte* pixelbuffer )
{
	// Add image by filler to get the region
	RectU rect;
	if ( mImageFiller->AddImage( PointU( width, height ), rect ) == _false )
		return _null;

	// Get the texture size
	_dword texture_width	= mTexture->GetWidth( );
	_dword texture_height	= mTexture->GetHeight( );

	// Calculate the texture coordinates
	Vector2 uv1, uv2;
	uv1.x = EGE_RATIO( rect.l, texture_width );
	uv1.y = EGE_RATIO( rect.t, texture_height );
	uv2.x = EGE_RATIO( rect.r, texture_width );
	uv2.y = EGE_RATIO( rect.b, texture_height );

	// Create sub-texture 2D
	IGraphicTexture2DPassRef sub_texture = GetGraphicResourceManager( )->CreateSubTexture2D( uv1, uv2, mTexture );
	if ( sub_texture.IsNull( ) )
	{
		mImageFiller->FreeImage( rect );
		return _null;
	}

	// Update the pixel buffer of texture
	if ( mTexture->UpdatePixelBuffer( rect, pixelbuffer ) == _false )
		return _null;

	// Update sub textures
	SubTextureInfo info;
	info.mName			= name;
	info.mRect			= rect;
	info.mSubTexture	= sub_texture;
	mSubTextures.InsertAscending< WStringPtr >( info );

	return sub_texture;
}

_void GraphicTexture2DImageFiller::RemoveSubTexture2D( WStringPtr name )
{
	SubTextureInfoArray::Iterator it = mSubTextures.SearchAscending( name );
	if ( it.IsValid( ) == _false )
		return;

	SubTextureInfo& info = it.GetObject( );

	mImageFiller->FreeImage( info.mRect );

	mSubTextures.Remove( it );
}
