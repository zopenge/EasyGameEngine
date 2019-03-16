//! @file     GLResources.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class GLSLProgram;
class GLFramebufferCache;

//!	The state cache
struct GLCachedState;
extern GLCachedState gGLCachedState;

//! When delete a VBO.
extern _void OnVBODeletion( GLuint buffer );
//! When delete a IBO.
extern _void OnIBODeletion( GLuint buffer );
//! When delete a VAO.
extern _void OnVAODeletion( GLuint buffer );

//!	When set active texture.
extern _void GLCachedSetActiveTexture( _dword index );

//!	Bind texture.
extern _void GLCachedBindTexture( GLuint target, GLuint tex_id );

//!	Bind buffer in cached way.
extern _void GLCachedBindFBO( GLuint buffer );
extern _void GLCachedBindRBO( GLuint buffer );
extern _void GLCachedBindVBO( GLuint buffer );
extern _void GLCachedBindIBO( GLuint buffer );
extern _void GLCachedBindVAO( GLuint buffer );

//!	Bind buffer.
extern _void GLBindVBO( GLuint buffer );
extern _void GLBindIBO( GLuint buffer );

//!	Frame buffer.
extern _void GLPurgeFramebufferFromCaches( GLuint buffer );

//!	Set buffer in cached way.
extern _void GLCachedSetReadBuffer( GLuint buffer );
extern _void GLCachedSetDrawBuffer( GLuint buffer );

//!	Shader.
extern _void GLCachedBindProgram( GLuint program );

// The GL API call counter
#if (_DISABLE_GL_API_CALL_COUNTER == 0)
extern _dword gGLAPICallCounter;
extern _void IncGLAPICallCounter( );
#endif

// Check the GL error
#if (_DISABLE_GL_ERROR_CHECK == 1)
	#if (_DISABLE_GL_API_CALL_COUNTER == 1)
		#define GL_CHECK_ERROR( x ) { x; }
	#else
		#define GL_CHECK_ERROR( x ) { IncGLAPICallCounter( ); x; }
	#endif
#else
	#if (_DISABLE_GL_API_CALL_COUNTER == 1)
		#define GL_CHECK_ERROR( x ) { x; GLCheckError( _FILENAME_A, _LINENUMBER ); }
	#else
		#define GL_CHECK_ERROR( x ) { IncGLAPICallCounter( ); x; GLCheckError( _FILENAME_A, _LINENUMBER ); }
	#endif
#endif

// Check the GL shader
#define GL_CHECK_SHADER( shader ) GLCheckShader( shader )
// Check the GL program
#define GL_CHECK_PROGRAM( program ) GLCheckProgram( program )
// Check the GL frame buffer
#define GL_CHECK_FBO( fbo ) GLCheckFramebuffer( fbo )

extern _void GLCheckError( AStringPtr file, _dword line );
extern _ubool GLCheckShader( GLuint shader );
extern _ubool GLCheckProgram( GLuint program );
extern _ubool GLCheckFramebuffer( GLuint fbo );

//----------------------------------------------------------------------------
// GLVertexDeclaration
//----------------------------------------------------------------------------

class GLVertexDeclaration : public VertexDeclarationRHI
{
private:
	//!	The stride in bytes
	_dword					mStride;
	//! Elements of the vertex declaration
	GLVertexElementArray	mVertexElements;

	//!	The vertex declaration define
	VertexElementRHIArray	mDefine;

public:
	GLVertexDeclaration( );
	virtual ~GLVertexDeclaration( );

public:
	_ubool Initialize( const VertexElementRHIArray& elements );

	_dword GetVertexType( ) const;

public:
	//!	Get the stride in bytes.
	EGE_GET_ACCESSOR_CONST( _dword, Stride )
	//!	Get the vertex declaration elements.
	EGE_GET_ACCESSOR_CONST( const GLVertexElementArray&, VertexElements )
	//!	Get the vertex declaration define.
	EGE_GET_ACCESSOR_CONST( const VertexElementRHIArray&, Define )
};

//----------------------------------------------------------------------------
// TGLShader
//----------------------------------------------------------------------------

template< _RENDER_RESOURCE_TYPE ResourceType, GLenum _TYPE >
class TGLShader : public TDynamicRHIResource< ResourceType >
{
protected:
	//!	The shader resource
	GLuint		mResource;
	//!	The shader code text in ANSI mode
	AStringObj	mCode;

protected:
	//!	Get the shader type name.
	static const _charw* GetShaderTypeName( GLenum type )
	{
		switch ( type )
		{
			case GL_VERTEX_SHADER:		return L"VS";
			case GL_FRAGMENT_SHADER:	return L"PS";
			default:
				return L"Unknown";
		}
	}

public:
	TGLShader( AStringPtr code )
	{
		mResource = 0;

		// Add GLSL version string if we do not have it
		AString shader_code = code;
		if ( code.SearchL2R( "#version" ) == -1 )
		{
			Version glsl_ver		= GetGLSLVersion( );
			AString glsl_ver_string = FORMAT_ASTRING_1( "#version %.3d\n\n", glsl_ver.GetMajorVersion( ) * 100 + glsl_ver.GetMinorVersion( ) * 10 );

			shader_code = glsl_ver_string + code;
		}

		mCode = GetStringTable( )->GetRefString( shader_code );

		GetResourceManagerRHI( )->CreateShader( this );
	}

