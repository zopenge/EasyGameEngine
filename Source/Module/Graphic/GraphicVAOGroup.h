//! @file     GraphicVAOGroup.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicVAOGroup
//----------------------------------------------------------------------------

class GraphicVAOGroup
{
private:
	//!	The vertex array object info
	struct VAOInfo
	{
		IOffsetAllocatorRef				mVBAllocator;
		IOffsetAllocatorRef				mIBAllocator;
		IGraphicVertexDeclarationRef	mVertexDecl;
		IGraphicVertexArrayRef			mVertexArrayObject;
	};
	typedef Array< VAOInfo* > VAOInfoArray;

private:
	//!	The vertex array objects
	VAOInfoArray	mVAOs;

private:
	//!	Check mesh.
	_ubool CheckMesh( const IGraphicMesh* mesh, _dword max_vertices_number, _dword stride ) const;

	//!	Write VB.
	_dword WriteVB( VAOInfo* vao_info, _dword vb_stride, _dword vb_size, const _byte* vb_buffer );
	//!	Write IB.
	_dword WriteIB( VAOInfo* vao_info, _dword offset, _dword ib_size, const _word* ib_buffer );

	//!	Create VAO.
	VAOInfo* CreateVAOInfo( _dword vertex_type, _dword vb_size, _dword ib_size );
	VAOInfo* CreateVAOInfo( _dword vertex_type );

public:
	GraphicVAOGroup( );
	~GraphicVAOGroup( );

public:
	//!	Get the VAO
	IGraphicVertexArray* GetVAO( _dword vertex_type, _dword vb_size, _dword ib_size );
	IGraphicVertexArray* GetVAO( _dword vertex_type );

	//!	Flush buffers.
	_void FlushBuffers( );
	//!	Free buffers.
	_void FreeBuffers( );

	//!	Add mesh.
	IGraphicMeshPassRef	AddMesh( _dword vertex_type, _dword vb_stride, _dword vb_size, const _byte* vb_buffer, _dword ib_size, const _word* ib_buffer );
};

//----------------------------------------------------------------------------
// GraphicVAOGroup Implementation
//----------------------------------------------------------------------------

}