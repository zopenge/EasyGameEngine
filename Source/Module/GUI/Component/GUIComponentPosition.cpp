//! @file     GUIComponentPosition.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIComponentPosition Implementation
//----------------------------------------------------------------------------

GUIComponentPosition::GUIComponentPosition( IGUIObject* gui_object ) : BaseClass( gui_object )
{
	mRegion				= RectF::cNull;

	mXRadian			= 0.0f;
	mAnimationXRotation	= 0.0f;
	mYRadian			= 0.0f;
	mAnimationYRotation	= 0.0f;
	mZDistance			= 0.0f;
	mAnimationZOffset	= 0.0f;
	mRotationAnchorZ	= 0.0f;

	mTransform			= Transform2D::cZero;
	mCachedTransform	= Matrix3::cIdentity;
	mCached3DTransform	= Matrix4::cIdentity;

	mRenderInSceneInfo	= _null;
}

GUIComponentPosition::~GUIComponentPosition( )
{
	EGE_DELETE( mRenderInSceneInfo );
}

Vector2 GUIComponentPosition::GetParentObjectLogicSize( ) const
{
	IGUIObject* parent = mGUIObject->ParentObject( );
	if ( parent != _null )
		return parent->GetComponentPosition( )->GetLogicSize( );

	return gGUIModule->GetRootApplication( )->GetComponentPosition( )->GetLogicSize( );
}

_void GUIComponentPosition::SendHSizeChangedMessage( )
{
	UpdateRegion( );

	GUIEventParentHSizeChanged parentchangedevent;
	parentchangedevent.mSize = mHorizontalInfo.GetLogicSize( );
	for ( IGUIObject* child_object = mGUIObject->FirstChildObject( ); child_object != _null; child_object = child_object->NextObject( ) )
		child_object->HandleEvent( parentchangedevent, FlagsObject( ) );

	GUIEventHSizeChanged selfevent;
	selfevent.mSize = mHorizontalInfo.GetLockSize( );
	mGUIObject->HandleEvent( selfevent, FlagsObject( ) );
}

_void GUIComponentPosition::SendVSizeChangedMessage( )
{
	UpdateRegion( );

	GUIEventParentVSizeChanged parentchangedevent;
	parentchangedevent.mSize = mVerticalInfo.GetLogicSize( );
	for ( IGUIObject* child_object = mGUIObject->FirstChildObject( ); child_object != _null; child_object = child_object->NextObject( ) )
		child_object->HandleEvent( parentchangedevent, FlagsObject( ) );

	GUIEventVSizeChanged selfevent;
	selfevent.mSize = mVerticalInfo.GetLockSize( );
	mGUIObject->HandleEvent( selfevent, FlagsObject( ) );
}

IObject* GUIComponentPosition::CloneTo( _void* arguments ) const
{
	IGUIObject* gui_object = (IGUIObject*)arguments;
	EGE_ASSERT( gui_object != _null );

	GUIComponentPosition* component = new GUIComponentPosition( gui_object );
	component->CopyFrom( this );
	component->mAnimationXRotation	= mAnimationXRotation;
	component->mAnimationYRotation	= mAnimationYRotation;
	component->mAnimationZOffset	= mAnimationZOffset;
	component->mXRadian				= mXRadian;
	component->mYRadian				= mYRadian;
	component->mZDistance			= mZDistance;
	component->mRotationAnchorZ		= mRotationAnchorZ;
	component->mTransform			= mTransform;
	component->mCachedTransform		= mCachedTransform;
	component->mCached3DTransform	= mCached3DTransform;
	component->mVerticalInfo.CopyFrom( mVerticalInfo );
	component->mHorizontalInfo.CopyFrom( mHorizontalInfo );

	component->UpdateRegion( );

	return component;
}

