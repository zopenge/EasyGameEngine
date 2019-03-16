//! @file     RHIMethods.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

// DEFINE_RHIMETHOD is used by the includer to modify the RHI method definitions.
#ifndef DEFINE_RHIMETHOD
	#error "The DEFINE_RHIMETHOD marco must be defined"
	#define DEFINE_RHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) Type Name ParameterTypesAndNames
#endif

//----------------------------------------------------------------------------
// RHI Driver
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	_ubool,
	Initialize,
	(),
	return _false;
	)
DEFINE_RHIMETHOD(
	_void,
	Finalize,
	(),
	;
	)
DEFINE_RHIMETHOD(
	_ubool,
	ResetResources,
	(),
	return _false;
	)
DEFINE_RHIMETHOD(
	_void,
	UnloadResources,
	(),
	;
	)
DEFINE_RHIMETHOD(
	IResourceManagerRHI*,
	GetResourceManager,
	(),
	return _null;
	)
DEFINE_RHIMETHOD(
	RenderStatsRHI&,
	GetRenderStats,
	(),
	static RenderStatsRHI sRenderStatsRHI; return sRenderStatsRHI;
	)
DEFINE_RHIMETHOD(
	const RenderStatsRHI&,
	GetRenderStats,
	() const,
	static RenderStatsRHI sRenderStatsRHI; return sRenderStatsRHI;
	)
DEFINE_RHIMETHOD(
	_void,
	ClearRenderStats,
	(),
	;
	)
DEFINE_RHIMETHOD(
	_void,
	ClearCaches,
	(),
	;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetRenderContextsNumber,
	(),
	return 0;
	)

//----------------------------------------------------------------------------
// RHI Features
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	_ubool,
	IsSupportETC1,
	() const,
	return _false;
	)
DEFINE_RHIMETHOD(
	_ubool,
	IsSupportETC2,
	() const,
	return _false;
	)
DEFINE_RHIMETHOD(
	_ubool,
	IsSupportVAO,
	() const,
	return _false;
	)
DEFINE_RHIMETHOD(
	_ubool,
	IsSupportInstancedRendering,
	() const,
	return _false;
	)

//----------------------------------------------------------------------------
// RHI VR Device
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	_void,
	SetVRRenderTargetTexID,
	(_dword index, _dword tex_id, const PointU& tex_size),
	;
	)
DEFINE_RHIMETHOD(
	PointU,
	GetVRTextureSize,
	(_dword index) const,
	return PointU::cZeroPoint;
	)
DEFINE_RHIMETHOD(
	VREyeRHI,
	GetVREyeInfo,
	(_dword index) const,
	return VREyeRHI( );
	)

//----------------------------------------------------------------------------
// RHI State
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	SamplerStateRHIPassRef,
	CreateSamplerState,
	(const SamplerStateInitializerRHI& initializer),
	return _null;
	)
DEFINE_RHIMETHOD(
	RasterizerStateRHIPassRef,
	CreateRasterizerState,
	(const RasterizerStateInitializerRHI& initializer),
	return _null;
	)
DEFINE_RHIMETHOD(
	DepthStateRHIPassRef,
	CreateDepthState,
	(const DepthStateInitializerRHI& initializer),
	return _null;
	)
DEFINE_RHIMETHOD(
	StencilStateRHIPassRef,
	CreateStencilState,
	(const StencilStateInitializerRHI& initializer),
	return _null;
	)
DEFINE_RHIMETHOD(
	BlendStateRHIPassRef,
	CreateBlendState,
	(const BlendStateInitializerRHI& initializer),
	return _null;
	)

DEFINE_RHIMETHOD(
	SamplerStateInitializerRHI,
	GetSamplerState,
	(const SamplerStateRHI* state) const,
	return SamplerStateInitializerRHI( _SF_NEAREST );
	)
DEFINE_RHIMETHOD(
	RasterizerStateInitializerRHI,
	GetRasterizerState,
	(const RasterizerStateRHI* state) const,
	return RasterizerStateInitializerRHI( _false, _false, _false, _false, _RFM_POINT, _RCM_NONE );
	)
