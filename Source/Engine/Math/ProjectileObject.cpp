//! @file     ProjectileObject.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ProjectileObject Implementation
//----------------------------------------------------------------------------

ProjectileObject::ProjectileObject( )
{
	mStartPosition		= Vector3::cOrigin;
	mStartDirection		= Vector3::cOrigin;

	mCurrentPosition	= Vector3::cOrigin;
	mCurrentDirection	= Vector3::cOrigin;
	mLastPosition		= Vector3::cOrigin;

	mMaxHeight			= 0.0f;

	mCurrentTickcount	= 0;
	mDuration			= 0;
}

ProjectileObject::~ProjectileObject( )
{

}

_ubool ProjectileObject::InitBySpeed( const Vector3& position, const Vector3& direction, const Vector3& target, _float speed, _float height_rate )
{
	// Get the distance to target
	_float distance	= ( position - target ).Magnitude( );

	return InitByDuration( position, direction, target, _dword( distance / ( 0.1f * speed ) ), height_rate );
}

_ubool ProjectileObject::InitByDuration( const Vector3& position, const Vector3& direction, const Vector3& target, _dword duration, _float height_rate )
{
	// Initialize start position and direction
	mStartPosition		= position;
	mStartDirection		= direction;
	mStartDirection.Normalize( );

	mCurrentPosition	= position;
	mCurrentDirection	= ( target - position ).Normalize( );
	mLastPosition		= position;

	// Get the distance to target
	_float distance		= ( target - position ).Magnitude( );

	// Set the max height
	mMaxHeight			= distance * 0.1f * height_rate;

	// Initialize the timer
	mCurrentTickcount	= 0;
	mDuration			= duration;

	return _true;
}

Vector3 ProjectileObject::GetCurrentDirection( ) const
{
	return mCurrentDirection;
}

Vector3 ProjectileObject::GetCurrentPosition( ) const
{
	return mCurrentPosition;
}

_dword ProjectileObject::GetDuration( ) const
{
	return mDuration;
}

_float ProjectileObject::GetLastSpeed( ) const
{
	Vector2 current = Vector2( mCurrentPosition.x, mCurrentPosition.y );
	Vector2 start	= Vector2( mStartPosition.x, mStartPosition.y );

	_dword time = mCurrentTickcount;
	if ( time > mDuration )
		time = mDuration;

	return Vector2( current - start ).Magnitude( ) / _float( time );
}

_float ProjectileObject::Update( _dword elapse, const Vector3& target )
{
	// Get the percentage from start position to target
	_float percentage = EGE_RATIO( mCurrentTickcount, mDuration );
	if ( percentage >= 1.0f )
		return 1.0f;

	// Update the last position
	mLastPosition = mCurrentPosition;

	// Update the direction
	mCurrentDirection = ( target - mCurrentPosition ).Normalize( );

	// Update the timer
	mCurrentTickcount += elapse;
	if ( mCurrentTickcount >= mDuration )
		mCurrentTickcount = mDuration;

	// Finish fly
	if ( mCurrentTickcount == mDuration )
	{
		mCurrentPosition = target;
	}
	// Flying
	else
	{
		// Update the current position
		Vector3 direction				= target - mStartPosition;
		Vector3 normalized_direction	= ( target - mStartPosition ).Normalize( );
		mCurrentPosition				= mStartPosition + normalized_direction * direction.Magnitude( ) * percentage;

		// Update the height
		_float height_rate = Math::Sin( Math::cPi * percentage );
		mCurrentPosition.z += height_rate * mMaxHeight;
	}

	return percentage;
}