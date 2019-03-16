//! @file     D3D11State.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// D3D11SamplerState
//----------------------------------------------------------------------------

class D3D11SamplerState : public SamplerStateRHI
{
public:
	D3D11_SAMPLER_DESC	mSamplerDesc;
};

//----------------------------------------------------------------------------
// D3D11RasterizerState
//----------------------------------------------------------------------------

class D3D11RasterizerState : public RasterizerStateRHI
{
public:
	D3D11_RASTERIZER_DESC	mRasterizerDesc;
};

//----------------------------------------------------------------------------
// D3D11DepthState
//----------------------------------------------------------------------------

class D3D11DepthState : public DepthStateRHI
{
public:
	D3D11_DEPTH_STENCIL_DESC	mDepthStencilDesc;
};

//----------------------------------------------------------------------------
// D3D11StencilState
//----------------------------------------------------------------------------

class D3D11StencilState : public StencilStateRHI
{
public:
	D3D11_DEPTH_STENCIL_DESC	mDepthStencilDesc;
	_dword						mStencilRef;
};

//----------------------------------------------------------------------------
// D3D11BlendState
//----------------------------------------------------------------------------

class D3D11BlendState : public BlendStateRHI
{
public:
	D3D11_BLEND_DESC	mBlendDesc;
	Color				mBlendFactor;

public:
	D3D11BlendState( ) 
		: mBlendFactor( Color::cNull ) {}
	virtual ~D3D11BlendState( ) {}
};

}