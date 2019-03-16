//! @file     GraphicEffect.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicEffect Implementation
//----------------------------------------------------------------------------

GraphicEffect::GraphicEffect( )
{
	mRenderQueueType		= _GRAPHIC_RENDER_TRANSPARENT;

	mUBOCRCValue			= 0;
	mIsNeedRefreshCRCValue	= _false;
	mLatestUBOBufferSize	= 0;

	mUniqueID				= 0;

	// Push the initial render states
	mRenderStates.Push( GraphicRenderStateInfo( ) );

	// Set the default render states
	SetSamplerState( ASTROBJ( uDiffuseTex ), WSTROBJ( SamplerLinear ) );
	SetBlendState( WSTROBJ( BlendMix ) );
}

GraphicEffect::~GraphicEffect( )
{
	FreeAllUniformBuffers( );
}

_dword GraphicEffect::GetUnBOTypeSize( _UNIFORM_BUFFER_DATA_TYPE data_type )
{
	switch ( data_type )
	{
		case _UBDT_BOOL:		return sizeof( _int );
		case _UBDT_LONG:		return sizeof( _int );
		case _UBDT_VEC1:		return sizeof( _float );
		case _UBDT_VEC2:		return sizeof( Vector2 );
		case _UBDT_VEC3:		return sizeof( Vector3 );
		case _UBDT_VEC4:		return sizeof( Vector4 );
		case _UBDT_MATRIX_3x3:	return sizeof( Matrix3 );
		case _UBDT_MATRIX_4x4:	return sizeof( Matrix4 );
		case _UBDT_BUFFER:		return 1; // Buffer use 1 bytes as element
		default:
			return 0;
	}
}

template< typename Type >
_void GraphicEffect::TransposeMatrix( _byte* buffer, _dword size )
{
	for ( _dword i = 0; i < size; i += sizeof( Type ) )
		((Type*)(buffer + i))->Transpose( );
}

_void GraphicEffect::TransposeMatrix( _UNIFORM_BUFFER_DATA_TYPE type, _byte* buffer, _dword size )
{
	if ( type == _UBDT_MATRIX_3x3 )
	{
		TransposeMatrix< Matrix3 >( buffer, size );
	}
	else if ( type == _UBDT_MATRIX_4x4 )
	{
		TransposeMatrix< Matrix4 >( buffer, size );
	}
}

_void GraphicEffect::FreeAllUniformBuffers( )
{
	for ( UniformBufferInfoMap::Iterator it = mLatestUBOs.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		UniformBufferInfo& uniform_buffer = it.GetObject( );

		EGE_FREE( uniform_buffer.mBuffer );
		EGE_FREE( uniform_buffer.mOriginalTransformBuffer );
	}
}

GraphicEffect::UniformBufferInfo* GraphicEffect::GetUBO( const AStringObj& name, _UNIFORM_BUFFER_DATA_TYPE data_type, _dword size )
{
	if ( name.IsEmpty( ) )
		return _null;

	if ( size == 0 )
		return _null;

	// Try to get the existing UBO
	UniformBufferInfo* ubo_info = mLatestUBOs.Search( name );
	if ( ubo_info != _null )
		return ubo_info;

	// Get the active location
	_dword location = gDynamicRHI->ActiveUniformBuffer( mBoundShaders, data_type, name, size );
	if ( location == -1 )
		return _null;

	// Insert uniform buffer info
	mLatestUBOs[ name ] = UniformBufferInfo( data_type, location, size, name );
	return &mLatestUBOs[ name ];
}

_void GraphicEffect::SetMatrixUBO( const AStringObj& name, _UNIFORM_BUFFER_DATA_TYPE data_type, _dword size, const _byte* buffer, _ubool transpose )
{
	// Get the UBO
	UniformBufferInfo* ubo_info = GetUBO( name, data_type, size );
	if ( ubo_info == _null )
		return;

	SetMatrixUBO( ubo_info, data_type, size, buffer, transpose );
}

