//! @file     RenderStateSerializer.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// RenderStateSerializer Implementation
//----------------------------------------------------------------------------

_dword RenderStateSerializer::OnQuerySamplerFilterEnumValue( WStringPtr name )
{
	if ( name.IsEqual( L"Nearest", _true ) )
		return _SF_NEAREST;
	else if ( name.IsEqual( L"Linear", _true ) )
		return _SF_LINEAR;

	return -1;
}

_dword RenderStateSerializer::OnQuerySamplerAddressModeEnumValue( WStringPtr name )
{
	if ( name.IsEqual( L"Wrap", _true ) )
		return _SAM_WRAP;
	else if ( name.IsEqual( L"Clamp", _true ) )
		return _SAM_CLAMP;
	else if ( name.IsEqual( L"ClampToEdge", _true ) )
		return _SAM_CLAMP_TO_EDGE;
	else if ( name.IsEqual( L"Mirror", _true ) )
		return _SAM_MIRROR;
	else if ( name.IsEqual( L"Repeat", _true ) )
		return _SAM_REPEAT;

	return -1;
}

_dword RenderStateSerializer::OnQueryRasterizerFillModeEnumValue( WStringPtr name )
{
	if ( name.IsEqual( L"Point", _true ) )
		return _RFM_POINT;
	else if ( name.IsEqual( L"WireFrame", _true ) )
		return _RFM_WIREFRAME;
	else if ( name.IsEqual( L"Solid", _true ) )
		return _RFM_SOLID;

	return -1;
}

_dword RenderStateSerializer::OnQueryRasterizerCullModeEnumValue( WStringPtr name )
{
	if ( name.IsEqual( L"None", _true ) )
		return _RCM_NONE;
	else if ( name.IsEqual( L"CW", _true ) )
		return _RCM_CW;
	else if ( name.IsEqual( L"CCW", _true ) )
		return _RCM_CCW;

	return -1;
}

_dword RenderStateSerializer::OnQueryCompareFunctionEnumValue( WStringPtr name )
{
	if ( name.IsEqual( L"Less", _true ) )
		return _CF_LESS;
	else if ( name.IsEqual( L"LessEqual", _true ) )
		return _CF_LESS_EQUAL;
	else if ( name.IsEqual( L"Greater", _true ) )
		return _CF_GREATER;
	else if ( name.IsEqual( L"GreaterEqual", _true ) )
		return _CF_GREATER_EQUAL;
	else if ( name.IsEqual( L"Equal", _true ) )
		return _CF_EQUAL;
	else if ( name.IsEqual( L"Never", _true ) )
		return _CF_NEVER;
	else if ( name.IsEqual( L"Always", _true ) )
		return _CF_ALWAYS;

	return -1;
}

_dword RenderStateSerializer::OnQueryStencilOperationEnumValue( WStringPtr name )
{
	if ( name.IsEqual( L"Keep", _true ) )
		return _SO_KEEP;
	else if ( name.IsEqual( L"Zero", _true ) )
		return _SO_ZERO;
	else if ( name.IsEqual( L"Replace", _true ) )
		return _SO_REPLACE;
	else if ( name.IsEqual( L"SaturatedIncrmenet", _true ) )
		return _SO_SATURATED_INCREMENT;
	else if ( name.IsEqual( L"SaturatedDecrmenet", _true ) )
		return _SO_SATURATED_DECREMENT;
	else if ( name.IsEqual( L"Invert", _true ) )
		return _SO_INVERT;
	else if ( name.IsEqual( L"Incrmenet", _true ) )
		return _SO_INCREMENT;
	else if ( name.IsEqual( L"Decrmenet", _true ) )
		return _SO_DECREMENT;

	return -1;
}

