//! @file     GraphicModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicModule Implementation
//----------------------------------------------------------------------------

GraphicModule::GraphicModule( ) : BaseClass( L"Graphic", Version( GRAPHIC_FILEVER ) )
{
	mGraphicViewport		= _null;
	mGraphicResourceManager	= _null;
	mGraphicVRDevice		= _null;

	mTexture2DSetCleanupTimer.Init( 10 SEC );
}

GraphicModule::~GraphicModule( )
{
	Finalize( );

	GetModuleManager( )->UnregisterModule( this );
}

_ubool GraphicModule::CreateDynamicRHI( )
{
	// Create dynamic RHI driver
	IDynamicRHIPassRef driver = new GLDrv( );

	// Use the RHI with render statistics
	IDynamicRHIPassRef stats_driver = new RHIStatsDrv( driver.GetPtr( ) );

	// Set the global dynamic RHI
	mDynamicRHI = stats_driver;
	gDynamicRHI = mDynamicRHI.GetPtr( );

	// Initialize dynamic RHI driver
	if ( gDynamicRHI->Initialize( ) == _false )
	{
		WLOG_ERROR( L"Initialize dynamic RHI failed" );
		return _false;
	}

	return _true;
}

_ubool GraphicModule::CreateResourceManager( _handle app_handle )
{
	// Create resource manager
	mGraphicResourceManager	= new GraphicResourceManager( );
	if ( mGraphicResourceManager->Initialize( app_handle ) == _false )
		return _false;

	gGraphicResourceManager = mGraphicResourceManager;

	return _true;
}

_ubool GraphicModule::CreateGraphicViewport( _handle app_handle, const PointU& size )
{
	WLOG_TRACE( L"Create graphic viewport ..." );

	// Create RHI viewport
	ViewportRHIRef viewport_resource = gDynamicRHI->CreateViewport( app_handle, size );
	if ( viewport_resource.IsNull( ) )
		return _false;

	// Create graphic viewport with back surface
	mGraphicViewport = new GraphicViewport( viewport_resource );
	if ( mGraphicViewport->Initialize( ) == _false )
		{ EGE_RELEASE( mGraphicViewport ); return _null; }

	gGraphicViewport = mGraphicViewport;

	WLOG_TRACE( L"Create graphic viewport OK" );

	return _true;
}

_ubool GraphicModule::CreateVRDevice( )
{
#if (_ENABLE_VR_DEVICE == 1)
	mGraphicVRDevice = new GraphicVRDevice( );
	if ( mGraphicVRDevice->Initialize( ) == _false )
		{ EGE_RELEASE( mGraphicVRDevice ); return _false; }

	gGraphicVRDevice = mGraphicVRDevice;
#endif

	return _true;
}

_ubool GraphicModule::CreateTexture2DSet( const PointU& size )
{
	mTexture2DSet = GetGraphicResourceManager( )->CreateTexture2DSet( size );
	if ( mTexture2DSet.IsNull( ) )
	{
		WLOG_ERROR_2( L"Create texture 2D set (%dx%d) failed", size.x, size.y );
		return _false;
	}

	return _true;
}

_ubool GraphicModule::Initialize( _handle app_handle, const PointU& size, _dword multisample )
{
	WLOG_TRACE( L"Create graphic module ..." );

	// Set the global info
	gMultisampleNumber = multisample;

	// Check the application handle
	if ( app_handle == _null )
	{
		WLOG_ERROR( L"You must provide the application handle to graphic module" );
		return _false;
	}

	// Create resource manager
	if ( CreateResourceManager( app_handle ) == _false )
	{
		WLOG_ERROR( L"Create graphic resource manager failed" );
		return _false;
	}

	// Create RHI driver
	if ( CreateDynamicRHI( ) == _false )
    {
        WLOG_ERROR( L"Create dynamic RHI failed" );
		return _false;
    }

	// Create graphic viewport
	if ( CreateGraphicViewport( app_handle, size ) == _false )
	{
		WLOG_ERROR( L"Create graphic viewport failed" );
		return _false;
	}

	// Create VR device
	if ( CreateVRDevice( ) == _false )
	{
		WLOG_ERROR( L"Create graphic OVR viewports failed" );
		return _false;
	}

	// Create texture 2D set
	if ( CreateTexture2DSet( PointU( 1024, 1024 ) ) == _false )
	{
		WLOG_ERROR( L"Create graphic texture 2D set failed" );
		return _false;
	}

	WLOG_TRACE( L"Create graphic module DONE" );

	return _true;
}

