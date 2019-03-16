//! @file     GraphicResourceManager.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicResourceManager Implementation
//----------------------------------------------------------------------------

GraphicResourceManager::GraphicResourceManager( )
{
	mAppHandle	= _null;
}

GraphicResourceManager::~GraphicResourceManager( )
{
	Finalize( );
}

_void GraphicResourceManager::CleanupFonts( )
{
	for ( _dword i = 0; i < mGraphicFonts.Number( ); i ++ )
	{
		IGraphicFont* font = mGraphicFonts[i];
		EGE_ASSERT( font != _null );

		// Remove font if it's released
		if ( font->GetRefCount( ) == 1 )
			mGraphicFonts.RemoveByIndex( i -- );
	}
}

_ubool GraphicResourceManager::CreateSurfaces( IGraphicSurfaceRef& render_target, IGraphicSurfaceRef& depth_stencil, _dword width, _dword height, _dword flags )
{
	if ( flags & _GRAPHIC_SURFACE_RENDER_TARGET )
	{
		render_target = CreateRenderTarget( width, height );
		if ( render_target.IsNull( ) )
			return _false;
	}

	if ( flags & _GRAPHIC_SURFACE_DEPTH_STENCIL )
	{
		depth_stencil = CreateDepthStencil( width, height );
		if ( depth_stencil.IsNull( ) )
			return _false;
	}

	return _true;
}

AStringR GraphicResourceManager::LoadShaderCodeByNode( ISerializableNode* node )
{
	if ( node == _null )
		return "";

	WString res_name;
	node->Read( L"name", res_name );

	AString code = LoadShaderCodeByResName( res_name );
	if ( code.IsEmpty( ) )
		return "";

	return code;
}

AStringR GraphicResourceManager::LoadShaderCodeByResName( WStringPtr res_name )
{
	IStreamReaderRef stream_reader = GetWorkingArchive( )->LoadResourceByName( res_name );
	if ( stream_reader.IsNull( ) )
		return "";

	AString shader_code( (const _chara*)stream_reader->GetBuffer( ), stream_reader->GetSize( ) );

	return ParseShaderCode( shader_code );
}

AStringR GraphicResourceManager::ParseShaderCode( AStringPtr code )
{
	ShaderParser parser;
	if ( parser.Load( code ) == _false )
		return "";

	return parser.GetShaderCode( );
}

_ubool GraphicResourceManager::CheckTextureCubeImageSize( _dword nummips, const TextureCubeWithMipmapsRHI* mipmaps ) const
{
	// Get image files
	for ( _dword mipindex = 0; mipindex < nummips; mipindex ++ )
	{
		const TextureCubeWithMipmapsRHI& mipmap_info = mipmaps[mipindex];

		if ( mipmap_info.IsImageSizeValid( ) == _false )
			return _false;
	}

	return _true;
}

_void GraphicResourceManager::RotateTextureCubeImage( _CUBE_TEX_SUBFACE_TYPE type, IImageFile* image_file )
{
	switch ( type )
	{
		case _CUBE_TEX_SUBFACE_POS_X:
			image_file->Rotate( IImageFile::_CLOCKWISE_270 );
			break;

		case _CUBE_TEX_SUBFACE_NEG_X:
		case _CUBE_TEX_SUBFACE_POS_Z:
		case _CUBE_TEX_SUBFACE_NEG_Z:
			image_file->Rotate( IImageFile::_CLOCKWISE_90 );
			break;

		case _CUBE_TEX_SUBFACE_POS_Y:
			image_file->Rotate( IImageFile::_CLOCKWISE_180 );
			break;

		case _CUBE_TEX_SUBFACE_NEG_Y:
			break;

		default:
			break;
	}
}

_ubool GraphicResourceManager::Initialize( _handle app_handle )
{
	WLOG_TRACE( L"Initialize graphic resource manager ..." );

	mAppHandle = app_handle;

	WLOG_TRACE( L"Initialize graphic resource manager OK" );

	return _true;
}

_void GraphicResourceManager::Finalize( )
{
	mSamplerStates.Clear( );
	mRasterizerStates.Clear( );
	mDepthStates.Clear( );
	mBlendStates.Clear( );
	mStencilStates.Clear( );

	mVShaders.Clear( );
	mPShaders.Clear( );
	mBoundShaders.Clear( );

	mGraphicFonts.Clear( _true );
}

