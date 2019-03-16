//! @file     D3D11Font.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D3D11Drv-Font Implementation
//----------------------------------------------------------------------------

FontRHIPassRef D3D11Drv::CreateFontFromStream( const FontInitializerRHI& initializer, IStreamReader* stream_reader )
{
	return _null;
}

FontRHIPassRef D3D11Drv::CloneFont( const FontRHI* font )
{
	return _null;
}

const FontInitializerRHI& D3D11Drv::GetFontInfo( FontRHI* font ) const
{
	static FontInitializerRHI sFontInitializerRHI;
	return sFontInitializerRHI;
}

_float D3D11Drv::GetCharAdvance( FontRHI* font, _dword code ) const
{
	return 0.0f;
}

_float D3D11Drv::GetCharMaxHeight( FontRHI* font ) const
{
	return 0.0f;
}

IFontFace* D3D11Drv::GetFontFace( FontRHI* font ) const
{
	return _null;
}

const FontCodeRHI* D3D11Drv::GetFontCode( FontRHI* font, _dword code, _dword stroke_size ) const
{
	return _null;
}

_void D3D11Drv::ClearFontCaches( FontRHI* font )
{
}
