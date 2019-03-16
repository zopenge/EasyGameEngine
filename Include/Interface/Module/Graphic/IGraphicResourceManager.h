//! @file     IGraphicResourceManager.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicResourceManager
//----------------------------------------------------------------------------

class IGraphicResourceManager : public IObject
{
public:
	//!	Create sampler state from resource name.
	//!	@param		type		The internal type.
	//!	@return		The sampler state.
	virtual SamplerStateRHIRef GetSamplerStateFromResName( const WStringObj& res_name ) PURE;
	//!	Create rasterizer state from resource name.
	//!	@param		type		The internal type.
	//!	@return		The rasterizer state.
	virtual RasterizerStateRHIRef GetRasterizerStateFromResName( const WStringObj& res_name ) PURE;
	//!	Create depth state from resource name.
	//!	@param		type		The internal type.
	//!	@return		The depth state.
	virtual DepthStateRHIRef GetDepthStateFromResName( const WStringObj& res_name ) PURE;
	//!	Create blend state from resource name.
	//!	@param		type		The internal type.
	//!	@return		The blend state.
	virtual BlendStateRHIRef GetBlendStateFromResName( const WStringObj& res_name ) PURE;
	//!	Create stencil state from resource name.
	//!	@param		type		The internal type.
	//!	@return		The stencil state.
	virtual StencilStateRHIRef GetStencilStateFromResName( const WStringObj& res_name ) PURE;

	//!	Create the vertex declaration.
	//!	@param		elements		The vertex declaration elements.
	//!	@return		The vertex declaration.
	virtual IGraphicVertexDeclarationPassRef CreateVertexDeclaration( const VertexElementRHIArray& elements ) PURE;
	//!	Create vertex declaration.
	//! @param		vertex_decl		The vertex declaration.
	//!	@return		The vertex declaration interface.
	virtual IGraphicVertexDeclarationPassRef CreateVertexDeclaration( VertexDeclarationRHI* vertex_decl ) PURE;
	//!	Create vertex declaration.
	//!	@param		vertex_type		The vertex type of geometry, @see _GEOMETRY_VERTEX_TYPE.
	//!	@return		The vertex declaration interface.
	virtual IGraphicVertexDeclarationPassRef CreateVertexDeclaration( _dword vertex_type ) PURE;

	//!	Create index buffer.
	//!	@param		index_buffer	The index buffer.
	//!	@return		The index buffer interface.
	virtual IGraphicIndexBufferPassRef CreateIndexBuffer( IndexBufferRHI* index_buffer ) PURE;
	//!	Create vertex buffer.
	//!	@param		vertex_buffer	The vertex buffer.
	//!	@return		The vertex buffer interface.
	virtual IGraphicVertexBufferPassRef CreateVertexBuffer( VertexBufferRHI* vertex_buffer ) PURE;

	//!	Create vertex array.
	//!	@param		draw_type		The draw type.
	//!	@param		vertex_decl		The vertex declaration.
	//!	@return		The vertex array interface.
	virtual IGraphicVertexArrayPassRef CreateVertexArray( _RESOURCE_DRAW_TYPE draw_type, VertexDeclarationRHI* vertex_decl ) PURE;

