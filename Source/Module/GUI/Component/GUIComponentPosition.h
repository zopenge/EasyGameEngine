//! @file     GUIComponentPosition.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GUIComponentPosition
//----------------------------------------------------------------------------

class GUIComponentPosition : public TGUIComponent< IGUIComponentPosition >
{
public:
	RTTI_CLASS_WITH_ARGUMENTS_DECL( GUIComponentPosition, IGUIComponentPosition, IGUIObject* )

public:
	_GUICOMPONENT_ENABLE_HANDLE_EVENT( )
	_GUICOMPONENT_ENABLE_TEST_REGION( )
	_GUICOMPONENT_ENABLE_EXPORT( )

public:
	typedef TGUIComponent< IGUIComponentPosition > BaseClass;

private:
	//!	The location info
	GUILocationInfo			mVerticalInfo;
	GUILocationInfo			mHorizontalInfo;

	//!	The region
	RectF					mRegion;

	//!	The rotation of X-axis
	_float					mXRadian;
	_float					mAnimationXRotation;
	//!	The rotation of Y-axis
	_float					mYRadian;
	_float					mAnimationYRotation;
	//!	The distance of Z-axis
	_float					mZDistance;
	_float					mAnimationZOffset;
	//! The rotation anchor
	_float					mRotationAnchorZ;
	//! The current cached transform to speed up;
	Matrix4					mCached3DTransform;

	//!	The current transform
	Transform2D				mTransform;
	//!	The current cached transform to speed up
	Matrix3					mCachedTransform;

	//!	The 3D scene info
	GUIRender3DInSceneInfo*	mRenderInSceneInfo;

private:
	//!	Update cached transform.
	inline _void UpdateCachedTransform( );
	inline GUIRender3DInSceneInfo* GetGUIRender3DInSceneInfo( );

private:
	//!	Send GUI messages.
	_void SendHSizeChangedMessage( );
	_void SendVSizeChangedMessage( );

	_void UpdateRegion( );
	_void UpdateCached3DTransform( );

	_ubool UpdateOverlayRenderTransform( IObject* viewport );
	_ubool UpdateScreenBillboardRenderTransform( IObject* viewport );
	_ubool UpdateViewportBillboardRenderTransform( IObject* viewport );
	_ubool UpdateAxialBillboardRenderTransform( IObject* viewport );
	_ubool UpdateRectangleRenderTransform( IObject* viewport );

public:
	GUIComponentPosition( IGUIObject* gui_object );
	virtual ~GUIComponentPosition( );

// IObject Interface
public:
	virtual IObject*				CloneTo( _void* arguments ) const override;

// ISerializable Interface
public:
	virtual _ubool					Import( ISerializableNode* node ) override;
	virtual _ubool					Export( ISerializableNode* node ) const override;

// IGUIComponent Interface
public:
	virtual _ubool					IsResident( ) const override;

	virtual _ubool					HandleEvent( const EventBase& event, const FlagsObject& flags ) override;

	virtual _GUI_TESTPOINT_RESULT_TYPE	PointInControl( const Vector2& position, const Matrix3& transform, Vector2* relative_position ) override;
	virtual _ubool					RegionInControl( const RectF& region, const Matrix3& transform ) override;

// IGUIComponentPosition Interface
public:
	virtual const IGUILocationInfo*	GetVerticalInfo( ) const override;
	virtual const IGUILocationInfo*	GetHorizontalInfo( ) const override;

	//!	Get parent object logic size.
	virtual Vector2					GetParentObjectLogicSize() const override;

	virtual const RectF&			GetRegionF( ) const override;

	virtual _void					SetAnchorType( _GUI_ANCHOR_TYPE horz, _GUI_ANCHOR_TYPE vert ) override;

	virtual _void					SetSizeTypeH( _GUI_SIZE_TYPE type ) override;
	virtual _void					SetSizeTypeV( _GUI_SIZE_TYPE type ) override;

	virtual _void					SetPercentSizeH( _float size ) override;
	virtual _void					SetPercentSizeV( _float size ) override;
	virtual _void					SetPercentSize( const Vector2& size ) override;
	virtual _void					SetLockOnSideSizeH( _float size ) override;
	virtual _void					SetLockOnSideSizeV( _float size ) override;
	virtual _void					SetLockOnSideSize( const Vector2& size ) override;
	virtual _void					SetAnchorPositionH( _float position ) override;
	virtual _void					SetAnchorPositionV( _float position ) override;
	virtual _void					SetAnchorPosition( const Vector2& position ) override;