_void GraphicResourceManager::ClearCaches( )
{
	CleanupFonts( );

	for ( _dword i = 0; i < mGraphicFonts.Number( ); i ++ )
		mGraphicFonts[i]->ClearCaches( );
}

SamplerStateRHIRef GraphicResourceManager::GetSamplerStateFromResName( const WStringObj& res_name )
{
	SamplerStateRHIRef& state = mSamplerStates[res_name];
	if ( state.IsNull( ) )
	{
		ISerializableNodeRef node = GetWorkingArchive( )->LoadSerializableNodeByName( res_name, _true );
		if ( node.IsNull( ) )
			return _null;

		SamplerStateInitializerRHI info( _SF_NEAREST );
		node->ReadEnum( L"filter", info.mFilter, _false, OnQueryEnumSamplerFilterEnumCallback );
		node->ReadEnum( L"address_u", info.mAddressU, _false, OnQueryEnumSamplerAddressModeEnumCallback );
		node->ReadEnum( L"address_v", info.mAddressV, _false, OnQueryEnumSamplerAddressModeEnumCallback );
		node->ReadEnum( L"address_w", info.mAddressW, _false, OnQueryEnumSamplerAddressModeEnumCallback );

		state = gDynamicRHI->CreateSamplerState( info );
	}

	return state;
}

RasterizerStateRHIRef GraphicResourceManager::GetRasterizerStateFromResName( const WStringObj& res_name )
{
	RasterizerStateRHIRef& state = mRasterizerStates[res_name];
	if ( state.IsNull( ) )
	{
		ISerializableNodeRef node = GetWorkingArchive( )->LoadSerializableNodeByName( res_name, _true );
		if ( node.IsNull( ) )
			return _null;

		RasterizerStateInitializerRHI info( _RFM_SOLID, _RCM_NONE );
		node->Read( L"enable_red_color_write", info.mEnableRedColorWrite );
		node->Read( L"enable_green_color_write", info.mEnableGreenColorWrite );
		node->Read( L"enable_blue_color_write", info.mEnableBlueColorWrite );
		node->Read( L"enable_alpha_color_write", info.mEnableAlphaColorWrite );
		node->ReadEnum( L"fill_mode", info.mFillMode, _false,  OnQueryEnumRasterizerFillModeEnumCallback );
		node->ReadEnum( L"cull_mode", info.mCullMode, _false, OnQueryEnumRasterizerCullModeEnumCallback );

		state = gDynamicRHI->CreateRasterizerState( info );
	}

	return state;
}

DepthStateRHIRef GraphicResourceManager::GetDepthStateFromResName( const WStringObj& res_name )
{
	return _null;
}

BlendStateRHIRef GraphicResourceManager::GetBlendStateFromResName( const WStringObj& res_name )
{
	BlendStateRHIRef& state = mBlendStates[res_name];
	if ( state.IsNull( ) )
	{
		ISerializableNodeRef node = GetWorkingArchive( )->LoadSerializableNodeByName( res_name, _true );
		if ( node.IsNull( ) )
			return _null;

		BlendStateInitializerRHI info;
		node->Read( L"enable", info.mEnableBlend );
		node->ReadEnum( L"color_src_factor", info.mColorSourceBlendFactor, _false, OnQueryEnumBlendFactorEnumCallback );
		node->ReadEnum( L"color_dst_factor", info.mColorDestBlendFactor, _false, OnQueryEnumBlendFactorEnumCallback );
		node->ReadEnum( L"alpha_src_factor", info.mAlphaSourceBlendFactor, _false, OnQueryEnumBlendFactorEnumCallback );
		node->ReadEnum( L"alpha_dst_factor", info.mAlphaDestBlendFactor, _false, OnQueryEnumBlendFactorEnumCallback );

		state = gDynamicRHI->CreateBlendState( info );
	}

	return state;
}

StencilStateRHIRef GraphicResourceManager::GetStencilStateFromResName( const WStringObj& res_name )
{
	return _null;
}

IGraphicVertexDeclarationPassRef GraphicResourceManager::CreateVertexDeclaration( const VertexElementRHIArray& elements )
{
	return CreateVertexDeclaration( gDynamicRHI->CreateVertexDeclaration( elements ).GetPtr( ) );
}

