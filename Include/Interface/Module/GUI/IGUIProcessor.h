//! @file     IGUIProcessor.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIProcessor
//----------------------------------------------------------------------------

class IGUIProcessor : public IObject
{
public:
	virtual const Matrix4& OnGetViewMatrix( IObject* viewport ) const PURE;
	virtual Vector2 OnGetViewportSize( IObject* viewport ) const PURE;
	virtual const Matrix4& OnGetViewProjectionMatrix( IObject* viewport ) const PURE;
	virtual Vector2 OnConvert3DTo2D( IObject* viewport, const Vector3& pos, _float* zsort ) const PURE;

	virtual Matrix4 OnGetViewportOverlayMatrix( IObject* viewport ) const PURE;
	virtual Matrix4 OnGetViewportOffsetMatrix( IObject* viewport ) const PURE;

	//!	When push overlay world transform.
	//!	@param		viewport	The graphic viewport.
	//!	@param		transform	The offset transform.
	//!	@return		none.
	virtual _void OnPushUserOrthoTransform( IObject* viewport, const Matrix4& transform ) PURE;
	//!	When pop overlay world transform.
	//!	@param		viewport	The graphic viewport.
	//!	@return		none.
	virtual _void OnPopUserOrthoTransform( IObject* viewport ) PURE;

	//!	When push overlay scissor rect.
	//!	@param		viewport	The graphic viewport.
	//!	@param		rect		The scissor rect.
	//!	@return		none.
	virtual _void OnPushOverlayScissorRect( IObject* viewport, const RectF& rect ) PURE;
	//!	When pop overlay scissor rect.
	//!	@param		viewport	The graphic viewport.
	//!	@return		none.
	virtual _void OnPopOverlayScissorRect( IObject* viewport ) PURE;

	virtual _ubool OnAppendGUIObjectAnimation( IGUIObject* gui_object, _dword delay, WStringPtr res_name ) PURE;
};

}