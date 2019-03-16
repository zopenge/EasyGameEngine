//! @file     Interpolator.h
//! @author   foreven
//! @version  1.1
//! @date     2013.1.11
//! Copyright ...

#pragma once

namespace EGE
{

class Interpolator : public TObject< IInterpolator >
{
private:
	typedef TObject< IInterpolator >	BaseClass;
	
private:
	InterpolatorFunc	mInterpolatorFunction;
	IntegralFunc		mIntegralFunction;
public:
	Interpolator( );
	Interpolator( InterpolatorFunc ipl_func, IntegralFunc integral_func );
	virtual ~Interpolator( );
	 
public:
	virtual _float		Calculate( _float alpha ) const override;
	virtual _float		GetIntegral( ) const override;
};

}