_void GraphicEffect::SetMatrixUBO( UniformBufferInfo* ubo_info, _UNIFORM_BUFFER_DATA_TYPE data_type, _dword size, const _byte* buffer, _ubool transpose )
{
	// Start to update modified uniform buffers
	if ( ubo_info->mBuffer == _null )
	{
		// Update uniform buffer
		ubo_info->mType		= data_type;
		ubo_info->mSize		= size;
		ubo_info->mBuffer	= (_byte*) ::malloc( size );

		// If it's transposed buffer the we need to backup original buffer
		if ( transpose )
		{
			ubo_info->mOriginalTransformBuffer = (_byte*) ::malloc( size );
			EGE_MEM_CPY( ubo_info->mOriginalTransformBuffer, buffer, size );
		}
	}
	// If the allocated buffer size is less than update size then re-allocate it
	else if ( ubo_info->mSize < size )
	{
		// Reallocate transform buffer
		ubo_info->mBuffer	= (_byte*) ::realloc( ubo_info->mBuffer, size );
		ubo_info->mSize	= size;

		// Update original buffer
		if ( ubo_info->mOriginalTransformBuffer != _null )
		{
			ubo_info->mOriginalTransformBuffer = (_byte*) ::realloc( ubo_info->mOriginalTransformBuffer, size );
			EGE_MEM_CPY( ubo_info->mOriginalTransformBuffer, buffer, size );
		}
	}
	else
	{
		// Check whether need to update buffer
		if ( EGE_MEM_CMP( ubo_info->mOriginalTransformBuffer, buffer, size ) == 0 )
			return;

		EGE_MEM_CPY( ubo_info->mOriginalTransformBuffer, buffer, size );
	}

	// Update uniform buffer data
	EGE_ASSERT( ubo_info->mBuffer != _null );
	EGE_MEM_CPY( ubo_info->mBuffer, buffer, size );

	// Transpose matrix if needed
	if ( transpose )
		TransposeMatrix( data_type, ubo_info->mBuffer, size );

	// Need to update UBO's CRC value
	mIsNeedRefreshCRCValue = _true;
}

_void GraphicEffect::SynTexture( _dword slot_index, const AStringObj& tex_name, Texture2DRHI* texture )
{
	// Syn texture slot index
	SetUBO( tex_name, slot_index );

	// Syn texture size
	Vector2 tex_size = ConvertPoint2Vector2( GetDynamicRHI( )->GetTexture2DSize( texture ) );
	SetUBO( tex_name + "Size", tex_size );
}

_ubool GraphicEffect::Link( AStringPtr ps_code, AStringPtr vs_code )
{
	// Create PS
	PixelShaderRHIRef ps = GetGraphicResourceManager( )->CreatePixelShader( ps_code );
	if ( ps.IsNull( ) )
	{
		WLOG_ERROR( L"Create PS shader failed" );
		return _false;
	}

	// Create VS
	VertexShaderRHIRef vs = GetGraphicResourceManager( )->CreateVertexShader( vs_code );
	if ( vs.IsNull( ) )
	{
		WLOG_ERROR( L"Create VS shader failed" );
		return _false;
	}

	// Create bound shader
	mBoundShaders = gDynamicRHI->CreateBoundShader( vs, ps );
	if ( mBoundShaders.IsNull( ) )
	{
		WLOG_ERROR( L"Create bound shader failed" );
		return _false;
	}

	// Update unique ID
	mUniqueID = AString( ps_code + vs_code ).GetCRCValue( );

	return _true;
}

AStringR GraphicEffect::BuildMacroCode( AStringPtr macros ) const
{
	AStringArray defined_macros;
	StringFormatter::SplitString( macros, defined_macros, "|", " \t" );

	AString code;
	for ( _dword i = 0; i < defined_macros.Number( ); i ++ )
		code += "#define " + defined_macros[i] + "\n";
	code += "\n";

	return code;
}

_ubool GraphicEffect::Initialize( AStringPtr vs_code, AStringPtr ps_code, AStringPtr macros )
{
	AString macro_code = BuildMacroCode( macros );

	mOriginalVSCode		= "#define _VS_\n" + macro_code + vs_code;
	mOriginalPSCode		= "#define _PS_\n" + macro_code + ps_code;
	mOptimizedVSCode	= "";
	mOptimizedPSCode	= "";

	if ( Link( ) == _false )
		return _false;

	return _true;
}

_ubool GraphicEffect::Initialize( BoundShaderRHI* bound_shader )
{
	if ( bound_shader == _null )
		return _false;

	mOriginalVSCode		= gDynamicRHI->GetVertexShaderCode( bound_shader );
	mOriginalPSCode		= gDynamicRHI->GetPixelShaderCode( bound_shader );
	mOptimizedVSCode	= mOriginalVSCode;
	mOptimizedPSCode	= mOriginalPSCode;

	mBoundShaders		= bound_shader;

	return _true;
}

_void GraphicEffect::SetSamplerState( const AStringObj& tex_name, const WStringObj& res_name )
{
	SetSamplerState( tex_name, GetGraphicResourceManager( )->GetSamplerStateFromResName( res_name ) );
}

