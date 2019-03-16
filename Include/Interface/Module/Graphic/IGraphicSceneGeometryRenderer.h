//! @file     IGraphicSceneGeometryRenderer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicSceneGeometryRenderer
//----------------------------------------------------------------------------

class IGraphicSceneGeometryRenderer : public IObject
{
public:
	//!	Flush render commands.
	//!	@param		none.
	//!	@return		none.
	virtual _void Flush( ) PURE;

	//!	Render geometry.
	//!	@remark		No copy any buffer into internal components, make sure your geometry's VAO is ready.
	//!	@param		vertex_buffer	The vertex buffer data.
	//!	@param		index_buffer	The index buffer data.
	//!	@param		geometry		The geometry info.
	//!	@return		none.
	virtual _void RenderGeometry( const _byte* vertex_buffer, const _word* index_buffer, const RenderableGeometry& geometry ) PURE;
	//!	Render mesh geometry.
	//!	@param		mesh					The mesh geometry.
	//!	@param		viewport				The viewport.
	//!	@param		model_transform			The mesh transform.
	//!	@param		color					The mesh color.
	//!	@param		bone_transform_buffer	The bone transform buffer data.
	//!	@param		bone_transform_size		The bone transform buffer size.
	//!	@param		textures				The textures.
	//!	@param		texture_cube			The texture cube.
	//!	@param		aabb					The axis aligned box of mesh.
	//! @return		none.
	virtual _void RenderMeshGeometry( IGraphicMesh* mesh, IGraphicViewport* viewport, const Matrix4& model_transform, const Color& color, const _byte* bone_transform_buffer, _dword bone_transform_size, Texture2DRHI** textures, TextureCubeRHI* texture_cube, const AxisAlignedBox* aabb ) PURE;
	//!	Append geometry to tail.
	//!	@remark		No copy any buffer into internal components, make sure your geometry's VAO is ready.
	//!	@param		geometry		The geometry info.
	//!	@return		none.
	virtual _void AppendGeometry( const RenderableGeometry& geometry ) PURE;
};

}