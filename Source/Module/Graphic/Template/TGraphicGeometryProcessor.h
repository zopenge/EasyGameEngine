//! @file     TGraphicGeometryProcessor.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GeometryChunk
//----------------------------------------------------------------------------

struct GeometryChunk
{
	//!	The distance
	_float				mDistance;
	//!	The renderable geometry
	RenderableGeometry	mGeometry;
};

//----------------------------------------------------------------------------
// TGraphicGeometryProcessor
//----------------------------------------------------------------------------

template< _dword _MAX_GEOMETRY_CHUNK, typename CompareFunc >
class TGraphicGeometryProcessor
{
protected:
	typedef BinaryHeap< _MAX_GEOMETRY_CHUNK, GeometryChunk*, CompareFunc > GeometryChunkHeap;

protected:
	//!	The max allocator buffer size in bytes
	enum { _MAX_ALLOCATOR_BUFFER_SZIE = 1 MB };
	//!	The max vertex buffer size in bytes
	enum { _MAX_VERTEX_BUFFER_SZIE = 2 MB };

protected:
	//!	The allocator
	IAllocatorRef			mAllocator;

	//!	The number of sub-sections in vertex buffer ( for offset usage )
	_dword					mVBSubSectionNumber[ _GVT_MAX_NUMBER ];
	//!	The offset of vertex buffer in bytes ( for allocating )
	_dword					mVBOffset[ _GVT_MAX_NUMBER ];
	//!	The vertex buffer
	VertexBufferRHIRef		mVertexBuffersRHI[ _GVT_MAX_NUMBER ];

	//!	The geometry chunk heap
	GeometryChunkHeap		mGeometryChunkHeap;

	//!	The last vertex type
	_GRAPHIC_VERTEX_TYPE	mLastVertexType;
	//!	The last geometry render stats ID ( to fast compare )
	_dword					mLastGeometryRenderStatsID;
	//!	The last geometry chunk 
	GeometryChunk*			mLastGeometryChunk;

protected:
	//!	Get default vertex stride in bytes.
	static _dword GetDefaultVertexStride( _GRAPHIC_VERTEX_TYPE vertex_type );

	//!	Calculate the geometry render stats ID.
	static _dword BuildGeometryRenderStatsID( const RenderableGeometry& geometry );

protected:
	//!	When update vertex buffer.
	//!	@param		vertex_type		The vertex type.
	//!	@param		offset			The offset of vertex buffer in bytes.
	//!	@param		size			The vertex buffer size in bytes.
	//!	@param		vertex_buffer	The vertex buffer.
	//! @return		True indicates success, false indicates failure.
	_ubool UpdateVertexBuffer( _GRAPHIC_VERTEX_TYPE vertex_type, _dword offset, _dword size, const _byte* vertex_buffer );
	//!	Allocate vertex buffer.
	//!	@param		vertex_type		The vertex type.
	//!	@param		size			The allocated size in bytes.
	//!	@param		offset			The offset of vertex buffer in bytes.
	//!	@return		The vertex buffer resource.
	VertexBufferRHI* AllocateVertexBuffer( _GRAPHIC_VERTEX_TYPE vertex_type, _dword size, _dword* offset );

	//!	Check whether can combine with last geometry or not.
	//!	@param		vertex_type		The vertex type.
	//! @param		geometry		The geometry.
	//!	@param		render_stats_id	The geometry render stats ID.
	//!	@return		True indicates can combine.
	_ubool CanCombineWithLastGeometryChunk( _GRAPHIC_VERTEX_TYPE vertex_type, const RenderableGeometry& geometry, _dword render_stats_id ) const;

