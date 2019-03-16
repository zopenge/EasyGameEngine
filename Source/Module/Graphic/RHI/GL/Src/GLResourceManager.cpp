//! @file     GLResourceManager.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLResourceManager Implementation
//----------------------------------------------------------------------------

GLResourceManager::GLResourceManager( )
{
	mIsResetting = _false;
}

GLResourceManager::~GLResourceManager( )
{
}

_void GLResourceManager::UnloadFBOs( )
{
	GLFramebufferCache::GetInstance( ).Clear( );
}

_ubool GLResourceManager::CreateVAO( VertexArrayRHI* vao )
{
	VAOResInfo& vao_res_info	= mVAOResources[ vao ];
	vao_res_info.mVAOResource	= (GLVertexArray*) vao;

	return _true;
}

_void GLResourceManager::UnloadVAOs( )
{
	for ( VAOResMap::Iterator it = mVAOResources.GetHeadIterator( ); it.IsValid( ); ++ it  )
		it.GetObject( ).mVAOResource->DeleteVAO( );
}

_ubool GLResourceManager::ResetVAO( )
{
	for ( VAOResMap::Iterator it = mVAOResources.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		if ( it.GetObject( ).mVAOResource->ResetVAO( ) == _false )
			return _false;
	}

	return _true;
}

template< typename BufferResType >
_ubool GLResourceManager::CreateBuffer( BufferResInfo< BufferResType >& res_info, BufferResType* res )
{
	res_info.mBufferRes	= res;

	return _true;
}

template< typename BufferResMapType >
_void GLResourceManager::UnloadBuffers( BufferResMapType& resources )
{
	for ( typename BufferResMapType::Iterator it = resources.GetHeadIterator( ); it.IsValid( ); ++ it )
		it.GetObject( ).mBufferRes->DeleteBuffer( );
}

template< typename BufferResMapType >
_void GLResourceManager::ResetBuffer( BufferResMapType& resources )
{
	for ( typename BufferResMapType::Iterator it = resources.GetHeadIterator( ); it.IsValid( ); ++ it )
		it.GetObject( ).mBufferRes->Reset( );
}

_ubool GLResourceManager::ResetBuffers( )
{
	ResetBuffer( mVBOResources );
	ResetBuffer( mIBOResources );

	return _true;
}

template< typename ShaderResType >
_ubool GLResourceManager::CreateShader( ShaderResInfo< ShaderResType >& res_info, ShaderResType* res )
{
	res_info.mShaderRes	= static_cast< ShaderResType* >( res );

	return _true;
}

template< typename ShaderResMapType >
_void GLResourceManager::UnloadShaders( ShaderResMapType& resources )
{
	for ( typename ShaderResMapType::Iterator it = resources.GetHeadIterator( ); it.IsValid( ); ++ it  )
		it.GetObject( ).mShaderRes->DeleteShader( );
}

_void GLResourceManager::UnloadTexture2DResource( Texture2DResInfo& res_info )
{
	GLTexture2D* tex_res = res_info.mTextureRes;
	EGE_ASSERT( tex_res != _null );

	// Delete texture
	tex_res->DeleteTexture( );
}

_void GLResourceManager::UnloadTexture2DResources( )
{
	for ( Texture2DResMap::Iterator it = mTexture2DResources.GetHeadIterator( ); it.IsValid( ); ++ it )
		UnloadTexture2DResource( it.GetObject( ) );
}

_void GLResourceManager::UnloadTextureCubeResource( TextureCubeResInfo& res_info )
{
	GLTextureCube* tex_res = res_info.mTextureRes;
	EGE_ASSERT( tex_res != _null );

	// Delete texture
	tex_res->DeleteTexture( );
}

_void GLResourceManager::UnloadTextureCubeResources( )
{
	for ( TextureCubeResMap::Iterator it = mTextureCubeResources.GetHeadIterator( ); it.IsValid( ); ++ it )
		UnloadTextureCubeResource( it.GetObject( ) );
}

_void GLResourceManager::UnloadTextureResources( )
{
	UnloadTexture2DResources( );
	UnloadTextureCubeResources( );
}

