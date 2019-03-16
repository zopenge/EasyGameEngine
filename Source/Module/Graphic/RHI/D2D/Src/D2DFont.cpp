\//! @file     D2DFont.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D2DDrv-Font Implementation
//----------------------------------------------------------------------------

FontRHIPassRef D2DDrv::CreateFontFromStream( const FontInitializerRHI& initializer, IStreamReader* stream_reader )
{
	return _null;
}

FontRHIPassRef D2DDrv::CloneFont( const FontRHI* font )
{
	return _null;
}

const FontInitializerRHI& D2DDrv::GetFontInfo( FontRHI* font ) const
{
	static FontInitializerRHI sFontInitializerRHI;
	return sFontInitializerRHI;
}

_float D2DDrv::GetCharAdvance( FontRHI* font, _dword code ) const
{
	return 0.0f;
}

_float D2DDrv::GetCharMaxHeight( FontRHI* font ) const
{
	return 0.0f;
}

IFontFace* D2DDrv::GetFontFace( FontRHI* font ) const
{
	return _null;
}

const FontCodeRHI* D2DDrv::GetFontCode( FontRHI* font, _dword code, _dword stroke_size ) const
{
	return _null;
}

_void D2DDrv::ClearFontCaches( FontRHI* font )
{
}

//----------------------------------------------------------------------------
// D2DFont Implementation
//----------------------------------------------------------------------------

D2DFont::D2DFont( )
{

}

D2DFont::~D2DFont( )
{

}