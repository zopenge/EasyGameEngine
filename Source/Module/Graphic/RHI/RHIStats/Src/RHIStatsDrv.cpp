//! @file     RHIStatsDrv.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

// Bind the assistant resource
#define BIND_ASSIST_RES( c ) resource->SetAsssistantResource( new c( resource.GetPtr( ) ) )

//----------------------------------------------------------------------------
// RHIStatsDrv Implementation
//----------------------------------------------------------------------------

RHIStatsDrv::RHIStatsDrv( IDynamicRHI* dynamic_rhi ) : mDynamicRHI( dynamic_rhi )
{
}

RHIStatsDrv::~RHIStatsDrv( )
{
}

_dword RHIStatsDrv::GetVerticesNumber( _PRIMITIVE_TYPE type, _dword number )
{
	switch ( type )
	{
		case _PT_POINT_LIST:		
			return number;

		case _PT_LINE_LIST:			
			return number * 2;

		case _PT_TRIANGLE_LIST:		
			return number * 3;

		case _PT_LINE_LOOP:			
			return number <= 2 ? number : number * 2 - 2;

		case _PT_TRIANGLE_STRIP:
		case _PT_TRIANGLE_FAN:
			return number <= 3 ? number : number + ( number - 3 ) * 2;

		default:
			return 0;
	}
}

_void RHIStatsDrv::Tick( _dword limited_elapse, _dword elapse )
{
	// Update the FPS timer
	if ( mFPSTimer.Tick( elapse ) )
	{
		mRenderStats.mFPS		= mFPSTimer.GetFPS( );
		mRenderStats.mAvgFPS	= mFPSTimer.GetAvgFPS( );
	}
}

_ubool RHIStatsDrv::Initialize( )
{
	return mDynamicRHI->Initialize( );
}

_void RHIStatsDrv::Finalize( )
{
	mDynamicRHI->Finalize( );
}

_ubool RHIStatsDrv::ResetResources( )
{
	return mDynamicRHI->ResetResources( );
}

_void RHIStatsDrv::UnloadResources( )
{
	mDynamicRHI->UnloadResources( );
}

IResourceManagerRHI* RHIStatsDrv::GetResourceManager( )
{
	return mDynamicRHI->GetResourceManager( );
}

RenderStatsRHI& RHIStatsDrv::GetRenderStats( )
{
	return mRenderStats;
}

const RenderStatsRHI& RHIStatsDrv::GetRenderStats( ) const
{
	return mRenderStats;
}

_void RHIStatsDrv::ClearRenderStats( )
{
	mRenderStats.ClearDrawingStats( );
}

_void RHIStatsDrv::ClearCaches( )
{
	mDynamicRHI->ClearCaches( );
}

_dword RHIStatsDrv::GetRenderContextsNumber( )
{
	return mDynamicRHI->GetRenderContextsNumber( );
}

_ubool RHIStatsDrv::IsSupportETC1( ) const
{
	return mDynamicRHI->IsSupportETC1( );
}

_ubool RHIStatsDrv::IsSupportETC2( ) const
{
	return mDynamicRHI->IsSupportETC2( );
}

_ubool RHIStatsDrv::IsSupportVAO( ) const
{
	return mDynamicRHI->IsSupportVAO( );
}

_ubool RHIStatsDrv::IsSupportInstancedRendering( ) const
{
	return mDynamicRHI->IsSupportInstancedRendering( );
}

_void RHIStatsDrv::SetVRRenderTargetTexID( _dword index, _dword tex_id, const PointU& tex_size )
{
	mDynamicRHI->SetVRRenderTargetTexID( index, tex_id, tex_size );
}

PointU RHIStatsDrv::GetVRTextureSize( _dword index ) const
{
	return mDynamicRHI->GetVRTextureSize( index );
}

VREyeRHI RHIStatsDrv::GetVREyeInfo( _dword index ) const
{
	return mDynamicRHI->GetVREyeInfo( index );
}

