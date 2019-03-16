//! @file     IPhysxShape.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IPhysxShape
//----------------------------------------------------------------------------

class IPhysxShape : public IObject
{
public:
	//!	The shape type
	enum _TYPE
	{
		_TYPE_UNKNOWN,
		_TYPE_CHAIN,
		_TYPE_CIRCLE,
		_TYPE_EDGE,
		_TYPE_POLYGON,

		_TYPE_PLANE,
		_TYPE_BOX,
		_TYPE_CYLINDER,
		_TYPE_CAPSULE,
		_TYPE_CONE,
		_TYPE_SPHERE,
		_TYPE_MULTI_SPHERE,
		_TYPE_CONVEX_HULL,
		_TYPE_CONVEX_TRIANGLE_MESH,
		_TYPE_HEIGHT_FIELD_TERRAIN,
		_TYPE_COMPOUND,
	};

public:
	//!	Get the shape type.
	//!	@param		none.
	//!	@return		The shape type.
	virtual _TYPE GetType( ) const PURE;
	//!	Get the shape resource.
	//!	@param		none.
	//!	@return		The shape type.
	virtual ShapePHIRef GetShapeResource( ) PURE;
};

//----------------------------------------------------------------------------
// IPhysxChainShape
//----------------------------------------------------------------------------

class IPhysxChainShape : public IPhysxShape
{
public:
};

//----------------------------------------------------------------------------
// IPhysxCircleShape
//----------------------------------------------------------------------------

class IPhysxCircleShape : public IPhysxShape
{
public:
	//!	Set the radius.
	//!	@param		radius	The radius.
	//!	@return		none.
	virtual _void SetRadius( _float radius ) PURE;
	//!	Get the radius.
	//!	@param		none.
	//!	@return		The radius.
	virtual _float GetRadius( ) const PURE;
};

//----------------------------------------------------------------------------
// IPhysxEdgeShape
//----------------------------------------------------------------------------

class IPhysxEdgeShape : public IPhysxShape
{
public:
};

//----------------------------------------------------------------------------
// IPhysxPolygonShape
//----------------------------------------------------------------------------

class IPhysxPolygonShape : public IPhysxShape
{
public:
	//!	The max vertices number
	enum { _MAX_VERTICES_NUMBER = 16 };

public:
	//! Copy vertices. 
	//!	@param		vertices	The vertices.
	//!	@param		number		The number of vertices.
	//!	@return		none.
	virtual _void Set( const Vector3* vertices, _dword number ) PURE;
	//! Build vertices to represent an axis-aligned 2D box.
	//! @param		width		The width of 2D box.
	//! @param		height		The height of 2D box.
	//!	@return		none.
	virtual _void SetAsBox( _float width, _float height ) PURE;

	//! Get vertices number. 
	//!	@param		none.
	//!	@return		The number of vertices.
	virtual _dword GetVerticesNumber( ) const PURE;
	//! Get vertex by index. 
	//!	@param		index		The index of vertices.
	//!	@return		The vertex.
	virtual Vector3 GetVertexByIndex( _dword index ) const PURE;
};

//----------------------------------------------------------------------------
// IPhysxPlaneShape
//----------------------------------------------------------------------------

class IPhysxPlaneShape : public IPhysxShape
{
public:
};

//----------------------------------------------------------------------------
// IPhysxBoxShape
//----------------------------------------------------------------------------

class IPhysxBoxShape : public IPhysxShape
{
public:
};

//----------------------------------------------------------------------------
// IPhysxCylinderShape
//----------------------------------------------------------------------------

class IPhysxCylinderShape : public IPhysxShape
{
public:
};

//----------------------------------------------------------------------------
// IPhysxCapsuleShape
//----------------------------------------------------------------------------

class IPhysxCapsuleShape : public IPhysxShape
{
public:
};

//----------------------------------------------------------------------------
// IPhysxConeShape
//----------------------------------------------------------------------------

class IPhysxConeShape : public IPhysxShape
{
public:
};

//----------------------------------------------------------------------------
// IPhysxSphereShape
//----------------------------------------------------------------------------

class IPhysxSphereShape : public IPhysxShape
{
public:
};

//----------------------------------------------------------------------------
// IPhysxMultiSphereShape
//----------------------------------------------------------------------------

class IPhysxMultiSphereShape : public IPhysxShape
{
public:
};

//----------------------------------------------------------------------------
// IPhysxConvexHullShape
//----------------------------------------------------------------------------

class IPhysxConvexHullShape : public IPhysxShape
{
public:
};

//----------------------------------------------------------------------------
// IPhysxConvexTriangleMeshShape
//----------------------------------------------------------------------------

class IPhysxConvexTriangleMeshShape : public IPhysxShape
{
public:
};

//----------------------------------------------------------------------------
// IPhysxHeightFieldTerrainShape
//----------------------------------------------------------------------------

class IPhysxHeightFieldTerrainShape : public IPhysxShape
{
public:
};

//----------------------------------------------------------------------------
// IPhysxCompoundShape
//----------------------------------------------------------------------------

class IPhysxCompoundShape : public IPhysxShape
{
public:
	//!	Get the child shapes number.
	//!	@param		none.
	//!	@return		The number of child shapes.
	virtual _dword GetChildShapesNumber( ) const PURE;
	//!	Get the child shape by index.
	//!	@param		index		The child index.
	//!	@return		The shape interface.
	virtual IPhysxShapeRef GetChildShapeByIndex( _dword index ) PURE;
	//!	Add the child shape.
	//!	@param		transform	The local transform.
	//!	@param		shape		The child shape.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool AddChildShape( const Matrix4& transform, IPhysxShape* shape ) PURE;
	//!	Remove the child shape.
	//!	@param		shape		The child shape.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RemoveChildShape( IPhysxShape* shape ) PURE;
};

}