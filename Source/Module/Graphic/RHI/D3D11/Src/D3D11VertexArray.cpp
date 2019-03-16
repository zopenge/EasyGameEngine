//! @file     D3D11VertexArray.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D3D11-VertexArray Implementation
//----------------------------------------------------------------------------

VertexArrayRHIPassRef D3D11Drv::CreateVertexArray( )
{
	return _null;
}

_void D3D11Drv::BindVertexArray( VertexArrayRHI* vertex_array )
{
}

_void D3D11Drv::UnbindVertexArray( )
{
}

_ubool D3D11Drv::SetVertexArrayDecl( VertexArrayRHI* vertex_array, VertexDeclarationRHI* declaration, VertexBufferRHI* vbo, IndexBufferRHI* ibo )
{
	return _false;
}

_dword D3D11Drv::GetVertexArrayResID( VertexArrayRHI* vertex_array )
{
	return 0;
}
