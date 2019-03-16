//! @file     D3D11Viewport.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D3D11Drv-Viewport Implementation
//----------------------------------------------------------------------------

ViewportRHIPassRef D3D11Drv::CreateViewport( _handle app_handle, const PointU& size, const PointU& device_size )
{
	// Create viewport
	D3D11Viewport* viewport = new D3D11Viewport( this );
	if ( viewport->Initialize( app_handle, size, device_size ) == _false )
		{ delete viewport; return _null; }

	return viewport;
}

_ubool D3D11Drv::ResizeViewport( ViewportRHI* viewport, const PointU& size )
{
	DYNAMIC_CAST_D3D11RESOURCE( Viewport, viewport );

	return d3d_viewport->Resize( size );
}

const PointU& D3D11Drv::GetViewportSize( ViewportRHI* viewport ) const
{
	DYNAMIC_CAST_D3D11RESOURCE( Viewport, viewport );

	return PointU::cZeroPoint;
}

_void D3D11Drv::BindViewport( ViewportRHI* viewport )
{
}

_void D3D11Drv::Present( ViewportRHI* viewport, _ubool clear_caches )
{
}

//----------------------------------------------------------------------------
// D3D11Viewport Implementation
//----------------------------------------------------------------------------

D3D11Viewport::D3D11Viewport( D3D11Drv* d3d_driver ) : mD3DDriver( d3d_driver )
{
	mDeviceWindow	= _null;

	mSize			= PointU::cZeroPoint;

	mBackBuffer		= _null;
}

D3D11Viewport::~D3D11Viewport( )
{
	EGE_DELETE( mBackBuffer );
}

D3D11Surface* D3D11Viewport::CreateSwapChainSurface( )
{
	// Grab the back buffer
	RefPtr< ID3D11Texture2D > back_buffer;
	if ( FAILED( mDXGISwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ),(_void**) &back_buffer.GetRawRef( ) ) ) )
		return _null;

	RefPtr<ID3D11RenderTargetView > rendertarget_view;

	// Create the render target view
	D3D11_RENDER_TARGET_VIEW_DESC desc;
	desc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.ViewDimension		= D3D11_RTV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = 0;
	if ( FAILED( mD3DDriver->GetDevice( )->CreateRenderTargetView( back_buffer.GetPtr( ), &desc, &rendertarget_view.GetRawRef( ) ) ) )
		return _null;

	return new D3D11Surface( D3D11Surface::_TYPE_RENDER_TARGET, mSize, rendertarget_view.GetPtr( ), back_buffer.GetPtr( ) );
}

_ubool D3D11Viewport::Initialize( _handle app_handle, const PointU& size, const PointU& device_size )
{
	// Save the window handle
	mDeviceWindow = (HWND) app_handle;
	if ( mDeviceWindow == _null )
		return _false;

	// Create a backbuffer/swapchain for each viewport
	RefPtr< IDXGIDevice > dxgi_device;
	if ( FAILED( mD3DDriver->GetDevice( )->QueryInterface( __uuidof( IDXGIDevice ), (_void**) &dxgi_device.GetRawRef( ) ) ) )
		return _false;

	RefPtr< IDXGIAdapter > dxgi_adapter;
	if ( FAILED( dxgi_device->GetParent( __uuidof( IDXGIAdapter ), (_void**) &dxgi_adapter.GetRawRef( ) ) ) )
		return _false;

	RefPtr< IDXGIFactory > dxgi_factory;
	if ( FAILED( dxgi_adapter->GetParent( __uuidof( IDXGIFactory ), (_void**) &dxgi_factory.GetRawRef( ) ) ) )
		return _false;

	// Create the swapchain.
	DXGI_SWAP_CHAIN_DESC desc				= {0};
	desc.BufferDesc.Width					= size.x;
	desc.BufferDesc.Height					= size.y;
	desc.BufferDesc.RefreshRate.Numerator	= 0;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering		= DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	desc.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
	desc.SampleDesc.Count					= 1;
	desc.SampleDesc.Quality					= 0;
	desc.BufferUsage						= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount						= 1;
	desc.OutputWindow						= mDeviceWindow;
	desc.Windowed							= _true;
	desc.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;
	desc.Flags								= 0;
	if ( FAILED( dxgi_factory->CreateSwapChain( dxgi_device.GetPtr( ), &desc, &mDXGISwapChain.GetRawRef( ) ) ) )
		return _false;

	// Create a RHI surface to represent the viewport's back buffer.
	mBackBuffer = CreateSwapChainSurface( );
	if ( mBackBuffer == _null )
		return _false;

	// Add the viewport into manager array
	mD3DDriver->AddViewport( this );

	return _true;
}

_ubool D3D11Viewport::Resize( const PointU& size )
{
	// The size must be different
	if ( mSize == size )
		return _true;

	// Update the size
	mSize = size;

	// Release our backbuffer reference, as required by DXGI before calling ResizeBuffers
	EGE_DELETE( mBackBuffer );

	// Resize the swap chain
	if ( FAILED( mDXGISwapChain->ResizeBuffers( 1, size.x, size.y, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH ) ) )
		return _false;

	// Create a RHI surface to represent the viewport's back buffer.
	mBackBuffer = CreateSwapChainSurface( );
	if ( mBackBuffer == _null )
		return _false;

	return _true;
}

_ubool D3D11Viewport::BeginDrawing( )
{
	// Set the render target and viewport
	gDynamicRHI->SetRenderTarget( mBackBuffer, _null );
	gDynamicRHI->SetViewport( Viewport( 0.0f, 0.0f, (_float) mSize.x, (_float) mSize.y, 0.0f, 1.0f ) );

	return _true;
}

_void D3D11Viewport::EndDrawing( _ubool present )
{
	if ( present )
	{
		// Present the back buffer to the viewport window
		mDXGISwapChain->Present( 1, 0 );
	}
}
