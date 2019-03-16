//! @file     D3D11State.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D3D11Drv-State Implementation
//----------------------------------------------------------------------------

SamplerStateRHIPassRef D3D11Drv::CreateSamplerState( const SamplerStateInitializerRHI& initializer )
{
	return _null;
}

RasterizerStateRHIPassRef D3D11Drv::CreateRasterizerState( const RasterizerStateInitializerRHI& initializer )
{
	return _null;
}

DepthStateRHIPassRef D3D11Drv::CreateDepthState( const DepthStateInitializerRHI& initializer )
{
	return _null;
}

StencilStateRHIPassRef D3D11Drv::CreateStencilState( const StencilStateInitializerRHI& initializer )
{
	return _null;
}

BlendStateRHIPassRef D3D11Drv::CreateBlendState( const BlendStateInitializerRHI& initializer )
{
	return _null;
}

SamplerStateInitializerRHI D3D11Drv::GetSamplerState( const SamplerStateRHI* state ) const
{
	return SamplerStateInitializerRHI( _SF_NEAREST );
}

RasterizerStateInitializerRHI D3D11Drv::GetRasterizerState( const RasterizerStateRHI* state ) const
{
	return RasterizerStateInitializerRHI( _false, _false, _false, _false, _RFM_POINT, _RCM_NONE );
}

DepthStateInitializerRHI D3D11Drv::GetDepthState( const DepthStateRHI* state ) const
{
	return DepthStateInitializerRHI( _false, _CF_LESS );
}

StencilStateInitializerRHI D3D11Drv::GetStencilState( const StencilStateRHI* state ) const
{
	return StencilStateInitializerRHI( );
}

BlendStateInitializerRHI D3D11Drv::GetBlendState( const BlendStateRHI* state ) const
{
	return BlendStateInitializerRHI( );
}