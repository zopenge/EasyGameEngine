//! @file     BulletStridingMesh.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// BulletStridingMesh
//----------------------------------------------------------------------------

class BulletStridingMesh : public StridingMeshPHI
{
private:
	Vector3*					mVertexBuffer;
	_word*						mIndexBuffer;
	btStridingMeshInterface*	mBTStridingMesh;

public:
	EGE_GET_ACCESSOR( Vector3*, VertexBuffer )
	EGE_GET_ACCESSOR( _word*, IndexBuffer )
	EGE_GET_ACCESSOR( btStridingMeshInterface*, BTStridingMesh )

public:
	BulletStridingMesh( Vector3* vb, _word* ib, btStridingMeshInterface* striding_mesh );
	virtual ~BulletStridingMesh( );
};

}