SamplerStateRHIPassRef RHIStatsDrv::CreateSamplerState( const SamplerStateInitializerRHI& initializer )
{
	return mDynamicRHI->CreateSamplerState( initializer );
}

RasterizerStateRHIPassRef RHIStatsDrv::CreateRasterizerState( const RasterizerStateInitializerRHI& initializer )
{
	return mDynamicRHI->CreateRasterizerState( initializer );
}

DepthStateRHIPassRef RHIStatsDrv::CreateDepthState( const DepthStateInitializerRHI& initializer )
{
	return mDynamicRHI->CreateDepthState( initializer );
}

StencilStateRHIPassRef RHIStatsDrv::CreateStencilState( const StencilStateInitializerRHI& initializer )
{
	return mDynamicRHI->CreateStencilState( initializer );
}

BlendStateRHIPassRef RHIStatsDrv::CreateBlendState( const BlendStateInitializerRHI& initializer )
{
	return mDynamicRHI->CreateBlendState( initializer );
}

SamplerStateInitializerRHI RHIStatsDrv::GetSamplerState( const SamplerStateRHI* state ) const
{
	return mDynamicRHI->GetSamplerState( state );
}

RasterizerStateInitializerRHI RHIStatsDrv::GetRasterizerState( const RasterizerStateRHI* state ) const
{
	return mDynamicRHI->GetRasterizerState( state );
}

DepthStateInitializerRHI RHIStatsDrv::GetDepthState( const DepthStateRHI* state ) const
{
	return mDynamicRHI->GetDepthState( state );
}

StencilStateInitializerRHI RHIStatsDrv::GetStencilState( const StencilStateRHI* state ) const
{
	return mDynamicRHI->GetStencilState( state );
}

BlendStateInitializerRHI RHIStatsDrv::GetBlendState( const BlendStateRHI* state ) const
{
	return mDynamicRHI->GetBlendState( state );
}

_ubool RHIStatsDrv::IsSameSamplerState( const SamplerStateRHI* state1, const SamplerStateRHI* state2 ) const
{
	return mDynamicRHI->IsSameSamplerState( state1, state2 );
}

_ubool RHIStatsDrv::IsSameRasterizerState( const RasterizerStateRHI* state1, const RasterizerStateRHI* state2 ) const
{
	return mDynamicRHI->IsSameRasterizerState( state1, state2 );
}

_ubool RHIStatsDrv::IsSameDepthState( const DepthStateRHI* state1, const DepthStateRHI* state2 ) const
{
	return mDynamicRHI->IsSameDepthState( state1, state2 );
}

_ubool RHIStatsDrv::IsSameStencilState( const StencilStateRHI* state1, const StencilStateRHI* state2 ) const
{
	return mDynamicRHI->IsSameStencilState( state1, state2 );
}

_ubool RHIStatsDrv::IsSameBlendState( const BlendStateRHI* state1, const BlendStateRHI* state2 ) const
{
	return mDynamicRHI->IsSameBlendState( state1, state2 );
}

PixelShaderRHIPassRef RHIStatsDrv::CreatePixelShader( AStringPtr code )
{
	PixelShaderRHIPassRef resource = mDynamicRHI->CreatePixelShader( code );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsPixelShader );

	return resource;
}

VertexShaderRHIPassRef RHIStatsDrv::CreateVertexShader( AStringPtr code )
{
	VertexShaderRHIPassRef resource = mDynamicRHI->CreateVertexShader( code );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsVertexShader );

	return resource;
}

BoundShaderRHIPassRef RHIStatsDrv::CreateBoundShader( VertexShaderRHI* vertexshader, PixelShaderRHI* pixelshader )
{
	BoundShaderRHIPassRef resource = mDynamicRHI->CreateBoundShader( vertexshader, pixelshader );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsBoundShader );

	return resource;
}

