//! @file     IPhysxFixture.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IPhysxFixture
//----------------------------------------------------------------------------

class IPhysxFixture
{
public:
	//!	Get the shape type.
	//!	@param		none.
	//!	@return		The shape type.
	virtual IPhysxShape::_TYPE GetShapeType( ) const PURE;
	//!	Get the shape.
	//!	@param		none.
	//!	@return		The shape.
	virtual IPhysxShapeRef GetShape( ) const PURE;

	//! Set the density of this fixture.
	//!	@param		density		The density value.
	//!	@return		none.
	virtual _void SetDensity( _float density ) PURE;
	//! Get the density of this fixture.
	//!	@param		none.
	//!	@return		The density value.
	virtual _float GetDensity( ) const PURE;

	//! Set the coefficient of friction.
	//!	@param		friction	The friction value.
	//!	@return		none.
	virtual _void SetFriction( _float friction ) PURE;
	//! Get the coefficient of friction.
	//!	@param		none.
	//!	@return		The friction value.
	virtual _float GetFriction( ) const PURE;

	//! Set the coefficient of restitution.
	//!	@param		restitution	The restitution value.
	//!	@return		none.
	virtual _void SetRestitution( _float restitution ) PURE;
	//! Get the coefficient of restitution.
	//!	@param		none.
	//!	@return		The restitution value.
	virtual _float GetRestitution( ) const PURE;
};

}