_ubool GUIComponentPosition::Import( ISerializableNode* node )
{
	if ( node == _null )
		return _false;

	_float x_degree = 0.0f;
	node->Read( L"x_degree", x_degree );
	mXRadian = Math::Degree2Radian( x_degree );

	_float y_degree = 0.0f;
	node->Read( L"y_degree", y_degree );
	mYRadian = Math::Degree2Radian( y_degree );

	node->Read( L"z_distance", mZDistance );
	node->Read( L"rotation_anchorz", mRotationAnchorZ );

	UpdateCached3DTransform( );

	Vector2 parentsize = GetParentObjectLogicSize( );

	ISerializableNodeRef hor_node = node->GetChildNodeByName( L"hor" );
	if ( mHorizontalInfo.Import( hor_node ) == _false )
		return _false;

	mHorizontalInfo.UpdateLogicSize( parentsize.x );
	mHorizontalInfo.UpdateLogicPosition( parentsize.x );
	SendHSizeChangedMessage( );

	ISerializableNodeRef ver_node = node->GetChildNodeByName( L"ver" );
	if ( mVerticalInfo.Import( ver_node ) == _false )
		return _false;

	mVerticalInfo.UpdateLogicSize( parentsize.y );
	mVerticalInfo.UpdateLogicPosition( parentsize.y );
	SendVSizeChangedMessage( );

	UpdateCachedTransform( );

	return _true;
}

_ubool GUIComponentPosition::Export( ISerializableNode* node ) const
{
	if ( node == _null )
		return _false;

	if ( node->Write( L"x_degree", Math::Radian2Degree( mXRadian ) ) == _false )
		return _false;
	if ( node->Write( L"y_degree", Math::Radian2Degree( mYRadian ) ) == _false )
		return _false;
	if ( node->Write( L"z_distance", mZDistance ) == _false )
		return _false;
	if ( node->Write( L"rotation_anchorz", mRotationAnchorZ ) == _false )
		return _false;

	ISerializableNodeRef child_node = node->InsertChildNode( L"hor", L"", _false );
	if ( mHorizontalInfo.Export( child_node ) == _false )
		return _false;

	child_node = node->InsertChildNode( L"ver", L"", _false );
	if ( mVerticalInfo.Export( child_node ) == _false )
		return _false;

	return _true;
}

_ubool GUIComponentPosition::IsResident( ) const
{
	return _true;
}

_GUI_TESTPOINT_RESULT_TYPE GUIComponentPosition::PointInControl( const Vector2& position, const Matrix3& transform, Vector2* relative_position )
{
	// Get the positions
	Vector2 lt_pos( mRegion.l, mRegion.t );
	Vector2 rb_pos( mRegion.r, mRegion.b );
	lt_pos *= transform;
	rb_pos *= transform;

	// Get the region
	Vector2 fixed_lt_pos( Math::Min( lt_pos.x, rb_pos.x ), Math::Min( lt_pos.y, rb_pos.y ) );
	Vector2 fixed_rb_pos( Math::Max( lt_pos.x, rb_pos.x ), Math::Max( lt_pos.y, rb_pos.y ) );

	// Test region
	if ( position.x > fixed_rb_pos.x || position.x < fixed_lt_pos.x )
		return _GTRT_OUT;
	if ( position.y > fixed_rb_pos.y || position.y < fixed_lt_pos.y )
		return _GTRT_OUT;

	if ( relative_position != _null )
		*relative_position = position - transform.GetTranslationVector( );

	return _GTRT_IN;
}

_ubool GUIComponentPosition::RegionInControl( const RectF& region, const Matrix3& transform )
{
	// Get the positions
	Vector2 lt_pos( mRegion.l, mRegion.t );
	Vector2 rb_pos( mRegion.r, mRegion.b );
	lt_pos *= transform;
	rb_pos *= transform;

	// Get the region
	Vector2 fixed_lt_pos( Math::Min( lt_pos.x, rb_pos.x ), Math::Min( lt_pos.y, rb_pos.y ) );
	Vector2 fixed_rb_pos( Math::Max( lt_pos.x, rb_pos.x ), Math::Max( lt_pos.y, rb_pos.y ) );

	// Test region
	if ( region.l > fixed_rb_pos.x || region.r < fixed_lt_pos.x )
		return _false;
	if ( region.t > fixed_rb_pos.y || region.b < fixed_lt_pos.y )
		return _false;

	return _true;
}

