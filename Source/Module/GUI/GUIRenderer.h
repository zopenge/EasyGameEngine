//! @file     GUIRenderer.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GUIRenderer
//----------------------------------------------------------------------------

class GUIRenderer
{
private:
	//!	The GUI object render info
	struct GUIRenderInfo
	{
		Matrix3	mTransform;
		Color	mColor;
		RectF	mClipRect;

		GUIRenderInfo( )
		{
			mTransform	= Matrix3::cIdentity;
			mColor		= Color::cNull;
			mClipRect	= RectF::cNull;
		}
		GUIRenderInfo( const Matrix3& transform, const Color& color, const RectF& clip_rect )
		{
			mTransform	= transform;
			mColor		= color;
			mClipRect	= clip_rect;
		}
	};

	//!	The control render info
	struct GUIControlRenderInfo : public GUIRenderInfo
	{
		IGUIObjectRef	mGUIObject;

		GUIControlRenderInfo( )
		{

		}
		GUIControlRenderInfo( IGUIObject* object, const Matrix3& transform, const Color& color, const RectF& clip_rect )
			: GUIRenderInfo( transform, color, clip_rect ), mGUIObject( object )
		{
		}
	};
	typedef Array< GUIControlRenderInfo > GUIControlRenderInfoArray;

	//!The control render in scene info
	struct GUIControlRenderInSceneInfo
	{
		IGUIObjectRef	mGUIObject;
		Matrix4			mMatrix4;
		Matrix3			mMatrix3;
		_ubool			mOverlay;
		_float			mZSort;
		operator const _float ( ) const
		{ return mZSort; }
	};
	typedef Array< GUIControlRenderInSceneInfo, _float >	GUIControlRenderInSceneInfoArray;

	//!	The component render info
	struct GUIComponentRenderInfo : public GUIRenderInfo
	{
		IGUIComponentRef	mGUIComponent;

		GUIComponentRenderInfo( )
		{

		}
		GUIComponentRenderInfo( IGUIComponent* object, const Matrix3& transform, const Color& color, const RectF& clip_rect )
			: GUIRenderInfo( transform, color, clip_rect ), mGUIComponent( object )
		{
		}
	};
	typedef Array< GUIComponentRenderInfo > GUIComponentRenderInfoArray;

private:
	GUIControlRenderInfoArray	mDelayRenderGUIObjects;
	GUIComponentRenderInfoArray	mDelayRenderGUIComponents;
	GUIControlRenderInSceneInfoArray	mPreRenderInSceneGUIObjects;
public:
	GUIRenderer( );
	~GUIRenderer( );

public:
	//!	Add delay render GUI object.
	_void AddPreRenderInSceneGUIObject( IGUIObject* object, const Matrix3& transform, _float zsort );
	_void AddPreRenderInSceneGUIObject( IGUIObject* object, const Matrix4& transform, _float zsort );
	_void AddDelayRenderGUIObject( IGUIObject* object, const Matrix3& transform, const Color& color, const RectF& clip_rect );
	_void AddDelayRenderGUIComponent( IGUIComponent* component, const Matrix3& transform, const Color& color, const RectF& clip_rect );
	//!	Render.
	_void RenderDelayObject( IObject* viewport );
	_void RenderPreObject( IObject* viewport );
};

}