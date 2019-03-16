//! @file     GDIViewport.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class GDIDrv;

//----------------------------------------------------------------------------
// GDIViewport
//----------------------------------------------------------------------------

class GDIViewport : public ViewportRHI
{
private:
	typedef RefPtr< GDISurface > SurfaceRef;

private:
	//!	The GDI driver
	GDIDrv*		mGDIDriver;

	//!	The window handle
	HWND		mWindowHandle;
	//!	The window DC
	HDC			mWindowDC;

	//!	The back surface
	SurfaceRef	mBackSurface;

	//! The size of the viewport
	PointU		mSize;

private:
	//!	Creates a back surface.
	_ubool CreateBackSurface( );

public:
	GDIViewport( );
	virtual ~GDIViewport( );

public:
	//!	Get the size.
	EGE_GET_ACCESSOR_CONST( const PointU&, Size )

public:
	//!	Initialize.
	_ubool Initialize( _handle app_handle, const PointU& size, const PointU& device_size );

	//!	Resize.
	_ubool Resize( const PointU& size );

	//!	Begin drawing.
	_ubool BeginDrawing( );
	//!	End drawing.
	_void EndDrawing( );

	//!	Present.
	_void Present( );

	//!	Get the back surface.
	GDISurface* GetBackSurface( );
};

}