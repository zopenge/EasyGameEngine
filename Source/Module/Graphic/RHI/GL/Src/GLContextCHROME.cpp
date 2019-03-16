//! @file     GLContextIOS.cpp
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

_ubool GLContext::Initialize( _handle app_handle, const PointU& device_size )
{
	mHandle = new Handle( );

	// Create GL context
	mHandle->mGLContext = CreateGLContext( app_handle, device_size );
	if ( mHandle->mGLContext == _null )
	{
		WLOG_ERROR_1( L"Create chrome OpenGLES context failed with '0x%.8x' application handle", (_dword) app_handle );
		return _false;
	}

	// Gather OpenGL info
	GLDrv::GatherInfo( );

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
	// Bind the default frame buffer
	GLCachedBindFBO( 0 );
}

_void GLContext::Present( )
{
	FlushGLBuffers( mHandle->mGLContext );
}

_void GLContext::SetOVRRenderTargetTexID( _dword index, _dword tex_id, const PointU& tex_size )
{
}

PointU GLContext::GetOVRFovTextureSize( _dword index )
{
	return PointU::cZeroPoint;
}

_void GLContext::SynOVRDeviceRegion( )
{
}

const OVREyeRHI& GLContext::GetOVREyeInfo( _dword index )
{
	static OVREyeRHI sGraphicOVREyeInfo; 
	return sGraphicOVREyeInfo;
}