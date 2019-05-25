//! @file     GeometryFile.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// GeometryMeshChunk Implementation
//----------------------------------------------------------------------------

GeometryMeshChunk::GeometryMeshChunk( )
{
	mVertexBufferData	= _null;
	mIndexBufferData	= _null;
}

GeometryMeshChunk::GeometryMeshChunk( _dword vertex_type, const _byte* vb_data, _dword vb_size, const _word* ib_data, _dword ib_size )
{
	mInfo.mVertexType			= vertex_type;
	mInfo.mVertexBufferStride	= GetVBStrideByType( vertex_type );
	mInfo.mVertexBufferNumber	= vb_size / mInfo.mVertexBufferStride;

	mInfo.mIndexBufferNumber = ib_size / sizeof( _word );
	mInfo.mIndexBufferStride = sizeof( _word );

	mVertexBufferData = new _byte[ mInfo.mVertexBufferStride * mInfo.mVertexBufferNumber ];
	EGE_MEM_CPY( mVertexBufferData, vb_data, mInfo.mVertexBufferStride * mInfo.mVertexBufferNumber );

	mIndexBufferData = new _word[mInfo.mIndexBufferNumber];
	EGE_MEM_CPY( mIndexBufferData, ib_data, mInfo.mIndexBufferNumber * sizeof( _word ) );

	mInfo.mReflectionPlane = Plane::cXYPlane;
}

GeometryMeshChunk::~GeometryMeshChunk( )
{
	EGE_DELETE_ARRAY( mVertexBufferData );
	EGE_DELETE_ARRAY( mIndexBufferData );
}

_ubool GeometryMeshChunk::GetVertexTypeByDecl( IStreamReader* stream_reader, _dword& type, _dword& stride ) const
{
	stream_reader->ReadDword( type );

	stride = GetVBStrideByType( type );

	return stride != 0;
}

_ubool GeometryMeshChunk::GetVertexTypeByDecl( ISerializableNode* node, _dword& type, _dword& stride ) const
{
	// We has the color component always
	type = _GVT_COLOR0;

	// Check bone info
	if ( node->GetChildNodeByName( L"skin" ).IsValid( ) )
		type |= _GVT_BONE_INDICES | _GVT_BONE_WEIGHT;

	// Check position
	_ubool pos_ret = _true;
	pos_ret &= node->HasProperty( L"posx" );
	pos_ret &= node->HasProperty( L"posy" );
	pos_ret &= node->HasProperty( L"posz" );
	if ( pos_ret )
		type |= _GVT_POS;

	// Check normal
	_ubool normal_ret = _true;
	normal_ret &= node->HasProperty( L"nx" );
	normal_ret &= node->HasProperty( L"ny" );
	normal_ret &= node->HasProperty( L"nz" );
	if ( normal_ret )
		type |= _GVT_NORMAL;

	// Check UV1
	_ubool uv1_ret = _true;
	uv1_ret &= node->HasProperty( L"u" );
	uv1_ret &= node->HasProperty( L"v" );
	if ( uv1_ret )
		type |= _GVT_UV1;

	// Check UV2
	_ubool uv2_ret = _true;
	uv2_ret &= node->HasProperty( L"u1" );
	uv2_ret &= node->HasProperty( L"v1" );
	if ( uv2_ret )
 		type |= _GVT_UV2;

	// Check Tangent
	_ubool tangent_ret = _true;
	tangent_ret &= node->HasProperty( L"tx" );
	tangent_ret &= node->HasProperty( L"ty" );
	tangent_ret &= node->HasProperty( L"tz" );
	if ( tangent_ret )
		type |= _GVT_TANGENT;

	stride = GetVBStrideByType( type );

	return stride != 0;
}

_void GeometryMeshChunk::UpdateAABox( const Vector3& pos )
{
	mInfo.mAABox.mMinVector.x = mInfo.mAABox.mMinVector.x == Math::cMinFloat ? pos.x : Math::Min( mInfo.mAABox.mMinVector.x, pos.x );
	mInfo.mAABox.mMinVector.y = mInfo.mAABox.mMinVector.y == Math::cMinFloat ? pos.y : Math::Min( mInfo.mAABox.mMinVector.y, pos.y );
	mInfo.mAABox.mMinVector.z = mInfo.mAABox.mMinVector.z == Math::cMinFloat ? pos.z : Math::Min( mInfo.mAABox.mMinVector.z, pos.z );
	mInfo.mAABox.mMaxVector.x = mInfo.mAABox.mMaxVector.x == Math::cMaxFloat ? pos.x : Math::Max( mInfo.mAABox.mMaxVector.x, pos.x );
	mInfo.mAABox.mMaxVector.y = mInfo.mAABox.mMaxVector.y == Math::cMaxFloat ? pos.y : Math::Max( mInfo.mAABox.mMaxVector.y, pos.y );
	mInfo.mAABox.mMaxVector.z = mInfo.mAABox.mMaxVector.z == Math::cMaxFloat ? pos.z : Math::Max( mInfo.mAABox.mMaxVector.z, pos.z );
}

_void  GeometryMeshChunk::UpdateUVBoundingBox( const Vector2& pos, Vector2& bounding_min, Vector2& bounding_max )
{
	bounding_min.x = bounding_min.x == Math::cMinFloat ? pos.x : Math::Min( bounding_min.x, pos.x );
	bounding_min.y = bounding_min.y == Math::cMinFloat ? pos.y : Math::Min( bounding_min.y, pos.y );
	bounding_max.x = bounding_max.x == Math::cMaxFloat ? pos.x : Math::Max( bounding_max.x, pos.x );
	bounding_max.y = bounding_max.y == Math::cMaxFloat ? pos.y : Math::Max( bounding_max.y, pos.y );
}

