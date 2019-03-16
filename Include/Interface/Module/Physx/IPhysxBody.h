//! @file     IPhysxBody.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IPhysxBody
//----------------------------------------------------------------------------

class IPhysxBody : public IObject
{
public:
	//! Get the body PHI resource.
	//!	@param		none.
	//! @return		The body PHI resource.
	virtual BodyPHIRef GetBodyRes( ) PURE;
};

//----------------------------------------------------------------------------
// IPhysxSoftBody
//----------------------------------------------------------------------------

class IPhysxSoftBody : public IPhysxBody
{
public:
};

//----------------------------------------------------------------------------
// IPhysxRigidBody
//----------------------------------------------------------------------------

class IPhysxRigidBody : public IPhysxBody
{
public:
	/// Get the body center position for the body's origin.
	//!	@param		none.
	//!	@return		The center position.
	virtual Vector3 GetCenter( ) const PURE;
	/// Get the body transform for the body's origin.
	//!	@param		none.
	//! @return		The world transform of the body's origin.
	virtual Matrix4 GetTransform( ) const PURE;

	//!	Set the spring or bounciness.
	//!	@param		restitution	The restitution value.
	//!	@return		none.
	virtual _void SetRestitution( _float restitution ) PURE;
	//!	Get the spring or bounciness.
	//!	@param		none.
	//!	@return		The restitution value.
	virtual _float GetRestitution( ) const PURE;

	//!	Set the damping of linear and angular.
	//!	@param		lin_damping	The damping of linear.
	//!	@param		ang_damping	The damping of angular.
	//!	@return		none.
	virtual _void SetDamping( _float lin_damping, _float ang_damping ) PURE;

	//!	Set the linear movement to specific axis.
	//!	@param		factor		The factor value.
	//!	@return		none.
	virtual _void SetLinearFactor( const Vector3& factor ) PURE;
	//!	Get the linear movement to specific axis.
	//!	@param		none.
	//!	@return		The factor value.
	virtual Vector3 GetLinearFactor( ) const PURE;
		
	//!	Set the angular movement to specific axis.
	//!	@param		factor		The factor value.
	//!	@return		none.
	virtual _void SetAngularFactor( const Vector3& factor ) PURE;
	//!	Get the angular movement to specific axis.
	//!	@param		none.
	//!	@return		The factor value.
	virtual Vector3 GetAngularFactor( ) const PURE;

	//!	Apply linear force.
	//!	@param		force		The force vector, usually in Newtons (N).
	//!	@return		none.
	virtual _void ApplyCentralImpulse( const Vector3& force ) PURE;
	//!	Apply angular force.
	//!	@param		force		The force vector, usually in Newtons (N).
	//!	@return		none.
	virtual _void ApplyTorqueImpulse( const Vector3& force ) PURE;
};

}