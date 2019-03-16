//! @file     IGraphicMeshSceneManager.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicMeshSceneRenderer
//----------------------------------------------------------------------------

class IGraphicMeshSceneRenderer : public IFlagsObject< IObject >
{
public:
	//!	The flags
	enum _FLAG
	{
		//!	Enable shadow effect.
		_FLAG_ENABLE_SHADOW	= 1 << 0,
	};

public:
	//!	Begin.
	//!	@param		scene_manager	The mesh scene manager.
	//!	@param		scene			The scene.
	//!	@param		viewport		The viewport.
	//!	@return		none.
	virtual _void Begin( IGraphicMeshSceneManager* scene_manager, IGraphicScene* scene, const Viewport& viewport ) PURE;
	//!	End.
	//!	@param		none.
	//!	@return		none.
	virtual _void End( ) PURE;

	//!	Draw mesh.
	//!	@param		mesh_info		The mesh info pointer.
	//!	@return		none.
	virtual _void DrawMesh( GraphicMeshInfo* mesh_info ) PURE;
};

//----------------------------------------------------------------------------
// IGraphicMeshSceneManager
//----------------------------------------------------------------------------

class IGraphicMeshSceneManager : public IObject
{
public:
	//!	The pick flag
	enum _PICK_FLAG
	{
		_PICK_FLAG_NEAREST_ONLY		= 1 << 0,
		_PICK_FLAG_BOUND_BOX_ONLY	= 1 << 1,
	};

public:
	//!	Enable/Disable options.
	//!	@param		options		The options, @see _GRAPHIC_MESH_SCENE_MANAGER_OPTIONS.
	//!	@param		enable		True indicates enable options, otherwise disable.
	//!	@return		none.
	virtual _void EnableOptions( _dword options, _ubool enable ) PURE;
	//!	Check enable options or not.
	//!	@param		options		The options, @see _GRAPHIC_MESH_SCENE_MANAGER_OPTIONS.
	//!	@return		True indicates these options enabled, otherwise disable.
	virtual _ubool IsEnableOptions( _dword options ) const PURE;

	//!	Set the environment's texture cube.
	//!	@param		texture_cube	The texture cube.
	//!	@return		none.
	virtual _void SetEnvTextureCube( IGraphicTextureCube* texture_cube ) PURE;
	//!	Get the environment's texture cube.
	//!	@param		none.
	//!	@return		The texture cube.
	virtual IGraphicTextureCube* GetEnvTextureCube( ) PURE;

	//!	Present to viewport.
	//!	@param		viewport	The viewport.
	//! @return		none.
	virtual _void Present( IGraphicScene* scene ) PURE;
	//!	Present to canvas.
	//!	@param		scene		The scene.
	//!	@param		viewport	The viewport.
	//! @return		none.
	virtual _void Present( IGraphicScene* scene, const Viewport& viewport ) PURE;
	//!	Present to canvas.
	//!	@param		canvas		The canvas.
	//! @return		none.
	virtual _void Present( IGraphicCanvas* canvas ) PURE;

	//!	Set the renderer.
	//!	@param		renderer	The renderer.
	//!	@return		none.
	virtual _void SetRenderer( IGraphicMeshSceneRenderer* renderer ) PURE;
	//!	Get the renderer.
	//!	@param		none.
	//!	@return		The renderer.
	virtual IGraphicMeshSceneRenderer* GetRenderer( ) const PURE;

	//!	Set the notifier.
	//!	@param		notifier	The notifier.
	//!	@return		none.
	virtual _void SetNotifier( IGraphicMeshSceneManagerNotifier* notifier ) PURE;
	//!	Get the notifier.
	//!	@param		none.
	//!	@return		The notifier.
	virtual IGraphicMeshSceneManagerNotifier* GetNotifier( ) const PURE;

	//!	Set the loader.
	//!	@param		loader		The loader.
	//!	@return		none.
	virtual _void SetLoader( IGraphicMeshSceneManagerLoader* loader ) PURE;
	//!	Get the loader.
	//!	@param		none.
	//!	@return		The loader.
	virtual IGraphicMeshSceneManagerLoader* GetLoader( ) const PURE;

	//!	Get buffer number.
	//!	@param		none.
	//!	@return		The buffer number.
	virtual _dword GetBufferNumber( ) const PURE;
	//!	Get VAO resource.
	//!	@param		buffer_index	The buffer index.
	//!	@return		The VAO interface.
	virtual IGraphicVertexArray* GetVAOByIndex( _dword buffer_index ) const PURE;
	//!	Get vertex declaration.
	//!	@param		buffer_index	The buffer index.
	//!	@return		The vertex declaration interface.
	virtual IGraphicVertexDeclaration* GetVertexDeclByIndex( _dword buffer_index ) const PURE;

