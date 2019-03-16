//! @file     IFNTFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IFNTFile
//----------------------------------------------------------------------------

class IFNTFile : public IBaseFile
{
public:
	//!	Get the page number.
	//!	@param		none.
	//!	@return		The page number.
	virtual _dword GetPageNumber( ) const PURE;
	//!	Get the image file name from page.
	//!	@param		index	The page index.
	//!	@return		The image file name.
	virtual WStringPtr GetPageImageFileName( _dword page_index ) const PURE;

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

	//!	Get the amount between characters.
	//!	@param		first_code	The first code.
	//!	@param		second_code	The second code.
	//!	@return		The amount.
	virtual _int GetAmountBetweenCharacters( _dword first_code, _dword second_code ) const PURE;

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
};

}