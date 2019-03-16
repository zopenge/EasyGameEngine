//! @file     Box2DFixture.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Box2DFixture
//----------------------------------------------------------------------------

class Box2DFixture : public FixturePHI
{
private:
	//!	The fixture resource
	b2Fixture*	mResource;

	//!	The body resource
	b2Body*		mBody;

public:
	Box2DFixture( b2Fixture* fixture, b2Body* body );
	virtual ~Box2DFixture( );

public:
	//!	Get the fixture resource.
	EGE_GETP_ACCESSOR( b2Fixture, Resource )
};

}