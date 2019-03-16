//! @file     GraphicGeometryGroup.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicGeometryGroup
//----------------------------------------------------------------------------

class GraphicGeometryGroup
{
private:
	//!	Use the distance to sort.
	typedef Pair< _float, GraphicGeometry* > GeometryPair;
	typedef Array< GeometryPair > GeometryArray;

private:
	//!	The render queue type
	_GRAPHIC_RENDER_QUEUE	mRenderQueueType;

	//!	The geometry chunks
	GeometryArray			mGeometries;

private:
	//!	Set textures sampler state.
	_void SetTexturesSamplerState( const GraphicGeometryInfo& geometry_info );

	//!	Get the distance of geometry.
	_float GetGeometryDistance( IGraphicSceneView* scene_view, const GraphicGeometry& geometry ) const;

	//!	Paint geometry.
	_void PaintGeometry( const GraphicGeometry& geometry );

	//!	Paint geometries
	_void PaintGeometriesInNormalMode( );
	_void PaintGeometriesInOptimizeMode( );

public:
	GraphicGeometryGroup( );
	~GraphicGeometryGroup( );

public:
	//!	Initialize.
	_ubool Initialize( _GRAPHIC_RENDER_QUEUE render_queue_type );

	//!	Insert geometry in auto mode.
	_void InsertGeometry( IGraphicSceneView* scene_view, GraphicGeometry* geometry );
	_void InsertGeometry( _float distance, GraphicGeometry* geometry );
	//!	Insert geometry from near to far.
	_void InsertGeometryFromNear2Far( _float distance, GraphicGeometry* geometry );
	//!	Insert geometry from far to near.
	_void InsertGeometryFromFar2Near( _float distance, GraphicGeometry* geometry );

	//!	Try combine with the last geometry.
	_ubool TryCombineWithLastGeometry( IGraphicEffect* effect, IGraphicVertexArray* vao, _dword ibo_start_index, const _byte* vb_data, const _word* ib_data, const GraphicGeometryInfo& geometry_info );

	//!	Paint geometries one by one.
	_void PaintGeometries( );
};

//----------------------------------------------------------------------------
// GraphicGeometryGroup Implementation
//----------------------------------------------------------------------------

}