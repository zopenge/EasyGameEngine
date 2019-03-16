//! @file     GraphicIndexBuffer.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicIndexBuffer Implementation
//----------------------------------------------------------------------------

GraphicIndexBuffer::GraphicIndexBuffer( IndexBufferRHI* ib )
{
	mIndexBuffer = ib;
}

GraphicIndexBuffer::~GraphicIndexBuffer( )
{
}

_dword GraphicIndexBuffer::GetStride( ) const
{
	return gDynamicRHI->GetIndexBufferStride( mIndexBuffer );
}

_dword GraphicIndexBuffer::GetSize( ) const
{
	return gDynamicRHI->GetIndexBufferSize( mIndexBuffer );
}

_void GraphicIndexBuffer::Write( _dword offset, _dword size, const _byte* buffer )
{
	gDynamicRHI->UpdateIndexBuffer( mIndexBuffer, offset, size, buffer );
}

_void GraphicIndexBuffer::Flush( )
{
	gDynamicRHI->FlushIndexBuffer( mIndexBuffer );
}

_byte* GraphicIndexBuffer::LockBufferData( _dword offset, _dword size )
{
	return gDynamicRHI->LockIndexBuffer( mIndexBuffer, offset, size );
}

_void GraphicIndexBuffer::UnlockBufferData( )
{
	gDynamicRHI->UnlockIndexBuffer( mIndexBuffer );
}

const _byte* GraphicIndexBuffer::GetBufferData( )
{
	return gDynamicRHI->GetIndexBufferData( mIndexBuffer );
}