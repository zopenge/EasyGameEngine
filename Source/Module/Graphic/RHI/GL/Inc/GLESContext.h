//! @file     GLESContext.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
//----------------------------------------------------------------------------
// GLESContext
//----------------------------------------------------------------------------

//!	The EGL/PowerVR context Info
class GLESContext
{
private:
	INTERNAL_HANDLER_DECL( );

public:
	GLESContext( );
	~GLESContext( );

public:
	//!	Create GL context.
	_ubool Create( _handle app_handle );

	//!	Make the current GL context.
	_ubool MakeCurrentGLContext( );

	//!	Flush GL buffers.
	_void FlushGLBuffers( );
};

}