PixelShaderRHI* RHIStatsDrv::GetPixelShader( BoundShaderRHI* shader ) 
{
	return mDynamicRHI->GetPixelShader( shader );
}

VertexShaderRHI* RHIStatsDrv::GetVertexShader( BoundShaderRHI* shader ) 
{
	return mDynamicRHI->GetVertexShader( shader );
}

const AStringObj& RHIStatsDrv::GetPixelShaderCode( BoundShaderRHI* shader )
{
	return mDynamicRHI->GetPixelShaderCode( shader );
}

const AStringObj& RHIStatsDrv::GetVertexShaderCode( BoundShaderRHI* shader )
{
	return mDynamicRHI->GetVertexShaderCode( shader );
}

_dword RHIStatsDrv::GetShaderResourceID( const BoundShaderRHI* shader ) const
{
	return mDynamicRHI->GetShaderResourceID( shader );
}

VertexDeclarationRHIPassRef RHIStatsDrv::CreateVertexDeclaration( const VertexElementRHIArray& elements )
{
	VertexDeclarationRHIPassRef resource = mDynamicRHI->CreateVertexDeclaration( elements );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsVertexDeclaration );

	return resource;
}

_dword RHIStatsDrv::GetVertexDeclarationVertexType( VertexDeclarationRHI* declaration )
{
	return mDynamicRHI->GetVertexDeclarationVertexType( declaration );
}

_dword RHIStatsDrv::GetVertexDeclarationStride( VertexDeclarationRHI* declaration )
{
	return mDynamicRHI->GetVertexDeclarationStride( declaration );
}

const VertexElementRHIArray& RHIStatsDrv::GetVertexDeclarationDefine( VertexDeclarationRHI* declaration )
{
	return mDynamicRHI->GetVertexDeclarationDefine( declaration );
}

_dword RHIStatsDrv::GetUniformBufferLocation( BoundShaderRHI* shader, AStringPtr name )
{
	return mDynamicRHI->GetUniformBufferLocation( shader, name );
}

_dword RHIStatsDrv::ActiveUniformBuffer( BoundShaderRHI* shader, _UNIFORM_BUFFER_DATA_TYPE type, const AStringObj& name, _dword size )
{
	return mDynamicRHI->ActiveUniformBuffer( shader, type, name, size );
}

_ubool RHIStatsDrv::UpdateUniformBuffer( BoundShaderRHI* shader, _dword location, const _void* buffer, _dword size )
{
	mRenderStats.mAPICallInfo.mUBOUpdateNumber ++;

	return mDynamicRHI->UpdateUniformBuffer( shader, location, buffer, size );
}

_ubool RHIStatsDrv::SetUniformPropertyValue( BoundShaderRHI* shader, AStringPtr name, _int value )
{
	mRenderStats.mAPICallInfo.mUBOUpdateNumber ++;

	return mDynamicRHI->SetUniformPropertyValue( shader, name, value );
}

IndexBufferRHIPassRef RHIStatsDrv::CreateIndexBuffer( _dword stride, _dword size, const _byte* buffer, _RESOURCE_DRAW_TYPE draw_type )
{
	IndexBufferRHIPassRef resource = mDynamicRHI->CreateIndexBuffer( stride, size, buffer, draw_type );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsIndexBuffer );

	return resource;
}

_byte* RHIStatsDrv::LockIndexBuffer( IndexBufferRHI* indexbuffer, _dword offset, _dword size )
{
	return mDynamicRHI->LockIndexBuffer( indexbuffer, offset, size );
}

_void RHIStatsDrv::UnlockIndexBuffer( IndexBufferRHI* indexbuffer )
{
	mDynamicRHI->UnlockIndexBuffer( indexbuffer );
}

const _byte* RHIStatsDrv::GetIndexBufferData( IndexBufferRHI* indexbuffer )
{
	return mDynamicRHI->GetIndexBufferData( indexbuffer );
}

