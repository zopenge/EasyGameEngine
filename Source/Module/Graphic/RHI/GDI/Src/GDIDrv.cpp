//! @file     GDIDrv.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GDIMethods
//----------------------------------------------------------------------------

EGE_BEGIN_NAMESPACE_2( EGE, GDI )

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) _##FuncName FuncName = _null;
#include "Module/Graphic/RHI/GDI/Inc/GDIMethods.h"
#undef DEFINE_FUNC_PTR

EGE_END_NAMESPACE_2( )

//----------------------------------------------------------------------------
// GDIDrv Implementation
//----------------------------------------------------------------------------

GDIDrv::GDIDrv( )
{
	mGDIToken		= 0;

	mGDIClearColor	= Color::cNull;
}

GDIDrv::~GDIDrv( )
{
	// Shutdown GUI-plus device
	if ( mGDIToken != 0 && GDI::GdiplusShutdown != _null )
		(*GDI::GdiplusShutdown)( mGDIToken );
}

_ubool GDIDrv::LoadGDIPlusLibrary( )
{
	// Load GDI+ libraries
	_handle gdiplus_dll = Platform::LoadLibrary( "gdiplus.dll" );
	if ( gdiplus_dll == _null )
		return _false;

	GET_FUNC_PTR( GDI, gdiplus_dll, GdiplusStartup )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdiplusShutdown )
	// ImageAttributes APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateImageAttributes )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCloneImageAttributes )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDisposeImageAttributes )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetImageAttributesToIdentity )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipResetImageAttributes )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetImageAttributesColorMatrix )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetImageAttributesThreshold )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetImageAttributesGamma )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetImageAttributesNoOp )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetImageAttributesColorKeys )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetImageAttributesOutputChannel )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetImageAttributesOutputChannelColorProfile )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetImageAttributesRemapTable )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetImageAttributesWrapMode )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageAttributesAdjustedPalette )
	// Graphics APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFlush )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateFromHDC )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateFromHDC2 )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateFromHWND )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateFromHWNDICM )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDeleteGraphics )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetDC )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipReleaseDC )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetCompositingMode )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetCompositingMode )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetRenderingOrigin )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetRenderingOrigin )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetCompositingQuality )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetCompositingQuality )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetSmoothingMode )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetSmoothingMode )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPixelOffsetMode )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPixelOffsetMode )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetTextRenderingHint )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetTextRenderingHint )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetTextContrast )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetTextContrast )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetInterpolationMode )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetInterpolationMode )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetWorldTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipResetWorldTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipMultiplyWorldTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipTranslateWorldTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipScaleWorldTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipRotateWorldTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetWorldTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipResetPageTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPageUnit )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPageScale )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPageUnit )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPageScale )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetDpiX )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetDpiY )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipTransformPoints )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipTransformPointsI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetNearestColor )
	// Image APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipLoadImageFromStream )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipLoadImageFromFile )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipLoadImageFromStreamICM )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipLoadImageFromFileICM )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCloneImage )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDisposeImage )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSaveImageToFile )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSaveImageToStream )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSaveAdd )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSaveAddImage )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageGraphicsContext )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageBounds )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageDimension )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageType )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageWidth )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageHeight )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageHorizontalResolution )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageVerticalResolution )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageFlags )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageRawFormat )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImagePixelFormat )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageThumbnail )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetEncoderParameterListSize )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetEncoderParameterList )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipImageGetFrameDimensionsCount )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipImageGetFrameDimensionsList )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipImageGetFrameCount )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipImageSelectActiveFrame )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipImageRotateFlip )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImagePalette )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetImagePalette )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImagePaletteSize )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPropertyCount )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPropertyIdList )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPropertyItemSize )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPropertyItem )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPropertySize )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetAllPropertyItems )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipRemovePropertyItem )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPropertyItem )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipImageForceValidation )
	// Bitmap APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateBitmapFromStream )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateBitmapFromFile )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateBitmapFromStreamICM )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateBitmapFromFileICM )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateBitmapFromScan0 )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateBitmapFromGraphics )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateBitmapFromDirectDrawSurface )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateBitmapFromGdiDib )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateBitmapFromHBITMAP )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateHBITMAPFromBitmap )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateBitmapFromHICON )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateHICONFromBitmap )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateBitmapFromResource )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCloneBitmapArea )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCloneBitmapAreaI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipBitmapLockBits )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipBitmapUnlockBits )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipBitmapGetPixel )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipBitmapSetPixel )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipBitmapSetResolution )
	// HatchBrush APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateHatchBrush )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetHatchStyle )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetHatchForegroundColor )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetHatchBackgroundColor )
	// TextureBrush APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateTexture )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateTexture2 )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateTextureIA )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateTexture2I )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateTextureIAI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetTextureTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetTextureTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipResetTextureTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipMultiplyTextureTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipTranslateTextureTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipScaleTextureTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipRotateTextureTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetTextureWrapMode )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetTextureWrapMode )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetTextureImage )
	// Brush APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCloneBrush )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDeleteBrush )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetBrushType )
	// SolidBrush APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateSolidFill )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetSolidFillColor )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetSolidFillColor )
	// Pen APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreatePen1 )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreatePen2 )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipClonePen )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDeletePen )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenWidth )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenWidth )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenUnit )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenUnit )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenLineCap197819 )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenStartCap )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenEndCap )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenDashCap197819 )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenStartCap )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenEndCap )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenDashCap197819 )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenLineJoin )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenLineJoin )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenCustomStartCap )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenCustomStartCap )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenCustomEndCap )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenCustomEndCap )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenMiterLimit )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenMiterLimit )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenMode )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenMode )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipResetPenTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipMultiplyPenTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipTranslatePenTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipScalePenTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipRotatePenTransform )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenColor )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenColor )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenBrushFill )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenBrushFill )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenFillType )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenDashStyle )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenDashStyle )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenDashOffset )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenDashOffset )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenDashCount )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenDashArray )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenDashArray )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenCompoundCount )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetPenCompoundArray )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetPenCompoundArray )
	// DrawLine APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawLine )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawLineI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawLines )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawLinesI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawArc )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawArcI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawBezier )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawBezierI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawBeziers )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawBeziersI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawRectangle )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawRectangleI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawRectangles )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawRectanglesI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawEllipse )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawEllipseI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawPie )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawPieI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawPolygon )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawPolygonI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawPath )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawCurve )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawCurveI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawCurve2 )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawCurve2I )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawCurve3 )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawCurve3I )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawClosedCurve )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawClosedCurveI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawClosedCurve2 )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawClosedCurve2I )
	// Fill APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGraphicsClear )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillRectangle )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillRectangleI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillRectangles )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillRectanglesI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillPolygon )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillPolygonI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillPolygon2 )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillPolygon2I )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillEllipse )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillEllipseI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillPie )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillPieI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillPath )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillClosedCurve )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillClosedCurveI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillClosedCurve2 )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillClosedCurve2I )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipFillRegion )
	// DrawImage APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawImage )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawImageI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawImageRect )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawImageRectI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawImagePoints )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawImagePointsI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawImagePointRect )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawImagePointRectI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawImageRectRect )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawImageRectRectI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawImagePointsRect )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawImagePointsRectI )
	// Clip APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetClipGraphics )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetClipRect )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetClipRectI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetClipPath )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetClipRegion )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetClipHrgn )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipResetClip )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipTranslateClip )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipTranslateClipI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetClip )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetClipBounds )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetClipBoundsI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipIsClipEmpty )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetVisibleClipBounds )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetVisibleClipBoundsI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipIsVisibleClipEmpty )
	// Image Decoder/Encoder APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageDecodersSize )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageDecoders )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageEncodersSize )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetImageEncoders )
	// FontFamily APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateFontFamilyFromName )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDeleteFontFamily )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCloneFontFamily )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetGenericFontFamilySansSerif )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetGenericFontFamilySerif )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetGenericFontFamilyMonospace )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetFamilyName )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipIsStyleAvailable )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetEmHeight )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetCellAscent )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetCellDescent )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetLineSpacing )
	// Font APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateFontFromDC )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateFontFromLogfontA )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateFontFromLogfontW )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateFont )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCloneFont )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDeleteFont )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetFamily )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetFontStyle )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetFontSize )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetFontUnit )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetFontHeight )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetFontHeightGivenDPI )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetLogFontA )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetLogFontW )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipNewInstalledFontCollection )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipNewPrivateFontCollection )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDeletePrivateFontCollection )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetFontCollectionFamilyCount )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetFontCollectionFamilyList )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipPrivateAddFontFile )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipPrivateAddMemoryFont )
	// Text APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawString )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipMeasureString )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipMeasureCharacterRanges )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawDriverString )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipMeasureDriverString )
	// String format APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateStringFormat )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipStringFormatGetGenericDefault )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipStringFormatGetGenericTypographic )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDeleteStringFormat )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCloneStringFormat )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetStringFormatFlags )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetStringFormatFlags )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetStringFormatAlign )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetStringFormatAlign )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetStringFormatLineAlign )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetStringFormatLineAlign )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetStringFormatTrimming )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetStringFormatTrimming )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetStringFormatHotkeyPrefix )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetStringFormatHotkeyPrefix )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetStringFormatTabStops )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetStringFormatTabStops )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetStringFormatTabStopCount )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetStringFormatDigitSubstitution )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetStringFormatDigitSubstitution )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipGetStringFormatMeasurableCharacterRangeCount )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetStringFormatMeasurableCharacterRanges )
	// Cached Bitmap APIs
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipCreateCachedBitmap )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDeleteCachedBitmap )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipDrawCachedBitmap )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipEmfToWmfBits )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetImageAttributesCachedBackground )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdipTestControl )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdiplusNotificationHook )
	GET_FUNC_PTR( GDI, gdiplus_dll, GdiplusNotificationUnhook )

	// Load the external SDK functions ( maybe not available in the low version )
	{
		// ImageAttributes APIs
		TRY_GET_FUNC_PTR( GDI, gdiplus_dll, GdipSetImageAttributesICMMode )
		// FontFamily APIs
		TRY_GET_FUNC_PTR( GDI, gdiplus_dll, GdipFontCollectionEnumerable )
		TRY_GET_FUNC_PTR( GDI, gdiplus_dll, GdipFontCollectionEnumerate )
	}

	return _true;
}

