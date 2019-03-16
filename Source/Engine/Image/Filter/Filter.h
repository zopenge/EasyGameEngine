//! @file     Filter.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GenericFilter
//----------------------------------------------------------------------------

class GenericFilter
{
protected:
	//! Filter support
	_double  mWidth;

public:
	GenericFilter( _double width ) : mWidth( width )
	{

	}
	virtual ~GenericFilter( )
	{

	}

public:
	EGE_GET_SET_ACCESSOR( _double, Width )

public:
	//! Returns F(dVal) where F is the filter's impulse response.
	virtual _double Filter( _double value ) PURE;
};

//----------------------------------------------------------------------------
// BoxFilter
//----------------------------------------------------------------------------

class BoxFilter : public GenericFilter
{
public:
    BoxFilter( ) : GenericFilter( 0.5 )
	{
	}
    virtual ~BoxFilter( )
	{
	}

public:
    virtual _double Filter ( _double value ) { return Math::Abs(value) <= mWidth ? 1.0 : 0.0; }
};

//----------------------------------------------------------------------------
// BilinearFilter
//----------------------------------------------------------------------------

class BilinearFilter : public GenericFilter
{
public:
	BilinearFilter( ) : GenericFilter( 1.0 )
	{
	}
	virtual ~BilinearFilter( )
	{
	}

public:
	virtual _double Filter ( _double value ) 
	{ 
		value = Math::Abs( value ); 
		return value < mWidth ? mWidth - value : 0.0; 
	}
};

//----------------------------------------------------------------------------
// BicubicFilter
//----------------------------------------------------------------------------

class BicubicFilter : public GenericFilter
{
protected:
	// data for parameterized Mitchell filter
    _double p0, p2, p3;
    _double q0, q1, q2, q3;

public:
    BicubicFilter( _double b = 1.0 / 3.0, _double c = 1.0 / 3.0 ) : GenericFilter( 2.0 )
	{
		p0 = (6 - 2*b) / 6;
		p2 = (-18 + 12*b + 6*c) / 6;
		p3 = (12 - 9*b - 6*c) / 6;
		q0 = (8*b + 24*c) / 6;
		q1 = (-12*b - 48*c) / 6;
		q2 = (6*b + 30*c) / 6;
		q3 = (-b - 6*c) / 6;
	}
    virtual ~BicubicFilter( )
	{
	}

public:
    virtual _double Filter( _double value ) 
	{ 
		value = Math::Abs( value );
		if(value < 1)
			return (p0 + value*value*(p2 + value*p3));
		if(value < 2)
			return (q0 + value*(q1 + value*(q2 + value*q3)));

		return 0.0;
	}
};

//----------------------------------------------------------------------------
// CatmullRomFilter
//----------------------------------------------------------------------------

class CatmullRomFilter : public GenericFilter
{
public:
	CatmullRomFilter( ) : GenericFilter( 2.0 )
	{
	}
	virtual ~CatmullRomFilter( )
	{
	}

public:
    virtual _double Filter( _double value )
	{ 
		if(value < -2) return 0;
		if(value < -1) return (0.5*(4 + value*(8 + value*(5 + value))));
		if(value < 0)  return (0.5*(2 + value*value*(-5 - 3*value)));
		if(value < 1)  return (0.5*(2 + value*value*(-5 + 3*value)));
		if(value < 2)  return (0.5*(4 + value*(-8 + value*(5 - value))));

		return 0.0;
	}
};

//----------------------------------------------------------------------------
// Lanczos3Filter
//----------------------------------------------------------------------------

class Lanczos3Filter : public GenericFilter
{
private:
	_double Sinc( _double value) 
	{
		if ( value != 0.0 )
		{
			value *= Math::cPi;
			return Math::Sin( (_float)value ) / value;
		}

		return 1.0;
	}

public:
	Lanczos3Filter( ) : GenericFilter( 3.0 )
	{
	}
	virtual ~Lanczos3Filter( )
	{
	}

public:
	virtual _double Filter( _double value )
	{
		value = Math::Abs( value ); 
		if ( value < mWidth )
			return Sinc( value ) * Sinc( value / mWidth );

		return 0.0;
	}
};

//----------------------------------------------------------------------------
// BSplineFilter
//----------------------------------------------------------------------------

class BSplineFilter : public GenericFilter
{
public:
	BSplineFilter( ) : GenericFilter( 2.0 )
	{
	}
	virtual ~BSplineFilter( )
	{
	}

public:
	virtual _double Filter( _double value )
	{
		value = Math::Abs( value );
		if(value < 1) return (4 + value*value*(-6 + 3*value)) / 6;
		if(value < 2) {
			double t = 2 - value;
			return (t*t*t / 6);
		}

		return 0.0;
	}
};

}