_dword RHIStatsDrv::GetIndexBufferStride( IndexBufferRHI* indexbuffer )
{
	return mDynamicRHI->GetIndexBufferStride( indexbuffer );
}

_dword RHIStatsDrv::GetIndexBufferSize( IndexBufferRHI* indexbuffer )
{
	return mDynamicRHI->GetIndexBufferSize( indexbuffer );
}

_ubool RHIStatsDrv::UpdateIndexBuffer( IndexBufferRHI* index_buffer, _dword offset, _dword size, const _byte* buffer )
{
	return mDynamicRHI->UpdateIndexBuffer( index_buffer, offset, size, buffer );
}

_ubool RHIStatsDrv::ResizeIndexBuffer( IndexBufferRHI* index_buffer, _dword size )
{
	mRenderStats.mTotalMemorySize -= mDynamicRHI->GetIndexBufferSize( index_buffer );
	mRenderStats.mTotalMemorySize += size;

	return mDynamicRHI->ResizeIndexBuffer( index_buffer, size );
}

_ubool RHIStatsDrv::FlushIndexBuffer( IndexBufferRHI* index_buffer )
{
	mRenderStats.mAPICallInfo.mIBFlushNumber ++;

	return mDynamicRHI->FlushIndexBuffer( index_buffer );
}

_dword RHIStatsDrv::GetIndexBufferResID( IndexBufferRHI* index_buffer )
{
	return mDynamicRHI->GetIndexBufferResID( index_buffer );
}

VertexBufferRHIPassRef RHIStatsDrv::CreateVertexBuffer( _dword stride, _dword size, const _byte* buffer, _RESOURCE_DRAW_TYPE draw_type )
{
	VertexBufferRHIPassRef resource = mDynamicRHI->CreateVertexBuffer( stride, size, buffer, draw_type );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsVertexBuffer );

	return resource;
}

_byte* RHIStatsDrv::LockVertexBuffer( VertexBufferRHI* vertexbuffer, _dword offset, _dword size )
{
	return mDynamicRHI->LockVertexBuffer( vertexbuffer, offset, size );
}

_void RHIStatsDrv::UnlockVertexBuffer( VertexBufferRHI* vertexbuffer )
{
	mDynamicRHI->UnlockVertexBuffer( vertexbuffer );
}

const _byte* RHIStatsDrv::GetVertexBufferData( VertexBufferRHI* vertexbuffer )
{
	return mDynamicRHI->GetVertexBufferData( vertexbuffer );
}

_dword RHIStatsDrv::GetVertexBufferStride( VertexBufferRHI* vertexbuffer )
{
	return mDynamicRHI->GetVertexBufferStride( vertexbuffer );
}

_dword RHIStatsDrv::GetVertexBufferSize( VertexBufferRHI* vertexbuffer )
{
	return mDynamicRHI->GetVertexBufferSize( vertexbuffer );
}

_ubool RHIStatsDrv::UpdateVertexBuffer( VertexBufferRHI* vertexbuffer, _dword offset, _dword size, const _byte* buffer )
{
	return mDynamicRHI->UpdateVertexBuffer( vertexbuffer, offset, size, buffer );
}

_ubool RHIStatsDrv::ResizeVertexBuffer( VertexBufferRHI* vertexbuffer, _dword size )
{
	mRenderStats.mTotalMemorySize -= mDynamicRHI->GetVertexBufferSize( vertexbuffer );
	mRenderStats.mTotalMemorySize += size;

	return mDynamicRHI->ResizeVertexBuffer( vertexbuffer, size );
}

_ubool RHIStatsDrv::FlushVertexBuffer( VertexBufferRHI* vertex_buffer )
{
	mRenderStats.mAPICallInfo.mVBFlushNumber ++;

	return mDynamicRHI->FlushVertexBuffer( vertex_buffer );
}

_dword RHIStatsDrv::GetVertexBufferResID( VertexBufferRHI* vertexbuffer )
{
	return mDynamicRHI->GetVertexBufferResID( vertexbuffer );
}