_ubool GDIDrv::GetImageEncoderClsid( _FILE_FORMAT type, CLSID& clsid )
{
	// Get the image encoder name
	WStringPtr name;
	switch ( type )
	{
		case _FF_BMP: name = L"image/bmp"; break;
		case _FF_JPG: name = L"image/jpeg"; break;
		case _FF_PNG: name = L"image/png"; break;
		default:
			return _false;
	}

	// Get the image encoder size
	UINT num = 0, size = 0;
	if ( GDI::GdipGetImageEncodersSize( &num, &size ) != Gdiplus::Ok )
		return _false;

	if ( size <= 0 )
		return _false;

	// Get the image encoders
	MemArrayPtr< Gdiplus::ImageCodecInfo > image_codec_info( num );
	if ( GDI::GdipGetImageEncoders( num, size, image_codec_info ) == Gdiplus::Ok )
		return _false;

	// Try to match the image encoder
	for ( _dword i = 0; i < num; i ++ )
	{
		if ( name == image_codec_info[i].MimeType )
		{
			clsid = image_codec_info[i].Clsid;
			return _true;
		}
	}

	return _false;
}

_ubool GDIDrv::Initialize( )
{
	// Load GDI+ library
	if ( LoadGDIPlusLibrary( ) == _false )
		return _false;

	// Initialize GDIPlus token
	Gdiplus::GdiplusStartupInput gdistartup;
	if ( GDI::GdiplusStartup( &mGDIToken, &gdistartup, _null ) != Gdiplus::Ok )
		return _false;

	gPixelFormats[ _PF_UNKNOWN					].mPlatformFormat	= PixelFormatUndefined;
	gPixelFormats[ _PF_R8G8B8					].mPlatformFormat	= PixelFormat24bppRGB;
	gPixelFormats[ _PF_A8R8G8B8					].mPlatformFormat	= PixelFormat32bppARGB;
	gPixelFormats[ _PF_G8						].mPlatformFormat	= PixelFormatUndefined;
	gPixelFormats[ _PF_G16						].mPlatformFormat	= PixelFormatUndefined;
	gPixelFormats[ _PF_DXT1						].mPlatformFormat	= PixelFormatUndefined;
	gPixelFormats[ _PF_DXT3						].mPlatformFormat	= PixelFormatUndefined;
	gPixelFormats[ _PF_DXT5						].mPlatformFormat	= PixelFormatUndefined;
	gPixelFormats[ _PF_UYVY						].mPlatformFormat	= PixelFormatUndefined;
	gPixelFormats[ _PF_DEPTH_STENCIL			].mPlatformFormat	= PixelFormatUndefined;
	gPixelFormats[ _PF_SHADOW_DEPTH				].mPlatformFormat	= PixelFormatUndefined;
	gPixelFormats[ _PF_FILTERED_SHADOW_DEPTH	].mPlatformFormat	= PixelFormatUndefined;
	gPixelFormats[ _PF_R32F						].mPlatformFormat	= PixelFormatUndefined;
	gPixelFormats[ _PF_D24						].mPlatformFormat	= PixelFormatUndefined;

	gPixelFormats[ _PF_FLOAT_RGB				].mPlatformFormat	= PixelFormatUndefined;
	gPixelFormats[ _PF_FLOAT_RGBA				].mPlatformFormat	= PixelFormatUndefined;

	gPixelFormats[ _PF_BC5						].mPlatformFormat	= PixelFormatUndefined;
	gPixelFormats[ _PF_A1						].mPlatformFormat	= PixelFormatUndefined;

	return _true;
}

