//! @file     BulletShape.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

#define BULLET_SHAPE_CLASS_DECL_WITH_NAME_BEGIN( name, x, res ) \
class Bullet##name##Shape : public TBulletShape< x##ShapePHI, res > \
{ \
private: \
	typedef TBulletShape< x##ShapePHI, res > BaseClass; \
public: \
	Bullet##name##Shape( res* shape ); \
	virtual ~Bullet##name##Shape( );
#define BULLET_SHAPE_CLASS_DECL_END( ) \
};
#define BULLET_SHAPE_CLASS_DECL_BEGIN( x, res ) BULLET_SHAPE_CLASS_DECL_WITH_NAME_BEGIN( x, x, res )
#define BULLET_SHAPE_CLASS_IMPL( x, res ) \
Bullet##x##Shape::Bullet##x##Shape( res* shape ) : BaseClass( shape ) \
{ \
} \
Bullet##x##Shape::~Bullet##x##Shape( ) \
{ \
}

//----------------------------------------------------------------------------
// TBulletShape
//----------------------------------------------------------------------------

template< typename Type, typename ShapeResourceType >
class TBulletShape : public Type
{
protected:
	//!	The shape resource
	ShapeResourceType*	mBTShape;

protected:
	TBulletShape( ShapeResourceType* shape ) { EGE_ASSERT( shape != _null ); mBTShape = shape; }
	virtual ~TBulletShape( ) { EGE_DELETE( mBTShape ); }

public:
	//!	Get the shape resource
	EGE_GETR_ACCESSOR( ShapeResourceType*, BTShape )
};


////----------------------------------------------------------------------------
//// BulletCircleShape
////----------------------------------------------------------------------------
//
//class BulletCircleShape : public TBulletShape< CircleShapePHI, b2CircleShape >
//{
//private:
//
//public:
//	BulletCircleShape( );
//	virtual ~BulletCircleShape( );
//
//public:
//};
//

////----------------------------------------------------------------------------
//// BulletEdgeShape
////----------------------------------------------------------------------------
//
//class BulletEdgeShape : public TBulletShape< EdgeShapePHI, b2EdgeShape >
//{
//private:
//
//public:
//	BulletEdgeShape( );
//	virtual ~BulletEdgeShape( );
//
//public:
//};
//
////----------------------------------------------------------------------------
//// BulletPolygonShape
////----------------------------------------------------------------------------
//
//class BulletPolygonShape : public TBulletShape< PolygonShapePHI, b2PolygonShape >
//{
//private:
//
//public:
//	BulletPolygonShape( );
//	virtual ~BulletPolygonShape( );
//};

//----------------------------------------------------------------------------
// BulletPlaneShape
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_DECL_BEGIN( Plane, btStaticPlaneShape )
BULLET_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// BulletBoxShape
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_DECL_BEGIN( Box, btBoxShape )
BULLET_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// BulletCylinderShape
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_DECL_BEGIN( Cylinder, btCylinderShape )
BULLET_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// BulletCapsuleShape
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_DECL_BEGIN( Capsule, btCapsuleShape )
BULLET_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// BulletConeShape
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_DECL_BEGIN( Cone, btConeShape )
BULLET_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// BulletSphereShape
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_DECL_BEGIN( Sphere, btSphereShape )
BULLET_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// BulletMultiSphereShape
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_DECL_BEGIN( MultiSphere, btMultiSphereShape )
BULLET_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// BulletConvexHullShape
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_DECL_BEGIN( ConvexHull, btConvexHullShape )
BULLET_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// BulletConvexTriangleMeshShape
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_DECL_BEGIN( ConvexTriangleMesh, btConvexTriangleMeshShape )
private:
	StridingMeshPHIRef	mStridingMesh;
public:
	BulletConvexTriangleMeshShape( StridingMeshPHI* striding_mesh, btConvexTriangleMeshShape* shape );
BULLET_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// BulletBvhTriangleMeshShape
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_DECL_WITH_NAME_BEGIN( BvhTriangleMesh, ConvexTriangleMesh, btBvhTriangleMeshShape )
private:
	StridingMeshPHIRef	mStridingMesh;
public:
	BulletBvhTriangleMeshShape( StridingMeshPHI* striding_mesh, btBvhTriangleMeshShape* shape );
BULLET_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// BulletHeightFieldTerrainShape
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_DECL_WITH_NAME_BEGIN( HeightFieldTerrain, HeightFieldTerrain, btHeightfieldTerrainShape )
private:
	_byte*	mFieldData;

public:
	BulletHeightFieldTerrainShape( _byte* field_data, btHeightfieldTerrainShape* shape );
BULLET_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// BulletCompoundShape
//----------------------------------------------------------------------------

BULLET_SHAPE_CLASS_DECL_WITH_NAME_BEGIN( Compound, Compound, btCompoundShape )
private:
	typedef Array< ShapePHIRef > ShapeArray;

private:
	ShapeArray	mChildShapes;

public:
	_dword GetChildShapesNumber( ) const;
	ShapePHIRef GetChildShape( _dword index );
	_ubool AddChildShape( const Matrix4& transform, ShapePHI* shape );
	_ubool RemoveChildShape( ShapePHI* shape );
BULLET_SHAPE_CLASS_DECL_END( )

}