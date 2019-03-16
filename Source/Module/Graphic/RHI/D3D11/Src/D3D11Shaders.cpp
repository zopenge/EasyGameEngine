//! @file     D3D11Shaders.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D3D11Drv-Shaders Implementation
//----------------------------------------------------------------------------

const ShaderCompileConfigInfo& D3D11Drv::GetShaderCompileConfigInfo( )
{
	static ShaderCompileConfigInfo sShaderCompileConfigInfo;
	return sShaderCompileConfigInfo;
};

PixelShaderRHIPassRef D3D11Drv::CreatePixelShader( AStringPtr code )
{
	return _null;
}

VertexShaderRHIPassRef D3D11Drv::CreateVertexShader( AStringPtr code )
{
	return _null;
}

BoundShaderRHIPassRef D3D11Drv::CreateBoundShader( VertexShaderRHI* vertexshader, PixelShaderRHI* pixelshader )
{
	return _null;
}

PixelShaderRHI* D3D11Drv::GetPixelShader( BoundShaderRHI* shader ) 
{
	return _null;
}

VertexShaderRHI* D3D11Drv::GetVertexShader( BoundShaderRHI* shader ) 
{
	return _null;
}

_ubool D3D11Drv::GetPixelShaderCode( PixelShaderRHI* ps, AString& code )
{
	return _false;
}

_ubool D3D11Drv::GetVertexShaderCode( VertexShaderRHI* vs, AString& code )
{
	return _false;
}

_dword D3D11Drv::GetShaderResourceID( const BoundShaderRHI* shader ) const
{
	return 0;
}

_dword D3D11Drv::ActiveUniformBuffer( BoundShaderRHI* shader, _UNIFORM_BUFFER_DATA_TYPE type, AStringPtr name, _dword size )
{
	return -1;
}

_ubool D3D11Drv::UpdateUniformBuffer( BoundShaderRHI* shader, _dword location, const _void* buffer, _dword size )
{
	return _false;
}

_ubool D3D11Drv::SetUniformPropertyValue( BoundShaderRHI* shader, AStringPtr name, _long value )
{
	return _false;
}

//----------------------------------------------------------------------------
// D3D11BoundShader Implementation
//----------------------------------------------------------------------------

D3D11BoundShader::D3D11BoundShader( )
{

}

D3D11BoundShader::~D3D11BoundShader( )
{

}