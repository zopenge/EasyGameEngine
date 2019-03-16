//! @file     Box2DShape.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TBox2DShape
//----------------------------------------------------------------------------

template< typename Type, typename ShapeResourceType >
class TBox2DShape : public Type
{
protected:
	//!	The shape resource
	ShapeResourceType	mShapeResource;

protected:
	TBox2DShape( ) { }
	virtual ~TBox2DShape( ) { }

public:
	//!	Get the shape resource
	EGE_GETR_ACCESSOR( ShapeResourceType, ShapeResource )
};

//----------------------------------------------------------------------------
// Box2DChainShape
//----------------------------------------------------------------------------

class Box2DChainShape : public TBox2DShape< ChainShapePHI, b2ChainShape >
{
private:

public:
	Box2DChainShape( );
	virtual ~Box2DChainShape( );

public:
};

//----------------------------------------------------------------------------
// Box2DCircleShape
//----------------------------------------------------------------------------

class Box2DCircleShape : public TBox2DShape< CircleShapePHI, b2CircleShape >
{
private:

public:
	Box2DCircleShape( );
	virtual ~Box2DCircleShape( );

public:
};

//----------------------------------------------------------------------------
// Box2DEdgeShape
//----------------------------------------------------------------------------

class Box2DEdgeShape : public TBox2DShape< EdgeShapePHI, b2EdgeShape >
{
private:

public:
	Box2DEdgeShape( );
	virtual ~Box2DEdgeShape( );

public:
};

//----------------------------------------------------------------------------
// Box2DPolygonShape
//----------------------------------------------------------------------------

class Box2DPolygonShape : public TBox2DShape< PolygonShapePHI, b2PolygonShape >
{
private:

public:
	Box2DPolygonShape( );
	virtual ~Box2DPolygonShape( );
};

}