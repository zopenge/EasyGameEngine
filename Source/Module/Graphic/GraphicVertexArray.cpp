//! @file     GraphicVertexArray.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicVertexArray Implementation
//----------------------------------------------------------------------------

GraphicVertexArray::GraphicVertexArray( )
{
	mIBStride	= 0;
	mIBOffset	= 0;

	mVBStride	= 0;
	mVBOffset	= 0;
}

GraphicVertexArray::~GraphicVertexArray( )
{
}

_ubool GraphicVertexArray::Initialize( _RESOURCE_DRAW_TYPE draw_type, VertexDeclarationRHI* vertex_decl )
{
	if ( vertex_decl == _null )
		return _false;

	// Get the vertex declaration
	mVertexDeclRHI = vertex_decl;

	// Get the stride of vertex in bytes
	_dword vertex_stride = gDynamicRHI->GetVertexDeclarationStride( vertex_decl );
	if ( vertex_stride == 0 )
		return _false;

	// Create VAO resource
	mVAOResource = gDynamicRHI->CreateVertexArray( );
	if ( mVAOResource.IsNull( ) )
		return _false;

	// Bind VAO
	gDynamicRHI->BindVertexArray( mVAOResource );

	// Get the initial VB size
	_dword initial_vb_size = vertex_stride;;

	// Create vertex buffer
	VertexBufferRHIRef vertex_buffer = gDynamicRHI->CreateVertexBuffer( vertex_stride, initial_vb_size, _null, draw_type );
	if ( vertex_buffer.IsNull( ) )
		return _false;

	// Get the initial IB size
	_dword initial_ib_size = sizeof( _word );;

	// Create index buffer
	IndexBufferRHIRef index_buffer = gDynamicRHI->CreateIndexBuffer( sizeof( _word ), initial_ib_size, _null, draw_type );
	if ( index_buffer.IsNull( ) )
		return _false;

	// Setup vertex declaration
	if ( gDynamicRHI->SetVertexArrayDecl( mVAOResource, vertex_decl, vertex_buffer, index_buffer ) == _false )
		return _false;

	// Create buffers manager
	mVertexBuffer	= gGraphicResourceManager->CreateVertexBuffer( vertex_buffer );
	mIndexBuffer	= gGraphicResourceManager->CreateIndexBuffer( index_buffer );
	if ( mVertexBuffer.IsNull( ) || mIndexBuffer.IsNull( ) )
		return _false;

	// Unbind VAO
	gDynamicRHI->UnbindVertexArray( );

	// Initialize cache info
	mVBStride	= mVertexBuffer->GetStride( );
	mIBStride	= mIndexBuffer->GetStride( );

	WLOG_TRACE_2( L"Create graphic vertex array object (VBStride: %d, IBStride: %d)", mVBStride, mIBStride );

	return _true;
}

VertexArrayRHI* GraphicVertexArray::GetResource( ) const
{
	return mVAOResource.GetPtr( );
}

_void GraphicVertexArray::Bind( )
{
	gDynamicRHI->BindVertexArray( mVAOResource );
}

_dword GraphicVertexArray::GetElementOffset( _VERTEX_ELEMENT_USAGE usage, _dword usage_index ) const
{
	// Get vertex declaration define
	const VertexElementRHIArray& vertex_decl_define = GetDynamicRHI( )->GetVertexDeclarationDefine( mVertexDeclRHI.GetPtr( ) );

	// Get offset of element
	for ( _dword i = 0; i < vertex_decl_define.Number( ); i ++ )
	{
		if ( vertex_decl_define[i].mUsage == usage && vertex_decl_define[i].mUsageIndex == usage_index )
			return vertex_decl_define[i].mOffset;
	}

	return -1;
}

_byte* GraphicVertexArray::LockVBData( _dword offset, _dword size )
{
	return mVertexBuffer->LockBufferData( offset, size );
}

_void GraphicVertexArray::UnlockVBData( )
{
	mVertexBuffer->UnlockBufferData( );
}

const _byte* GraphicVertexArray::GetVBData( )
{
	return mVertexBuffer->GetBufferData( );
}

_dword GraphicVertexArray::GetVBStride( ) const
{
	return mVBStride;
}

_dword GraphicVertexArray::GetVBSize( ) const
{
	return mVertexBuffer->GetSize( );
}

_dword GraphicVertexArray::GetVBOffset( ) const
{
	return mVBOffset;
}

_dword GraphicVertexArray::GetVBIndex( ) const
{
	return mVBOffset / mVBStride;
}

_void GraphicVertexArray::WriteVB( _dword offset, _dword size, const _byte* buffer )
{
	mVertexBuffer->Write( offset, size, buffer );

	mVBOffset = offset + size;
}

_void GraphicVertexArray::WriteVB( _dword size, const _byte* buffer )
{
	mVertexBuffer->Write( mVBOffset, size, buffer );

	mVBOffset += size;
}

_byte* GraphicVertexArray::LockIBData( _dword offset, _dword size )
{
	return mIndexBuffer->LockBufferData( offset, size );
}

_void GraphicVertexArray::UnlockIBData( )
{
	mIndexBuffer->UnlockBufferData( );
}

const _byte* GraphicVertexArray::GetIBData( )
{
	return mIndexBuffer->GetBufferData( );
}

_dword GraphicVertexArray::GetIBStride( ) const
{
	return mIBStride;
}

_dword GraphicVertexArray::GetIBSize( ) const
{
	return mIndexBuffer->GetSize( );
}

_dword GraphicVertexArray::GetIBOffset( ) const
{
	return mIBOffset;
}

_void GraphicVertexArray::WriteIB( _dword offset, _dword size, const _byte* buffer )
{
	mIndexBuffer->Write( offset, size, buffer );

	mIBOffset = offset + size;
}

_void GraphicVertexArray::WriteIB( _dword size, const _byte* buffer )
{
	mIndexBuffer->Write( mIBOffset, size, buffer );

	mIBOffset += size;
}

_void GraphicVertexArray::WriteBuffers( _dword vb_size, const _byte* vb_data, _dword ib_number, const _word* ib_data )
{
	EGE_ASSERT( vb_data != _null );

	// Update IBO
	if ( ib_data != _null )
	{
		EGE_ASSERT( ib_number != 0 );

		// Get the offset of vertex buffer
		_word cur_index_offset = (_word) GetVBIndex( );

		// Fix the index buffer with the start index of IBO
		static _word fixed_ib_data[ 0xFFFF ];
		for ( _dword i = 0; i < ib_number; i ++ )
			fixed_ib_data[i] = ib_data[i] + cur_index_offset;

		// Update index buffer
		_dword ib_data_size = ib_number * sizeof( _word );
		WriteIB( ib_data_size, (const _byte*) fixed_ib_data );
	}

	// Update VBO
	EGE_ASSERT( vb_size != 0 );
	WriteVB( vb_size, vb_data );
}

_void GraphicVertexArray::FlushBuffers( )
{
	if ( gDynamicRHI->IsSupportVAO( ) )
		Bind( );

	mVertexBuffer->Flush( );
	mIndexBuffer->Flush( );

	mVBOffset = 0;
	mIBOffset = 0;
}