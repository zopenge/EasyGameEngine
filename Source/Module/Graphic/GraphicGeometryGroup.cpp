//! @file     GraphicGeometryGroup.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicGeometryGroup Implementation
//----------------------------------------------------------------------------

GraphicGeometryGroup::GraphicGeometryGroup( )
{
	mRenderQueueType = _GRAPHIC_RENDER_BACKGROUND;
}

GraphicGeometryGroup::~GraphicGeometryGroup( )
{
}

_void GraphicGeometryGroup::SetTexturesSamplerState( const GraphicGeometryInfo& geometry_info )
{
	const GraphicRenderStateInfo&	state_info		= geometry_info.mRenderStates;
	const SamplerStateRHIRefMap&	sampler_states	= state_info.mSamplerStates;
	
	// We must use the textures to match the slot index, not sampler states
	_dword slot_index = 0;
	for ( Texture2DRHIRefMap::Iterator it = geometry_info.mTextures.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		const SamplerStateRHIRef* sampler_state = sampler_states.Search( it.GetKey( ) );
		if ( sampler_state == _null )
			continue;

		gDynamicRHI->SetSamplerState( slot_index ++, *sampler_state, it.GetObject( ) );
	}

	// Set the sampler state of texture cube
	gDynamicRHI->SetSamplerState( slot_index ++, state_info.mCubeTextureSamplerState, geometry_info.mTextureCube );
}

_float GraphicGeometryGroup::GetGeometryDistance( IGraphicSceneView* scene_view, const GraphicGeometry& geometry ) const
{
	const GraphicMeshGeometryInfo& mesh_geometry_info = geometry.GetGeometryInfo( );

	_float distance = scene_view->GetDistanceFromCamera( mesh_geometry_info.mAABox.CenterVector( ) );

	return distance + mesh_geometry_info.mRenderDistanceOffset;
}

_void GraphicGeometryGroup::PaintGeometry( const GraphicGeometry& geometry )
{
	const GraphicGeometryInfo& geometry_info = geometry.GetGeometryInfo( );

	// Set the weight by primitive type
	switch ( geometry_info.mPrimitiveType )
	{
		case _PT_LINE_LIST:
		case _PT_LINE_LOOP:
			gDynamicRHI->SetLineWidth( geometry_info.mWeight );
			break;

		default:
			break;
	}

	// Bind VAO
	gDynamicRHI->BindVertexArray( geometry_info.mVAOResource );

	// Set the viewport
	EGE_ASSERT( geometry_info.mViewport != _null );
	gDynamicRHI->SetViewport( *geometry_info.mViewport );

	// Get the bound shader
	BoundShaderRHI* bound_shader = geometry.GetEffect( )->GetBoundShader( );
	EGE_ASSERT( bound_shader != _null );

	// Set the bound shader
	gDynamicRHI->SetBoundShader( bound_shader );

	// Get the modified uniform buffers info
	const _dword				uniform_buffers_number	= geometry_info.mUBONumber;
	const GraphicUniformBuffer* uniform_buffers			= geometry_info.mUBOs;

	// Update uniform buffers
	for ( _dword i = 0; i < geometry_info.mUBONumber; i ++ )
	{
		const GraphicUniformBuffer& uniform_buffer = geometry_info.mUBOs[i];

		gDynamicRHI->UpdateUniformBuffer( bound_shader, uniform_buffer.mLocation, uniform_buffer.mBuffer, uniform_buffer.mSize );
	}

	// Set the sampler state of textures
	SetTexturesSamplerState( geometry_info );

	// Set other render states
	const GraphicRenderStateInfo& state_info = geometry_info.mRenderStates;
	gDynamicRHI->SetRasterizerState( state_info.mRasterizerState );
	gDynamicRHI->SetDepthState( state_info.mDepthState );
	gDynamicRHI->SetStencilState( state_info.mStencilState );
	gDynamicRHI->SetBlendState( state_info.mBlendState );

	// Draw primitives
	if ( geometry_info.mIBONumber != 0 )
		gDynamicRHI->DrawIndexedPrimitive( (_PRIMITIVE_TYPE) geometry_info.mPrimitiveType, geometry_info.mIBOStartIndex, geometry_info.mIBONumber );
	else
		gDynamicRHI->DrawPrimitive( (_PRIMITIVE_TYPE) geometry_info.mPrimitiveType, geometry_info.mVBOffset / geometry_info.mVBStride, geometry_info.mVBSize / geometry_info.mVBStride );
}