	virtual ~TGLShader( )
	{
		DeleteShader( );

		GetResourceManagerRHI( )->RemoveShader( this );
	}

public:
	//!	Get the shader resource
	EGE_GET_ACCESSOR_CONST( GLuint, Resource )
	//!	Get the shader code
	EGE_GETR_ACCESSOR_CONST( AStringObj, Code )

public:
	//!	Compile the shader code.
	_ubool CompileShader( )
	{
		// Check whether has been compiled successful
		if ( mResource != 0 )
			return _true;

		// Create the shader resource
		mResource = __glCreateShader( _TYPE );
		EGE_ASSERT( mResource != 0 );

		WLOG_TRACE_1( L"Create (%d) shader program", (_dword) mResource );
		
		// Get the code text
		GLchar* code_text = (GLchar*) mCode.Str( );
		EGE_ASSERT( code_text != _null );

		// Compile the shader code
		GL_CHECK_ERROR( __glShaderSource( mResource, 1, (const GLchar**) &code_text, _null ) );
		GL_CHECK_ERROR( __glCompileShader( mResource ) );

		// Check the compile status
		if ( GL_CHECK_SHADER( mResource ) == _false )
		{
			DeleteShader( );
			return _false;
		}

		WLOG_TRACE_1( L"Compile (%d) shader program OK", (_dword) mResource );

		return _true;
	}
	//!	Delete shader.
	_void DeleteShader( )
	{
		if ( mResource != 0 )
		{
			WLOG_TRACE_1( L"Delete (%d) shader program", mResource );
			GL_CHECK_ERROR( __glDeleteShader( mResource ) );

			mResource = 0;
		}
	}
};

typedef TGLShader< _RRT_VERTEX_SHADER, GL_VERTEX_SHADER >	GLVertexShader;
typedef TGLShader< _RRT_PIXEL_SHADER, GL_FRAGMENT_SHADER >	GLPixelShader;

//----------------------------------------------------------------------------
// GLBoundShader
//----------------------------------------------------------------------------

//! Combined shader state and vertex definition for rendering geometry. 
//!	Each unique instance consists of a vertex decl, vertex shader, and pixel shader.
class GLBoundShader : public BoundShaderRHI
{
private:
	//!	The uniform buffer info
	struct UniformBufferInfo : public UniformBufferRHI
	{
		MemArrayPtr< _byte >	mBuffer;
	};
	typedef Array< UniformBufferInfo > UniformBufferInfoArray;

private:
	//!	The GLSL program
	GLSLProgram*				mGLSLProgram;

	//!	The uniform buffers
	UniformBufferInfoArray		mUniformBuffers;

	//!	The vertex shader
	RefPtr< GLVertexShader >	mVertexShader;
	//!	The pixel shader
	RefPtr< GLPixelShader >		mPixelShader;

private:
	//!	Check whether need to update uniform buffer.
	_ubool IsNeedUpdateUniformBuffer( _dword location, const _void* buffer, _dword size );

public:
	GLBoundShader( VertexShaderRHI* vs, PixelShaderRHI* ps );
	virtual ~GLBoundShader( );

public:
	//!	Get vertex shader.
	EGE_GET_ACCESSOR( GLVertexShader*, VertexShader )
	//!	Get pixel shader.
	EGE_GET_ACCESSOR( GLPixelShader*, PixelShader )

public:
	//!	Initialize.
	_ubool Initialize( );

	//!	Get shader resource ID.
	_dword GetShaderResourceID( ) const;

	//!	Delete shader.
	_void DeleteShader( );

	//!	Bind.
	_void Bind( );

	// Get uniform buffer location
	_dword GetUniformLocation( AStringPtr name ) const;
	//!	Active uniform buffer.
	_dword ActiveUniformBuffer( _UNIFORM_BUFFER_DATA_TYPE type, const AStringObj& name, _dword size );
	//!	Update uniform buffer.
	_ubool UpdateUniformBuffer( _dword location, const _void* buffer, _dword size );
	//!	Set uniform property value.
	_ubool SetUniformPropertyValue( AStringPtr name, _int value );
};

//----------------------------------------------------------------------------
// TGLBuffer
//----------------------------------------------------------------------------

//!	The buffer bind and delete function declaration.
typedef _void (*OnBufferBindFunction)( GLuint );
typedef _void (*OnBufferCacheBindFunction)( GLuint );
typedef _void (*OnBufferDeleteFunction)( GLuint );

