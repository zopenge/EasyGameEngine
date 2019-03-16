//! @file     GraphicResourceManager.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicResourceManager
//----------------------------------------------------------------------------

class GraphicResourceManager : public INTERFACE_OBJECT_IMPL( IGraphicResourceManager )
{
private:
	//!	The render states cache, use (resource name) as key.
	typedef Map< SamplerStateRHIRef, WStringObj > SamplerStateRHIRefMap;
	typedef Map< RasterizerStateRHIRef, WStringObj > RasterizerStateRHIRefMap;
	typedef Map< DepthStateRHIRef, WStringObj > DepthStateRHIRefMap;
	typedef Map< BlendStateRHIRef, WStringObj > BlendStateRHIRefMap;
	typedef Map< StencilStateRHIRef, WStringObj > StencilStateRHIRefMap;

	//!	The VS/PS cache, use code as key
	typedef Map< VertexShaderRHIRef, _crcvalue > VertexShaderRHIRefMap;
	typedef Map< PixelShaderRHIRef, _crcvalue > PixelShaderRHIRefMap;

	//!	The bound shaders cache, use (resource name) or (PSCode + VSCode) as key
	typedef Map< BoundShaderRHIRef, _crcvalue > BoundShaderRHIRefMap;

	//!	The fonts cache
	typedef Array< IGraphicFontRef > GraphicFontArray;

private:
	//!	The application handle
	_handle						mAppHandle;

	//!	The render states
	SamplerStateRHIRefMap		mSamplerStates;
	RasterizerStateRHIRefMap	mRasterizerStates;
	DepthStateRHIRefMap			mDepthStates;
	BlendStateRHIRefMap			mBlendStates;	
	StencilStateRHIRefMap		mStencilStates;	

	//!	The shaders
	VertexShaderRHIRefMap		mVShaders;
	PixelShaderRHIRefMap		mPShaders;
	BoundShaderRHIRefMap		mBoundShaders;

	//!	The font resource list
	GraphicFontArray			mGraphicFonts;

private:
	//!	Cleanup fonts.
	_void CleanupFonts( );

	//!	Create surfaces.
	_ubool CreateSurfaces( IGraphicSurfaceRef& render_target, IGraphicSurfaceRef& depth_stencil, _dword width, _dword height, _dword flags );

	//!	Load shader code by serializable node.
	AStringR LoadShaderCodeByNode( ISerializableNode* node );
	//!	Load shader code by resource name.
	AStringR LoadShaderCodeByResName( WStringPtr res_name );

	//!	Parse shader code.
	AStringR ParseShaderCode( AStringPtr code );

	//!	Check texture cube image size.
	_ubool CheckTextureCubeImageSize( _dword nummips, const TextureCubeWithMipmapsRHI* mipmaps ) const;
	//!	Rotate texture cube image.
	_void RotateTextureCubeImage( _CUBE_TEX_SUBFACE_TYPE type, IImageFile* image_file );

public:
	GraphicResourceManager( );
	virtual ~GraphicResourceManager( );

public:
	//!	Initialize.
	_ubool Initialize( _handle app_handle );
	//!	Finalize.
	_void Finalize( );

	//!	Clear caches.
	_void ClearCaches( );

// IGraphicResourceManager Interface
public:
	virtual SamplerStateRHIRef					GetSamplerStateFromResName( const WStringObj& res_name ) override;
	virtual RasterizerStateRHIRef				GetRasterizerStateFromResName( const WStringObj& res_name ) override;
	virtual DepthStateRHIRef					GetDepthStateFromResName( const WStringObj& res_name ) override;
	virtual BlendStateRHIRef					GetBlendStateFromResName( const WStringObj& res_name ) override;
	virtual StencilStateRHIRef					GetStencilStateFromResName( const WStringObj& res_name ) override;

	virtual IGraphicVertexDeclarationPassRef	CreateVertexDeclaration( const VertexElementRHIArray& elements ) override;
	virtual IGraphicVertexDeclarationPassRef	CreateVertexDeclaration( VertexDeclarationRHI* vertex_decl ) override;
	virtual IGraphicVertexDeclarationPassRef	CreateVertexDeclaration( _dword vertex_type ) override;

	virtual IGraphicIndexBufferPassRef			CreateIndexBuffer( IndexBufferRHI* index_buffer ) override;
	virtual IGraphicVertexBufferPassRef			CreateVertexBuffer( VertexBufferRHI* vertex_buffer ) override;

	virtual IGraphicVertexArrayPassRef			CreateVertexArray( _RESOURCE_DRAW_TYPE draw_type, VertexDeclarationRHI* vertex_decl ) override;

	virtual IGraphicTexture2DPassRef			CreateTexture2D( Texture2DRHI* resource ) override;
	virtual IGraphicTexture2DPassRef			CreateTexture2DFromStream( WStringPtr res_name, IStreamReader* stream_reader, _dword nummips ) override;
	virtual IGraphicTexture2DPassRef			CreateTexture2DFromImageFile( WStringPtr res_name, IImageFile* imagefile, _dword nummips ) override;
	virtual IGraphicTexture2DPassRef			CreateTexture2DWithMipmaps( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, const _byte** pixels ) override;
	virtual IGraphicTexture2DPassRef			CreateTexture2D( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, const _byte* pixelbuffer, _ubool is_dynamic ) override;
	virtual IGraphicTexture2DPassRef			CreateSubTexture2D( const Vector2& uv1, const Vector2& uv2, IGraphicTexture2D* texture ) override;

