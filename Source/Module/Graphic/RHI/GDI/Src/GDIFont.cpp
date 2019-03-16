//! @file     GDIFont.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GDIDrv-Font Implementation
//----------------------------------------------------------------------------

FontRHIPassRef GDIDrv::CreateFontFromStream( const FontInitializerRHI& initializer, IStreamReader* stream_reader )
{
	// Create the font collection
	Gdiplus::GpFontCollection* font_collection = _null;
	if ( GDI::GdipNewPrivateFontCollection( &font_collection ) != Gdiplus::Ok )
		return _null;

	// Add font from memory
	if ( GDI::GdipPrivateAddMemoryFont( font_collection, stream_reader->GetBuffer( ), stream_reader->GetSize( ) ) != Gdiplus::Ok )
	{
		GDI::GdipDeletePrivateFontCollection( &font_collection );
		return _null;
	}

	// Create font
	GDIFont* font = new GDIFont( font_collection, initializer );
	if ( font->Initialize( ) == _false )
	{
		GDI::GdipDeletePrivateFontCollection( &font_collection );
		return _null;
	}

	return font;
}

FontRHIPassRef GDIDrv::CloneFont( const FontRHI* font )
{
	return _null;
}

const FontInitializerRHI& GDIDrv::GetFontInfo( FontRHI* font ) const
{
	DYNAMIC_CAST_GDIRESOURCE( Font, font );

	return gdi_font->GetInfo( );
}

_float GDIDrv::GetCharAdvance( FontRHI* font, _dword code ) const
{
	return 0.0f;
}

_float GDIDrv::GetCharMaxHeight( FontRHI* font ) const
{
	return 0.0f;
}

IFontFace* GDIDrv::GetFontFace( FontRHI* font ) const
{
	return _null;
}

const FontCodeRHI* GDIDrv::GetFontCode( FontRHI* font, _dword code, _dword stroke_size ) const
{
	return _null;
}

_void GDIDrv::ClearFontCaches( FontRHI* font )
{
}

//----------------------------------------------------------------------------
// GDIFont Implementation
//----------------------------------------------------------------------------

GDIFont::GDIFont( Gdiplus::GpFontCollection* font, const FontInitializerRHI& info ) : mGDIFontCollection( font ), mInfo( info )
{
	mGDIFontFamilyNumber	= 0;

	mGDIFont				= _null;
	mGDIStringFormat		= _null;

	EGE_INIT_ARRAY( mGDIFontFamilyBuffer );
}

GDIFont::~GDIFont( )
{
	// Release GDI string format
	if ( mGDIStringFormat != _null )
		GDI::GdipDeleteStringFormat( mGDIStringFormat );

	// Release GDI font
	if ( mGDIFont != _null )
		GDI::GdipDeleteFont( mGDIFont );

	// Delete font collection
	if ( mGDIFontCollection != _null )
		GDI::GdipDeletePrivateFontCollection( &mGDIFontCollection );
}

_ubool GDIFont::Initialize( )
{
	// Get the font family list
	if ( GDI::GdipGetFontCollectionFamilyList( mGDIFontCollection, _MAX_FONT_FAMILY_NUMBER, mGDIFontFamilyBuffer, (INT*) &mGDIFontFamilyNumber ) != Gdiplus::Ok )
		return _false;

	// We must have one font family info at least
	if ( mGDIFontFamilyNumber == 0 )
		return _false;

	// Initialize the font style
	_dword font_style = Gdiplus::FontStyleRegular;
	if ( mInfo.mStyles & _FONT_STYLE_BOLD )
		font_style |= Gdiplus::FontStyleBold;
	if ( mInfo.mStyles & _FONT_STYLE_ITALIC )
		font_style |= Gdiplus::FontStyleItalic;
	if ( mInfo.mStyles & _FONT_STYLE_UNDERLINE )
		font_style |= Gdiplus::FontStyleUnderline;

	// Create GDI font
	if ( GDI::GdipCreateFont( mGDIFontFamilyBuffer[0], (_float) mInfo.mSize, font_style, Gdiplus::UnitPoint, &mGDIFont ) != Gdiplus::Ok )
		return _false;

	// Create GDI font format
	if ( GDI::GdipCreateStringFormat( 0, LANG_NEUTRAL, &mGDIStringFormat ) != Gdiplus::Ok )
		return _false;

	return _true;
}