_dword RenderStateSerializer::OnQueryBlendFactorEnumValue( WStringPtr name )
{
	if ( name.IsEqual( L"Zero", _true ) )
		return _BF_ZERO;
	else if ( name.IsEqual( L"One", _true ) )
		return _BF_ONE;
	else if ( name.IsEqual( L"SourceColor", _true ) )
		return _BF_SOURCE_COLOR;
	else if ( name.IsEqual( L"InverseSourceColor", _true ) )
		return _BF_INVERSE_SOURCE_COLOR;
	else if ( name.IsEqual( L"SourceAlpha", _true ) )
		return _BF_SOURCE_ALPHA;
	else if ( name.IsEqual( L"InverseSourceAlpha", _true ) )
		return _BF_INVERSE_SOURCE_ALPHA;
	else if ( name.IsEqual( L"DestAlpha", _true ) )
		return _BF_DEST_ALPHA;
	else if ( name.IsEqual( L"InverseDestAlpha", _true ) )
		return _BF_INVERSE_DEST_ALPHA;
	else if ( name.IsEqual( L"DestColor", _true ) )
		return _BF_DEST_COLOR;
	else if ( name.IsEqual( L"InverseDestColor", _true ) )
		return _BF_INVERSE_DEST_COLOR;

	return -1;
}

WStringPtr RenderStateSerializer::OnQuerySamplerFilterEnumName( _dword value )
{
	switch ( value )
	{
		case _SF_NEAREST:	return L"Nearest";
		case _SF_LINEAR:	return L"Linear";
		default:
			return L"";
	}
}

WStringPtr RenderStateSerializer::OnQuerySamplerAddressModeEnumName( _dword value )
{
	switch ( value )
	{
		case _SAM_WRAP:				return L"Wrap";
		case _SAM_CLAMP:			return L"Clamp";
		case _SAM_CLAMP_TO_EDGE:	return L"ClampToEdge";
		case _SAM_MIRROR:			return L"Mirror";
		case _SAM_REPEAT:			return L"Repeat";
		default:
			return L"";
	}
}

WStringPtr RenderStateSerializer::OnQueryRasterizerFillModeEnumName( _dword value )
{
	switch ( value )
	{
		case _RFM_POINT:		return L"Point";
		case _RFM_WIREFRAME:	return L"WireFrame";
		case _RFM_SOLID:		return L"Solid";
		default:
			return L"";
	}
}

WStringPtr RenderStateSerializer::OnQueryRasterizerCullModeEnumName( _dword value )
{
	switch ( value )
	{
		case _RCM_NONE:	return L"None";
		case _RCM_CW:	return L"CW";
		case _RCM_CCW:	return L"CCW";
		default:
			return L"";
	}
}

WStringPtr RenderStateSerializer::OnQueryCompareFunctionEnumName( _dword value )
{
	switch ( value )
	{
		case _CF_LESS:			return L"Less";
		case _CF_LESS_EQUAL:	return L"LessEqual";
		case _CF_GREATER:		return L"Greater";
		case _CF_GREATER_EQUAL:	return L"GreaterEqual";
		case _CF_EQUAL:			return L"Equal";
		case _CF_NEVER:			return L"Never";
		case _CF_ALWAYS:		return L"Always";
		default:
			return L"";
	}
}

WStringPtr RenderStateSerializer::OnQueryStencilOperationEnumName( _dword value )
{
	switch ( value )
	{
		case _SO_KEEP:					return L"Keep";
		case _SO_ZERO:					return L"Zero";
		case _SO_REPLACE:				return L"Replace";
		case _SO_SATURATED_INCREMENT:	return L"SaturatedIncrmenet";
		case _SO_SATURATED_DECREMENT:	return L"SaturatedDecrmenet";
		case _SO_INVERT:				return L"Invert";
		case _SO_INCREMENT:				return L"Incrmenet";
		case _SO_DECREMENT:				return L"Decrmenet";
		default:
			return L"";
	}
}

