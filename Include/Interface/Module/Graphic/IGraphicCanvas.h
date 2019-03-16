//! @file     IGraphicCanvas.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicCanvas
//----------------------------------------------------------------------------

class IGraphicCanvas : public IGraphicScene
{
public:
	//!	Set the scene.
	//!	@param		scene		The scene.
	//!	@return		none.
	virtual _void SetScene( IGraphicScene* scene ) PURE;
	//!	Get the scene.
	//!	@param		none.
	//!	@return		The scene.
	virtual IGraphicScene* GetScene( ) PURE;

	//!	Get the size.
	//!	@param		none.
	//!	@return		The size.
	virtual const PointU& GetSize( ) const PURE;

	//!	Get the render target.
	//!	@param		none.
	//!	@return		The render target surface.
	virtual IGraphicSurface* GetRenderTarget( ) PURE;
	//!	Get the depth stencil.
	//!	@param		none.
	//!	@return		The depth stencil surface.
	virtual IGraphicSurface* GetDepthStencil( ) PURE;

	//!	Lock render target.
	//!	@param		stride		The stride of pixel buffer.
	//! @return		The pixel buffer, null indicates failure.
	virtual _void* LockRenderTarget( _dword& stride ) PURE;
	//!	Unlock render target.
	//!	@param		none.
	//! @return		none.
	virtual _void UnlockRenderTarget( ) PURE;

	//!	Set the viewport and projection transform from scene's view.
	//!	@param		client_size		The client size.
	//!	@param		scene_view		The scene view.
	//!	@return		none.
	virtual _void SetViewportAndProjectionTransform( const PointU& client_size, IGraphicScene* scene ) PURE;
};

}