_ubool GeometryMeshChunk::ReadPos( ISerializableNode* node, Vector3& pos )
{
	_ubool ret = _true;

	ret &= node->Read( L"posx", pos.x );
	ret &= node->Read( L"posy", pos.y );
	ret &= node->Read( L"posz", pos.z );

	return ret;
}

_ubool GeometryMeshChunk::ReadColor( ISerializableNode* node, Color& color )
{
	_ubool ret = _true;

	ret &= node->Read( L"color", color );

	return ret;
}

_ubool GeometryMeshChunk::ReadNormal( ISerializableNode* node, Vector3& normal )
{
	_ubool ret = _true;

	ret &= node->Read( L"nx", normal.x );
	ret &= node->Read( L"ny", normal.y );
	ret &= node->Read( L"nz", normal.z );

	normal.Normalize( );

	return ret;
}

_ubool GeometryMeshChunk::ReadUV1( ISerializableNode* node, Vector2& uv )
{
	_ubool ret = _true;

	ret &= node->Read( L"u", uv.x );
	ret &= node->Read( L"v", uv.y );

	return ret;
}

_ubool GeometryMeshChunk::ReadUV2( ISerializableNode* node, Vector2& uv )
{
	_ubool ret = _true;

	ret &= node->Read( L"u1", uv.x );
	ret &= node->Read( L"v1", uv.y );

	return ret;
}

_ubool GeometryMeshChunk::ReadSkinInfo( ISerializableNode* node, _dword& bone_id, Vector4& weight )
{
	ISerializableNodeRef skin_node = node->GetChildNodeByName( L"skin" );
	if ( skin_node.IsValid( ) )
	{
		_byte*	bone_id_of_vertex	= (_byte*)&bone_id;
		_float* weight_of_vertex	= (_float*)&weight;

		// Read all skin info
		for ( _dword i = 0; i < _MAX_SKIN_NUMBER_PRE_VERTEX; i ++ )
		{
			_ubool ret = _true;
			ret &= skin_node->Read( L"bone", bone_id_of_vertex[i] );
			ret &= skin_node->Read( L"weight", weight_of_vertex[i] );
			if ( ret == _false )
				return _false;

			if ( skin_node->MoveNext( ) == _false )
				break;
		}
	}

	return _true;
}

_ubool GeometryMeshChunk::ReadTangent( ISerializableNode* node, Vector4& tangent )
{
	_ubool ret = _true;

	ret &= node->Read( L"tx", tangent.x );
	ret &= node->Read( L"ty", tangent.y );
	ret &= node->Read( L"tz", tangent.z );

	if ( node->Read( L"tw", tangent.w ) == _false )
		tangent.w = 1.0f;

	return ret;
}

_ubool GeometryMeshChunk::LoadVerticesInfo( ISerializableNode* node )
{
	// Get the vertex buffer number
	mInfo.mVertexBufferNumber = node->GetChildNodesNumber( );
	if ( mInfo.mVertexBufferNumber == 0 )
		return _false;

	// Get the first vertex node
	ISerializableNodeRef vertex_node = node->GetFirstChildNode( );
	if ( vertex_node.IsNull( ) )
		return _false;

	// Get the vertex type and stride
	if ( GetVertexTypeByDecl( vertex_node, mInfo.mVertexType, mInfo.mVertexBufferStride ) == _false )
		return _false;

	// Get the total vertex buffer size
	_dword vb_size = mInfo.mVertexBufferStride * mInfo.mVertexBufferNumber;

	// Create vertex buffer data
	EGE_ASSERT( mVertexBufferData == _null );
	mVertexBufferData = new _byte[ vb_size ];
	EGE_MEM_SET( mVertexBufferData, 0, vb_size );

	_ubool update_reflection_plane = ( mInfo.mVertexType & _GVT_POS ) && ( mInfo.mVertexType & _GVT_NORMAL ) && mInfo.mVertexBufferNumber != 0;
	Vector3 avg_normal = Vector3::cOrigin;
	Vector3 avg_position = Vector3::cOrigin;

	// Read vertices
	for ( _dword i = 0; i < vb_size; i += mInfo.mVertexBufferStride )
	{
		_byte* buffer = mVertexBufferData + i;

		// Read position
		if ( mInfo.mVertexType & _GVT_POS )
		{
			Vector3* pos = (Vector3*) buffer;
			if ( ReadPos( vertex_node, *pos ) == _false )
				return _false;

			// Update AABox
			UpdateAABox( *pos );

			if ( update_reflection_plane )
				avg_position += *pos;

			buffer += sizeof( Vector3 );
		}

		// Read color
		if ( mInfo.mVertexType & _GVT_COLOR0 )
		{
			// Try to read color, can be null when configure file is not existing
			Color color = Color::cWhite;
			ReadColor( vertex_node, color );

			// Use white color as default
			*(_dword*) buffer = color;

			// Nothing to do, just keep the color component info
			buffer += sizeof( _dword );
		}

		// Read normal
		if ( mInfo.mVertexType & _GVT_NORMAL )
		{
			if ( ReadNormal( vertex_node, *(Vector3*) buffer ) == _false )
				return _false;

			if ( update_reflection_plane )
				avg_normal += *(Vector3*) buffer;

			buffer += sizeof( Vector3 );
		}

		// Read UV1
		if ( mInfo.mVertexType & _GVT_UV1 )
		{
			if ( ReadUV1( vertex_node, *(Vector2*) buffer ) == _false )
				return _false;

			// Update uv bounding
			UpdateUVBoundingBox( *(Vector2*) buffer, mInfo.mUV1Bounding[0], mInfo.mUV1Bounding[1] );

			buffer += sizeof( Vector2 );
		}

		// Read UV2
		if ( mInfo.mVertexType & _GVT_UV2 )
		{
			if ( ReadUV2( vertex_node, *(Vector2*) buffer ) == _false )
				return _false;

			// Update uv bounding
			UpdateUVBoundingBox( *(Vector2*) buffer, mInfo.mUV2Bounding[0], mInfo.mUV2Bounding[1] );

			buffer += sizeof( Vector2 );
		}

		// Read skin info
		if ( ( mInfo.mVertexType & _GVT_BONE_INDICES ) && ( mInfo.mVertexType & _GVT_BONE_WEIGHT ) )
		{
			_dword*		bone_id = (_dword*) buffer;
			Vector4*	weight	= (Vector4*) (buffer + sizeof( _dword ));

			if ( ReadSkinInfo( vertex_node, *bone_id, *weight ) == _false )
				return _false;

			buffer += sizeof( _dword ) + sizeof( Vector4 );
		}

		// Read Tangent
		if ( mInfo.mVertexType & _GVT_TANGENT )
		{
			if ( ReadTangent( vertex_node, *(Vector4*) buffer ) == _false )
				return _false;

			buffer += sizeof( Vector4 );
		}

		// Check the bounds
		EGE_ASSERT( ( (buffer - (mVertexBufferData + i)) % mInfo.mVertexBufferStride ) == 0 );

		// Move to the next vertex node
		if ( vertex_node->MoveNext( ) == _false )
			break;
	}

	if ( update_reflection_plane )
	{
		avg_normal.Normalize( );
		avg_position /= (_float)mInfo.mVertexBufferNumber;
	}
	else
	{
		avg_normal = Vector3::cZAxis;
		avg_position = Vector3::cOrigin;
	}

	mInfo.mReflectionPlane = Plane( avg_position, avg_normal );

	return _true;
}