template< _RENDER_RESOURCE_TYPE ResourceType, GLenum _TYPE, OnBufferBindFunction _BUFFER_BIND_FUNC, OnBufferCacheBindFunction _BUFFER_CACHE_BIND_FUNC, OnBufferDeleteFunction _BUFFER_DELETE_FUNC >
class TGLBuffer : public TDynamicRHIResource< ResourceType >
{
protected:
	typedef MemArrayPtr< _byte > BufferArray;

protected:
	//!	The buffer resource
	GLuint				mResource;
	//!	The actual buffer size, use to determine whether resize it
	_dword				mRealSize;

	//!	The stride size in bytes of each element
	_dword				mStride;
	//!	The draw type
	_RESOURCE_DRAW_TYPE	mDrawType;

	//!	The lock field
	DwordDataField		mLockDataField;
	//!	The update field
	DwordDataField		mUpdateDataField;
	
	//!	The last resize time
	_dword				mLastResizeTime;
	//!	The buffer data
	BufferArray			mBufferData;

protected:
	//!	Get the buffer type string.
	WStringPtr GetTypeString( ) const
	{
		if ( ResourceType == _RRT_INDEX_BUFFER )
			return L"IndexBuffer";
		else if ( ResourceType == _RRT_VERTEX_BUFFER )
			return L"VertexBuffer";
		else
			return L"Unknown";
	}

	//!	Translate the draw type to buffer draw type.
	GLenum TranslateDrawType( _RESOURCE_DRAW_TYPE draw_type ) const
	{
		switch ( draw_type )
		{
			case _RDT_TYPE_STATIC:	return GL_STATIC_DRAW;
			case _RDT_TYPE_DYNAMIC:	return GL_DYNAMIC_DRAW;
			case _RDT_TYPE_STREAM:	return GL_STREAM_DRAW;
			default:
				return 0;
		}
	}
	//!	Translate the draw type to string.
	WStringPtr TranslateDrawType2String( _RESOURCE_DRAW_TYPE draw_type ) const
	{
		switch ( draw_type )
		{
			case _RDT_TYPE_STATIC:	return L"STATIC_DRAW";
			case _RDT_TYPE_DYNAMIC:	return L"DYNAMIC_DRAW";
			case _RDT_TYPE_STREAM:	return L"STREAM_DRAW";
			default:
				return L"";
		}
	}

	//!	Create buffer data.
	_ubool CreateBufferData( _dword size, const _byte* data, _RESOURCE_DRAW_TYPE draw_type )
	{
		EGE_ASSERT( size != 0 );

		GL_CHECK_ERROR( __glBufferData( _TYPE, size, data, TranslateDrawType( draw_type ) ) );

		// Create lock buffer data
		mBufferData.Create( size, data );

		return _true;
	}

	//!	Update data field.
	_void UpdateDataField( const DwordDataField& data_field )
	{
		if ( mUpdateDataField == DwordDataField::cNull )
		{
			mUpdateDataField = data_field;
		}
		else
		{
			if ( mUpdateDataField.CanCombine( data_field ) )
				mUpdateDataField.Combine( data_field );
			else
				mUpdateDataField.Init( 0, mBufferData.Number( ) );
		}
	}

public:
	TGLBuffer( _dword stride, _dword size, const _byte* data, _RESOURCE_DRAW_TYPE draw_type ) 
		: mResource( 0 ), mStride( stride )
	{
		mRealSize			= 0;

		mDrawType			= draw_type;

		mLockDataField		= DwordDataField::cNull;
		mUpdateDataField	= DwordDataField::cNull;

		mLastResizeTime		= 0;

		// Generate resource buffer 
		GL_CHECK_ERROR( __glGenBuffers( 1, &mResource ) );

		// Bind it
		Bind( );

		// Create buffer data
		CreateBufferData( size, data, draw_type );

		WLOG_TRACE_4( L"Create '%s(%s)' buffer data (id: %d, size:%d)",
			GetTypeString( ).Str( ), TranslateDrawType2String( draw_type ).Str( ), mResource, mBufferData.Number( ) );

		GetResourceManagerRHI( )->CreateBuffer( this );
	}

	virtual ~TGLBuffer( )
	{
		DeleteBuffer( );

		GetResourceManagerRHI( )->RemoveBuffer( this );
	}

public:
	//!	Get the resource
	EGE_GET_ACCESSOR_CONST( GLuint, Resource )
	//!	Get the buffer stride
	EGE_GET_ACCESSOR_CONST( _dword, Stride )

public:
	//!	Delete buffer.
	_void DeleteBuffer( )
	{
		if ( mResource != 0 )
		{
			_BUFFER_DELETE_FUNC( mResource );
			GL_CHECK_ERROR( __glDeleteBuffers( 1, &mResource ) );

			WLOG_TRACE_3( L"Delete '%s' buffer data (id: %d, size:%d)", GetTypeString( ).Str( ), mResource, mBufferData.Number( ) );

			mResource = 0;
		}
	}

