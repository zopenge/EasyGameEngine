//! @file     GLIndexBuffer.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLDrv-IndexBuffer Implementation
//----------------------------------------------------------------------------

IndexBufferRHIPassRef GLDrv::CreateIndexBuffer( _dword stride, _dword size, const _byte* buffer, _RESOURCE_DRAW_TYPE draw_type )
{
	return new GLIndexBuffer( stride, size, buffer, draw_type );
}

_byte* GLDrv::LockIndexBuffer( IndexBufferRHI* indexbuffer, _dword offset, _dword size )
{
	DYNAMIC_CAST_GLRESOURCE( IndexBuffer, indexbuffer );
	return gl_indexbuffer->Lock( offset, size );
}

_void GLDrv::UnlockIndexBuffer( IndexBufferRHI* indexbuffer )
{
	DYNAMIC_CAST_GLRESOURCE( IndexBuffer, indexbuffer );
	return gl_indexbuffer->Unlock( );
}

const _byte* GLDrv::GetIndexBufferData( IndexBufferRHI* indexbuffer )
{
	DYNAMIC_CAST_GLRESOURCE( IndexBuffer, indexbuffer );
	return gl_indexbuffer->GetBufferData( );
}

_dword GLDrv::GetIndexBufferStride( IndexBufferRHI* indexbuffer )
{
	DYNAMIC_CAST_GLRESOURCE( IndexBuffer, indexbuffer );
	return gl_indexbuffer->GetStride( );
}

_dword GLDrv::GetIndexBufferSize( IndexBufferRHI* indexbuffer )
{
	DYNAMIC_CAST_GLRESOURCE( IndexBuffer, indexbuffer );
	return gl_indexbuffer->GetBufferSize( );
}

_ubool GLDrv::UpdateIndexBuffer( IndexBufferRHI* index_buffer, _dword offset, _dword size, const _byte* buffer )
{
	if ( GetGLContextNumber( ) > 1 && gGLSupportVAO == _false )
		GLCachedBindIBO( 0 );

	DYNAMIC_CAST_GLRESOURCE( IndexBuffer, index_buffer );
	return gl_index_buffer->Update( offset, size, buffer );
}

_ubool GLDrv::ResizeIndexBuffer( IndexBufferRHI* index_buffer, _dword size )
{
	DYNAMIC_CAST_GLRESOURCE( IndexBuffer, index_buffer );
	return gl_index_buffer->Resize( size );
}

_ubool GLDrv::FlushIndexBuffer( IndexBufferRHI* index_buffer )
{
	DYNAMIC_CAST_GLRESOURCE( IndexBuffer, index_buffer );
	return gl_index_buffer->Flush( );
}

_dword GLDrv::GetIndexBufferResID( IndexBufferRHI* index_buffer )
{
	DYNAMIC_CAST_GLRESOURCE( IndexBuffer, index_buffer );
	return gl_index_buffer->GetResource( );
}