_ubool GeometryMeshChunk::LoadIndexesInfo( ISerializableNode* node )
{
	// Get the vertex index buffer number
	mInfo.mIndexBufferNumber = node->GetChildNodesNumber( );
	if ( mInfo.mIndexBufferNumber == 0 )
		return _false;

	// Get the first index node
	ISerializableNodeRef index_node = node->GetFirstChildNode( );
	if ( index_node.IsNull( ) )
		return _false;

	// We use the 16 bits index buffer data
	mInfo.mIndexBufferStride = sizeof( _word );

	// Create vertex index buffer data
	mIndexBufferData = new _word[ mInfo.mIndexBufferNumber ];
	if ( mIndexBufferData == _null )
		return _false;

	// Read indexes
	for ( _dword i = 0; i < mInfo.mIndexBufferNumber; i ++, index_node->MoveNext( ) )
	{
		if ( index_node->Read( L"value", mIndexBufferData[i] ) == _false )
			return _false;
	}

	return _true;
}

_ubool GeometryMeshChunk::Import( ISerializableNode* node )
{
	if ( node == _null )
		return _false;

	// Read basic info
	if ( node->Read( L"name", mChunkName ) == _false )
	{
		WLOG_ERROR( L"Load geometry mesh chunk name failed" );
		return _false;
	}

	// Read vertices info
	ISerializableNodeRef vertices_node = node->GetChildNodeByName( L"vertices" );
	if ( vertices_node.IsValid( ) && LoadVerticesInfo( vertices_node ) == _false )
	{
		WLOG_ERROR( L"Load geometry vertices info failed" );
		return _false;
	}

	// Read indexes info
	ISerializableNodeRef indexes_node = node->GetChildNodeByName( L"indexes" );
	if ( indexes_node.IsValid( ) && LoadIndexesInfo( indexes_node ) == _false )
	{
		WLOG_ERROR( L"Load geometry indexes info failed" );
		return _false;
	}

	return _true;
}

_ubool GeometryMeshChunk::WritePos( ISerializableNode* node, const Vector3& pos ) const
{
	if ( node->Write( L"posx", L"posy", L"posz", pos ) == _false )
		return _false;

	return _true;
}

_ubool GeometryMeshChunk::WriteNormal( ISerializableNode* node, const Vector3& normal ) const
{
	if ( node->Write( L"nx", L"ny", L"nz", normal ) == _false )
		return _false;

	return _true;
}

_ubool GeometryMeshChunk::WriteUV1( ISerializableNode* node, const Vector2& uv ) const
{
	if ( node->Write( L"u", L"v", uv ) == _false )
		return _false;

	return _true;
}

_ubool GeometryMeshChunk::WriteUV2( ISerializableNode* node, const Vector2& uv ) const
{
	if ( node->Write( L"u1", L"v1", uv ) == _false )
		return _false;

	return _true;
}

_ubool GeometryMeshChunk::WriteSkinInfo( ISerializableNode* node, _dword bone_id, const Vector4& weight ) const
{
	_dword bone_id_of_vertex[ _MAX_SKIN_NUMBER_PRE_VERTEX ]	= {0};
	_float weight_of_vertex[ _MAX_SKIN_NUMBER_PRE_VERTEX ]	= {0};

	bone_id_of_vertex[0]	= (_dword) EGE_LOBYTE( EGE_LOWORD( bone_id ) );
	bone_id_of_vertex[1]	= (_dword) EGE_HIBYTE( EGE_LOWORD( bone_id ) );
	bone_id_of_vertex[2]	= (_dword) EGE_LOBYTE( EGE_HIWORD( bone_id ) );
	bone_id_of_vertex[3]	= (_dword) EGE_HIBYTE( EGE_HIWORD( bone_id ) );

	weight_of_vertex[0]		= weight.x;
	weight_of_vertex[1]		= weight.y;
	weight_of_vertex[2]		= weight.z;
	weight_of_vertex[3]		= weight.w;

	_dword skin_number = 0;
	for ( _dword i = 0; i < _MAX_SKIN_NUMBER_PRE_VERTEX; ++ i, skin_number ++ )
	{
		if ( weight_of_vertex[i] == 0.0f )
			break;
	}

	for ( _dword i = 0; i < skin_number; ++ i )
	{
		ISerializableNodeRef skin_node = node->InsertChildNode( L"skin", L"", _false );
		if ( skin_node->Write( L"bone", bone_id_of_vertex[i] ) == _false )
			return _false;

		if ( skin_node->Write( L"weight", weight_of_vertex[i] ) == _false )
			return _false;
	}
	return _true;
}

