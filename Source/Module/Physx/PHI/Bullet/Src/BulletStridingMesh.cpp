//! @file     BulletStridingMesh.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

#if (_PHYSX_USE_BULLET_ == 1)

//----------------------------------------------------------------------------
// BulletDrv-StridingMesh Implementation
//----------------------------------------------------------------------------

StridingMeshPHIPassRef BulletDrv::CreateStridingMesh( const Vector3* vertices_list, _dword vertices_number, const _word* index_list, _dword index_number )
{
	if ( vertices_list == _null || vertices_number == 0 )
		return _null;

	if ( index_list == _null || index_number == 0 )
		return _null;

	Vector3* vertices_list_temp	= new Vector3[ vertices_number ];
	EGE_MEM_CPY( vertices_list_temp, vertices_list, vertices_number * sizeof( Vector3 ) );

	_word* index_list_temp = new _word[ index_number ];
	EGE_MEM_CPY( index_list_temp, index_list, index_number * sizeof( _word ) );

	btIndexedMesh mesh = BulletHelper::BuildIndexedMesh( vertices_list_temp, vertices_number, index_list_temp, index_number );

	btTriangleIndexVertexArray* bullet_triangle_index_vertex_array = new btTriangleIndexVertexArray( );
	bullet_triangle_index_vertex_array->addIndexedMesh( mesh, PHY_SHORT );

	return new BulletStridingMesh( vertices_list_temp, index_list_temp, bullet_triangle_index_vertex_array );
}

//----------------------------------------------------------------------------
// BulletStridingMesh Implementation
//----------------------------------------------------------------------------

BulletStridingMesh::BulletStridingMesh( Vector3* vb, _word* ib, btStridingMeshInterface* striding_mesh )
{
	EGE_ASSERT( vb != _null );
	EGE_ASSERT( ib != _null );
	EGE_ASSERT( striding_mesh != _null );

	mVertexBuffer	= vb;
	mIndexBuffer	= ib;
	mBTStridingMesh	= striding_mesh;
}

BulletStridingMesh::~BulletStridingMesh( )
{
	EGE_DELETE_ARRAY( mVertexBuffer );
	EGE_DELETE_ARRAY( mIndexBuffer );

	EGE_DELETE( mBTStridingMesh );
}

#endif