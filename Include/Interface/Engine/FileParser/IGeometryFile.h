//! @file     IGeometryFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGeometryMeshChunk
//----------------------------------------------------------------------------

class IGeometryMeshChunk : public ISerializable
{
public:
	//!	Get the chunk name.
	//!	@param		none.
	//!	@return		The chunk name.
	virtual WStringPtr GetChunkName( ) const PURE;

	//!	Read from stream.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadFromStream( IStreamReader* stream_reader ) PURE;
	//!	Write to stream.
	//!	@param		stream_writer	The stream writer.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool WriteToStream( IStreamWriter* stream_writer, _dword output_vertex_declare ) const PURE;

	//!	Get the mesh info.
	//!	@param		none.
	//!	@return		The mesh info.
	virtual const GeometryMeshChunkInfo& GetInfo( ) const PURE;

	//!	Get the vertex buffer element offset in bytes.
	//!	@param		type		The vertex element type.
	//!	@return		The vertex buffer element offset in bytes.
	virtual _dword GetVertexBufferElementOffset( _GEOMETRY_VERTEX_TYPE type ) const PURE;
	//!	Get the vertex buffer size in bytes.
	//!	@param		none.
	//!	@return		The vertex buffer size in bytes.
	virtual _dword GetVertexBufferSize( ) const PURE;
	//!	Get the vertex buffer data.
	//!	@param		none.
	//!	@return		The vertex buffer data.
	virtual const _byte* GetVertexBufferData( ) const PURE;

	//!	Get the index buffer size in bytes.
	//!	@param		none.
	//!	@return		The index buffer size in bytes.
	virtual _dword GetIndexBufferSize( ) const PURE;
	//!	Get the index buffer data (16-bits).
	//!	@param		none.
	//!	@return		The index buffer data.
	virtual const _word* GetIndexBufferData( ) const PURE;
};

//----------------------------------------------------------------------------
// IGeometryFile
//----------------------------------------------------------------------------

class IGeometryFile : public IBaseFile
{
public:
	//!	Get mesh chunk.
	//!	@param		none.
	//!	@return		The chunk resource interface.
	virtual IGeometryMeshChunkRef GetMeshChunk( ) PURE;

	//!	Dump to XML string.
	//!	@param		none.
	//!	@return		The XML string.
	virtual WStringR DumpToXMLString( ) const PURE;
};

}