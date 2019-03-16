//! @file     GraphicVertexDeclaration.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicVertexDeclaration
//----------------------------------------------------------------------------

class GraphicVertexDeclaration : public TObject< IGraphicVertexDeclaration >
{
private:
	//!	The vertex type, @see _GEOMETRY_VERTEX_TYPE.
	_dword					mVertexType;
	//!	The vertex declaration resource
	VertexDeclarationRHIRef	mVertexDeclRHI;

private:
	//!	Get vertex element type.
	static _VERTEX_ELEMENT_TYPE GetElementType( WStringPtr type );
	//!	Get vertex element type size in bytes.
	static _dword GetElementTypeSize( _VERTEX_ELEMENT_TYPE type );
	//!	Get vertex element usage.
	static _VERTEX_ELEMENT_USAGE GetElementUsage( WStringPtr usage );

public:
	GraphicVertexDeclaration(  );
	virtual ~GraphicVertexDeclaration( );

public:
	//!	Initialize.
	_ubool Initialize( _dword vertex_type );
	_ubool Initialize( VertexDeclarationRHI* vertex_decl );

// IGraphicVertexDeclaration Interface
public:
	virtual _dword					GetVertexType( ) const override;
	virtual _dword					GetStride( ) const override;

	virtual _dword					GetElementOffset( _VERTEX_ELEMENT_USAGE usage, _dword usage_index ) const override;

	virtual VertexDeclarationRHI*	GetResource( ) override;
};

}