	//!	Bind the buffer
	_void Bind( )
	{
		if ( ResourceType == _RRT_INDEX_BUFFER )
			gGLCachedState.mPendingIBO = (IndexBufferRHI*) this;
		else if ( ResourceType == _RRT_VERTEX_BUFFER )
			gGLCachedState.mPendingVBO = (VertexBufferRHI*) this;

		GL_CHECK_ERROR( _BUFFER_CACHE_BIND_FUNC( mResource ) );
	}

	//!	Reset the buffer.
	_void Reset( )
	{
		// Delete the old resource
		DeleteBuffer( );

		// Generate resource buffer 
		GL_CHECK_ERROR( __glGenBuffers( 1, &mResource ) );

		// Bind it
		Bind( );

		// Create buffer data
		GL_CHECK_ERROR( __glBufferData( _TYPE, mBufferData.Number( ), mBufferData.GetPointer( ), TranslateDrawType( mDrawType ) ) );

		WLOG_TRACE_4( L"Recreate '%s(%s)' buffer data (id: %d, size:%d)",
			GetTypeString( ).Str( ), TranslateDrawType2String( mDrawType ).Str( ), mResource, mBufferData.Number( ) );
	}

	//!	Check whether is locked.
	_ubool IsLocked( ) const
	{
		return mLockDataField.GetNumber( ) != 0;
	}

	//!	Lock.
	_byte* Lock( _dword offset, _dword size )
	{
		if ( offset == -1 || size == 0 )
			return _null;

		if ( size > mBufferData.Number( ) || offset + size > mBufferData.Number( ) )
			return _null;

		if ( IsLocked( ) )
			return _null;

		// Save the locked offset and size
		mLockDataField.Init( offset, size );

		return mBufferData.GetPointer( ) + offset;
	}

	//!	Unlock
	_void Unlock( )
	{
		if ( IsLocked( ) == _false )
			return;

		UpdateDataField( mLockDataField );

		// Clear lock info
		mLockDataField = DwordDataField::cNull;
	}

	//!	Get the buffer data
	const _byte* GetBufferData( )
	{
		return mBufferData.GetPointer( );
	}

	//!	Get the buffer size.
	_dword GetBufferSize( ) const
	{
		return mBufferData.Number( );
	}

	//!	Check whether it's dynamic or not.
	_ubool IsDynamic( ) const
	{
		return mDrawType == _RDT_TYPE_DYNAMIC;
	}

	//!	Update the buffer.
	_ubool Update( _dword offset, _dword size, const _byte* data )
	{
		if ( IsLocked( ) )
			return _false;

		_dword total_size = offset + size;
		if ( total_size > mBufferData.Number( ) )
		{
			if ( Resize( total_size ) == _false )
				return _false;
		}

		// Update the lock buffer data
		EGE_MEM_CPY( mBufferData.GetPointer( ) + offset, data, size );

		// Update data field
		UpdateDataField( DwordDataField( offset, size ) );

		return _true;
	}

	//!	Resize the buffer.
	_ubool Resize( _dword size )
	{
		EGE_ASSERT( size != 0 );

		_dword tickcount = Platform::GetCurrentTickCount( );

		// If we resize very fast then we should enlarge the size here
		_dword grow_size = 0;
		if ( mLastResizeTime != 0 && tickcount - mLastResizeTime < 100 )
			grow_size = size;

		mLastResizeTime = tickcount;

		WLOG_TRACE_5( L"Resize '%s' buffer data [%d->%d+%d] (id: %d)", GetTypeString( ).Str( ), mBufferData.Number( ), size, grow_size, mResource );

		// Resize buffer data
		_dword total_size = size + grow_size;
		if ( mBufferData.Resize( total_size ) == _false )
			return _false;

		return _true;
	}

	//! Flush.
	_ubool Flush( )
	{
		if ( mUpdateDataField != DwordDataField::cNull )
		{
			Bind( );

			// Check whether need to resize it
			if ( mBufferData.Number( ) > mRealSize )
			{
				mRealSize = mBufferData.Number( );

				// Resize buffer
				GL_CHECK_ERROR( __glBufferData( _TYPE, mRealSize, mBufferData.GetPointer( ), TranslateDrawType( mDrawType ) ) );
			}
			else
			{
				// Update buffer data
				_dword offset	= mUpdateDataField.GetOffset( );
				_dword size		= mUpdateDataField.GetNumber( );
				GL_CHECK_ERROR( __glBufferSubData( _TYPE, offset, size, mBufferData.GetPointer( ) + offset ) );
			}

			mUpdateDataField = DwordDataField::cNull;
		}

		return _true;
	}
};

typedef TGLBuffer< _RRT_INDEX_BUFFER,	GL_ELEMENT_ARRAY_BUFFER,	GLBindIBO, GLCachedBindIBO, OnIBODeletion >	GLIndexBuffer;
typedef TGLBuffer< _RRT_VERTEX_BUFFER,	GL_ARRAY_BUFFER,			GLBindVBO, GLCachedBindVBO, OnVBODeletion >	GLVertexBuffer;

