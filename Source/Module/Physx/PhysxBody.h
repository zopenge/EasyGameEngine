//! @file     PhysxBody.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PhysxBody
//----------------------------------------------------------------------------

template< typename BodyResType, typename Type >
class TPhysxBody : public INTERFACE_OBJECT_IMPL( Type )
{
protected:
	//!	The body resource
	RefPtr< BodyResType >	mBodyRes;

protected:
	TPhysxBody( BodyResType* body )
	{
		mBodyRes = body;
	}
	virtual ~TPhysxBody( )
	{

	}

// IPhysxRigidBody Interface
public:
	virtual BodyPHIRef GetBodyRes( )
	{
		return mBodyRes.template cast_static< BodyPHI >( );
	}
};

//----------------------------------------------------------------------------
// PhysxSoftBody
//----------------------------------------------------------------------------

class PhysxSoftBody : public TPhysxBody< SoftBodyPHI, IPhysxSoftBody >
{
private:
	typedef TPhysxBody< SoftBodyPHI, IPhysxSoftBody > BaseClass;

private:

public:
	PhysxSoftBody( SoftBodyPHI* body );
	virtual ~PhysxSoftBody( );

// IPhysxSoftBody Interface
public:
};

//----------------------------------------------------------------------------
// PhysxRigidBody
//----------------------------------------------------------------------------

class PhysxRigidBody : public TPhysxBody< RigidBodyPHI, IPhysxRigidBody >
{
private:
	typedef TPhysxBody< RigidBodyPHI, IPhysxRigidBody > BaseClass;

private:
	//!	The shape
	IPhysxShapeRef	mShape;

public:
	PhysxRigidBody( RigidBodyPHI* body, IPhysxShape* shape );
	virtual ~PhysxRigidBody( );

// IPhysxRigidBody Interface
public:
	virtual Vector3	GetCenter( ) const override;
	virtual Matrix4	GetTransform( ) const override;

	virtual _void	SetRestitution( _float restitution ) override;
	virtual _float	GetRestitution( ) const override;

	virtual _void	SetDamping( _float lin_damping, _float ang_damping ) override;

	virtual _void	SetLinearFactor( const Vector3& factor ) override;
	virtual Vector3	GetLinearFactor( ) const override;

	virtual _void	SetAngularFactor( const Vector3& factor ) override;
	virtual Vector3	GetAngularFactor( ) const override;

	virtual _void	ApplyCentralImpulse( const Vector3& force ) override;
	virtual _void	ApplyTorqueImpulse( const Vector3& force ) override;
};

//----------------------------------------------------------------------------
// PhysxRigidBody Implementation
//----------------------------------------------------------------------------

}