//! @file     PhysxChainShape.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

#define PHYSX_SHAPE_CLASS_DECL_BEGIN( x ) \
class Physx##x##Shape : public TPhysxShape< Physx##x##Shape, x##ShapePHI, IPhysx##x##Shape > \
{ \
private: \
	typedef TPhysxShape< Physx##x##Shape, x##ShapePHI, IPhysx##x##Shape > BaseClass; \
public: \
	Physx##x##Shape( x##ShapePHI* shape ); \
	virtual ~Physx##x##Shape( );
#define PHYSX_SHAPE_CLASS_DECL_END( ) \
};
#define PHYSX_SHAPE_CLASS_IMPL( x, type ) \
Physx##x##Shape::Physx##x##Shape( x##ShapePHI* shape ) : BaseClass( type, shape ) \
{ \
} \
Physx##x##Shape::~Physx##x##Shape( ) \
{ \
}

//----------------------------------------------------------------------------
// PhysxChainShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( Chain )
PHYSX_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// PhysxCircleShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( Circle )
// IPhysxCircleShape Interface
public:
	virtual _void	SetRadius( _float radius ) override;
	virtual _float	GetRadius( ) const override;
PHYSX_SHAPE_CLASS_DECL_END( )
	
//----------------------------------------------------------------------------
// PhysxEdgeShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( Edge )
PHYSX_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// PhysxPolygonShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( Polygon )
// IPhysxPolygonShape Interface
public:
	virtual _void	Set( const Vector3* vertices, _dword number ) override;
	virtual _void	SetAsBox( _float width, _float height ) override;

	virtual _dword	GetVerticesNumber( ) const override;
	virtual Vector3	GetVertexByIndex( _dword index ) const override;
PHYSX_SHAPE_CLASS_DECL_END( )
	
//----------------------------------------------------------------------------
// PhysxPlaneShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( Plane )
PHYSX_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// PhysxBoxShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( Box )
PHYSX_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// PhysxCylinderShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( Cylinder )
PHYSX_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// PhysxCapsuleShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( Capsule )
PHYSX_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// PhysxConeShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( Cone )
PHYSX_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// PhysxSphereShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( Sphere )
PHYSX_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// PhysxMultiSphereShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( MultiSphere )
PHYSX_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// PhysxConvexHullShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( ConvexHull )
PHYSX_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// PhysxConvexTriangleMeshShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( ConvexTriangleMesh )
PHYSX_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// PhysxHeightFieldTerrainShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( HeightFieldTerrain )
PHYSX_SHAPE_CLASS_DECL_END( )

//----------------------------------------------------------------------------
// PhysxCompoundShape
//----------------------------------------------------------------------------

PHYSX_SHAPE_CLASS_DECL_BEGIN( Compound )
private:
	typedef Array< IPhysxShapeRef > ShapeArray;

private:
	ShapeArray	mChildShapes;

// IPhysxCompoundShape Interface
public:
	virtual _dword			GetChildShapesNumber( ) const override;
	virtual IPhysxShapeRef	GetChildShapeByIndex( _dword index ) override;
	virtual _ubool			AddChildShape( const Matrix4& transform, IPhysxShape* shape ) override;
	virtual _ubool			RemoveChildShape( IPhysxShape* shape ) override;
PHYSX_SHAPE_CLASS_DECL_END( )

}