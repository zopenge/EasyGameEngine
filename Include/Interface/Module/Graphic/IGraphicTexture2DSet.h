//! @file     IGraphicTexture2DSet.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicTexture2DSet
//----------------------------------------------------------------------------

class IGraphicTexture2DSet : public IObject
{
public:
	//!	Cleanup.
	//!	@remark		Remove unused sub textures.
	//!	@param		none.
	//!	@return		none.
	virtual _void Cleanup( ) PURE;

	//!	Add image from stream.
	//!	@param		name				The texture name.
	//! @param		stream_reader		The stream reader.
	//! @param		stand_alone_mode	True indicates use the whole texture instead without any combination.
	//! @return		The texture 2D interface.
	virtual IGraphicTexture2DPassRef AddImage( WStringPtr name, IStreamReader* stream_reader, _ubool stand_alone_mode ) PURE;
	//!	Add image from image file.
	//!	@param		name				The texture name.
	//! @param		imagefile			The image file.
	//! @param		stand_alone_mode	True indicates use the whole texture instead without any combination.
	//! @return		The texture 2D interface.
	virtual IGraphicTexture2DPassRef AddImage( WStringPtr name, IImageFile* imagefile, _ubool stand_alone_mode ) PURE;
	//!	Add image from pixel buffer.
	//!	@param		name				The texture name.
	//!	@param		width				The image width.
	//!	@param		height				The image height.
	//!	@param		format				The image pixel format.
	//!	@param		pixelbuffer			The image pixel buffer.
	//! @param		stand_alone_mode	True indicates use the whole texture instead without any combination.
	//! @return		The texture 2D interface.
	virtual IGraphicTexture2DPassRef AddImage( WStringPtr name, _dword width, _dword height, _PIXEL_FORMAT format, const _byte* pixelbuffer, _ubool stand_alone_mode ) PURE;
	//!	Remove image.
	//!	@param		name				The texture name.
	//!	@return		none.
	virtual _void RemoveImage( WStringPtr name ) PURE;
	//!	Remove all images.
	//!	@param		none.
	//!	@return		none.
	virtual _void RemoveAllImages( ) PURE;
};

}