WStringPtr RenderStateSerializer::OnQueryBlendFactorEnumName( _dword value )
{
	switch ( value )
	{
		case _BF_ZERO:					return L"Zero";
		case _BF_ONE:					return L"One";
		case _BF_SOURCE_COLOR:			return L"SourceColor";
		case _BF_INVERSE_SOURCE_COLOR:	return L"InverseSourceColor";
		case _BF_SOURCE_ALPHA:			return L"SourceAlpha";
		case _BF_INVERSE_SOURCE_ALPHA:	return L"InverseSourceAlpha";
		case _BF_DEST_ALPHA:			return L"DestAlpha";
		case _BF_INVERSE_DEST_ALPHA:	return L"InverseDestAlpha";
		case _BF_DEST_COLOR:			return L"DestColor";
		case _BF_INVERSE_DEST_COLOR:	return L"InverseDestColor";
		default:
			return L"";
	}
}

_ubool RenderStateSerializer::ImportSamplerState( ISerializableNode* state_node, GraphicRenderStateInfo& render_states )
{
	ISerializableNodeRef node = state_node->GetChildNodeByName( L"Sampler" );
	if ( node.IsValid( ) )
	{
		do
		{
			// Initialize sampler state arguments
			SamplerStateInitializerRHI init( _SF_LINEAR );
			node->ReadEnum( L"Filter", (_dword&) init.mFilter, _false, OnQuerySamplerFilterEnumValue );
			node->ReadEnum( L"AddressU", (_dword&) init.mAddressU, _false, OnQuerySamplerAddressModeEnumValue );
			node->ReadEnum( L"AddressV", (_dword&) init.mAddressV, _false, OnQuerySamplerAddressModeEnumValue );
			node->ReadEnum( L"AddressW", (_dword&) init.mAddressW, _false, OnQuerySamplerAddressModeEnumValue );

			// Read the texture index
			_dword index = -1;
			if ( node->Read( L"Index", index ) == _false )
				return _false;

			render_states.mSamplerStates[ index ] = GetDynamicRHI( )->CreateSamplerState( init ).GetPtr( );
			if ( render_states.mSamplerStates[ index ] == _null )
				return _false;
		}
		while( node->MoveNext( L"Sampler" ) );
	}

	return _true;
}

_ubool RenderStateSerializer::ImportRasterizerState( ISerializableNode* state_node, GraphicRenderStateInfo& render_states )
{
	ISerializableNodeRef node = state_node->GetChildNodeByName( L"Rasterizer" );
	if ( node.IsValid( ) )
	{
		// Initialize rasterizer state arguments
		RasterizerStateInitializerRHI init( _true, _true, _true, _true, _RFM_SOLID, _RCM_NONE );
		node->ReadEnum( L"FillMode", (_dword&) init.mFillMode, _false, OnQueryRasterizerFillModeEnumValue );
		node->ReadEnum( L"CullMode", (_dword&) init.mCullMode, _false, OnQueryRasterizerCullModeEnumValue );

		render_states.mRasterizerState = GetDynamicRHI( )->CreateRasterizerState( init ).GetPtr( );
		if ( render_states.mRasterizerState == _null )
			return _false;
	}

	return _true;
}

_ubool RenderStateSerializer::ImportDepthState( ISerializableNode* state_node, GraphicRenderStateInfo& render_states )
{
	ISerializableNodeRef node = state_node->GetChildNodeByName( L"Depth" );
	if ( node.IsValid( ) )
	{
		// Initialize depth state arguments
		DepthStateInitializerRHI init( _true, _CF_LESS_EQUAL );
		node->Read( L"EnableDepthWrite", init.mEnableDepthWrite );
		node->ReadEnum( L"DepthTest", (_dword&) init.mDepthTest, _false, OnQueryCompareFunctionEnumValue );

		render_states.mDepthState = GetDynamicRHI( )->CreateDepthState( init ).GetPtr( );
		if ( render_states.mDepthState == _null )
			return _false;
	}

	return _true;
}

