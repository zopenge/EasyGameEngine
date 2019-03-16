//! @file     GraphicVertexArray.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicVertexArray
//----------------------------------------------------------------------------

class GraphicVertexArray : public INTERFACE_OBJECT_IMPL( IGraphicVertexArray )
{
private:
	//!	The vertex array resource
	VertexArrayRHIRef		mVAOResource;
	//!	The vertex declaration resource
	VertexDeclarationRHIRef	mVertexDeclRHI;

	//!	The stride of index buffer
	_dword					mIBStride;
	//!	The current offset of index buffer
	_dword					mIBOffset;
	//!	The index buffer
	IGraphicIndexBufferRef	mIndexBuffer;

	//!	The stride of vertex buffer
	_dword					mVBStride;
	//!	The current offset of vertex buffer
	_dword					mVBOffset;
	//!	The vertex buffer
	IGraphicVertexBufferRef	mVertexBuffer;

public:
	GraphicVertexArray( );
	virtual ~GraphicVertexArray( );

public:
	//!	Initialize.
	_ubool Initialize( _RESOURCE_DRAW_TYPE draw_type, VertexDeclarationRHI* vertex_decl );

// IGraphicVertexArray Interface
public:
	virtual VertexArrayRHI*	GetResource( ) const override;

	virtual _void			Bind( ) override;

	virtual _dword			GetElementOffset( _VERTEX_ELEMENT_USAGE usage, _dword usage_index ) const override;

	virtual _byte*			LockVBData( _dword offset, _dword size ) override;
	virtual _void			UnlockVBData( ) override;
	virtual const _byte*	GetVBData( ) override;
	virtual _dword			GetVBStride( ) const override;
	virtual _dword			GetVBSize( ) const override;
	virtual _dword			GetVBOffset( ) const override;
	virtual _dword			GetVBIndex( ) const override;
	virtual _void			WriteVB( _dword offset, _dword size, const _byte* buffer ) override;
	virtual _void			WriteVB( _dword size, const _byte* buffer ) override;

	virtual _byte*			LockIBData( _dword offset, _dword size ) override;
	virtual _void			UnlockIBData( ) override;
	virtual const _byte*	GetIBData( ) override;
	virtual _dword			GetIBStride( ) const override;
	virtual _dword			GetIBSize( ) const override;
	virtual _dword			GetIBOffset( ) const override;
	virtual _void			WriteIB( _dword offset, _dword size, const _byte* buffer ) override;
	virtual _void			WriteIB( _dword size, const _byte* buffer ) override;

	virtual _void			WriteBuffers( _dword vb_size, const _byte* vb_data, _dword ib_number, const _word* ib_data ) override;
	virtual _void			FlushBuffers( ) override;
};

//----------------------------------------------------------------------------
// GraphicVertexArray Implementation
//----------------------------------------------------------------------------

}