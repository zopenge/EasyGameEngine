//! @file     Interpolation.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Interpolation
//----------------------------------------------------------------------------

//! This class provides some interpolation functions.
class Interpolation
{
public:
	static _float	Current( _float alpha );
	static _float	Next( _float alpha );
	static _float	Middle( _float alpha );
	static _float	Linear( _float alpha );

	static _float	SineIn( _float alpha );
	static _float	SineOut( _float alpha );
	static _float	SineInOut( _float alpha );
	static _float	SineOutIn( _float alpha );

	static _float	QuadIn( _float alpha );
	static _float	QuadOut( _float alpha );
	static _float	QuadInOut( _float alpha );
	static _float	QuadOutIn( _float alpha );

	static _float	CubicIn( _float alpha );
	static _float	CubicOut( _float alpha );
	static _float	CubicInOut( _float alpha );
	static _float	CubicOutIn( _float alpha );

	static _float	InQuartIn( _float alpha );
	static _float	InQuartOut( _float alpha );

	static _float	QuartIn( _float alpha );
	static _float	QuartOut( _float alpha );
	static _float	QuartInOut( _float alpha );
	static _float	QuartOutIn( _float alpha );

	static _float	QuintIn( _float alpha );
	static _float	QuintOut( _float alpha );
	static _float	QuintInOut( _float alpha );
	static _float	QuintOutIn( _float alpha );

	static _float	ExpoIn( _float alpha );
	static _float	ExpoOut( _float alpha );
	static _float	ExpoInOut( _float alpha );
	static _float	ExpoOutIn( _float alpha );

	static _float	CircIn( _float alpha );
	static _float	CircOut( _float alpha );
	static _float	CircInOut( _float alpha );
	static _float	CircOutIn( _float alpha );

	static _float	Elastic( _float alpha );
	static _float	ElasticIn( _float alpha );
	static _float	ElasticOut( _float alpha );
	static _float	ElasticInOut( _float alpha );
	static _float	ElasticOutIn( _float alpha );

	static _float	BackIn( _float alpha );
	static _float	BackOut( _float alpha );
	static _float	BackInOut( _float alpha );
	static _float	BackOutIn( _float alpha );

	static _float	BounceIn( _float alpha );
	static _float	BounceOut( _float alpha );
	static _float	BounceInOut( _float alpha );
	static _float	BounceOutIn( _float alpha );

	// Integral
	static _float	IntegralCurrent( );
	static _float	IntegralNext( );
	static _float	IntegralMiddle( );
	static _float	IntegralLinear( );

	static _float	IntegralSineIn( );
	static _float	IntegralSineOut( );
	static _float	IntegralSineInOut( );
	static _float	IntegralSineOutIn( );

	static _float	IntegralQuadIn( );
	static _float	IntegralQuadOut( );
	static _float	IntegralQuadInOut( );
	static _float	IntegralQuadOutIn( );

	static _float	IntegralCubicIn( );
	static _float	IntegralCubicOut( );
	static _float	IntegralCubicInOut( );
	static _float	IntegralCubicOutIn( );

	static _float	IntegralInQuartIn( );
	static _float	IntegralInQuartOut( );

	static _float	IntegralQuartIn( );
	static _float	IntegralQuartOut( );
	static _float	IntegralQuartInOut( );
	static _float	IntegralQuartOutIn( );

	static _float	IntegralQuintIn( );
	static _float	IntegralQuintOut( );
	static _float	IntegralQuintInOut( );
	static _float	IntegralQuintOutIn( );

	static _float	IntegralExpoIn( );
	static _float	IntegralExpoOut( );
	static _float	IntegralExpoInOut( );
	static _float	IntegralExpoOutIn( );

	static _float	IntegralCircIn( );
	static _float	IntegralCircOut( );
	static _float	IntegralCircInOut( );
	static _float	IntegralCircOutIn( );

	static _float	IntegralElastic( );
	static _float	IntegralElasticIn( );
	static _float	IntegralElasticOut( );
	static _float	IntegralElasticInOut( );
	static _float	IntegralElasticOutIn( );

	static _float	IntegralBackIn( );
	static _float	IntegralBackOut( );
	static _float	IntegralBackInOut( );
	static _float	IntegralBackOutIn( );

	static _float	IntegralBounceIn( );
	static _float	IntegralBounceOut( );
	static _float	IntegralBounceInOut( );
	static _float	IntegralBounceOutIn( );

};

//----------------------------------------------------------------------------
// Interpolation Implementation
//----------------------------------------------------------------------------

inline _float Interpolation::Current( _float alpha )
{
	return 0.0f;
}

inline _float Interpolation::Next( _float alpha )
{
	return 1.0f;
}

inline _float Interpolation::Middle( _float alpha )
{
	return 0.5f;
}