VertexArrayRHIPassRef RHIStatsDrv::CreateVertexArray( )
{
	return mDynamicRHI->CreateVertexArray( );
}

_void RHIStatsDrv::BindVertexArray( VertexArrayRHI* vertex_array )
{
	mDynamicRHI->BindVertexArray( vertex_array );
}

_void RHIStatsDrv::UnbindVertexArray( )
{
	mDynamicRHI->UnbindVertexArray( );
}

_ubool RHIStatsDrv::SetVertexArrayDecl( VertexArrayRHI* vertex_array, VertexDeclarationRHI* declaration, VertexBufferRHI* vbo, IndexBufferRHI* ibo )
{
	return mDynamicRHI->SetVertexArrayDecl( vertex_array, declaration, vbo, ibo );
}

_dword RHIStatsDrv::GetVertexArrayResID( VertexArrayRHI* vertex_array )
{
	return mDynamicRHI->GetVertexArrayResID( vertex_array );
}

const GPUTextureInfoRHI& RHIStatsDrv::GetGPUTextureInfo( )
{
	return mDynamicRHI->GetGPUTextureInfo( );
}

TextureCubeRHIPassRef RHIStatsDrv::CreateTextureCube( WStringPtr res_name, _dword nummips, const TextureCubeWithMipmapsRHI& mipmaps_info )
{
	TextureCubeRHIPassRef resource = mDynamicRHI->CreateTextureCube( res_name, nummips, mipmaps_info );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsTextureCube );

	return resource;
}

TextureCubeRHIPassRef RHIStatsDrv::CreateTextureCubeWithMipmaps( WStringPtr res_name, _dword nummips, const TextureCubeWithMipmapsRHI* mipmaps_info )
{
	TextureCubeRHIPassRef resource = mDynamicRHI->CreateTextureCubeWithMipmaps( res_name, nummips, mipmaps_info );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsTextureCube );

	return resource;
}

const PointU& RHIStatsDrv::GetTextureCubeSize( TextureCubeRHI* texture ) const
{
	return mDynamicRHI->GetTextureCubeSize( texture );
}

_dword RHIStatsDrv::GetTextureCubeSizeInBytes( TextureCubeRHI* texture ) const
{
	return mDynamicRHI->GetTextureCubeSizeInBytes( texture );
}

_dword RHIStatsDrv::GetTextureCubeMipNumber( const TextureCubeRHI* texture ) const
{
	return mDynamicRHI->GetTextureCubeMipNumber( texture );
}

Texture2DRHIPassRef RHIStatsDrv::CreateTexture2D( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, const _byte* pixel, _ubool is_dynamic )
{
	Texture2DRHIPassRef resource = mDynamicRHI->CreateTexture2D( res_name, width, height, format, nummips, pixel, is_dynamic );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsTexture2D );

	return resource;
}

Texture2DRHIPassRef RHIStatsDrv::CreateTexture2DFromImageFile( WStringPtr res_name, IImageFile* image_file, _dword nummips )
{
	Texture2DRHIPassRef resource = mDynamicRHI->CreateTexture2DFromImageFile( res_name, image_file, nummips );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsTexture2D );

	return resource;
}

Texture2DRHIPassRef RHIStatsDrv::CreateTexture2DWithMipmaps( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, const _byte** pixels )
{
	Texture2DRHIPassRef resource = mDynamicRHI->CreateTexture2DWithMipmaps( res_name, width, height, format, nummips, pixels );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsTexture2D );

	return resource;
}

_ubool RHIStatsDrv::UpdateTexture2D( Texture2DRHI* texture, const RectU& rect, const _byte* pixel )
{
	return mDynamicRHI->UpdateTexture2D( texture, rect, pixel );
}

_ubool RHIStatsDrv::ReadTexture2DMipPixel( const Texture2DRHI* texture, _byte* pixel_buffer )
{
	return mDynamicRHI->ReadTexture2DMipPixel( texture, pixel_buffer );
}