_void GDIDrv::Finalize( )
{
}

_ubool GDIDrv::ResetResources( IApplication* application )
{
	return _true;
}

_void GDIDrv::UnloadResources( )
{
}

IResourceManagerRHI* GDIDrv::GetResourceManager( )
{
	static NullResourceManagerRHI sResourceManagerRHI;
	return &sResourceManagerRHI;
}

RenderStatsRHI& GDIDrv::GetRenderStats( )
{
	static RenderStatsRHI sRenderStatsRHI; 
	return sRenderStatsRHI;
}

const RenderStatsRHI& GDIDrv::GetRenderStats( ) const
{
	static RenderStatsRHI sRenderStatsRHI; 
	return sRenderStatsRHI;
}

_void GDIDrv::ClearRenderStats( )
{

}

IAllocator* GDIDrv::GetAllocator( )
{
	return _null;
}

_void GDIDrv::ClearCaches( )
{

}

_dword GDIDrv::GetRenderContextsNumber( )
{
	return 1;
}

_ubool GDIDrv::HandleEvent( EventBase& event )
{
	return _false;
}

_ubool GDIDrv::IsBlockEvent( _dword event_id, _ubool& is_async )
{
	return _false;
}

_ubool GDIDrv::IsSupportVAO( )
{
	return _false;
}