//----------------------------------------------------------------------------
// TGLTexture
//----------------------------------------------------------------------------

template< _RENDER_RESOURCE_TYPE ResourceType >
class TGLTexture : public TDynamicRHIResource< ResourceType >
{
protected:
	//!	The flags
	enum _FLAG
	{
		//!	True indicates auto delete texture in destructor
		_FLAG_IS_AUTO_DELETE		= 1 << 0,
		//!	True indicates it's cube map
		_FLAG_IS_CUBE_MAP			= 1 << 1,
		//!	True indicates it's dynamic texture.
		_FLAG_IS_DYNAMIC			= 1 << 2,
		//!	True indicates lock sampler state
		_FLAG_LOCK_SAMPLER_STATE	= 1 << 3,
	};

protected:
	//!	The flags
	FlagsObject			mFlags;

	//! The texture resource
	GLuint				mResource;

	//! The texture target
	GLenum				mTarget;
	//!	The internal pixel format of the texture
	GLenum				mInternalFormat;
	//!	The data type of the texture
	GLenum				mDataType;
	//!	The size in bytes of the texture
	_dword				mSizeInBytes;

	//! The number of mip-maps in the texture
	_dword				mNumMips;
	//! The texture's pixel format
	_PIXEL_FORMAT		mPixelFormat;

	//! The size of the texture
	PointU				mSize;

	//!	The texture sampler state
	GLSamplerStateInfo	mSamplerState;

protected:
	//!	Get the target type.
	GLenum GetTargetType( _dword sub_index ) const
	{
		if ( mFlags.HasFlags( _FLAG_IS_CUBE_MAP ) )
			return GL_TEXTURE_CUBE_MAP_POSITIVE_X + sub_index;
		else
			return mTarget;
	}

	//!	Initialize.
	_void Initialize( GLuint texture, GLenum target, GLenum internalformat, GLenum datatype, _dword size_in_bytes, _dword nummips, _PIXEL_FORMAT format, const PointU& size, const GLSamplerStateInfo& sampler_state )
	{
		mResource		= texture;

		mTarget			= target;
		mInternalFormat	= internalformat;
		mDataType		= datatype;

		mSizeInBytes	= size_in_bytes;

		mNumMips		= nummips;
		mPixelFormat	= format;

		mSize			= size;

		mSamplerState	= sampler_state;

		// The texture size must be match the power of 2
		EGE_ASSERT( Math::IsPowerOf2( size.x ) );
		EGE_ASSERT( Math::IsPowerOf2( size.y ) );

		// Default we delete self
		mFlags.EnableFlags( _FLAG_IS_AUTO_DELETE, _true );

		WLOG_TRACE_4( L"Create (%d) [%dx%d(mips:%d)] GL texture", mResource, mSize.x, mSize.y, mNumMips );
	}

public:
	TGLTexture( )
	{
		mResource		= 0;

		mTarget			= GL_NONE;
		mInternalFormat	= GL_NONE;
		mDataType		= GL_NONE;

		mSizeInBytes	= 0;

		mNumMips		= 0;
		mPixelFormat	= _PF_UNKNOWN;

		mSize			= PointU::cZeroPoint;
	}
	virtual ~TGLTexture( )
	{
		if ( mFlags.HasFlags( _FLAG_IS_AUTO_DELETE ) )
			DeleteTexture( );

		GetResourceManagerRHI( )->RemoveTexture( this );
	}

public:
	//!	Get the texture resource.
	EGE_GET_ACCESSOR_CONST( GLuint, Resource )
	//!	Get the texture target.
	EGE_GET_ACCESSOR_CONST( GLenum, Target )
	//!	Get the size in bytes.
	EGE_GET_ACCESSOR_CONST( _dword, SizeInBytes )
	//!	Get the number of mips.
	EGE_GET_ACCESSOR_CONST( _dword, NumMips )
	//!	Get the texture pixel format.
	EGE_GET_ACCESSOR_CONST( _PIXEL_FORMAT, PixelFormat )
	//!	Get the texture size.
	EGE_GETR_ACCESSOR_CONST( PointU, Size )
	//!	Get the sampler state info.
	EGE_GETR_ACCESSOR_CONST( GLSamplerStateInfo, SamplerState )

public:
	TGLTexture& operator = ( const TGLTexture& texture )
	{
		UpdateResourceID( texture.mResource );

		mTarget			= texture.mTarget;
		mInternalFormat	= texture.mInternalFormat;
		mDataType		= texture.mDataType;

		mNumMips		= texture.mNumMips;
		mPixelFormat	= texture.mPixelFormat;

		mSize			= texture.mSize;

		return *this;
	}

public:
	_void InitTex( WStringPtr res_name, GLuint texture, GLenum target, GLenum internalformat, GLenum datatype, _dword size_in_bytes, _dword nummips, _PIXEL_FORMAT format, const PointU& size, const GLSamplerStateInfo& sampler_state, const _byte* pixels, _ubool is_dynamic )
	{
		Initialize( texture, target, internalformat, datatype, size_in_bytes, nummips, format, size, sampler_state );

		mFlags.EnableFlags( _FLAG_IS_DYNAMIC, is_dynamic );

		GetResourceManagerRHI( )->CreateTexture( (Texture2DRHI*) this, res_name, pixels );
	}
	_void InitCubeMapTex( WStringPtr res_name, GLuint texture, GLenum target, GLenum internalformat, GLenum datatype, _dword size_in_bytes, _dword nummips, _PIXEL_FORMAT format, const PointU& size, const GLSamplerStateInfo& sampler_state, const TextureCubeWithMipmapsRHI& mipmaps_info )
	{
		Initialize( texture, target, internalformat, datatype, size_in_bytes, nummips, format, size, sampler_state );

		mFlags.CombineFlags( _FLAG_IS_CUBE_MAP );

		GetResourceManagerRHI( )->CreateTexture( (TextureCubeRHI*) this, res_name, mipmaps_info );
	}
	_void InitCubeMapTex( WStringPtr res_name, GLuint texture, GLenum target, GLenum internalformat, GLenum datatype, _dword size_in_bytes, _dword nummips, _PIXEL_FORMAT format, const PointU& size, const GLSamplerStateInfo& sampler_state, const TextureCubeWithMipmapsRHI* mipmaps_info )
	{
		Initialize( texture, target, internalformat, datatype, size_in_bytes, nummips, format, size, sampler_state );

		mFlags.CombineFlags( _FLAG_IS_CUBE_MAP );

		GetResourceManagerRHI( )->CreateTexture( (TextureCubeRHI*) this, res_name, mipmaps_info );
	}

