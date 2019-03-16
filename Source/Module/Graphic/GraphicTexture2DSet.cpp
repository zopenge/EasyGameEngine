//! @file     GraphicTexture2DSet.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicTexture2DSet Implementation
//----------------------------------------------------------------------------

GraphicTexture2DSet::GraphicTexture2DSet( )
{
	mTextureSize	= PointU::cZeroPoint;
	mSpace			= PointU::cZeroPoint;
}

GraphicTexture2DSet::~GraphicTexture2DSet( )
{
	RemoveAllImages( );
}

_ubool GraphicTexture2DSet::Initialize( const PointU& size, const PointU& space )
{
	if ( size.x == 0 || size.y == 0 )
		return _false;

	mTextureSize	= size;
	mSpace			= space;

	return _true;
}

_void GraphicTexture2DSet::Cleanup( )
{
	for ( _dword i = 0; i < mTextureImageFillers.Number( ); i ++ )
		mTextureImageFillers[i]->Cleanup( );
}

IGraphicTexture2DPassRef GraphicTexture2DSet::AddImage( WStringPtr name, IStreamReader* stream_reader, _ubool stand_alone_mode )
{
	IImageFileRef image_file = GetInterfaceFactory( )->ParseImageFile( stream_reader );
	if ( image_file.IsNull( ) )
		return _null;

	return AddImage( name, image_file, stand_alone_mode );
}

IGraphicTexture2DPassRef GraphicTexture2DSet::AddImage( WStringPtr name, IImageFile* imagefile, _ubool stand_alone_mode )
{
	if ( imagefile == _null )
		return _null;

	return AddImage( name, imagefile->GetWidth( ), imagefile->GetHeight( ), imagefile->GetPixelFormat( ), imagefile->GetPixelBuffer( ), stand_alone_mode );
}

IGraphicTexture2DPassRef GraphicTexture2DSet::AddImage( WStringPtr name, _dword width, _dword height, _PIXEL_FORMAT format, const _byte* pixelbuffer, _ubool stand_alone_mode )
{
	// Check the max texture limited
	if ( width > mTextureSize.x || height > mTextureSize.y )
	{
		WLOG_ERROR_4( L"Add image failed, due to its size (%dx%d) is out of range (%dx%d)", width, height, mTextureSize.x, mTextureSize.y );
		return _null;
	}

	// Try to add image into the biggest texture info
	for ( _dword i = 0; i < mTextureImageFillers.Number( ); i ++ )
	{
		GraphicTexture2DImageFiller* tex_image_filler = mTextureImageFillers[i];
		EGE_ASSERT( tex_image_filler != _null );

		// Skip for stand alone mode
		if ( tex_image_filler->IsStandAloneMode( ) && tex_image_filler->GetSubTexturesNumber( ) != 0 )
			continue;

		// Check whether it's compatible
		if ( tex_image_filler->GetPixelFormat( ) != format )
			continue;

		// Try to fill image into texture 2D
		IGraphicTexture2DPassRef sub_texture = tex_image_filler->CreateSubTexture2D( name, width, height, pixelbuffer );
		if ( sub_texture.IsNull( ) )
			continue; // fill failed, it's full

		// Feedback the sub texture if succeed to add into the existing texture
		return sub_texture;
	}

	// If it's stand alone mode then we try to use the best fit size for texture
	PointU tex_size = mTextureSize, space = mSpace;
	if ( stand_alone_mode )
	{
		tex_size.x	= Math::UpperBoundPowerOf2( width );
		tex_size.y	= Math::UpperBoundPowerOf2( height );
		space		= PointU::cZeroPoint;
	}

	// Create texture info when it's empty or all existing textures are full
	GraphicTexture2DImageFiller* new_tex_image_filler = new GraphicTexture2DImageFiller( stand_alone_mode );
	if ( new_tex_image_filler->Initialize( format, tex_size, space ) == _false )
		{ EGE_DELETE( new_tex_image_filler ); return _null; }

	mTextureImageFillers.Append( new_tex_image_filler );

	return new_tex_image_filler->CreateSubTexture2D( name, width, height, pixelbuffer );
}

_void GraphicTexture2DSet::RemoveImage( WStringPtr name )
{
	for ( _dword i = 0; i < mTextureImageFillers.Number( ); i ++ )
	{
		GraphicTexture2DImageFiller* tex_image_filler = mTextureImageFillers[i];
		EGE_ASSERT( tex_image_filler != _null );

		tex_image_filler->RemoveSubTexture2D( name );

		if ( tex_image_filler->GetSubTexturesNumber( ) == 0 )
		{
			EGE_DELETE( tex_image_filler );
			mTextureImageFillers.RemoveByIndex( i -- );
		}
	}
}

_void GraphicTexture2DSet::RemoveAllImages( )
{
	for ( _dword i = 0; i < mTextureImageFillers.Number( ); i ++ )
	{
		EGE_DELETE( mTextureImageFillers[i] );
	}

	mTextureImageFillers.Clear( _true );
}
