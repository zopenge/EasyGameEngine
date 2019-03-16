//! @file     GLFont.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLDrv-Font Implementation
//----------------------------------------------------------------------------

FontRHIPassRef GLDrv::CreateFontFromStream( const FontInitializerRHI& initializer, IStreamReader* stream_reader )
{
	GLFont* font = new GLFont( );
	if ( font->Initialize( initializer, stream_reader ) == _false )
		{ EGE_RELEASE( font ); return _null; }
	
	return font;
}

const FontInitializerRHI& GLDrv::GetFontInfo( FontRHI* font ) const
{
	DYNAMIC_CAST_GLRESOURCE( Font, font );

	return gl_font->GetInfo( );
}

_float GLDrv::GetCharAdvance( FontRHI* font, _dword code ) const
{
	DYNAMIC_CAST_GLRESOURCE( Font, font );

	return (_float) gl_font->GetFontFace( )->GetCharSize( code ).x;
}

_float GLDrv::GetCharMaxHeight( FontRHI* font ) const
{
	DYNAMIC_CAST_GLRESOURCE( Font, font );

	return (_float) gl_font->GetFontFace( )->GetCharMaxHeight( );
}

IFontFace* GLDrv::GetFontFace( FontRHI* font ) const
{
	DYNAMIC_CAST_GLRESOURCE( Font, font );

	return gl_font->GetFontFace( );
}

const FontCodeRHI* GLDrv::GetFontCode( FontRHI* font, _dword code ) const
{
	DYNAMIC_CAST_GLRESOURCE( Font, font );

	return gl_font->GetFontCode( code );
}

const FontCodeRHI* GLDrv::GetFontCodeByStrokeEffect( FontRHI* font, _dword code, _dword stroke_size ) const
{
	DYNAMIC_CAST_GLRESOURCE( Font, font );

	return gl_font->GetFontCodeByStrokeInfo( code, stroke_size );
}

const FontCodeRHI* GLDrv::GetFontCodeByBlurEffect( FontRHI* font, _dword code, _dword blur_size, _dword blur_factor ) const
{
	DYNAMIC_CAST_GLRESOURCE( Font, font );

	return gl_font->GetFontCodeByBlurInfo( code, blur_size, blur_factor );
}

_void GLDrv::ClearFontCaches( FontRHI* font )
{
	DYNAMIC_CAST_GLRESOURCE( Font, font );

	gl_font->ClearCaches( );
}

//----------------------------------------------------------------------------
// GLFont Implementation
//----------------------------------------------------------------------------

GLFont::GLFont( )
{
	mFontTextureSet = _null;
}

GLFont::~GLFont( )
{
	EGE_DELETE( mFontTextureSet );
}

_ubool GLFont::Initialize( const FontInitializerRHI& initializer, IStreamReader* stream_reader )
{
	mInfo = initializer;

	// Create font texture set
	mFontTextureSet = new RenderFontTextureSet( );

	// Create font face of freetyp2
	mFontFace = GetInterfaceFactory( )->CreateFontFace( initializer.mType, stream_reader );
	if ( mFontFace.IsNull( ) )
		return _false;

	// Set the font size
	mFontFace->SetFontSize( mInfo.mSize );

	return _true;
}

IObject* GLFont::CloneTo( _ubool standalone ) const
{
	GLFont* font			= new GLFont( );
	font->mInfo				= mInfo;
	font->mFontTextureSet	= new RenderFontTextureSet( );
	font->mFontFace			= mFontFace->CloneToPassRef< IFontFace >( standalone );
	if ( font->mFontFace.IsNull( ) )
		{ EGE_RELEASE( font ); return _null; }

	font->mFontFace->SetFontSize( font->mInfo.mSize );

	return font;
}

_void GLFont::ClearCaches( )
{
	mFontTextureSet->ClearCaches( );
}

const FontCodeRHI* GLFont::GetFontCode( _dword code )
{
	return mFontTextureSet->CreateCode( mFontFace, code );
}

const FontCodeRHI* GLFont::GetFontCodeByStrokeInfo( _dword code, _dword stroke_size )
{
	return mFontTextureSet->CreateCodeByStrokeInfo( mFontFace, code, stroke_size );
}

const FontCodeRHI* GLFont::GetFontCodeByBlurInfo( _dword code, _dword blur_size, _dword blur_factor )
{
	return mFontTextureSet->CreateCodeByBlurInfo( mFontFace, code, blur_size, blur_factor );
}