IGraphicVertexDeclarationPassRef GraphicResourceManager::CreateVertexDeclaration( VertexDeclarationRHI* vertex_decl )
{
	if ( vertex_decl == _null )
		return _null;

	GraphicVertexDeclaration* decl = new GraphicVertexDeclaration( );
	if ( decl->Initialize( vertex_decl ) == _false )
		{ EGE_RELEASE( decl ); return _null; }

	return decl;
}

IGraphicVertexDeclarationPassRef GraphicResourceManager::CreateVertexDeclaration( _dword vertex_type )
{
	GraphicVertexDeclaration* decl = new GraphicVertexDeclaration( );
	if ( decl->Initialize( vertex_type ) == _false )
		{ EGE_RELEASE( decl ); return _null; }

	return decl;
}

IGraphicIndexBufferPassRef GraphicResourceManager::CreateIndexBuffer( IndexBufferRHI* index_buffer )
{
	return new GraphicIndexBuffer( index_buffer );
}

IGraphicVertexBufferPassRef GraphicResourceManager::CreateVertexBuffer( VertexBufferRHI* vertex_buffer )
{
	return new GraphicVertexBuffer( vertex_buffer );
}

IGraphicVertexArrayPassRef GraphicResourceManager::CreateVertexArray( _RESOURCE_DRAW_TYPE draw_type, VertexDeclarationRHI* vertex_decl )
{
	GraphicVertexArray* vertex_array = new GraphicVertexArray( );
	if ( vertex_array->Initialize( draw_type, vertex_decl ) == _false )
		{ EGE_RELEASE( vertex_array ); return _null; }

	return vertex_array;
}

IGraphicTexture2DPassRef GraphicResourceManager::CreateTexture2D( Texture2DRHI* resource )
{
	if ( resource == _null )
		return _null;

	return new GraphicTexture2D( resource );
}

IGraphicTexture2DPassRef GraphicResourceManager::CreateTexture2DFromStream( WStringPtr res_name, IStreamReader* stream_reader, _dword nummips )
{
	IImageFileRef imagefile( GetInterfaceFactory( )->ParseImageFile( stream_reader ) );
	if ( imagefile.IsNull( ) )
		return _null;

	return CreateTexture2DFromImageFile( res_name, imagefile, nummips );
}

IGraphicTexture2DPassRef GraphicResourceManager::CreateTexture2DFromImageFile( WStringPtr res_name, IImageFile* imagefile, _dword nummips )
{
	if ( imagefile == _null )
		return _null;

	// Create RHI texture resource
	Texture2DRHIRef texture_resource = gDynamicRHI->CreateTexture2DFromImageFile( res_name, imagefile, nummips );
	if ( texture_resource.IsNull( ) )
		return _null;

	return new GraphicTexture2D( texture_resource );
}

IGraphicTexture2DPassRef GraphicResourceManager::CreateTexture2DWithMipmaps( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, const _byte** pixels )
{
	if ( width == 0 || height == 0 )
		return _null;

	// Create RHI texture resource
	Texture2DRHIRef texture_resource = gDynamicRHI->CreateTexture2DWithMipmaps( res_name, width, height, format, nummips, pixels );
	if ( texture_resource.IsNull( ) )
		return _null;

	return new GraphicTexture2D( texture_resource );
}

IGraphicTexture2DPassRef GraphicResourceManager::CreateTexture2D( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, const _byte* pixelbuffer, _ubool is_dynamic )
{
	if ( width == 0 || height == 0 )
		return _null;

	// Create RHI texture resource
	Texture2DRHIRef texture_resource = gDynamicRHI->CreateTexture2D( res_name, width, height, format, nummips, pixelbuffer, is_dynamic );
	if ( texture_resource.IsNull( ) )
		return _null;

	return new GraphicTexture2D( texture_resource );
}

IGraphicTexture2DPassRef GraphicResourceManager::CreateSubTexture2D( const Vector2& uv1, const Vector2& uv2, IGraphicTexture2D* texture )
{
	if ( texture == _null )
		return _null;

	GraphicSubTexture2D* sub_tex = new GraphicSubTexture2D( uv1, uv2, texture );
	if ( sub_tex->Initialize( ) == _false )
		{ EGE_RELEASE( sub_tex ); return _null; }

	return sub_tex;
}

