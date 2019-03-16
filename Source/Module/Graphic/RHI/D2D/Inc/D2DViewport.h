//! @file     D2DViewport.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class D2DDrv;

//----------------------------------------------------------------------------
// D2DViewport
//----------------------------------------------------------------------------

class D2DViewport : public ViewportRHI
{
private:
	typedef RefPtr< D2DSurface > SurfaceRef;

private:
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
	D2DViewport( );
	virtual ~D2DViewport( );

public:
	//!	Initialize.
	_ubool Initialize( _handle app_handle, const PointU& size, const PointU& device_size );

	//!	Resize.
	_ubool Resize( const PointU& size );

	//!	Get the back surface.
	D2DSurface* GetBackSurface( );
};

}