_ubool GeometryMeshChunk::WriteTangent( ISerializableNode* node, const Vector4& tangent ) const
{
	if ( node->Write( L"tx", L"ty", L"tz", L"tw", tangent ) == _false )
		return _false;

	return _true;
}

_ubool GeometryMeshChunk::WriteVerticesInfo( ISerializableNode* node ) const
{
	ISerializableNodeRef vertices_node = node->InsertChildNode( L"vertices", L"", _false );

	// Get the total vertex buffer size
	_dword vb_size = mInfo.mVertexBufferStride * mInfo.mVertexBufferNumber;

	for ( _dword i = 0; i < vb_size; i += mInfo.mVertexBufferStride )
	{
		ISerializableNodeRef vertex_node = vertices_node->InsertChildNode( L"vertex", L"", _false );

		_byte* buffer = mVertexBufferData + i;

		// Write pos
		if ( mInfo.mVertexType & _GVT_POS )
		{
			if ( WritePos( vertex_node, *(Vector3*) buffer ) == _false )
				return _false;

			buffer += sizeof( Vector3 );
		}

		// Skip to write color
		if ( mInfo.mVertexType & _GVT_COLOR0 )
			buffer += sizeof( _dword );

		// Write normal
		if ( mInfo.mVertexType & _GVT_NORMAL )
		{
			if ( WriteNormal( vertex_node, *(Vector3*) buffer ) == _false )
				return _false;

			buffer += sizeof( Vector3 );
		}

		// Write UV1
		if ( mInfo.mVertexType & _GVT_UV1 )
		{
			if ( WriteUV1( vertex_node, *(Vector2*) buffer ) == _false )
				return _false;

			buffer += sizeof( Vector2 );
		}

		// Write UV2
		if ( mInfo.mVertexType & _GVT_UV2 )
		{
			if ( WriteUV2( vertex_node, *(Vector2*) buffer ) == _false )
				return _false;

			buffer += sizeof( Vector2 );
		}

		// Write skin info
		if ( ( mInfo.mVertexType & _GVT_BONE_INDICES ) && ( mInfo.mVertexType & _GVT_BONE_WEIGHT ) )
		{
			_dword*		bone_id = (_dword*) buffer;
			Vector4*	weight	= (Vector4*) (buffer + sizeof( _dword ));

			if ( WriteSkinInfo( vertex_node, *bone_id, *weight ) == _false )
				return _false;

			buffer += sizeof( _dword ) + sizeof( Vector4 );
		}

		// Write Tangent
		if ( mInfo.mVertexType & _GVT_TANGENT )
		{
			if ( WriteTangent( vertex_node, *(Vector4*) buffer ) == _false )
				return _false;

			buffer += sizeof( Vector4 );
		}

		// Check the bounds
		EGE_ASSERT( ( (buffer - (mVertexBufferData + i)) % mInfo.mVertexBufferStride ) == 0 );
	}

	return _true;
}

_ubool GeometryMeshChunk::WriteIndexesInfo( ISerializableNode* node ) const
{
	ISerializableNodeRef indexes_node = node->InsertChildNode( L"indexes", L"", _false );
	for ( _dword i = 0; i < mInfo.mIndexBufferNumber; i ++ )
	{
		ISerializableNodeRef index_node = indexes_node->InsertChildNode( L"index", L"", _false );
		if ( index_node->Write( L"value", mIndexBufferData[i] ) == _false )
			return _false;
	}

	return _true;
}

_ubool GeometryMeshChunk::Export( ISerializableNode* node ) const
{
	if ( node->Write( L"name", mChunkName ) == _false )
		return _false;

	if ( WriteVerticesInfo( node ) == _false )
		return _false;

	if ( WriteIndexesInfo( node ) == _false )
		return _false;	

	return _true;
}

WStringPtr GeometryMeshChunk::GetChunkName( ) const
{
	return mChunkName;
}

_ubool GeometryMeshChunk::ReadFromStream( IStreamReader* stream_reader )
{
	stream_reader->ReadString( mChunkName );
	stream_reader->SeekByArrangedValueFromBegin( 4 );

	if ( LoadVerticesInfo( stream_reader ) == _false )
		return _false;

	stream_reader->SeekByArrangedValueFromBegin( 4 );

	if ( LoadIndexesInfo( stream_reader ) == _false )
		return _false;

	stream_reader->SeekByArrangedValueFromBegin( 4 );

	return _true;
}

_ubool GeometryMeshChunk::WriteToStream( IStreamWriter* stream_writer, _dword output_vertex_declare ) const
{
	_dword fixed_output_vertex_decl = output_vertex_declare == 0 ? mInfo.mVertexType : output_vertex_declare;
	fixed_output_vertex_decl = fixed_output_vertex_decl & mInfo.mVertexType;
	
	stream_writer->WriteString( mChunkName );
	stream_writer->SeekByArrangedValueFromBegin( 4 );

	VertexAccessor vertex_accessor;
	if ( BuildVertexAccessor( fixed_output_vertex_decl, vertex_accessor ) == _false )
		return _false;

	if ( GenerateTangentAccessor( vertex_accessor ) == _false )
	{
		fixed_output_vertex_decl &= ~( (_dword) _GVT_NORMAL );
		fixed_output_vertex_decl &= ~( (_dword) _GVT_TANGENT );
	}
	else
	{
		fixed_output_vertex_decl |= (_dword) _GVT_NORMAL;
		fixed_output_vertex_decl |= (_dword) _GVT_TANGENT;
	}

	if ( WriteVerticesInfo( stream_writer, fixed_output_vertex_decl, mInfo.mVertexBufferNumber, vertex_accessor ) == _false )
		return _false;

	stream_writer->SeekByArrangedValueFromBegin( 4 );

	if ( WriteIndexesInfo( stream_writer ) == _false )
		return _false;

	stream_writer->SeekByArrangedValueFromBegin( 4 );

	return _true;
}