_dword RHIStatsDrv::GetTexture2DResID( const Texture2DRHI* texture ) const
{
	return mDynamicRHI->GetTexture2DResID( texture );
}

const PointU& RHIStatsDrv::GetTexture2DSize( const Texture2DRHI* texture ) const
{
	return mDynamicRHI->GetTexture2DSize( texture );
}

_dword RHIStatsDrv::GetTexture2DMipNumber( const Texture2DRHI* texture ) const
{
	return mDynamicRHI->GetTexture2DMipNumber( texture );
}

_dword RHIStatsDrv::GetTexture2DMipSize( const Texture2DRHI* texture, _dword mipindex ) const
{
	return mDynamicRHI->GetTexture2DMipSize( texture, mipindex );
}

_dword RHIStatsDrv::GetTexture2DStride( const Texture2DRHI* texture, _dword mipindex ) const
{
	return mDynamicRHI->GetTexture2DStride( texture, mipindex );
}

_ubool RHIStatsDrv::IsTexture2DDynamic( const Texture2DRHI* texture ) const
{
	return mDynamicRHI->IsTexture2DDynamic( texture );
}

_PIXEL_FORMAT RHIStatsDrv::GetTexture2DPixelFormat( const Texture2DRHI* texture ) const
{
	return mDynamicRHI->GetTexture2DPixelFormat( texture );
}

_dword RHIStatsDrv::GetTexture2DSizeInBytes( Texture2DRHI* texture ) const
{
	return mDynamicRHI->GetTexture2DSizeInBytes( texture );
}

SamplerStateInitializerRHI RHIStatsDrv::GetTexture2DSamplerStateInfo( Texture2DRHI* texture ) const
{
	return mDynamicRHI->GetTexture2DSamplerStateInfo( texture );
}

_void RHIStatsDrv::LockTexture2DSamplerState( Texture2DRHI* texture, _ubool lock )
{
	return mDynamicRHI->LockTexture2DSamplerState( texture, lock );
}

_ubool RHIStatsDrv::IsTexture2DCompressed( Texture2DRHI* texture ) const
{
	return mDynamicRHI->IsTexture2DCompressed( texture );
}

FontRHIPassRef RHIStatsDrv::CreateFontFromStream( const FontInitializerRHI& initializer, IStreamReader* stream_reader )
{
	FontRHIPassRef resource = mDynamicRHI->CreateFontFromStream( initializer, stream_reader );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsFont );

	return resource;
}

const FontInitializerRHI& RHIStatsDrv::GetFontInfo( FontRHI* font ) const
{
	return mDynamicRHI->GetFontInfo( font );
}

_float RHIStatsDrv::GetCharAdvance( FontRHI* font, _dword code ) const
{
	return mDynamicRHI->GetCharAdvance( font, code );
}

_float RHIStatsDrv::GetCharMaxHeight( FontRHI* font ) const
{
	return mDynamicRHI->GetCharMaxHeight( font );
}

IFontFace* RHIStatsDrv::GetFontFace( FontRHI* font ) const
{
	return mDynamicRHI->GetFontFace( font );
}

const FontCodeRHI* RHIStatsDrv::GetFontCode( FontRHI* font, _dword code ) const
{
	return mDynamicRHI->GetFontCode( font, code );
}

const FontCodeRHI* RHIStatsDrv::GetFontCodeByStrokeEffect( FontRHI* font, _dword code, _dword stroke_size ) const
{
	return mDynamicRHI->GetFontCodeByStrokeEffect( font, code, stroke_size );
}

const FontCodeRHI* RHIStatsDrv::GetFontCodeByBlurEffect( FontRHI* font, _dword code, _dword blur_size, _dword blur_factor ) const
{
	return mDynamicRHI->GetFontCodeByBlurEffect( font, code, blur_size, blur_factor );
}

