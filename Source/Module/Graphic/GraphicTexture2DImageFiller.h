//! @file     GraphicTexture2DImageFiller.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicTexture2DImageFiller
//----------------------------------------------------------------------------

class GraphicTexture2DImageFiller
{
private:
	struct SubTextureInfo
	{
		WString					mName;
		RectU					mRect;
		IGraphicTexture2DRef	mSubTexture;

		operator WStringPtr( ) const
			{ return mName; }

		SubTextureInfo( )
		{
			mRect = RectU::cNull;
		}
	};
	typedef Array< SubTextureInfo > SubTextureInfoArray;

private:
	//!	True indicates it's stand alone mode
	_ubool					mIsStandAloneMode;

	//!	The pixel format
	_PIXEL_FORMAT			mPixelFormat;

	//!	The 2D texture filler
	IImageFillerRef			mImageFiller;
	//!	The 2D texture
	IGraphicTexture2DRef	mTexture;
	//!	The sub textures
	SubTextureInfoArray		mSubTextures;

public:
	GraphicTexture2DImageFiller( _ubool stand_alone_mode );
	~GraphicTexture2DImageFiller( );

public:
	EGE_IS_ACCESSOR( StandAloneMode )
	EGE_GET_ACCESSOR_CONST( _PIXEL_FORMAT, PixelFormat )

public:
	//!	Initialize.
	//!	@param		format		The texture pixel format.
	//!	@param		size		The texture filler size.
	//!	@param		space		The space size between images in pixel.
	//! @return		True indicates success, false indicates failure.
	_ubool Initialize( _PIXEL_FORMAT format, const PointU& size, const PointU& space );

	//!	Cleanup.
	_void Cleanup( );

	//!	Get the sub textures number.
	_dword GetSubTexturesNumber( ) const;

	//!	Create sub-texture 2D.
	IGraphicTexture2DPassRef CreateSubTexture2D( WStringPtr name, _dword width, _dword height, const _byte* pixelbuffer );
	//!	Remove sub-texture 2D.
	_void RemoveSubTexture2D( WStringPtr name );
};

//----------------------------------------------------------------------------
// GraphicTexture2DImageFiller Implementation
//----------------------------------------------------------------------------

}