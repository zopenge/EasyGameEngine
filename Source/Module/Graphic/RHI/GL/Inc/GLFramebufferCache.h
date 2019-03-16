//! @file     GLFramebufferCache.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class GLSurface;

//----------------------------------------------------------------------------
// GLFramebufferCache
//----------------------------------------------------------------------------

class GLFramebufferCache
{
	SINGLETON( GLFramebufferCache )

public:
	//!	The frame buffer cache data
	struct GLFramebufferData
	{
		GLFramebuffer	mFramebuffer;
		GLSurface*		mRenderTarget;
		GLSurface*		mDepthStencil;

		GLFramebufferData( GLSurface* rendertarget = _null, GLSurface* depthstencil = _null )
			: mRenderTarget( rendertarget ), mDepthStencil( depthstencil ) {}
	};
	typedef Map< GLFramebufferData, _qword > GLFramebufferDataMap;

private:
	//!	Build FBO key ID.
	inline static _qword BuildFBOKeyID( GLSurface* rendertarget, GLSurface* depthstencil );

private:
	//!	The cache map
	GLFramebufferDataMap	mCache;

public:
	//!	Clear all cache.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );

	//!	Get the frame buffer.
	//!	@param		rendertarget	The render target.
	//!	@param		depthstencil	The depth stencil target.
	//!	@return		The frame buffer object.
	GLFramebuffer* GetFramebuffer( GLSurface* rendertarget, GLSurface* depthstencil );
	//!	Release frame buffer.
	//!	@param		surface		The surface.
	//!	@return		none.
	_void ReleaseFramebuffer( GLSurface* surface );
};

//----------------------------------------------------------------------------
// GLFramebufferCache Implementation
//----------------------------------------------------------------------------

_qword GLFramebufferCache::BuildFBOKeyID( GLSurface* rendertarget, GLSurface* depthstencil )
{
	_qword key_id = ((_qword) rendertarget) | ((_qword) depthstencil << 32);
	return key_id;
}

}