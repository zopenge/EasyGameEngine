//! @file     GraphicVAOGroup.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicVAOGroup Implementation
//----------------------------------------------------------------------------

GraphicVAOGroup::GraphicVAOGroup( )
{
}

GraphicVAOGroup::~GraphicVAOGroup( )
{
	for ( _dword i = 0; i < mVAOs.Number( ); i ++ )
	{
		EGE_DELETE( mVAOs[i] );
	}
}

_ubool GraphicVAOGroup::CheckMesh( const IGraphicMesh* mesh, _dword max_vertices_number, _dword stride ) const
{
	// Check the start bytes in VB with vertex stride, it must arrange to it
	if ( mesh->GetVBDataField( ).GetOffset( ) % stride )
		return _false;

	// Check the VB bounds
	if ( (mesh->GetVBDataField( ).GetOffset( ) + mesh->GetVBDataField( ).GetNumber( )) > max_vertices_number * stride )
		return _false;

	// Check the start bytes in IB with 16-bits index buffer bounds, it must arrange to it
	if ( mesh->GetIBDataField( ).GetOffset( ) % sizeof( _word ) )
		return _false;

	return _true;
}

_dword GraphicVAOGroup::WriteVB( VAOInfo* vao_info, _dword vb_stride, _dword vb_size, const _byte* vb_buffer )
{
	// Get offset as start bytes
	_dword start_bytes = vao_info->mVBAllocator->Alloc( vb_size );
	if ( start_bytes == -1 )
		return -1;

	// Check the start bytes with stride
	EGE_ASSERT( (start_bytes % vb_stride) == 0 );

	// Get the VAO
	IGraphicVertexArray* vao = vao_info->mVertexArrayObject;
	EGE_ASSERT( vao != _null );

	// Update VB buffer data
	vao->WriteVB( start_bytes, vb_size, vb_buffer );

	return start_bytes;
}

_dword GraphicVAOGroup::WriteIB( VAOInfo* vao_info, _dword offset, _dword ib_size, const _word* ib_buffer )
{
	// Get the index buffer number
	EGE_ASSERT( (ib_size % sizeof( _word )) == 0 );
	_dword ib_number = ib_size / sizeof( _word );

	// Get offset as start bytes
	_dword start_bytes = vao_info->mIBAllocator->Alloc( ib_size );
	if ( start_bytes == -1 )
		return -1;

	// The index element must add the offset of vertices
	MemArrayPtr< _word > fixed_ib_buffer( ib_number);
	for ( _dword i = 0; i < ib_number; i ++ )
		fixed_ib_buffer[i] = _word(ib_buffer[i] + offset);

	// Get the VAO
	IGraphicVertexArray* vao = vao_info->mVertexArrayObject;
	EGE_ASSERT( vao != _null );

	// Update IB buffer data
	vao->WriteIB( start_bytes, ib_size, (const _byte*) fixed_ib_buffer.GetPointer( ) );

	return start_bytes;
}

GraphicVAOGroup::VAOInfo* GraphicVAOGroup::CreateVAOInfo( _dword vertex_type, _dword vb_size, _dword ib_size )
{
	for ( _dword i = 0; i < mVAOs.Number( ); i ++ )
	{
		VAOInfo* vao_info = mVAOs[i];

		// Check the vertex type
		if ( vao_info->mVertexDecl->GetVertexType( ) != vertex_type )
			continue;

		// Check the VB free space
		if ( vao_info->mVBAllocator->CanAlloc( vb_size ) == _false )
			continue;

		// Check the IB free space
		if ( ib_size != 0 )
		{
			if ( vao_info->mIBAllocator->CanAlloc( ib_size ) == _false )
				continue;
		}

		return vao_info;
	}

	VAOInfo* vao_info = CreateVAOInfo( vertex_type );
	if ( vao_info == _null )
		return _null;

	return vao_info;
}

