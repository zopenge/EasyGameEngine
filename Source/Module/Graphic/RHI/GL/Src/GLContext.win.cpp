//! @file     GLContext.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//!	The context handle
struct GLContext::Handle
{
	//!	The GL context
	_handle	mGLContext;

	Handle( )
	{
		mGLContext = _null;
	}
	~Handle( )
	{
		ReleaseGLContext( mGLContext );
	}
};

//----------------------------------------------------------------------------
// GLContext Implementation
//----------------------------------------------------------------------------

GLContext::GLContext( )
{
	mHandle = _null;
}

GLContext::~GLContext( )
{
	Finalize( );
}

_ubool GLContext::Initialize( _handle app_handle )
{
	mHandle = new Handle( );

	// Create GL context
	mHandle->mGLContext = CreateGLContext( app_handle );
	if ( mHandle->mGLContext == _null )
		return _false;
	
	return _true;
}

_void GLContext::Finalize( )
{
	EGE_DELETE( mHandle );
}

_handle GLContext::GetContext( ) const
{
	return mHandle->mGLContext;
}

_void GLContext::Bind( )
{
	GLCachedBindFBO( 0 );
}

_void GLContext::Present( )
{
	FlushGLBuffers( mHandle->mGLContext );
}

_void GLContext::SetVRRenderTargetTexID( _dword index, _dword tex_id, const PointU& tex_size )
{
	::SetVRRenderTargetTexID( mHandle->mGLContext, index, tex_id, tex_size );
}

PointU GLContext::GetVRTextureSize( _dword index ) const
{
	return ::GetVRTextureSize( mHandle->mGLContext, index );
}

VREyeRHI GLContext::GetVREyeInfo( _dword index ) const
{
	return ::GetVREyeInfo( mHandle->mGLContext, index );
}