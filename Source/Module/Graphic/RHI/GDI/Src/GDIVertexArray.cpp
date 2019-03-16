//! @file     GDIVertexArray.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GDI-VertexArray Implementation
//----------------------------------------------------------------------------

VertexArrayRHIPassRef GDIDrv::CreateVertexArray( )
{
	return _null;
}

_void GDIDrv::BindVertexArray( VertexArrayRHI* vertex_array )
{
}

_void GDIDrv::UnbindVertexArray( )
{
}

_ubool GDIDrv::SetVertexArrayDecl( VertexArrayRHI* vertex_array, VertexDeclarationRHI* declaration, VertexBufferRHI* vbo, IndexBufferRHI* ibo )
{
	return _false;
}

_dword GDIDrv::GetVertexArrayResID( VertexArrayRHI* vertex_array )
{
	return 0;
}