IGraphicTextureCubePassRef GraphicResourceManager::CreateTextureCube( TextureCubeRHI* resource )
{
	if ( resource == _null )
		return _null;

	return new GraphicTextureCube( resource );
}

IGraphicTextureCubePassRef GraphicResourceManager::CreateTextureCube( WStringPtr res_name, _dword nummips, const TextureCubeWithMipmapsRHI& mipmaps_info )
{
	// Create RHI texture resource
	TextureCubeRHIRef texture_resource = gDynamicRHI->CreateTextureCube( res_name, nummips, mipmaps_info );
	if ( texture_resource.IsNull( ) )
		return _null;

	return new GraphicTextureCube( texture_resource );
}

IGraphicTextureCubePassRef GraphicResourceManager::CreateTextureCubeWithMipmaps( WStringPtr res_name, _dword nummips, const TextureCubeWithMipmapsRHI* mipmaps_info )
{
	if ( mipmaps_info == _null )
		return _null;

	// Create RHI texture resource
	TextureCubeRHIRef texture_resource = gDynamicRHI->CreateTextureCubeWithMipmaps( res_name, nummips, mipmaps_info );
	if ( texture_resource.IsNull( ) )
		return _null;

	return new GraphicTextureCube( texture_resource );
}

IGraphicTexture2DSetPassRef GraphicResourceManager::CreateTexture2DSet( const PointU& size, const PointU& space )
{
	GraphicTexture2DSet* texture_set = new GraphicTexture2DSet( );
	if ( texture_set->Initialize( size, space ) == _false )
		{ EGE_RELEASE( texture_set ); return _null; }

	return texture_set;
}

IGraphicBackSurfacePassRef GraphicResourceManager::CreateBackSurface( _dword width, _dword height )
{
	GraphicBackSurface* surface = new GraphicBackSurface( );
	if ( surface->Initialize( width, height ) == _false )
		{ EGE_RELEASE( surface ); return _null; }

	return surface;
}

IGraphicSurfacePassRef GraphicResourceManager::CreateRenderTarget( _dword width, _dword height )
{
	// Create target surface
	SurfaceRHIRef resource = gDynamicRHI->CreateTargetableSurface( width, height, _PF_A8R8G8B8 );
	if ( resource.IsNull( ) )
		return _null;

	// Create render target
	GraphicSurface* surface = new GraphicSurface( );
	if ( surface->Initialize( resource ) == _false )
		{ EGE_RELEASE( surface ); return _null; }

	return surface;
}

IGraphicSurfacePassRef GraphicResourceManager::CreateRenderTarget( IGraphicTextureCube* texture_cube )
{
	if ( texture_cube == _null )
		return _null;

	// Create target surface
	SurfaceRHIRef resource = gDynamicRHI->CreateTargetableSurface( texture_cube->GetResource( ) );
	if ( resource.IsNull( ) )
		return _null;

	// Create render target
	GraphicSurface* surface = new GraphicSurface( );
	if ( surface->Initialize( resource ) == _false )
		{ EGE_RELEASE( surface ); return _null; }

	return surface;
}

IGraphicSurfacePassRef GraphicResourceManager::CreateDepthSurface( _dword width, _dword height )
{
	if ( width == 0 || height == 0 )
		return _null;

	// Create texture resource
	Texture2DRHIRef texture = gDynamicRHI->CreateTexture2D( L"", width, height, _PF_DEPTH_STENCIL, 1, _null, _true );
	if ( texture.IsNull( ) )
		return _null;

	// Create target surface
	SurfaceRHIRef resource = gDynamicRHI->CreateTargetableSurface( texture );
	if ( resource.IsNull( ) )
		return _null;

	// Create render target
	GraphicSurface* surface = new GraphicSurface( );
	if ( surface->Initialize( resource ) == _false )
		{ EGE_RELEASE( surface ); return _null; }

	return surface;
}

IGraphicSurfacePassRef GraphicResourceManager::CreateDepthStencil( _dword width, _dword height )
{
	if ( width == 0 || height == 0 )
		return _null;

	// Create texture resource
	Texture2DRHIRef texture = gDynamicRHI->CreateTexture2D( L"", width, height, _PF_DEPTH_STENCIL, 1, _null, _true );
	if ( texture.IsNull( ) )
		return _null;

	// Create target surface
	SurfaceRHIRef resource = gDynamicRHI->CreateTargetableSurface( texture );
	if ( resource.IsNull( ) )
		return _null;

	// Create render target
	GraphicSurface* surface = new GraphicSurface( );
	if ( surface->Initialize( resource ) == _false )
		{ EGE_RELEASE( surface ); return _null; }

	return surface;
}

