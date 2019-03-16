//! @file     Box2DShape.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// Box2DDrv-Shape Implementation
//----------------------------------------------------------------------------

ShapePHIPassRef Box2DDrv::CloneShape( const ShapePHI* shape )
{
	switch ( shape->GetResourceType( ) )
	{
		case _PRT_CHAIN_SHAPE:
		{
			DYNAMIC_CAST_BOX2D_RESOURCE( ChainShape, shape ); 
			
			Box2DChainShape* chain_shape = new Box2DChainShape( );
			chain_shape->GetShapeResource( ) = box2d_shape->GetShapeResource( );

			return chain_shape;
		}
		break;

		case _PRT_CIRCLE_SHAPE:
		{
			DYNAMIC_CAST_BOX2D_RESOURCE( CircleShape, shape ); 

			Box2DCircleShape* circle_shape = new Box2DCircleShape( );
			circle_shape->GetShapeResource( ) = box2d_shape->GetShapeResource( );

			return circle_shape;
		}
		break;

		case _PRT_EDGE_SHAPE:
		{
			DYNAMIC_CAST_BOX2D_RESOURCE( EdgeShape, shape ); 

			Box2DEdgeShape* edge_shape = new Box2DEdgeShape( );
			edge_shape->GetShapeResource( ) = box2d_shape->GetShapeResource( );

			return edge_shape;
		}
		break;

		case _PRT_POLYGON_SHAPE:
		{
			DYNAMIC_CAST_BOX2D_RESOURCE( PolygonShape, shape ); 

			Box2DPolygonShape* polygon_shape = new Box2DPolygonShape( );
			polygon_shape->GetShapeResource( ) = box2d_shape->GetShapeResource( );

			return polygon_shape;
		}
		break;

		default:
			return _null;
	}
}

ChainShapePHIPassRef Box2DDrv::CreateChainShape( )
{
	return new Box2DChainShape( );
}

CircleShapePHIPassRef Box2DDrv::CreateCircleShape( )
{
	return new Box2DCircleShape( );
}

EdgeShapePHIPassRef Box2DDrv::CreateEdgeShape( )
{
	return new Box2DEdgeShape( );
}

PolygonShapePHIPassRef Box2DDrv::CreatePolygonShape( )
{
	return new Box2DPolygonShape( );
}

_void Box2DDrv::SetPolygonShapeVertices( PolygonShapePHI* shape, const Vector3* vertices, _dword number )
{
	if ( shape == _null || vertices == _null || number == 0 )
		return;

	DYNAMIC_CAST_BOX2D_RESOURCE( PolygonShape, shape );

	// Build vertices buffer
	const _dword cMaxNumber = 1024; FixedArray< b2Vec2, cMaxNumber > vector_2d_array;
	for ( _dword i = 0; i < number; i ++ )
		vector_2d_array.Append( b2Vec2( vertices[i].x, vertices[i].y ) );

	// Update the vertices of shape
	box2d_shape->GetShapeResource( ).Set( vector_2d_array.GetBuffer( ), number );
}

_void Box2DDrv::SetPolygonShapeAsBox( PolygonShapePHI* shape, _float width, _float height )
{
	if ( shape == _null )
		return;

	DYNAMIC_CAST_BOX2D_RESOURCE( PolygonShape, shape );

	// Update the vertices of shape
	box2d_shape->GetShapeResource( ).SetAsBox( width, height );
}

_dword Box2DDrv::GetPolygonShapeVerticesNumber( PolygonShapePHI* shape )
{
	if ( shape == _null )
		return 0;

	DYNAMIC_CAST_BOX2D_RESOURCE( PolygonShape, shape );

	// Get the number of vertices
	return box2d_shape->GetShapeResource( ).m_vertexCount;
}

Vector3 Box2DDrv::GetPolygonShapeVertexByIndex( PolygonShapePHI* shape, _dword index )
{
	if ( shape == _null )
		return Vector3::cOrigin;

	DYNAMIC_CAST_BOX2D_RESOURCE( PolygonShape, shape );

	if ( index >= (_dword) box2d_shape->GetShapeResource( ).m_vertexCount )
		return Vector3::cOrigin;

	const b2Vec2& vector = box2d_shape->GetShapeResource( ).m_vertices[ index ];

	return Vector3( vector.x, vector.y, 0.0f );
}

