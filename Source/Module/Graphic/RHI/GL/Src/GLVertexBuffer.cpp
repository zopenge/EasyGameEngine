//! @file     GLVertexBuffer.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLDrv-VertexBuffer Implementation
//----------------------------------------------------------------------------

VertexBufferRHIPassRef GLDrv::CreateVertexBuffer( _dword stride, _dword size, const _byte* buffer, _RESOURCE_DRAW_TYPE draw_type )
{
	return new GLVertexBuffer( stride, size, buffer, draw_type );
}

_byte* GLDrv::LockVertexBuffer( VertexBufferRHI* vertexbuffer, _dword offset, _dword size )
{
	DYNAMIC_CAST_GLRESOURCE( VertexBuffer, vertexbuffer );
	return gl_vertexbuffer->Lock( offset, size );
}

_void GLDrv::UnlockVertexBuffer( VertexBufferRHI* vertexbuffer )
{
	DYNAMIC_CAST_GLRESOURCE( VertexBuffer, vertexbuffer );
	return gl_vertexbuffer->Unlock( );
}

const _byte* GLDrv::GetVertexBufferData( VertexBufferRHI* vertexbuffer )
{
	DYNAMIC_CAST_GLRESOURCE( VertexBuffer, vertexbuffer );
	return gl_vertexbuffer->GetBufferData( );
}

_dword GLDrv::GetVertexBufferStride( VertexBufferRHI* vertexbuffer )
{
	DYNAMIC_CAST_GLRESOURCE( VertexBuffer, vertexbuffer );
	return gl_vertexbuffer->GetStride( );
}

_dword GLDrv::GetVertexBufferSize( VertexBufferRHI* vertexbuffer )
{
	DYNAMIC_CAST_GLRESOURCE( VertexBuffer, vertexbuffer );
	return gl_vertexbuffer->GetBufferSize( );
}

_ubool GLDrv::UpdateVertexBuffer( VertexBufferRHI* vertexbuffer, _dword offset, _dword size, const _byte* buffer )
{
	if ( GetGLContextNumber( ) > 1 && gGLSupportVAO == _false )
		GLCachedBindVBO( 0 );

	DYNAMIC_CAST_GLRESOURCE( VertexBuffer, vertexbuffer );
	return gl_vertexbuffer->Update( offset, size, buffer );
}

_ubool GLDrv::ResizeVertexBuffer( VertexBufferRHI* vertexbuffer, _dword size )
{
	DYNAMIC_CAST_GLRESOURCE( VertexBuffer, vertexbuffer );
	return gl_vertexbuffer->Resize( size );
}

_ubool GLDrv::FlushVertexBuffer( VertexBufferRHI* vertexbuffer )
{
	DYNAMIC_CAST_GLRESOURCE( VertexBuffer, vertexbuffer );
	return gl_vertexbuffer->Flush( );
}

_dword GLDrv::GetVertexBufferResID( VertexBufferRHI* vertexbuffer )
{
	DYNAMIC_CAST_GLRESOURCE( VertexBuffer, vertexbuffer );
	return gl_vertexbuffer->GetResource( );
}