DEFINE_RHIMETHOD(
	DepthStateInitializerRHI,
	GetDepthState,
	(const DepthStateRHI* state) const,
	return DepthStateInitializerRHI( _false, _CF_LESS );
	)
DEFINE_RHIMETHOD(
	StencilStateInitializerRHI,
	GetStencilState,
	(const StencilStateRHI* state) const,
	return StencilStateInitializerRHI( );
	)
DEFINE_RHIMETHOD(
	BlendStateInitializerRHI,
	GetBlendState,
	(const BlendStateRHI* state) const,
	return BlendStateInitializerRHI( );
	)

DEFINE_RHIMETHOD(
	_ubool,
	IsSameSamplerState,
	(const SamplerStateRHI* state1, const SamplerStateRHI* state2) const,
	return _false;
	)
DEFINE_RHIMETHOD(
	_ubool,
	IsSameRasterizerState,
	(const RasterizerStateRHI* state1, const RasterizerStateRHI* state2) const,
	return _false;
	)
DEFINE_RHIMETHOD(
	_ubool,
	IsSameDepthState,
	(const DepthStateRHI* state1, const DepthStateRHI* state2) const,
	return _false;
	)
DEFINE_RHIMETHOD(
	_ubool,
	IsSameStencilState,
	(const StencilStateRHI* state1, const StencilStateRHI* state2) const,
	return _false;
	)
DEFINE_RHIMETHOD(
	_ubool,
	IsSameBlendState,
	(const BlendStateRHI* state1, const BlendStateRHI* state2) const,
	return _false;
	)

//----------------------------------------------------------------------------
// RHI Shader
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	PixelShaderRHIPassRef,
	CreatePixelShader,
	(AStringPtr code),
	return _null;
	)
DEFINE_RHIMETHOD(
	VertexShaderRHIPassRef,
	CreateVertexShader,
	(AStringPtr code),
	return _null;
	)
DEFINE_RHIMETHOD(
	BoundShaderRHIPassRef,
	CreateBoundShader,
	(VertexShaderRHI* vertexshader, PixelShaderRHI* pixelshader),
	return _null;
	);

DEFINE_RHIMETHOD(
	PixelShaderRHI*,
	GetPixelShader,
	(BoundShaderRHI* shader),
	return _null;
	)
DEFINE_RHIMETHOD(
	VertexShaderRHI*,
	GetVertexShader,
	(BoundShaderRHI* shader),
	return _null;
	)
DEFINE_RHIMETHOD(
	const AStringObj&,
	GetPixelShaderCode,
	(BoundShaderRHI* shader),
	return GetStringTable( )->GetNullAString( );
	)
DEFINE_RHIMETHOD(
	const AStringObj&,
	GetVertexShaderCode,
	(BoundShaderRHI* shader),
	return GetStringTable( )->GetNullAString( );
	)
DEFINE_RHIMETHOD(
	_dword,
	GetShaderResourceID,
	(const BoundShaderRHI* shader) const,
	return 0;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetUniformBufferLocation,
	(BoundShaderRHI* shader, AStringPtr name),
	return -1;
	);
DEFINE_RHIMETHOD(
	_dword,
	ActiveUniformBuffer,
	(BoundShaderRHI* shader, _UNIFORM_BUFFER_DATA_TYPE type, const AStringObj& name, _dword size),
	return -1;
	);
DEFINE_RHIMETHOD(
	_ubool,
	UpdateUniformBuffer,
	(BoundShaderRHI* shader, _dword location, const _void* buffer, _dword size),
	return _false;
	);
DEFINE_RHIMETHOD(
	_ubool,
	SetUniformPropertyValue,
	(BoundShaderRHI* shader, AStringPtr name, _int value),
	return _false;
	);

