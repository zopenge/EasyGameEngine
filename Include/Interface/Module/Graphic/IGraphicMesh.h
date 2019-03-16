//! @file     IGraphicMesh.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicMesh
//----------------------------------------------------------------------------

class IGraphicMesh : public IObject
{
public:
	//!	Get the vertex array object.
	//!	@param		none.
	//!	@return		The vertex array object interface.
	virtual IGraphicVertexArray* GetVAO( ) PURE;

	//!	Get the mesh geometry info.
	//!	@param		none.
	//!	@return		The mesh geometry info.
	virtual const GraphicMeshGeometryInfo& GetMeshGeometryInfo( ) const PURE;

	//!	Get data field in VB.
	//!	@param		none.
	//!	@return		The data field in VB.
	virtual const DwordDataField& GetVBDataField( ) const PURE;
	//!	Get data field in IB.
	//!	@param		none.
	//!	@return		The data field in IB.
	virtual const DwordDataField& GetIBDataField( ) const PURE;

	//!	Get vertex type.
	//!	@param		none.
	//!	@return		The vertex type, @see _GEOMETRY_VERTEX_TYPE.
	virtual _dword GetVertexType( ) const PURE;

	//!	Get vertex buffer stride in bytes.
	//!	@param		none.
	//!	@return		The stride in bytes.
	virtual _dword GetVBStride( ) const PURE;
	//!	Get vertex buffer size in bytes.
	//!	@param		none.
	//!	@return		The size in bytes.
	virtual _dword GetVBSize( ) const PURE;
	//!	Get vertex buffer offset in bytes.
	//!	@param		start_index		The start index of vertex buffer.
	//!	@return		The offset in bytes.
	virtual _dword GetVBOffset( _dword start_index ) const PURE;
	//!	Get the vertex buffer data.
	//!	@param		none.
	//!	@return		The vertex buffer data.
	virtual _byte* LockVBData( ) PURE;
	//!	Get the vertex buffer data.
	//!	@param		none.
	//!	@return		none.
	virtual _void UnlockVBData( ) PURE;
	//!	Get the vertex buffer data.
	//!	@param		none.
	//!	@return		The vertex buffer data.
	virtual const _byte* GetVBData( ) PURE;

	//!	Get index buffer size in bytes.
	//!	@param		none.
	//!	@return		The size in bytes.
	virtual _dword GetIBSize( ) const PURE;
	//!	Get index buffer offset in bytes.
	//!	@param		start_index		The start index of vertex buffer.
	//!	@return		The offset in bytes.
	virtual _dword GetIBOffset( _dword start_index ) const PURE;
	//!	Get index buffer start index.
	//!	@param		none.
	//!	@return		The start index of index buffer.
	virtual _dword GetIBStartIndex( ) const PURE;
	//!	Get index buffer number (not size, the elements number of index buffer).
	//!	@param		none.
	//!	@return		The number of elements in index buffer.
	virtual _dword GetIBNumber( ) const PURE;
	//!	Get the index buffer data.
	//!	@param		none.
	//!	@return		The index buffer data.
	virtual _word* LockIBData( ) PURE;
	//!	Get the index buffer data.
	//!	@param		none.
	//!	@return		none.
	virtual _void UnlockIBData( ) PURE;
	//!	Get the index buffer data.
	//!	@param		none.
	//!	@return		The index buffer data.
	virtual const _word* GetIBData( ) PURE;

	//!	Update vertex's UV buffer.
	//!	@param		usage_index	The usage index.
	//!	@param		number		The uv buffer number in float-2, not in bytes.
	//!	@param		buffer		The uv buffer data in float-2.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool UpdateUVBuffer( _dword usage_index, _dword number, const Vector2* buffer ) PURE;

	//!	Intersect by ray.
	//!	@param		ray			The ray.
	//!	@param		distance	The distance from ray to nearest triangle.
	//!	@return		True indicates ray hit mesh successful.
	virtual _ubool RayVS( const Ray& ray, _float* distance = _null ) PURE;
};

}