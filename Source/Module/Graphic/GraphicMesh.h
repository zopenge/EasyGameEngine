//! @file     GraphicMesh.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicMesh
//----------------------------------------------------------------------------

class GraphicMesh : public TObject< IGraphicMesh >
{
private:
	//!	The VAO resource
	IGraphicVertexArrayRef	mVAO;

	//!	The vertex type, @see _GEOMETRY_VERTEX_TYPE.
	_dword					mVertexType;

	//!	The mesh geometry info
	GraphicMeshGeometryInfo	mMeshGeometryInfo;

	//!	The data field in VB
	DwordDataField			mVBDataField;
	//!	The VB allocator
	IOffsetAllocatorRef		mVBAllocator;

	//!	The data field in IB
	DwordDataField			mIBDataField;
	//!	The IB allocators
	IOffsetAllocatorRef		mIBAllocator;

public:
	GraphicMesh( IGraphicVertexArray* vao, _dword vertex_type, const DwordDataField& vb_field, IOffsetAllocator* vb_allocator, const DwordDataField& ib_field, IOffsetAllocator* ib_allocator );
	virtual ~GraphicMesh( );

// IGraphicMesh Interface
public:
	virtual IGraphicVertexArray*			GetVAO( ) override;

	virtual const GraphicMeshGeometryInfo&	GetMeshGeometryInfo( ) const override;

	virtual const DwordDataField&			GetVBDataField( ) const override;
	virtual const DwordDataField&			GetIBDataField( ) const override;

	virtual _dword							GetVertexType( ) const override;

	virtual _dword							GetVBStride( ) const override;
	virtual _dword							GetVBSize( ) const override;
	virtual _dword							GetVBOffset( _dword start_index ) const override;
	virtual _byte*							LockVBData( ) override;
	virtual _void							UnlockVBData( ) override;
	virtual const _byte*					GetVBData( ) override;

	virtual _dword							GetIBSize( ) const override;
	virtual _dword							GetIBOffset( _dword start_index ) const override;
	virtual _dword							GetIBStartIndex( ) const override;
	virtual _dword							GetIBNumber( ) const override;
	virtual _word*							LockIBData( ) override;
	virtual _void							UnlockIBData( ) override;
	virtual const _word*					GetIBData( ) override;

	virtual _ubool							UpdateUVBuffer( _dword usage_index, _dword number, const Vector2* buffer ) override;

	virtual _ubool							RayVS( const Ray& ray, _float* distance = _null ) override;
};

//----------------------------------------------------------------------------
// GraphicMesh Implementation
//----------------------------------------------------------------------------

}