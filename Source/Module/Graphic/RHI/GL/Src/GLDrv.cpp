//! @file     GLDrv.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLDrv Implementation
//----------------------------------------------------------------------------

GLDrv::GLDrv( )
{
	mResourceManager	= _null;

	mMainViewport		= _null;
}

GLDrv::~GLDrv( )
{
	Finalize( );
}

_ubool GLDrv::InitResourceManager( )
{
#if _ENABLE_GL_DEVICE_MANAGER == 1
	mResourceManager = new GLResourceManager( );
#else
	mResourceManager = new NullResourceManagerRHI( );
#endif
	if ( mResourceManager->Initialize( ) == _false )
	{
		WLOG_ERROR( L"Initialize GL resource manager failed" );
		return _false;
	}

	gResourceManagerRHI = mResourceManager;

	return _true;
}

_ubool GLDrv::Initialize( )
{
	// Initialize EGL API
	if ( InitializeEGLAPI( ) == _false )
		return _false;

	// Initialize GL resource manager
	if ( InitResourceManager( ) == _false )
		return _false;

	return _true;
}

_void GLDrv::Finalize( )
{
	gGLCachedState.Clear( );

	mMainViewport = _null;

	GLFramebufferCache::GetInstance( ).Clear( );
	GLSLOptimizer::GetInstance( ).Finalize( );

	EGE_RELEASE( mResourceManager );
	gResourceManagerRHI = &NullGraphic::GetInstance( ).GetDeviceManagerRHI( );

	// Finalize EGL API
	FinalizeEGLAPI( );
}

_ubool GLDrv::ResetResources( )
{
	return mResourceManager->Reset( );
}

_void GLDrv::UnloadResources( )
{
	mResourceManager->Unload( );
}

IResourceManagerRHI* GLDrv::GetResourceManager( )
{
	return mResourceManager;
}

RenderStatsRHI& GLDrv::GetRenderStats( )
{
	static RenderStatsRHI sRenderStatsRHI; 
	return sRenderStatsRHI;
}

const RenderStatsRHI& GLDrv::GetRenderStats( ) const
{
	static RenderStatsRHI sRenderStatsRHI; 
	return sRenderStatsRHI;
}

_void GLDrv::ClearRenderStats( )
{

}

_void GLDrv::ClearCaches( )
{
	// Clear GL cached data
	gGLCachedState.Clear( );

	// http://dheartf.blog.163.com/blog/static/3850546520127231034460/

	// Unbind GLSL program
	GLCachedBindProgram( 0 );
}

_dword GLDrv::GetRenderContextsNumber( )
{
	return GetGLContextNumber( );
}

_void GLDrv::SetVRRenderTargetTexID( _dword index, _dword tex_id, const PointU& tex_size )
{
	mMainViewport->GetGLContext( )->SetVRRenderTargetTexID( index, tex_id, tex_size );
}

PointU GLDrv::GetVRTextureSize( _dword index ) const
{
	return mMainViewport->GetGLContext( )->GetVRTextureSize( index );
}

VREyeRHI GLDrv::GetVREyeInfo( _dword index ) const
{
	return mMainViewport->GetGLContext( )->GetVREyeInfo( index );
}