	//!	Check whether it's dynamic texture or not.
	_ubool IsDynamic( ) const
	{
		return mFlags.HasFlags( _FLAG_IS_DYNAMIC );
	}

	//!	Check whether it's compressed texture or not.
	_ubool IsCompressed( ) const
	{
		switch ( mPixelFormat )
		{
			case _PF_DXT1:
			case _PF_DXT3:
			case _PF_DXT5:
			case _PF_ETC1_RGB8:
			case _PF_ETC2_RGBA8:
			case _PF_RGB_PVRTC_4BPP:
			case _PF_RGB_PVRTC_2BPP:
			case _PF_RGBA_PVRTC_4BPP:
			case _PF_RGBA_PVRTC_2BPP:
				return _true;

			default:
				break;
		}

		return _false;
	}

	//!	Enable/Disable auto delete self.
	_void EnableAutoDeleteSelf( _ubool enable )
	{
		mFlags.EnableFlags( _FLAG_IS_AUTO_DELETE, enable );
	}

	//!	Update resource ID.
	_void UpdateResourceID( GLuint texture_id )
	{
		DeleteTexture( );

		mResource	= texture_id;
	}

	//!	Delete texture.
	_void DeleteTexture( )
	{
		// Release texture resource
		if ( mResource != 0 )
		{
			WLOG_TRACE_4( L"Delete (%d) [%dx%d(mips:%d)] GL texture", mResource, mSize.x, mSize.y, mNumMips );
			GL_CHECK_ERROR( __glDeleteTextures( 1, &mResource ) );

			mResource = 0;
		}
	}

	//!	Get the number of blocks of mip-maps.
	PointU GetBlocksNum( _dword mipindex ) const
	{
		// Calculate the dimensions of the mip-map.
		_dword blocksize_x 	= gPixelFormats[ mPixelFormat ].mBlockSizeX;
		_dword blocksize_y 	= gPixelFormats[ mPixelFormat ].mBlockSizeY;
		_dword mipsize_x 	= Math::Max< _dword >( mSize.x >> mipindex, blocksize_x );
		_dword mipsize_y 	= Math::Max< _dword >( mSize.y >> mipindex, blocksize_y );
		_dword numblocks_x	= ( mipsize_x + blocksize_x - 1 ) / blocksize_x;
		_dword numblocks_y	= ( mipsize_y + blocksize_y - 1 ) / blocksize_y;
		
		return PointU( numblocks_x, numblocks_y );
	}
	//!	Get block bytes.
	_dword GetBlockBytes( ) const
	{
		return gPixelFormats[mPixelFormat].mBlockBytes;
	}

	//!	Get the stride.
	_dword GetStride( _dword mipindex ) const
	{
		// Get the number of blocks
		PointU blocks_num = GetBlocksNum( mipindex );

		// Get the stride of texture pixel buffer
		return blocks_num.x * GetBlockBytes( );
	}
	//!	Get the mip size in bytes of mip-maps.
	_dword GetMipSize( _dword mipindex, _dword* stride ) const
	{
		// Get the number of blocks
		PointU blocks_num = GetBlocksNum( mipindex );

		// Get the block bytes
		_dword block_bytes = GetBlockBytes( );

		// Feedback the stride
		if ( stride != _null )
			*stride = blocks_num.x * block_bytes;

		return blocks_num.x * blocks_num.y * block_bytes;
	}