PlaneShapePHIPassRef Box2DDrv::CreatePlaneShape( const Vector3& normal, _float constant )
{
	return _null;
}

BoxShapePHIPassRef Box2DDrv::CreateBoxShape( const Vector3& half_extents )
{
	return _null;
}

CylinderShapePHIPassRef Box2DDrv::CreateCylinderShape( const Vector3& half_extents )
{
	return _null;
}

CapsuleShapePHIPassRef Box2DDrv::CreateCapsuleShape( _float radius, _float height )
{
	return _null;
}

ConeShapePHIPassRef Box2DDrv::CreateConeShape( _float radius, _float height )
{
	return _null;
}

_void Box2DDrv::SetCircleShapeRadius( CircleShapePHI* shape, _float radius )
{
	DYNAMIC_CAST_BOX2D_RESOURCE( CircleShape, shape );
	if ( box2d_shape != _null )
		box2d_shape->GetShapeResource( ).m_radius = radius;
}

_float Box2DDrv::GetCircleShapeRadius( CircleShapePHI* shape )
{
	DYNAMIC_CAST_BOX2D_RESOURCE( CircleShape, shape );
	if ( box2d_shape == _null )
		return 0.0f;

	return box2d_shape->GetShapeResource( ).m_radius;
}

SphereShapePHIPassRef Box2DDrv::CreateSphereShape( _float radius )
{
	return _null;
}

MultiSphereShapePHIPassRef Box2DDrv::CreateMultiSphereShape( const Vector3* pos_list, const _float* radius_list, _dword number )
{
	return _null;
}

ConvexHullShapePHIPassRef Box2DDrv::CreateConvexHullShape( const Vector3* pos_list, _dword number )
{
	return _null;
}

ConvexTriangleMeshShapePHIPassRef Box2DDrv::CreateConvexTriangleMeshShape( const StridingMeshPHI* striding_mesh )
{
	return _null;
}

ConvexTriangleMeshShapePHIPassRef Box2DDrv::CreateBvhTriangleMeshShape( const StridingMeshPHI* striding_mesh )
{
	return _null;
}

HeightFieldTerrainShapePHIPassRef Box2DDrv::CreateHeightFieldTerrainShape( _dword grid_x, _dword grid_y, const _void* field_data, _float height_scale, _float min_height, _float max_height, _PHYSX_UP_AXIS_TYPE up_axis, _PHYSX_DATA_TYPE data_type, _ubool flip_quad_edges )
{
	return _null;
}

CompoundShapePHIPassRef Box2DDrv::CreateCompoundShape( )
{
	return _null;
}

_dword Box2DDrv::GetChildShapeNumberOfCompoundShape( const CompoundShapePHI* compound_shape )
{
	return 0;
}

ShapePHIRef Box2DDrv::GetChildShapeOfCompoundShape( CompoundShapePHI* compound_shape, _dword index )
{
	return _null;
}

_ubool Box2DDrv::AddChildShapeOfCompoundShape( CompoundShapePHI* compound_shape, const Matrix4& transform, ShapePHI* shape )
{
	return _false;
}

_ubool Box2DDrv::RemoveChildShapeOfCompoundShape( CompoundShapePHI* compound_shape, ShapePHI* shape )
{
	return _false;
}

//----------------------------------------------------------------------------
// Box2DChainShape Implementation
//----------------------------------------------------------------------------

Box2DChainShape::Box2DChainShape( )
{
}

Box2DChainShape::~Box2DChainShape( )
{
}

//----------------------------------------------------------------------------
// Box2DCircleShape Implementation
//----------------------------------------------------------------------------

Box2DCircleShape::Box2DCircleShape( )
{
}

Box2DCircleShape::~Box2DCircleShape( )
{
}

//----------------------------------------------------------------------------
// Box2DEdgeShape Implementation
//----------------------------------------------------------------------------

Box2DEdgeShape::Box2DEdgeShape( )
{
}

Box2DEdgeShape::~Box2DEdgeShape( )
{
}

//----------------------------------------------------------------------------
// Box2DPolygonShape Implementation
//----------------------------------------------------------------------------

Box2DPolygonShape::Box2DPolygonShape( )
{
}

Box2DPolygonShape::~Box2DPolygonShape( )
{
}