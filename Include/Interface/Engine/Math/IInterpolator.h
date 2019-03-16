//! @file     IInterpolator.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IInterpolator
//----------------------------------------------------------------------------

class IInterpolator : public IObject
{
public:
	//! Calculates interpolation.
	//! @param		alpha	The alpha factor.
	//! @return		The result value of interpolation.
	virtual _float Calculate( _float alpha ) const PURE;
	virtual _float GetIntegral( ) const PURE;
};

typedef _float	(*InterpolatorFunc)( _float );
typedef _float	(*IntegralFunc)( );

}