_ubool RenderStateSerializer::ImportStencilState( ISerializableNode* state_node, GraphicRenderStateInfo& render_states )
{
	ISerializableNodeRef node = state_node->GetChildNodeByName( L"Stencil" );
	if ( node.IsValid( ) )
	{
		// Initialize stencil state arguments
		StencilStateInitializerRHI init;
		node->Read( L"EnableFrontFaceStencil", init.mEnableFrontFaceStencil );
		node->ReadEnum( L"FrontFaceStencilTest", (_dword&) init.mFrontFaceStencilTest, _false, OnQueryCompareFunctionEnumValue );
		node->ReadEnum( L"FrontFaceStencilFailStencilOp", (_dword&) init.mFrontFaceStencilFailStencilOp, _false, OnQueryStencilOperationEnumValue );
		node->ReadEnum( L"FrontFaceDepthFailStencilOp", (_dword&) init.mFrontFaceDepthFailStencilOp, _false, OnQueryStencilOperationEnumValue );
		node->ReadEnum( L"FrontFacePassStencilOp", (_dword&) init.mFrontFacePassStencilOp, _false, OnQueryStencilOperationEnumValue );
		node->Read( L"EnableBackFaceStencil", init.mEnableBackFaceStencil );
		node->ReadEnum( L"BackFaceStencilTest", (_dword&) init.mBackFaceStencilTest, _false, OnQueryCompareFunctionEnumValue );
		node->ReadEnum( L"BackFaceStencilFailStencilOp", (_dword&) init.mBackFaceStencilFailStencilOp, _false, OnQueryStencilOperationEnumValue );
		node->ReadEnum( L"BackFaceDepthFailStencilOp", (_dword&) init.mBackFaceDepthFailStencilOp, _false, OnQueryStencilOperationEnumValue );
		node->ReadEnum( L"BackFacePassStencilOp", (_dword&) init.mBackFacePassStencilOp, _false, OnQueryStencilOperationEnumValue );
		node->Read( L"StencilReadMask", init.mStencilReadMask );
		node->Read( L"StencilWriteMask", init.mStencilWriteMask );
		node->Read( L"StencilRef", init.mStencilRef );

		render_states.mStencilState = GetDynamicRHI( )->CreateStencilState( init ).GetPtr( );
		if ( render_states.mStencilState == _null )
			return _false;
	}

	return _true;
}

_ubool RenderStateSerializer::ImportBlendState( ISerializableNode* state_node, GraphicRenderStateInfo& render_states )
{
	ISerializableNodeRef node = state_node->GetChildNodeByName( L"Blend" );
	if ( node.IsValid( ) )
	{
		// Initialize blend state arguments
		BlendStateInitializerRHI init;
		node->Read( L"Enable", init.mEnableBlend );
		node->ReadEnum( L"ColorSourceBlendFactor", (_dword&) init.mColorSourceBlendFactor, _false, OnQueryBlendFactorEnumValue );
		node->ReadEnum( L"ColorDestBlendFactor", (_dword&) init.mColorDestBlendFactor, _false, OnQueryBlendFactorEnumValue );
		node->ReadEnum( L"AlphaSourceBlendFactor", (_dword&) init.mAlphaSourceBlendFactor, _false, OnQueryBlendFactorEnumValue );
		node->ReadEnum( L"AlphaDestBlendFactor", (_dword&) init.mAlphaDestBlendFactor, _false, OnQueryBlendFactorEnumValue );

		render_states.mBlendState = GetDynamicRHI( )->CreateBlendState( init ).GetPtr( );
		if ( render_states.mBlendState == _null )
			return _false;
	}

	return _true;
}

