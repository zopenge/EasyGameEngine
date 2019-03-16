//! @file     GraphicAsyncEffect.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicAsyncEffect Implementation
//----------------------------------------------------------------------------

GraphicAsyncEffect::GraphicAsyncEffect( IGraphicEffect* effect )
{
	EGE_ASSERT( effect != _null );

	mEffect = effect;
}

GraphicAsyncEffect::~GraphicAsyncEffect( )
{
}

_void GraphicAsyncEffect::SetSamplerState( _dword index, SamplerStateRHI* state )
{
	mEffect->SetSamplerState( index, state );
}

_void GraphicAsyncEffect::SetCubeTextureSamplerState( SamplerStateRHI* state )
{
	mEffect->SetCubeTextureSamplerState( state );
}

_void GraphicAsyncEffect::SetRasterizerState( RasterizerStateRHI* state )
{
	mEffect->SetRasterizerState( state );
}

_void GraphicAsyncEffect::SetDepthState( DepthStateRHI* state )
{
	mEffect->SetDepthState( state );
}

_void GraphicAsyncEffect::SetStencilState( StencilStateRHI* state )
{
	mEffect->SetStencilState( state );
}

_void GraphicAsyncEffect::SetBlendState( BlendStateRHI* state )
{
	mEffect->SetBlendState( state );
}

SamplerStateRHI* GraphicAsyncEffect::GetSamplerState( _dword index ) const
{
	return mEffect->GetSamplerState( index );
}

SamplerStateRHI* GraphicAsyncEffect::GetCubeTextureSamplerState( ) const
{
	return mEffect->GetCubeTextureSamplerState( );
}

RasterizerStateRHI* GraphicAsyncEffect::GetRasterizerState( ) const
{
	return mEffect->GetRasterizerState( );
}

DepthStateRHI* GraphicAsyncEffect::GetDepthState( ) const
{
	return mEffect->GetDepthState( );
}

StencilStateRHI* GraphicAsyncEffect::GetStencilState( ) const
{
	return mEffect->GetStencilState( );
}

BlendStateRHI* GraphicAsyncEffect::GetBlendState( ) const
{
	return mEffect->GetBlendState( );
}

_void GraphicAsyncEffect::SetRenderStates( const GraphicRenderStateInfo& state_info )
{
	mEffect->SetRenderStates( state_info );
}

const GraphicRenderStateInfo& GraphicAsyncEffect::GetRenderStates( ) const
{
	return mEffect->GetRenderStates( );
}

_void GraphicAsyncEffect::PushStates( )
{
	mEffect->PushStates( );
}

_void GraphicAsyncEffect::PopStates( )
{
	mEffect->PopStates( );
}

const GraphicRenderStateInfoStack& GraphicAsyncEffect::GetStates( ) const
{
	return mEffect->GetStates( );
}

_GRAPHIC_RENDER_QUEUE GraphicAsyncEffect::GetRenderSlot( ) const
{
	return mEffect->GetRenderSlot( );
}

_void GraphicAsyncEffect::SetManualDepth( _ubool manual_depth )
{
	return mEffect->SetManualDepth( manual_depth );
}

_ubool GraphicAsyncEffect::GetManualDepth( ) const
{
	return mEffect->GetManualDepth( );
}

WStringPtr GraphicAsyncEffect::GetName( ) const
{
	return mEffect->GetName( );
}

const GraphicEffectBase& GraphicAsyncEffect::GetBaseInfo( ) const
{
	return mEffect->GetBaseInfo( );
}

const FlagsObject& GraphicAsyncEffect::GetEnabledFunctions( ) const
{
	return mEffect->GetEnabledFunctions( );
}

const FlagsObject& GraphicAsyncEffect::GetEnabledSlotFunctions( _GRAPHIC_LIGHT_SLOT slot ) const
{
	return mEffect->GetEnabledSlotFunctions( slot );
}

_ubool GraphicAsyncEffect::IsShared( ) const
{
	return mEffect->IsShared( );
}