inline _float Interpolation::Linear( _float alpha )
{
	return alpha;
}

inline _float Interpolation::IntegralCurrent( )
{
	return 0.0f;
}

inline _float Interpolation::IntegralNext( )
{
	return 1.0f;
}

inline _float Interpolation::IntegralMiddle( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralLinear( )
{
	return 0.5f;
}

//----------------------------------------------------------------------------
// In and Out function
//----------------------------------------------------------------------------

inline _float Interpolation::SineIn( _float alpha )
{
	return -1 * Math::Cos( alpha * Math::cPi * 0.5f ) + 1;
}
inline _float Interpolation::IntegralSineIn( )
{
	// integrate -cos(x*pi*0.5)+1 dx from x=0 to 1
	return 0.36338f;
}

inline _float Interpolation::SineOut( _float alpha )
{
	return Math::Sin( alpha * Math::cPi * 0.5f );
}
inline _float Interpolation::IntegralSineOut( )
{
	// integrate sin(x*pi*0.5) dx from x=0 to 1
	return 0.63662f;
}

inline _float Interpolation::QuadIn( _float alpha )
{
	return alpha * alpha;
}
inline _float Interpolation::IntegralQuadIn( )
{
	// integrate x^2 dx from x=0 to 1
	return 1.0f / 3.0f;
}

inline _float Interpolation::QuadOut( _float alpha )
{
	return - alpha * ( alpha - 2.0f );
}
inline _float Interpolation::IntegralQuadOut( )
{
	// integrate -x(x-2) dx from x=0 to 1
	return 2.0f / 3.0f;
}

inline _float Interpolation::CubicIn( _float alpha )
{
	return alpha * alpha * alpha;
}
inline _float Interpolation::IntegralCubicIn( )
{
	// integrate x^3 dx from x=0 to 1
	return 0.25f;
}

inline _float Interpolation::CubicOut( _float alpha )
{
	return 1.0f - CubicIn( 1.0f - alpha );
}
inline _float Interpolation::IntegralCubicOut( )
{
	// integrate 1-(1-x)^3 dx from x=0 to 1
	return 0.75f;
}

inline _float Interpolation::InQuartIn( _float alpha )
{
	return Math::Sqrt( Math::Sqrt( alpha ) );
}
inline _float Interpolation::IntegralInQuartIn( )
{
	// integrate sqrt(sqrt(x)) dx from x=0 to 1
	return 0.8f;
}

inline _float Interpolation::InQuartOut( _float alpha )
{
	return 1.0f - Math::Sqrt( Math::Sqrt( 1.0f - alpha ) );
}
inline _float Interpolation::IntegralInQuartOut( )
{
	// integrate 1-sqrt(sqrt(1-x)) dx from x=0 to 1
	return 0.2f;
}

inline _float Interpolation::QuartIn( _float alpha )
{
	return alpha * alpha * alpha * alpha;
}
inline _float Interpolation::IntegralQuartIn( )
{
	// integrate x^4 dx from x=0 to 1
	return 0.2f;
}

inline _float Interpolation::QuartOut( _float alpha )
{
	return 1.0f - QuartIn( 1.0f - alpha );
}
inline _float Interpolation::IntegralQuartOut( )
{
	// integrate 1-(1-x)^4 dx from x=0 to 1
	return 0.8f;
}

inline _float Interpolation::QuintIn( _float alpha )
{
	return alpha * alpha * alpha * alpha * alpha;
}
inline _float Interpolation::IntegralQuintIn( )
{
	// integrate x^5 dx from x=0 to 1
	return 1.0f / 6.0f;
}

inline _float Interpolation::QuintOut( _float alpha )
{
	return 1.0f - QuintIn( 1.0f - alpha );
}
inline _float Interpolation::IntegralQuintOut( )
{
	// integrate 1-(1-x)^5 dx from x=0 to 1
	return 5.0f / 6.0f;
}

inline _float Interpolation::ExpoIn( _float alpha )
{
	if ( alpha == 0.0f || alpha == 1.0f )
		return alpha;

	return Math::Pow( 2.0f, 10.0f * ( alpha - 1.0f ) ) - 0.001f;
}
inline _float Interpolation::IntegralExpoIn( )
{
	// integrate pow(2,10*(x-1))-0.001 dx from x=0 to 1
	return 0.143129f;
}

inline _float Interpolation::ExpoOut( _float alpha )
{
	return 1.0f - ExpoIn( 1.0f - alpha );
}
inline _float Interpolation::IntegralExpoOut( )
{
	// integrate 1-(pow(2,10*(1-x-1))-0.001) dx from x=0 to 1
	return 0.856871f;
}

inline _float Interpolation::CircIn( _float alpha )
{
	return -( Math::Sqrt( 1 - alpha * alpha ) - 1.0f );
}
inline _float Interpolation::IntegralCircIn( )
{
	// integrate -(sqrt(1-(x)^2)-1) dx from x=0 to 1
	return 0.214602f;
}

inline _float Interpolation::CircOut( _float alpha )
{
	return 1.0f - CircIn( 1.0f - alpha );
}
inline _float Interpolation::IntegralCircOut( )
{
	// integrate 1+(sqrt(1-(1-x)^2)-1) dx from x=0 to 1
	return 0.785398f;
}

inline _float Interpolation::ElasticIn( _float alpha )
{
	return 1.0f - ElasticOut( 1.0f - alpha );
}
inline _float Interpolation::IntegralElasticIn( )
{
	// integrate -pow(2,-10(1-x))sin((1-x-0.3/4)*2*pi/0.3) dx from x=0 to 1
	return 0.014285f;
}

inline _float Interpolation::ElasticOut( _float alpha )
{
	if ( alpha == 0.0f || alpha == 1.0f )
		return alpha;

	_float param1 = 0.3f/**/;
	_float s = param1 * 0.25f;
	return Math::Pow( 2.0f, -10.0f * alpha ) * Math::Sin( ( alpha - s ) * Math::c2Pi / param1 ) + 1.0f;
}
inline _float Interpolation::IntegralElasticOut( )
{
	// integrate pow(2,-10(x))sin((x-0.3/4)*2*pi/0.3)+1 dx from x=0 to 1
	return 0.985715f;
}

inline _float Interpolation::Elastic( _float alpha )
{
	if ( alpha == 0.0f || alpha == 1.0f )
		return 0.0f;

	_float param1 = 0.3f;
	return Math::Pow( 2.0f, -10.0f * alpha ) * Math::Sin( ( alpha ) * Math::c2Pi / param1 );
}
inline _float Interpolation::IntegralElastic( )
{
	// integrate pow(2,-10(x))sin((x)*2*pi/0.3) dx from x=0 to 1
	return 0.043042f;
}

inline _float Interpolation::BackIn( _float alpha )
{
	_float overshoot = 1.70158f;
	return alpha * alpha * ( ( overshoot + 1.0f ) * alpha - overshoot );
}
inline _float Interpolation::IntegralBackIn( )
{
	// integrate ((x)^2)(2.70158x-1.70158) dx from x=0 to 1
	return 0.108202f;
}

inline _float Interpolation::BackOut( _float alpha )
{
	return 1.0f - BackIn( 1.0f - alpha );
}
inline _float Interpolation::IntegralBackOut( )
{
	// integrate 1-((1-x)^2)(2.70158(1-x)-1.70158) dx from x=0 to 1
	return 0.891798f;
}

inline _float Interpolation::BounceIn( _float alpha )
{
	return 1.0f - BounceOut( 1.0f - alpha );
}
inline _float Interpolation::IntegralBounceIn( )
{
	// integrate 1-(7.5625*((1-x)^2)) dx from x=1-1/2.75 to 1							0.242424f
	// integrate 1-(7.5625*((1-x-1.5/2.75)^2)+0.75) dx from x=1-2/2.75 to 1-1/2.75			0.0606061f
	// integrate 1-(7.5625*((1-x-2.25/2.75)^2)+0.9375) dx from x=1-2.5/2.75 to 1-2/2.75		0.00757576f
	// integrate 1-(7.5625*((1-x-2.625/2.75)^2)+0.984375) dx from x=0 to 1-2.5/2.75			0.00094697f
	return 0.31155283f;
}

inline _float Interpolation::BounceOut( _float alpha )
{
	if ( alpha < 1.0f / 2.75f )
	{
		return 7.5625f * alpha * alpha;
	}
	else if ( alpha < 2.0f / 2.75f )
	{
		alpha -= 1.5f / 2.75f;
		return 7.5625f * alpha * alpha + 0.75f;
	}
	else if ( alpha < 2.5f / 2.75f )
	{
		alpha -= 2.25f / 2.75f;
		return 7.5625f * alpha * alpha + 0.9375f;
	}

	alpha -= 2.625f / 2.75f;
	return 7.5625f * alpha * alpha + 0.984375f;
}
inline _float Interpolation::IntegralBounceOut( )
{
	// integrate 7.5625*((x)^2) dx from x=0 to 1/2.75								0.121212f
	// integrate 7.5625*((x-1.5/2.75)^2)+0.75 dx from x=1/2.75 to 2/2.75			0.303030f
	// integrate 7.5625*((x-2.25/2.75)^2)+0.9375 dx from x=2/2.75 to 2.5/2.75		0.174242f
	// integrate 7.5625*((x-2.625/2.75)^2)+0.984375 dx from x=2.5/2.75 to 1			0.0899621f
	return 0.6884461f;
}

//----------------------------------------------------------------------------
// InOut function
//----------------------------------------------------------------------------

inline _float Interpolation::SineInOut( _float alpha )
{
	return -0.5f * ( Math::Cos( alpha * Math::cPi ) - 1.0f );
}

inline _float Interpolation::QuadInOut( _float alpha )
{
	if ( alpha < 0.5f )
		return 0.5f * QuadIn( alpha * 2.0f );

	return 0.5f + 0.5f * QuadOut( alpha * 2.0f - 1.0f );
}

inline _float Interpolation::CubicInOut( _float alpha )
{
	if ( alpha < 0.5f )
		return 0.5f * CubicIn( alpha * 2.0f );

	return 0.5f + 0.5f * CubicOut( alpha * 2.0f - 1.0f );
}

inline _float Interpolation::QuartInOut( _float alpha )
{
	if ( alpha < 0.5f )
		return 0.5f * QuartIn( alpha * 2.0f );

	return 0.5f + 0.5f * QuartOut( alpha * 2.0f - 1.0f );
}

inline _float Interpolation::QuintInOut( _float alpha )
{
	if ( alpha < 0.5f )
		return 0.5f * QuintIn( alpha * 2.0f );

	return 0.5f + 0.5f * QuintOut( alpha * 2.0f - 1.0f );
}

inline _float Interpolation::ExpoInOut( _float alpha )
{
	if ( alpha < 0.5f )
		return 0.5f * ExpoIn( alpha * 2.0f );

	return 0.5f + 0.5f * ExpoOut( alpha * 2.0f - 1.0f );
}

inline _float Interpolation::CircInOut( _float alpha )
{
	if ( alpha < 0.5f )
		return 0.5f * CircIn( alpha * 2.0f );

	return 0.5f + 0.5f * CircOut( alpha * 2.0f - 1.0f );
}

inline _float Interpolation::ElasticInOut( _float alpha )
{
	if ( alpha < 0.5f )
		return 0.5f * ElasticIn( alpha * 2.0f );

	return 0.5f + 0.5f * ElasticOut( alpha * 2.0f - 1.0f );
}

inline _float Interpolation::BackInOut( _float alpha )
{
	if ( alpha < 0.5f )
		return 0.5f * BackIn( alpha * 2.0f );

	return 0.5f + 0.5f * BackOut( alpha * 2.0f - 1.0f );
}

inline _float Interpolation::BounceInOut( _float alpha )
{
	if ( alpha < 0.5f )
		return 0.5f * BounceIn( alpha * 2.0f );

	return 0.5f + 0.5f * BounceOut( alpha * 2.0f - 1.0f );
}


//----------------------------------------------------------------------------
// OutIn function
//----------------------------------------------------------------------------

inline _float Interpolation::SineOutIn( _float alpha )
{
	return 1.0f - SineInOut( 1.0f - alpha );
}

inline _float Interpolation::QuadOutIn( _float alpha )
{
	return 1.0f - QuadInOut( 1.0f - alpha );
}

inline _float Interpolation::CubicOutIn( _float alpha )
{
	return 1.0f - CubicInOut( 1.0f - alpha );
}

inline _float Interpolation::QuartOutIn( _float alpha )
{
	return 1.0f - QuartInOut( 1.0f - alpha );
}

inline _float Interpolation::QuintOutIn( _float alpha )
{
	return 1.0f - QuintInOut( 1.0f - alpha );
}

inline _float Interpolation::ExpoOutIn( _float alpha )
{
	return 1.0f - ExpoInOut( 1.0f - alpha );
}

inline _float Interpolation::CircOutIn( _float alpha )
{
	return 1.0f - CircInOut( 1.0f - alpha );
}

inline _float Interpolation::ElasticOutIn( _float alpha )
{
	return 1.0f - ElasticInOut( 1.0f - alpha );
}

inline _float Interpolation::BackOutIn( _float alpha )
{
	return 1.0f - BackInOut( 1.0f - alpha );
}

inline _float Interpolation::BounceOutIn( _float alpha )
{
	return 1.0f - BounceInOut( 1.0f - alpha );
}

inline _float Interpolation::IntegralSineInOut( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralSineOutIn( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralQuadInOut( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralQuadOutIn( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralCubicInOut( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralCubicOutIn( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralQuartInOut( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralQuartOutIn( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralQuintInOut( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralQuintOutIn( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralExpoInOut( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralExpoOutIn( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralCircInOut( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralCircOutIn( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralElasticInOut( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralElasticOutIn( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralBackInOut( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralBackOutIn( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralBounceInOut( )
{
	return 0.5f;
}

inline _float Interpolation::IntegralBounceOutIn( )
{
	return 0.5f;
}


}