IGraphicCanvasPassRef GraphicResourceManager::CreateCanvas( _dword width, _dword height, _dword flags )
{
	IGraphicSurfaceRef render_target, depth_stencil;
	if ( CreateSurfaces( render_target, depth_stencil, width, height, flags ) == _false )
		return _null;

	GraphicCanvas* canvas = new GraphicCanvas( );
	if ( canvas->Initialize( render_target, depth_stencil ) == _false )
		{ EGE_RELEASE( canvas ); return _null; }

	return canvas;
}

IGraphicCanvasPassRef GraphicResourceManager::CreateCanvas( IGraphicSurface* render_target, IGraphicSurface* depth_stencil )
{
	GraphicCanvas* canvas = new GraphicCanvas( );
	if ( canvas->Initialize( render_target, depth_stencil ) == _false )
		{ EGE_RELEASE( canvas ); return _null; }

	return canvas;
}

IGraphicCanvasPassRef GraphicResourceManager::CreateCanvas( IGraphicScene* scene, _dword width, _dword height, _dword flags )
{
	IGraphicSurfaceRef render_target, depth_stencil;
	if ( CreateSurfaces( render_target, depth_stencil, width, height, flags ) == _false )
		return _null;

	GraphicCanvas* canvas = new GraphicCanvas( );
	if ( canvas->Initialize( scene, render_target, depth_stencil ) == _false )
		{ EGE_RELEASE( canvas ); return _null; }

	return canvas;
}

IGraphicCanvasPassRef GraphicResourceManager::CreateCanvas( IGraphicScene* scene, IGraphicSurface* render_target, IGraphicSurface* depth_stencil )
{
	GraphicCanvas* canvas = new GraphicCanvas( );
	if ( canvas->Initialize( scene, render_target, depth_stencil ) == _false )
		{ EGE_RELEASE( canvas ); return _null; }

	return canvas;
}

IGraphicFontPassRef GraphicResourceManager::CreateFont( FontRHI* resource )
{
	if ( resource == _null )
		return _null;

	GraphicFont* font = new GraphicFont( resource );

	CleanupFonts( );
	mGraphicFonts.Append( font );

	return font;
}

IGraphicFontPassRef GraphicResourceManager::CreateFontFromStream( const FontInitializerRHI& initializer, IStreamReader* stream_reader )
{
	if ( initializer.IsValid( ) == _false || stream_reader == _null )
		return _null;

	// Create RHI font resource
	FontRHIRef font_resource = gDynamicRHI->CreateFontFromStream( initializer, stream_reader );
	if ( font_resource.IsNull( ) )
		return _null;

	return CreateFont( font_resource );
}

IGraphicFontPassRef GraphicResourceManager::CreateFontFromSystem( const FontInitializerRHI& initializer, WStringPtr name )
{
	IStreamReaderRef stream_reader = GetPlatform( )->LoadSystemFont( name );
	if ( stream_reader.IsNull( ) )
		return _null;

	return CreateFontFromStream( initializer, stream_reader );
}

IGraphicFontPassRef GraphicResourceManager::CreateFontFromSystem( const FontInitializerRHI& initializer, WStringPtr name, const DwordRange& utf16_code_range )
{
	// Try to load from system
	IGraphicFontPassRef font = CreateFontFromSystem( initializer, name );
	if ( font.IsValid( ) )
		return font;

	// Get the system fonts by UTF-16 code range
	FileInfoArray files;
	if ( GetPlatform( )->GetSystemFontFiles( files, utf16_code_range, 1 ) && files.Number( ) == 1 )
		return CreateFontFromSystem( initializer, files[0].mAbsolutePath );

	WLOG_ERROR_3( L"Create font from '%s' system with utf-16 code range(%d, %d) failed", name.Str( ), utf16_code_range.mMinValue, utf16_code_range.mMaxValue );

	return _null;
}