//----------------------------------------------------------------------------
// RHI VertexDeclaration
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	VertexDeclarationRHIPassRef,
	CreateVertexDeclaration,
	(const VertexElementRHIArray& elements),
	return _null;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetVertexDeclarationVertexType,
	(VertexDeclarationRHI* declaration),
	return 0;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetVertexDeclarationStride,
	(VertexDeclarationRHI* declaration),
	return 0;
	)
DEFINE_RHIMETHOD(
	const VertexElementRHIArray&,
	GetVertexDeclarationDefine,
	(VertexDeclarationRHI* declaration),
	static VertexElementRHIArray sNull; return sNull;
	)

//----------------------------------------------------------------------------
// RHI IndexBuffer
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	IndexBufferRHIPassRef,
	CreateIndexBuffer,
	(_dword stride, _dword size, const _byte* buffer, _RESOURCE_DRAW_TYPE draw_type),
	return _null;
	)
DEFINE_RHIMETHOD(
	_byte*,
	LockIndexBuffer,
	(IndexBufferRHI* indexbuffer, _dword offset, _dword size),
	return _null;
	)
DEFINE_RHIMETHOD(
	_void,
	UnlockIndexBuffer,
	(IndexBufferRHI* indexbuffer),
	;
	)
DEFINE_RHIMETHOD(
	const _byte*,
	GetIndexBufferData,
	(IndexBufferRHI* indexbuffer),
	return _null;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetIndexBufferStride,
	(IndexBufferRHI* indexbuffer),
	return 0;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetIndexBufferSize,
	(IndexBufferRHI* indexbuffer),
	return 0;
	)
DEFINE_RHIMETHOD(
	_ubool,
	UpdateIndexBuffer,
	(IndexBufferRHI* index_buffer, _dword offset, _dword size, const _byte* buffer),
	return _false;
	)
DEFINE_RHIMETHOD(
	_ubool,
	ResizeIndexBuffer,
	(IndexBufferRHI* index_buffer, _dword size),
	return _false;
	)
DEFINE_RHIMETHOD(
	_ubool,
	FlushIndexBuffer,
	(IndexBufferRHI* index_buffer),
	return _false;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetIndexBufferResID,
	(IndexBufferRHI* index_buffer),
	return 0;
	)

//----------------------------------------------------------------------------
// RHI VertexBuffer
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	VertexBufferRHIPassRef,
	CreateVertexBuffer,
	(_dword stride, _dword size, const _byte* buffer, _RESOURCE_DRAW_TYPE draw_type),
	return _null;
	)
DEFINE_RHIMETHOD(
	_byte*,
	LockVertexBuffer,
	(VertexBufferRHI* vertexbuffer, _dword offset, _dword size),
	return _null;
	)
DEFINE_RHIMETHOD(
	_void,
	UnlockVertexBuffer,
	(VertexBufferRHI* vertexbuffer),
	;
	)
DEFINE_RHIMETHOD(
	const _byte*,
	GetVertexBufferData,
	(VertexBufferRHI* vertexbuffer),
	return _null;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetVertexBufferStride,
	(VertexBufferRHI* vertexbuffer),
	return 0;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetVertexBufferSize,
	(VertexBufferRHI* vertexbuffer),
	return 0;
	)
DEFINE_RHIMETHOD(
	_ubool,
	UpdateVertexBuffer,
	(VertexBufferRHI* vertexbuffer, _dword offset, _dword size, const _byte* buffer),
	return _false;
	)
DEFINE_RHIMETHOD(
	_ubool,
	ResizeVertexBuffer,
	(VertexBufferRHI* vertexbuffer, _dword size),
	return _false;
	)
DEFINE_RHIMETHOD(
	_ubool,
	FlushVertexBuffer,
	(VertexBufferRHI* vertexbuffer),
	return _false;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetVertexBufferResID,
	(VertexBufferRHI* vertexbuffer),
	return 0;
	)

//----------------------------------------------------------------------------
// RHI VertexArray
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	VertexArrayRHIPassRef,
	CreateVertexArray,
	(),
	return _null;
	)
