//! @file     BulletBody.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TBulletBody
//----------------------------------------------------------------------------

template< typename Type, typename BodyResourceType >
class TBulletBody : public Type
{
protected:
	//!	The body resource
	BodyResourceType*	mBTBody;

protected:
	TBulletBody( BodyResourceType* body ) 
	{
		EGE_ASSERT( body != _null ); 
		
		mBTBody			= body; 
	}
	virtual ~TBulletBody( )
	{
		EGE_DELETE( mBTBody ); 
	}

public:
	//!	Get the body resource
	EGE_GETR_ACCESSOR( BodyResourceType*, BTBody )
};

//----------------------------------------------------------------------------
// BulletSoftBody
//----------------------------------------------------------------------------

class BulletSoftBody : public TBulletBody< SoftBodyPHI, btSoftBody >
{
private:
	typedef TBulletBody< SoftBodyPHI, btSoftBody > BaseClass;

public:
	BulletSoftBody( btSoftBody* body );
	virtual ~BulletSoftBody( );
};

//----------------------------------------------------------------------------
// BulletRigidBody
//----------------------------------------------------------------------------

class BulletRigidBody : public TBulletBody< RigidBodyPHI, btRigidBody >
{
private:
	typedef TBulletBody< RigidBodyPHI, btRigidBody > BaseClass;

private:
	//!	The motion state
	btDefaultMotionState*	mBTMotionState;

public:
	BulletRigidBody( btDefaultMotionState* motion_state, btRigidBody* rigid_body );
	virtual ~BulletRigidBody( );
};

}