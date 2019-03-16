//! @file     PhysxShape.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// PhysxChainShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( Chain, _TYPE_CHAIN )

//----------------------------------------------------------------------------
// PhysxCircleShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( Circle, _TYPE_CIRCLE )

_void PhysxCircleShape::SetRadius( _float radius )
{
	gDynamicPHI->SetCircleShapeRadius( mShapeResource, radius );
}

_float PhysxCircleShape::GetRadius( ) const
{
	return gDynamicPHI->GetCircleShapeRadius( mShapeResource.GetPtr( ) );
}

//----------------------------------------------------------------------------
// PhysxEdgeShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( Edge, _TYPE_EDGE )

//----------------------------------------------------------------------------
// PhysxPolygonShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( Polygon, _TYPE_POLYGON )

_void PhysxPolygonShape::Set( const Vector3* vertices, _dword number )
{
	gDynamicPHI->SetPolygonShapeVertices( mShapeResource, vertices, number );
}

_void PhysxPolygonShape::SetAsBox( _float width, _float height )
{
	gDynamicPHI->SetPolygonShapeAsBox( mShapeResource, width, height );
}

_dword PhysxPolygonShape::GetVerticesNumber( ) const 
{
	return gDynamicPHI->GetPolygonShapeVerticesNumber( mShapeResource.GetPtr( ) );
}

Vector3 PhysxPolygonShape::GetVertexByIndex( _dword index ) const
{
	return gDynamicPHI->GetPolygonShapeVertexByIndex( mShapeResource.GetPtr( ), index );
}

//----------------------------------------------------------------------------
// PhysxPlaneShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( Plane, _TYPE_PLANE )

//----------------------------------------------------------------------------
// PhysxBoxShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( Box, _TYPE_BOX )

//----------------------------------------------------------------------------
// PhysxCylinderShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( Cylinder, _TYPE_CYLINDER )

//----------------------------------------------------------------------------
// PhysxCapsuleShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( Capsule, _TYPE_CAPSULE )

//----------------------------------------------------------------------------
// PhysxConeShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( Cone, _TYPE_CONE )

//----------------------------------------------------------------------------
// PhysxSphereShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( Sphere, _TYPE_SPHERE )

//----------------------------------------------------------------------------
// PhysxMultiSphereShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( MultiSphere, _TYPE_MULTI_SPHERE )

//----------------------------------------------------------------------------
// PhysxConvexHullShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( ConvexHull, _TYPE_CONVEX_HULL )

//----------------------------------------------------------------------------
// PhysxConvexTriangleMeshShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( ConvexTriangleMesh, _TYPE_CONVEX_TRIANGLE_MESH )

//----------------------------------------------------------------------------
// PhysxHeightFieldTerrainShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( HeightFieldTerrain, _TYPE_HEIGHT_FIELD_TERRAIN )

//----------------------------------------------------------------------------
// PhysxCompoundShape Implementation
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_IMPL( Compound, _TYPE_COMPOUND )

_dword PhysxCompoundShape::GetChildShapesNumber( ) const
{
	return mChildShapes.Number( );
}

IPhysxShapeRef PhysxCompoundShape::GetChildShapeByIndex( _dword index )
{
	return mChildShapes[ index ];
}

_ubool PhysxCompoundShape::AddChildShape( const Matrix4& transform, IPhysxShape* shape )
{
	if ( shape == _null )
		return _false;

	if ( gDynamicPHI->AddChildShapeOfCompoundShape( mShapeResource, transform, shape->GetShapeResource( ) ) == _false )
		return _false;

	mChildShapes.Append( shape );

	return _true;
}

_ubool PhysxCompoundShape::RemoveChildShape( IPhysxShape* shape )
{
	if ( shape == _null )
		return _false;

	if ( gDynamicPHI->RemoveChildShapeOfCompoundShape( mShapeResource, shape->GetShapeResource( ) ) == _false )
		return _false;

	mChildShapes.Remove( shape );

	return _true;
}