_ubool GDIDrv::IsSupportInstancedRendering( )
{
	return _false;
}

PointU GDIDrv::GetOVRFovTextureSize( _dword index )
{
	return PointU::cZeroPoint;
}

_void GDIDrv::SetOVRRenderTargetTexID( _dword index, _dword tex_id, const PointU& tex_size )
{
}

_void GDIDrv::SynOVRDeviceRegion( )
{
}

const OVREyeRHI& GDIDrv::GetOVREyeInfo( _dword index )
{
	static OVREyeRHI sGraphicOVREyeInfo; 
	return sGraphicOVREyeInfo;
}

SamplerStateRHIPassRef GDIDrv::CreateSamplerState( const SamplerStateInitializerRHI& initializer )
{
	return _null;
}

RasterizerStateRHIPassRef GDIDrv::CreateRasterizerState( const RasterizerStateInitializerRHI& initializer )
{
	return _null;
}

DepthStateRHIPassRef GDIDrv::CreateDepthState( const DepthStateInitializerRHI& initializer )
{
	return _null;
}

StencilStateRHIPassRef GDIDrv::CreateStencilState( const StencilStateInitializerRHI& initializer )
{
	return _null;
}

BlendStateRHIPassRef GDIDrv::CreateBlendState( const BlendStateInitializerRHI& initializer )
{
	return _null;
}

SamplerStateInitializerRHI GDIDrv::GetSamplerState( const SamplerStateRHI* state ) const
{
	return SamplerStateInitializerRHI( _SF_NEAREST );
}

RasterizerStateInitializerRHI GDIDrv::GetRasterizerState( const RasterizerStateRHI* state ) const
{
	return RasterizerStateInitializerRHI( _false, _false, _false, _false, _RFM_POINT, _RCM_NONE );
}

DepthStateInitializerRHI GDIDrv::GetDepthState( const DepthStateRHI* state ) const
{
	return DepthStateInitializerRHI( _false, _CF_LESS );
}

StencilStateInitializerRHI GDIDrv::GetStencilState( const StencilStateRHI* state ) const
{
	return StencilStateInitializerRHI( );
}

BlendStateInitializerRHI GDIDrv::GetBlendState( const BlendStateRHI* state ) const
{
	return BlendStateInitializerRHI( );
}

const ShaderCompileConfigInfo& GDIDrv::GetShaderCompileConfigInfo( )
{
	static ShaderCompileConfigInfo sShaderCompileConfigInfo;
	return sShaderCompileConfigInfo;
};

PixelShaderRHIPassRef GDIDrv::CreatePixelShader( AStringPtr code )
{
	return _null;
}

