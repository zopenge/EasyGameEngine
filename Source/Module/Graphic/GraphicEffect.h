//! @file     GraphicEffect.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicEffect
//----------------------------------------------------------------------------

class GraphicEffect : public TObject< IGraphicEffect >
{
private:
	//!	The uniform buffer info
	struct UniformBufferInfo : public GraphicUniformBuffer
	{
		//!	The original transform buffer
		_byte*	mOriginalTransformBuffer;

		UniformBufferInfo( )
		{
			mOriginalTransformBuffer = _null;
		}
		UniformBufferInfo( _UNIFORM_BUFFER_DATA_TYPE type, _dword location, _dword size, const AStringObj& name )
			: GraphicUniformBuffer( type, location, size, name )
		{
			mOriginalTransformBuffer = _null;
		}
	};
	//!	Use the UBO's name as key.
	typedef Map< UniformBufferInfo, AStringObj > UniformBufferInfoMap;
	
private:
	//!	The render slot
	_GRAPHIC_RENDER_QUEUE		mRenderQueueType;
	//!	The render states stack
	GraphicRenderStateInfoStack	mRenderStates;

	//!	The active UBO CRC value
	_crcvalue					mUBOCRCValue;
	//!	True indicates we need to refresh the UBO's CRC value
	_ubool						mIsNeedRefreshCRCValue;
	//!	The latest UBO buffers size in bytes
	_dword						mLatestUBOBufferSize;
	//!	The latest UBO buffers data 
	MemArrayPtr< _byte >		mLatestUBOBufferData;

	//!	The latest uniform buffer array
	UniformBufferInfoMap		mLatestUBOs;

	//!	The unique ID
	_dword						mUniqueID;
	//!	The original VS code
	AStringObj					mOriginalVSCode;
	//!	The original PS code
	AStringObj					mOriginalPSCode;
	//!	The optimized VS code
	AStringObj					mOptimizedVSCode;
	//!	The optimized PS code
	AStringObj					mOptimizedPSCode;

	//!	The bound shader
	BoundShaderRHIRef			mBoundShaders;

private:
	//!	Get the uniform buffer type size in bytes.
	static _dword GetUnBOTypeSize( _UNIFORM_BUFFER_DATA_TYPE data_type );

private:
	//!	Transpose matrix.
	template< typename Type >
	_void TransposeMatrix( _byte* buffer, _dword size );
	_void TransposeMatrix( _UNIFORM_BUFFER_DATA_TYPE type, _byte* buffer, _dword size );

	//!	Free all uniform buffers.
	_void FreeAllUniformBuffers( );

	//!	Get uniform buffer by name.
	UniformBufferInfo* GetUBO( const AStringObj& name, _UNIFORM_BUFFER_DATA_TYPE data_type, _dword size );

	//!	Update matrix uniform buffers.
	_void SetMatrixUBO( const AStringObj& name, _UNIFORM_BUFFER_DATA_TYPE data_type, _dword size, const _byte* buffer, _ubool transpose );
	_void SetMatrixUBO( UniformBufferInfo* ubo_info, _UNIFORM_BUFFER_DATA_TYPE data_type, _dword size, const _byte* buffer, _ubool transpose );

	//! Syn with texture.
	_void SynTexture( _dword slot_index, const AStringObj& tex_name, Texture2DRHI* texture );

	//!	Link.
	_ubool Link( AStringPtr ps_code, AStringPtr vs_code );

	//!	Build macros code.
	AStringR BuildMacroCode( AStringPtr macros ) const;

public:
	GraphicEffect( );
	virtual ~GraphicEffect( );

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr vs_code, AStringPtr ps_code, AStringPtr macros );
	_ubool Initialize( BoundShaderRHI* bound_shader );

// IGraphicEffect Interface
public:
	virtual _void								SetSamplerState( const AStringObj& tex_name, const WStringObj& res_name ) override;
	virtual _void								SetCubeTextureSamplerState( const WStringObj& res_name ) override;
	virtual _void								SetRasterizerState( const WStringObj& res_name ) override;
	virtual _void								SetDepthState( const WStringObj& res_name ) override;
	virtual _void								SetStencilState( const WStringObj& res_name ) override;
	virtual _void								SetBlendState( const WStringObj& res_name ) override;

	virtual _void								SetSamplerState( const AStringObj& tex_name, SamplerStateRHI* state ) override;
	virtual _void								SetCubeTextureSamplerState( SamplerStateRHI* state ) override;
	virtual _void								SetRasterizerState( RasterizerStateRHI* state ) override;
	virtual _void								SetDepthState( DepthStateRHI* state ) override;
	virtual _void								SetStencilState( StencilStateRHI* state ) override;
	virtual _void								SetBlendState( BlendStateRHI* state ) override;

	virtual SamplerStateRHI*					GetSamplerState( const AStringObj& tex_name ) const override;
	virtual SamplerStateRHI*					GetCubeTextureSamplerState( ) const override;
	virtual RasterizerStateRHI*					GetRasterizerState( ) const override;
	virtual DepthStateRHI*						GetDepthState( ) const override;
	virtual StencilStateRHI*					GetStencilState( ) const override;
	virtual BlendStateRHI*						GetBlendState( ) const override;

	virtual _void								SetRenderStates( const GraphicRenderStateInfo& state_info ) override;
	virtual const GraphicRenderStateInfo&		GetRenderStates( ) const override;

	virtual _void								PushStates( ) override;
	virtual _void								PopStates( ) override;
	virtual const GraphicRenderStateInfoStack&	GetStates( ) const override;

	virtual _void								SetRenderQueueType( _GRAPHIC_RENDER_QUEUE type ) override;
	virtual _GRAPHIC_RENDER_QUEUE				GetRenderQueueType( ) const override;

	virtual _dword								GetUniqueID( ) const override;
	virtual BoundShaderRHI*						GetBoundShader( ) const override;

	virtual AStringPtr							GetPSCode( ) const override;
	virtual AStringPtr							GetOriginalPSCode( ) const override;

	virtual AStringPtr							GetVSCode( ) const override;
	virtual AStringPtr							GetOriginalVSCode( ) const override;

	virtual _crcvalue							GetUBOCRCValue( ) override;

	virtual _void								ResetUBOs( ) override;
	virtual const _byte*						GetUBOs( _dword& number, _dword& total_size ) const override;

	virtual _ubool								HasUBO( const AStringObj& name ) const override;

	virtual _void								SetUBO( const AStringObj& name, _ubool value ) override;
	virtual _void								SetUBO( const AStringObj& name, _int value ) override;
	virtual _void								SetUBO( const AStringObj& name, _dword value ) override;
	virtual _void								SetUBO( const AStringObj& name, _float value ) override;
	virtual _void								SetUBO( const AStringObj& name, const Color& color ) override;
	virtual _void								SetUBO( const AStringObj& name, const Vector2& value ) override;
	virtual _void								SetUBO( const AStringObj& name, const Vector3& value ) override;
	virtual _void								SetUBO( const AStringObj& name, const Vector4& value ) override;
	virtual _void								SetUBO( const AStringObj& name, const Matrix3& transform, _ubool transpose ) override;
	virtual _void								SetUBO( const AStringObj& name, const Matrix4& transform, _ubool transpose ) override;
	virtual _void								SetUBO( const AStringObj& name, _UNIFORM_BUFFER_DATA_TYPE data_type, _dword size, const _byte* buffer ) override;

	virtual _void								SynTextures( const Texture2DRHIRefMap& textures ) override;

	virtual _ubool								Link( ) override;

	virtual _ubool								Optimize( ) override;
	virtual _ubool								HasOptimized( ) const override;
};

}