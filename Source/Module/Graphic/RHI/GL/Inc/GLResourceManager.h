//! @file     GLResourceManager.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GLResourceManager
//----------------------------------------------------------------------------

class GLResourceManager : public TObject< IResourceManagerRHI >
{
private:
	//!	The vertex array resource info
	struct VAOResInfo
	{
		GLVertexArray*	mVAOResource;

		VAOResInfo( )
		{
			mVAOResource = _null;
		}
	};
	typedef Map< VAOResInfo, VertexArrayRHI* > VAOResMap;

	//!	The buffer resource info
	template< typename BufferResType >
	struct BufferResInfo
	{
		BufferResType*	mBufferRes;

		BufferResInfo( )
		{
			mBufferRes	= _null;
		}
	};
	typedef BufferResInfo< GLVertexBuffer > VBOResInfo;
	typedef BufferResInfo< GLIndexBuffer > IBOResInfo;

	typedef Map< VBOResInfo, VertexBufferRHI* > VBOResMap;
	typedef Map< IBOResInfo, IndexBufferRHI* > IBOResMap;

	//!	The shader resource info
	template< typename ShaderResType >
	struct ShaderResInfo
	{
		ShaderResType*	mShaderRes;

		ShaderResInfo( )
		{
			mShaderRes = _null;
		}
	};
	typedef ShaderResInfo< GLVertexShader > VertexShaderResInfo;
	typedef ShaderResInfo< GLPixelShader > PixelShaderResInfo;
	typedef ShaderResInfo< GLBoundShader > BoundShaderResInfo;

	typedef Map< VertexShaderResInfo, VertexShaderRHI* > VertexShaderResMap;
	typedef Map< PixelShaderResInfo, PixelShaderRHI* > PixelShaderResMap;
	typedef Map< BoundShaderResInfo, BoundShaderRHI* > BoundShaderResMap;

	//!	The texture resource info
	template< typename Type >
	struct TextureResInfo
	{
		WStringObj	mTextureResName;
		Type*		mTextureRes;

		TextureResInfo( )
		{
			mTextureRes	= _null;
		}
	};

	//!	The texture 2D resource info
	struct Texture2DResInfo : public TextureResInfo< GLTexture2D >
	{
		_byte*	mPixelBuffer;

		Texture2DResInfo( )
		{
			mPixelBuffer = _null;
		}
		~Texture2DResInfo( )
		{
			EGE_DELETE_ARRAY( mPixelBuffer );
		}
	};
	typedef Map< Texture2DResInfo, Texture2DRHI* > Texture2DResMap;

	//!	The texture cube resource info
	struct TextureCubeResInfo : public TextureResInfo< GLTextureCube >
	{
		TextureCubeWithMipmapsRHIBase*	mMipmaps;

		TextureCubeResInfo( )
		{
			mMipmaps = _null;
		}
		~TextureCubeResInfo( )
		{
			EGE_DELETE_ARRAY( mMipmaps );
		}
	};
	typedef Map< TextureCubeResInfo, TextureCubeRHI* > TextureCubeResMap;

private:
	//!	True indicates it's resetting
	_ubool					mIsResetting;

	//!	The VAO resource list
	VAOResMap				mVAOResources;

	//!	The VBO/IBO resource list
	VBOResMap				mVBOResources;
	IBOResMap				mIBOResources;

	//!	The shader resource list
	VertexShaderResMap		mVertexShaderResources;
	PixelShaderResMap		mPixelShaderResources;
	BoundShaderResMap		mBoundShaderResources;

	//!	The textures resources list
	Texture2DResMap			mTexture2DResources;
	TextureCubeResMap		mTextureCubeResources;

	//!	The stream compressor
	ICompressionEncoderRef	mCompressionEncoder;
	ICompressionDecoderRef	mCompressionDecoder;

private:
	//!	Delete FBOs.
	_void UnloadFBOs( );

	//!	Create VAO.
	_ubool CreateVAO( VertexArrayRHI* vao );
	//!	Delete VAO.
	_void UnloadVAOs( );
	//!	Reset VAO.
	_ubool ResetVAO( );

	//!	Create buffer resource info.
	template< typename BufferResType >
	_ubool CreateBuffer( BufferResInfo< BufferResType >& res_info, BufferResType* res );
	//!	Delete buffer.
	template< typename BufferResMapType >
	_void UnloadBuffers( BufferResMapType& resources );
	//!	Reset buffer.
	template< typename BufferResMapType >
	_void ResetBuffer( BufferResMapType& resources );
	//!	Reset buffers.
	_ubool ResetBuffers( );

	//!	Create shader.
	template< typename ShaderResType >
	_ubool CreateShader( ShaderResInfo< ShaderResType >& res_info, ShaderResType* res );
	//!	Delete shader.
	template< typename ShaderResMapType >
	_void UnloadShaders( ShaderResMapType& resources );

	//!	Delete textures.
	_void UnloadTexture2DResource( Texture2DResInfo& res_info );
	_void UnloadTexture2DResources( );
	_void UnloadTextureCubeResource( TextureCubeResInfo& res_info );
	_void UnloadTextureCubeResources( );
	_void UnloadTextureResources( );
	//!	Reset textures.
	TextureCubeRHIRef ResetTextureCubeResource( TextureCubeResInfo& res_info );
	_ubool ResetTexture2DResources( );
	_ubool ResetTextureCubeResources( );
	_ubool ResetTextureResources( );

public:
	GLResourceManager( );
	virtual ~GLResourceManager( );

// IResourceManagerRHI Interface
public:
	virtual _ubool	Initialize( ) override;
	virtual _void	Finalize( ) override;

	virtual _ubool	Reset( ) override;
	virtual _void	Unload( ) override;

	virtual _ubool	CreateVAOResource( VertexArrayRHI* vao ) override;
	virtual _void	RemoveVAOResource( VertexArrayRHI* vao ) override;

	virtual _ubool	CreateBuffer( VertexBufferRHI* vbo ) override;
	virtual _ubool	CreateBuffer( IndexBufferRHI* ibo ) override;
	virtual _void	RemoveBuffer( VertexBufferRHI* vbo ) override;
	virtual _void	RemoveBuffer( IndexBufferRHI* ibo ) override;

	virtual _ubool	CreateShader( VertexShaderRHI* vs ) override;
	virtual _ubool	CreateShader( PixelShaderRHI* ps ) override;
	virtual _ubool	CreateShader( BoundShaderRHI* shader ) override;
	virtual _void	RemoveShader( VertexShaderRHI* vs ) override;
	virtual _void	RemoveShader( PixelShaderRHI* ps ) override;
	virtual _void	RemoveShader( BoundShaderRHI* shader ) override;

	virtual _ubool	CreateTexture( Texture2DRHI* texture, WStringPtr res_name, const _byte* pixels ) override;
	virtual _ubool	CreateTexture( TextureCubeRHI* texture, WStringPtr res_name, const TextureCubeWithMipmapsRHI& mipmaps_info ) override;
	virtual _ubool	CreateTexture( TextureCubeRHI* texture, WStringPtr res_name, const TextureCubeWithMipmapsRHI* mipmaps_info ) override;
	virtual _void	UpdateTexture( Texture2DRHI* texture, const RectU& rect, const _byte* pixel ) override;
	virtual _void	RemoveTexture( Texture2DRHI* texture ) override;
	virtual _void	RemoveTexture( TextureCubeRHI* texture ) override;
};

}