	//! Insert geometry.
	//!	@param		vertex_type		The vertex type.
	//! @param		offset			The offset of vertex buffer in bytes.
	//! @param		distance		The distance of geometry to view.
	//! @param		geometry		The geometry.
	//! @return		The renderable geometry in processor after insert.
	RenderableGeometry* InsertGeometry( _GRAPHIC_VERTEX_TYPE vertex_type, _dword offset, _float distance, const RenderableGeometry& geometry );
	//!	Insert geometry chunk.
	//! @param		distance		The distance of geometry to view.
	//! @param		geometry		The geometry.
	//! @return		The geometry chunk.
	GeometryChunk* InsertGeometryChunk( _float distance, const RenderableGeometry& geometry );

public:
	TGraphicGeometryProcessor( IAllocator* allocator );
	~TGraphicGeometryProcessor( );

public:
	//! Render geometry.
	//! @param		distance		The distance of geometry to view.
	//! @param		geometry		The geometry.
	//! @return		none.
	_void Render( _float distance, const RenderableGeometry& geometry );
	//! Render geometry with vertex buffer.
	//! @param		distance		The distance of geometry to view.
	//!	@param		vertex_type		The vertex type.
	//!	@param		vertex_buffer	The vertex buffer.
	//! @param		geometry		The geometry.
	//! @return		none.
	_void Render( _float distance, _GRAPHIC_VERTEX_TYPE vertex_type, const _byte* vertex_buffer, const RenderableGeometry& geometry );

	//!	Flush all render commands.
	//!	@param		drawer			The primitive drawer.
	//!	@return		none.
	_void Flush( IGraphicDrawer* renderer );
};

//----------------------------------------------------------------------------
// TGraphicGeometryProcessor Implementation
//----------------------------------------------------------------------------

template< _dword _MAX_GEOMETRY_CHUNK, typename CompareFunc >
TGraphicGeometryProcessor< _MAX_GEOMETRY_CHUNK, CompareFunc >::TGraphicGeometryProcessor( IAllocator* allocator ) : mAllocator( allocator )
{
	EGE_INIT_ARRAY( mVBSubSectionNumber );
	EGE_INIT_ARRAY( mVBOffset );

	mLastVertexType				= _GVT_UNKNOWN;
	mLastGeometryRenderStatsID	= 0;
	mLastGeometryChunk			= _null;
}

template< _dword _MAX_GEOMETRY_CHUNK, typename CompareFunc >
TGraphicGeometryProcessor< _MAX_GEOMETRY_CHUNK, CompareFunc >::~TGraphicGeometryProcessor( )
{
}

template< _dword _MAX_GEOMETRY_CHUNK, typename CompareFunc >
_dword TGraphicGeometryProcessor< _MAX_GEOMETRY_CHUNK, CompareFunc >::GetDefaultVertexStride( _GRAPHIC_VERTEX_TYPE vertex_type )
{
	switch ( vertex_type )
	{
		case _GVT_OVERLAY_WITHOUT_TEX:		return sizeof( RenderableOverlayWithoutTex );
		case _GVT_OVERLAY_WITH_TEX1:		return sizeof( RenderableOverlayWithTex1 );
		case _GVT_OVERLAY_WITH_TEX2:		return sizeof( RenderableOverlayWithTex2 );
		case _GVT_OVERLAY_TEXT:				return sizeof( RenderableOverlayWithTex1 );
		case _GVT_PRIMITIVE_WITHOUT_TEX:	return sizeof( RenderablePrimitiveWithoutTex );
		case _GVT_PRIMITIVE_WITH_TEX1:		return sizeof( RenderablePrimitiveWithTex1 );
		case _GVT_PRIMITIVE_WITH_TEX2:		return sizeof( RenderablePrimitiveWithTex2 );
		case _GVT_PRIMITIVE_TEXT:			return sizeof( RenderablePrimitiveWithTex1 );
		default:
			return 0;
	}
}

template< _dword _MAX_GEOMETRY_CHUNK, typename CompareFunc >
_dword TGraphicGeometryProcessor< _MAX_GEOMETRY_CHUNK, CompareFunc >::BuildGeometryRenderStatsID( const RenderableGeometry& geometry )
{
	_dword id = 0;
	for ( _dword i = 0; i < sizeof ( RenderableGeometryBase ) / sizeof( _dword ); i ++ )
		id += ((const _dword*) &geometry)[i];

	return id;
}

