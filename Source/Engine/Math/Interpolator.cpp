//! @file     Interpolator.cpp
//! @author   foreven
//! @version  1.1
//! @date     2013.1.11
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Interpolator Implementation
//----------------------------------------------------------------------------

Interpolator::Interpolator( )
	: mInterpolatorFunction( _null )
	, mIntegralFunction( _null )
{

}

Interpolator::Interpolator( InterpolatorFunc ipl_func, IntegralFunc integral_func )
	: mInterpolatorFunction( ipl_func )
	, mIntegralFunction( integral_func )
{

}

Interpolator::~Interpolator( )
{

}

_float Interpolator::Calculate( _float alpha ) const
{
	if ( mInterpolatorFunction != _null )
		return (*mInterpolatorFunction )( alpha );

	return alpha;
}

_float Interpolator::GetIntegral( ) const
{
	if ( mIntegralFunction != _null )
		return ( *mIntegralFunction )( );

	return 0.0f;
}