	//! Update sub-texture.
	_void UpdateSubTexture( const RectU& rect, const _byte* pixel )
	{
		EGE_ASSERT( pixel != _null );

		// Get the platform pixel format
		GLenum platform_pixel_format = (GLenum) gPixelFormats[ mPixelFormat ].mPlatformFormat;
		EGE_ASSERT( platform_pixel_format != 0 );

		// Enable and bind texture
		GLCachedSetActiveTexture( 0 );
		GLCachedBindTexture( mTarget, mResource );

		// Update texture
		GL_CHECK_ERROR( __glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ) );
		{
			GL_CHECK_ERROR( __glTexSubImage2D( GetTargetType( 0 ),
				0, 
				rect.l,
				rect.t,
				rect.GetWidth( ),
				rect.GetHeight( ),
				platform_pixel_format,
				mDataType,
				pixel ) );
		}
		GL_CHECK_ERROR( __glPixelStorei( GL_UNPACK_ALIGNMENT, 4 ) );

		// Restore the texture on stage 0
		if ( gGLCachedState.mTextures[0].mTarget != GL_NONE )
			GLCachedBindTexture( gGLCachedState.mTextures[0].mTarget, gGLCachedState.mTextures[0].mResource );

		GetResourceManagerRHI( )->UpdateTexture( (Texture2DRHI*) this, rect, pixel );
	}

	//!	Read the mip pixel buffer.
	_ubool ReadMipPixel( _byte* pixel_buffer ) const
	{
		// OpenGLES doesn't support 'glGetTexImage' API
#if (_OPENGLES_ == 1)
		return _false;
#else
		if ( pixel_buffer == _null )
			return _false;

		// Get the internal pixel format and data type
		_PIXEL_FORMAT pixel_format = mPixelFormat; GLenum internalformat = GL_RGBA; GLenum datatype = GL_UNSIGNED_BYTE;
		if ( GLHelper::FindInternalFormatAndType( pixel_format, internalformat, datatype ) == _false )
			return _false;

		// Bind texture
		GLCachedBindTexture( mTarget, mResource );

		// Read the texture image pixel buffer
		GL_CHECK_ERROR( __glGetTexImage( mTarget, 0, internalformat, datatype, pixel_buffer ) );

		return _true;
#endif
	}

	//!	Lock the texture sampler state.
	_void LockSamplerState( _ubool lock )
	{
		mFlags.EnableFlags( _FLAG_LOCK_SAMPLER_STATE, lock );
	}

	//!	Set the texture sampler state.
	_void SetSamplerState( const GLSamplerStateInfo& state )
	{
		mSamplerState = state;
	}
	//!	Update the texture sampler state.
	_void UpdateSamplerState( const GLSamplerStateInfo& state )
	{
		if ( mFlags.HasFlags( _FLAG_LOCK_SAMPLER_STATE ) )
			return;

		// Texture wrap
		if ( mSamplerState.mAddressU != state.mAddressU )
		{
			GL_CHECK_ERROR( __glTexParameteri( mTarget, GL_TEXTURE_WRAP_S, state.mAddressU ) );
			mSamplerState.mAddressU = state.mAddressU;
		}
		if ( mSamplerState.mAddressV != state.mAddressV )
		{
			GL_CHECK_ERROR( __glTexParameteri( mTarget, GL_TEXTURE_WRAP_T, state.mAddressV ) );
			mSamplerState.mAddressV = state.mAddressV;
		}
		if ( mSamplerState.mAddressW != state.mAddressW )
		{
#if (_OPENGLES_ == 0)
			GL_CHECK_ERROR( __glTexParameteri( mTarget, GL_TEXTURE_WRAP_R, state.mAddressW ) );
#endif
			mSamplerState.mAddressW = state.mAddressW;
		}

		// Texture compare mode
		if ( mSamplerState.mTextureCompareMode != state.mTextureCompareMode )
		{
#if (_OPENGLES_ == 0)
			GL_CHECK_ERROR( __glTexParameteri( mTarget, GL_TEXTURE_COMPARE_MODE, state.mTextureCompareMode ) );
#endif
			mSamplerState.mTextureCompareMode = state.mTextureCompareMode;
		}

		// Texture filter
		if ( mSamplerState.mMagFilter != state.mMagFilter )
		{
			GL_CHECK_ERROR( __glTexParameteri( mTarget, GL_TEXTURE_MAG_FILTER, state.mMagFilter ) );	
			mSamplerState.mMagFilter = state.mMagFilter;
		}
		if ( mSamplerState.mMinFilter != state.mMinFilter )
		{
			GLint gl_filter = state.mMinFilter; 
			if ( mNumMips == 1 )
			{
				if ( gl_filter == GL_NEAREST_MIPMAP_LINEAR )
					gl_filter = GL_NEAREST;
				else
					gl_filter = GL_LINEAR;
			}

			GL_CHECK_ERROR( __glTexParameteri( mTarget, GL_TEXTURE_MIN_FILTER, gl_filter ) );
			mSamplerState.mMinFilter = state.mMinFilter;
		}
	}
};

