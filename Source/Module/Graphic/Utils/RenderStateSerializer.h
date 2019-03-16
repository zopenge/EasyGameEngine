//! @file     RenderStateSerializer.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RenderStateSerializer
//----------------------------------------------------------------------------

class RenderStateSerializer
{
private:
	//!	When query the sampler filter enumeration value.
	static _dword OnQuerySamplerFilterEnumValue( WStringPtr name );
	//!	When query the sampler address mode enumeration value.
	static _dword OnQuerySamplerAddressModeEnumValue( WStringPtr name );
	//!	When query the rasterizer fill mode enumeration value.
	static _dword OnQueryRasterizerFillModeEnumValue( WStringPtr name );
	//!	When query the rasterizer cull mode enumeration value.
	static _dword OnQueryRasterizerCullModeEnumValue( WStringPtr name );
	//!	When query the compare function enumeration value.
	static _dword OnQueryCompareFunctionEnumValue( WStringPtr name );
	//!	When query the stencil operation enumeration value.
	static _dword OnQueryStencilOperationEnumValue( WStringPtr name );
	//!	When query the blend factor enumeration value.
	static _dword OnQueryBlendFactorEnumValue( WStringPtr name );

	//!	When query the sampler filter enumeration name.
	static WStringPtr OnQuerySamplerFilterEnumName( _dword value );
	//!	When query the sampler address mode enumeration name.
	static WStringPtr OnQuerySamplerAddressModeEnumName( _dword value );
	//!	When query the rasterizer fill mode enumeration name.
	static WStringPtr OnQueryRasterizerFillModeEnumName( _dword value );
	//!	When query the rasterizer cull mode enumeration name.
	static WStringPtr OnQueryRasterizerCullModeEnumName( _dword value );
	//!	When query the compare function enumeration name.
	static WStringPtr OnQueryCompareFunctionEnumName( _dword value );
	//!	When query the stencil operation enumeration name.
	static WStringPtr OnQueryStencilOperationEnumName( _dword value );
	//!	When query the blend factor enumeration name.
	static WStringPtr OnQueryBlendFactorEnumName( _dword value );

public:
	//!	Import sampler/rasterizer/depth/stencil/blend state.
	static _ubool ImportSamplerState( ISerializableNode* node, GraphicRenderStateInfo& render_states );
	static _ubool ImportRasterizerState( ISerializableNode* node, GraphicRenderStateInfo& render_states );
	static _ubool ImportDepthState( ISerializableNode* node, GraphicRenderStateInfo& render_states );
	static _ubool ImportStencilState( ISerializableNode* node, GraphicRenderStateInfo& render_states );
	static _ubool ImportBlendState( ISerializableNode* node, GraphicRenderStateInfo& render_states );

	//!	Import render states.
	static _ubool ImportRenderStates( ISerializableNode* node, GraphicRenderStateInfo& render_states );

	//!	Export sampler/rasterizer/depth/stencil/blend state.
	static _ubool ExportSamplerState( ISerializableNode* node, const GraphicRenderStateInfo& render_states );
	static _ubool ExportRasterizerState( ISerializableNode* node, const GraphicRenderStateInfo& render_states );
	static _ubool ExportDepthState( ISerializableNode* node, const GraphicRenderStateInfo& render_states );
	static _ubool ExportStencilState( ISerializableNode* node, const GraphicRenderStateInfo& render_states );
	static _ubool ExportBlendState( ISerializableNode* node, const GraphicRenderStateInfo& render_states );
	//!	Export render states.
	static _ubool ExportRenderStates( ISerializableNode* node, const GraphicRenderStateInfo& render_states );
};

//----------------------------------------------------------------------------
// RenderStateSerializer Implementation
//----------------------------------------------------------------------------

}