_void GraphicEffect::SetCubeTextureSamplerState( const WStringObj& res_name ) 
{
	SetCubeTextureSamplerState( GetGraphicResourceManager( )->GetSamplerStateFromResName( res_name ) );
}

_void GraphicEffect::SetRasterizerState( const WStringObj& res_name )
{
	SetRasterizerState( GetGraphicResourceManager( )->GetRasterizerStateFromResName( res_name ) );
}

_void GraphicEffect::SetDepthState( const WStringObj& res_name )
{
	SetDepthState( GetGraphicResourceManager( )->GetDepthStateFromResName( res_name ) );
}

_void GraphicEffect::SetStencilState( const WStringObj& res_name )
{
	SetStencilState( GetGraphicResourceManager( )->GetStencilStateFromResName( res_name ) );
}

_void GraphicEffect::SetBlendState( const WStringObj& res_name )
{
	SetBlendState( GetGraphicResourceManager( )->GetBlendStateFromResName( res_name ) );
}

_void GraphicEffect::SetSamplerState( const AStringObj& tex_name, SamplerStateRHI* state )
{
	mRenderStates.Top( ).mSamplerStates[ tex_name ] = state;
}

_void GraphicEffect::SetCubeTextureSamplerState( SamplerStateRHI* state )
{
	mRenderStates.Top( ).mCubeTextureSamplerState = state;
}

_void GraphicEffect::SetRasterizerState( RasterizerStateRHI* state )
{
	mRenderStates.Top( ).mRasterizerState = state;
}

_void GraphicEffect::SetDepthState( DepthStateRHI* state )
{
	mRenderStates.Top( ).mDepthState = state;
}

_void GraphicEffect::SetStencilState( StencilStateRHI* state )
{
	mRenderStates.Top( ).mStencilState = state;
}

_void GraphicEffect::SetBlendState( BlendStateRHI* state )
{
	mRenderStates.Top( ).mBlendState = state;
}

SamplerStateRHI* GraphicEffect::GetSamplerState( const AStringObj& tex_name ) const
{
	const SamplerStateRHIRef* state = mRenderStates.Top( ).mSamplerStates.Search( tex_name );
	if ( state == _null )
		return _null;

	return *state;
}

SamplerStateRHI* GraphicEffect::GetCubeTextureSamplerState( ) const
{
	return mRenderStates.Top( ).mCubeTextureSamplerState;
}

RasterizerStateRHI* GraphicEffect::GetRasterizerState( ) const
{
	return mRenderStates.Top( ).mRasterizerState;
}

DepthStateRHI* GraphicEffect::GetDepthState( ) const
{
	return mRenderStates.Top( ).mDepthState;
}

StencilStateRHI* GraphicEffect::GetStencilState( ) const
{
	return mRenderStates.Top( ).mStencilState;
}

BlendStateRHI* GraphicEffect::GetBlendState( ) const
{
	return mRenderStates.Top( ).mBlendState;
}

_void GraphicEffect::SetRenderStates( const GraphicRenderStateInfo& state_info )
{
	mRenderStates.Top( ) = state_info;
}

const GraphicRenderStateInfo& GraphicEffect::GetRenderStates( ) const
{
	return mRenderStates.Top( );
}

_void GraphicEffect::PushStates( )
{
	GraphicRenderStateInfo states = mRenderStates.Top( );
	mRenderStates.Push( states );
}

_void GraphicEffect::PopStates( )
{
	mRenderStates.Pop( );
}

const GraphicRenderStateInfoStack& GraphicEffect::GetStates( ) const
{
	return mRenderStates;
}

_void GraphicEffect::SetRenderQueueType( _GRAPHIC_RENDER_QUEUE type )
{
	mRenderQueueType = type;
}

_GRAPHIC_RENDER_QUEUE GraphicEffect::GetRenderQueueType( ) const
{
	return mRenderQueueType;
}

_dword GraphicEffect::GetUniqueID( ) const
{
	return mUniqueID;
}

BoundShaderRHI* GraphicEffect::GetBoundShader( ) const
{
	return mBoundShaders.GetPtr( );
}

AStringPtr GraphicEffect::GetPSCode( ) const
{
	return gDynamicRHI->GetPixelShaderCode( mBoundShaders );
}

AStringPtr GraphicEffect::GetOriginalPSCode( ) const
{
	return mOriginalPSCode;
}

AStringPtr GraphicEffect::GetVSCode( ) const
{
	return gDynamicRHI->GetVertexShaderCode( mBoundShaders );
}