	virtual _void					SetLogicSizeH( _float size ) override;
	virtual _void					SetLogicSizeV( _float size ) override;
	virtual _void					SetLogicSize( const Vector2& size ) override;
	virtual _void					SetLogicPositionH( _float position ) override;
	virtual _void					SetLogicPositionV( _float position ) override;
	virtual _void					SetLogicPosition( const Vector2& position ) override;
	virtual _void					SetLogicPositionFromRoot( const Vector2& position ) override;
	virtual _void					SetLogicScale( const Vector2& scale ) override;

	virtual Vector2					GetLogicSize( ) const override;
	virtual Vector2					GetAnchorPosition( ) const override;
	virtual Vector2					GetLogicPosition( ) const override;
	virtual Vector2					GetLogicScale( ) const override;

	virtual _void					SetXRadian( _float radian ) override;
	virtual _float					GetXRadian( ) const override;
	virtual _void					SetYRadian( _float radian ) override;
	virtual _float					GetYRadian( ) const override;
	virtual _void					SetZDistance( _float distance ) override;
	virtual _float					GetZDistance( ) const override;
	virtual _void					SetRotationAnchorZ( _float distance ) override;
	virtual _float					GetRotationAnchorZ( ) const override;
	virtual Matrix4					GetRender3DUITransformMatrix( const Matrix4& scaling_matrix ) const override;

	virtual _void					SetScale( const Vector2& scale ) override;
	virtual const Vector2&			GetScale( ) const override;

	virtual _void					SetRadian( _float radian ) override;
	virtual _float					GetRadian( ) const override;

	virtual _void					SetAnimationXYRotation( _float rotation_x, _float rotation_y ) override;
	virtual _void					SetAnimationXRotation( _float radian ) override;
	virtual _float					GetAnimationXRotation( ) const override;
	virtual _void					SetAnimationYRotation( _float radian ) override;
	virtual _float					GetAnimationYRotation( ) const override;

	virtual _void					SetOffset( const Vector2& offset ) override;
	virtual const Vector2&			GetOffset( ) const override;
	virtual _void					SetOffset( const Vector3& offset ) override;
	virtual _void					SetOffsetZ( _float offset ) override;
	virtual _float					GetOffsetZ( ) const override;

	virtual const Matrix3&			GetTransform( ) const override;

	virtual _void					SetTransform2D( const Transform2D& transform ) override;
	virtual const Transform2D&		GetTransform2D( ) const override;

	virtual _void					SetRenderInSceneType( _dword render_type ) override;
	virtual _void					SetRenderInSceneLocalTransform( const Transform3D& offset ) override;
	virtual _void					SetRenderInSceneSize( const Vector2& size ) override;
	virtual _void					SetRenderInSceneAxis( const Vector3& axis ) override;
	virtual _dword					GetRenderInSceneType( ) const override;
	virtual const Transform3D&		GetRenderInSceneLocalTransform( ) const override;
	virtual const Vector2&			GetRenderInSceneSize( ) const override;
	virtual const Vector3&			GetRenderInSceneAxis( ) const override;
	virtual Vector2					GetRenderInSceneScreenPosition( IObject* viewport, _float* zsort ) const override;

	virtual _ubool					UpdateRenderInSceneTransform( IObject* viewport, const Matrix4& trnasform ) override;
	virtual _void					ResetControlRender3DInUIInfo( ) override;
	virtual _void					Relayout() override;
};

//----------------------------------------------------------------------------
// GUIComponentPosition Implementation
//----------------------------------------------------------------------------

_void GUIComponentPosition::UpdateCachedTransform( )
{
	mCachedTransform = mTransform.ToMatrix( GetLogicPosition( ), GetLogicScale( ) );
}

GUIRender3DInSceneInfo* GUIComponentPosition::GetGUIRender3DInSceneInfo( )
{
	if ( mRenderInSceneInfo == _null )
		mRenderInSceneInfo = new GUIRender3DInSceneInfo;

	return mRenderInSceneInfo;
}

}