//! @file     GLDevice.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLDevice Implementation
//----------------------------------------------------------------------------

GLDevice::GLDevice( )
{
}

GLDevice::~GLDevice( )
{
}

_ubool GLDevice::Initialize( )
{
	return _true;
}

_void GLDevice::Finalize( )
{
}

_ubool GLDevice::Reset( )
{
	return _true;
}

_ubool GLDevice::UpdateVBO( GLVertexBuffer* vbo, _dword offset, _dword size, const _byte* data )
{
	return _true;
}

_void GLDevice::RemoveVBO( GLVertexBuffer* vbo )
{

}

_ubool GLDevice::UpdateGLSLProgram( GLSLProgram* glsl_program )
{
	return _true;
}

_void GLDevice::RemoveGLSLProgram( GLSLProgram* glsl_program )
{

}
