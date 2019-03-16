//! @file     IGraphicSceneDrawer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicSceneDrawer
//----------------------------------------------------------------------------

class IGraphicSceneDrawer : public IGraphicDrawer
{
public:
	//!	Set the scissor/clip rect.
	//!	@param		enable		True indicates enable the scissor rect.
	//!	@param		rect		The scissor rect.
	//!	@return		none.
	virtual _void SetScissorRect( _ubool enable, const RectU& rect ) PURE;
	//!	Get the scissor/clip rect info.
	//!	@param		enable			whether enable the scissor rect.
	//!	@param		rect			The scissor rect.
	//!	@return		none.
	virtual _void GetScissorRect( _ubool& enable, RectU& rect ) const PURE;
	//!	Push the scissor/clip rect.
	//!	@param		enable		True indicates enable the scissor rect.
	//!	@param		rect		The scissor rect.
	//!	@return		none.
	virtual _void PushScissorRect( _ubool enable, const RectU& rect ) PURE;
	//!	Pop the scissor/clip rect.
	//!	@param		none.
	//!	@return		none.
	virtual _void PopScissorRect( ) PURE;

	//!	Push the overlay scissor/clip rect.
	//!	@param		rect		The scissor rect.
	//!	@return		none.
	virtual _void PushOverlayScissorRect( const RectF& rect ) PURE;
	//!	Pop the overlay scissor/clip rect.
	//!	@param		none.
	//!	@return		none.
	virtual _void PopOverlayScissorRect( ) PURE;

	//!	Push the overlay transform.
	//!	@param		transform	The overlay transform.
	//!	@return		none.
	virtual _void PushOverlayTransform( const Matrix3& transform ) PURE;
	//!	Pop the overlay transform.
	//!	@param		none.
	//!	@return		none.
	virtual _void PopOverlayTransform( ) PURE;
	//!	Set the overlay transform.
	//!	@param		transform	The overlay transform.
	//!	@return		none.
	virtual _void SetOverlayTransform( const Matrix3& transform ) PURE;
	//!	Get the overlay transform.
	//!	@param		none.
	//!	@return		The overlay transform.
	virtual const Matrix3& GetOverlayTransform( ) const PURE;

	//!	Push the overlay world transform.
	//!	@param		transform	The overlay world transform.
	//!	@return		none.
	virtual _void PushUserOrthoTransform( const Matrix4& transform ) PURE;
	//!	Pop the overlay world transform.
	//!	@param		none.
	//!	@return		none.
	virtual _void PopUserOrthoTransform( ) PURE;
	//!	Set the overlay world transform.
	//!	@param		transform	The overlay world transform.
	//!	@return		none.
	virtual _void SetUserOrthoTransform( const Matrix4& transform ) PURE;
	//!	Get the overlay world transform.
	//!	@param		none.
	//!	@return		The overlay world transform.
	virtual const Matrix4& GetUserOrthoTransform( ) const PURE;

	//!	Push the offset transform.
	//!	@param		transform	The offset transform.
	//!	@return		none.
	virtual _void PushOffsetTransform( const Matrix4& transform ) PURE;
	//!	Pop the offset transform.
	//!	@param		none.
	//!	@return		none.
	virtual _void PopOffsetTransform( ) PURE;
	//!	Set the offset transform.
	//!	@param		transform	The offset transform.
	//!	@return		none.
	virtual _void SetOffsetTransform( const Matrix4& transform ) PURE;
	//!	Get the offset transform.
	//!	@param		none.
	//!	@return		The offset transform.
	virtual const Matrix4& GetOffsetTransform( ) const PURE;
};

}