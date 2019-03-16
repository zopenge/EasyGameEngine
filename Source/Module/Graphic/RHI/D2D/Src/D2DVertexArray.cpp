//! @file     D2DVertexArray.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D2D-VertexArray Implementation
//----------------------------------------------------------------------------

VertexArrayRHIPassRef D2DDrv::CreateVertexArray( )
{
	return _null;
}

_void D2DDrv::BindVertexArray( VertexArrayRHI* vertex_array )
{
}

_void D2DDrv::UnbindVertexArray( )
{
}

_ubool D2DDrv::SetVertexArrayDecl( VertexArrayRHI* vertex_array, VertexDeclarationRHI* declaration, VertexBufferRHI* vbo, IndexBufferRHI* ibo )
{
	return _false;
}

_dword D2DDrv::GetVertexArrayResID( VertexArrayRHI* vertex_array )
{
	return 0;
}
