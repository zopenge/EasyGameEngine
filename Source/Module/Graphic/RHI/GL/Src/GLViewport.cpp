//! @file     GLViewport.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

#if (_DISABLE_GL_API_CALL_COUNTER == 0)
_dword EGE::gGLAPICallCounter = 0;
_void EGE::IncGLAPICallCounter( )
{
	EGE::gGLAPICallCounter ++;
}
#endif

//----------------------------------------------------------------------------
// GLDrv-Viewport Implementation
//----------------------------------------------------------------------------

ViewportRHIPassRef GLDrv::CreateViewport( _handle app_handle, const PointU& size )
{
	// Create viewport
	GLViewport* viewport = new GLViewport( );

	// Update the main viewport
	if ( mMainViewport == _null )
		mMainViewport = viewport;

	// Initialize viewport
	if ( viewport->Initialize( app_handle, size ) == _false )
	{
		if ( mMainViewport == viewport )
			mMainViewport = _null;

		delete viewport; 
		return _null; 
	}

	return viewport;
}

_ubool GLDrv::ResizeViewport( ViewportRHI* viewport, const PointU& size )
{
	DYNAMIC_CAST_GLRESOURCE( Viewport, viewport );

	return gl_viewport->Resize( size );
}

const PointU& GLDrv::GetViewportSize( ViewportRHI* viewport ) const
{
	DYNAMIC_CAST_GLRESOURCE( Viewport, viewport );

	return gl_viewport->GetSize( );
}

_void GLDrv::BindViewport( ViewportRHI* viewport )
{
	DYNAMIC_CAST_GLRESOURCE( Viewport, viewport );

	// Make the current GL context
	MakeCurrentGLContext( gl_viewport->GetGLContext( )->GetContext( ) );
}

_void GLDrv::Present( ViewportRHI* viewport )
{
	DYNAMIC_CAST_GLRESOURCE( Viewport, viewport );

	// Present
	gl_viewport->Present( );

	// Reset the GL API call counter
#if (_DISABLE_GL_API_CALL_COUNTER == 0)
	gGLAPICallCounter = 0;
#endif

	// Clear caches if we have multiple viewports
	if ( GetGLContextNumber( ) > 1 )
		ClearCaches( );
}

//----------------------------------------------------------------------------
// GLViewport Implementation
//----------------------------------------------------------------------------

GLViewport::GLViewport( )
{
	mGLContext	= new GLContext( );

	mSize		= PointU::cZeroPoint;
}

GLViewport::~GLViewport( )
{
	// Release the OpenGL context
	mGLContext->Finalize( );
	EGE_DELETE( mGLContext );

	// Update the unique shared GL context
	if ( gSharedViewportRHI == this )
		gSharedViewportRHI = _null;
}

_ubool GLViewport::Initialize( _handle app_handle, const PointU& size )
{
	// Create GL context
	if ( mGLContext->Initialize( app_handle ) == _false )
	{
		WLOG_ERROR_1( L"Initialize GL context with (handle:0x%.16llx) viewport failed", (_qword)app_handle );
		return _false;
	}

	// Share GL context
	if ( gSharedViewportRHI != _null )
	{
		// Get the GL context which to share
		const GLContext* gl_context = static_cast< GLViewport* >( gSharedViewportRHI )->GetGLContext( );
		EGE_ASSERT( gl_context );

		// Share GL context
		if ( ShareGLContext( gl_context->GetContext( ), mGLContext->GetContext( ) ) == _false )
		{
			WLOG_ERROR_1( L"Create shared GL context with (handle:0x%.16llx) viewport failed", (_qword)app_handle );
			return _false;
		}
	}

	// Update the unique shared GL context
	if ( gSharedViewportRHI == _null )
		gSharedViewportRHI = this;

	// Resize the back buffer
	if ( Resize( size ) == _false )
		return _false;
	
	return _true;
}

_dword GLViewport::GetWidth( ) const
{
	return mSize.x;
}

_dword GLViewport::GetHeight( ) const
{
	return mSize.y;
}

_ubool GLViewport::Resize( const PointU& size )
{
	mSize = size;

	return _true;
}

_void GLViewport::Present( )
{
	// Present the back buffer to the viewport window
	GetGLContext( )->Present( );
}