//! @file     EulerAngles.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// EulerAngles Implementation
//----------------------------------------------------------------------------

const EulerAngles EulerAngles::cIdentity( 0.0f, 0.0f, 0.0f );

EulerAngles& EulerAngles::Identity( )
{
	mHeading	= 0.0f;
	mPitch		= 0.0f;
	mBank		= 0.0f;

	return *this;
}

EulerAngles& EulerAngles::Canonize( )
{
	// First, wrap pitch range ¨Cpi ... pi.
	mPitch = Math::WrapPi( mPitch );

	// Check for "the back side" of the matrix pitch outside the canonical range of ¨Cpi/2 ... pi/2.
	if ( mPitch < Math::cPi * -0.5f )
	{
		mPitch		= -Math::cPi - mPitch;
		mHeading	= mHeading + Math::cPi;
		mBank		= mBank + Math::cPi;
	}
	else if ( mPitch > Math::cPi * 0.5f )
	{
		mPitch		= Math::cPi - mPitch;
		mHeading	= mHeading + Math::cPi;
		mBank		= mBank + Math::cPi;
	}

	// Check for the gimbel lock case (witha slight tolerance).
	if ( Math::Abs( mPitch ) > Math::cPi * 0.5f - Math::cFloatEpsilon )
	{
		// gimbel lock. Assign all rotation abthe vertical axis to heading.
		mHeading	= mHeading + mBank;
		mBank		= 0.0f;
	}
	else
	{
		// Not gimbel lock. Wrap the bank angle canonical range.
		mBank		= Math::WrapPi( mBank );
	}

	// Wrap heading canonical range.
	mHeading = Math::WrapPi( mHeading );

	return *this;
}

_void EulerAngles::GetAxisAndAngle( Vector3& axis, _float& angle ) const
{
	_float x = Math::Abs( mPitch	/ Math::c2Pi );
	_float y = Math::Abs( mHeading	/ Math::c2Pi );
	_float z = Math::Abs( mBank		/ Math::c2Pi );

	if ( z < Math::cFloatEpsilon && y < Math::cFloatEpsilon )
	{
		axis	= Vector3::cYAxis;
		angle	= mPitch;
	}
	else if ( x < Math::cFloatEpsilon && z < Math::cFloatEpsilon )
	{
		axis	= Vector3::cYAxis;
		angle	= mHeading;
	}
	else if ( x < Math::cFloatEpsilon && y < Math::cFloatEpsilon )
	{
		axis	= Vector3::cZAxis;
		angle	= mBank;
	}	
	else
	{
		Quaternion q;
		Math::EulerAngles2Quaternion( *this, q );
		q.GetAxisAndAngle( axis, angle );
	}
}