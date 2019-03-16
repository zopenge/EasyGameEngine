//! @file     GraphicSharedEffect.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicSharedEffect Implementation
//----------------------------------------------------------------------------

GraphicSharedEffect::GraphicSharedEffect( IGraphicEffect* effect, const GraphicEffectBase& base_info )
{
	EGE_ASSERT( effect != _null );

	// Update the base info
	mBaseInfo = base_info;

	// We only share the internal effect
	mEffect = effect->GetInternalEffect( );
	EGE_ASSERT( mEffect.IsValid( ) );

	// Update the render states, remember do not push the it from (mEffect), because the it could be the shared effect
	SetRenderStates( effect->GetRenderStates( ) );
}

GraphicSharedEffect::GraphicSharedEffect( IGraphicEffect* effect, const GraphicMaterialInfo& info )
{
	EGE_ASSERT( effect != _null );

	// We only share the internal effect
	mEffect = effect->GetInternalEffect( );
	EGE_ASSERT( mEffect.IsValid( ) );

	// Update the base info
	mBaseInfo = effect->GetBaseInfo( );

	// Update the render states, remember do not push the it from (mEffect), because the it could be the shared effect
	SetRenderStates( effect->GetRenderStates( ) );

	// Update sampler render states
	for ( _dword i = 0; i < _TEXRES_MAX_NUMBER; i ++ )
	{
		SamplerStateRHIRef sampler_state = GetGraphicShaderManager( )->GetInternalSamplerState( (_GRAPHIC_INTERNAL_SAMPLER_STATE_TYPE) info.mTexNames.mSamplerStates[i] );
		if ( sampler_state.IsNull( ) )
			continue;

		WStringPtr tex_res_name = info.mTexNames.mResNames[i];
		if ( tex_res_name.IsEmpty( ) )
			continue;

		_dword tex_slot_index = GetTexSlotIndex( (_TEXRES_ID)i );
		if ( tex_slot_index == -1 )
			continue;

		SetSamplerState( tex_slot_index, sampler_state );
	}

	// Get render states
	RasterizerStateRHIRef	rasterizer_state	= GetGraphicShaderManager( )->GetInternalRasterizerState( info.mRasterizerStateType );
	DepthStateRHIRef		depth_state			= GetGraphicShaderManager( )->GetInternalDepthState( info.mDepthStateType );
	StencilStateRHIRef		stencil_state		= GetGraphicShaderManager( )->GetInternalStencilState( info.mStencilStateType );
	BlendStateRHIRef		blend_state			= GetGraphicShaderManager( )->GetInternalBlendState( info.mBlendStateType );

	// Update render states
	if ( rasterizer_state.IsValid( ) )
		SetRasterizerState( rasterizer_state );
	if ( depth_state.IsValid( ) )
		SetDepthState( depth_state );
	if ( stencil_state.IsValid( ) )
		SetStencilState( stencil_state );
	if ( blend_state.IsValid( ) )
		SetBlendState( blend_state );
}

GraphicSharedEffect::~GraphicSharedEffect( )
{
}

WStringPtr GraphicSharedEffect::GetName( ) const
{
	return mEffect->GetName( );
}

const GraphicEffectBase& GraphicSharedEffect::GetBaseInfo( ) const
{
	return mBaseInfo;
}

const FlagsObject& GraphicSharedEffect::GetEnabledFunctions( ) const
{
	return mEffect->GetEnabledFunctions( );
}

const FlagsObject& GraphicSharedEffect::GetEnabledSlotFunctions( _GRAPHIC_LIGHT_SLOT slot ) const
{
	return mEffect->GetEnabledSlotFunctions( slot );
}

_ubool GraphicSharedEffect::IsShared( ) const
{
	return _true;
}

IGraphicEffect* GraphicSharedEffect::GetInternalEffect( ) const
{
	return mEffect->GetInternalEffect( );
}

BoundShaderRHI* GraphicSharedEffect::GetBoundShader( ) const
{
	return mEffect->GetBoundShader( );
}

AStringPtr GraphicSharedEffect::GetPSCode( ) const
{
	return mEffect->GetPSCode( );
}

AStringPtr GraphicSharedEffect::GetVSCode( ) const
{
	return mEffect->GetVSCode( );
}

_crcvalue GraphicSharedEffect::GetUBOCRCValue( )
{
	return mEffect->GetUBOCRCValue( );
}

_void GraphicSharedEffect::ResetUBOs( )
{
	mEffect->ResetUBOs( );
}

const _byte* GraphicSharedEffect::GetUBOs( _dword& number, _dword& total_size ) const
{
	return mEffect->GetUBOs( number, total_size );
}

_ubool GraphicSharedEffect::HasUBO( _GRAPHIC_UBT type ) const
{
	return mEffect->HasUBO( type );
}

_void GraphicSharedEffect::SetUBO( _GRAPHIC_UBT type, _ubool value )
{
	mEffect->SetUBO( type, value );
}

_void GraphicSharedEffect::SetUBO( _GRAPHIC_UBT type, _int value )
{
	mEffect->SetUBO( type, value );
}

_void GraphicSharedEffect::SetUBO( _GRAPHIC_UBT type, _float value )
{
	mEffect->SetUBO( type, value );
}

_void GraphicSharedEffect::SetUBO( _GRAPHIC_UBT type, const Vector2& value )
{
	mEffect->SetUBO( type, value );
}

_void GraphicSharedEffect::SetUBO( _GRAPHIC_UBT type, const Vector3& value )
{
	mEffect->SetUBO( type, value );
}

_void GraphicSharedEffect::SetUBO( _GRAPHIC_UBT type, const Vector4& value )
{
	mEffect->SetUBO( type, value );
}

_void GraphicSharedEffect::SetUBO( _GRAPHIC_UBT type, const Matrix3& transform, _ubool transpose )
{
	mEffect->SetUBO( type, transform, transpose );
}

_void GraphicSharedEffect::SetUBO( _GRAPHIC_UBT type, const Matrix4& transform, _ubool transpose )
{
	mEffect->SetUBO( type, transform, transpose );
}

_void GraphicSharedEffect::SetUBO( _GRAPHIC_UBT type, _UNIFORM_BUFFER_DATA_TYPE data_type, _dword size, const _byte* buffer )
{
	mEffect->SetUBO( type, data_type, size, buffer );
}

_void GraphicSharedEffect::SetLDRColorUBO( _GRAPHIC_UBT type, const Color& color )
{
	mEffect->SetLDRColorUBO( type, color );
}

_void GraphicSharedEffect::SetHDRColorUBO( _GRAPHIC_UBT type, const Vector4& color )
{
	mEffect->SetHDRColorUBO( type, color );
}

_dword GraphicSharedEffect::GetTexSlotIndex( _TEXRES_ID id )
{
	return mEffect->GetTexSlotIndex( id );
}

_void GraphicSharedEffect::SynTextureInfo( Texture2DRHI** textures )
{
	mEffect->SynTextureInfo( textures );
}

_void GraphicSharedEffect::CombineRenderStates( IGraphicEffect* effect )
{
	CombineRenderStatesFromEffect( effect );
}

_ubool GraphicSharedEffect::Compile( )
{
	return mEffect->Compile( );
}

GraphicShaderSerializeInfo GraphicSharedEffect::GetExportInfo( ) const
{
	GraphicShaderSerializeInfo export_info = mEffect->GetExportInfo( );

	export_info.mBaseInfoNode = GetBaseInfo( ).ToSerializableNode( );

	return export_info;
}