	//!	Create 2D texture from resource.
	//! @param		resource		The texture resource.
	//!	@return		The texture interface.
	virtual IGraphicTexture2DPassRef CreateTexture2D( Texture2DRHI* resource ) PURE;
	//!	Create 2D texture from stream.
	//!	@param		res_name		The resource name.
	//! @param		stream_reader	The stream reader.
	//! @param		nummips			The mipmaps level.
	//!	@return		The texture interface.
	virtual IGraphicTexture2DPassRef CreateTexture2DFromStream( WStringPtr res_name, IStreamReader* stream_reader, _dword nummips ) PURE;
	//!	Create 2D texture from image file.
	//!	@param		res_name		The resource name.
	//! @param		imagefile		The image file.
	//! @param		nummips			The mipmaps level.
	//!	@return		The texture interface.
	virtual IGraphicTexture2DPassRef CreateTexture2DFromImageFile( WStringPtr res_name, IImageFile* imagefile, _dword nummips ) PURE;
	//!	Create 2D texture with mipmaps info.
	//!	@param		res_name		The resource name.
	//!	@param		width			The image width.
	//!	@param		height			The image height.
	//!	@param		format			The image pixel format.
	//! @param		nummips			The mipmaps level.
	//!	@param		pixels			The image pixels of mipmaps.
	//!	@return		The texture interface.
	virtual IGraphicTexture2DPassRef CreateTexture2DWithMipmaps( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, const _byte** pixels ) PURE;
	//!	Create 2D texture from pixel buffer.
	//!	@param		res_name		The resource name.
	//!	@param		width			The image width.
	//!	@param		height			The image height.
	//!	@param		format			The image pixel format.
	//! @param		nummips			The mipmaps level.
	//!	@param		pixelbuffer		The image pixel buffer.
	//!	@return		The texture interface.
	virtual IGraphicTexture2DPassRef CreateTexture2D( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, const _byte* pixelbuffer, _ubool is_dynamic ) PURE;
	//!	Create sub-texture from texture 2D.
	//! @param		uv1				The left-top texture coordinates.
	//! @param		uv2				The right-bottom texture coordinates.
	//! @param		texture			The texture 2D.
	//!	@return		The texture interface.
	virtual IGraphicTexture2DPassRef CreateSubTexture2D( const Vector2& uv1, const Vector2& uv2, IGraphicTexture2D* texture ) PURE;
	
	//!	Create cube texture from resource.
	//! @param		resource		The texture resource.
	//!	@return		The texture interface.
	virtual IGraphicTextureCubePassRef CreateTextureCube( TextureCubeRHI* resource ) PURE;
	//!	Create cube texture.
	//!	@param		res_name		The resource name.
	//!	@param		nummips			The mipmaps level.
	//!	@param		mipmaps_info	The mipmaps info.
	//!	@return		The texture interface.
	virtual IGraphicTextureCubePassRef CreateTextureCube( WStringPtr res_name, _dword nummips, const TextureCubeWithMipmapsRHI& mipmaps_info ) PURE;
	//!	Create cube texture.
	//!	@param		res_name		The resource name.
	//!	@param		nummips			The mipmaps level.
	//!	@param		mipmaps_info	The mipmaps info.
	//!	@return		The texture interface.
	virtual IGraphicTextureCubePassRef CreateTextureCubeWithMipmaps( WStringPtr res_name, _dword nummips, const TextureCubeWithMipmapsRHI* mipmaps_info ) PURE;

	//!	Create 2D texture set.
	//!	@param		size			The texture size.
	//!	@param		space			The space size of images.
	//! @return		The texture 2D interface.
	virtual IGraphicTexture2DSetPassRef CreateTexture2DSet( const PointU& size, const PointU& space = PointU::cZeroPoint ) PURE;

	//!	Create back surface.
	//!	@param		width			The surface width.
	//!	@param		height			The surface height.
	//!	@return		The back surface.
	virtual IGraphicBackSurfacePassRef CreateBackSurface( _dword width, _dword height ) PURE;

