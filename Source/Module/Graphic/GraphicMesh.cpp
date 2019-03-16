//! @file     GraphicMesh.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicMesh Implementation
//----------------------------------------------------------------------------

GraphicMesh::GraphicMesh( IGraphicVertexArray* vao, _dword vertex_type, const DwordDataField& vb_field, IOffsetAllocator* vb_allocator, const DwordDataField& ib_field, IOffsetAllocator* ib_allocator )
{
	mVAO			= vao;

	mVertexType		= vertex_type;

	mVBDataField	= vb_field;
	mVBAllocator	= vb_allocator;

	mIBDataField	= ib_field;
	mIBAllocator	= ib_allocator;
}

GraphicMesh::~GraphicMesh( )
{
	EGE_ASSERT( mVBAllocator.IsValid( ) );
	EGE_ASSERT( mIBAllocator.IsValid( ) );

	// Get offsets
	_dword vb_offset = mVBDataField.GetOffset( );
	_dword ib_offset = mIBDataField.GetOffset( );

	// Remove buffer from VB and IB allocator
	_dword vb_ref_count = mVBAllocator->Free( vb_offset );
	_dword ib_ref_count = mIBAllocator->Free( ib_offset );

	// Cleanup VB allocator
	if ( vb_ref_count == 0 )
	{
		mVBAllocator->Cleanup( );
		WLOG_DEBUG_2( L"Remove (VB:[%d,%d]) mesh from scene", vb_offset, mVBDataField.GetEndOffset( ) );
	}

	// Cleanup IB allocator
	if ( ib_ref_count == 0 )
	{
		mIBAllocator->Cleanup( );
		WLOG_DEBUG_2( L"Remove (IB:[%d,%d]) mesh from scene", ib_offset, mIBDataField.GetEndOffset( ) );
	}
}

IGraphicVertexArray* GraphicMesh::GetVAO( )
{
	return mVAO;
}

const GraphicMeshGeometryInfo& GraphicMesh::GetMeshGeometryInfo( ) const
{
	return mMeshGeometryInfo;
}

const DwordDataField& GraphicMesh::GetVBDataField( ) const
{
	return mVBDataField;
}

const DwordDataField& GraphicMesh::GetIBDataField( ) const
{
	return mIBDataField;
}

_dword GraphicMesh::GetVertexType( ) const
{
	return mVertexType;
}

_dword GraphicMesh::GetVBStride( ) const
{
	return mVAO->GetVBStride( );
}

_dword GraphicMesh::GetVBSize( ) const
{
	return mVBDataField.GetNumber( );
}

_dword GraphicMesh::GetVBOffset( _dword start_index ) const
{
	return mVBDataField.GetOffset( ) + start_index * GetVBStride( );
}

_byte* GraphicMesh::LockVBData( )
{
	return mVAO->LockVBData( GetVBOffset( 0 ), GetVBSize( ) );
}

_void GraphicMesh::UnlockVBData( )
{
	mVAO->UnlockVBData( );
}

const _byte* GraphicMesh::GetVBData( )
{
	const _byte* buffer = mVAO->GetVBData( );
	if ( buffer == _null )
		return _null;

	return buffer + GetVBOffset( 0 );
}

_dword GraphicMesh::GetIBSize( ) const
{
	return mIBDataField.GetNumber( );
}

_dword GraphicMesh::GetIBOffset( _dword start_index ) const
{
	return mIBDataField.GetOffset( ) + start_index * sizeof( _word );
}

_dword GraphicMesh::GetIBStartIndex( ) const
{
	return mIBDataField.GetOffset( ) / sizeof( _word );
}

_dword GraphicMesh::GetIBNumber( ) const
{
	return mIBDataField.GetNumber( ) / sizeof( _word );
}

_word* GraphicMesh::LockIBData( )
{
	return (_word*)mVAO->LockIBData( GetIBOffset( 0 ), GetIBSize( ) );
}

_void GraphicMesh::UnlockIBData( )
{
	mVAO->UnlockIBData( );
}

const _word* GraphicMesh::GetIBData( )
{
	const _byte* buffer = mVAO->GetIBData( );
	if ( buffer == _null )
		return _null;

	return (const _word*)(buffer + GetIBOffset( 0 ));
}

_ubool GraphicMesh::UpdateUVBuffer( _dword usage_index, _dword number, const Vector2* buffer )
{
	if ( number == 0 )
		return _false;

	if ( buffer == _null )
		return _false;

	// Get VB offset in bytes
	_dword vb_offset = GetVBOffset( 0 );
	if ( vb_offset == -1 )
		return _false;

	// Get the VB stride
	_dword vb_stride = GetVBStride( );

	// Get the VB size in bytes
	_dword vb_size = vb_stride * number;
	if ( vb_size == 0 )
		return _false;

	// Get VB buffer data
	_byte* vb_buffer = mVAO->LockVBData( vb_offset, vb_size );
	if ( vb_buffer == _null )
		return _false;

	// Get VB element's offset in bytes
	_dword element_offset = mVAO->GetElementOffset( _VEU_TEXTURE_COORDINATE, usage_index );
	EGE_ASSERT( element_offset != -1 );

	// Update UV
	_byte* to_uv_buffer = vb_buffer + element_offset;
	for ( _dword i = 0; i < number; i ++, to_uv_buffer += vb_stride )
		*(Vector2*) to_uv_buffer = buffer[i];

	mVAO->UnlockVBData( );

	return _true;
}

_ubool GraphicMesh::RayVS( const Ray& ray, _float* distance )
{
	// Get the vertex and index number
	_dword vb_stride		= GetVBStride( );
	_dword vertex_number	= GetVBSize( ) / vb_stride;
	_dword index_number		= GetIBNumber( );

	// Lock VBO and IBO
	const _byte* vb_buffer = GetVBData( );
	const _word* ib_buffer = GetIBData( );
	EGE_ASSERT( vb_buffer != _null );
	EGE_ASSERT( ib_buffer != _null );

	// Test with mesh
	_ubool hit = Intersection::RayVSMesh( ray, vb_stride, vertex_number, vb_buffer, index_number, ib_buffer, distance );
	return hit;
}
