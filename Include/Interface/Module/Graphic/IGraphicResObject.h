//! @file     IGraphicResObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicResObject
//----------------------------------------------------------------------------

class IGraphicResObject : public IResObject
{
public:
	//!	Set effect.
	//!	@param		effect	The effect.
	//!	@return		none.
	virtual _void SetEffect( IGraphicEffect* effect ) PURE;
	//!	Get effect.
	//!	@param		none.
	//!	@return		The effect.
	virtual IGraphicEffect* GetEffect( ) const PURE;

	//!	Set color.
	//!	@param		color	The color.
	//!	@return		none.
	virtual _void SetColor( const Color& color ) PURE;
	//!	Get color.
	//!	@param		none.
	//!	@return		The color.
	virtual const Color& GetColor( ) const PURE;

	//!	Set position.
	//!	@param		position	The position.
	//!	@return		none.
	virtual _void SetPosition2D( const Vector2& position ) PURE;
	//!	Get position.
	//!	@param		none.
	//!	@return		The position.
	virtual Vector2 GetPosition2D( ) const PURE;
	//!	Set scale.
	//!	@param		scale	The scale.
	//!	@return		none.
	virtual _void SetScale2D( const Vector2& scale ) PURE;
	//!	Get scale.
	//!	@param		none.
	//!	@return		The scale.
	virtual Vector2 GetScale2D( ) const PURE;
	//!	Set 2D transform.
	//!	@param		transform	The 2D transform.
	//!	@return		none.
	virtual _void SetTransform2D( const Transform2D& transform ) PURE;
	//!	Get 2D transform.
	//!	@param		none.
	//!	@return		The 2D transform.
	virtual Transform2D GetTransform2D( ) const PURE;

	//!	Set transform.
	//!	@param		transform	The transform.
	//!	@return		none.
	virtual _void SetTransform3D( const Transform3D& transform ) PURE;
	//!	Get transform.
	//!	@param		none.
	//!	@return		The transform.
	virtual Transform3D GetTransform3D( ) const PURE;

	//!	Set mesh geometry axis-aligned box.
	//!	@param		box			The axis-aligned box.
	//!	@return		none.
	virtual _void SetAABox( const AxisAlignedBox& box ) PURE;
	//!	Get oriented box.
	//!	@param		none.
	//!	@return		The oriented box.
	virtual OrientedBox2D GetOBBox( ) const PURE;
	//!	Get original oriented box.
	//!	@param		none.
	//!	@return		The oriented box.
	virtual OrientedBox2D GetOriginalOBBox( ) const PURE;
	//!	Get axis-aligned box.
	//!	@param		none.
	//!	@return		The axis-aligned box.
	virtual AxisAlignedBox GetAABox( ) const PURE;
	//!	Get original axis-aligned box.
	//!	@param		none.
	//!	@return		The axis-aligned box.
	virtual AxisAlignedBox GetOriginAABox( ) const PURE;
	//! Get box
	//! @param		none.
	//! @return		The box.
	virtual Box GetBox( ) const PURE;

	//!	Test point.
	//!	@param		camera_transform	The matrix of camera.
	//!	@param		position			The testing position.
	//!	@return		True indicates hit the object.
	virtual _ubool TestPoint( const Matrix3& camera_transform, const Vector2& position ) const PURE;
	//!	Test point.
	//!	@param		position		The testing position.
	//!	@return		True indicates hit the object.
	virtual _ubool TestPoint( const Vector2& position ) const PURE;
	//!	Test region.
	//!	@param		region			The testing region.
	//!	@return		True indicates hit the object.
	virtual _ubool TestRegion( const RectF& region ) const PURE;

	//!	Render as overlay.
	//!	@param		scene			The scene.
	//!	@param		transform		The transform, can be null.
	//!	@param		color			The color, can be null.
	//!	@param		axis_transform	The axis transform.
	//!	@return		none.
	virtual _void RenderOverlay( IGraphicScene* scene, const Matrix3& transform, const Color& color ) PURE;
	//!	Render as screen aligned billboard.
	//!	@param		scene		The scene.
	//!	@param		position	The center position.
	//!	@param		size		The billboard size.
	//!	@param		radian		The billboard rotation radian.
	//!	@param		color		The geometry temporary color.
	//!	@return		none.
	virtual _void RenderScreenAlignedBillboard( IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Color& color ) PURE;
	//!	Render as world oriented billboard.
	//!	@param		scene		The scene.
	//!	@param		position	The center position.
	//!	@param		size		The billboard size.
	//!	@param		radian		The billboard rotation radian.
	//!	@param		color		The geometry color.
	//!	@return		none.
	virtual _void RenderViewpointOrientedBillboard( IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Color& color ) PURE;
	//!	Render as axial billboard.
	//!	@param		scene		The scene.
	//!	@param		position	The center position.
	//!	@param		size		The billboard size.
	//!	@param		axis		The axis direction.
	//!	@param		color		The geometry color.
	//!	@return		none.
	virtual _void RenderAxialBillboard( IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Vector3& axis, const Color& color, const Vector3* result_scaling ) PURE;
	//!	Render as axial billboard.
	//!	@param		scene		The scene.
	//!	@param		position	The center position.
	//!	@param		size		The billboard size.
	//!	@param		normal		The normal direction.
	//!	@param		color		The geometry color.
	//!	@return		none.
	virtual _void RenderRectBillboard( IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Color& color ) PURE;

	virtual _void RenderWireFrame( IGraphicScene* scene, const Matrix4& transform, const Color& color ) PURE;
	virtual _void RenderNormal( IGraphicScene* scene, const Matrix4& transform, const Color& color ) PURE;
	virtual _void RenderAxisAlignedBox( IGraphicScene* scene, const Matrix4& transform, const Color& color ) PURE;
	virtual _void RenderStroke( IGraphicScene* viewport, const Matrix4& transform, const Color& color ) PURE;
	virtual _void RenderZBuffer( IGraphicScene* viewport, const Matrix4& transform ) PURE;
	virtual _void RenderGeometry( IGraphicScene* viewport, const Matrix4& transform, const Color& color ) PURE;
};

}