_ubool GUIComponentPosition::HandleEvent( const EventBase& event, const FlagsObject& flags )
{
	switch ( event.mEventID )
	{
	case _GUI_EVENT_PERENT_HSIZE_CHANGED:
		{
			const GUIEventParentHSizeChanged& sizeevent = (const GUIEventParentHSizeChanged&) event;
			mHorizontalInfo.UpdateLogicSize( sizeevent.mSize );
			mHorizontalInfo.UpdateLogicPosition( sizeevent.mSize );
			SendHSizeChangedMessage( );

			UpdateCachedTransform( );
		}
		break;

	case _GUI_EVENT_PERENT_VSIZE_CHANGED:
		{
			const GUIEventParentVSizeChanged& sizeevent = (const GUIEventParentVSizeChanged&) event;
			mVerticalInfo.UpdateLogicSize( sizeevent.mSize );
			mVerticalInfo.UpdateLogicPosition( sizeevent.mSize );
			SendVSizeChangedMessage( );

			UpdateCachedTransform( );
		}
		break;
	}

	return _false;
}

const IGUILocationInfo* GUIComponentPosition::GetVerticalInfo( ) const 
{
	return &mVerticalInfo;
}

const IGUILocationInfo* GUIComponentPosition::GetHorizontalInfo( ) const 
{
	return &mHorizontalInfo;
}

const RectF& GUIComponentPosition::GetRegionF( ) const
{
	return mRegion;
}

_void GUIComponentPosition::SetAnchorType( _GUI_ANCHOR_TYPE horz, _GUI_ANCHOR_TYPE vert )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	mHorizontalInfo.SetAnchorType( horz, parent_size.x );
	mVerticalInfo.SetAnchorType( vert, parent_size.y );

	UpdateCachedTransform( );
}

_void GUIComponentPosition::SetSizeTypeH( _GUI_SIZE_TYPE type )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	mHorizontalInfo.SetSizeType( type, parent_size.x );

	SendHSizeChangedMessage( );
}

_void GUIComponentPosition::SetSizeTypeV( _GUI_SIZE_TYPE type )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	mVerticalInfo.SetSizeType( type, parent_size.y );

	SendVSizeChangedMessage( );
}

_void GUIComponentPosition::SetLogicSizeH( _float size )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	if ( mHorizontalInfo.SetLogicSize( size, parent_size.x ) )
		SendHSizeChangedMessage( );

	UpdateCachedTransform( );
}

_void GUIComponentPosition::SetLogicSizeV( _float size )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	if ( mVerticalInfo.SetLogicSize( size, parent_size.y ) )
		SendVSizeChangedMessage( );

	UpdateCachedTransform( );
}

_void GUIComponentPosition::SetLogicSize( const Vector2& size )
{
	SetLogicSizeH( size.x );
	SetLogicSizeV( size.y );
}

_void GUIComponentPosition::SetPercentSizeH( _float size )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	if ( mHorizontalInfo.SetPercentSize( size, parent_size.x ) )
		SendHSizeChangedMessage( );

	UpdateCachedTransform( );
}

_void GUIComponentPosition::SetPercentSizeV( _float size )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	if ( mVerticalInfo.SetPercentSize( size, parent_size.y ) )
		SendVSizeChangedMessage( );

	UpdateCachedTransform( );
}

_void GUIComponentPosition::SetPercentSize( const Vector2& size )
{
	SetPercentSizeH( size.x );
	SetPercentSizeV( size.y );
}

_void GUIComponentPosition::SetLockOnSideSizeH( _float size )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	if ( mHorizontalInfo.SetLockSize( size, parent_size.x ) )
	{
		SendHSizeChangedMessage( );
		UpdateCachedTransform( );
	}
}