_void RHIStatsDrv::ClearFontCaches( FontRHI* font )
{
	mDynamicRHI->ClearFontCaches( font );
}

SurfaceRHIPassRef RHIStatsDrv::CreateTargetableSurface( Texture2DRHI* texture )
{
	SurfaceRHIPassRef resource = mDynamicRHI->CreateTargetableSurface( texture );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsSurface );

	return resource;
}

SurfaceRHIPassRef RHIStatsDrv::CreateTargetableSurface( TextureCubeRHI* texture )
{
	SurfaceRHIPassRef resource = mDynamicRHI->CreateTargetableSurface( texture );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsSurface );

	return resource;
}

SurfaceRHIPassRef RHIStatsDrv::CreateTargetableSurface( _dword width, _dword height, _PIXEL_FORMAT format )
{
	SurfaceRHIPassRef resource = mDynamicRHI->CreateTargetableSurface( width, height, format );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsSurface );

	return resource;
}

const PointU& RHIStatsDrv::GetSurfaceSize( SurfaceRHI* surface ) const
{
	return mDynamicRHI->GetSurfaceSize( surface );
}

Texture2DRHI* RHIStatsDrv::GetSurfaceTexture2D( SurfaceRHI* surface ) const
{
	return mDynamicRHI->GetSurfaceTexture2D( surface );
}

TextureCubeRHI* RHIStatsDrv::GetSurfaceTextureCube( SurfaceRHI* surface ) const
{
	return mDynamicRHI->GetSurfaceTextureCube( surface );
}

_ubool RHIStatsDrv::SetSurfaceTextureCubeFaceIndex( SurfaceRHI* surface, _dword index )
{
	return mDynamicRHI->SetSurfaceTextureCubeFaceIndex( surface, index );
}

_dword RHIStatsDrv::GetSurfaceTextureCubeFaceIndex( SurfaceRHI* surface ) const
{
	return mDynamicRHI->GetSurfaceTextureCubeFaceIndex( surface );
}

ViewportRHIPassRef RHIStatsDrv::CreateViewport( _handle app_handle, const PointU& size )
{
	ViewportRHIPassRef resource = mDynamicRHI->CreateViewport( app_handle, size );
	if ( resource.IsNull( ) )
		return _null;

	BIND_ASSIST_RES( RHIStatsViewport );

	return resource;
}

_ubool RHIStatsDrv::ResizeViewport( ViewportRHI* viewport, const PointU& size )
{
	return mDynamicRHI->ResizeViewport( viewport, size );
}

const PointU& RHIStatsDrv::GetViewportSize( ViewportRHI* viewport ) const
{
	return mDynamicRHI->GetViewportSize( viewport );
}

_void RHIStatsDrv::SetLineWidth( _float width )
{
	mDynamicRHI->SetLineWidth( width );
}

_void RHIStatsDrv::SetRenderTarget( SurfaceRHI* rendertarget, SurfaceRHI* depthstencil )
{
	mDynamicRHI->SetRenderTarget( rendertarget, depthstencil );
}

_void RHIStatsDrv::ReadPixels( const RectU& rect, _PIXEL_FORMAT format, _byte* pixels )
{
	mDynamicRHI->ReadPixels( rect, format, pixels );
}

_void RHIStatsDrv::SetBoundShader( BoundShaderRHI* shader )
{
	mDynamicRHI->SetBoundShader( shader );
}

_void RHIStatsDrv::SetDepthState( const DepthStateRHI* state )
{
	mDynamicRHI->SetDepthState( state );
}
 
_void RHIStatsDrv::SetStencilState( const StencilStateRHI* state )
{
	mDynamicRHI->SetStencilState( state );
}

_void RHIStatsDrv::SetBlendState( const BlendStateRHI* state )
{
	mDynamicRHI->SetBlendState( state );
}
 
_void RHIStatsDrv::SetRasterizerState( const RasterizerStateRHI* state )
{
	mDynamicRHI->SetRasterizerState( state );
}

