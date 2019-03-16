//! @file     GUIComponentState.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GUIComponentState
//----------------------------------------------------------------------------

class GUIComponent3DRender : public TGUIComponent< IGUIComponent3DRender >
{
public:
	RTTI_CLASS_WITH_ARGUMENTS_DECL( GUIComponent3DRender, IGUIComponent3DRender, IGUIObject* )

public:
	_GUICOMPONENT_ENABLE_HANDLE_EVENT( )
	_GUICOMPONENT_ENABLE_EXPORT( )

public:
	typedef TGUIComponent< IGUIComponent3DRender > BaseClass;

private:
	_float						mFov;
	Frustum						mFrustum;
	Matrix4						mScalingMatrix;
	Matrix4						mProjectionMatrix;
	Matrix4						mViewProjectionMatrix;

public:
	GUIComponent3DRender( IGUIObject* gui_object );
	virtual ~GUIComponent3DRender( );

public:
	_void						UpdateRenderInfo( );

// IObject Interface
public:
	virtual IObject*			CloneTo( _void* arguments ) const override;

// ISerializable Interface
public:
	virtual _ubool				Import( ISerializableNode* node ) override;
	virtual _ubool				Export( ISerializableNode* node ) const override;

// IGUIComponent Interface
public:
	virtual _ubool				IsResident( ) const override;

	virtual _ubool				HandleEvent( const EventBase& event, const FlagsObject& flags ) override;

// IGUIComponentState Interface
public:
	virtual _void				SetFOV( _float fov ) override;
	virtual _float				GetFOV( ) const override;
	virtual const Frustum&		GetFrustum( ) const override;
	virtual const Matrix4&		GetScalingMatrix( ) const override;
	virtual const Matrix4&		GetProjectionMatrix( ) const override;
	virtual const Matrix4&		GetViewProjectionMatrix( ) const override;
	virtual Vector3				Get3DPosition( _float x, _float y ) const override;
};

//----------------------------------------------------------------------------
// GUIComponentState Implementation
//----------------------------------------------------------------------------

}