TextureCubeRHIRef GLResourceManager::ResetTextureCubeResource( TextureCubeResInfo& res_info )
{
	GLTextureCube* tex_res = res_info.mTextureRes;
	EGE_ASSERT( tex_res != _null );

	// The texture cube
	TextureCubeRHIRef texture_cube;

	// Get the resource name
	WStringPtr res_name = res_info.mTextureResName.Str( );

	// Load texture resource
	IStreamReaderRef stream_reader = GetWorkingArchive( )->LoadResourceByName( res_name );
	if ( stream_reader.IsNull( ) )
	{
		WLOG_ERROR_1( L"Load texture cube '%s' from working archive failed", res_name.Str( ) );
		return _false;
	}

	// Try to load mipmaps from file
	_dword nummips = 0; TextureCubeWithMipmapsRHI* mipmaps_info = _null;
	if ( GetGraphicResourceManager( )->LoadTextureCubeImages( stream_reader, nummips, mipmaps_info ) )
	{
		texture_cube = GetDynamicRHI( )->CreateTextureCubeWithMipmaps( res_name, nummips, mipmaps_info );

		EGE_DELETE_ARRAY( mipmaps_info );
	}
	// Auto generate mipmaps
	else
	{
		// Parse the image files
		TextureCubeWithMipmapsRHI mipmaps_info;
		for ( _dword i = 0; i < 6; i ++ )
		{
			mipmaps_info.mResNames[i] = res_info.mMipmaps->mResNames[i];

			mipmaps_info.mImageFiles[i] = GetGraphicResourceManager( )->LoadTextureCubeImage( (_CUBE_TEX_SUBFACE_TYPE)i, mipmaps_info.mResNames[i] );
			if ( mipmaps_info.mImageFiles[i].IsNull( ) )
			{
				WLOG_ERROR_3( L"Load (%d)'%s' sub-image from auto gen '%s' texture cube failed", i, mipmaps_info.mResNames[i].Str( ), res_name.Str( ) );
				return _null;
			}
		}

		// Create new texture
		texture_cube = GetDynamicRHI( )->CreateTextureCube( res_name, nummips, mipmaps_info );
	}

	return texture_cube;
}

_ubool GLResourceManager::ResetTexture2DResources( )
{
	for ( Texture2DResMap::Iterator it = mTexture2DResources.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		GLTexture2D* tex_res = it.GetObject( ).mTextureRes;
		EGE_ASSERT( tex_res != _null );

		// The new resource
		Texture2DRHIRef texture_2d;

		// Check the resource name ( it could be empty )
		WStringPtr res_name	= it.GetObject( ).mTextureResName.Str( );
		if ( res_name.IsEmpty( ) )
		{
			// Get the pixel buffer
			const _byte* pixel_buffer = it.GetObject( ).mPixelBuffer;

			// Create texture 2D
			texture_2d = GetDynamicRHI( )->CreateTexture2D( L"", tex_res->GetSize( ).x, tex_res->GetSize( ).y, tex_res->GetPixelFormat( ), tex_res->GetNumMips( ), pixel_buffer, tex_res->IsDynamic( ) );
		}
		else
		{
			// Parse the image file
			IImageFileRef image_file = GetWorkingArchive( )->LoadImageFileByName( res_name );
			if ( image_file.IsNull( ) )
			{
				WLOG_ERROR_1( L"Load '%s' texture 2D resource from IO resource manager failed", res_name.Str( ) );
				return _false;
			}

			// Create new texture
			texture_2d = GetDynamicRHI( )->CreateTexture2DFromImageFile( res_name, image_file, tex_res->GetNumMips( ) );
		}

		if ( texture_2d.IsNull( ) )
			return _false;

		// Update the resource ID
		texture_2d.cast_static< GLTexture2D >( )->EnableAutoDeleteSelf( _false );
		tex_res->UpdateResourceID( texture_2d.cast_static< GLTexture2D >( )->GetResource( ) );
		tex_res->SetSamplerState( texture_2d.cast_static< GLTexture2D >( )->GetSamplerState( ) );
	}

	return _true;
}

_ubool GLResourceManager::ResetTextureCubeResources( )
{
	for ( TextureCubeResMap::Iterator it = mTextureCubeResources.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		TextureCubeResInfo& res_info = it.GetObject( );

		GLTextureCube* tex_res = res_info.mTextureRes;
		EGE_ASSERT( tex_res != _null );

		// The texture cube
		TextureCubeRHIRef texture_cube = ResetTextureCubeResource( res_info );
		if ( texture_cube.IsNull( ) )
		{
			WLOG_ERROR_1( L"Reset '%s' texture cube resource failed", res_info.mTextureResName.Str( ) );
			return _false;
		}

		// Update the resource ID
		texture_cube.cast_static< GLTextureCube >( )->EnableAutoDeleteSelf( _false );
		tex_res->UpdateResourceID( texture_cube.cast_static< GLTextureCube >( )->GetResource( ) );
	}

	return _true;
}

