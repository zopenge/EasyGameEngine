//! @file     IFontFace.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IFontFace
//----------------------------------------------------------------------------

class IFontFace : public IObject
{
public:
	//!	Get the font face type.
	//!	@param		none.
	//!	@return		The font face type.
	virtual _FONT_FACE_TYPE GetFaceType( ) const PURE;

	//!	Check whether has character.
	//!	@param		code	The character code.
	//!	@return		True indicates it has character.
	virtual _ubool HasCharacter( _dword code ) const PURE;

	//!	Get the char size.
	//!	@param		code	The character code.
	//!	@return		The char size.
	virtual PointU GetCharSize( _dword code ) PURE;
	//!	Get the char max height.
	//!	@param		none.
	//!	@return		The char max height.
	virtual _dword GetCharMaxHeight( ) const PURE;

	//!	Get UV.
	//!	@param		x			The x position.
	//!	@param		y			The y position.
	//!	@return		The UV coordinate.
	virtual Vector2 GetUV( _dword x, _dword y ) const PURE;

	//!	Get the amount between characters.
	//!	@param		first_code	The first code.
	//!	@param		second_code	The second code.
	//!	@return		The amount.
	virtual _int GetAmountBetweenCharacters( _dword first_code, _dword second_code ) const PURE;

	//!	Get the font size.
	//!	@param		none.
	//!	@return		The font size.
	virtual _dword GetFontSize( ) const PURE;
	//!	Set the font size.
	//!	@param		size	The font size.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetFontSize( _dword size ) PURE;
	//!	Get the font code info.
	//!	@param		code	The character code.
	//!	@param		flags	The character load flags, @see _FONT_FACE_LOAD_FLAGS.
	//!	@param		info	The character code info.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetFontCodeInfo( _dword code, _dword flags, FontFaceCodeInfoBase& info ) PURE;

	//!	Render character.
	//!	@param		code	The character code.
	//!	@param		info	The character code info.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RenderCharacter( _dword code, FontFaceCodeInfo& info ) PURE;
	//!	Render character with stroke size.
	//!	@param		code		The character code.
	//!	@param		stroke_size	The stroke size.
	//!	@param		stroke_info	The character code stroke info.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RenderCharacterByStrokeInfo( _dword code, _dword stroke_size, FontFaceCodeInfo& stroke_info ) PURE;
	//!	Render character with blur size and factor.
	//!	@param		code		The character code.
	//!	@param		blur_size	The blur size.
	//!	@param		blur_factor	The blur factor.
	//!	@param		blur_info	The character code blur info.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RenderCharacterByBlurInfo( _dword code, _dword blur_size, _float blur_factor, FontFaceCodeInfo& blur_info ) PURE;

	//!	Check whether it's image type.
	//!	@param		none.
	//!	@return		True indicates it's image type.
	virtual _ubool IsImageType( ) const PURE;
	//!	Get the image codes number.
	//!	@remark		Only supports font image type.
	//!	@param		none.
	//!	@return		The number of codes.
	virtual _dword GetImageCodesNumber( ) const PURE;
	//!	Get the image code info by index.
	//!	@remark		Only supports font image type.
	//!	@param		index		The index of image code.
	//!	@param		info		The info of image code.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetImageCodeInfoByIndex( _dword index, FontFaceCodeInfo& info ) const PURE;
	//!	Get the image pixel buffer.
	//!	@remark		Only supports font image type.
	//!	@param		size		The image size.
	//!	@return		The pixel buffer format in ARGB.
	virtual const _dword* GetImagePixelBuffer( PointU& size ) const PURE;
};

}