_void GUIComponentPosition::SetLockOnSideSizeV( _float size )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	if ( mVerticalInfo.SetLockSize( size, parent_size.y ) )
	{
		SendVSizeChangedMessage( );
		UpdateCachedTransform( );
	}
}

_void GUIComponentPosition::SetLockOnSideSize( const Vector2& size )
{
	SetLockOnSideSizeH( size.x );
	SetLockOnSideSizeV( size.y );
}

_void GUIComponentPosition::SetAnchorPositionH( _float position )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	if ( mHorizontalInfo.SetAnchorPosition( position, parent_size.x ) )
		SendHSizeChangedMessage( );

	UpdateCachedTransform( );
}

_void GUIComponentPosition::SetAnchorPositionV( _float position )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	if ( mVerticalInfo.SetAnchorPosition( position, parent_size.y ) )
		SendVSizeChangedMessage( );

	UpdateCachedTransform( );
}

_void GUIComponentPosition::SetAnchorPosition( const Vector2& position )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	if ( mHorizontalInfo.SetAnchorPosition( position.x, parent_size.x ) )
		SendHSizeChangedMessage( );
	if ( mVerticalInfo.SetAnchorPosition( position.y, parent_size.y ) )
		SendVSizeChangedMessage( );

	UpdateCachedTransform( );
}

_void GUIComponentPosition::SetLogicPositionH( _float position )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	if ( mHorizontalInfo.SetLogicPosition( position, parent_size.x ) )
		SendHSizeChangedMessage( );

	UpdateCachedTransform( );
}

_void GUIComponentPosition::SetLogicPositionV( _float position )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	if ( mVerticalInfo.SetLogicPosition( position, parent_size.y ) )
		SendVSizeChangedMessage( );

	UpdateCachedTransform( );
}

_void GUIComponentPosition::SetLogicPosition( const Vector2& position )
{
	Vector2 parent_size = GetParentObjectLogicSize( );

	if ( mHorizontalInfo.SetLogicPosition( position.x, parent_size.x ) )
		SendHSizeChangedMessage( );
	if ( mVerticalInfo.SetLogicPosition( position.y, parent_size.y ) )
		SendVSizeChangedMessage( );

	UpdateCachedTransform( );
}

_void GUIComponentPosition::SetLogicPositionFromRoot( const Vector2& position )
{
	if ( mGUIObject->ParentObject( ) == _null )
	{
		SetLogicPosition( position );
		return;
	}
	Matrix3 parent_matrix = mGUIObject->ParentObject( )->GetChildWorldTransform( );
	Vector2 p = position * parent_matrix.Inverse( );
	SetLogicPosition( p );
}

_void GUIComponentPosition::SetLogicScale( const Vector2& scale )
{
	mHorizontalInfo.SetLogicScale( scale.x );
	mVerticalInfo.SetLogicScale( scale.y );
	UpdateCachedTransform( );
}

Vector2 GUIComponentPosition::GetLogicSize( ) const
{
	return Vector2( mHorizontalInfo.GetLogicSize( ), mVerticalInfo.GetLogicSize( ) );
}

Vector2 GUIComponentPosition::GetAnchorPosition( ) const
{
	return Vector2( mHorizontalInfo.GetAnchorPosition( ), mVerticalInfo.GetAnchorPosition( ) );
}

Vector2 GUIComponentPosition::GetLogicPosition( ) const
{
	return Vector2( mHorizontalInfo.GetLogicPosition( ), mVerticalInfo.GetLogicPosition( ) );
}

Vector2 GUIComponentPosition::GetLogicScale( ) const
{
	return Vector2( mHorizontalInfo.GetLogicScale( ), mVerticalInfo.GetLogicScale( ) );
}

_void GUIComponentPosition::SetScale( const Vector2& scale )
{
	mTransform.mScale = scale;

	UpdateCachedTransform( );
}