_void GraphicModule::Finalize( )
{
	WLOG_TRACE( L"Release graphic module ..." );

	// Finalize all resources
	mDynamicRHI->Finalize( );

	// Finalize managers
	mGraphicResourceManager->Finalize( );

	// Release viewport
	EGE_RELEASE( mGraphicVRDevice );
	EGE_RELEASE( mGraphicViewport );

	// Clear render device
	mDynamicRHI.Clear( );

	// Release managers
	EGE_RELEASE( mGraphicResourceManager );

	WLOG_TRACE( L"Release graphic module DONE" );

	// Clear global modules
	gDynamicRHI				= _null;
	gSharedViewportRHI		= _null;
	gGraphicViewport		= _null;
	gGraphicResourceManager	= _null;
	gGraphicModule			= _null;

	// Clear other modules
	gResourceManagerRHI		= &NullGraphic::GetInstance( ).GetDeviceManagerRHI( );
	gGraphicVRDevice		= &NullGraphic::GetInstance( ).GetGraphicVRDevice( );
}

_void GraphicModule::Tick( _dword limited_elapse, _dword elapse )
{
	// Cleanup texture 2D set
	if ( mTexture2DSetCleanupTimer.IsOverdue( elapse, _false ) )
		mTexture2DSet->Cleanup( );

	// Update the render hardware info
	gDynamicRHI->Tick( limited_elapse, elapse );
}

_void GraphicModule::FrameTick( _dword frame )
{
	// Clear render stats
	mDynamicRHI->ClearRenderStats( );
}

_ubool GraphicModule::ResetResources( )
{
	if ( GetDynamicRHI( )->ResetResources( ) == _false )
		return _false;

	return _true;
}

_void GraphicModule::UnloadResources( )
{
	mGraphicViewport->ClearCaches( );
	mGraphicResourceManager->ClearCaches( );

	GetDynamicRHI( )->UnloadResources( );
}

_void GraphicModule::HandleEvent( EventBase& event )
{
	gGraphicVRDevice->HandleEvent( event );

	switch ( event.mEventID )
	{
		case _EVENT_CLIENT_SIZE_CHANGED:
		{
			const EventClientSizeChanged& msg = (const EventClientSizeChanged&) event;

			mGraphicViewport->SetClientSize( msg.mClientSize );
		}
		break;
		
		case _EVENT_LOW_MEMORY:
		{
			mGraphicResourceManager->ClearCaches( );
		}
		break;

		default:
			break;
	}
}

IGraphicTexture2DSet* GraphicModule::GetTexture2DSet( )
{
	return mTexture2DSet;
}

IGraphicSurface* GraphicModule::GetRenderTarget( )
{
	return mCurRenderTarget;
}

IGraphicSurface* GraphicModule::GetDepthStencil( )
{
	return mCurDepthStencil;
}

_void GraphicModule::SetRenderTarget( IGraphicSurface* rendertarget, IGraphicSurface* depthstencil )
{
	mCurRenderTarget = rendertarget;
	mCurDepthStencil = depthstencil;

	// Get the RHI resources
	SurfaceRHI* rendertarget_source = _null;
	SurfaceRHI* depthstencil_source = _null;
	if ( rendertarget != _null )
		rendertarget_source = rendertarget->GetResource( );
	if ( depthstencil != _null )
		depthstencil_source = depthstencil->GetResource( );

	// Set the render target and depth stencil
	gDynamicRHI->SetRenderTarget( rendertarget_source, depthstencil_source );
}