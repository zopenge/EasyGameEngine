//! @file     IGUIComponentPosition.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//---------------------------------------------.-------------------------------
// IGUIComponentPosition
//----------------------------------------------------------------------------

class IGUIComponentPosition : public IGUIComponent
{
public:
	CLASS_NAME_DECL( IGUIComponentPosition )

public:
	//!	Get the vertical info interface.
	//!	@param		none.
	//!	@return		The vertical info interface.
	virtual const IGUILocationInfo*	GetVerticalInfo( ) const PURE;
	//!	Get the horizontal info interface.
	//!	@param		none.
	//!	@return		The horizontal info interface.
	virtual const IGUILocationInfo* GetHorizontalInfo( ) const PURE;

	virtual Vector2 GetParentObjectLogicSize() const PURE;

	//!	Get the region.
	virtual const RectF& GetRegionF( ) const PURE;

	//!	Set the anchor type.
	virtual _void SetAnchorType( _GUI_ANCHOR_TYPE horz, _GUI_ANCHOR_TYPE vert ) PURE;

	//!	Set the size type (horz).
	//!	@param		type		The size type.
	//!	@return		none.
	virtual _void SetSizeTypeH( _GUI_SIZE_TYPE type ) PURE;
	//!	Set the size type (vert).
	//!	@param		type		The size type.
	//!	@return		none.
	virtual _void SetSizeTypeV( _GUI_SIZE_TYPE type ) PURE;

	//!	Set the size in percentage (horz).
	//!	@param		size		The size in in percentage.
	//!	@return		none.
	virtual _void SetPercentSizeH( _float size ) PURE;
	//!	Set the size in percentage (vert).
	//!	@param		size		The size in in percentage.
	//!	@return		none.
	virtual _void SetPercentSizeV( _float size ) PURE;
	//!	Set the size in percentage.
	//!	@param		size		The size in in percentage.
	//!	@return		none.
	virtual _void SetPercentSize( const Vector2& size ) PURE;

	virtual _void SetLockOnSideSizeH( _float size ) PURE;
	virtual _void SetLockOnSideSizeV( _float size ) PURE;
	virtual _void SetLockOnSideSize( const Vector2& size ) PURE;
	virtual _void SetAnchorPositionH( _float position ) PURE;
	virtual _void SetAnchorPositionV( _float position ) PURE;
	virtual _void SetAnchorPosition( const Vector2& position ) PURE;

	virtual _void SetLogicSizeH( _float size ) PURE;
	virtual _void SetLogicSizeV( _float size ) PURE;
	virtual _void SetLogicSize( const Vector2& size ) PURE;
	virtual _void SetLogicPositionH( _float position ) PURE;
	virtual _void SetLogicPositionV( _float position ) PURE;
	virtual _void SetLogicPosition( const Vector2& position ) PURE;
	virtual _void SetLogicPositionFromRoot( const Vector2& position ) PURE;
	virtual _void SetLogicScale( const Vector2& scale ) PURE;
				    
	virtual Vector2 GetLogicSize( ) const PURE;
	virtual Vector2 GetAnchorPosition( ) const PURE;
	virtual Vector2 GetLogicPosition( ) const PURE;
	virtual Vector2 GetLogicScale( ) const PURE;

	//!	Set the scale factor.
	//!	@param		scale		The scale factor.
	//!	@return		none.
	virtual _void SetScale( const Vector2& scale ) PURE;
	//!	Get the scale factor.
	//!	@param		none.
	//!	@return		The scale.
	virtual const Vector2& GetScale( ) const PURE;

	//!	Set the rotation radian.
	//!	@param		radian		The rotation radian.
	//!	@return		none.
	virtual _void SetRadian( _float radian ) PURE;
	//!	Get the rotation radian.
	//!	@param		none.
	//!	@return		The rotation radian.
	virtual _float GetRadian( ) const PURE;
	
	// x, y rotation for animation
	virtual _void SetAnimationXYRotation( _float rotation_x, _float rotation_y ) PURE;
	virtual _void SetAnimationXRotation( _float radian ) PURE;
	virtual _float GetAnimationXRotation( ) const PURE;
	virtual _void SetAnimationYRotation( _float radian ) PURE;
	virtual _float GetAnimationYRotation( ) const PURE;


	//!	Set the X-rotation radian.
	//!	@param		radian		The rotation radian.
	//!	@return		none.
	virtual _void SetXRadian( _float radian ) PURE;
	//!	Get the X-rotation radian.
	//!	@param		none.
	//!	@return		The rotation radian.
	virtual _float GetXRadian( ) const PURE;

	//!	Set the Y-rotation radian.
	//!	@param		radian		The rotation radian.
	//!	@return		none.
	virtual _void SetYRadian( _float radian ) PURE;
	//!	Get the Y-rotation radian.
	//!	@param		none.
	//!	@return		The rotation radian.
	virtual _float GetYRadian( ) const PURE;

	//!	Set the Z-Axis distance.
	//!	@param		distance	The distance.
	//!	@return		none.
	virtual _void SetZDistance( _float distance ) PURE;
	//!	Get the Z-Axis distance.
	//!	@param		none.
	//!	@return		The distance.
	virtual _float GetZDistance( ) const PURE;
	virtual _void SetRotationAnchorZ( _float distance ) PURE;
	virtual _float GetRotationAnchorZ( ) const PURE;
	virtual Matrix4 GetRender3DUITransformMatrix( const Matrix4& scaling_matrix ) const PURE;

	//!	Set the object relative position.
	//!	@param		position	The relative position.
	//!	@param		type		The origin position type.
	//!	@return		none.
	virtual _void SetOffset( const Vector2& offset ) PURE;
	//!	Get the object relative center position.
	//!	@param		type		The origin position type.
	//!	@return		The relative center position.
	virtual const Vector2& GetOffset( ) const PURE;
	virtual _void SetOffset( const Vector3& offset ) PURE;
	virtual _void SetOffsetZ( _float offset ) PURE;
	virtual _float GetOffsetZ( ) const PURE;

	//!	Get the object relative transform.
	//!	@param		none.
	//!	@return		The relative transform.
	virtual const Matrix3& GetTransform( ) const PURE;

	//!	Set the object relative transform.
	//!	@param		transform	The relative transform.
	//!	@return		none.
	virtual _void SetTransform2D( const Transform2D& transform ) PURE;
	//!	Get the object relative transform.
	//!	@param		none.
	//!	@return		The relative transform.
	virtual const Transform2D& GetTransform2D( ) const PURE;

	virtual _void SetRenderInSceneType( _dword render_type ) PURE;
	virtual _void SetRenderInSceneLocalTransform( const Transform3D& offset ) PURE;
	virtual _void SetRenderInSceneSize( const Vector2& size ) PURE;
	virtual _void SetRenderInSceneAxis( const Vector3& axis ) PURE;
	virtual _dword GetRenderInSceneType( ) const PURE;
	virtual const Transform3D& GetRenderInSceneLocalTransform( ) const PURE;
	virtual const Vector2& GetRenderInSceneSize( ) const PURE;
	virtual const Vector3& GetRenderInSceneAxis( ) const PURE;
	virtual Vector2 GetRenderInSceneScreenPosition( IObject* viewport, _float* zsort ) const PURE;
	virtual _ubool UpdateRenderInSceneTransform( IObject* viewport, const Matrix4& trnasform ) PURE;
	virtual _void ResetControlRender3DInUIInfo( ) PURE;
	virtual _void Relayout() PURE;
};

}