_ubool GeometryMeshChunk::ReadAABBox( IStreamReader* stream_reader, AxisAlignedBox& bounding )
{
	stream_reader->ReadFloat( bounding.mMinVector.x );
	stream_reader->ReadFloat( bounding.mMinVector.y );
	stream_reader->ReadFloat( bounding.mMinVector.z );
	stream_reader->ReadFloat( bounding.mMaxVector.x );
	stream_reader->ReadFloat( bounding.mMaxVector.y );
	stream_reader->ReadFloat( bounding.mMaxVector.z );

	return _true;
}

_ubool GeometryMeshChunk::ReadUVBoundingBox( IStreamReader* stream_reader, Vector2& bounding_min, Vector2& bounding_max )
{
	stream_reader->ReadFloat( bounding_min.x );
	stream_reader->ReadFloat( bounding_min.y );
	stream_reader->ReadFloat( bounding_max.x );
	stream_reader->ReadFloat( bounding_max.y );

	return _true;
}

_ubool GeometryMeshChunk::ReadPos( IStreamReader* stream_reader, Vector3& pos, _float& tangent_w )
{
	_qword code = 0;
	stream_reader->ReadQword( code );

	pos = ValueEncoder::DecodeVector3<_qword>( code, mInfo.mAABox.mMinVector, mInfo.mAABox.mMaxVector, 21 );

	_qword flag = ( code >> 63 ) & 0x1;
	tangent_w = flag == 0 ? 1.0f : -1.0f;

	return _true;
}

_ubool GeometryMeshChunk::ReadUV( IStreamReader* stream_reader, Vector2& uv, const Vector2& bounding_min, const Vector2& bounding_max )
{
	_dword code = 0;
	stream_reader->ReadDword( code );

	uv = ValueEncoder::DecodeVector2<_dword>( code, bounding_min, bounding_max );

	return _true;
}

_ubool GeometryMeshChunk::ReadSkinInfo( IStreamReader* stream_reader, _dword& bone_id, Vector4& weight )
{
	stream_reader->ReadDword( bone_id );

	_dword encode_value = 0;
	stream_reader->ReadDword( encode_value );
	weight = ValueEncoder::DecodeWeight<_dword>( encode_value );

	return _true;
}

_ubool GeometryMeshChunk::ReadTangentSpaceRotation( IStreamReader* stream_reader, Vector3* normal, Vector4* tangent )
{
	_dword decode_value = 0;
	stream_reader->ReadDword( decode_value );

	Quaternion rot = ValueEncoder::DecodeQuaternion<_dword>( decode_value );
	if ( normal != _null )
	{
		*normal = Vector3::cZAxis * rot;
	}
		
	if ( tangent != _null )
	{
		Vector3 tangent3 = Vector3::cXAxis * rot;
		tangent->x = tangent3.x;
		tangent->y = tangent3.y;
		tangent->z = tangent3.z;
	}

	return _true;
}

_ubool GeometryMeshChunk::LoadVerticesInfo( IStreamReader* stream_reader )
{
	// Get the vertex buffer number
	stream_reader->ReadDword( mInfo.mVertexBufferNumber );
	if ( mInfo.mVertexBufferNumber == 0 )
		return _false;

	// Get the vertex type and stride
	if ( GetVertexTypeByDecl( stream_reader, mInfo.mVertexType, mInfo.mVertexBufferStride ) == _false )
		return _false;

	// read aabb and uv bounding box for decompress position and uv
	if ( mInfo.mVertexType & _GVT_POS )
	{
		if ( ReadAABBox( stream_reader, mInfo.mAABox ) == _false )
			return _false;
	}

	if ( mInfo.mVertexType & _GVT_UV1 )
	{
		if ( ReadUVBoundingBox( stream_reader, mInfo.mUV1Bounding[0], mInfo.mUV1Bounding[1] ) == _false )
			return _false;
	}

	if ( mInfo.mVertexType & _GVT_UV2 )
	{
		if ( ReadUVBoundingBox( stream_reader, mInfo.mUV2Bounding[0], mInfo.mUV2Bounding[1] ) == _false )
			return _false;
	}

	// Get the total vertex buffer size
	_dword vb_size = mInfo.mVertexBufferStride * mInfo.mVertexBufferNumber;

	// Create vertex buffer data
	EGE_ASSERT( mVertexBufferData == _null );
	mVertexBufferData = new _byte[ vb_size ];
	EGE_MEM_SET( mVertexBufferData, 0, vb_size );

	_ubool update_reflection_plane = ( mInfo.mVertexType & _GVT_POS ) && ( mInfo.mVertexType & _GVT_NORMAL ) && mInfo.mVertexBufferNumber != 0;
	Vector3 avg_normal = Vector3::cOrigin;
	Vector3 avg_position = Vector3::cOrigin;

	// Read vertices
	for ( _dword i = 0; i < vb_size; i += mInfo.mVertexBufferStride )
	{
		_byte* buffer = mVertexBufferData + i;

		_float tangent_w = 1.0f;

		// Read position
		if ( mInfo.mVertexType & _GVT_POS )
		{
			Vector3* pos = (Vector3*) buffer;
			if ( ReadPos( stream_reader, *pos, tangent_w ) == _false )
				return _false;

			if ( update_reflection_plane )
				avg_position += *pos;

			buffer += sizeof( Vector3 );
		}

		// Skip to read color
		if ( mInfo.mVertexType & _GVT_COLOR0 )
		{
			// Use white color as default
			*(_dword*) buffer = Color::cWhite;

			buffer += sizeof( _dword );
		}

		// Get the normal pointer and wait to update it
		Vector3* normal_ptr = _null;
		if ( mInfo.mVertexType & _GVT_NORMAL )
		{
			normal_ptr = (Vector3*) buffer;

			buffer += sizeof( Vector3 );
		}

		// Read UV1
		if ( mInfo.mVertexType & _GVT_UV1 )
		{
			if ( ReadUV( stream_reader, *(Vector2*) buffer, mInfo.mUV1Bounding[0], mInfo.mUV1Bounding[1] ) == _false )
				return _false;

			buffer += sizeof( Vector2 );
		}

		// Read UV2
		if ( mInfo.mVertexType & _GVT_UV2 )
		{
			if ( ReadUV( stream_reader, *(Vector2*) buffer, mInfo.mUV2Bounding[0], mInfo.mUV2Bounding[0] ) == _false )
				return _false;

			buffer += sizeof( Vector2 );
		}

		// Read skin info
		if ( ( mInfo.mVertexType & _GVT_BONE_INDICES ) && ( mInfo.mVertexType & _GVT_BONE_WEIGHT ) )
		{
			_dword*		bone_id = (_dword*) buffer;
			Vector4*	weight = (Vector4*) ( buffer + sizeof( _dword ) );

			if ( ReadSkinInfo( stream_reader, *bone_id, *weight ) == _false )
				return _false;

			buffer += sizeof( _dword ) + sizeof( Vector4 );
		}

		// Get the tangent pointer and wait to update it
		Vector4* tangent_ptr = _null;
		if ( mInfo.mVertexType & _GVT_TANGENT )
		{
			tangent_ptr = (Vector4*) buffer;

			buffer += sizeof( Vector4 );
		}

		// Read the tanget space rotation
		if ( ( mInfo.mVertexType & _GVT_NORMAL ) || ( mInfo.mVertexType & _GVT_TANGENT ) )
		{
			if ( ReadTangentSpaceRotation( stream_reader, normal_ptr, tangent_ptr ) == _false )
				return _false;
		}

		if ( tangent_ptr != _null )
			tangent_ptr->w = tangent_w;

		if ( update_reflection_plane )
			avg_normal += *(Vector3*) normal_ptr;

		// Check the bounds
		EGE_ASSERT( ( (buffer - (mVertexBufferData + i)) % mInfo.mVertexBufferStride ) == 0 );
	}

	if ( update_reflection_plane )
	{
		avg_normal.Normalize( );
		avg_position /= (_float)mInfo.mVertexBufferNumber;
	}
	else
	{
		avg_normal = Vector3::cZAxis;
		avg_position = Vector3::cOrigin;
	}
	mInfo.mReflectionPlane = Plane( avg_position, avg_normal );

	return _true;
}