	//!	Create render target.
	//!	@param		width			The surface width.
	//!	@param		height			The surface height.
	//!	@return		The surface.
	virtual IGraphicSurfacePassRef CreateRenderTarget( _dword width, _dword height ) PURE;
	//!	Create render target from texture cube.
	//!	@param		texture_cube	The texture cube.
	//!	@return		The surface.
	virtual IGraphicSurfacePassRef CreateRenderTarget( IGraphicTextureCube* texture_cube ) PURE;
	//!	Create depth surface.
	//!	@param		width			The surface width.
	//!	@param		height			The surface height.
	//!	@return		The surface.
	virtual IGraphicSurfacePassRef CreateDepthSurface( _dword width, _dword height ) PURE;
	//!	Create depth stencil.
	//!	@param		width			The surface width.
	//!	@param		height			The surface height.
	//!	@return		The surface.
	virtual IGraphicSurfacePassRef CreateDepthStencil( _dword width, _dword height ) PURE;
	//!	Create canvas.
	//!	@param		width			The surface width.
	//!	@param		height			The surface height.
	//!	@param		flags			The surface creation flags, @see _GRPAHIC_SURFACE_CREATION_FLAGS.
	//!	@return		The canvas.
	virtual IGraphicCanvasPassRef CreateCanvas( _dword width, _dword height, _dword flags ) PURE;
	//!	Create canvas.
	//!	@param		render_target	The render target.
	//!	@param		depth_stencil	The depth stencil.
	//!	@return		The canvas.
	virtual IGraphicCanvasPassRef CreateCanvas( IGraphicSurface* render_target, IGraphicSurface* depth_stencil ) PURE;
	//!	Create canvas.
	//!	@param		scene			The scene.
	//!	@param		width			The surface width.
	//!	@param		height			The surface height.
	//!	@param		flags			The surface creation flags, @see _GRPAHIC_SURFACE_CREATION_FLAGS.
	//!	@return		The canvas.
	virtual IGraphicCanvasPassRef CreateCanvas( IGraphicScene* scene, _dword width, _dword height, _dword flags ) PURE;
	//!	Create canvas.
	//!	@param		scene			The scene.
	//!	@param		render_target	The render target.
	//!	@param		depth_stencil	The depth stencil.
	//!	@return		The canvas.
	virtual IGraphicCanvasPassRef CreateCanvas( IGraphicScene* scene, IGraphicSurface* render_target, IGraphicSurface* depth_stencil ) PURE;

	//!	Create font.
	//!	@param		resource		The font resource.
	//!	@return		The font interface.
	virtual IGraphicFontPassRef CreateFont( FontRHI* resource ) PURE;
	//!	Create font from stream.
	//!	@param		initializer		The font initializer.
	//!	@param		stream_reader	The font stream.
	//!	@return		The font interface.
	virtual IGraphicFontPassRef CreateFontFromStream( const FontInitializerRHI& initializer, IStreamReader* stream_reader ) PURE;
	//!	Create font from system.
	//!	@param		initializer		The font initializer.
	//!	@param		name			The font name.
	//!	@return		The font interface.
	virtual IGraphicFontPassRef CreateFontFromSystem( const FontInitializerRHI& initializer, WStringPtr name ) PURE;
	//!	Create font from system.
	//!	@param		initializer			The font initializer.
	//!	@param		name				The font name.
	//!	@param		utf16_code_range	The UTF-16 code range, if the specified font resource is not existing.
	//!	@return		The font interface.
	virtual IGraphicFontPassRef CreateFontFromSystem( const FontInitializerRHI& initializer, WStringPtr name, const DwordRange& utf16_code_range ) PURE;
	//!	Create font from system.
	//!	@param		initializer			The font initializer.
	//!	@param		name				The font name.
	//!	@param		utf16_code_ranges	The UTF-16 code ranges, if the specified font resource is not existing.
	//!	@return		The font interface.
	virtual IGraphicFontPassRef CreateFontFromSystem( const FontInitializerRHI& initializer, WStringPtr name, const Array< DwordRange >& utf16_code_ranges ) PURE;
	//!	Create font from resource name.
	//!	@param		initializer		The font initializer.
	//!	@param		res_name		The resource name.
	//!	@return		The font interface.
	virtual IGraphicFontPassRef CreateFontFromResName( const FontInitializerRHI& initializer, const WStringObj& res_name ) PURE;
	//!	Create font from resource name.
	//!	@param		initializer			The font initializer.
	//!	@param		res_name			The resource name.
	//!	@param		utf16_code_range	The UTF-16 code range, if the specified font resource is not existing.
	//!	@return		The font interface.
	virtual IGraphicFontPassRef CreateFontFromResName( const FontInitializerRHI& initializer, const WStringObj& res_name, const DwordRange& utf16_code_range ) PURE;
	//!	Create font from resource name.
	//!	@param		initializer			The font initializer.
	//!	@param		res_name			The resource name.
	//!	@param		utf16_code_ranges	The UTF-16 code ranges, if the specified font resource is not existing.
	//!	@return		The font interface.
	virtual IGraphicFontPassRef CreateFontFromResName( const FontInitializerRHI& initializer, const WStringObj& res_name, const Array< DwordRange >& utf16_code_ranges ) PURE;

