//! @file     GLConstantBuffer.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLConstantBuffer Implementation
//----------------------------------------------------------------------------

GLConstantBuffer::GLConstantBuffer( )
{
	_dword offset = 0;

	for ( _dword i = 0; i < _UNIFORM_BUFFER_MAXNUMBER; i ++ )
	{
		mChunks.Append( Chunk( offset, gGLUniformData[i].mSize ) );

		offset += gGLUniformData[i].mSize;
	}
}

GLConstantBuffer::~GLConstantBuffer( )
{
}

_void GLConstantBuffer::Update( _dword slot, _dword offset, _dword size, const _byte* buffer )
{
	Chunk& chunk = mChunks[ slot ];
	EGE_ASSERT( offset + size <= chunk.mSize );

	Platform::MemCpy( chunk.mBuffer	+ offset, buffer, size );
}

_void GLConstantBuffer::UpdateUniforms( GLBoundShader* shader )
{
	EGE_ASSERT( shader != _null );

	// Update all changed uniform buffers
	for ( _dword i = 0; i < mChunks.Number( ); i ++ )
	{
		Chunk& chunk = mChunks[i];

		shader->UpdateUniforms( i, chunk.mBuffer, chunk.mSize );
	}
}