typedef TGLTexture< _RRT_TEXTURE >		GLTexture;
typedef TGLTexture< _RRT_TEXTURE_2D >	GLTexture2D;
typedef TGLTexture< _RRT_TEXTURE_CUBE >	GLTextureCube;

//----------------------------------------------------------------------------
// GLFont
//----------------------------------------------------------------------------

//! The font wrap textures and use free type face to render
class GLFont : public FontRHI
{
private:
	//!	The font info
	FontInitializerRHI		mInfo;
	//!	The freetype2 font face 
	IFontFaceRef			mFontFace;

	//!	The render font texture set
	RenderFontTextureSet*	mFontTextureSet;

public:
	GLFont( );
	virtual ~GLFont( );

public:
	//!	Get the font info.
	EGE_GETR_ACCESSOR( FontInitializerRHI, Info )
	//!	Get the font face.
	EGE_GET_ACCESSOR( IFontFace*, FontFace )

// IObject Interface
public:
	virtual IObject* CloneTo( _ubool standalone ) const override;

public:
	//!	Initialize.
	_ubool Initialize( const FontInitializerRHI& initializer, IStreamReader* stream_reader );

	//!	Clear caches.
	_void ClearCaches( );

	//!	Get font code.
	const FontCodeRHI* GetFontCode( _dword code );
	//!	Get font code with stroke info.
	const FontCodeRHI* GetFontCodeByStrokeInfo( _dword code, _dword stroke_size );
	//!	Get font code with blur info.
	const FontCodeRHI* GetFontCodeByBlurInfo( _dword code, _dword blur_size, _dword blur_factor );
};

//----------------------------------------------------------------------------
// GLVertexArrayBase
//----------------------------------------------------------------------------

class GLVertexArrayBase : public VertexArrayRHI
{
public:
	virtual _void Bind( ) PURE;
	virtual _void Unbind( ) PURE;
	virtual _ubool Setup( VertexDeclarationRHI* declaration, VertexBufferRHI* vbo, IndexBufferRHI* ibo ) PURE;
	virtual _dword GetResID( ) const PURE;
};

//----------------------------------------------------------------------------
// GLVertexArray
//----------------------------------------------------------------------------

//! The GL vertex array wrap VAO resource (hardware)
class GLVertexArray : public GLVertexArrayBase
{
private:
	//!	The VAO resource
	GLuint					mVAOResource;

	//!	The vertex declaration
	GLVertexDeclaration*	mDeclaration;
	//!	The VBO and IBO resource
	GLVertexBuffer*			mVBOResource;
	GLIndexBuffer*			mIBOResource;

private:
	_ubool Setup( );

public:
	GLVertexArray( );
	virtual ~GLVertexArray( );

public:
	EGE_GET_ACCESSOR( GLVertexBuffer*, VBOResource )
	EGE_GET_ACCESSOR( GLIndexBuffer*, IBOResource )

public:
	//!	Reset VAO.
	_ubool ResetVAO( );
	//!	Delete VAO.
	_void DeleteVAO( );

// GLVertexArrayBase Interface
public:
	virtual _void	Bind( ) override;
	virtual _void	Unbind( ) override;
	virtual _ubool	Setup( VertexDeclarationRHI* declaration, VertexBufferRHI* vbo, IndexBufferRHI* ibo ) override;
	virtual _dword	GetResID( ) const override;
};

//----------------------------------------------------------------------------
// GLSoftwareVertexArray
//----------------------------------------------------------------------------

//! The GL vertex array wrap VAO resource (software)
class GLSoftwareVertexArray : public GLVertexArrayBase
{
private:
	//!	The resource ID, just for compare usage
	_dword					mResID;

	//!	The binding VBO
	VertexBufferRHIRef		mVBO;
	//!	The binding IBO
	IndexBufferRHIRef		mIBO;

	//!	The vertex declaration
	VertexDeclarationRHIRef	mVertexDecl;

private:
	_void EnableVertexElement( const GLVertexElement& element, GLsizei stride, GLuint vbo );
	_void SetupVBO( );
	_void SetupIBO( );

public:
	GLSoftwareVertexArray( );
	virtual ~GLSoftwareVertexArray( );

// GLVertexArrayBase Interface
public:
	virtual _void	Bind( ) override;
	virtual _void	Unbind( ) override;
	virtual _ubool	Setup( VertexDeclarationRHI* declaration, VertexBufferRHI* vbo, IndexBufferRHI* ibo ) override;
	virtual _dword	GetResID( ) const override;
};

}