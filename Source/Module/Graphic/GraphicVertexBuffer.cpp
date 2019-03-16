//! @file     GraphicVertexBuffer.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicVertexBuffer Implementation
//----------------------------------------------------------------------------

GraphicVertexBuffer::GraphicVertexBuffer( VertexBufferRHI* vb )
{
	mVertexBuffer = vb;
}

GraphicVertexBuffer::~GraphicVertexBuffer( )
{
}

_dword GraphicVertexBuffer::GetStride( ) const
{
	return gDynamicRHI->GetVertexBufferStride( mVertexBuffer );
}

_dword GraphicVertexBuffer::GetSize( ) const
{
	return gDynamicRHI->GetVertexBufferSize( mVertexBuffer );
}

_void GraphicVertexBuffer::Write( _dword offset, _dword size, const _byte* buffer )
{
	gDynamicRHI->UpdateVertexBuffer( mVertexBuffer, offset, size, buffer );
}

_void GraphicVertexBuffer::Flush( )
{
	gDynamicRHI->FlushVertexBuffer( mVertexBuffer );
}

_byte* GraphicVertexBuffer::LockBufferData( _dword offset, _dword size )
{
	return gDynamicRHI->LockVertexBuffer( mVertexBuffer, offset, size );
}

_void GraphicVertexBuffer::UnlockBufferData( )
{
	gDynamicRHI->UnlockVertexBuffer( mVertexBuffer );
}

const _byte* GraphicVertexBuffer::GetBufferData( )
{
	return gDynamicRHI->GetVertexBufferData( mVertexBuffer );
}