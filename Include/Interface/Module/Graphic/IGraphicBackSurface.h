//! @file     IGraphicBackSurface.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicBackSurface
//----------------------------------------------------------------------------

class IGraphicBackSurface : public IObject
{
public:
	//!	Check whether it's rendering.
	//!	@param		none.
	//!	@return		True indicates it's rendering.
	virtual _ubool IsRendering( ) const PURE;

	//!	Get the canvas.
	//!	@param		none.
	//!	@return		The canvas.
	virtual IGraphicCanvas* GetCanvas( ) PURE;

	//!	Get the surface size.
	//!	@param		none.
	//!	@return		The surface size.
	virtual PointU GetSize( ) const PURE;

	//!	Set the previous client size.
	//!	@param		size	The previous client size.
	//!	@return		none.
	virtual _void SetPrevClientSize( const PointU& size ) PURE;

	//!	Set the clear buffers info.
	//!	@param		none.
	//!	@return		none.
	virtual _void SetClearBuffersInfo( const GraphicClearBuffersInfo& info ) PURE;

	//!	Set the rendering scale.
	//!	@param		scale	The rendering scale.
	//! @return		none.
	virtual _void SetRenderScale( _float scale ) PURE;
	//!	Get the rendering scale.
	//!	@param		none.
	//! @return		The rendering scale.
	virtual _float GetRenderScale( ) const PURE;

	//!	Begin render.
	//!	@param		scene	The render scene.
	//! @return		none.
	virtual _void BeginRender( IGraphicScene* scene ) PURE;
	//!	End render by default effect.
	//!	@param		none.
	//! @return		none.
	virtual _void EndRender( ) PURE;

	//!	Render to scene.
	//!	@param		scene		The scene.
	//!	@return		none.
	virtual _void RenderToScene( IGraphicScene* scene ) PURE;
	//!	Render to scene.
	//!	@param		scene		The scene.
	//!	@param		effect		The render effect.
	//!	@return		none.
	virtual _void RenderToScene( IGraphicScene* scene, IGraphicEffect* effect ) PURE;

	//!	Present render buffers.
	//!	@param		none.
	//!	@return		none.
	virtual _void PresentRenderBuffers( ) PURE;
};

}