_ubool GeometryMeshChunk::LoadIndexesInfo( IStreamReader* stream_reader )
{
	// Get the vertex index buffer number
	stream_reader->ReadDword( mInfo.mIndexBufferNumber );
	if ( mInfo.mIndexBufferNumber == 0 )
		return _false;

	// We use the 16 bits index buffer data
	mInfo.mIndexBufferStride = sizeof( _word );

	// Create vertex index buffer data
	mIndexBufferData = new _word[ mInfo.mIndexBufferNumber ];
	if ( mIndexBufferData == _null )
		return _false;

	// Read indexes
	for ( _dword i = 0; i < mInfo.mIndexBufferNumber; i ++ )
	{
		stream_reader->ReadWord( mIndexBufferData[i] );
	}

	return _true;
}

_ubool GeometryMeshChunk::WriteAABBox( IStreamWriter* stream_writer, const AxisAlignedBox& bounding ) const
{
	stream_writer->WriteFloat( bounding.mMinVector.x );
	stream_writer->WriteFloat( bounding.mMinVector.y );
	stream_writer->WriteFloat( bounding.mMinVector.z );
	stream_writer->WriteFloat( bounding.mMaxVector.x );
	stream_writer->WriteFloat( bounding.mMaxVector.y );
	stream_writer->WriteFloat( bounding.mMaxVector.z );

	return _true;
}

_ubool GeometryMeshChunk::WriteUVBoundingBox( IStreamWriter* stream_writer, const Vector2& bounding_min, const Vector2& bounding_max ) const
{
	stream_writer->WriteFloat( bounding_min.x );
	stream_writer->WriteFloat( bounding_min.y );
	stream_writer->WriteFloat( bounding_max.x );
	stream_writer->WriteFloat( bounding_max.y );

	return _true;
}

_ubool GeometryMeshChunk::WritePos( IStreamWriter* stream_writer, const Vector3& pos, const AxisAlignedBox& bounding_box, _float tangent_w ) const
{
	_qword tangent_flag = tangent_w < 0.0f ? 1 : 0;
	_qword encode_value = ValueEncoder::EncodeVector3<_qword>( pos, bounding_box.mMinVector, bounding_box.mMaxVector, 21 );
	encode_value |= ( tangent_flag & 0x1 ) << 63;
	stream_writer->WriteQword( encode_value );

	return _true;
}

_ubool GeometryMeshChunk::WriteUV( IStreamWriter* stream_writer, const Vector2& uv, const Vector2& bounding_min, const Vector2& bounding_max ) const
{
	_dword encode_value = ValueEncoder::EncodeVector2<_dword>( uv, bounding_min, bounding_max );
	stream_writer->WriteDword( encode_value );

	return _true;
}

_ubool GeometryMeshChunk::WriteSkinInfo( IStreamWriter* stream_writer, _dword bone_id, const Vector4& weight ) const
{
	stream_writer->WriteDword( bone_id );

	_dword encode_value = ValueEncoder::EncodeWeight<_dword>( weight );
	stream_writer->WriteDword( encode_value );

	return _true;
}