template< _dword _MAX_GEOMETRY_CHUNK, typename CompareFunc >
VertexBufferRHI* TGraphicGeometryProcessor< _MAX_GEOMETRY_CHUNK, CompareFunc >::AllocateVertexBuffer( _GRAPHIC_VERTEX_TYPE vertex_type, _dword size, _dword* offset )
{
	if ( mVBOffset[ vertex_type ] + size > _MAX_VERTEX_BUFFER_SZIE )
		return _null;

	// Create vertex buffer
	if ( mVertexBuffersRHI[ vertex_type ].IsNull( ) )
	{
		mVertexBuffersRHI[ vertex_type ] = gDynamicRHI->CreateVertexBuffer( GetDefaultVertexStride( vertex_type ), _MAX_VERTEX_BUFFER_SZIE, _null, _RUF_DYNAMIC );
		if ( mVertexBuffersRHI[ vertex_type ].IsNull( ) )
			return _null;
	}

	// Feedback the current offset of vertex buffer
	if ( offset != _null )
		*offset = mVBOffset[ vertex_type ];

	// Update the sub-section number
	mVBSubSectionNumber[ vertex_type ] ++;

	// Update the offset of vertex buffer ( in order to match the valid offset of vertex buffer )
	mVBOffset[ vertex_type ] += size;

	return mVertexBuffersRHI[ vertex_type ];
}

template< _dword _MAX_GEOMETRY_CHUNK, typename CompareFunc >
_ubool TGraphicGeometryProcessor< _MAX_GEOMETRY_CHUNK, CompareFunc >::CanCombineWithLastGeometryChunk( _GRAPHIC_VERTEX_TYPE vertex_type, const RenderableGeometry& geometry, _dword render_stats_id ) const
{
	// We must enable the primitive auto combination feature
	if ( gGraphicModule->IsEnableOptions( _GRAPHIC_OPTION_PRIMITIVE_AUTO_COMBINATION ) == _false )
		return _false;

	// We must have the last geometry chunk info
	if ( mLastGeometryChunk == _null )
		return _false;

	// Get the last geometry
	const RenderableGeometry& last_geometry = mLastGeometryChunk->mGeometry;

	// We can't combine the specified primitive type like this
	if ( geometry.mPrimitiveType >= _PT_LINE_LOOP && geometry.mPrimitiveType <= _PT_TRIANGLE_FAN )
		return _false;

	// The weight must be match
	if ( Math::Equal( geometry.mWeight, last_geometry.mWeight ) == _false )
		return _false;

	// The last vertex type not match
	if ( mLastVertexType != vertex_type )
		return _false;

	// The viewport is different with last geometry
	if ( geometry.mViewportSize != _null && geometry.mViewportSize != last_geometry.mViewportSize )
		return _false;

	// The transform is different with last geometry
	if ( geometry.mTransform != _null && geometry.mTransform != last_geometry.mTransform )
		return _false;

	// Check the geometry render status
	if ( mLastGeometryRenderStatsID != render_stats_id )
		return _false;

	// Check the uniform buffer
	if ( geometry.mUniformBuffers != last_geometry.mUniformBuffers )
		return _false;

	return _true;
}

template< _dword _MAX_GEOMETRY_CHUNK, typename CompareFunc >
_ubool TGraphicGeometryProcessor< _MAX_GEOMETRY_CHUNK, CompareFunc >::UpdateVertexBuffer( _GRAPHIC_VERTEX_TYPE vertex_type, _dword offset, _dword size, const _byte* vertex_buffer )
{
	if ( ( offset > _MAX_VERTEX_BUFFER_SZIE ) || ( offset + size > _MAX_VERTEX_BUFFER_SZIE ) )
		return _false;

	EGE_ASSERT( mVertexBuffersRHI[ vertex_type ].IsValid( ) );
	return gDynamicRHI->UpdateVertexBuffer( mVertexBuffersRHI[ vertex_type ], offset, size, vertex_buffer );
}

template< _dword _MAX_GEOMETRY_CHUNK, typename CompareFunc >
RenderableGeometry* TGraphicGeometryProcessor< _MAX_GEOMETRY_CHUNK, CompareFunc >::InsertGeometry( _GRAPHIC_VERTEX_TYPE vertex_type, _dword offset, _float distance, const RenderableGeometry& geometry )
{
	// Insert geometry chunk
	GeometryChunk* chunk = InsertGeometryChunk( distance, geometry );
	if ( chunk == _null )
		return _null;

	// Update offset of vertex buffer
	chunk->mGeometry.mVertexOffset = offset;

	// Update vertex buffer
	chunk->mGeometry.mVertexBufferRHI = mVertexBuffersRHI[ vertex_type ];

	return &chunk->mGeometry;
}

