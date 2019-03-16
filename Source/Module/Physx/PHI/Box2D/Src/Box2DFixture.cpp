//! @file     Box2DFixture.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// Helper Functions
//----------------------------------------------------------------------------

static const b2Shape* TranslateShape( const ShapePHI* shape )
{
	if ( shape == _null )
		return _null;

	switch ( shape->GetResourceType( ) )
	{
		case _PRT_CHAIN_SHAPE:		{ DYNAMIC_CAST_BOX2D_RESOURCE( ChainShape, shape ); return &box2d_shape->GetShapeResource( ); }
		case _PRT_CIRCLE_SHAPE:		{ DYNAMIC_CAST_BOX2D_RESOURCE( CircleShape, shape ); return &box2d_shape->GetShapeResource( ); }
		case _PRT_EDGE_SHAPE:		{ DYNAMIC_CAST_BOX2D_RESOURCE( EdgeShape, shape ); return &box2d_shape->GetShapeResource( ); }
		case _PRT_POLYGON_SHAPE:	{ DYNAMIC_CAST_BOX2D_RESOURCE( PolygonShape, shape ); return &box2d_shape->GetShapeResource( ); }
		default:
			return _null;
	}
}

//----------------------------------------------------------------------------
// Box2DDrv-Fixture Implementation
//----------------------------------------------------------------------------

FixturePHIPassRef Box2DDrv::CreateFixture( BodyPHI* body, const PhysxFixtureDef& fixture, ShapePHI* shape )
{
	DYNAMIC_CAST_BOX2D_RESOURCE( Body, body );
	if ( box2d_body == _null )
		return _null;

	// Get the box2d shape
	const b2Shape* box2d_shape = TranslateShape( shape );
	if ( box2d_shape == _null )
		return _null;

	// Initialize fixture definition
	b2FixtureDef fixture_def;
	fixture_def.shape		= box2d_shape;
	fixture_def.friction	= fixture.mFriction;
	fixture_def.restitution	= fixture.mRestitution;
	fixture_def.density		= fixture.mDensity;
	fixture_def.isSensor	= EGE_BOOLEAN( fixture.mIsSensor );

	// Create fixture
	b2Fixture* box2d_fixture = box2d_body->GetResource( )->CreateFixture( &fixture_def );
	if ( box2d_fixture == _null )
		return _null;

	return new Box2DFixture( box2d_fixture, box2d_body->GetResource( ) );
}

_void Box2DDrv::SetFixtureDensity( FixturePHI* fixture, _float density )
{
	b2Fixture* box2d_fixture = GET_PHI_RESOURCE( Box2DFixture, fixture );
	if ( box2d_fixture != _null )
		box2d_fixture->SetDensity( density );
}

_float Box2DDrv::GetFixtureDensity( FixturePHI* fixture )
{
	b2Fixture* box2d_fixture = GET_PHI_RESOURCE( Box2DFixture, fixture );
	if ( box2d_fixture == _null )
		return 0.0f;

	return box2d_fixture->GetDensity( );
}

_void Box2DDrv::SetFixtureFriction( FixturePHI* fixture, _float friction )
{
	b2Fixture* box2d_fixture = GET_PHI_RESOURCE( Box2DFixture, fixture );
	if ( box2d_fixture != _null )
		box2d_fixture->SetFriction( friction );
}

_float Box2DDrv::GetFixtureFriction( FixturePHI* fixture )
{
	b2Fixture* box2d_fixture = GET_PHI_RESOURCE( Box2DFixture, fixture );
	if ( box2d_fixture == _null )
		return 0.0f;

	return box2d_fixture->GetFriction( );
}

_void Box2DDrv::SetFixtureRestitution( FixturePHI* fixture, _float restitution )
{
	b2Fixture* box2d_fixture = GET_PHI_RESOURCE( Box2DFixture, fixture );
	if ( box2d_fixture != _null )
		box2d_fixture->SetRestitution( restitution );
}

_float Box2DDrv::GetFixtureRestitution( FixturePHI* fixture )
{
	b2Fixture* box2d_fixture = GET_PHI_RESOURCE( Box2DFixture, fixture );
	if ( box2d_fixture == _null )
		return 0.0f;

	return box2d_fixture->GetRestitution( );
}

//----------------------------------------------------------------------------
// Box2DFixture Implementation
//----------------------------------------------------------------------------

Box2DFixture::Box2DFixture( b2Fixture* fixture, b2Body* body ) : mResource( fixture ), mBody( body )
{
}

Box2DFixture::~Box2DFixture( )
{
	// Destroy body from body
	if ( mResource != _null && mBody != _null )
		mBody->DestroyFixture( mResource );
}