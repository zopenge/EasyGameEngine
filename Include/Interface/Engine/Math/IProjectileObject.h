//! @file     IProjectileObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IProjectileObject
//----------------------------------------------------------------------------

class IProjectileObject : public IObject
{
public:
	//!	Get the current direction.
	//!	@param		none.
	//!	@return		The current direction.
	virtual Vector3 GetCurrentDirection( ) const PURE;
	//!	Get the current position.
	//!	@param		none.
	//!	@return		The current position.
	virtual Vector3 GetCurrentPosition( ) const PURE;

	//!	Get the duration in milliseconds.
	//!	@param		none.
	//!	@return		The duration in milliseconds.
	virtual _dword GetDuration( ) const PURE;
	//!	Get the last speed per-second.
	//!	@param		none.
	//!	@return		The last speed per-second.
	virtual _float GetLastSpeed( ) const PURE;

	//!	Update the current position and direction by the target position.
	//! @param		elapse		The millisecond time of the update interval.
	//!	@param		target		The target position.
	//!	@return		The progression to target position in percentage, 1.0 indicates reach the target position.
	virtual _float Update( _dword elapse, const Vector3& target ) PURE;
};

}