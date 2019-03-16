//! @file     GLRenderTarget.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GLSurface
//----------------------------------------------------------------------------

class GLSurface : public SurfaceRHI
{
private:
	//!	The pixel format
	_PIXEL_FORMAT		mFormat;
	//!	The surface size
	PointU				mSize;

	//! The render buffer resource ID
	GLuint				mRenderBufferResource;

	//! The 2D texture resource, if it's null then indicates it's render buffer resource type
	Texture2DRHIRef		mTexture2D;

	//!	The face index of cube texture
	_dword				mFaceIndex;
	//!	The cube texture resource
	TextureCubeRHIRef	mTextureCube;

public:
	GLSurface( Texture2DRHI* texture );
	GLSurface( TextureCubeRHI* texture );
	GLSurface( GLuint resource, _PIXEL_FORMAT format, const PointU& size );
	virtual ~GLSurface( );

public:
	//!	Get the surface pixel format.
	EGE_GET_ACCESSOR_CONST( _PIXEL_FORMAT, Format )
	//!	Get the surface size.
	EGE_GET_ACCESSOR_CONST( const PointU&, Size )
	//!	Get the render buffer resource ID.
	EGE_GET_ACCESSOR_CONST( GLuint, RenderBufferResource )
	//!	Get the 2D texture.
	EGE_GET_ACCESSOR( Texture2DRHI*, Texture2D )
	//!	Get/Set the cube texture.
	EGE_GET_SET_ACCESSOR( _dword, FaceIndex )
	//!	Get the cube texture.
	EGE_GET_ACCESSOR( TextureCubeRHI*, TextureCube )

public:
	 //! Get the resource ID, could be render buffer or texture resource ID.
	GLuint GetResourceID( ) const;
};

}