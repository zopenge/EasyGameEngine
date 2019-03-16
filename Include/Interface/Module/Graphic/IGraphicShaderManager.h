//! @file     IGraphicShaderManager.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicShaderManager
//----------------------------------------------------------------------------

class IGraphicShaderManager : public IObject
{
public:
	//!	Create vertex shader.
	//!	@param		code		The vertex shader code.
	//!	@return		The vertex shader.
	virtual VertexShaderRHIRef CreateVertexShader( AStringPtr code ) PURE;
	//!	Create pixel shader.
	//!	@param		code		The pixel shader code.
	//!	@return		The pixel shader.
	virtual PixelShaderRHIRef CreatePixelShader( AStringPtr code ) PURE;

	//!	Create effect.
	//!	@remark		We will load it from working archive.
	//!	@param		name		The effect name.
	//!	@return		The effect interface.
	virtual IGraphicEffectPassRef CreateEffect( WStringPtr name ) PURE;
};

}