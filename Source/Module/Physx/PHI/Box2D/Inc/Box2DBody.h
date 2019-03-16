//! @file     Box2DBody.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Box2DBody
//----------------------------------------------------------------------------

class Box2DBody : public BodyPHI
{
private:
	//!	The body resource
	b2Body*		mResource;
	//!	The scene/world resource
	b2World*	mWorld;

public:
	Box2DBody( b2Body* body, b2World* world );
	virtual ~Box2DBody( );

public:
	//!	Get the body resource.
	EGE_GETP_ACCESSOR( b2Body, Resource )
};

}