const Vector2& GUIComponentPosition::GetScale( ) const
{
	return mTransform.mScale;
}

_void GUIComponentPosition::SetRadian( _float radian )
{
	mTransform.mRadian = radian;

	UpdateCachedTransform( );
}

_float GUIComponentPosition::GetRadian( ) const
{
	return mTransform.mRadian;
}

_void GUIComponentPosition::SetAnimationXRotation( _float radian )
{
	mAnimationXRotation = radian;
	UpdateCached3DTransform( );
}

_float GUIComponentPosition::GetAnimationXRotation( ) const
{
	return mAnimationXRotation;
}

_void GUIComponentPosition::SetAnimationYRotation( _float radian )
{
	mAnimationYRotation = radian;
	UpdateCached3DTransform( );
}

_float GUIComponentPosition::GetAnimationYRotation( ) const
{
	return mAnimationYRotation;
}

_void GUIComponentPosition::SetAnimationXYRotation( _float rotation_x, _float rotation_y )
{
	mAnimationXRotation = rotation_x;
	mAnimationYRotation = rotation_y;
	UpdateCached3DTransform( );
}

_void GUIComponentPosition::SetXRadian( _float radian )
{
	mXRadian = radian;
	UpdateCached3DTransform( );
}

_float GUIComponentPosition::GetXRadian( ) const
{
	return mXRadian;
}

_void GUIComponentPosition::SetYRadian( _float radian )
{
	mYRadian = radian;
	UpdateCached3DTransform( );
}

_float GUIComponentPosition::GetYRadian( ) const
{
	return mYRadian;
}

_void GUIComponentPosition::SetZDistance( _float distance )
{
	mZDistance = distance;
}

_float GUIComponentPosition::GetZDistance( ) const
{
	return mZDistance;
}

_void GUIComponentPosition::SetRotationAnchorZ( _float distance )
{
	mRotationAnchorZ = distance;
	UpdateCached3DTransform( );
}

_float GUIComponentPosition::GetRotationAnchorZ( ) const
{
	return mRotationAnchorZ;
}

Matrix4 GUIComponentPosition::GetRender3DUITransformMatrix( const Matrix4& scaling_matrix ) const
{
	Matrix4 matrix = Matrix4( ).Translation( Vector3( 0.0f, 0.0f, mRotationAnchorZ ) * scaling_matrix );
	matrix *= mCached3DTransform;
	matrix *= Matrix4( ).Translation( Vector3( 0.0f, 0.0f, mZDistance + mAnimationZOffset - mRotationAnchorZ ) * scaling_matrix );
	return matrix;
}

_void GUIComponentPosition::UpdateRegion( )
{
	Vector2 halfsize	= GetLogicSize( ) * 0.5f;
	mRegion.l			= -halfsize.x;
	mRegion.t			= -halfsize.y;
	mRegion.r			= halfsize.x;
	mRegion.b			= halfsize.y;
}

_void GUIComponentPosition::UpdateCached3DTransform( )
{
	mCached3DTransform = Matrix4( ).RotationX( mXRadian + mAnimationXRotation ) * Matrix4( ).RotationY( mYRadian + mAnimationYRotation );
}

_void GUIComponentPosition::SetOffset( const Vector2& position )
{
	mTransform.mPosition = position;

	UpdateCachedTransform( );
}

const Vector2& GUIComponentPosition::GetOffset( ) const
{
	return mTransform.mPosition;
}

_void GUIComponentPosition::SetOffset( const Vector3& offset )
{
	mTransform.mPosition.x = offset.x;
	mTransform.mPosition.y = offset.y;

	UpdateCachedTransform( );

	SetOffsetZ( offset.z );
}

_void GUIComponentPosition::SetOffsetZ( _float offset )
{
	mAnimationZOffset = offset;
}

_float GUIComponentPosition::GetOffsetZ( ) const
{
	return mAnimationZOffset;
}