DEFINE_RHIMETHOD(
	_void,
	BindVertexArray,
	(VertexArrayRHI* vertex_array),
	;
	)
DEFINE_RHIMETHOD(
	_void,
	UnbindVertexArray,
	(),
	;
	)
DEFINE_RHIMETHOD(
	_ubool,
	SetVertexArrayDecl,
	(VertexArrayRHI* vertex_array, VertexDeclarationRHI* declaration, VertexBufferRHI* vbo, IndexBufferRHI* ibo),
	return _false;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetVertexArrayResID,
	(VertexArrayRHI* vertex_array),
	return 0;
	)

//----------------------------------------------------------------------------
// RHI Texture
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	const GPUTextureInfoRHI&,
	GetGPUTextureInfo,
	(),
	static GPUTextureInfoRHI sNull; return sNull;
	)

// Texture Cube
DEFINE_RHIMETHOD(
	TextureCubeRHIPassRef,
	CreateTextureCube,
	(WStringPtr res_name, _dword nummips, const TextureCubeWithMipmapsRHI& mipmaps_info),
	return _null;
	)
DEFINE_RHIMETHOD(
	TextureCubeRHIPassRef,
	CreateTextureCubeWithMipmaps,
	(WStringPtr res_name, _dword nummips, const TextureCubeWithMipmapsRHI* mipmaps_info),
	return _null;
	)
DEFINE_RHIMETHOD(
	const PointU&,
	GetTextureCubeSize,
	(TextureCubeRHI* texture) const,
	return PointU::cZeroPoint;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetTextureCubeSizeInBytes,
	(TextureCubeRHI* texture) const,
	return 0;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetTextureCubeMipNumber,
	(const TextureCubeRHI* texture) const,
	return 0;
	)

// Texture 2D
DEFINE_RHIMETHOD(
	Texture2DRHIPassRef,
	CreateTexture2D,
	(WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, const _byte* pixel, _ubool is_dynamic),
	return _null;
	)
DEFINE_RHIMETHOD(
	Texture2DRHIPassRef,
	CreateTexture2DFromImageFile,
	(WStringPtr res_name, IImageFile* image_file, _dword nummips),
	return _null;
	)
DEFINE_RHIMETHOD(
	Texture2DRHIPassRef,
	CreateTexture2DWithMipmaps,
	(WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, const _byte** pixels),
	return _null;
	)
DEFINE_RHIMETHOD(
	_ubool,
	UpdateTexture2D,
	(Texture2DRHI* texture, const RectU& rect, const _byte* pixel),
	return _false;
	)
DEFINE_RHIMETHOD(
	_ubool,
	ReadTexture2DMipPixel,
	(const Texture2DRHI* texture, _byte* pixel_buffer),
	return _false;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetTexture2DResID,
	(const Texture2DRHI* texture) const,
	return 0;
	)
DEFINE_RHIMETHOD(
	const PointU&,
	GetTexture2DSize,
	(const Texture2DRHI* texture) const,
	return PointU::cZeroPoint;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetTexture2DMipNumber,
	(const Texture2DRHI* texture) const,
	return 0;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetTexture2DMipSize,
	(const Texture2DRHI* texture, _dword mipindex) const,
	return 0;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetTexture2DStride,
	(const Texture2DRHI* texture, _dword mipindex) const,
	return 0;
	)
DEFINE_RHIMETHOD(
	_ubool,
	IsTexture2DDynamic,
	(const Texture2DRHI* texture) const,
	return _false;
	)
DEFINE_RHIMETHOD(
	_PIXEL_FORMAT,
	GetTexture2DPixelFormat,
	(const Texture2DRHI* texture) const,
	return _PF_UNKNOWN;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetTexture2DSizeInBytes,
	(Texture2DRHI* texture) const,
	return 0;
	)
DEFINE_RHIMETHOD(
	SamplerStateInitializerRHI,
	GetTexture2DSamplerStateInfo,
	(Texture2DRHI* texture) const,
	return SamplerStateInitializerRHI( _SF_NEAREST );
	)