_ubool GLResourceManager::ResetTextureResources( )
{
	if ( ResetTexture2DResources( ) == _false )
	{
		WLOG_ERROR( L"Reset texture 2D resources failed" );
		return _false;
	}

	if ( ResetTextureCubeResources( ) == _false )
	{
		WLOG_ERROR( L"Reset texture cube resources failed" );
		return _false;
	}

	return _true;
}

_ubool GLResourceManager::Initialize( )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

#if (_USE_COMPRESSION_ == 1)
	mCompressionEncoder = GetInterfaceFactory( )->CreateCompressionEncoder( _COMPRESSION_ZLIB );
	if ( mCompressionEncoder.IsNull( ) )
		return _false;

	mCompressionEncoder->SetLevel( ICompressionEncoder::_LEVEL_DEFAULT );

	mCompressionDecoder = GetInterfaceFactory( )->CreateCompressionDecoder( _COMPRESSION_ZLIB );
	if ( mCompressionDecoder.IsNull( ) )
		return _false;
#endif

	return _true;
}

_void GLResourceManager::Finalize( )
{
	EGE_ASSERT( Platform::IsMainThread( ) );
}

_ubool GLResourceManager::Reset( )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	WLOG_TRACE( L"Resetting GL resources ..." );

	Unload( );

	DataOwner< _ubool > data_owner( mIsResetting );
	mIsResetting = _true;

	gGLCachedState.Clear( );

	if ( ResetBuffers( ) == _false )
	{
		WLOG_ERROR( L"Reset buffer resources failed" );
		return _false;
	}

	if ( ResetVAO( ) == _false )
	{
		WLOG_ERROR( L"Reset vertex array resources failed" );
		return _false;
	}

	if ( ResetTextureResources( ) == _false )
	{
		WLOG_ERROR( L"Reset texture resources failed" );
		return _false;
	}

	gGLCachedState.Clear( );

	WLOG_TRACE( L"Reset GL resources OK" );

	return _true;
}

_void GLResourceManager::Unload( )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	WLOG_TRACE( L"Unloading GL resources ..." );

	UnloadFBOs( );

	UnloadVAOs( );

	UnloadBuffers( mVBOResources );
	UnloadBuffers( mIBOResources );

	UnloadShaders( mVertexShaderResources );
	UnloadShaders( mPixelShaderResources );
	UnloadShaders( mBoundShaderResources );

	UnloadTextureResources( );

	WLOG_TRACE( L"Unload GL resources OK" );
}

_ubool GLResourceManager::CreateVAOResource( VertexArrayRHI* vao )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return _true;

	return CreateVAO( vao );
}

_void GLResourceManager::RemoveVAOResource( VertexArrayRHI* vao )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return;

	mVAOResources.Remove( vao );
}

_ubool GLResourceManager::CreateBuffer( VertexBufferRHI* vbo )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return _true;

	return CreateBuffer( mVBOResources[ vbo ], static_cast< GLVertexBuffer* >( vbo ) );
}

_ubool GLResourceManager::CreateBuffer( IndexBufferRHI* ibo )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return _true;

	return CreateBuffer( mIBOResources[ ibo ], static_cast< GLIndexBuffer* >( ibo ) );
}

_void GLResourceManager::RemoveBuffer( VertexBufferRHI* vbo )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return;

	mVBOResources.Remove( vbo );
}

_void GLResourceManager::RemoveBuffer( IndexBufferRHI* ibo )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return;

	mIBOResources.Remove( ibo );
}

_ubool GLResourceManager::CreateShader( VertexShaderRHI* vs )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return _true;

	return CreateShader< GLVertexShader >( mVertexShaderResources[ vs ], static_cast< GLVertexShader* >( vs ) );
}

_ubool GLResourceManager::CreateShader( PixelShaderRHI* ps )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return _true;

	return CreateShader< GLPixelShader >( mPixelShaderResources[ ps ], static_cast< GLPixelShader* >( ps ) );
}

