//! @file     GUIComponent3DRender.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIComponent3DRender Implementation
//----------------------------------------------------------------------------

GUIComponent3DRender::GUIComponent3DRender( IGUIObject* gui_object ) : BaseClass( gui_object )
{
	mFov					= 58.0f;
	mFrustum				= Frustum::cIdentity;
	mScalingMatrix			= Matrix4::cIdentity;
	mProjectionMatrix		= Matrix4::cIdentity;
	mViewProjectionMatrix	= Matrix4::cIdentity;
}

GUIComponent3DRender::~GUIComponent3DRender( )
{

}

_void GUIComponent3DRender::UpdateRenderInfo( )
{
	Vector2 root_size = GetGUIModule( )->GetRootApplication( )->GetComponentPosition( )->GetLogicSize( );
	if ( root_size.x == 0.0f || root_size.y == 0.0f )
	{
		mFrustum				= Frustum::cIdentity;
		mScalingMatrix			= Matrix4::cIdentity;
		mProjectionMatrix		= Matrix4::cIdentity;
		mViewProjectionMatrix	= Matrix4::cIdentity;
	}
	else
	{
		_float aspect = root_size.y == 0.0f ? 1.0f : root_size.x / root_size.y;
		mProjectionMatrix = Matrix4::CreatePerspectiveFovRH( Math::Degree2Radian( mFov ), aspect, 1.0f, 200.0f );
		mFrustum = Frustum( GetGUIModule( )->Get3DUIViewMatrix( ), mProjectionMatrix );
		mViewProjectionMatrix = GetGUIModule( )->Get3DUIViewMatrix( ) * mProjectionMatrix;

		Vector3 pick_pos_1 = Get3DPosition( 0.0f, 0.0f );
		Vector3 pick_pos_2 = Get3DPosition( 1000.0f, 0.0f );
		_float scale = ( pick_pos_1 - pick_pos_2 ).Magnitude( ) / 1000.0f;

		mScalingMatrix	= Matrix4( ).Scaling( Vector3( scale, scale, scale ) );
	}
}

IObject* GUIComponent3DRender::CloneTo( _void* arguments ) const
{
	IGUIObject* gui_object = (IGUIObject*)arguments;
	EGE_ASSERT( gui_object != _null );

	GUIComponent3DRender* component = new GUIComponent3DRender( gui_object );
	component->CopyFrom( this );
	component->SetFOV( GetFOV( ) );

	return component;
}

_ubool GUIComponent3DRender::Import( ISerializableNode* node )
{
	if ( node == _null )
		return _false;

	node->Read( L"fov", mFov );
	UpdateRenderInfo( );

	return _true;
}

_ubool GUIComponent3DRender::Export( ISerializableNode* node ) const
{
	if ( node == _null )
		return _false;

	if ( node->Write( L"fov", mFov ) == _false )
		return _false;

	return _true;
}

_ubool GUIComponent3DRender::IsResident( ) const
{
	return _true;
}

_ubool GUIComponent3DRender::HandleEvent( const EventBase& event, const FlagsObject& flags )
{
	switch ( event.mEventID )
	{
	case _GUI_EVENT_SCENE_RESIZE:
		{
			UpdateRenderInfo( );
		}
		break;
	}

	return _false;
}

_void GUIComponent3DRender::SetFOV( _float fov )
{
	mFov = fov;
	UpdateRenderInfo( );
}

_float GUIComponent3DRender::GetFOV( ) const
{
	return mFov;
}

const Frustum& GUIComponent3DRender::GetFrustum( ) const
{
	return mFrustum;
}

const Matrix4& GUIComponent3DRender::GetScalingMatrix( ) const
{
	return mScalingMatrix;
}

const Matrix4& GUIComponent3DRender::GetProjectionMatrix( ) const
{
	return mProjectionMatrix;
}

const Matrix4& GUIComponent3DRender::GetViewProjectionMatrix( ) const
{
	return mViewProjectionMatrix;
}

Vector3 GUIComponent3DRender::Get3DPosition( _float x, _float y ) const
{
	Vector2 root_size = GetGUIModule( )->GetRootApplication( )->GetComponentPosition( )->GetLogicSize( );

	Ray ray = Ray::GetPickRay( x, y, root_size.x, root_size.y, GetGUIModule( )->Get3DUIViewMatrix( ), mProjectionMatrix );
	const Plane& near_plane = mFrustum.mPlanes[0];
	// Get the pick positions of near plane
	_float distance = 0.0f;
	Intersection::RayVSPlane( ray, near_plane, &distance );
	Vector3	pick_pos = ray.mOrigin + ray.mDirection * distance;

	return pick_pos;
}