VertexShaderRHIPassRef GDIDrv::CreateVertexShader( AStringPtr code )
{
	return _null;
}

BoundShaderRHIPassRef GDIDrv::CreateBoundShader( VertexShaderRHI* vertexshader, PixelShaderRHI* pixelshader )
{
	return _null;
}

PixelShaderRHI* GDIDrv::GetPixelShader( BoundShaderRHI* shader ) 
{
	return _null;
}

VertexShaderRHI* GDIDrv::GetVertexShader( BoundShaderRHI* shader ) 
{
	return _null;
}

_ubool GDIDrv::GetPixelShaderCode( PixelShaderRHI* ps, AString& code )
{
	return _false;
}

_ubool GDIDrv::GetVertexShaderCode( VertexShaderRHI* vs, AString& code )
{
	return _false;
}

_dword GDIDrv::GetShaderResourceID( const BoundShaderRHI* shader ) const
{
	return 0;
}

_dword GDIDrv::ActiveUniformBuffer( BoundShaderRHI* shader, _UNIFORM_BUFFER_DATA_TYPE type, AStringPtr name, _dword size )
{
	return -1;
}

_ubool GDIDrv::UpdateUniformBuffer( BoundShaderRHI* shader, _dword location, const _void* buffer, _dword size )
{
	return _false;
}

_ubool GDIDrv::SetUniformPropertyValue( BoundShaderRHI* shader, AStringPtr name, _long value )
{
	return _false;
}

VertexDeclarationRHIPassRef GDIDrv::CreateVertexDeclaration( const VertexElementRHIArray& elements )
{
	return _null;
}

_dword GDIDrv::GetVertexDeclarationVertexType( VertexDeclarationRHI* declaration )
{
	return 0;
}

_dword GDIDrv::GetVertexDeclarationStride( VertexDeclarationRHI* declaration )
{
	return 0;
}

const VertexElementRHIArray& GDIDrv::GetVertexDeclarationDefine( VertexDeclarationRHI* declaration )
{
	static VertexElementRHIArray sNull;
	return sNull;
}

IndexBufferRHIPassRef GDIDrv::CreateIndexBuffer( _dword stride, _dword size, const _byte* buffer, _dword usage_flags, _RESOURCE_DRAW_TYPE draw_type )
{
	return _null;
}

_void* GDIDrv::LockIndexBuffer( IndexBufferRHI* indexbuffer, _dword offset, _dword size, _RESOURCE_LOCK_FLAG flag )
{
	return _null;
}

_void GDIDrv::UnlockIndexBuffer( IndexBufferRHI* indexbuffer )
{
}

_dword GDIDrv::GetIndexBufferStride( IndexBufferRHI* indexbuffer )
{
	return 0;
}

_dword GDIDrv::GetIndexBufferSize( IndexBufferRHI* indexbuffer )
{
	return 0;
}

_ubool GDIDrv::UpdateIndexBuffer( IndexBufferRHI* index_buffer, _dword offset, _dword size, const _byte* buffer, _ubool discard )
{
	return _false;
}

_ubool GDIDrv::ResizeIndexBuffer( IndexBufferRHI* index_buffer, _dword size )
{
	return _false;
}

_dword GDIDrv::GetIndexBufferResID( IndexBufferRHI* index_buffer )
{
	return 0;
}

VertexBufferRHIPassRef GDIDrv::CreateVertexBuffer( _dword stride, _dword size, const _byte* buffer, _dword usage_flags, _RESOURCE_DRAW_TYPE draw_type )
{
	return _null;
}

_void* GDIDrv::LockVertexBuffer( VertexBufferRHI* vertexbuffer, _dword offset, _dword size, _RESOURCE_LOCK_FLAG flag )
{
	return _null;
}

_void GDIDrv::UnlockVertexBuffer( VertexBufferRHI* vertexbuffer )
{
}

_dword GDIDrv::GetVertexBufferStride( VertexBufferRHI* vertexbuffer )
{
	return 0;
}

_dword GDIDrv::GetVertexBufferSize( VertexBufferRHI* vertexbuffer )
{
	return 0;
}

_ubool GDIDrv::UpdateVertexBuffer( VertexBufferRHI* vertexbuffer, _dword offset, _dword size, const _byte* buffer, _ubool discard )
{
	return _false;
}

_ubool GDIDrv::ResizeVertexBuffer( VertexBufferRHI* vertexbuffer, _dword size )
{
	return _false;
}

_dword GDIDrv::GetVertexBufferResID( VertexBufferRHI* vertexbuffer )
{
	return 0;
}