_ubool RenderStateSerializer::ImportRenderStates( ISerializableNode* node, GraphicRenderStateInfo& render_states )
{
	// The render state node can be null
	ISerializableNodeRef state_node = node->GetChildNodeByName( L"RenderStats" );
	if ( state_node.IsValid( ) )
	{
		// Import render states
		if ( ImportSamplerState( state_node, render_states ) == _false )
			return _false;

		// Import rasterizer state
		if ( ImportRasterizerState( state_node, render_states ) == _false )
			return _false;

		// Import depth state
		if ( ImportDepthState( state_node, render_states ) == _false )
			return _false;

		// Import stencil state
		if ( ImportStencilState( state_node, render_states ) == _false )
			return _false;

		// Import blend state
		if ( ImportBlendState( state_node, render_states ) == _false )
			return _false;
	}

	return _true;
}

_ubool RenderStateSerializer::ExportSamplerState( ISerializableNode* node, const GraphicRenderStateInfo& render_states )
{
	for ( _dword i = 0; i < render_states.mSamplerStates.Number( ); i ++ )
	{
		const SamplerStateRHI* sampler_state = render_states.mSamplerStates[i];
		if ( sampler_state == _null )
			continue;

		ISerializableNodeRef state_node = node->InsertChildNode( L"Sampler", L"", _false );
		if ( state_node.IsNull( ) )
			return _false;

		// Write sampler state arguments
		SamplerStateInitializerRHI init = GetDynamicRHI( )->GetSamplerState( sampler_state );
		state_node->WriteEnum( L"Filter", init.mFilter, _false, OnQuerySamplerFilterEnumName );
		state_node->WriteEnum( L"AddressU", init.mAddressU, _false, OnQuerySamplerAddressModeEnumName );
		state_node->WriteEnum( L"AddressV", init.mAddressV, _false, OnQuerySamplerAddressModeEnumName );
		state_node->WriteEnum( L"AddressW", init.mAddressW, _false, OnQuerySamplerAddressModeEnumName );

		// Write the texture index
		if ( state_node->Write( L"Index", i ) == _false )
			return _false;
	}

	return _true;
}

_ubool RenderStateSerializer::ExportRasterizerState( ISerializableNode* node, const GraphicRenderStateInfo& render_states )
{
	if ( render_states.mRasterizerState != _null )
	{
		ISerializableNodeRef state_node = node->InsertChildNode( L"Rasterizer", L"", _false );
		if ( state_node.IsValid( ) )
		{
			// Write rasterizer state arguments
			RasterizerStateInitializerRHI init = GetDynamicRHI( )->GetRasterizerState( render_states.mRasterizerState );
			state_node->WriteEnum( L"FillMode", init.mFillMode, _false, OnQueryRasterizerFillModeEnumName );
			state_node->WriteEnum( L"CullMode", init.mCullMode, _false, OnQueryRasterizerCullModeEnumName );
		}
	}

	return _true;
}

_ubool RenderStateSerializer::ExportDepthState( ISerializableNode* node, const GraphicRenderStateInfo& render_states )
{
	if ( render_states.mDepthState != _null )
	{
		ISerializableNodeRef state_node = node->InsertChildNode( L"Depth", L"", _false );
		if ( state_node.IsValid( ) )
		{
			// Write depth state arguments
			DepthStateInitializerRHI init = GetDynamicRHI( )->GetDepthState( render_states.mDepthState );
			state_node->Write( L"EnableDepthWrite", init.mEnableDepthWrite );
			state_node->WriteEnum( L"DepthTest", init.mDepthTest, _false, OnQueryCompareFunctionEnumName );
		}
	}

	return _true;
}