_void RHIStatsDrv::SetRasterizerStateImmediate( const RasterizerStateInitializerRHI& initializer )
{
	mDynamicRHI->SetRasterizerStateImmediate( initializer );
}

_void RHIStatsDrv::SetSamplerState( _dword samplerindex, const SamplerStateRHI* state, Texture2DRHI* texture )
{
	mDynamicRHI->SetSamplerState( samplerindex, state, texture );
}

_void RHIStatsDrv::SetSamplerState( _dword samplerindex, const SamplerStateRHI* state, TextureCubeRHI* texture )
{
	mDynamicRHI->SetSamplerState( samplerindex, state, texture );
}

_void RHIStatsDrv::SetViewport( const Viewport& viewport )
{
	mDynamicRHI->SetViewport( viewport );
}

_void RHIStatsDrv::BindViewport( ViewportRHI* viewport )
{
	mDynamicRHI->BindViewport( viewport );
}

_void RHIStatsDrv::Present( ViewportRHI* viewport )
{
	// Reset the GL API call counter
#if (_DISABLE_GL_API_CALL_COUNTER == 0)
	mRenderStats.mAPICallInfo.mAPICallNumber = gGLAPICallCounter;
#endif

	mDynamicRHI->Present( viewport );
}

_void RHIStatsDrv::ClearBuffers( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil )
{
	mDynamicRHI->ClearBuffers( clearcolor, color, cleardepth, depth, clearstencil, stencil );
}

_void RHIStatsDrv::DrawPoint( const Vector2& position, const Color& color )
{
	mDynamicRHI->DrawPoint( position, color );
}

_void RHIStatsDrv::DrawLine( const Vector2& start, const Vector2& end, const Color& color, _float width )
{
	mDynamicRHI->DrawLine( start, end, color, width );
}

_void RHIStatsDrv::DrawLine( const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width )
{
	mDynamicRHI->DrawLine( start, end, color_start, color_end, width );
}

_void RHIStatsDrv::DrawRectangle( const RectI& rect, const Color& color, _dword width )
{
	mDynamicRHI->DrawRectangle( rect, color, width );
}

_void RHIStatsDrv::DrawRectangle( const RectF& rect, const Color& color, _float width )
{
	mDynamicRHI->DrawRectangle( rect, color, width );
}

_void RHIStatsDrv::FillRectangle( const RectI& rect, const Color& color )
{
	mDynamicRHI->FillRectangle( rect, color );
}

_void RHIStatsDrv::FillRectangle( const RectF& rect, const Color& color )
{
	mDynamicRHI->FillRectangle( rect, color );
}

_void RHIStatsDrv::DrawSprite( const Vector2& position, const Vector2& size, Texture2DRHI* texture, const Color& color, const Vector2& uv1, const Vector2& uv2, _ubool is_rotate, _ubool is_round )
{
	mDynamicRHI->DrawSprite( position, size, texture, color, uv1, uv2, is_rotate, is_round );
}

_void RHIStatsDrv::DrawText( _dword alignment, const RectF& rect, WStringPtr string, FontRHI* font, const Color& color )
{
	mDynamicRHI->DrawText( alignment, rect, string, font, color );
}

_void RHIStatsDrv::DrawPrimitive( _PRIMITIVE_TYPE type, _dword offset, _dword number )
{
	mRenderStats.mAPICallInfo.mDPNumber ++;
	mRenderStats.mVerticesNumber += GetVerticesNumber( type, number );

	mDynamicRHI->DrawPrimitive( type, offset, number );
}

_void RHIStatsDrv::DrawIndexedPrimitive( _PRIMITIVE_TYPE type, _dword start_index, _dword number )
{
	mRenderStats.mAPICallInfo.mDPNumber ++;
	mRenderStats.mVerticesNumber += GetVerticesNumber( type, number );

	mDynamicRHI->DrawIndexedPrimitive( type, start_index, number );
}