	//!	Add mesh geometry.
	//!	@param		mesh_chunk		The geometry mesh chunk.
	//!	@param		effect			The effect.
	//!	@param		transform		The transform what will affect all vertices.
	//!	@return		The mesh geometry interface.
	virtual IGraphicMeshPassRef AddMesh( IGeometryMeshChunk* mesh_chunk, IGraphicEffect* effect, const Matrix4* transform ) PURE;
	//!	Add mesh geometry by existing one in shared way.
	//!	@param		mesh					The geometry mesh what belongs to this scene.
	//!	@param		effect					The effect.
	//!	@param		default_tex_res_names	The default texture resource names.
	//!	@return		The mesh geometry interface.
	virtual IGraphicMeshPassRef AddSharedMesh( IGraphicMesh* mesh, IGraphicEffect* effect, const MultipleTexResNames& default_tex_res_names ) PURE;
	//!	Remove mesh geometry.
	//!	@param		mesh		The mesh geometry.
	//!	@return		True indicates remove successful, otherwise indicates it's not mesh of this scene.
	virtual _ubool RemoveMesh( IGraphicMesh* mesh ) PURE;
	//!	Draw mesh geometry.
	//!	@param		mesh					The mesh geometry.
	//!	@param		viewport				The viewport.
	//!	@param		model_transform			The mesh transform.
	//!	@param		color					The mesh color.
	//!	@param		bone_transform_buffer	The bone transform buffer data.
	//!	@param		bone_transform_size		The bone transform buffer size.
	//!	@param		textures				The textures.
	//! @return		none.
	virtual _void DrawMesh( IGraphicMesh* mesh, IGraphicViewport* viewport, const Matrix4& model_transform, const Color& color, const _byte* bone_transform_buffer, _dword bone_transform_size, Texture2DRHI** textures, TextureCubeRHI* texture_cube, const AxisAlignedBox* aabb ) PURE;

	//!	Lock to get the vertex buffer in read only mode.
	//!	@param		mesh			The mesh geometry.
	//!	@return		The vertex buffer data.
	virtual const _byte* LockVBInReadOnlyMode( IGraphicMesh* mesh ) PURE;
	//!	Unlock to get the vertex buffer in read only mode.
	//!	@param		mesh			The mesh geometry.
	//!	@return		none.
	virtual _void UnlockVBInReadOnlyMode( IGraphicMesh* mesh ) PURE;
	//!	Lock to get the index buffer in read only mode.
	//!	@param		mesh			The mesh geometry.
	//!	@return		The index buffer data.
	virtual const _byte* LockIBInReadOnlyMode( IGraphicMesh* mesh ) PURE;
	//!	Unlock to get the index buffer in read only mode.
	//!	@param		mesh			The mesh geometry.
	//!	@return		none.
	virtual _void UnlockIBInReadOnlyMode( IGraphicMesh* mesh ) PURE;

	//!	Update vertex's position of mesh.
	//!	@param		mesh		The mesh geometry.
	//!	@param		start_index	The start index of vertices.
	//!	@param		positions	The positions.
	//!	@param		number		The number of positions.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool UpdateVertexPosition( IGraphicMesh* mesh, _dword start_index, const Vector3* positions, _dword number ) PURE;
	//!	Update vertex's UV(x) of mesh.
	//!	@param		mesh		The mesh geometry.
	//!	@param		start_index	The start index of vertices.
	//!	@param		uv_list		The uv coordinates list.
	//!	@param		number		The number of positions.
	//!	@param		uv_index	The uv index of multiple textures, start from 0.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool UpdateVertexUV( IGraphicMesh* mesh, _dword start_index, const Vector2* uv_list, _dword number, _dword uv_index ) PURE;

	//!	Intersect mesh by ray.
	//!	@param		mesh		The mesh geometry.
	//!	@param		ray			The ray.
	//!	@param		distance	The distance from ray to nearest triangle.
	//!	@return		True indicates ray hit mesh successful.
	virtual _ubool RayVSMesh( IGraphicMesh* mesh, const Ray& ray, _float* distance = _null ) PURE;

	//!	Pick meshes by ray.
	//!	@param		ray			The pick ray.
	//!	@param		distance	The distance from the picked mesh.
	//!	@param		flags		The pick flags, @see _PICK_FLAG.
	//!	@param		meshes		The picked meshes.
	//!	@return		True indicates pick mesh successful, otherwise indicates nothing be picked.
	virtual _ubool PickMeshes( const Ray& ray, _float& distance, _dword flags, IGraphicMeshRefArray& meshes ) PURE;
	//!	Pick meshes by AABox.
	//!	@param		box			The AABox.
	//!	@param		flags		The pick flags, @see _PICK_FLAG.
	//!	@param		meshes		The picked meshes.
	//!	@return		True indicates pick mesh successful, otherwise indicates nothing be picked.
	virtual _ubool PickMeshes( const AxisAlignedBox& box, _dword flags, IGraphicMeshRefArray& meshes ) PURE;
};

}