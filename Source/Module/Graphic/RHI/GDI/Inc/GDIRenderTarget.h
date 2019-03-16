//! @file     GDIRenderTarget.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GDISurface
//----------------------------------------------------------------------------

class GDISurface : public SurfaceRHI
{
private:
	//!	The graphic DC
	HDC						mCompatibleDC;
	//!	The compatible bitmap
	HBITMAP					mCompatibleBitmap;

	//!	The GDI graphic
	Gdiplus::GpGraphics*	mGDIGraphics;
	//!	The GDI pen
	Gdiplus::GpPen*			mGDIPen;
	//!	The GDI solid color brush
	Gdiplus::GpSolidFill*	mGDISolidColorBrush;

	//!	The surface size
	PointU					mSize;

	//!	The texture
	Texture2DRHIRef			mTexture;

public:
	GDISurface( const PointU& size, Texture2DRHI* texture );
	virtual ~GDISurface( );

public:
	//!	Create compatible DC.
	//!	@param		hdc		The target DC.
	//!	@return		True indicates successful, otherwise indicates failure.
	_ubool CreateCompatibleDC( HDC hdc );

	//!	Get the pen.
	//!	@param		width	The pen width.
	//!	@param		color	The pen color.
	//!	@return		The GDI pen.
	Gdiplus::GpPen* GetGDIPen( _float width, const Color& color );
	//!	Get the solid color brush.
	//!	@param		color	The brush color.
	//!	@return		The GDI solid color brush.
	Gdiplus::GpSolidFill* GetGDISolidColorBrush( const Color& color );

public:
	//!	Get the compatible DC.
	EGE_GET_ACCESSOR_CONST( HDC, CompatibleDC )
	//!	Get the compatible bitmap.
	EGE_GET_ACCESSOR_CONST( HBITMAP, CompatibleBitmap )
	//!	Get the GDI graphic
	EGE_GET_ACCESSOR_CONST( Gdiplus::GpGraphics*, GDIGraphics )
	//!	Get the surface size.
	EGE_GETR_ACCESSOR_CONST( PointU, Size )
	//!	Get the texture.
	EGE_GET_ACCESSOR( Texture2DRHI*, Texture )
};

}