IGraphicFontPassRef GraphicResourceManager::CreateFontFromSystem( const FontInitializerRHI& initializer, WStringPtr name, const Array< DwordRange >& utf16_code_ranges )
{
	// Try to load from system
	IGraphicFontPassRef font = CreateFontFromSystem( initializer, name );
	if ( font.IsValid( ) )
		return font;

	// Get the system fonts by UTF-16 code range
	FileInfoArray files;
	if ( GetPlatform( )->GetSystemFontFiles( files, utf16_code_ranges, 1 ) && files.Number( ) == 1 )
		return CreateFontFromSystem( initializer, files[0].mAbsolutePath );

	WLOG_ERROR_1( L"Create font from '%s' system with utf-16 code ranges failed", name.Str( ) );

	return _null;
}

IGraphicFontPassRef GraphicResourceManager::CreateFontFromResName( const FontInitializerRHI& initializer, const WStringObj& res_name )
{
	// Try to load from working archive
	IStreamReaderRef stream_reader = GetWorkingArchive( )->LoadResourceByName( res_name );
	if ( stream_reader.IsValid( ) )
		return CreateFontFromStream( initializer, stream_reader );

	// Try to load from system
	IGraphicFontPassRef font = CreateFontFromSystem( initializer, res_name );
	if ( font.IsValid( ) )
		return font;

	WLOG_ERROR_1( L"Create font from '%s' resource failed", res_name.Str( ) );

	return _null;
}

IGraphicFontPassRef GraphicResourceManager::CreateFontFromResName( const FontInitializerRHI& initializer, const WStringObj& res_name, const DwordRange& utf16_code_range )
{
	// Try to load from working archive
	IStreamReaderRef stream_reader = GetWorkingArchive( )->LoadResourceByName( res_name );
	if ( stream_reader.IsValid( ) )
		return CreateFontFromStream( initializer, stream_reader );

	// Try to load from system
	IGraphicFontPassRef font = CreateFontFromSystem( initializer, res_name, utf16_code_range );
	if ( font.IsValid( ) )
		return font;

	WLOG_ERROR_3( L"Create font from '%s' resource with utf-16 code range(%d, %d) failed", res_name.Str( ), utf16_code_range.mMinValue, utf16_code_range.mMaxValue );

	return _null;
}

IGraphicFontPassRef	GraphicResourceManager::CreateFontFromResName( const FontInitializerRHI& initializer, const WStringObj& res_name, const Array< DwordRange >& utf16_code_ranges )
{
	// Try to load from working archive
	IStreamReaderRef stream_reader = GetWorkingArchive( )->LoadResourceByName( res_name );
	if ( stream_reader.IsValid( ) )
		return CreateFontFromStream( initializer, stream_reader );

	// Try to load from system
	IGraphicFontPassRef font = CreateFontFromSystem( initializer, res_name, utf16_code_ranges );
	if ( font.IsValid( ) )
		return font;

	WLOG_ERROR_1( L"Create font from '%s' resource with utf-16 code ranges failed", res_name.Str( ) );

	return _null;
}

IGraphicScenePassRef GraphicResourceManager::CreateScene( )
{
	GraphicScene* scene = new GraphicScene( );
	if ( scene->Initialize( ) == _false )
		{ EGE_RELEASE( scene ); return _null; }

	return scene;
}

IGraphicSceneViewPassRef GraphicResourceManager::CreateSceneView( )
{
	return new GraphicSceneView( );
}

IGraphicViewportPassRef GraphicResourceManager::CreateViewport( const PointU& size )
{
	return CreateViewport( mAppHandle, size );
}

IGraphicViewportPassRef GraphicResourceManager::CreateViewport( _handle app_handle, const PointU& size )
{
	// Create RHI viewport
	ViewportRHIRef viewport_resource = gDynamicRHI->CreateViewport( app_handle, size );
	if ( viewport_resource.IsNull( ) )
		return _null;

	// Create viewport
	GraphicViewport* viewport = new GraphicViewport( viewport_resource );
	if ( viewport->Initialize( ) == _false )
		{ EGE_RELEASE( viewport ); return _null; }

	// If we have more than 1 render context then we will use the shared viewport
	if ( gDynamicRHI->GetRenderContextsNumber( ) > 1 )
	{
		GraphicSharedViewport* shared_viewport = new GraphicSharedViewport( viewport );
		viewport->Release( );

		return shared_viewport;
	}
	else
	{
		return viewport;
	}
}

