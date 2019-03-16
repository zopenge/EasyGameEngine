//! @file     D2DRenderTarget.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// D2DSurface
//----------------------------------------------------------------------------

class D2DSurface : public SurfaceRHI
{
private:
	//!	The D2D render target with DC
	RefPtr< ID2D1DCRenderTarget >	mD2DRenderTarget;
	//!	The compatible DC
	HDC								mCompatibleDC;
	//!	The compatible bitmap
	HBITMAP							mCompatibleBitmap;

	//!	The solid color brush
	RefPtr< ID2D1SolidColorBrush >	mD2DSolidColorBrush;

	//!	The surface size
	PointU							mSize;

public:
	D2DSurface( ID2D1DCRenderTarget* rendertarget, const PointU& size );
	virtual ~D2DSurface( );

public:
	//!	Create compatible DC.
	//!	@param		hdc		The target DC.
	//!	@return		True indicates successful, otherwise indicates failure.
	_ubool CreateCompatibleDC( HDC hdc );
	//!	Bind the target DC.
	//!	@param		hdc		The target DC.
	//!	@param		rect	The region of DC.
	//!	@return		True indicates successful, otherwise indicates failure.
	_ubool BindDC( HDC hdc, const RectI& rect );

	//!	Get the solid color brush.
	//!	@param		color	The brush color.
	//!	@return		The D2D solid color brush.
	ID2D1SolidColorBrush* GetD2DSolidColorBrush( const Color& color );

public:
	//!	Get the D2D render target.
	EGE_GET_ACCESSOR( ID2D1DCRenderTarget*, D2DRenderTarget )
	//!	Get the compatible DC.
	EGE_GET_ACCESSOR_CONST( HDC, CompatibleDC )
	//!	Get the compatible bitmap.
	EGE_GET_ACCESSOR_CONST( HBITMAP, CompatibleBitmap )
	//!	Get the surface size.
	EGE_GETR_ACCESSOR_CONST( PointU, Size )
};

}