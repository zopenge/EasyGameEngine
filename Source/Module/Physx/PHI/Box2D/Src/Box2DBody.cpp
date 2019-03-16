//! @file     Box2DBody.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// Helper Functions
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Box2DDrv-Body Implementation
//----------------------------------------------------------------------------

RigidBodyPHIPassRef Box2DDrv::CreateRigidBody( ScenePHI* scene, _float mass, const Matrix4& start_transform, const Matrix4& center_of_mass_offset, const Vector3& local_inertia, ShapePHI* shape )
{
	DYNAMIC_CAST_BOX2D_RESOURCE( Scene, scene );

	return _null;
	//// Initialize body definition
	//b2BodyDef body_def;
	//body_def.type		= TranslateBodyType( body.mType );
	//body_def.position	= b2Vec2( body.mPosition.x, body.mPosition.y );

	//// Create body
	//b2Body* box2d_body = box2d_scene->GetResource( )->CreateBody( &body_def );
	//if ( box2d_body == _null )
	//	return _null;

	//return new Box2DBody( box2d_body, box2d_scene->GetResource( ) );
}

_void Box2DDrv::RemoveBody( ScenePHI* scene, BodyPHI* body )
{

}

Vector3 Box2DDrv::GetBodyCenter( const BodyPHI* body )
{
	DYNAMIC_CAST_BOX2D_RESOURCE( Body, body );

	const b2Vec2& position = box2d_body->GetResource( )->GetPosition( );

	return Vector3( position.x, position.y, 0.0f );
}

Matrix4 Box2DDrv::GetBodyTransform( const BodyPHI* body )
{
	DYNAMIC_CAST_BOX2D_RESOURCE( Body, body );

	const b2Transform& matrx2 = box2d_body->GetResource( )->GetTransform( );

	return Matrix4( ).Translation( matrx2.p.x, matrx2.p.y, 0.0f ) * Matrix2( ).Rotation( matrx2.q.GetAngle( ) );
}

_void Box2DDrv::SetBodyRestitution( BodyPHI* body, _float restitution )
{
}

_float Box2DDrv::GetBodyRestitution( const BodyPHI* body )
{
	return 0.0f;
}

_void Box2DDrv::SetBodyDamping( BodyPHI* body, _float lin_damping, _float ang_damping )
{
}

_void Box2DDrv::SetBodyLinearFactor( BodyPHI* body, const Vector3& factor )
{
}

Vector3 Box2DDrv::GetBodyLinearFactor( const BodyPHI* body )
{
	return Vector3::cOrigin;
}

_void Box2DDrv::SetBodyAngularFactor( BodyPHI* body, const Vector3& factor )
{
}

Vector3	Box2DDrv::GetBodyAngularFactor( const BodyPHI* body )
{
	return Vector3::cOrigin;
}

_void Box2DDrv::ApplyBodyCentralImpulse( BodyPHI* body, const Vector3& force )
{
	DYNAMIC_CAST_BOX2D_RESOURCE( Body, body );

	box2d_body->GetResource( )->ApplyForceToCenter( b2Vec2( force.x, force.y ) );
}

_void Box2DDrv::ApplyBodyTorqueImpulse( BodyPHI* body, const Vector3& force )
{
	DYNAMIC_CAST_BOX2D_RESOURCE( Body, body );

	box2d_body->GetResource( )->ApplyTorque( force.z );
}

//----------------------------------------------------------------------------
// Box2DBody Implementation
//----------------------------------------------------------------------------

Box2DBody::Box2DBody( b2Body* body, b2World* world ) : mResource( body ), mWorld( world )
{
}

Box2DBody::~Box2DBody( )
{
	// Destroy body from scene/world
	if ( mResource != _null && mWorld != _null )
		mWorld->DestroyBody( mResource );
}