_ubool GeometryMeshChunk::WriteTangentSpaceRotation( IStreamWriter* stream_writer, const Vector3& normal, const Vector4& tangent ) const
{
	Quaternion rot;
	rot.Rotation( Vector3::cXAxis, Vector3::cZAxis, Vector3( tangent.x, tangent.y, tangent.z ), normal );
	_dword encode_value = ValueEncoder::EncodeQuaternion<_dword>( rot );

	stream_writer->WriteDword( encode_value );

	return _true;
}

_ubool GeometryMeshChunk::WriteVerticesInfo( IStreamWriter* stream_writer, _dword output_vertex_declare, _dword total_vertex_count, const VertexAccessor& vertex_buffer ) const
{
	// write the vertex buffer number
	stream_writer->WriteDword( total_vertex_count );

	// write the vertex type
	stream_writer->WriteDword( output_vertex_declare );

	// write aabb and uv bounding box for decompress position and uv
	if ( output_vertex_declare & _GVT_POS )
	{
		if ( WriteAABBox( stream_writer, mInfo.mAABox ) == _false )
			return _false;
	}

	if ( output_vertex_declare & _GVT_UV1 )
	{
		if ( WriteUVBoundingBox( stream_writer, mInfo.mUV1Bounding[0], mInfo.mUV1Bounding[1] ) == _false )
			return _false;
	}

	if ( output_vertex_declare & _GVT_UV2 )
	{
		if ( WriteUVBoundingBox( stream_writer, mInfo.mUV2Bounding[0], mInfo.mUV2Bounding[1] ) == _false )
			return _false;
	}

	// write buffer
	for ( _dword i = 0; i < total_vertex_count; ++ i )
	{
		// Write pos
		if ( output_vertex_declare & _GVT_POS )
		{
			_float tangent_w = 1.0f;
			if ( vertex_buffer.mTangent.IsValid( ) )
				tangent_w = vertex_buffer.mTangent[i].w;

			if ( WritePos( stream_writer, vertex_buffer.mPosition[i], mInfo.mAABox, tangent_w ) == _false )
				return _false;
		}
		// Write UV1
		if ( output_vertex_declare & _GVT_UV1 )
		{
			if ( WriteUV( stream_writer, vertex_buffer.mUV1[i], mInfo.mUV1Bounding[0], mInfo.mUV1Bounding[1] ) == _false )
				return _false;
		}
		// Write UV2
		if ( output_vertex_declare & _GVT_UV2 )
		{
			if ( WriteUV( stream_writer, vertex_buffer.mUV2[i], mInfo.mUV2Bounding[0], mInfo.mUV2Bounding[1] ) == _false )
				return _false;
		}
		// Write skin info
		if ( ( output_vertex_declare & _GVT_BONE_INDICES ) && ( output_vertex_declare & _GVT_BONE_WEIGHT ) )
		{
			if ( WriteSkinInfo( stream_writer, vertex_buffer.mBoneID[i], vertex_buffer.mBoneWeight[i] ) == _false )
				return _false;
		}

		// Write tangent space
		if ( ( output_vertex_declare & _GVT_NORMAL ) && ( output_vertex_declare & _GVT_TANGENT ) )
		{
			if ( WriteTangentSpaceRotation( stream_writer, vertex_buffer.mNormal[i], vertex_buffer.mTangent[i] ) == _false )
				return _true;
		}
	}

	return _true;
}

_ubool GeometryMeshChunk::BuildVertexAccessor( _dword output_vertex_declare, VertexAccessor& vertex_accessor ) const
{
	_byte* buffer = mVertexBufferData;

	// get pos
	if ( mInfo.mVertexType & _GVT_POS )
	{
		if ( output_vertex_declare & _GVT_POS )
			vertex_accessor.mPosition.Share( mInfo.mVertexBufferNumber, buffer, mInfo.mVertexBufferStride );
		buffer += sizeof( Vector3 );
	}

	// get color
	if ( mInfo.mVertexType & _GVT_COLOR0 )
	{
		if ( output_vertex_declare & _GVT_COLOR0 )
			vertex_accessor.mColor.Share( mInfo.mVertexBufferNumber, buffer, mInfo.mVertexBufferStride );
		buffer += sizeof( _dword );
	}

	// get normal
	if ( mInfo.mVertexType & _GVT_NORMAL )
	{
		if ( output_vertex_declare & _GVT_NORMAL )
			vertex_accessor.mNormal.Share( mInfo.mVertexBufferNumber, buffer, mInfo.mVertexBufferStride );
		buffer += sizeof( Vector3 );
	}

	// get UV1
	if ( mInfo.mVertexType & _GVT_UV1 )
	{
		if ( output_vertex_declare & _GVT_UV1 )
			vertex_accessor.mUV1.Share( mInfo.mVertexBufferNumber, buffer, mInfo.mVertexBufferStride );
		buffer += sizeof( Vector2 );
	}

	// get UV2
	if ( mInfo.mVertexType & _GVT_UV2 )
	{
		if ( output_vertex_declare & _GVT_UV2 )
			vertex_accessor.mUV2.Share( mInfo.mVertexBufferNumber, buffer, mInfo.mVertexBufferStride );
		buffer += sizeof( Vector2 );
	}

	// get skin info
	if ( ( mInfo.mVertexType & _GVT_BONE_INDICES ) && ( mInfo.mVertexType & _GVT_BONE_WEIGHT ) )
	{
		if ( ( output_vertex_declare & _GVT_BONE_INDICES ) && ( output_vertex_declare & _GVT_BONE_WEIGHT ) )
		{
			vertex_accessor.mBoneID.Share( mInfo.mVertexBufferNumber, buffer, mInfo.mVertexBufferStride );
			vertex_accessor.mBoneWeight.Share( mInfo.mVertexBufferNumber, ( buffer + sizeof( _dword ) ), mInfo.mVertexBufferStride );
		}
		buffer += sizeof( _dword ) + sizeof( Vector4 );
	}

	// get Tangent
	if ( mInfo.mVertexType & _GVT_TANGENT )
	{
		if ( output_vertex_declare & _GVT_TANGENT )
			vertex_accessor.mTangent.Share( mInfo.mVertexBufferNumber, buffer, mInfo.mVertexBufferStride );
		buffer += sizeof( Vector4 );
	}

	return _true;
}

