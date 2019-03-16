//! @file     GraphicModule.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicModule
//----------------------------------------------------------------------------

class GraphicModule : public INTERFACE_MODULE_IMPL( IGraphicModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( IGraphicModule ) BaseClass;

private:
	//!	The dynamic RHI
	IDynamicRHIRef			mDynamicRHI;
	//!	The graphic viewport
	GraphicViewport*		mGraphicViewport;
	//!	The graphic resource manager
	GraphicResourceManager*	mGraphicResourceManager;
	//!	The graphic VR device (optional)
	GraphicVRDevice*		mGraphicVRDevice;

	//!	The texture 2D set cleanup time
	Timer					mTexture2DSetCleanupTimer;
	//!	The texture 2D set
	IGraphicTexture2DSetRef	mTexture2DSet;

	//!	The current render target
	IGraphicSurfaceRef		mCurRenderTarget;
	//!	The current depth stencil
	IGraphicSurfaceRef		mCurDepthStencil;

private:
	//!	Create dynamic RHI.
	_ubool CreateDynamicRHI( );
	//!	Create resource manager.
	_ubool CreateResourceManager( _handle app_handle );
	//!	Create graphic Viewport.
	_ubool CreateGraphicViewport( _handle app_handle, const PointU& size );
	//!	Create VR device.
	_ubool CreateVRDevice( );

	//!	Create texture 2D set.
	_ubool CreateTexture2DSet( const PointU& size );

public:
	GraphicModule( );
	virtual ~GraphicModule( );

public:
	//!	Initialize.
	_ubool Initialize( _handle app_handle, const PointU& size, _dword multisample );
	//!	Finalize.
	_void Finalize( );

// IObject Interface
public:
	virtual _void					Tick( _dword limited_elapse, _dword elapse ) override;
	virtual _void					FrameTick( _dword frame ) override;

// IModule Interface
public:
	virtual _ubool					ResetResources( ) override;
	virtual _void					UnloadResources( ) override;

	virtual _void					HandleEvent( EventBase& event ) override;

// IGraphicModule Interface
public:
	virtual IGraphicTexture2DSet*	GetTexture2DSet( ) override;

	virtual IGraphicSurface*		GetRenderTarget( ) override;
	virtual IGraphicSurface*		GetDepthStencil( ) override;
	virtual _void					SetRenderTarget( IGraphicSurface* rendertarget, IGraphicSurface* depthstencil ) override;
};

}