IGraphicLightPassRef GraphicResourceManager::CreateLight( )
{
	return new GraphicLight( );
}

IGraphicFlatMirrorPassRef GraphicResourceManager::CreateFlatMirror( const PointU& size, const Plane& plane )
{
	GraphicFlatMirror* mirror = new GraphicFlatMirror( );
	if ( mirror->Initialize( size ) == _false )
		{ EGE_RELEASE( mirror ); return _null; }

	mirror->SetPlane( plane );

	return mirror;
}

IGraphicSphereMirrorPassRef GraphicResourceManager::CreateSphereMirror( const PointU& size )
{
	GraphicSphereMirror* mirror = new GraphicSphereMirror( );
	if ( mirror->Initialize( size ) == _false )
		{ EGE_RELEASE( mirror ); return _null; }

	return mirror;
}

AStringR GraphicResourceManager::OptimizeVertexShader( AStringPtr code )
{
	AString optimized_code;
	if ( GLSLOptimizer::GetInstance( ).OptimizeVSCode( code, optimized_code ) == _false )
		return "";

	return optimized_code;
}

AStringR GraphicResourceManager::OptimizePixelShader( AStringPtr code )
{
	AString optimized_code;
	if ( GLSLOptimizer::GetInstance( ).OptimizePSCode( code, optimized_code ) == _false )
		return "";

	return optimized_code;
}

VertexShaderRHIRef GraphicResourceManager::CreateVertexShader( AStringPtr code )
{
	VertexShaderRHIRef& vs = mVShaders[ code.GetCRCValue( ) ];
	if ( vs.IsNull( ) )
		vs = gDynamicRHI->CreateVertexShader( code );

	return vs;
}

PixelShaderRHIRef GraphicResourceManager::CreatePixelShader( AStringPtr code )
{
	PixelShaderRHIRef& ps = mPShaders[code.GetCRCValue( )];
	if ( ps.IsNull( ) )
		ps = gDynamicRHI->CreatePixelShader( code );

	return ps;
}

IGraphicEffectPassRef GraphicResourceManager::CreateEffectFromShader( BoundShaderRHI* shader )
{
	GraphicEffect* effect = new GraphicEffect( );
	if ( effect->Initialize( shader ) == _false )
		{ EGE_RELEASE( effect ); return _null; }

	return effect;
}

IGraphicEffectPassRef GraphicResourceManager::CreateEffectFromResName( const WStringObj& res_name )
{
	// Try to load from cache
	const BoundShaderRHIRef* shader = mBoundShaders.Search( res_name.GetID( ) );
	if ( shader != _null )
		return CreateEffectFromShader( *shader );

	// Load shader file
	ISerializableNodeRef node = GetWorkingArchive( )->LoadSerializableNodeByName( res_name );
	if ( node.IsNull( ) )
		return _null;

	// Load VS code
	ISerializableNodeRef vs_node = node->GetChildNodeByName( L"vs" );
	if ( vs_node.IsNull( ) )
		return _null;

	AString vs_code = LoadShaderCodeByNode( vs_node );
	if ( vs_code.IsEmpty( ) )
		return _null;

	// Load PS code
	ISerializableNodeRef ps_node = node->GetChildNodeByName( L"ps" );
	if ( ps_node.IsNull( ) )
		return _null;

	AString ps_code = LoadShaderCodeByNode( ps_node );
	if ( ps_code.IsEmpty( ) )
		return _null;

	IGraphicEffectPassRef effect = CreateEffectFromCode( vs_code, ps_code, "" );
	if ( effect.IsNull( ) )
		return _null;

	// Update cache
	mBoundShaders[ res_name.GetID( ) ] = effect->GetBoundShader( );

	return effect;
}

IGraphicEffectPassRef GraphicResourceManager::CreateEffectFromEffect( IGraphicEffect* effect, AStringPtr macros )
{
	if ( effect == _null )
		return _null;

	return CreateEffectFromCode( effect->GetOriginalVSCode( ), effect->GetOriginalPSCode( ), macros );
}

