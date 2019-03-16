//! @file     IGraphicEffect.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicEffect
//----------------------------------------------------------------------------

class IGraphicEffect : public IObject
{
public:
	//!	Set the sampler state.
	//!	@param		tex_name		The texture name.
	//!	@param		res_name		The resource name.
	//!	@return		none.
	virtual _void SetSamplerState( const AStringObj& tex_name, const WStringObj& res_name ) PURE;
	//!	Set the cube texture sampler state.
	//!	@param		res_name		The resource name.
	//!	@return		none.
	virtual _void SetCubeTextureSamplerState( const WStringObj& res_name ) PURE;
	//!	Set the rasterizer state.
	//!	@param		res_name		The resource name.
	//!	@return		none.
	virtual _void SetRasterizerState( const WStringObj& res_name ) PURE;
	//!	Set the depth state.
	//!	@param		res_name		The resource name.
	//!	@return		none.
	virtual _void SetDepthState( const WStringObj& res_name ) PURE;
	//!	Set the stencil state.
	//!	@param		res_name		The resource name.
	//!	@return		none.
	virtual _void SetStencilState( const WStringObj& res_name ) PURE;
	//!	Set the blend state.
	//!	@param		res_name		The resource name.
	//!	@return		none.
	virtual _void SetBlendState( const WStringObj& res_name ) PURE;

	//!	Set the sampler state.
	//!	@param		tex_name		The texture name.
	//!	@param		state			The sampler state.
	//!	@return		none.
	virtual _void SetSamplerState( const AStringObj& tex_name, SamplerStateRHI* state ) PURE;
	//!	Set the cube texture sampler state.
	//!	@param		state			The sampler state.
	//!	@return		none.
	virtual _void SetCubeTextureSamplerState( SamplerStateRHI* state ) PURE;
	//!	Set the rasterizer state.
	//!	@param		state			The rasterizer state.
	//!	@return		none.
	virtual _void SetRasterizerState( RasterizerStateRHI* state ) PURE;
	//!	Set the depth state.
	//!	@param		state			The depth state.
	//!	@return		none.
	virtual _void SetDepthState( DepthStateRHI* state ) PURE;
	//!	Set the stencil state.
	//!	@param		state			The stencil state.
	//!	@return		none.
	virtual _void SetStencilState( StencilStateRHI* state ) PURE;
	//!	Set the blend state.
	//!	@param		state			The blend state.
	//!	@return		none.
	virtual _void SetBlendState( BlendStateRHI* state ) PURE;

	//!	Get the sampler state.
	//!	@param		tex_name		The texture name.
	//!	@return		The sampler state.
	virtual SamplerStateRHI* GetSamplerState( const AStringObj& tex_name ) const PURE;
	//!	Get the cube texture sampler state.
	//!	@param		none.
	//!	@return		The sampler state.
	virtual SamplerStateRHI* GetCubeTextureSamplerState( ) const PURE;
	//!	Get the rasterizer state.
	//!	@param		none.
	//!	@return		The rasterizer state.
	virtual RasterizerStateRHI* GetRasterizerState( ) const PURE;
	//!	Get the depth state.
	//!	@param		none.
	//!	@return		The depth state.
	virtual DepthStateRHI* GetDepthState( ) const PURE;
	//!	Get the stencil state.
	//!	@param		none.
	//!	@return		The stencil state.
	virtual StencilStateRHI* GetStencilState( ) const PURE;
	//!	Get the blend state.
	//!	@param		none.
	//!	@return		The blend state.
	virtual BlendStateRHI* GetBlendState( ) const PURE;

	//!	Set the render states.
	//!	@param		state_info		The state info.
	//!	@return		none.
	virtual _void SetRenderStates( const GraphicRenderStateInfo& state_info ) PURE;
	//!	Get the render states.
	//!	@param		none.
	//!	@return		The state info.
	virtual const GraphicRenderStateInfo& GetRenderStates( ) const PURE;

	//!	Push the current states.
	//!	@param		none.
	//!	@return		none.
	virtual _void PushStates( ) PURE;
	//!	Pop the top of states stack and resume current states.
	//!	@param		none.
	//!	@return		none.
	virtual _void PopStates( ) PURE;
	//!	Get the render states stack.
	//!	@param		none.
	//!	@return		The render states stack.
	virtual const GraphicRenderStateInfoStack& GetStates( ) const PURE;

	//!	Set the render queue type.
	//!	@param		type	The render queue type.
	//!	@return		none.
	virtual _void SetRenderQueueType( _GRAPHIC_RENDER_QUEUE type ) PURE;
	//!	Get the render queue type.
	//!	@param		none.
	//!	@return		The render queue type.
	virtual _GRAPHIC_RENDER_QUEUE GetRenderQueueType( ) const PURE;

	//!	Get unique ID of bound shader.
	//!	@param		none.
	//!	@return		The unique ID.
	virtual _dword GetUniqueID( ) const PURE;
	//!	Get bound shader.
	//!	@param		none.
	//!	@return		The bound shader.
	virtual BoundShaderRHI* GetBoundShader( ) const PURE;