const Matrix3& GUIComponentPosition::GetTransform( ) const
{
	return mCachedTransform;
}

_void GUIComponentPosition::SetTransform2D( const Transform2D& transform )
{
	mTransform = transform;

	UpdateCachedTransform( );
}

const Transform2D& GUIComponentPosition::GetTransform2D( ) const
{
	return mTransform;
}

_void GUIComponentPosition::SetRenderInSceneType( _dword render_type )
{
	GetGUIRender3DInSceneInfo( )->mRenderType = render_type;
}

_void GUIComponentPosition::SetRenderInSceneLocalTransform( const Transform3D& offset )
{
	GetGUIRender3DInSceneInfo( )->mLocalTransform = offset;
}

_void GUIComponentPosition::SetRenderInSceneSize( const Vector2& size )
{
	GetGUIRender3DInSceneInfo( )->mSize = size;
}

_void GUIComponentPosition::SetRenderInSceneAxis( const Vector3& axis )
{
	GetGUIRender3DInSceneInfo( )->mAxis = axis;
}

_dword GUIComponentPosition::GetRenderInSceneType( ) const
{
	if ( mRenderInSceneInfo == _null )
		return _GRIST_OVERLAY;
	return mRenderInSceneInfo->mRenderType;
}

const Transform3D& GUIComponentPosition::GetRenderInSceneLocalTransform( ) const
{
	if ( mRenderInSceneInfo == _null )
		return Transform3D::cZero;
	return mRenderInSceneInfo->mLocalTransform;
}

const Vector2& GUIComponentPosition::GetRenderInSceneSize( ) const
{
	if ( mRenderInSceneInfo == _null )
		return Vector2::cIdentity;
	return mRenderInSceneInfo->mSize;
}

const Vector3& GUIComponentPosition::GetRenderInSceneAxis( ) const
{
	if ( mRenderInSceneInfo == _null )
		return Vector3::cZAxis;
	return mRenderInSceneInfo->mAxis;
}

_ubool GUIComponentPosition::UpdateRenderInSceneTransform( IObject* viewport, const Matrix4& transform )
{
	GUIRender3DInSceneInfo* info = GetGUIRender3DInSceneInfo( );
	info->mRenderTransform = transform;
	
	switch ( info->mRenderType )
	{
	case _GRIST_OVERLAY:
		{
			return UpdateOverlayRenderTransform( viewport );
		}
		break;
	case _GRIST_SCREEN_BILLBOARD:
		{
			return UpdateScreenBillboardRenderTransform( viewport );
		}
		break;
	case _GRIST_VIEWPORT_BILLBOARD:
		{
			return UpdateViewportBillboardRenderTransform( viewport );
		}
		break;
	case _GRIST_AXIAL_BILLBOARD:
		{
			return UpdateAxialBillboardRenderTransform( viewport );
		}
		break;
	case _GRIST_RECTANGLE:
		{
			return UpdateRectangleRenderTransform( viewport );
		}
		break;
	}

	return _false;
}

_ubool GUIComponentPosition::UpdateScreenBillboardRenderTransform( IObject* viewport )
{
	Vector2 logic_size = GetLogicSize( );
	logic_size.x = logic_size.x == 0.0f ? 0.0f : 1.0f / logic_size.x;
	logic_size.y = logic_size.y == 0.0f ? 0.0f : 1.0f / logic_size.y;

	GUIRender3DInSceneInfo* info = GetGUIRender3DInSceneInfo( );
	Vector3 position = info->mLocalTransform.mTranslate * info->mRenderTransform;
	Matrix3 mat3 = Matrix3::CreateScaling( info->mSize.x * logic_size.x, -info->mSize.y * logic_size.y, 0.0f );

	Matrix4 view_transform = GetGUIModule( )->GetProcessor( )->OnGetViewMatrix( viewport );
	Vector3 up_axis = view_transform.GetUpVector( );
	Vector3 right_axis = view_transform.GetRightVector( );

	mat3 *= Matrix3( ).FromRotation( Quaternion( ).Rotation( Vector3::cXAxis, Vector3::cYAxis, right_axis, up_axis ) );
	info->mFinalTransform = Matrix4( ).FromTranslationRotation( Vector3::cOrigin, mat3 );
	info->mFinalTransform *= Matrix4( ).Translation( position );
	info->mFinalTransform *= GetGUIModule( )->GetProcessor( )->OnGetViewProjectionMatrix( viewport );

	info->mZSort = ( Vector3::cOrigin * info->mFinalTransform ).z;
	GetGUIModule( )->AddPreRenderInSceneGUIObject( mGUIObject, info->mFinalTransform, info->mZSort );
	return _true;
}

