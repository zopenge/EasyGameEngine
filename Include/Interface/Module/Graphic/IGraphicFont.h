//! @file     IGraphicFont.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicFont
//----------------------------------------------------------------------------

class IGraphicFont : public ITFlagsObject< IObject >
{
public:
	//!	The flags
	enum _FLAG
	{
		_FLAG_USE_SMALL_HEIGHT = 1 << 0,
	};

public:
	//!	Clear caches.
	//!	@param		none.
	//!	@return		none.
	virtual _void ClearCaches( ) PURE;

	//!	Get the font size.
	//!	@param		none.
	//!	@return		The font size.
	virtual _dword GetFontSize( ) const PURE;
	//!	Set the font size.
	//!	@param		size	The font size.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetFontSize( _dword size ) PURE;

	//!	Get the effect.
	//!	@param		none.
	//!	@return		The effect.
	virtual IGraphicEffect* GetEffect( ) const PURE;

	//!	Get the font flags.
	//!	@param		none.
	//!	@return		The font flags.
	virtual const FontInitializerRHI& GetFontInfo( ) const PURE;
	//!	Get the resource handle.
	//!	@param		none.
	//!	@return		The font resource handle.
	virtual FontRHI* GetResource( ) const PURE;
	//!	Get the font face.
	//!	@param		none.
	//!	@return		The font face.
	virtual IFontFace* GetFontFace( ) const PURE;

	//!	Get the font code info.
	//!	@remark		We will render the code to texture if it's not existing.
	//!	@param		code		The font code.
	//! @param		codle_font	The code's font.
	//!	@return		The font code info, null indicates failure.
	virtual const FontCodeRHI* GetFontCode( _dword code, IGraphicFont*& code_font ) PURE;

	//!	Get sub fonts.
	//!	@param		none.
	//!	@return		The sub fonts.
	virtual const Array< IGraphicFontRef >& GetSubFonts( ) const PURE;
	//!	Add sub font.
	//!	@param		font		The sub font.
	//!	@return		none.
	virtual _void AddSubFont( IGraphicFont* font ) PURE;
	//!	Clear all sub fonts.
	//!	@param		none.
	//!	@return		none.
	virtual _void ClearAllSubFonts( ) PURE;
};

}