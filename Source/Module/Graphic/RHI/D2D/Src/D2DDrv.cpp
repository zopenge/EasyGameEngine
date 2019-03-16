//! @file     D2DDrv.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D2DMethods
//----------------------------------------------------------------------------

EGE_BEGIN_NAMESPACE_2( EGE, D2D )

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) _##FuncName FuncName = _null;
#include "Module/Graphic/RHI/D2D/Inc/D2DMethods.h"
#undef DEFINE_FUNC_PTR

EGE_END_NAMESPACE_2( )

//----------------------------------------------------------------------------
// D2DDrv Implementation
//----------------------------------------------------------------------------

D2DDrv::D2DDrv( )
{
	mD2DClearColor	= TranslateD2DColorF( Color::cBlack );
}

D2DDrv::~D2DDrv( )
{
}

D2D1_COLOR_F D2DDrv::TranslateD2DColorF( const Color& color )
{
	D2D1_COLOR_F d2d_color;
	d2d_color.r = color.r;
	d2d_color.g = color.g;
	d2d_color.b = color.b;
	d2d_color.a = color.a;

	return d2d_color;
}

D2D1_RECT_F D2DDrv::TranslateD2DRectF( const RectI& rect )
{
	D2D1_RECT_F d2d_rect;
	d2d_rect.left	= (_float) rect.l;
	d2d_rect.top	= (_float) rect.t;
	d2d_rect.right	= (_float) rect.r;
	d2d_rect.bottom = (_float) rect.b;

	return d2d_rect;
}

D2D1_RECT_F D2DDrv::TranslateD2DRectF( const RectF& rect )
{
	D2D1_RECT_F d2d_rect;
	d2d_rect.left	= rect.l;
	d2d_rect.top	= rect.t;
	d2d_rect.right	= rect.r;
	d2d_rect.bottom = rect.b;

	return d2d_rect;
}

_ubool D2DDrv::Initialize( )
{
	// Load D2D libraries
	_handle d2d1_dll = Platform::LoadLibrary( "d2d1.dll" );
	if ( d2d1_dll == _null )
	{
		WLOG_ERROR( L"Load 'd2d1.dll' failed" );
		return _false;
	}

	// Get D2D functions
	GET_FUNC_PTR( D2D, d2d1_dll, D2D1CreateFactory )

	// Create D2D factory
	D2D1_FACTORY_OPTIONS options;
	options.debugLevel = D2D1_DEBUG_LEVEL_WARNING;
	if ( FAILED( D2D::D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof( ID2D1Factory ), &options, (_void**) &mD2DFactory.GetRawRef( ) ) ) )
	{
		WLOG_ERROR( L"Create D2D1 factory failed" );
		return _false;
	}

	return _true;
}

_void D2DDrv::Finalize( )
{
}

_ubool D2DDrv::ResetResources( IApplication* application )
{
	return _true;
}

_void D2DDrv::UnloadResources( )
{
}

IResourceManagerRHI* D2DDrv::GetResourceManager( )
{
	return _null;
}

RenderStatsRHI& D2DDrv::GetRenderStats( )
{
	static RenderStatsRHI sRenderStatsRHI; 
	return sRenderStatsRHI;
}

const RenderStatsRHI& D2DDrv::GetRenderStats( ) const
{
	static RenderStatsRHI sRenderStatsRHI; 
	return sRenderStatsRHI;
}

_void D2DDrv::ClearRenderStats( )
{

}

IAllocator* D2DDrv::GetAllocator( )
{
	return _null;
}

_void D2DDrv::ClearCaches( )
{

}

_dword D2DDrv::GetRenderContextsNumber( )
{
	return 1;
}

_ubool D2DDrv::HandleEvent( EventBase& event )
{
	return _false;
}

_ubool D2DDrv::IsBlockEvent( _dword event_id, _ubool& is_async )
{
	return _false;
}

_ubool D2DDrv::IsSupportVAO( )
{
	return _false;
}

_ubool D2DDrv::IsSupportInstancedRendering( )
{
	return _false;
}

PointU D2DDrv::GetOVRFovTextureSize( _dword index )
{
	return PointU::cZeroPoint;
}

_void D2DDrv::SetOVRRenderTargetTexID( _dword index, _dword tex_id, const PointU& tex_size )
{
}

_void D2DDrv::SynOVRDeviceRegion( )
{
}

const OVREyeRHI& D2DDrv::GetOVREyeInfo( _dword index )
{
	static OVREyeRHI sGraphicOVREyeInfo; 
	return sGraphicOVREyeInfo;
}

SamplerStateRHIPassRef D2DDrv::CreateSamplerState( const SamplerStateInitializerRHI& initializer )
{
	return _null;
}

RasterizerStateRHIPassRef D2DDrv::CreateRasterizerState( const RasterizerStateInitializerRHI& initializer )
{
	return _null;
}

DepthStateRHIPassRef D2DDrv::CreateDepthState( const DepthStateInitializerRHI& initializer )
{
	return _null;
}

StencilStateRHIPassRef D2DDrv::CreateStencilState( const StencilStateInitializerRHI& initializer )
{
	return _null;
}

BlendStateRHIPassRef D2DDrv::CreateBlendState( const BlendStateInitializerRHI& initializer )
{
	return _null;
}

SamplerStateInitializerRHI D2DDrv::GetSamplerState( const SamplerStateRHI* state ) const
{
	return SamplerStateInitializerRHI( _SF_NEAREST );
}