_ubool GeometryMeshChunk::GenerateTangentAccessor( VertexAccessor& vertex_accessor ) const
{
	if ( vertex_accessor.mPosition.IsNull( ) || vertex_accessor.mNormal.IsNull( ) || vertex_accessor.mUV1.IsNull( ) )
		return vertex_accessor.mTangent.IsValid( );

	vertex_accessor.mTangent.Clear( );

	WordMemSegmentPtr index_accessor;
	index_accessor.Share( mInfo.mIndexBufferNumber, mIndexBufferData, mInfo.mIndexBufferStride );
	vertex_accessor.mTangent.Create( mInfo.mVertexBufferNumber );

	Math::CalculateTangentByNormalUV( index_accessor, vertex_accessor.mPosition, vertex_accessor.mNormal, vertex_accessor.mUV1, vertex_accessor.mTangent );

	return _true;
}

_ubool GeometryMeshChunk::WriteIndexesInfo( IStreamWriter* stream_writer ) const
{
	// write the vertex index buffer number
	stream_writer->WriteDword( mInfo.mIndexBufferNumber );

	// Read indexes
	for ( _dword i = 0; i < mInfo.mIndexBufferNumber; i ++ )
	{
		stream_writer->WriteWord( mIndexBufferData[i] );
	}

	return _true;
}

const GeometryMeshChunkInfo& GeometryMeshChunk::GetInfo( ) const
{
	return mInfo;
}

_dword GeometryMeshChunk::GetVertexBufferElementOffset( _GEOMETRY_VERTEX_TYPE type ) const
{
	return GetVBOffsetByType( mInfo.mVertexType, type );
}

_dword GeometryMeshChunk::GetVertexBufferSize( ) const
{
	return mInfo.mVertexBufferNumber * mInfo.mVertexBufferStride;
}

const _byte* GeometryMeshChunk::GetVertexBufferData( ) const
{
	return mVertexBufferData;
}

_dword GeometryMeshChunk::GetIndexBufferSize( ) const
{
	return mInfo.mIndexBufferNumber * mInfo.mIndexBufferStride;
}

const _word* GeometryMeshChunk::GetIndexBufferData( ) const
{
	return mIndexBufferData;
}

//----------------------------------------------------------------------------
// GeometryFile Implementation
//----------------------------------------------------------------------------

GeometryFile::GeometryFile( )
{
	mMeshChunk = _null;
}

GeometryFile::~GeometryFile( )
{
	Unload( );
}

_FILE_FORMAT GeometryFile::GetFileID( ) const
{
	return _FF_GEOMETRY;
}

_ubool GeometryFile::LoadFromBinary( IStreamReader* stream_reader )
{
	// Read file header
	stream_reader->ReadBuffer( &mHeaderInfo, sizeof( HeaderInfo ) );

	// Check the file ID
	if ( mHeaderInfo.mFileID != _FILE_ID )
		return _false;

	// Create and import mesh chunk
	mMeshChunk = new GeometryMeshChunk( );
	if ( mMeshChunk->ReadFromStream( stream_reader ) == _false )
		return _false;

	return _true;
}

_ubool GeometryFile::LoadFromXML( IStreamReader* stream_reader )
{
	ISerializableNodeRef root_node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( stream_reader );
	if ( root_node.IsNull( ) )
	{
		WLOG_ERROR( L"Load geometry from XML stream failed" );
		return _false;
	}

	// Get the serializable node of mesh element
	ISerializableNodeRef mesh_node = root_node->GetFirstChildNode( );
	if ( mesh_node.IsNull( ) )
	{
		WLOG_ERROR( L"Load geometry from XML stream failed, due to none any child node" );
		return _false;
	}

	// Get the chunk type name
	WString chunk_type_name = mesh_node->GetNodeName( );

	// Create and import mesh chunk
	mMeshChunk = new GeometryMeshChunk( );
	if ( mMeshChunk->Import( mesh_node ) == _false )
	{
		WLOG_ERROR( L"Import geometry chunk failed" );
		return _false;
	}

	return _true;
}

_ubool GeometryFile::LoadFromStream( IStreamReader* stream_reader )
{
	// It's binary file format
	if ( GetInterfaceFactory( )->GetCommonFileTypeFromStream( stream_reader ) == _FF_GEOMETRY )
		return LoadFromBinary( stream_reader );

	return LoadFromXML( stream_reader );
}

_void GeometryFile::Unload( )
{
	EGE_RELEASE( mMeshChunk );
}

_ubool GeometryFile::SaveToStream( IStreamWriter* stream_writer, _dword flags ) const
{
	// Write file ID
	stream_writer->WriteDword( _FILE_ID );

	// Write file header info
	stream_writer->WriteBuffer( &mHeaderInfo, sizeof( HeaderInfo ) );

	// Write mesh chunk
	if ( mMeshChunk->WriteToStream( stream_writer, flags ) == _false )
		return _false;

	return _true;
}

IGeometryMeshChunkRef GeometryFile::GetMeshChunk( ) 
{
	return mMeshChunk;
}

WString GeometryFile::DumpToXMLString( ) const
{
	IMarkupLangFileRef xmlfile = GetInterfaceFactory( )->CreateXMLFile( L"root", _ENCODING_UTF8 );
	if ( xmlfile.IsNull( ) )
		return WString( L"" );

	ISerializableNodeRef node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( xmlfile );
	if ( node.IsNull( ) )
		return WString( L"" );

	ISerializableNodeRef mesh_node = node->InsertChildNode( L"mesh", L"", _false );
	if ( mMeshChunk->Export( mesh_node ) == _false )
		return WString( L"" );

	return xmlfile->GetRootElement( )->DumpToString( );
}
