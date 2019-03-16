//! @file     GraphicFont.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicFont
//----------------------------------------------------------------------------

class GraphicFont : public INTERFACE_OBJECT_IMPL( TFlagsObject< IGraphicFont > )
{
private:
	typedef Array< IGraphicFontRef > GraphicFontArray;

private:
	//!	The font face
	IFontFaceRef		mFontFace;
	//!	The RHI font resource
	FontRHIRef			mResource;

	//!	The graphic effect
	IGraphicEffectRef	mEffect;

	//!	The sub fonts
	GraphicFontArray	mSubFonts;

private:
	//!	Initialize effect.
	_ubool InitEffect( );

public:
	GraphicFont( FontRHI* resource );
	virtual ~GraphicFont( );

// IObject Interface
public:
	virtual IObject*						CloneTo( _ubool standalone ) const override;

// IGraphicFont Interface
public:
	virtual _void							ClearCaches( ) override;

	virtual _dword							GetFontSize( ) const override;
	virtual _ubool							SetFontSize( _dword size ) override;

	virtual IGraphicEffect*					GetEffect( ) const override;

	virtual const FontInitializerRHI&		GetFontInfo( ) const override;
	virtual FontRHI*						GetResource( ) const override;
	virtual IFontFace*						GetFontFace( ) const override;

	virtual const FontCodeRHI*				GetFontCode( _dword code, IGraphicFont*& code_font ) override;

	virtual const Array< IGraphicFontRef >& GetSubFonts( ) const override;
	virtual _void							AddSubFont( IGraphicFont* font ) override;
	virtual _void							ClearAllSubFonts( ) override;
};

//----------------------------------------------------------------------------
// GraphicFont Implementation
//----------------------------------------------------------------------------

}