template< _dword _MAX_GEOMETRY_CHUNK, typename CompareFunc >
GeometryChunk* TGraphicGeometryProcessor< _MAX_GEOMETRY_CHUNK, CompareFunc >::InsertGeometryChunk( _float distance, const RenderableGeometry& geometry )
{
	// Allocate new geometry chunk
	GeometryChunk* chunk = (GeometryChunk*) mAllocator->Alloc( sizeof( GeometryChunk ) );
	if ( chunk == _null )
		return _null;

	// Set the chunk info
	chunk->mDistance = distance;
	chunk->mGeometry = geometry;

	// We increase the distance a little for adding order ( it will make optimize confused ... not use it )
	chunk->mDistance += _float( mGeometryChunkHeap.Number( ) );
	
	// Insert into heap and feedback
	mGeometryChunkHeap.Insert( chunk );
	return chunk;
}

template< _dword _MAX_GEOMETRY_CHUNK, typename CompareFunc >
_void TGraphicGeometryProcessor< _MAX_GEOMETRY_CHUNK, CompareFunc >::Render( _float distance, const RenderableGeometry& geometry )
{
	EGE_ASSERT( geometry.mVertexBufferRHI != _null );

	InsertGeometryChunk( distance, geometry );
}

template< _dword _MAX_GEOMETRY_CHUNK, typename CompareFunc >
_void TGraphicGeometryProcessor< _MAX_GEOMETRY_CHUNK, CompareFunc >::Render( _float distance, _GRAPHIC_VERTEX_TYPE vertex_type, const _byte* vertex_buffer, const RenderableGeometry& geometry )
{
	EGE_ASSERT( vertex_buffer != _null );

	// The render stats of geometry
	_dword render_stats_id = BuildGeometryRenderStatsID( geometry );

	// Can combine with last geometry
	if ( CanCombineWithLastGeometryChunk( vertex_type, geometry, render_stats_id ) )
	{
		// The offset of vertex buffer after allocated
		_dword offset = 0;

		// Allocate vertex buffer
		AllocateVertexBuffer( vertex_type, geometry.mVertexSize, &offset );

		// Update the vertex buffer
		UpdateVertexBuffer( vertex_type, offset, geometry.mVertexSize, vertex_buffer );

		// Update the size of geometry in vertex buffer
		mLastGeometryChunk->mGeometry.mVertexSize += geometry.mVertexSize;
	}
	else
	{
		// Insert geometry chunk
		GeometryChunk* geometry_chunk = InsertGeometryChunk( distance, geometry );
		if ( geometry_chunk == _null )
			return;

		// The offset of vertex buffer after allocated
		_dword offset = 0;

		// Allocate vertex buffer
		VertexBufferRHIRef vertex_buffer_rhi = AllocateVertexBuffer( vertex_type, geometry.mVertexSize, &offset );
		if ( vertex_buffer_rhi.IsNull( ) )
			return;

		// Update the vertex buffer
		UpdateVertexBuffer( vertex_type, offset, geometry.mVertexSize, vertex_buffer );

		// Update offset of vertex buffer
		geometry_chunk->mGeometry.mVertexOffset = offset;

		// Update the vertex buffer resource
		geometry_chunk->mGeometry.mVertexBufferRHI = vertex_buffer_rhi;

		// Update the last geometry info
		mLastVertexType				= vertex_type;
		mLastGeometryRenderStatsID	= render_stats_id;
		mLastGeometryChunk			= geometry_chunk;
	}
}

template< _dword _MAX_GEOMETRY_CHUNK, typename CompareFunc >
_void TGraphicGeometryProcessor< _MAX_GEOMETRY_CHUNK, CompareFunc >::Flush( IGraphicDrawer* renderer )
{
	EGE_ASSERT( renderer != _null );

	// Render all geometry
	GeometryChunk* geometry_chunk = _null;
	while ( mGeometryChunkHeap.ExtractTopElement( geometry_chunk ) )
	{
		renderer->DrawGeometry( geometry_chunk->mGeometry );

		geometry_chunk->mGeometry.Clear( );
	}

	// Clear the last geometry info
	mLastVertexType				= _GVT_UNKNOWN;
	mLastGeometryRenderStatsID	= 0;
	mLastGeometryChunk			= _null;

	// Clear the temporary info
	EGE_INIT_ARRAY( mVBSubSectionNumber );
	EGE_INIT_ARRAY( mVBOffset );
}

}