_ubool GUIComponentPosition::UpdateViewportBillboardRenderTransform( IObject* viewport )
{
	Vector2 logic_size = GetLogicSize( );
	logic_size.x = logic_size.x == 0.0f ? 0.0f : 1.0f / logic_size.x;
	logic_size.y = logic_size.y == 0.0f ? 0.0f : 1.0f / logic_size.y;

	GUIRender3DInSceneInfo* info = GetGUIRender3DInSceneInfo( );
	Vector3 position = info->mLocalTransform.mTranslate * info->mRenderTransform;
	Matrix3 mat3 = Matrix3::CreateScaling( info->mSize.x * logic_size.x, -info->mSize.y * logic_size.y, 0.0f );

	Matrix4 view_transform = GetGUIModule( )->GetProcessor( )->OnGetViewMatrix( viewport );
	Matrix4 view_inverse = Matrix4( view_transform ).Inverse( );
	Vector3 up_axis = view_transform.GetUpVector( );
	Vector3 look_axis = view_inverse.GetTranslationVector( ) - position;
	Vector3 right_axis = Vector3::Cross( up_axis, look_axis ).Normalize( );
	up_axis = Vector3::Cross( right_axis, look_axis ).Normalize( );
	mat3 *= Matrix3( ).FromRotation( Quaternion( ).Rotation( Vector3::cXAxis, Vector3::cYAxis, right_axis, up_axis ) );
	info->mFinalTransform = Matrix4( ).FromTranslationRotation( Vector3::cOrigin, mat3 );
	info->mFinalTransform *= Matrix4( ).Translation( position );
	info->mFinalTransform *= GetGUIModule( )->GetProcessor( )->OnGetViewProjectionMatrix( viewport );

	info->mZSort = ( Vector3::cOrigin * info->mFinalTransform ).z;
	GetGUIModule( )->AddPreRenderInSceneGUIObject( mGUIObject, info->mFinalTransform, info->mZSort );
	return _true;
}

_ubool GUIComponentPosition::UpdateAxialBillboardRenderTransform( IObject* viewport )
{
	Vector2 logic_size = GetLogicSize( );
	logic_size.x = logic_size.x == 0.0f ? 0.0f : 1.0f / logic_size.x;
	logic_size.y = logic_size.y == 0.0f ? 0.0f : 1.0f / logic_size.y;

	GUIRender3DInSceneInfo* info = GetGUIRender3DInSceneInfo( );
	Vector3 position = info->mLocalTransform.mTranslate * info->mRenderTransform;
	Matrix3 mat3 = Matrix3::CreateScaling( info->mSize.x * logic_size.x, -info->mSize.y * logic_size.y, 0.0f );
	Vector3 axis = ( info->mAxis * info->mRenderTransform.GetRotationMatrix( ) ).Normalize( );

	Matrix4 view_transform = GetGUIModule( )->GetProcessor( )->OnGetViewMatrix( viewport );
	Matrix4 view_inverse = Matrix4( view_transform ).Inverse( );

	Vector3 up_axis		= axis;
	Vector3 look_axis	= view_inverse.GetTranslationVector( ) - position;
	Vector3 right_axis	= Vector3::Cross( up_axis, look_axis ).Normalize( );
	mat3 *= Matrix3( ).FromRotation( Quaternion( ).Rotation( Vector3::cXAxis, Vector3::cYAxis, right_axis, up_axis ) );
	info->mFinalTransform = Matrix4( ).FromTranslationRotation( Vector3::cOrigin, mat3 );
	info->mFinalTransform *= Matrix4( ).Translation( position );
	info->mFinalTransform *= GetGUIModule( )->GetProcessor( )->OnGetViewProjectionMatrix( viewport );

	info->mZSort = ( Vector3::cOrigin * info->mFinalTransform ).z;
	GetGUIModule( )->AddPreRenderInSceneGUIObject( mGUIObject, info->mFinalTransform, info->mZSort );
	return _true;
}