_ubool GLResourceManager::CreateShader( BoundShaderRHI* shader )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return _true;

	return CreateShader< GLBoundShader >( mBoundShaderResources[ shader ], static_cast< GLBoundShader* >( shader ) );
}

_void GLResourceManager::RemoveShader( VertexShaderRHI* vs )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return;

	mVertexShaderResources.Remove( vs );
}

_void GLResourceManager::RemoveShader( PixelShaderRHI* ps )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return;

	mPixelShaderResources.Remove( ps );
}

_void GLResourceManager::RemoveShader( BoundShaderRHI* shader )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return;

	mBoundShaderResources.Remove( shader );
}

_ubool GLResourceManager::CreateTexture( Texture2DRHI* texture, WStringPtr res_name, const _byte* pixels )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return _true;

	Texture2DResInfo& res_info	= mTexture2DResources[ texture ];
	res_info.mTextureRes		= static_cast< GLTexture2D* >( texture );
	res_info.mTextureResName	= res_name;

	// Save the pixel info if it's not dynamic texture and without resource name
	if ( res_name.IsEmpty( ) && gDynamicRHI->IsTexture2DDynamic( texture ) == _false )
	{
		if ( pixels == _null )
			return _false;

		_dword size = GetDynamicRHI( )->GetTexture2DSizeInBytes( texture );
		if ( size == 0 )
			return _false;

		res_info.mPixelBuffer = new _byte[ size ];
		EGE_MEM_CPY( res_info.mPixelBuffer, pixels, size );
	}

	return _true;
}

_ubool GLResourceManager::CreateTexture( TextureCubeRHI* texture, WStringPtr res_name, const TextureCubeWithMipmapsRHI& mipmaps_info )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return _true;

	TextureCubeResInfo& res_info	= mTextureCubeResources[ texture ];
	res_info.mTextureRes			= static_cast< GLTextureCube* >( texture );
	res_info.mTextureResName		= GetStringTable( )->GetRefString( res_name );
	res_info.mMipmaps				= new TextureCubeWithMipmapsRHIBase[1];
	res_info.mMipmaps[0]			= (const TextureCubeWithMipmapsRHIBase&) mipmaps_info;

	return _true;
}

_ubool GLResourceManager::CreateTexture( TextureCubeRHI* texture, WStringPtr res_name, const TextureCubeWithMipmapsRHI* mipmaps_info )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	EGE_ASSERT( mipmaps_info != _null );

	if ( mIsResetting )
		return _true;

	_dword mipnumber = GetDynamicRHI( )->GetTextureCubeMipNumber( texture );

	TextureCubeResInfo& res_info	= mTextureCubeResources[ texture ];
	res_info.mTextureRes			= static_cast< GLTextureCube* >( texture );
	res_info.mTextureResName		= res_name;
	if ( mipnumber != 0 )
		res_info.mMipmaps = new TextureCubeWithMipmapsRHIBase[ mipnumber ];

	for ( _dword i = 0; i < mipnumber; i ++ )
		res_info.mMipmaps[i] = (const TextureCubeWithMipmapsRHIBase&) mipmaps_info[i];

	return _true;
}

_void GLResourceManager::UpdateTexture( Texture2DRHI* texture, const RectU& rect, const _byte* pixel )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return;

	Texture2DResInfo& res_info = mTexture2DResources[ texture ];
	if ( res_info.mPixelBuffer == _null )
		return;

	_dword stride = res_info.mTextureRes->GetStride( 0 );
	EGE_ASSERT( stride != 0 );

	_dword block_bytes = res_info.mTextureRes->GetBlockBytes( );
	EGE_ASSERT( block_bytes != 0 );

	for ( _dword y = rect.t; y < rect.b; y ++ )
	{
		_dword			size		= rect.GetWidth( ) * block_bytes;
		_byte*			to_buffer	= res_info.mPixelBuffer + y * stride + rect.l * block_bytes;
		const _byte*	from_buffer = pixel + (y - rect.t) * size;

		EGE_MEM_CPY( to_buffer, from_buffer, size );
	}
}

_void GLResourceManager::RemoveTexture( Texture2DRHI* texture )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return;

	mTexture2DResources.Remove( texture );
}

_void GLResourceManager::RemoveTexture( TextureCubeRHI* texture )
{
	EGE_ASSERT( Platform::IsMainThread( ) );

	if ( mIsResetting )
		return;

	mTextureCubeResources.Remove( texture );
}