_ubool RenderStateSerializer::ExportStencilState( ISerializableNode* node, const GraphicRenderStateInfo& render_states )
{
	if ( render_states.mStencilState != _null )
	{
		ISerializableNodeRef state_node = node->InsertChildNode( L"Stencil", L"", _false );
		if ( state_node.IsValid( ) )
		{
			// Write stencil state arguments
			StencilStateInitializerRHI init = GetDynamicRHI( )->GetStencilState( render_states.mStencilState );
			state_node->Write( L"EnableFrontFaceStencil", init.mEnableFrontFaceStencil );
			state_node->WriteEnum( L"FrontFaceStencilTest", init.mFrontFaceStencilTest, _false, OnQueryCompareFunctionEnumName );
			state_node->WriteEnum( L"FrontFaceStencilFailStencilOp", init.mFrontFaceStencilFailStencilOp, _false, OnQueryStencilOperationEnumName );
			state_node->WriteEnum( L"FrontFaceDepthFailStencilOp", init.mFrontFaceDepthFailStencilOp, _false, OnQueryStencilOperationEnumName );
			state_node->WriteEnum( L"FrontFacePassStencilOp", init.mFrontFacePassStencilOp, _false, OnQueryStencilOperationEnumName );
			state_node->Write( L"EnableBackFaceStencil", init.mEnableBackFaceStencil );
			state_node->WriteEnum( L"BackFaceStencilTest", init.mBackFaceStencilTest, _false, OnQueryCompareFunctionEnumName );
			state_node->WriteEnum( L"BackFaceStencilFailStencilOp", init.mBackFaceStencilFailStencilOp, _false, OnQueryStencilOperationEnumName );
			state_node->WriteEnum( L"BackFaceDepthFailStencilOp", init.mBackFaceDepthFailStencilOp, _false, OnQueryStencilOperationEnumName );
			state_node->WriteEnum( L"BackFacePassStencilOp", init.mBackFacePassStencilOp, _false, OnQueryStencilOperationEnumName );
			state_node->Write( L"StencilReadMask", init.mStencilReadMask );
			state_node->Write( L"StencilWriteMask", init.mStencilWriteMask );
			state_node->Write( L"StencilRef", init.mStencilRef );
		}
	}

	return _true;
}

_ubool RenderStateSerializer::ExportBlendState( ISerializableNode* node, const GraphicRenderStateInfo& render_states )
{
	if ( render_states.mBlendState != _null )
	{
		ISerializableNodeRef state_node = node->InsertChildNode( L"Blend", L"", _false );
		if ( state_node.IsValid( ) )
		{
			// Write blend state arguments
			BlendStateInitializerRHI init = GetDynamicRHI( )->GetBlendState( render_states.mBlendState );
			state_node->Write( L"Enable", init.mEnableBlend );
			state_node->WriteEnum( L"ColorSourceBlendFactor", init.mColorSourceBlendFactor, _false, OnQueryBlendFactorEnumName );
			state_node->WriteEnum( L"ColorDestBlendFactor", init.mColorDestBlendFactor, _false, OnQueryBlendFactorEnumName );
			state_node->WriteEnum( L"AlphaSourceBlendFactor", init.mAlphaSourceBlendFactor, _false, OnQueryBlendFactorEnumName );
			state_node->WriteEnum( L"AlphaDestBlendFactor", init.mAlphaDestBlendFactor, _false, OnQueryBlendFactorEnumName );
		}
	}

	return _true;
}

_ubool RenderStateSerializer::ExportRenderStates( ISerializableNode* node, const GraphicRenderStateInfo& render_states )
{
	ISerializableNodeRef state_node = node->InsertChildNode( L"RenderStats", L"", _false );
	if ( state_node.IsNull( ) )
		return _false;

	// Export render states
	if ( ExportSamplerState( state_node, render_states ) == _false )
		return _false;

	// Export rasterizer state
	if ( ExportRasterizerState( state_node, render_states ) == _false )
		return _false;

	// Export depth state
	if ( ExportDepthState( state_node, render_states ) == _false )
		return _false;

	// Export stencil state
	if ( ExportStencilState( state_node, render_states ) == _false )
		return _false;

	// Export blend state
	if ( ExportBlendState( state_node, render_states ) == _false )
		return _false;

	return _true;
}