AStringPtr GraphicEffect::GetOriginalVSCode( ) const
{
	return mOriginalVSCode;
}

_crcvalue GraphicEffect::GetUBOCRCValue( )
{
	if ( mIsNeedRefreshCRCValue )
	{
		// Prepare to flush latest UBOs
		mUBOCRCValue			= 0;
		mLatestUBOBufferSize	= 0;

		// Get the total UBO size in bytes
		EGE_ASSERT( mLatestUBOs.Number( ) != 0 );
		for ( UniformBufferInfoMap::Iterator it = mLatestUBOs.GetHeadIterator( ); it.IsValid( ); ++ it )
		{
			const GraphicUniformBuffer& ubo_info = it.GetObject( );

			// Update total size
			mLatestUBOBufferSize += sizeof( GraphicUniformBuffer ) + ubo_info.mSize;
		}

		// We must have something to do
		EGE_ASSERT( mLatestUBOBufferSize != 0 );

		// Resize buffer to write
		mLatestUBOBufferData.Resize( mLatestUBOBufferSize );

		// Save the active(updated) UBOs
		_byte* info_start_address	= mLatestUBOBufferData.GetPointer( );
		_byte* buffer_start_address = mLatestUBOBufferData.GetPointer( ) + mLatestUBOs.Number( ) * sizeof( GraphicUniformBuffer );
		for ( UniformBufferInfoMap::Iterator it = mLatestUBOs.GetHeadIterator( ); it.IsValid( ); ++ it )
		{
			const GraphicUniformBuffer& ubo_info = it.GetObject( );

			// Get the size
			_dword size = ubo_info.mSize;
			EGE_ASSERT( size != 0 );

			// Get the buffer
			const _byte* buffer = ubo_info.mBuffer;
			EGE_ASSERT( buffer != _null );

			// Update CRC value
			mUBOCRCValue = CRC::BuildFromBuffer( buffer, size, mUBOCRCValue );

			// Write UBO buffer
			EGE_MEM_CPY( buffer_start_address, buffer, size );
			buffer_start_address += size;

			// Write UBO info
			EGE_MEM_CPY( info_start_address, &ubo_info, sizeof( GraphicUniformBuffer ) );
			info_start_address += sizeof( GraphicUniformBuffer );
		}

		EGE_ASSERT( info_start_address == mLatestUBOBufferData.GetPointer( ) + mLatestUBOs.Number( ) * sizeof( GraphicUniformBuffer ) );
		EGE_ASSERT( buffer_start_address == mLatestUBOBufferData.GetPointer( ) + mLatestUBOBufferSize );

		mIsNeedRefreshCRCValue = _false;
	}

	return mUBOCRCValue;
}

_void GraphicEffect::ResetUBOs( )
{
	// Clear UBOs info
	mUBOCRCValue			= 0;
	mIsNeedRefreshCRCValue	= _true;

	FreeAllUniformBuffers( );
}

const _byte* GraphicEffect::GetUBOs( _dword& number, _dword& total_size ) const
{
	number		= mLatestUBOs.Number( );
	total_size	= mLatestUBOBufferSize;

	return mLatestUBOBufferData.GetPointer( );
}

_ubool GraphicEffect::HasUBO( const AStringObj& name ) const
{
	if ( mLatestUBOs.HasKey( name ) )
		return _true;

	if ( gDynamicRHI->GetUniformBufferLocation( mBoundShaders, name ) != -1 )
		return _true;

	return _false;
}

_void GraphicEffect::SetUBO( const AStringObj& name, _ubool value )
{
	SetUBO( name, _UBDT_BOOL, sizeof( value ), (const _byte*)&value );
}

_void GraphicEffect::SetUBO( const AStringObj& name, _int value )
{
	SetUBO( name, _UBDT_LONG, sizeof( value ), (const _byte*)&value );
}

_void GraphicEffect::SetUBO( const AStringObj& name, _dword value )
{
	SetUBO( name, _UBDT_LONG, sizeof( value ), (const _byte*)&value );
}

_void GraphicEffect::SetUBO( const AStringObj& name, _float value )
{
	SetUBO( name, _UBDT_VEC1, sizeof( value ), (const _byte*)&value );
}

_void GraphicEffect::SetUBO( const AStringObj& name, const Color& color )
{
	const _float color_components[4] =
	{
		color.Red( ),
		color.Green( ),
		color.Blue( ),
		color.Alpha( ),
	};

	SetUBO( name, _UBDT_VEC4, sizeof( color_components ), (const _byte*)&color_components );
}