_ubool GUIComponentPosition::UpdateRectangleRenderTransform( IObject* viewport )
{
	Vector2 logic_size = GetLogicSize( );
	logic_size.x = logic_size.x == 0.0f ? 0.0f : 1.0f / logic_size.x;
	logic_size.y = logic_size.y == 0.0f ? 0.0f : 1.0f / logic_size.y;

	GUIRender3DInSceneInfo* info = GetGUIRender3DInSceneInfo( );
	Vector3 position = info->mLocalTransform.mTranslate * info->mRenderTransform;
	Matrix3 mat3 = Matrix3::CreateScaling( info->mSize.x * logic_size.x, -info->mSize.y * logic_size.y, 0.0f );
	mat3 *= Matrix3( ).FromRotation( info->mLocalTransform.mRotation );
	info->mFinalTransform = Matrix4( ).FromTranslationRotation( Vector3::cOrigin, mat3 );
	info->mFinalTransform *= Matrix4( ).Translation( position );
	info->mFinalTransform *= GetGUIModule( )->GetProcessor( )->OnGetViewProjectionMatrix( viewport );

	info->mZSort = ( Vector3::cOrigin * info->mFinalTransform ).z;
	GetGUIModule( )->AddPreRenderInSceneGUIObject( mGUIObject, info->mFinalTransform, info->mZSort );
	return _true;
}

_ubool GUIComponentPosition::UpdateOverlayRenderTransform( IObject* viewport )
{
	GUIRender3DInSceneInfo* info = GetGUIRender3DInSceneInfo( );
	Vector3 position = info->mLocalTransform.mTranslate * info->mRenderTransform;

	Vector2 pos_screen = GetGUIModule( )->GetProcessor( )->OnConvert3DTo2D( viewport, position, &info->mZSort );
	Vector2 ui_scale = GetGUIModule( )->GetRootApplication( )->GetComponentPosition( )->GetScale( );
	Matrix3 matrix = Matrix3( pos_screen, ui_scale, 0.0f );

	if ( info->mZSort < 1.0f )
	{
		GetGUIModule( )->AddPreRenderInSceneGUIObject( mGUIObject, matrix, info->mZSort );
		return _true;
	}
	return _false;
}

Vector2 GUIComponentPosition::GetRenderInSceneScreenPosition( IObject* viewport, _float* zsort ) const
{
	if ( mRenderInSceneInfo == _null )
		return Vector2::cOrigin;

	Vector3 position = mRenderInSceneInfo->mLocalTransform.mTranslate * mRenderInSceneInfo->mRenderTransform;
	Vector2 pos_screen = GetGUIModule( )->GetProcessor( )->OnConvert3DTo2D( viewport, position, zsort );

	return pos_screen;
}

_void GUIComponentPosition::ResetControlRender3DInUIInfo( )
{
	SetAnimationXYRotation( 0.0f, 0.0f );
	SetOffsetZ( 0.0f );
	SetXRadian( 0.0f );
	SetYRadian( 0.0f );
	SetZDistance( 0.0f );
	SetRotationAnchorZ( 0.0f );
}

_void GUIComponentPosition::Relayout()
{
	SendHSizeChangedMessage();
	SendVSizeChangedMessage();
}
