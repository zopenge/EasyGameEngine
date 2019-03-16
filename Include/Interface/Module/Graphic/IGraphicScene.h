//! @file     IGraphicScene.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicScene
//----------------------------------------------------------------------------

class IGraphicScene : public IGraphicDrawer
{
public:
	//!	Set the viewport.
	//!	@param		viewport		The viewport.
	//!	@return		none.
	virtual _void SetViewport( const Viewport& viewport ) PURE;
	//!	Get the viewport.
	//!	@param		none.
	//!	@return		The viewport.
	virtual const Viewport& GetViewport( ) const PURE;

	//!	Set the client size.
	//!	@param		size		The client size.
	//!	@return		none.
	virtual _void SetClientSize( const PointU& size ) PURE;
	//!	Get the client size.
	//!	@param		none.
	//!	@return		The client size.
	virtual const PointU& GetClientSize( ) const PURE;
	//!	Get the ratio of client size.
	//!	@param		none.
	//!	@return		The ratio of client size.
	virtual const Ratio& GetClientRatio( ) const PURE;

	//!	Flush buffers.
	//!	@param		none.
	//!	@return		none.
	virtual _void FlushBuffers( ) PURE;

	//!	Clear caches.
	//!	@param		none.
	//!	@return		none.
	virtual _void ClearCaches( ) PURE;

	//!	Get the view transform (right-hand).
	//!	@remark		You should call this interface between begin and end procession.
	//!	@param		none.
	//!	@return		The transform.
	virtual const Matrix4& GetViewTransform( ) const PURE;
	//!	Get the view + projection transform (right-hand).
	//!	@remark		You should call this interface between begin and end procession.
	//!	@param		none.
	//!	@return		The transform.
	virtual const Matrix4& GetVPTransform( ) const PURE;

	//!	Clear render buffers.
	//!	@param		clearcolor		True indicates clear the color-buffer.
	//!	@param		color			The clear color.
	//!	@param		cleardepth		True indicates clear the depth-buffer.
	//!	@param		depth			The clear depth.
	//!	@param		clearstencil	True indicates clear the stencil-buffer.
	//!	@param		stencil			The clear stencil.
	//! @return		none.
	virtual _void ClearRenderBuffers( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil ) PURE;
	//!	Present the render buffers.
	//!	@param		none.
	//!	@return		none.
	virtual _void PresentRenderBuffers( ) PURE;
	//!	Present the render buffers to canvas.
	//!	@param		canvas			The canvas.
	//!	@return		none.
	virtual _void PresentRenderBuffers( IGraphicCanvas* canvas ) PURE;

	//!	Set the scene view.
	//!	@param		view	The scene view.
	//! @return		none.
	virtual _void SetSceneView( IGraphicSceneView* view ) PURE;
	//!	Get the scene view.
	//!	@param		none.
	//!	@return		The scene view.
	virtual IGraphicSceneView* GetSceneView( ) const PURE;

	//!	Get the last viewport.
	//!	@param		none.
	//!	@return		The unique address of viewport.
	virtual const Viewport* GetLastViewport( ) PURE;

	//!	Pick meshes by ray.
	//!	@param		ray				The pick ray.
	//!	@param		bound_box_only	True indicates pick by bound box only, much faster but less precision.
	//!	@param		meshes			The picked meshes from near to far.
	//!	@return		True indicates pick mesh successful, otherwise indicates nothing be picked.
	virtual _ubool PickMeshes( const Ray& ray, _ubool bound_box_only, IGraphicMeshRefArray& meshes ) PURE;
	//!	Pick meshes by AABox.
	//!	@param		box				The AABox.
	//!	@param		bound_box_only	True indicates pick by bound box only, much faster but less precision.
	//!	@param		meshes			The picked meshes from near to far.
	//!	@return		True indicates pick mesh successful, otherwise indicates nothing be picked.
	virtual _ubool PickMeshes( const AxisAlignedBox& box, _ubool bound_box_only, IGraphicMeshRefArray& meshes ) PURE;

	//!	Add mesh.
	//!	@param		mesh_chunk		The mesh chunk info.
	//!	@return		The mesh geometry interface.
	virtual IGraphicMeshPassRef AddMesh( IGeometryMeshChunk* mesh_chunk ) PURE;

	//!	Get the position of a 3d point on screen
	//!	@param		point		The 3d point.
	//!	@return		The position on screen.
	virtual Vector2 Convert3DTo2D( const Vector3& point, _float* zsort ) PURE;
	//!	Get the position of a 3d point on screen
	//!	@param		size		The viewport size.
	//!	@param		point		The 3d point.
	//!	@param		zsort		The zsort distance.
	//!	@return		The position on screen.
	virtual Vector2 Convert3DTo2D( const PointU& size, const Vector3& point, _float* zsort ) PURE;

	//! Get the pick ray
	//! @param		point		The screen point.
	//! @return		The pick ray.
	virtual Ray GetPickRay( _int x, _int y ) PURE;
	//! Get the pick ray
	//!	@param		size		The viewport size.
	//! @param		x			The x position.
	//! @param		y			The y position.
	//! @return		The pick ray.
	virtual Ray GetPickRay( const PointU& size, _int x, _int y ) PURE;
};

}