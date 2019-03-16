//! @file     GraphicGeometry.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{


//----------------------------------------------------------------------------
// GraphicGeometry
//----------------------------------------------------------------------------

class GraphicGeometry
{
private:
	IGraphicEffectRef		mEffect;

	GraphicMeshGeometryInfo	mGeometryInfo;

public:
	GraphicGeometry( );
	~GraphicGeometry( );

public:
	EGE_GETR_ACCESSOR_CONST( GraphicMeshGeometryInfo, GeometryInfo )
	EGE_GETP_ACCESSOR_CONST( IGraphicEffect, Effect )

public:
	//!	Initialize.
	_void Init( IGraphicEffect* effect, const GraphicMeshGeometryInfo& geometry_info );
	_void Init( IGraphicVertexArray* vao, IGraphicEffect* effect, const GraphicGeometryInfo& geometry_info, _dword ibo_start_index );

	//!	Append texture.
	_void AppendTexture( const AStringObj& name, IGraphicTexture2D* texture );
	_void AppendTexture( const AStringObj& name, Texture2DRHI* texture );

	//!	Check whether can combine with geometry or not.
	_ubool CanCombine( const GraphicGeometry& geometry ) const;
	_ubool CanCombine( const GraphicGeometryInfo& geometry_info, IGraphicEffect* effect, const VertexArrayRHI* vao, _dword ibo_start_index ) const;

	//!	Combine geometry.
	_void CombineGeometry( const GraphicGeometryInfo& geometry_info );

	//!	Get the distance from camera.
	_float GetDistanceFromCamera( const IGraphicSceneView* scene_view ) const;

	//!	Update mesh UBO info.
	_void UpdateMeshUBOs( IGraphicScene* scene );
	//!	Update scene UBO info.
	_void UpdateSceneUBOs( IGraphicScene* scene );

	// Save UBOs.
	_void SaveUBOs( IBufferAllocator* allocator );
};

//----------------------------------------------------------------------------
// GraphicGeometry Implementation
//----------------------------------------------------------------------------

}