//! @file     GraphicGlobals.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Static Resident String Object Name
//----------------------------------------------------------------------------

// Samplers
STATIC_WSTROBJ_V( SamplerNearest, L"sampler_nearest.xml" );
STATIC_WSTROBJ_V( SamplerLinear, L"sampler_linear.xml" );

// Rasterizer
STATIC_WSTROBJ_V( RasterizerDisableColorWrite, L"rasterizer_disable_color_write.xml" );

// Blend
STATIC_WSTROBJ_V( BlendMix, L"blend_mix.xml" );

// Common Shader
STATIC_WSTROBJ_V( eVertexColor, L"vertex_color.shader" );
STATIC_WSTROBJ_V( eTex0, L"tex0.shader" );
STATIC_WSTROBJ_V( eTex0DiscardTransparent, L"tex0_discard_transparent.shader" );

// Overlay Shader
STATIC_WSTROBJ_V( eOverlayDrawText, L"overlay_draw_text.shader" );

// Textures
STATIC_ASTROBJ( uDiffuseTex );

// FlatMirror
STATIC_ASTROBJ( uFlatMirrorPlane );
STATIC_ASTROBJ( uFlatMirrorAttenuationDistance );
STATIC_ASTROBJ( uFlatMirrorTex );

// SphereMirror
STATIC_ASTROBJ( uSphereMirrorTex );

// SpriteMask
STATIC_ASTROBJ( uSpriteMaskPosMin );
STATIC_ASTROBJ( uSpriteMaskPosXDir );
STATIC_ASTROBJ( uSpriteMaskPosYDir );
STATIC_ASTROBJ( uSpriteMaskUVMin );
STATIC_ASTROBJ( uSpriteMaskUVRange );
STATIC_ASTROBJ( uSpriteMaskTex );

// Mesh
STATIC_ASTROBJ( uModelColor );
STATIC_ASTROBJ( uModelTransform );

// Transforms
STATIC_ASTROBJ( uViewTransform );
STATIC_ASTROBJ( uProjectionTransform );
STATIC_ASTROBJ( uMVPTransform );

// Camera
STATIC_ASTROBJ( uEyePos );
STATIC_ASTROBJ( uEyeLookAt );

//----------------------------------------------------------------------------
// The graphic enumerations
//----------------------------------------------------------------------------

//!	The graphic surface creation flags
enum _GRPAHIC_SURFACE_CREATION_FLAGS
{
	_GRAPHIC_SURFACE_RENDER_TARGET	= 1 << 0, //! Has render target.
	_GRAPHIC_SURFACE_DEPTH_STENCIL	= 1 << 1, //! Has depth stencil
	_GRAPHIC_SURFACE_ALL			= _GRAPHIC_SURFACE_RENDER_TARGET | _GRAPHIC_SURFACE_DEPTH_STENCIL,
};

//!	The graphic render queue
enum _GRAPHIC_RENDER_QUEUE
{
	_GRAPHIC_RENDER_BACKGROUND,		//! Draw geometry one by one at begin.
	_GRAPHIC_RENDER_OPAQUE,			//!	Draw geometry from near to far.
	_GRAPHIC_RENDER_TRANSPARENT,	//!	Draw geometry from far to near.
	_GRAPHIC_RENDER_OVERLAY,		//!	Draw geometry one by one at last.
};

//!	The graphic mirror type
enum _GRAPHIC_MIRROR_TYPE
{
	_GRAPHIC_MIRROR_NONE	= 0,
	_GRAPHIC_MIRROR_FLAT	= 1 << 0,
	_GRAPHIC_MIRROR_SPHERE	= 1 << 1,
};

//----------------------------------------------------------------------------
// The graphic structure
//----------------------------------------------------------------------------

//!	The graphic render statistic
struct GraphicRenderStatistic : public RenderStatsRHI
{
};

//!	The graphic clear buffers info
struct GraphicClearBuffersInfo
{
	_ubool	mIsClearColor;
	_ubool	mIsClearDepth;
	_ubool	mIsClearStencil;
	Color	mClearColor;
	_float	mClearDepth;
	_dword	mClearStencil;

	_void Reset( );

	GraphicClearBuffersInfo( );
};

//!	The graphic uniform buffer
struct GraphicUniformBuffer : public UniformBufferRHI
{
	//!	The buffer data
	_byte*	mBuffer;

	GraphicUniformBuffer( );
	GraphicUniformBuffer( _UNIFORM_BUFFER_DATA_TYPE type, _dword location, _dword size, const AStringObj& name );
};

//!	The graphic UV info
struct GraphicUVInfo
{
	//! The texture left-top coordinate.
	Vector2 mLT;
	//! The texture left-bottom coordinate.
	Vector2 mLB;
	//! The texture right-top coordinate.
	Vector2 mRT;
	//! The texture right-bottom coordinate.
	Vector2 mRB;

	Vector2 GetMin( ) const;
	Vector2 GetMax( ) const;
	Vector2 GetRange( ) const;

