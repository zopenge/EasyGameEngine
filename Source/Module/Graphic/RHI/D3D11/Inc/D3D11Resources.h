//! @file     D3D11Resources.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// D3D11VertexDeclaration
//----------------------------------------------------------------------------

class D3D11VertexDeclaration : public VertexDeclarationRHI
{
private:

public:
	D3D11VertexDeclaration( const VertexElementRHIArray& elements );
	virtual ~D3D11VertexDeclaration( );
};

//----------------------------------------------------------------------------
// D3D11VertexShader
//----------------------------------------------------------------------------

class D3D11VertexShader : public VertexShaderRHI
{
public:
	//! The vertex shader resource
	RefPtr< ID3D11VertexShader > mResource;

public:
	D3D11VertexShader( ID3D11VertexShader* resource ) 
		: mResource( resource ) {}

	virtual ~D3D11VertexShader( );
};

//----------------------------------------------------------------------------
// D3D11PixelShader
//----------------------------------------------------------------------------

class D3D11PixelShader : public PixelShaderRHI
{
public:
	//! The pixel shader resource
	RefPtr< ID3D11PixelShader > mResource;

public:
	D3D11PixelShader( ID3D11PixelShader* resource ) 
		: mResource( resource ) {}

	virtual ~D3D11PixelShader( );
};

//----------------------------------------------------------------------------
// D3D11BoundShader
//----------------------------------------------------------------------------

class D3D11BoundShader : public BoundShaderRHI
{
private:

public:
	D3D11BoundShader( );
	~D3D11BoundShader( );

public:
	//!	Initialize.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	_ubool Initialize( );

	//!	Bind.
	//!	@param		none.
	//!	@return		none.
	_void Bind( );
};

//----------------------------------------------------------------------------
// TD3D11Buffer
//----------------------------------------------------------------------------

template< _RENDER_RESOURCE_TYPE ResourceType >
class TD3D11Buffer : public TDynamicRHIResource< ResourceType >
{
public:
	//! The vertex buffer resource
	RefPtr< ID3D11Buffer > mResource;

public:
	TD3D11Buffer( ) 
		{}

	virtual ~TD3D11Buffer( ) {}
};

typedef TD3D11Buffer< _RRT_INDEX_BUFFER >	D3D11IndexBuffer;
typedef TD3D11Buffer< _RRT_VERTEX_BUFFER >	D3D11VertexBuffer;

//----------------------------------------------------------------------------
// TD3D11Texture
//----------------------------------------------------------------------------

template< _RENDER_RESOURCE_TYPE ResourceType >
class TD3D11Texture : public TDynamicRHIResource< ResourceType >
{
protected:
	//! The D3D texture resource
	RefPtr< ID3D11Texture2D > mResource;

public:
	TD3D11Texture( ID3D11Texture2D* texture ) : mResource( texture )
		{}

	virtual ~TD3D11Texture( ) {}

public:
	//!	Get the D3D texture resource
	EGE_GET_ACCESSOR( ID3D11Texture2D*, Resource )
};

typedef TD3D11Texture< _RRT_TEXTURE >		D3D11Texture;
typedef TD3D11Texture< _RRT_TEXTURE_2D >	D3D11Texture2D;

}