_void GraphicGeometryGroup::PaintGeometriesInNormalMode( )
{
	for ( _dword i = 0; i < mGeometries.Number( ); i ++ )
		PaintGeometry( *mGeometries[i].mObject2 );

	mGeometries.Clear( );
}

_void GraphicGeometryGroup::PaintGeometriesInOptimizeMode( )
{
	if ( mGeometries.Number( ) == 0 )
		return;

	// Get the latest geometry
	GraphicGeometry* last_geometry = mGeometries[0].mObject2;
	EGE_ASSERT( last_geometry != _null );

	// Draw all geometries
	for ( _dword i = 1; i < mGeometries.Number( ); i ++ )
	{
		GraphicGeometry* geometry = mGeometries[i].mObject2;
		EGE_ASSERT( geometry != _null );

		// Check whether can combine it
		if ( last_geometry->CanCombine( *geometry ) )
		{
			last_geometry->CombineGeometry( geometry->GetGeometryInfo( ) );
			continue;
		}

		// Paint it
		PaintGeometry( *last_geometry );

		// Update the latest geometry
		last_geometry = geometry;
	}

	// Paint the last geometry
	PaintGeometry( *last_geometry );

	mGeometries.Clear( );
}

_ubool GraphicGeometryGroup::Initialize( _GRAPHIC_RENDER_QUEUE render_queue_type )
{
	mRenderQueueType = render_queue_type;

	return _true;
}

_void GraphicGeometryGroup::InsertGeometry( IGraphicSceneView* scene_view, GraphicGeometry* geometry )
{
	_float distance = GetGeometryDistance( scene_view, *geometry );

	InsertGeometry( distance, geometry );
}

_void GraphicGeometryGroup::InsertGeometry( _float distance, GraphicGeometry* geometry )
{
	switch ( mRenderQueueType )
	{
		case _GRAPHIC_RENDER_BACKGROUND:
		case _GRAPHIC_RENDER_OVERLAY:
			mGeometries.Append( GeometryPair( distance, geometry ) );
			break;

		case _GRAPHIC_RENDER_OPAQUE:
			InsertGeometryFromNear2Far( distance, geometry );
			break;

		case _GRAPHIC_RENDER_TRANSPARENT:
			InsertGeometryFromFar2Near( distance, geometry );
			break;

		default:
			break;
	}
}

_void GraphicGeometryGroup::InsertGeometryFromNear2Far( _float distance, GraphicGeometry* geometry )
{
	mGeometries.InsertAscending( GeometryPair( distance, geometry ) );
}

_void GraphicGeometryGroup::InsertGeometryFromFar2Near( _float distance, GraphicGeometry* geometry )
{
	mGeometries.InsertDescending( GeometryPair( distance, geometry ) );
}

_ubool GraphicGeometryGroup::TryCombineWithLastGeometry( IGraphicEffect* effect, IGraphicVertexArray* vao, _dword ibo_start_index, const _byte* vb_data, const _word* ib_data, const GraphicGeometryInfo& geometry_info )
{
	if ( mGeometries.Number( ) == 0 )
		return _false;

	// Get the last geometry info
	GraphicGeometry* last_geometry = mGeometries.GetTailElement( ).mObject2;
	EGE_ASSERT( last_geometry != _null );

	// Try to combine it
	if ( last_geometry->CanCombine( geometry_info, effect, vao->GetResource( ), ibo_start_index ) == _false )
		return _false;

	// Update the vertex buffer and index buffer
	vao->WriteBuffers( geometry_info.mVBSize, vb_data, geometry_info.mIBONumber, ib_data );

	// Combine geometry
	last_geometry->CombineGeometry( geometry_info );

	return _true;
}

_void GraphicGeometryGroup::PaintGeometries( )
{
	switch ( mRenderQueueType )
	{
		case _GRAPHIC_RENDER_BACKGROUND:
		case _GRAPHIC_RENDER_OVERLAY:
			PaintGeometriesInNormalMode( );
			break;

		case _GRAPHIC_RENDER_OPAQUE:
		case _GRAPHIC_RENDER_TRANSPARENT:
			PaintGeometriesInOptimizeMode( );
			break;

		default:
			break;
	}
}