RasterizerStateInitializerRHI D2DDrv::GetRasterizerState( const RasterizerStateRHI* state ) const
{
	return RasterizerStateInitializerRHI( _false, _false, _false, _false, _RFM_POINT, _RCM_NONE );
}

DepthStateInitializerRHI D2DDrv::GetDepthState( const DepthStateRHI* state ) const
{
	return DepthStateInitializerRHI( _false, _CF_LESS );
}

StencilStateInitializerRHI D2DDrv::GetStencilState( const StencilStateRHI* state ) const
{
	return StencilStateInitializerRHI( );
}

BlendStateInitializerRHI D2DDrv::GetBlendState( const BlendStateRHI* state ) const
{
	return BlendStateInitializerRHI( );
}

const ShaderCompileConfigInfo& D2DDrv::GetShaderCompileConfigInfo( )
{
	static ShaderCompileConfigInfo sShaderCompileConfigInfo;
	return sShaderCompileConfigInfo;
};

PixelShaderRHIPassRef D2DDrv::CreatePixelShader( AStringPtr code )
{
	return _null;
}

VertexShaderRHIPassRef D2DDrv::CreateVertexShader( AStringPtr code )
{
	return _null;
}

BoundShaderRHIPassRef D2DDrv::CreateBoundShader( VertexShaderRHI* vertexshader, PixelShaderRHI* pixelshader )
{
	return _null;
}

PixelShaderRHI* D2DDrv::GetPixelShader( BoundShaderRHI* shader ) 
{
	return _null;
}

VertexShaderRHI* D2DDrv::GetVertexShader( BoundShaderRHI* shader ) 
{
	return _null;
}

_ubool D2DDrv::GetPixelShaderCode( PixelShaderRHI* ps, AString& code )
{
	return _false;
}

_ubool D2DDrv::GetVertexShaderCode( VertexShaderRHI* vs, AString& code )
{
	return _false;
}

_dword D2DDrv::GetShaderResourceID( const BoundShaderRHI* shader ) const
{
	return 0;
}

_dword D2DDrv::ActiveUniformBuffer( BoundShaderRHI* shader, _UNIFORM_BUFFER_DATA_TYPE type, AStringPtr name, _dword size )
{
	return -1;
}

_ubool D2DDrv::UpdateUniformBuffer( BoundShaderRHI* shader, _dword location, const _void* buffer, _dword size )
{
	return _false;
}

_ubool D2DDrv::SetUniformPropertyValue( BoundShaderRHI* shader, AStringPtr name, _long value )
{
	return _false;
}

VertexDeclarationRHIPassRef D2DDrv::CreateVertexDeclaration( const VertexElementRHIArray& elements )
{
	return _null;
}

_dword D2DDrv::GetVertexDeclarationVertexType( VertexDeclarationRHI* declaration )
{
	return 0;
}

_dword D2DDrv::GetVertexDeclarationStride( VertexDeclarationRHI* declaration )
{
	return 0;
}

const VertexElementRHIArray& D2DDrv::GetVertexDeclarationDefine( VertexDeclarationRHI* declaration )
{
	static VertexElementRHIArray sNull;
	return sNull;
}

IndexBufferRHIPassRef D2DDrv::CreateIndexBuffer( _dword stride, _dword size, const _byte* buffer, _dword usage_flags, _RESOURCE_DRAW_TYPE draw_type )
{
	return _null;
}

_void* D2DDrv::LockIndexBuffer( IndexBufferRHI* indexbuffer, _dword offset, _dword size, _RESOURCE_LOCK_FLAG flag )
{
	return _null;
}

_void D2DDrv::UnlockIndexBuffer( IndexBufferRHI* indexbuffer )
{
}

_dword D2DDrv::GetIndexBufferStride( IndexBufferRHI* indexbuffer )
{
	return 0;
}

_dword D2DDrv::GetIndexBufferSize( IndexBufferRHI* indexbuffer )
{
	return 0;
}

_ubool D2DDrv::UpdateIndexBuffer( IndexBufferRHI* index_buffer, _dword offset, _dword size, const _byte* buffer, _ubool discard )
{
	return _false;
}

_ubool D2DDrv::ResizeIndexBuffer( IndexBufferRHI* index_buffer, _dword size )
{
	return _false;
}

_dword D2DDrv::GetIndexBufferResID( IndexBufferRHI* index_buffer )
{
	return 0;
}

VertexBufferRHIPassRef D2DDrv::CreateVertexBuffer( _dword stride, _dword size, const _byte* buffer, _dword usage_flags, _RESOURCE_DRAW_TYPE draw_type )
{
	return _null;
}

_void* D2DDrv::LockVertexBuffer( VertexBufferRHI* vertexbuffer, _dword offset, _dword size, _RESOURCE_LOCK_FLAG flag )
{
	return _null;
}

_void D2DDrv::UnlockVertexBuffer( VertexBufferRHI* vertexbuffer )
{
}

_dword D2DDrv::GetVertexBufferStride( VertexBufferRHI* vertexbuffer )
{
	return 0;
}

_dword D2DDrv::GetVertexBufferSize( VertexBufferRHI* vertexbuffer )
{
	return 0;
}

_ubool D2DDrv::UpdateVertexBuffer( VertexBufferRHI* vertexbuffer, _dword offset, _dword size, const _byte* buffer, _ubool discard )
{
	return _false;
}

_ubool D2DDrv::ResizeVertexBuffer( VertexBufferRHI* vertexbuffer, _dword size )
{
	return _false;
}

_dword D2DDrv::GetVertexBufferResID( VertexBufferRHI* vertexbuffer )
{
	return 0;
}