IGraphicEffect* GraphicAsyncEffect::GetInternalEffect( ) const
{
	return (IGraphicEffect*)this;
}

BoundShaderRHI* GraphicAsyncEffect::GetBoundShader( ) const
{
	return mEffect->GetBoundShader( );
}

AStringPtr GraphicAsyncEffect::GetPSCode( ) const
{
	return mEffect->GetPSCode( );
}

AStringPtr GraphicAsyncEffect::GetVSCode( ) const
{
	return mEffect->GetVSCode( );
}

_crcvalue GraphicAsyncEffect::GetUBOCRCValue( )
{
	Compile( );

	return mEffect->GetUBOCRCValue( );
}

_void GraphicAsyncEffect::ResetUBOs( )
{
	mEffect->ResetUBOs( );
}

const _byte* GraphicAsyncEffect::GetUBOs( _dword& number, _dword& total_size ) const
{
	return mEffect->GetUBOs( number, total_size );
}

_ubool GraphicAsyncEffect::HasUBO( _GRAPHIC_UBT type ) const
{
	return mEffect->HasUBO( type );
}

_void GraphicAsyncEffect::SetUBO( _GRAPHIC_UBT type, _ubool value )
{
	Compile( );

	mEffect->SetUBO( type, value );
}

_void GraphicAsyncEffect::SetUBO( _GRAPHIC_UBT type, _int value )
{
	Compile( );

	mEffect->SetUBO( type, value );
}

_void GraphicAsyncEffect::SetUBO( _GRAPHIC_UBT type, _float value )
{
	Compile( );

	mEffect->SetUBO( type, value );
}

_void GraphicAsyncEffect::SetUBO( _GRAPHIC_UBT type, const Vector2& value )
{
	Compile( );

	mEffect->SetUBO( type, value );
}

_void GraphicAsyncEffect::SetUBO( _GRAPHIC_UBT type, const Vector3& value )
{
	Compile( );

	mEffect->SetUBO( type, value );
}

_void GraphicAsyncEffect::SetUBO( _GRAPHIC_UBT type, const Vector4& value )
{
	Compile( );

	mEffect->SetUBO( type, value );
}

_void GraphicAsyncEffect::SetUBO( _GRAPHIC_UBT type, const Matrix3& transform, _ubool transpose )
{
	Compile( );

	mEffect->SetUBO( type, transform, transpose );
}

_void GraphicAsyncEffect::SetUBO( _GRAPHIC_UBT type, const Matrix4& transform, _ubool transpose )
{
	Compile( );

	mEffect->SetUBO( type, transform, transpose );
}

_void GraphicAsyncEffect::SetUBO( _GRAPHIC_UBT type, _UNIFORM_BUFFER_DATA_TYPE data_type, _dword size, const _byte* buffer )
{
	Compile( );

	mEffect->SetUBO( type, data_type, size, buffer );
}

_void GraphicAsyncEffect::SetLDRColorUBO( _GRAPHIC_UBT type, const Color& color )
{
	Compile( );

	mEffect->SetLDRColorUBO( type, color );
}

_void GraphicAsyncEffect::SetHDRColorUBO( _GRAPHIC_UBT type, const Vector4& color )
{
	Compile( );

	mEffect->SetHDRColorUBO( type, color );
}

_dword GraphicAsyncEffect::GetTexSlotIndex( _TEXRES_ID id )
{
	Compile( );

	return mEffect->GetTexSlotIndex( id );
}

_void GraphicAsyncEffect::SynTextureInfo( Texture2DRHI** textures )
{
	Compile( );

	mEffect->SynTextureInfo( textures );
}

_void GraphicAsyncEffect::CombineRenderStates( IGraphicEffect* effect )
{
	mEffect->CombineRenderStates( effect );
}

_ubool GraphicAsyncEffect::Compile( )
{
	return mEffect->Compile( );
}

GraphicShaderSerializeInfo GraphicAsyncEffect::GetExportInfo( ) const
{
	return mEffect->GetExportInfo( );
}