GraphicVAOGroup::VAOInfo* GraphicVAOGroup::CreateVAOInfo( _dword vertex_type )
{
	// Create vertex declaration
	IGraphicVertexDeclarationRef vertex_decl = GetGraphicResourceManager( )->CreateVertexDeclaration( vertex_type );
	if ( vertex_decl.IsNull( ) )
		return _null;

	// Create VAO
	IGraphicVertexArrayRef vao = GetGraphicResourceManager( )->CreateVertexArray( _RDT_TYPE_DYNAMIC, vertex_decl->GetResource( ) );
	if ( vao.IsNull( ) )
		return _null;

	//!	The max VB and IB size, actually we do not allocate the memory, just for calculating the offset of VB and IB buffers
	const _dword max_ib_size = 64 KB;
	const _dword max_vb_size = 64 MB;

	// Create VB allocator
	IOffsetAllocatorRef vb_allocator = GetInterfaceFactory( )->CreateOffsetAllocator( max_vb_size, 1 );
	if ( vb_allocator.IsNull( ) )
		return _null;

	// Create IB allocator
	IOffsetAllocatorRef ib_allocator = GetInterfaceFactory( )->CreateOffsetAllocator( max_ib_size, 1 );
	if ( ib_allocator.IsNull( ) )
		return _null;

	// Create and append it
	VAOInfo* vao_info				= new VAOInfo( );
	vao_info->mVBAllocator			= vb_allocator;
	vao_info->mIBAllocator			= ib_allocator;
	vao_info->mVertexDecl			= vertex_decl;
	vao_info->mVertexArrayObject	= vao;
	mVAOs.Append( vao_info );

	return vao_info;
}

IGraphicVertexArray* GraphicVAOGroup::GetVAO( _dword vertex_type, _dword vb_size, _dword ib_size )
{
	VAOInfo* vao_info = CreateVAOInfo( vertex_type, vb_size, ib_size );
	if ( vao_info == _null )
		return _null;

	return vao_info->mVertexArrayObject;
}

IGraphicVertexArray* GraphicVAOGroup::GetVAO( _dword vertex_type )
{
	VAOInfo* vao_info = CreateVAOInfo( vertex_type );
	if ( vao_info == _null )
		return _null;

	return vao_info->mVertexArrayObject;
}

_void GraphicVAOGroup::FlushBuffers( )
{
	for ( _dword i = 0; i < mVAOs.Number( ); i ++ )
		mVAOs[i]->mVertexArrayObject->FlushBuffers( );
}

_void GraphicVAOGroup::FreeBuffers( )
{
	for ( _dword i = 0; i < mVAOs.Number( ); i ++ )
	{
		VAOInfo* vao_info = mVAOs[i];
		EGE_ASSERT( vao_info != _null );

		vao_info->mVBAllocator->FreeAll( );
		vao_info->mIBAllocator->FreeAll( );
	}
}

IGraphicMeshPassRef	GraphicVAOGroup::AddMesh( _dword vertex_type, _dword vb_stride, _dword vb_size, const _byte* vb_buffer, _dword ib_size, const _word* ib_buffer )
{
	if ( vertex_type == 0 )
		return _null;

	if ( vb_stride == 0 )
		return _null;

	// Create VAO info
	VAOInfo* vao_info = CreateVAOInfo( vertex_type, vb_size, ib_size );
	if ( vao_info == _null )
		return _null;

	// Fill mesh into VB
	_dword start_bytes_of_vb = WriteVB( vao_info, vb_stride, vb_size, vb_buffer );
	if ( start_bytes_of_vb == -1 )
		return _null;

	// Calculate the offset of IB
	_dword offset = start_bytes_of_vb / vb_stride;

	// Fill mesh into IB
	_dword start_bytes_of_ib = WriteIB( vao_info, offset, ib_size, ib_buffer );
	if ( start_bytes_of_ib == -1 )
		return _null;

	// Build the VB and IB data field
	DwordDataField vb_data_field( start_bytes_of_vb, vb_size );
	DwordDataField ib_data_field( start_bytes_of_ib, ib_size );

	// Get the VAO
	IGraphicVertexArray* vao = vao_info->mVertexArrayObject;
	EGE_ASSERT( vao != _null );

	// Create mesh geometry
	GraphicMesh* mesh = new GraphicMesh( vao, vertex_type, vb_data_field, vao_info->mVBAllocator, ib_data_field, vao_info->mIBAllocator );

	// Check mesh
#ifdef _DEBUG
	EGE_ASSERT( CheckMesh( mesh, vao->GetVBSize( ) / vb_stride, vb_stride ) );
#endif

	// Show log
	WLOG_DEBUG_5( L"Add VAO(%d) - VB:[%d,%d), IB:[%d,%d) mesh", 
		GetDynamicRHI( )->GetVertexArrayResID( vao->GetResource( ) ),
		start_bytes_of_vb, start_bytes_of_vb + vb_size, 
		start_bytes_of_ib, start_bytes_of_ib + ib_size);

	return mesh;
}