	//!	Get pixel shader code.
	//!	@param		none.
	//!	@return		The pixel shader code.
	virtual AStringPtr GetPSCode( ) const PURE;
	//!	Get original pixel shader code.
	//!	@param		none.
	//!	@return		The pixel shader code.
	virtual AStringPtr GetOriginalPSCode( ) const PURE;

	//!	Get vertex shader code.
	//!	@param		none.
	//!	@return		The vertex shader code.
	virtual AStringPtr GetVSCode( ) const PURE;
	//!	Get original vertex shader code.
	//!	@param		none.
	//!	@return		The vertex shader code.
	virtual AStringPtr GetOriginalVSCode( ) const PURE;

	//!	Get the UBO CRC value.
	//!	@param		none.
	//!	@return		The UBO CRC value.
	virtual _crcvalue GetUBOCRCValue( ) PURE;

	//!	Reset uniform buffers.
	//!	@param		none.
	//!	@return		none.
	virtual _void ResetUBOs( ) PURE;
	//!	Get uniform buffers.
	//!	@param		number		The number of UBO buffers.
	//!	@param		total_size	The total size of UBO buffers.
	//!	@return		The uniform buffers data.
	virtual const _byte* GetUBOs( _dword& number, _dword& total_size ) const PURE;

	//!	Check whether has specified uniform buffer.
	//!	@param		name		The uniform buffer name.
	//!	@return		True indicates UBO is existing.
	virtual _ubool HasUBO( const AStringObj& name ) const PURE;

	//!	Update boolean value uniform buffer.
	//!	@param		name		The uniform buffer name.
	//!	@param		value		The boolean value.
	//!	@return		none.
	virtual _void SetUBO( const AStringObj& name, _ubool value ) PURE;
	//!	Update signed integer value uniform buffer.
	//!	@param		name		The uniform buffer name.
	//!	@param		value		The boolean value.
	//!	@return		none.
	virtual _void SetUBO( const AStringObj& name, _int value ) PURE;
	//!	Update unsigned integer value uniform buffer.
	//!	@param		name		The uniform buffer name.
	//!	@param		value		The boolean value.
	//!	@return		none.
	virtual _void SetUBO( const AStringObj& name, _dword value ) PURE;
	//!	Update float value uniform buffer.
	//!	@param		name		The uniform buffer name.
	//!	@param		value		The float value.
	//!	@return		none.
	virtual _void SetUBO( const AStringObj& name, _float value ) PURE;
	//!	Update color uniform buffer.
	//!	@param		name		The uniform buffer name.
	//!	@param		color		The color.
	//!	@return		none.
	virtual _void SetUBO( const AStringObj& name, const Color& color ) PURE;
	//!	Update 2-float values uniform buffer.
	//!	@param		name		The uniform buffer name.
	//!	@param		value		The 2-floats value.
	//!	@return		none.
	virtual _void SetUBO( const AStringObj& name, const Vector2& value ) PURE;
	//!	Update 3-float values uniform buffer.
	//!	@param		name		The uniform buffer name.
	//!	@param		value		The 3-floats value.
	//!	@return		none.
	virtual _void SetUBO( const AStringObj& name, const Vector3& value ) PURE;
	//!	Update 4-float values uniform buffer.
	//!	@param		name		The uniform buffer name.
	//!	@param		value		The 4-floats value.
	//!	@return		none.
	virtual _void SetUBO( const AStringObj& name, const Vector4& value ) PURE;
	//!	Update matrix uniform buffer.
	//!	@param		name		The uniform buffer name.
	//!	@param		transform	The matrix transform.
	//!	@param		transpose	True indicates will transpose in shader.
	//!	@return		none.
	virtual _void SetUBO( const AStringObj& name, const Matrix3& transform, _ubool transpose ) PURE;
	//!	Update matrix uniform buffer.
	//!	@param		name		The uniform buffer name.
	//!	@param		transform	The matrix transform.
	//!	@param		transpose	True indicates will transpose in shader.
	//!	@return		none.
	virtual _void SetUBO( const AStringObj& name, const Matrix4& transform, _ubool transpose ) PURE;
	//!	Update uniform buffer of bound shader.
	//!	@param		name		The uniform buffer name.
	//!	@param		data_type	The buffer data type.
	//!	@param		size		The buffer size in bytes.
	//!	@param		buffer		The buffer data.
	//!	@return		none.
	virtual _void SetUBO( const AStringObj& name, _UNIFORM_BUFFER_DATA_TYPE data_type, _dword size, const _byte* buffer ) PURE;

	//!	Syn the textures.
	//!	@remark		It will syn textures info into shader.
	//!	@param		textures	The textures.
	//!	@return		none.
	virtual _void SynTextures( const Texture2DRHIRefMap& textures ) PURE;

	//!	Link.
	//!	@param		none.
	//!	@return		True indicates success false indicates failure.
	virtual _ubool Link( ) PURE;

	//!	Optimize.
	//!	@param		none.
	//!	@return		True indicates success false indicates failure.
	virtual _ubool Optimize( ) PURE;
	//!	Check whether has optimized.
	//!	@param		none.
	//!	@return		True indicates has optimized
	virtual _ubool HasOptimized( ) const PURE;
};

}