//! @file     GeometryFile.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GeometryMeshChunk
//----------------------------------------------------------------------------

class GeometryMeshChunk : public TSerializable< TObject< IGeometryMeshChunk > >
{
private:
	enum
	{
		//!	The max skin info number pre-vertex
		_MAX_SKIN_NUMBER_PRE_VERTEX = 4,
	};

private:
	struct VertexAccessor
	{
		Vector3MemSegmentPtr	mPosition;
		Vector3MemSegmentPtr	mNormal;
		Vector4MemSegmentPtr	mTangent;
		DwordMemSegmentPtr		mColor;
		Vector2MemSegmentPtr	mUV1;
		Vector2MemSegmentPtr	mUV2;
		DwordMemSegmentPtr		mBoneID;
		Vector4MemSegmentPtr	mBoneWeight;
	};

private:
	//!	The geometry chunk name
	WString					mChunkName;

	//!	The mesh info
	GeometryMeshChunkInfo	mInfo;

	//!	The vertex buffer data
	_byte*					mVertexBufferData;
	//!	The index buffer data
	_word*					mIndexBufferData;

private:
	//!	Get the vertex type by vertex declaration.
	_ubool GetVertexTypeByDecl( ISerializableNode* node, _dword& type, _dword& stride ) const;
	_ubool GetVertexTypeByDecl( IStreamReader* stream_reader, _dword& type, _dword& stride ) const;

	//!	Update AABox.
	_void UpdateAABox( const Vector3& pos );
	_void UpdateUVBoundingBox( const Vector2& pos, Vector2& bounding_min, Vector2& bounding_max );

	//!	Read position.
	_ubool ReadPos( ISerializableNode* node, Vector3& pos );
	//!	Read color.
	_ubool ReadColor( ISerializableNode* node, Color& color );
	//!	Read normal.
	_ubool ReadNormal( ISerializableNode* node, Vector3& normal );
	//!	Read uv1.
	_ubool ReadUV1( ISerializableNode* node, Vector2& uv );
	//!	Read uv1.
	_ubool ReadUV2( ISerializableNode* node, Vector2& uv );
	//!	Read skin info.
	_ubool ReadSkinInfo( ISerializableNode* node, _dword& bone_id, Vector4& weight );
	//!	Read tangent.
	_ubool ReadTangent( ISerializableNode* node, Vector4& tangent );

	//!	Load vertices info.
	_ubool LoadVerticesInfo( ISerializableNode* node );
	//!	Load indexes info.
	_ubool LoadIndexesInfo( ISerializableNode* node );

	//!	Read aabb.
	_ubool ReadAABBox( IStreamReader* stream_reader, AxisAlignedBox& bounding );
	//!	Read uv bounding box.
	_ubool ReadUVBoundingBox( IStreamReader* stream_reader, Vector2& bounding_min, Vector2& bounding_max );
	//!	Read position.
	_ubool ReadPos( IStreamReader* stream_reader, Vector3& pos, _float& tangent_w );
	//!	Read uv.
	_ubool ReadUV( IStreamReader* stream_reader, Vector2& uv, const Vector2& bounding_min, const Vector2& bounding_max );
	//!	Read skin info.
	_ubool ReadSkinInfo( IStreamReader* stream_reader, _dword& bone_id, Vector4& weight );
	//! Write Tangent Space Rotation
	_ubool ReadTangentSpaceRotation( IStreamReader* stream_writer, Vector3* normal, Vector4* tangent );

	//!	Load vertices info.
	_ubool LoadVerticesInfo( IStreamReader* stream_reader );
	//!	Load indexes info.
	_ubool LoadIndexesInfo( IStreamReader* stream_reader );

	//!	Write position.
	_ubool WritePos( ISerializableNode* node, const Vector3& pos ) const;
	//!	Write normal.
	_ubool WriteNormal( ISerializableNode* node, const Vector3& normal ) const;
	//!	Write uv1.
	_ubool WriteUV1( ISerializableNode* node, const Vector2& uv ) const;
	//!	Write uv1.
	_ubool WriteUV2( ISerializableNode* node, const Vector2& uv ) const;
	//!	Write skin info.
	_ubool WriteSkinInfo( ISerializableNode* node, _dword bone_id, const Vector4& weight ) const;
	//!	Write tangent.
	_ubool WriteTangent( ISerializableNode* node, const Vector4& tangent ) const;

