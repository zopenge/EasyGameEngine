//! @file     GraphicTexture2DSet.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicTexture2DSet
//----------------------------------------------------------------------------

class GraphicTexture2DSet : public INTERFACE_OBJECT_IMPL( IGraphicTexture2DSet )
{
private:
	//!	The texture image filler array
	typedef Array< GraphicTexture2DImageFiller* > ImageFillerArray;

private:
	//!	The texture size
	PointU				mTextureSize;
	//!	The space size of images
	PointU				mSpace;

	//!	The texture image fillers
	ImageFillerArray	mTextureImageFillers;

public:
	GraphicTexture2DSet( );
	virtual ~GraphicTexture2DSet( );

public:
	//!	Initialize.
	//!	@param		size		The texture filler size.
	//!	@param		space		The space size between images in pixel.
	//! @return		True indicates success, false indicates failure.
	_ubool Initialize( const PointU& size, const PointU& space );

// IGraphicTexture2DSet Interface
public:
	virtual _void						Cleanup( ) override;

	virtual IGraphicTexture2DPassRef	AddImage( WStringPtr name, IStreamReader* stream_reader, _ubool stand_alone_mode ) override;
	virtual IGraphicTexture2DPassRef	AddImage( WStringPtr name, IImageFile* imagefile, _ubool stand_alone_mode ) override;
	virtual IGraphicTexture2DPassRef	AddImage( WStringPtr name, _dword width, _dword height, _PIXEL_FORMAT format, const _byte* pixelbuffer, _ubool stand_alone_mode ) override;
	virtual _void						RemoveImage( WStringPtr name ) override;
	virtual _void						RemoveAllImages( ) override;
};

//----------------------------------------------------------------------------
// GraphicTexture2DSet Implementation
//----------------------------------------------------------------------------

}