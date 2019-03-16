//! @file     Box2DScene.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Box2DScene
//----------------------------------------------------------------------------

class Box2DScene : public ScenePHI
{
private:
	//!	The box2D world resource
	b2World*	mResource;

public:
	Box2DScene( b2World* resource );
	virtual ~Box2DScene( );

public:
	//!	Get the world resource.
	EGE_GETP_ACCESSOR( b2World, Resource )
};

}