	//!	Write vertices info.
	_ubool WriteVerticesInfo( ISerializableNode* node ) const;
	//!	Write indexes info.
	_ubool WriteIndexesInfo( ISerializableNode* node ) const;

	//!	Write aabb.
	_ubool WriteAABBox( IStreamWriter* stream_writer, const AxisAlignedBox& bounding ) const;
	//!	Write uv bounding box.
	_ubool WriteUVBoundingBox( IStreamWriter* stream_writer, const Vector2& bounding_min, const Vector2& bounding_max ) const;
	//!	Write position.
	_ubool WritePos( IStreamWriter* stream_writer, const Vector3& pos, const AxisAlignedBox& bounding, _float tangent_w ) const;
	//!	Write uv.
	_ubool WriteUV( IStreamWriter* stream_writer, const Vector2& uv, const Vector2& bounding_min, const Vector2& bounding_max ) const;
	//!	Write skin info.
	_ubool WriteSkinInfo( IStreamWriter* stream_writer, _dword bone_id, const Vector4& weight ) const;
	//! Write Tangent Space Rotation
	_ubool WriteTangentSpaceRotation( IStreamWriter* stream_writer, const Vector3& normal, const Vector4& tangent ) const;

	_ubool BuildVertexAccessor( _dword fixed_output_vertex_decl, VertexAccessor& vertex_accessor ) const;
	_ubool GenerateTangentAccessor( VertexAccessor& vertex_accessor ) const;

	//!	Write vertices info.
	_ubool WriteVerticesInfo( IStreamWriter* stream_writer, _dword output_vertex_declare, _dword total_vertex_count, const VertexAccessor& vertex_buffer ) const;
	//!	Write indexes info.
	_ubool WriteIndexesInfo( IStreamWriter* stream_writer ) const;

public:
	GeometryMeshChunk( );
	GeometryMeshChunk( _dword vertex_type, const _byte* vb_data, _dword vb_size, const _word* ib_data, _dword ib_size );
	virtual ~GeometryMeshChunk( );

// ISerializable Interface
public:
	virtual _ubool							Import( ISerializableNode* node ) override;
	virtual _ubool							Export( ISerializableNode* node ) const override;

// IGeometryMeshChunk Interface
public:
	virtual WStringPtr						GetChunkName( ) const override;

	virtual _ubool							ReadFromStream( IStreamReader* stream_reader ) override;
	virtual _ubool							WriteToStream( IStreamWriter* stream_writer, _dword output_vertex_declare ) const override;

	virtual const GeometryMeshChunkInfo&	GetInfo( ) const override;

	virtual _dword							GetVertexBufferElementOffset( _GEOMETRY_VERTEX_TYPE type ) const override;
	virtual _dword							GetVertexBufferSize( ) const override;
	virtual const _byte*					GetVertexBufferData( ) const override;

	virtual _dword							GetIndexBufferSize( ) const override;
	virtual const _word*					GetIndexBufferData( ) const override;
};

//----------------------------------------------------------------------------
// GeometryFile
//----------------------------------------------------------------------------

class GeometryFile : public INTERFACE_BASEFILE_IMPL( IGeometryFile )
{
public:
	//!	The geometry file ID
	enum { _FILE_ID = EGE_ID( 'G', 'e', 'o', 'm' ) };

private:
	//!	The header info
	struct HeaderInfo
	{
		_dword	mFileID;

		HeaderInfo( )
		{
			mFileID = _FILE_ID;
		}
	};

private:
	typedef INTERFACE_BASEFILE_IMPL( IGeometryFile ) BaseClass;

private:
	//!	The header info
	HeaderInfo			mHeaderInfo;

	//!	The geometry mesh chunk
	GeometryMeshChunk*	mMeshChunk;

private:
	//!	Load geometry in binary format.
	_ubool LoadFromBinary( IStreamReader* stream_reader );
	//!	Load geometry in XML format.
	_ubool LoadFromXML( IStreamReader* stream_reader);

public:
	GeometryFile( );
	virtual ~GeometryFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT			GetFileID( ) const override;

	virtual _ubool 					LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 					Unload( ) override;

	virtual _ubool					SaveToStream( IStreamWriter* stream_writer, _dword flags ) const override;

// IGeometryFile Interface
public:
	virtual IGeometryMeshChunkRef	GetMeshChunk( ) override;

	virtual WStringR				DumpToXMLString( ) const override;
};

}