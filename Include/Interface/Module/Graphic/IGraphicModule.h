//! @file     IGraphicModule.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicModule
//----------------------------------------------------------------------------

class IGraphicModule : public IModule
{
public:
	//!	Get the texture 2D set.
	//!	@param		none.
	//!	@return		The texture 2D set.
	virtual IGraphicTexture2DSet* GetTexture2DSet( ) PURE;

	//!	Get the render target.
	//!	@param		none.
	//!	@return		The render target surface.
	virtual IGraphicSurface* GetRenderTarget( ) PURE;
	//!	Get the depth stencil.
	//!	@param		none.
	//!	@return		The depth stencil surface.
	virtual IGraphicSurface* GetDepthStencil( ) PURE;
	//!	Set the render target and depth stencil.
	//!	@param		rendertarget	The render target.
	//!	@param		depthstencil	The depth stencil.
	//!	@return		none.
	virtual _void SetRenderTarget( IGraphicSurface* rendertarget, IGraphicSurface* depthstencil ) PURE;
};

}