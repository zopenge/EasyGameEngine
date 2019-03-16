//! @file     ProjectileObject.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ProjectileObject
//----------------------------------------------------------------------------

class ProjectileObject : public INTERFACE_OBJECT_IMPL( IProjectileObject )
{
private:
	//!	The start position
	Vector3 mStartPosition;
	//!	The start direction
	Vector3 mStartDirection;

	//!	The current position
	Vector3 mCurrentPosition;
	//!	The current direction
	Vector3 mCurrentDirection;
	//!	The last position
	Vector3 mLastPosition;

	//!	The max height
	_float	mMaxHeight;

	//!	The current tickcount
	_dword	mCurrentTickcount;
	//!	The duration in milliseconds
	_dword	mDuration;

public:
	ProjectileObject( );
	virtual ~ProjectileObject( );

public:
	//!	Initialize by speed.
	_ubool InitBySpeed( const Vector3& position, const Vector3& direction, const Vector3& target, _float speed, _float height_rate );
	//!	Initialize by duration.
	_ubool InitByDuration( const Vector3& position, const Vector3& direction, const Vector3& target, _dword duration, _float height_rate );

// IProjectileObject Interface
public:
	virtual Vector3 GetCurrentDirection( ) const override;
	virtual Vector3 GetCurrentPosition( ) const override;

	virtual _dword 	GetDuration( ) const override;
	virtual _float 	GetLastSpeed( ) const override;

	virtual _float 	Update( _dword elapse, const Vector3& target ) override;
};

}