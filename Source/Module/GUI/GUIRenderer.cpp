//! @file     GUIRenderer.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIRenderer Implementation
//----------------------------------------------------------------------------

GUIRenderer::GUIRenderer( )
{
}

GUIRenderer::~GUIRenderer( )
{
}

_void GUIRenderer::AddPreRenderInSceneGUIObject( IGUIObject* object, const Matrix3& transform, _float zsort )
{
	EGE_ASSERT( object != _null );

	for ( _dword i = 0; i < mPreRenderInSceneGUIObjects.Number( ); ++ i )
	{
		if ( mPreRenderInSceneGUIObjects[i].mGUIObject.GetPtr( ) == object )
		{
			mPreRenderInSceneGUIObjects.RemoveByIndex( i );
			break;
		}
	}

	GUIControlRenderInSceneInfo info;
	info.mGUIObject = object;
	info.mMatrix3 = transform;
	info.mZSort = zsort;
	info.mOverlay = _true;
	mPreRenderInSceneGUIObjects.InsertDescending( info );
}

_void GUIRenderer::AddPreRenderInSceneGUIObject( IGUIObject* object, const Matrix4& transform, _float zsort )
{
	EGE_ASSERT( object != _null );

	for ( _dword i = 0; i < mPreRenderInSceneGUIObjects.Number( ); ++ i )
	{
		if ( mPreRenderInSceneGUIObjects[i].mGUIObject.GetPtr( ) == object )
		{
			mPreRenderInSceneGUIObjects.RemoveByIndex( i );
			break;
		}
	}

	GUIControlRenderInSceneInfo info;
	info.mGUIObject = object;
	info.mMatrix4 = transform;
	info.mZSort = zsort;
	info.mOverlay = _false;

	mPreRenderInSceneGUIObjects.InsertDescending( info );
}

_void GUIRenderer::AddDelayRenderGUIObject( IGUIObject* object, const Matrix3& transform, const Color& color, const RectF& clip_rect )
{
	EGE_ASSERT( object != _null );

	mDelayRenderGUIObjects.Append( GUIControlRenderInfo( object, transform, color, clip_rect ) );
}

_void GUIRenderer::AddDelayRenderGUIComponent( IGUIComponent* component, const Matrix3& transform, const Color& color, const RectF& clip_rect )
{
	EGE_ASSERT( component != _null );

	mDelayRenderGUIComponents.Append( GUIComponentRenderInfo( component, transform, color, clip_rect ) );
}

_void GUIRenderer::RenderDelayObject( IObject* viewport )
{
	// Render all delay GUI objects
	for ( _dword i = 0; i < mDelayRenderGUIObjects.Number( ); i ++ )
	{
		GUIControlRenderInfo& info = mDelayRenderGUIObjects[i];

		// Get the component state's flags
		FlagsObject& flags = info.mGUIObject->GetComponentState( )->GetStatesEx( );

		// Render it
		flags.ClearFlags( _GUI_STATE_EX_DELAY_RENDER );
		info.mGUIObject->Render( viewport, info.mTransform, info.mColor, info.mClipRect, _false, _false );
		flags.CombineFlags( _GUI_STATE_EX_DELAY_RENDER );
	}

	// Render all delay component objects
	for ( _dword i = 0; i < mDelayRenderGUIComponents.Number( ); i ++ )
	{
		GUIComponentRenderInfo& info = mDelayRenderGUIComponents[i];

		info.mGUIComponent->RenderAfterRootApplication( viewport, info.mTransform, info.mColor, info.mClipRect );
	}

	// Clear it
	mDelayRenderGUIObjects.Clear( );
	mDelayRenderGUIComponents.Clear( );
}

_void GUIRenderer::RenderPreObject( IObject* viewport )
{
	for ( _dword i = 0; i < mPreRenderInSceneGUIObjects.Number( ); ++ i )
	{
		GUIControlRenderInSceneInfo& info = mPreRenderInSceneGUIObjects[i];

		// Get the component state's flags
		FlagsObject& flags = info.mGUIObject->GetComponentState( )->GetAttributes( );

		// Render it
		flags.ClearFlags( _GUI_ATTRIBUTE_SCENE3D );
		if ( info.mOverlay )
		{
			info.mGUIObject->Render( viewport, info.mMatrix3, Color::cWhite, RectF::cMax, _false, _true );
		}
		else
		{
			GetGUIModule( )->GetProcessor( )->OnPushUserOrthoTransform( viewport, info.mMatrix4 );
			info.mGUIObject->Render( viewport, Matrix3::cIdentity, Color::cWhite, RectF::cMax, _false, _true );
			GetGUIModule( )->GetProcessor( )->OnPopUserOrthoTransform( viewport );
		}
		flags.CombineFlags( _GUI_ATTRIBUTE_SCENE3D );
	}

	mPreRenderInSceneGUIObjects.Clear( );
}