IGraphicEffectPassRef GraphicResourceManager::CreateEffectFromCode( const AStringObj& vs_code, const AStringObj& ps_code, AStringPtr macros )
{
	// Parse shader code
	AString parsed_vs_code = ParseShaderCode( vs_code );
	AString parsed_ps_code = ParseShaderCode( ps_code );

	// Create effect
	GraphicEffect* effect = new GraphicEffect( );
	if ( effect->Initialize( parsed_vs_code, parsed_ps_code, macros ) == _false )
		{ EGE_RELEASE( effect ); return _null; }

	// Update cache
	mBoundShaders[effect->GetUniqueID( )] = effect->GetBoundShader( );

	return effect;
}

IImageFilePassRef GraphicResourceManager::LoadTextureCubeImage( _CUBE_TEX_SUBFACE_TYPE type, WStringPtr res_name )
{
	IImageFilePassRef image_file = GetWorkingArchive( )->LoadImageFileByName( res_name );
	if ( image_file.IsNull( ) )
		return _null;

	// Rotate image
	RotateTextureCubeImage( type, image_file.GetPtr( ) );

	return image_file;
}

_ubool GraphicResourceManager::LoadTextureCubeImages( IStreamReader* stream_reader, _dword& num_mips, TextureCubeWithMipmapsRHI*& mipmaps )
{
	if ( stream_reader == _null )
		return _false;

	// Try to parse from compressed file
	IZIPFileRef zip_file = GetInterfaceFactory( )->ParseCompressedFile( stream_reader );
	if ( zip_file.IsValid( ) )
	{
		// Get the files number
		_dword files_number = zip_file->GetFileNumber( );
		if ( files_number == 0 )
			return _false;

		// We must arrange to 6x number
		if  ( files_number % 6 != 0 )
			return _false;

		// Create mipmaps info
		num_mips	= files_number / 6;
		mipmaps		= new TextureCubeWithMipmapsRHI[num_mips];

		// The sub-image resource names table
		WStringPtr sub_image_res_names[] = 
		{
			L"+x%d.png",
			L"-x%d.png",
			L"+y%d.png",
			L"-y%d.png",
			L"+z%d.png",
			L"-z%d.png",
		};

		// Start to load mipmaps info
		for ( _dword mipindex = 0; mipindex < num_mips; mipindex ++ )
		{
			TextureCubeWithMipmapsRHI& mipmap_info = mipmaps[mipindex];

			for ( _dword i = 0; i < 6; i ++ )
			{
				// Get the sub-image resource name
				mipmap_info.mResNames[i] = FORMAT_WSTRING_1( sub_image_res_names[i], mipindex );

				// Load sub-image
				IStreamReaderRef image_stream_reader = zip_file->GetFile( mipmap_info.mResNames[i] );
				if ( image_stream_reader.IsNull( ) )
				{
					EGE_DELETE_ARRAY( mipmaps );
					return _false;
				}

				// Parse sub-image and we do not need to rotate it
				mipmap_info.mImageFiles[i] = GetInterfaceFactory( )->ParseImageFile( image_stream_reader );
				if ( mipmap_info.mImageFiles[i].IsNull( ) )
				{
					EGE_DELETE_ARRAY( mipmaps );
					return _false;
				}
			}
		}
	}
	// Try to parse from config file
	else
	{
		ISerializableNodeRef root_node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( stream_reader );
		if ( root_node.IsNull( ) )
			return _false;

		ISerializableNodeRef node = root_node->GetChildNodeByName( L"TextureCube" );
		if ( node.IsNull( ) )
			return _false;

		// Create mipmaps info
		num_mips	= 1;
		mipmaps		= new TextureCubeWithMipmapsRHI[num_mips];

		// Read mipmaps info
		TextureCubeWithMipmapsRHI& mipmap_info = mipmaps[0];
		if ( mipmap_info.Import( node ) == _false )
			return _false;

		// Load images
		for ( _dword i = 0; i < _CUBE_TEX_SUBFACE_NUMBER; i ++ )
		{
			// Load image file
			IImageFileRef image_file = LoadTextureCubeImage( (_CUBE_TEX_SUBFACE_TYPE) i, mipmap_info.mResNames[i] );
			if ( image_file.IsNull( ) )
			{
				EGE_DELETE_ARRAY( mipmaps );
				return _false;
			}

			// Update the sub texture info
			mipmap_info.mImageFiles[i] = image_file;
		}
	}

	// Check image size
	if ( CheckTextureCubeImageSize( num_mips, mipmaps ) == _false )
		return _false;

	return _true;
}