	//!	Create scene.
	//!	@param		none.
	//!	@return		The scene interface.
	virtual IGraphicScenePassRef CreateScene( ) PURE;
	//!	Create scene view.
	//!	@param		none.
	//!	@return		The scene view interface.
	virtual IGraphicSceneViewPassRef CreateSceneView( ) PURE;
	//!	Create viewport.
	//!	@param		size			The initial viewport size.
	//!	@return		The viewport interface.
	virtual IGraphicViewportPassRef CreateViewport( const PointU& size ) PURE;
	//!	Create viewport.
	//!	@param		app_handle		The application handle.
	//!	@param		size			The initial viewport size.
	//!	@return		The viewport interface.
	virtual IGraphicViewportPassRef CreateViewport( _handle app_handle, const PointU& size ) PURE;

	//!	Create light.
	//!	@param		none.
	//!	@return		The light interface.
	virtual IGraphicLightPassRef CreateLight( ) PURE;

	//!	Create flat mirror.
	//!	@param		size		The size.
	//!	@return		The mirror.
	virtual IGraphicFlatMirrorPassRef CreateFlatMirror( const PointU& size, const Plane& plane ) PURE;
	//!	Create sphere mirror.
	//!	@param		size		The size.
	//!	@return		The mirror.
	virtual IGraphicSphereMirrorPassRef CreateSphereMirror( const PointU& size ) PURE;

	//!	Optimize vertex shader code.
	//!	@param		code		The vertex shader code.
	//!	@return		The optimized vertex shader code, empty string indicates failure.
	virtual AStringR OptimizeVertexShader( AStringPtr code ) PURE;
	//!	Optimize pixel shader code.
	//!	@param		code		The vertex shader code.
	//!	@return		The optimized pixel shader code, empty string indicates failure.
	virtual AStringR OptimizePixelShader( AStringPtr code ) PURE;

	//!	Create vertex shader in cache mode.
	//!	@param		code		The vertex shader code.
	//!	@return		The vertex shader.
	virtual VertexShaderRHIRef CreateVertexShader( AStringPtr code ) PURE;
	//!	Create pixel shader in cache mode.
	//!	@param		code		The pixel shader code.
	//!	@return		The pixel shader.
	virtual PixelShaderRHIRef CreatePixelShader( AStringPtr code ) PURE;

	//!	Create effect from shader.
	//!	@param		shader		The shader.
	//!	@return		The effect interface.
	virtual IGraphicEffectPassRef CreateEffectFromShader( BoundShaderRHI* shader ) PURE;
	//!	Create effect from resource name.
	//!	@remark		We will load it from working archive.
	//!	@param		res_name	The effect resource name.
	//!	@return		The effect interface.
	virtual IGraphicEffectPassRef CreateEffectFromResName( const WStringObj& res_name ) PURE;
	//!	Create effect from other effect.
	//!	@param		effect		The effect.
	//!	@param		macros		The enabled macros, use '|' to split it.
	//!	@return		The effect interface.
	virtual IGraphicEffectPassRef CreateEffectFromEffect( IGraphicEffect* effect, AStringPtr macros ) PURE;
	//!	Create effect from code.
	//!	@param		vs_code		The vertex shader code.
	//!	@param		ps_code		The pixel shader code.
	//!	@param		macros		The enabled macros, use '|' to split it.
	//!	@return		The effect interface.
	virtual IGraphicEffectPassRef CreateEffectFromCode( const AStringObj& vs_code, const AStringObj& ps_code, AStringPtr macros ) PURE;

	//!	Load the texture cube image.
	//!	@param		type		The face type.
	//!	@param		res_name	The resource name.
	//!	@return		The images list.
	virtual IImageFilePassRef LoadTextureCubeImage( _CUBE_TEX_SUBFACE_TYPE type, WStringPtr res_name ) PURE;
	//!	Load the texture cube images list.
	//!	@param		stream_reader	The stream reader.
	//!	@param		num_mips		The number of mips.
	//!	@param		info			The texture cube info.
	//!	@return		The images list.
	virtual _ubool LoadTextureCubeImages( IStreamReader* stream_reader, _dword& num_mips, TextureCubeWithMipmapsRHI*& mipmaps ) PURE;
};

}