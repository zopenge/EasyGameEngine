//! @file     IGraphicVertexDeclaration.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicVertexDeclaration
//----------------------------------------------------------------------------

class IGraphicVertexDeclaration : public IObject
{
public:
	//!	Get the vertex type.
	//!	@param		none.
	//!	@param		The vertex type, @see _GEOMETRY_VERTEX_TYPE.
	virtual _dword GetVertexType( ) const PURE;
	//!	Get the stride of vertex in bytes.
	//!	@param		none.
	//!	@param		The stride of vertex in bytes.
	virtual _dword GetStride( ) const PURE;

	//!	Get element's offset in bytes.
	//!	@param		usage		The vertex element usage.
	//!	@param		usage_index	The usage index.
	//!	@return		The offset in bytes.
	virtual _dword GetElementOffset( _VERTEX_ELEMENT_USAGE usage, _dword usage_index ) const PURE;

	//!	Get the vertex declaration resource.
	//!	@param		none.
	//!	@return		The vertex declaration.
	virtual VertexDeclarationRHI* GetResource( ) PURE;
};

}