	GraphicUVInfo( );
	GraphicUVInfo( const Vector2& uv1, const Vector2& uv2 );
	GraphicUVInfo( const Vector2& lt_uv, const Vector2& lb_uv, const Vector2& rt_uv, const Vector2& rb_uv );
};

//!	The graphic mask UV info
struct GraphicMaskUVInfo : GraphicUVInfo
{
	_ubool	mIsRotate;

	GraphicMaskUVInfo( );
	GraphicMaskUVInfo( _ubool is_rotate, const GraphicUVInfo& uv_info );
};

//! The graphic vertex info
struct GraphicVertexInfo
{
	Vector3	mPosition;
	_dword	mColor;
	_dword	mSecondaryColor;
	Vector2	mUV1;

	// Overlay
	_void Init( const Vector2& pos, _dword color );
	_void Init( const Vector2& pos, _dword color, const Vector2& uv );
	_void Init( const Vector2& pos, _dword color, _dword secondary_color, const Vector2& uv );
	_void Init( const Vector2& pos, _dword color, _float u, _float v );
	_void Init( const Vector2& pos, _dword color, _dword secondary_color, _float u, _float v );

	// Primitive
	_void Init( const Vector3& pos, _dword color );
	_void Init( const Vector3& pos, _dword color, const Vector2& uv );
	_void Init( const Vector3& pos, _dword color, _float u, _float v );
};

//!	The rasterizer states(use texture name as key)
typedef Map< SamplerStateRHIRef, AStringObj > SamplerStateRHIRefMap;

//!	The graphic render state info
struct GraphicRenderStateInfo
{
	SamplerStateRHIRefMap	mSamplerStates;
	SamplerStateRHIRef		mCubeTextureSamplerState;

	RasterizerStateRHIRef	mRasterizerState;
	DepthStateRHIRef		mDepthState;
	StencilStateRHIRef		mStencilState;
	BlendStateRHIRef		mBlendState;

	_ubool IsEqual( const GraphicRenderStateInfo& info ) const;
};
typedef Stack< GraphicRenderStateInfo > GraphicRenderStateInfoStack;

//!	The textures(use texture name as key)
typedef Map< Texture2DRHIRef, AStringObj > Texture2DRHIRefMap;

//!	The graphic geometry info
struct GraphicGeometryInfo
{
	//!	The primitive type, @see _PRIMITIVE_TYPE
	_dword					mPrimitiveType;

	//!	The geometry weight
	//!		- Line primitive: use it as width.
	//!		- others are undefined.
	_float					mWeight;

	//!	The uniform buffers CRC value to check whether can combine 
	_crcvalue				mUBOCRCValue;
	//!	The uniform buffers number
	_dword					mUBONumber;
	//!	The uniform buffers
	GraphicUniformBuffer*	mUBOs;

	//!	The vertex stride in bytes
	_dword					mVBStride;
	//!	The vertex offset in bytes
	_dword					mVBOffset;
	//!	The vertex size in bytes
	_dword					mVBSize;

	//!	The start index of vertices in index buffer
	_dword					mIBOStartIndex;
	//!	The vertices number in index buffer
	_dword					mIBONumber;

	//!	The VAO resource
	VertexArrayRHIRef		mVAOResource;

	//!	The viewport 
	const Viewport*			mViewport;

	//!	The passing render states
	GraphicRenderStateInfo	mRenderStates;

	//!	The textures
	Texture2DRHIRefMap		mTextures;
	//!	The texture cube map
	TextureCubeRHIRef		mTextureCube;

	//!	Initialize.
	_void Init( _PRIMITIVE_TYPE type, _float weight, _dword vb_stride, _dword vb_number );
	_void InitWithIB( _PRIMITIVE_TYPE type, _float weight, _dword vb_stride, _dword vb_number, _dword ib_number );

	//!	Append texture.
	_void AppendTexture( const AStringObj& name, Texture2DRHI* texture );

	//! Check whether can combine with other geometry info.
	_ubool CanCombine( const GraphicGeometryInfo& geometry ) const;
	_ubool CanCombine( const GraphicGeometryInfo& geometry, const VertexArrayRHI* vao, _crcvalue ubo_crc_value, _dword ibo_start_index ) const;

	//!	Get index buffer size.
	_dword GetIBSize( ) const;

	GraphicGeometryInfo( );
};

//!	The graphic mesh geometry info.
struct GraphicMeshGeometryInfo : public GraphicGeometryInfo
{
	//! The render distance offset
	_float					mRenderDistanceOffset;

	//!	The current color
	Color					mColor;
	//!	The model transform
	Matrix4					mModelTransform;
	//!	The axis aligned box
	AxisAlignedBox			mAABox;

	//!	The mirror type
	_GRAPHIC_MIRROR_TYPE	mMirrorType;
	//!	The mirror size
	_dword					mMirrorSize;
	//!	The mirror reflect type, @see _GRAPHIC_MIRROR_TYPE
	_dword					mMirrorReflectType;
	//!	The reflection plane
	Plane					mMirrorReflectionPlane;

	GraphicMeshGeometryInfo( );
};

}