	virtual IGraphicTextureCubePassRef			CreateTextureCube( TextureCubeRHI* resource ) override;
	virtual IGraphicTextureCubePassRef			CreateTextureCube( WStringPtr res_name, _dword nummips, const TextureCubeWithMipmapsRHI& mipmaps_info ) override;
	virtual IGraphicTextureCubePassRef			CreateTextureCubeWithMipmaps( WStringPtr res_name, _dword nummips, const TextureCubeWithMipmapsRHI* mipmaps_info ) override;

	virtual IGraphicTexture2DSetPassRef			CreateTexture2DSet( const PointU& size, const PointU& space = PointU::cZeroPoint ) override;

	virtual IGraphicBackSurfacePassRef			CreateBackSurface( _dword width, _dword height ) override;

	virtual IGraphicSurfacePassRef				CreateRenderTarget( _dword width, _dword height ) override;
	virtual IGraphicSurfacePassRef				CreateRenderTarget( IGraphicTextureCube* texture_cube ) override;
	virtual IGraphicSurfacePassRef				CreateDepthSurface( _dword width, _dword height ) override;
	virtual IGraphicSurfacePassRef				CreateDepthStencil( _dword width, _dword height ) override;
	virtual IGraphicCanvasPassRef				CreateCanvas( _dword width, _dword height, _dword flags ) override;
	virtual IGraphicCanvasPassRef				CreateCanvas( IGraphicSurface* render_target, IGraphicSurface* depth_stencil ) override;
	virtual IGraphicCanvasPassRef				CreateCanvas( IGraphicScene* scene, _dword width, _dword height, _dword flags ) override;
	virtual IGraphicCanvasPassRef				CreateCanvas( IGraphicScene* scene, IGraphicSurface* render_target, IGraphicSurface* depth_stencil ) override;

	virtual IGraphicFontPassRef					CreateFont( FontRHI* resource ) override;
	virtual IGraphicFontPassRef 				CreateFontFromStream( const FontInitializerRHI& initializer, IStreamReader* stream_reader ) override;
	virtual IGraphicFontPassRef					CreateFontFromSystem( const FontInitializerRHI& initializer, WStringPtr name ) override;
	virtual IGraphicFontPassRef					CreateFontFromSystem( const FontInitializerRHI& initializer, WStringPtr name, const DwordRange& utf16_code_range ) override;
	virtual IGraphicFontPassRef					CreateFontFromSystem( const FontInitializerRHI& initializer, WStringPtr name, const Array< DwordRange >& utf16_code_ranges ) override;
	virtual IGraphicFontPassRef					CreateFontFromResName( const FontInitializerRHI& initializer, const WStringObj& res_name ) override;
	virtual IGraphicFontPassRef					CreateFontFromResName( const FontInitializerRHI& initializer, const WStringObj& res_name, const DwordRange& utf16_code_range ) override;
	virtual IGraphicFontPassRef					CreateFontFromResName( const FontInitializerRHI& initializer, const WStringObj& res_name, const Array< DwordRange >& utf16_code_ranges ) override;

	virtual IGraphicScenePassRef				CreateScene( ) override;
	virtual IGraphicSceneViewPassRef			CreateSceneView( ) override;
	virtual IGraphicViewportPassRef				CreateViewport( const PointU& size ) override;
	virtual IGraphicViewportPassRef				CreateViewport( _handle app_handle, const PointU& size ) override;

	virtual IGraphicLightPassRef				CreateLight( ) override;

	virtual IGraphicFlatMirrorPassRef			CreateFlatMirror( const PointU& size, const Plane& plane ) override;
	virtual IGraphicSphereMirrorPassRef			CreateSphereMirror( const PointU& size ) override;

	virtual AStringR							OptimizeVertexShader( AStringPtr code ) override;
	virtual AStringR							OptimizePixelShader( AStringPtr code ) override;

	virtual VertexShaderRHIRef					CreateVertexShader( AStringPtr code ) override;
	virtual PixelShaderRHIRef					CreatePixelShader( AStringPtr code ) override;

	virtual IGraphicEffectPassRef				CreateEffectFromShader( BoundShaderRHI* shader ) override;
	virtual IGraphicEffectPassRef				CreateEffectFromResName( const WStringObj& res_name ) override;
	virtual IGraphicEffectPassRef				CreateEffectFromEffect( IGraphicEffect* effect, AStringPtr macros ) override;
	virtual IGraphicEffectPassRef				CreateEffectFromCode( const AStringObj& vs_code, const AStringObj& ps_code, AStringPtr macros ) override;

	virtual IImageFilePassRef					LoadTextureCubeImage( _CUBE_TEX_SUBFACE_TYPE type, WStringPtr res_name ) override;
	virtual _ubool								LoadTextureCubeImages( IStreamReader* stream_reader, _dword& num_mips, TextureCubeWithMipmapsRHI*& mipmaps ) override;
};

//----------------------------------------------------------------------------
// GraphicResourceManager Implementation
//----------------------------------------------------------------------------

}