DEFINE_RHIMETHOD(
	_void,
	LockTexture2DSamplerState,
	(Texture2DRHI* texture, _ubool lock),
	;
	)
DEFINE_RHIMETHOD(
	_ubool,
	IsTexture2DCompressed,
	(Texture2DRHI* texture) const,
	return _false;
	)

//----------------------------------------------------------------------------
// RHI Font
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	FontRHIPassRef,
	CreateFontFromStream,
	(const FontInitializerRHI& initializer, IStreamReader* stream_reader),
	return _null;
	)
DEFINE_RHIMETHOD(
	const FontInitializerRHI&,
	GetFontInfo,
	(FontRHI* font) const,
	static FontInitializerRHI sFontInitializerRHI; return sFontInitializerRHI;
	)
DEFINE_RHIMETHOD(
	_float,
	GetCharAdvance,
	(FontRHI* font, _dword code) const,
	return 0.0f;
	)
DEFINE_RHIMETHOD(
	_float,
	GetCharMaxHeight,
	(FontRHI* font) const,
	return 0.0f;
	)
DEFINE_RHIMETHOD(
	IFontFace*,
	GetFontFace,
	(FontRHI* font) const,
	return _null;
	)
DEFINE_RHIMETHOD(
	const FontCodeRHI*,
	GetFontCode,
	(FontRHI* font, _dword code) const,
	return _null;
	)
DEFINE_RHIMETHOD(
	const FontCodeRHI*,
	GetFontCodeByStrokeEffect,
	(FontRHI* font, _dword code, _dword stroke_size) const,
	return _null;
	)
DEFINE_RHIMETHOD(
	const FontCodeRHI*,
	GetFontCodeByBlurEffect,
	(FontRHI* font, _dword code, _dword blur_size, _dword blur_factor) const,
	return _null;
	)
DEFINE_RHIMETHOD(
	_void,
	ClearFontCaches,
	(FontRHI* font),
	;
	)

//----------------------------------------------------------------------------
// RHI Surface
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	SurfaceRHIPassRef,
	CreateTargetableSurface,
	(Texture2DRHI* texture),
	return _null;
	)
DEFINE_RHIMETHOD(
	SurfaceRHIPassRef,
	CreateTargetableSurface,
	(TextureCubeRHI* texture),
	return _null;
	)
DEFINE_RHIMETHOD(
	SurfaceRHIPassRef,
	CreateTargetableSurface,
	(_dword width, _dword height, _PIXEL_FORMAT format),
	return _null;
	)
DEFINE_RHIMETHOD(
	const PointU&,
	GetSurfaceSize,
	(SurfaceRHI* surface) const,
	return PointU::cZeroPoint;
	)
DEFINE_RHIMETHOD(
	Texture2DRHI*,
	GetSurfaceTexture2D,
	(SurfaceRHI* surface) const,
	return _null;
	)
DEFINE_RHIMETHOD(
	TextureCubeRHI*,
	GetSurfaceTextureCube,
	(SurfaceRHI* surface) const,
	return _null;
	)
DEFINE_RHIMETHOD(
	_ubool,
	SetSurfaceTextureCubeFaceIndex,
	(SurfaceRHI* surface, _dword index),
	return _false;
	)
DEFINE_RHIMETHOD(
	_dword,
	GetSurfaceTextureCubeFaceIndex,
	(SurfaceRHI* surface) const,
	return -1;
	)

//----------------------------------------------------------------------------
// RHI Viewport
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	ViewportRHIPassRef,
	CreateViewport,
	(_handle app_handle, const PointU& size),
	return _null;
	)
DEFINE_RHIMETHOD(
	_ubool,
	ResizeViewport,
	(ViewportRHI* viewport, const PointU& size),
	return _false;
	)
DEFINE_RHIMETHOD(
	const PointU&,
	GetViewportSize,
	(ViewportRHI* viewport) const,
	return PointU::cZeroPoint;
	)