_void GraphicEffect::SetUBO( const AStringObj& name, const Vector2& value )
{
	SetUBO( name, _UBDT_VEC2, sizeof( value ), (const _byte*)&value );
}

_void GraphicEffect::SetUBO( const AStringObj& name, const Vector3& value )
{
	SetUBO( name, _UBDT_VEC3, sizeof( value ), (const _byte*)&value );
}

_void GraphicEffect::SetUBO( const AStringObj& name, const Vector4& value )
{
	SetUBO( name, _UBDT_VEC4, sizeof( value ), (const _byte*)&value );
}

_void GraphicEffect::SetUBO( const AStringObj& name, const Matrix3& transform, _ubool transpose )
{
	SetMatrixUBO( name, _UBDT_MATRIX_3x3, sizeof( transform ), (const _byte*)&transform, transpose );
}

_void GraphicEffect::SetUBO( const AStringObj& name, const Matrix4& transform, _ubool transpose )
{
	SetMatrixUBO( name, _UBDT_MATRIX_4x4, sizeof( transform ), (const _byte*)&transform, transpose );
}

_void GraphicEffect::SetUBO( const AStringObj& name, _UNIFORM_BUFFER_DATA_TYPE data_type, _dword size, const _byte* buffer )
{
	EGE_ASSERT( size != 0 );

	// Get the modified uniform buffers
	UniformBufferInfo* ubo_info = GetUBO( name, data_type, size );
	if ( ubo_info == _null )
		return;

	// It's matrix type
	if ( data_type == _UBDT_MATRIX_3x3 || data_type == _UBDT_MATRIX_4x4 )
	{
		SetMatrixUBO( ubo_info, data_type, size, buffer, _true );
	}
	else
	{
		// It's must not the matrix type
		EGE_ASSERT( ubo_info->mOriginalTransformBuffer == _null );

		// Start to update modified uniform buffers
		if ( ubo_info->mBuffer == _null )
		{
			// Update uniform buffer
			ubo_info->mType		= data_type;
			ubo_info->mSize		= size;
			ubo_info->mBuffer	= (_byte*) ::malloc( size );
		}
		// If the allocated buffer size is less than update size then re-allocate it
		else if ( ubo_info->mSize < size )
		{
			// Reallocate transform buffer
			ubo_info->mBuffer	= (_byte*) ::realloc( ubo_info->mBuffer, size );
			ubo_info->mSize		= size;
		}
		else
		{
			// Check whether need to update buffer
			if ( EGE_MEM_CMP( ubo_info->mBuffer, buffer, size ) == 0 )
				return;
		}

		// Update uniform buffer data
		EGE_ASSERT( ubo_info->mBuffer != _null );
		EGE_MEM_CPY( ubo_info->mBuffer, buffer, size );

		// Need to update UBO's CRC value
		mIsNeedRefreshCRCValue = _true;
	}
}

_void GraphicEffect::SynTextures( const Texture2DRHIRefMap& textures )
{
	_dword slot_index = 0;

	for ( Texture2DRHIRefMap::Iterator it = textures.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		const AStringObj& tex_name = it.GetKey( );

		// Get the texture
		Texture2DRHI* texture = it.GetObject( );
		if ( texture == _null )
			continue;

		SynTexture( slot_index ++, tex_name, texture );
	}
}

_ubool GraphicEffect::Link( )
{
	// Link in optimized mode
	if ( HasOptimized( ) )
	{
		if ( Link( mOptimizedPSCode, mOptimizedVSCode ) == _false )
			return _false;
	}
	// Link in normal mode
	else
	{
		if ( Link( mOriginalPSCode, mOriginalVSCode ) == _false )
			return _false;
	}

	return _true;
}

_ubool GraphicEffect::Optimize( )
{
	// Optimize PS code
	AString optimized_ps_code = GetGraphicResourceManager( )->OptimizePixelShader( mOriginalPSCode );
	if ( optimized_ps_code.IsEmpty( ) )
		return _false;

	// Optimize VS code
	AString optimized_vs_code = GetGraphicResourceManager( )->OptimizePixelShader( mOriginalVSCode );
	if ( optimized_vs_code.IsEmpty( ) )
		return _false;

	// Save it
	mOptimizedPSCode = optimized_ps_code;
	mOptimizedVSCode = optimized_vs_code;

	return _true;
}

_ubool GraphicEffect::HasOptimized( ) const
{
	if ( mOptimizedPSCode.IsEmpty( ) || mOptimizedVSCode.IsEmpty( ) )
		return _false;

	return _true;
}
