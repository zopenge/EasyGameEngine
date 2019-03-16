//! @file     D3D11Viewport.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class D3D11Drv;

//----------------------------------------------------------------------------
// D3D11Viewport
//----------------------------------------------------------------------------

class D3D11Viewport : public ViewportRHI
{
private:
	//! The window handle associated with the D3D device
	HWND						mDeviceWindow;

	//!	The D3D driver
	D3D11Drv*					mD3DDriver;
	//!	The DXGI-SwapChain interface
	RefPtr< IDXGISwapChain >	mDXGISwapChain;

	//! The size of the viewport
	PointU						mSize;

	//!	The back surface
	D3D11Surface*				mBackBuffer;

private:
	//!	Creates a surface to represent a swap chain's back buffer.
	//!	@param		none.
	//!	@return		The back surface.
	D3D11Surface* CreateSwapChainSurface( );

public:
	D3D11Viewport( D3D11Drv* d3d_driver );
	virtual ~D3D11Viewport( );

public:
	//!	Initialize.
	_ubool Initialize( _handle app_handle, const PointU& size, const PointU& device_size );

	//!	Resize.
	_ubool Resize( const PointU& size );

	//!	Begin/End drawing.
	_ubool BeginDrawing( );
	_void EndDrawing( _ubool present );
};

}