DEFINE_RHIMETHOD( 
	_void,
	BindViewport,
	(ViewportRHI* viewport),
	;
	)
DEFINE_RHIMETHOD( 
	_void,
	Present,
	(ViewportRHI* viewport),
	;
	)

//----------------------------------------------------------------------------
// RHI Command
//----------------------------------------------------------------------------

DEFINE_RHIMETHOD(
	_void,
	SetViewport,
	(const Viewport& viewport),
	;
	)

DEFINE_RHIMETHOD( 
	_void,
	SetDepthState,
	(const DepthStateRHI* state),
	;
	)
DEFINE_RHIMETHOD( 
	_void,
	SetStencilState,
	(const StencilStateRHI* state),
	;
	)
DEFINE_RHIMETHOD( 
	_void,
	SetBlendState,
	(const BlendStateRHI* state),
	;
	)
DEFINE_RHIMETHOD( 
	_void,
	SetRasterizerState,
	(const RasterizerStateRHI* state),
	;
	)
DEFINE_RHIMETHOD( 
	_void,
	SetRasterizerStateImmediate,
	(const RasterizerStateInitializerRHI& initializer),
	;
	)
DEFINE_RHIMETHOD(
	_void,
	SetSamplerState,
	(_dword samplerindex, const SamplerStateRHI* state, Texture2DRHI* texture),
	;
	)
DEFINE_RHIMETHOD(
	_void,
	SetSamplerState,
	(_dword samplerindex, const SamplerStateRHI* state, TextureCubeRHI* texture),
	;
	)

DEFINE_RHIMETHOD(
	_void,
	SetLineWidth,
	(_float width),
	;
	)

DEFINE_RHIMETHOD(
	_void,
	SetRenderTarget,
	(SurfaceRHI* rendertarget, SurfaceRHI* depthstencil),
	;
	)
DEFINE_RHIMETHOD(
	_void,
	ReadPixels,
	(const RectU& rect, _PIXEL_FORMAT format, _byte* pixels),
	;
	)

DEFINE_RHIMETHOD(
	_void,
	SetBoundShader,
	(BoundShaderRHI* shader),
	;
	)

DEFINE_RHIMETHOD(
	_void,
	ClearBuffers,
	(_ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil),
	;
	)

DEFINE_RHIMETHOD(
	_void,
	DrawPoint,
	(const Vector2& position, const Color& color),
	;
	)
DEFINE_RHIMETHOD(
	_void,
	DrawLine,
	(const Vector2& start, const Vector2& end, const Color& color, _float width),
	;
	)
DEFINE_RHIMETHOD(
	_void,
	DrawLine,
	(const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width),
	;
	)
DEFINE_RHIMETHOD(
	_void,
	DrawRectangle,
	(const RectI& rect, const Color& color, _dword width),
	;
	)
DEFINE_RHIMETHOD(
	_void,
	DrawRectangle,
	(const RectF& rect, const Color& color, _float width),
	;
	)
DEFINE_RHIMETHOD(
	_void,
	FillRectangle,
	(const RectI& rect, const Color& color),
	;
	)
DEFINE_RHIMETHOD(
	_void,
	FillRectangle,
	(const RectF& rect, const Color& color),
	;
	)

DEFINE_RHIMETHOD(
	_void,
	DrawSprite,
	(const Vector2& position, const Vector2& size, Texture2DRHI* texture, const Color& color, const Vector2& uv1, const Vector2& uv2, _ubool is_rotate, _ubool is_round),
	;
	)

DEFINE_RHIMETHOD(
	_void,
	DrawText,
	(_dword alignment, const RectF& rect, WStringPtr string, FontRHI* font, const Color& color),
	;
	)

DEFINE_RHIMETHOD(
	_void,
	DrawPrimitive,
	(_PRIMITIVE_TYPE type, _dword offset, _dword number),
	;
	)
DEFINE_RHIMETHOD(
	_void,
	DrawIndexedPrimitive,
	(_PRIMITIVE_TYPE type, _dword start_index, _dword number),
	;
	)