//! @file     GLESContext.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLESContext Internal Handler Implementation
//----------------------------------------------------------------------------

INTERNAL_HANDLER_IMPL_BEGIN( GLESContext )
	_handle	mAppHandle;

	INTERNAL_HANDLER_CONSTRUCTOR( )
	{
		mAppHandle = _null;
	}
INTERNAL_HANDLER_IMPL_END( )

//----------------------------------------------------------------------------
// GLESContext Implementation
//----------------------------------------------------------------------------

GLESContext::GLESContext( )
{
	INTERNAL_HANDLER_CREATE( );
}

GLESContext::~GLESContext( )
{
	INTERNAL_HANDLER_RELEASE( );
}

_ubool GLESContext::Create( _handle app_handle )
{
	if ( app_handle == _null )
		return _false;

	INTERNAL_HANDLER( )->mAppHandle = app_handle;

	return _true;
}

_ubool GLESContext::MakeCurrentGLContext( )
{
	return _true;
}

_void GLESContext::FlushGLBuffers( )
{
}