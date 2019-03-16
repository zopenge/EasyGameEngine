//! @file     NvPhysxShape.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NvPhysxChainShape
//----------------------------------------------------------------------------

class NvPhysxChainShape : public ChainShapePHI
{
private:

public:
	NvPhysxChainShape( );
	virtual ~NvPhysxChainShape( );

public:
};

//----------------------------------------------------------------------------
// NvPhysxCircleShape
//----------------------------------------------------------------------------

class NvPhysxCircleShape : public CircleShapePHI
{
private:

public:
	NvPhysxCircleShape( );
	virtual ~NvPhysxCircleShape( );

public:
};

//----------------------------------------------------------------------------
// NvPhysxEdgeShape
//----------------------------------------------------------------------------

class NvPhysxEdgeShape : public EdgeShapePHI
{
private:

public:
	NvPhysxEdgeShape( );
	virtual ~NvPhysxEdgeShape( );

public:
};

//----------------------------------------------------------------------------
// NvPhysxPolygonShape
//----------------------------------------------------------------------------

class NvPhysxPolygonShape : public PolygonShapePHI
{
private:

public:
	NvPhysxPolygonShape( );
	virtual ~NvPhysxPolygonShape( );

public:
};

}