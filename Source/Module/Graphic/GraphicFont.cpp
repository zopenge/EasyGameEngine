//! @file     GraphicFont.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicFont Implementation
//----------------------------------------------------------------------------

GraphicFont::GraphicFont( FontRHI* resource ) : mResource( resource )
{
	// Get the font face interface
	mFontFace = gDynamicRHI->GetFontFace( mResource );
	EGE_ASSERT( mFontFace.IsValid( ) );

	// Initialize effect
	InitEffect( );
}

GraphicFont::~GraphicFont( )
{
}

_ubool GraphicFont::InitEffect( )
{
	// Get the internal effect type
	if ( mFontFace->IsImageType( ) )
		mEffect = GetGraphicResourceManager( )->CreateEffectFromResName( WSTROBJ( eTex0 ) );
	else
		mEffect = GetGraphicResourceManager( )->CreateEffectFromResName( WSTROBJ( eOverlayDrawText ) );

	if ( mEffect.IsNull( ) )
		return _false;

	return _true;
}

IObject* GraphicFont::CloneTo( _ubool standalone ) const
{
	FontRHIRef resource = mResource->CloneToPassRef< FontRHI >( standalone );
	if ( resource.IsNull( ) )
		return _null;

	GraphicFont* font = new GraphicFont( resource );

	for ( _dword i = 0; i < mSubFonts.Number( ); i ++ )
	{
		IGraphicFontPassRef sub_font = mSubFonts[i]->CloneToPassRef< IGraphicFont >( standalone );
		if ( sub_font.IsNull( ) )
			{ EGE_RELEASE( font ); return _null; }

		font->AddSubFont( sub_font.GetPtr( ) );
	}

	return font;
}

_void GraphicFont::ClearCaches( )
{
	gDynamicRHI->ClearFontCaches( mResource );

	for ( _dword i = 0; i < mSubFonts.Number( ); ++ i )
		mSubFonts[i]->ClearCaches( );
}

_dword GraphicFont::GetFontSize( ) const
{
	return mFontFace->GetFontSize( );
}

_ubool GraphicFont::SetFontSize( _dword size )
{
	return mFontFace->SetFontSize( size );
}

IGraphicEffect* GraphicFont::GetEffect( ) const
{
	return mEffect.GetPtr( );
}

const FontInitializerRHI& GraphicFont::GetFontInfo( ) const
{
	return gDynamicRHI->GetFontInfo( mResource.GetPtr( ) );
}

FontRHI* GraphicFont::GetResource( ) const
{
	return mResource.GetPtr( );
}

IFontFace* GraphicFont::GetFontFace( ) const
{
	return mFontFace.GetPtr( );
}

const FontCodeRHI* GraphicFont::GetFontCode( _dword code, IGraphicFont*& code_font )
{
	const FontCodeRHI* font_code_rhi = gDynamicRHI->GetFontCode( mResource, code );
	if ( font_code_rhi == _null )
	{
		for ( _dword i = 0; i < mSubFonts.Number( ); ++ i )
		{
			font_code_rhi = mSubFonts[i]->GetFontCode( code, code_font );
			if ( font_code_rhi != _null )
				return font_code_rhi;
		}

		return _null;
	}

	code_font = this;
	return font_code_rhi;
}

const Array< IGraphicFontRef >& GraphicFont::GetSubFonts( ) const
{
	return mSubFonts;
}

_void GraphicFont::AddSubFont( IGraphicFont* font )
{
	if ( font == _null )
		return;

	mSubFonts.Append( font );
}

_void GraphicFont::ClearAllSubFonts( )
{
	mSubFonts.Clear( _true );
}