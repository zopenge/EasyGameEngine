//! @file     Math.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class Vector2;
class Vector3;
class Vector4;
class Matrix3;
class Quaternion;
class EulerAngles;
class AxisAlignedBox;
template< typename Type >
class Rect;
template< typename Type >
class MemSegmentPtr;

//----------------------------------------------------------------------------
// Math
//----------------------------------------------------------------------------

//! This class provides many common mathematics functions.
class Math
{
public:
	//! 0.0f
	static const _float cZero;
	//! 1.0f
	static const _float cOne;
	//! The ratio of a circle's circumference to its diameter.
	static const _float cPi;
	//! Double of the ratio of a circle's circumference to its diameter.
	static const _float c2Pi;
	//! The base of the natural system of logarithms (e).
	static const _float cE;
	//! The maximum float value.
	static const _float cMaxFloat;
	//! The minimum float value.
	static const _float cMinFloat;
	//! The maximum int value.
	static const _int cMaxInt;
	//! The minimum int value.
	static const _int cMinInt;
	//! The maximum uint value.
	static const _dword cMaxDword;
	//! The minimum uint value.
	static const _dword cMinDword;
	//! The epsilon value for float value comparison.
	static const _float cFloatEpsilon;
	//! The epsilon value for double value comparison.
	static const _double cDoubleEpsilon;

public:
	//! Compares two arguments and returns the smaller one.
	//! @param		value1		Integer value 1.
	//! @param		value2		Integer value 2.
	//! @return		The smaller one.
	template< typename Type >
	static Type Min( Type value1, Type value2 );
	//! Compares two arguments and returns the larger one.
	//! @param		value1		Integer value 1.
	//! @param		value2		Integer value 2.
	//! @return		The larger one.
	template< typename Type >
	static Type Max( Type value1, Type value2 );
	//! Clamp value into the range specified by min and max.
	//! @param		value		Integer value to be clamped.
	//! @param		min			Minimal value of the range.
	//! @param		max			Maximal value of the range.
	//! @return		The clamped value.
	template< typename Type >
	static Type Clamp( Type value, Type min, Type max );
	//! Clamp value into the range specified by 0 and 1.
	//! @param		value		Integer value to be clamped.
	//! @return		The clamped value.
	template< typename Type >
	static Type Clamp01( Type value );
	//!	Integer Wrap.
	//! @param		value		Integer value to be wrapped.
	//! @param		min			Minimal value of the range.
	//! @param		max			Maximal value of the range.
	//! @return		Returns the wrapped value between <b>min</b> and <b>max</b>. 
	//!				Such that <b>min</b> = 1, <b>max</b> = 5 then passing in 7 will return a value of 2.
	template< typename Type >
	static Type Wrap( Type value, Type min, Type max );
	//!	Remap the value in the other range by percentage in the old range.
	//! @param		value		The value to be remapped.
	//! @param		input_min	The input minimal value of the range.
	//! @param		input_max	The input maximal value of the range.
	//! @param		output_min	The output minimal value of the range.
	//! @param		output_max	The output maximal value of the range.
	//! @param		clamp		True indicates would clamp the value by the input range.
	//! @return		Returns the remapped value.
	template< typename Type >
	static Type Remap( Type value, Type input_min, Type input_max, Type output_min, Type output_max, _ubool clamp = _true );

	//! Swap two arguments.
	//! @param		value1		Integer value 1.
	//! @param		value2		Integer value 2.
	//! @return		none.
	template< typename Type >
	static _void Swap( Type& value1, Type& value2 );

	//! Calculates linear interpolation of two value.
	//! @param		vector1		Source value 1.
	//! @param		vector2		Target value 2.
	//! @param		factor		The interpolation factor, will clamp to between 0 to 1.
	//! @return		The result value of interpolation, value1 + ( value2 - value1 ) * factor.
	template< typename Type >
	static Type Lerp( Type value1, Type value2, _float factor );

	//! Calculates the value from value1 close to value2.
	//! @param		vector1		Source value 1.
	//! @param		vector2		Target value 2.
	//! @param		step		The close step.
	//! @return		The result value of interpolation.
	template< typename Type >
	static Type CloseToValue( Type value1, Type value2, Type step );

	//! Calculates the value from value1 lerp to value2.
	//! @param		vector1		Source value 1.
	//! @param		vector2		Target value 2.
	//! @param		alpha		The lerp alpha.
	//! @return		The result value of interpolation.
	template< typename Type >
	static Type LerpToValue( Type value1, Type value2, Type alpha );

public:
	//! Compare two value with float margin.
	//! @param		v1			The value 1.
	//! @param		v2			The value 2.
	//! @param		margin		The margin that allows some error.
	//! @return		True if they are identical, false otherwise.
	static _ubool Equal( _float v1, _float v2, _float margin = Math::cFloatEpsilon );
	//! Compare two value with double margin.
	//! @param		v1			The value 1.
	//! @param		v2			The value 2.
	//! @param		margin		The margin that allows some error.
	//! @return		True if they are identical, false otherwise.
	static _ubool Equal( _double v1, _double v2, _double margin = Math::cDoubleEpsilon );

	//! Calculates the absolute value.
	//! @param		value		Integer value.
	//! @return		The absolute value of argument.
	static _int Abs( _int value );
	//! Calculates the absolute value.
	//! @param		value		Floating-point value.
	//! @return		The absolute value of argument.
	static _float Abs( _float value );
	//! Calculates the absolute value.
	//! @param		value		Double-point value.
	//! @return		The absolute value of argument.
	static _double Abs( _double value );

	//! Converts radian to degree.
	//! @param		radian		Angle in radians.
	//! @return		The angle value of argument.
	static _float Radian2Degree( _float radian );
	//! Converts degree to radian.
	//! @param		degree		Angle in degrees.
	//! @return		The radian value of argument.
	static _float Degree2Radian( _float degree );

	//!	Get interval time in milliseconds by FPS.
	//!	@param		fps			The FPS.
	//!	@return		The interval time in milliseconds.
	static _dword GetIntervalTimeByFPS( _float fps );
	//!	Get FPS by interval time in milliseconds.
	//!	@param		interval	The interval time in milliseconds.
	//!	@return		The FPS.
	static _float GetFPSByIntervalTime( _dword interval );
	//!	Convert frame to elapsed time in milliseconds.
	//!	@param		frame		The key frame.
	//!	@param		fps			The FPS.
	//!	@return		The elapsed time in milliseconds.
	static _dword Frame2ElapsedTime( _float frame, _float fps );
	//!	Convert elapsed time in milliseconds to frame.
	//!	@param		elapse		The elapsed time in milliseconds.
	//!	@param		fps			The FPS.
	//!	@return		The key frame.
	static _float ElapsedTime2Frame( _dword elapse, _float fps );

	//! Calculates the integer closest in value to the argument.
	//! @param		value		Floating-point value.
	//! @return		The integer closest in value to the argument.
	static _int Round( _float value );
	//! Round up to the next integer (ex: 1.1f rounds to 2, -1.1f rounds to -2).
	//! @param		value		Floating-point value.
	//! @return		The integer round up in value to the argument.
	static _int RoundUp( _float value );

	//!	Get the mipmaps level by size.
	//!	@param		size		The texture size.
	//!	@return		The mipmaps level.
	static _dword GetMipmapLevel( _dword size );
	//!	Get the mipmaps level by width or height.
	//!	@param		width		The texture width.
	//!	@param		height		The texture height.
	//!	@return		The mipmaps level.
	static _dword GetMipmapLevel( _dword width, _dword height );

	//!	Counts the number of bits set.
	//!	@param		value		The value.
	//!	@return		The number of bits set.
	static _dword GetBitsSet( _dword value );
	//!	Reverse all the bits in m such that bit 31 becomes bit 1.
	//!	@param		value		The value.
	//!	@return		The bitwise reverse of value.
	static _dword ReverseBits( _dword value );
	//!	Get the index of the most significant bit.
	//!	@param		value		The value.
	//!	@return		The index of the most significant bit
	static _dword GetLastBitSet( _dword value );

	//!	Swap 16-bits value in bytes.
	//!	@param		value		The value.
	//!	@return		The swapped value.
	static _word BSwap16( _word value );
	//!	Swap 32-bits value in bytes.
	//!	@param		value		The value.
	//!	@return		The swapped value.
	static _dword BSwap32( _dword value );
	//!	Swap 64-bits value in bytes.
	//!	@param		value		The value.
	//!	@return		The swapped value.
	static _qword BSwap64( _qword value );
	//!	Swap 32-bits float value in bytes.
	//!	@param		value		The float value.
	//!	@return		The swapped float value.
	static _float BSwapFloat( _float value );
	//!	Swap 64-bits double value in bytes.
	//!	@param		value		The double value.
	//!	@return		The swapped double value.
	static _double BSwapDouble( _double value );

	//!	Check whether is prime number.
	//!	@param		value		The value what you want to check.
	//!	@return		True indicates the value is prime number.
	static _ubool IsPrime( _dword value );
	//!	Check whether is power of 2.
	//!	@param		value		The value what you want to check.
	//!	@return		True indicates the value is power of 2.
	static _ubool IsPowerOf2( _dword value );
	//!	Upper value to 2^N bound.
	//!	@param		value		The value.
	//!	@return		The 2^N bound arranged value.
	static _dword UpperBoundPowerOf2( _dword value );
	//!	Lower value to 2^N bound.
	//!	@param		value		The value.
	//!	@return		The 2^N bound arranged value.
	static _dword LowerBoundPowerOf2( _dword value );

	//!	Arrange upper value.
	//!	@param		value			The value.
	//!	@param		arrangevalue	The value what you want to arrange.
	//!	@return		The arranged value.
	static _dword UpperArrange( _dword value, _dword arrangevalue );
	//!	Arrange lower value.
	//!	@param		value			The value.
	//!	@param		arrangevalue	The value what you want to arrange.
	//!	@return		The arranged value.
	static _dword LowerArrange( _dword value, _dword arrangevalue );

	//! Calculates the ceiling of a value.
	//! @param		value		Floating-point value.
	//! @return		A float value representing the smallest integer that is greater than or equal to argument.
	static _float Ceil( _float value );
	//! Calculates the floor of a value.
	//! @param		value		Floating-point value.
	//! @return		A float value representing the largest integer that is less than or equal to argument.
	static _float Floor( _float value );
	//! Calculates the floating-point remainder.
	//! @param		valuex		Floating-point value.
	//! @param		valuey		Floating-point value.
	//! @return		Floating-point remainder of valuex/valuey.
	static _float Fmod( _float valuex, _float valuey );

	//! Calculates the square root.
	//! @param		value		Nonnegative floating-point value.
	//! @return		The square root of argument, or an indefinite if argument is negative.
	static _float Sqrt( _float value );
	//! Calculates the exponential.
	//! @param		value		Floating-point value.
	//! @return		The exponential value of argument, or INF if overflow, or 0 if underflow.
	static _float Exp( _float value );
	//! Calculates logarithms.
	//! @param		value		Value whose logarithm is to be found.
	//! @return		The logarithm of argument, or an indefinite if argument is negative, or INF if argument is 0.
	static _float Log( _float value );
	//! Calculates base raised to the power of exponent.
	//! @param		base		The base.
	//! @param		exponent	The exponent.
	//! @return		The value that base raised to the power of exponent.
	static _float Pow( _float base, _float exponent );

	//! Wrap an angle in range ¨Cpi...pi by adding the correct multiple of 2 pi.
	//! @param		radian		Angle in radians.
	//! @return		Angle in range ¨Cpi...pi.
	static _float WrapPi( _float radian );
	//! Calculate the sine.
	//! @param		radian		Angle in radians.
	//! @return		The sine of argument.
	static _float Sin( _float radian );
	//! Calculate the cosine.
	//! @param		radian		Angle in radians.
	//! @return		The cosine of argument.
	static _float Cos( _float radian );
	//! Calculate the sine and cosine.
	//! @param		radian		Angle in radians.
	//! @param		r			The value of sin and cos {sin(x), cos(x)}.
	//! @return		none.
	static _void SinCos( _float radian, _float r[2] );
	//! Calculate the sine and cosine.
	//! @param		radian		Angle in radians.
	//! @param		sin_v		The value of sin.
	//! @param		cos_v		The value of cos.
	//! @return		none.
	static _void SinCos( _float radian, _float& sin_v, _float& cos_v );
	//! Calculate the tangent.
	//! @param		radian		Angle in radians.
	//! @return		The tangent of argument.
	static _float Tan( _float radian );
	//! Calculate the cotangent.
	//! @param		radian		Angle in radians.
	//! @return		The cotangent of argument.
	static _float Cot( _float radian );
	//! Calculates the arcsine.
	//! @param		value		Value whose arcsine is to be calculated.
	//! @return		The arcsine of argument in the range -PI/2 to PI/2 radians.
	static _float Asin( _float value );
	//! Calculates the arccosine.
	//! @param		value		Value between -1 and 1 whose arccosine is to be calculated. 
	//! @return		The arccosine of argument in the range 0 to PI radians. 
	static _float Acos( _float value );
	//! Calculates the arctangent.
	//! @param		value		Value whose arctangent is to be calculated.
	//! @return		The arctangent of argument in the range -PI/2 to PI/2 radians, or 0 if value is 0.
	static _float Atan( _float value );
	//! Calculates the arctangent.
	//! @param		valuey		Value whose arctangent is to be calculated.
	//! @param		valuex		Value whose arctangent is to be calculated.
	//! @return		The arctangent of valuey/valuex in the range -PI to PI radians, or 0 if valuex is 0.
	static _float Atan( _float valuey, _float valuex );

	//!	Convert Quaternion to EulerAngles ( use the standard quaternion multiplication, rotate order is x->y->z ).
	//!	@param		quaternion		The Quaternion.
	//!	@param		angles			The EulerAngles.
	//! @return		none.
	static _void Quaternion2EulerAngles( const Quaternion& quaternion, EulerAngles& angles );
	//!	Convert Matrix3 to EulerAngles.
	//!	@param		matrix			The Matrix3.
	//!	@param		angles			The EulerAngles.
	//! @return		none.
	static _void Matrix2EulerAngles( const Matrix3& matrix, EulerAngles& angles );
	//!	Convert EulerAngles to Quaternion( use the standard quaternion multiplication, rotate order is x->y->z ).
	//!	@param		angles			The EulerAngles.
	//!	@param		quaternion		The Quaternion.
	//! @return		none.
	static _void EulerAngles2Quaternion( const EulerAngles& angles, Quaternion& quaternion );
	//!	Convert Matrix3 to Quaternion.
	//!	@param		matrix			The Matrix3.
	//!	@param		quaternion			The Quaternion.
	//! @return		none.
	static _void Matrix2Quaternion( const Matrix3& matrix, Quaternion& quaternion );
	//!	Convert EulerAngles to Matrix3.
	//!	@param		angles			The EulerAngles.
	//!	@param		matrix			The Matrix3.
	//! @return		none.
	static _void EulerAngles2Matrix( const EulerAngles& angles, Matrix3& matrix );
	//!	Convert Quaternion to Matrix3.
	//!	@param		quaternion		The Quaternion.
	//!	@param		matrix			The Matrix3.
	//! @return		none.
	static _void Quaternion2Matrix( const Quaternion& quaternion, Matrix3& matrix );

	//! Calculates the value from value1 lerp to value2.
	//! @param		vector1		Source value 1.
	//! @param		vector2		Target value 2.
	//! @param		alpha		The lerp alpha.
	//! @return		The result value of interpolation.
	static Quaternion SLerpToValue( const Quaternion& src, const Quaternion& dst, _float alpha );

	//! Calculate Tangent by vertex position, normal and uv
	//! @param		index_buffer	The index_buffer.
	//! @param		position_buffer	The position buffer.
	//! @param		normal_buffer	The normal buffer.
	//! @param		uv_buffer		The uv buffer.
	//! @param		ret_tangent_buffer	The result tangent buffer.
	static _void CalculateTangentByNormalUV( const MemSegmentPtr< _word >& index_buffer, const MemSegmentPtr< Vector3 >& position_buffer, const MemSegmentPtr< Vector3 >& normal_buffer, const MemSegmentPtr< Vector2 >& uv_buffer, MemSegmentPtr< Vector4 >& ret_tangent_buffer );
};

//----------------------------------------------------------------------------
// Math Implementation
//----------------------------------------------------------------------------

template< typename Type >
inline Type Math::Min( Type value1, Type value2 )
{
	return value1 < value2 ? value1 : value2;
}

template< typename Type >
inline Type Math::Max( Type value1, Type value2 )
{
	return value1 >= value2 ? value1 : value2;
}

template< typename Type >
inline Type Math::Clamp( Type value, Type min, Type max )
{
	if ( value < min )
		value = min;
	else if ( value > max )
		value = max;

	return value;
}

template< typename Type >
inline Type Math::Clamp01( Type value )
{
	if ( value < (Type) 0 )
		value = (Type) 0;
	else if ( value >( Type )1 )
		value = (Type) 1;

	return value;
}

template< typename Type >
inline Type Math::Wrap( Type value, Type min, Type max )
{
	// Get the range
	Type range = max - min;
	if ( range == 0 )
		return 0;

	// Wrap the value in this range
	if ( value > max )
	{
		Type tval = ( ( value - 1 ) - max ) % range;
		return min + tval;
	} 
	else if ( value < min )
	{
		Type tval = ( min - ( value + 1 ) ) % range;
		return max - tval;
	}

	return value;
}

template<>
inline _float Math::Wrap< _float >( _float value, _float min, _float max )
{
	if ( value > max ) 
	{
		_float tval = Fmod( value - max, max - min );
		return min + tval;
	} 
	else if ( value < min )
	{
		_float tval = Fmod( min - value, max - min );
		return max - tval;
	}

	return value;
}

template< typename Type >
inline Type Math::Remap( Type value, Type input_min, Type input_max, Type output_min, Type output_max, _ubool clamp )
{
	Type i_min = Min( input_min, input_max );
	Type i_max = Max( input_min, input_max );
	Type o_min = Min( output_min, output_max );
	Type o_max = Max( output_min, output_max );

	if ( i_min == i_max )
		return o_min;

	if ( clamp )
		value = Clamp( value, i_min, i_max );

	_double percent = _double( value - i_min ) / _double( i_max - i_min );

	return o_min + Type( percent * _double( o_max - o_min ) );
}

template< typename Type >
inline _void Math::Swap( Type& value1, Type& value2 )
{
	Type temp = value1;

	value1 = value2;
	value2 = temp;
}

template< typename Type >
inline Type Math::Lerp( Type value1, Type value2, _float factor )
{
	return (Type)( value1 + ( value2 - value1 ) * factor );
}

template< typename Type >
inline Type Math::CloseToValue( Type value1, Type value2, Type step )
{
	Type value = value1;
	if ( value < value2 )
	{
		value += step;
		if ( value > value2 )
			value = value2;
	}
	else if ( value > value2 )
	{
		value -= step;
		if ( value < value2 )
			value = value2;
	}
	return value;
}

template< typename Type >
inline Type Math::LerpToValue( Type value1, Type value2, Type step )
{
	Type value = value1;
	if ( value < value2 )
	{
		value = Lerp( value, value2, step );
		if ( value > value2 )
			value = value2;
	}
	else if ( value > value2 )
	{
		value = Lerp( value, value2, step );
		if ( value < value2 )
			value = value2;
	}
	return value;
}

inline _ubool Math::Equal( _float v1, _float v2, _float margin )
{
	return Math::Abs( v1 - v2 ) <= margin;
}

inline _ubool Math::Equal( _double v1, _double v2, _double margin )
{
	return Math::Abs( v1 - v2 ) <= margin;
}

inline _int Math::Abs( _int value )
{
	return value >= 0 ? value : -value;
}

inline _float Math::Abs( _float value )
{
#if (_USE_NEON_ == 1)
	return fabsf_neon( value );
#else
	return value >= 0.0f ? value : -value;
#endif
}

inline _double Math::Abs( _double value )
{
	return value >= 0.0 ? value : -value;
}

inline _float Math::Radian2Degree( _float radian )
{
	return radian / cPi * 180.0f;
}

inline _float Math::Degree2Radian( _float degree )
{
	return degree / 180.0f * cPi;
}

inline _dword Math::GetIntervalTimeByFPS( _float fps )
{
	return fps > 0.0f ? _dword( 1000.0f / fps ) : 0;
}

inline _float Math::GetFPSByIntervalTime( _dword interval )
{
	if ( interval == 0 )
		return 0.0f;

	return EGE_RATIO( 1000, interval );
}

inline _dword Math::Frame2ElapsedTime( _float frame, _float fps )
{
	return (_dword)( frame * 1000.0f / fps );
}

inline _float Math::ElapsedTime2Frame( _dword elapse, _float fps )
{
	return fps * (((_float) elapse) * 0.001f );
}

inline _int Math::Round( _float value )
{
	if ( value >= 0.0f )
		return (_int) ( value + 0.5f );
	else
		return (_int) ( value - 0.5f );
}

inline _int Math::RoundUp( _float value )
{
	if ( value >= 0.0f )
		return value > (_float)( (_int) value ) ? (_int) value + 1 : (_int) value;
	else
		return value < (_float)( (_int) value ) ? (_int) value - 1 : (_int) value;
}

inline _dword Math::GetMipmapLevel( _dword size )
{
	_dword mipcount = 1;
	while ( size >>= 1 )
		mipcount ++;

	return mipcount;
}

inline _dword Math::GetMipmapLevel( _dword width, _dword height )
{
	return GetMipmapLevel( Math::Max( width, height ) );
}

inline _dword Math::GetBitsSet( _dword value )
{
	// http://resnet.uoregon.edu/~gurney_j/jmpc/bitwise.html
	// http://hi.baidu.com/sunyubo458/blog/item/e26e9303439b7a7f3812bb7a.html 
	value = ( value & 0x55555555 ) + ( ( value & 0xAAAAAAAA ) >> 1 );
	value = ( value & 0x33333333 ) + ( ( value & 0xCCCCCCCC ) >> 2 );
	value = ( value & 0x0F0F0F0F ) + ( ( value & 0xF0F0F0F0 ) >> 4 );
	value = ( value & 0x00FF00FF ) + ( ( value & 0xFF00FF00 ) >> 8 );
	value = ( value & 0x0000FFFF ) + ( ( value & 0xFFFF0000 ) >> 16 );

	return value;
}

inline _dword Math::ReverseBits( _dword value )
{
	// http://resnet.uoregon.edu/~gurney_j/jmpc/bitwise.html
	// http://hi.baidu.com/sunyubo458/blog/item/e26e9303439b7a7f3812bb7a.html 
	value = ( ( value >> 1  ) & 0x55555555 ) | ( ( value << 1  ) & 0xAAAAAAAA );
	value = ( ( value >> 2  ) & 0x33333333 ) | ( ( value << 2  ) & 0xCCCCCCCC );
	value = ( ( value >> 4  ) & 0x0F0F0F0F ) | ( ( value << 4  ) & 0xF0F0F0F0 );
	value = ( ( value >> 8  ) & 0x00FF00FF ) | ( ( value << 8  ) & 0xFF00FF00 );
	value = ( ( value >> 16 ) & 0x0000FFFF ) | ( ( value << 16 ) & 0xFFFF0000 );

	return value;
}

inline _dword Math::GetLastBitSet( _dword value )
{
	value = ReverseBits( value );
	return 31 - ( GetBitsSet( value ^ ( value - 1 ) ) - 1 );
}

inline _word Math::BSwap16( _word value )
{
#if defined _PLATFORM_IOS_
	return _OSSwapInt16( value );
#else
	return ( value >> 8 ) | ( value << 8 );
#endif
}

inline _dword Math::BSwap32( _dword value )
{
#if defined _PLATFORM_IOS_
	return _OSSwapInt32( value );
#else
	return ((value & 0x000000FF) << 24) 
		| ((value & 0x0000FF00) << 8) 
		| ((value & 0xFF000000) >> 24) 
		| ((value & 0x00FF0000) >> 8);
#endif
}

inline _qword Math::BSwap64( _qword value )
{
	return ((value & 0x00000000000000FFLL) << 56) 
		| ((value & 0x000000000000FF00LL) << 40) 
		| ((value & 0x0000000000FF0000LL) << 24) 
		| ((value & 0x00000000FF000000LL) << 8) 
		| ((value & 0xFF000000000000FFLL) >> 56) 
		| ((value & 0x00FF000000000000LL) >> 40) 
		| ((value & 0x0000FF0000000000LL) >> 24) 
		| ((value & 0x000000FF00000000LL) >> 8);
}

inline _float Math::BSwapFloat( _float value )
{
	_dword tmp = BSwap32( *reinterpret_cast< _dword* >( &value ) );
	return *( reinterpret_cast< _float* >( &tmp ) );
}

inline _double Math::BSwapDouble( _double value )
{
	_qword tmp = BSwap64( *reinterpret_cast< _qword* >( &value ) );
	return *( reinterpret_cast< _double* >( &tmp ) );
}

inline _ubool Math::IsPrime( _dword value )
{
	if ( value < 2 ) 
		return _false;

	if ( value == 2 ) 
		return _true;

	for ( _dword i = 2; i * i <= value; i += 2 )
	{
		if ( value % i == 0) 
			return _false;
	}

	return _true;
}

inline _ubool Math::IsPowerOf2( _dword value )
{
	return ( value & ( value - 1 ) ) == 0;
}

inline _dword Math::UpperBoundPowerOf2( _dword value )
{
	if ( value == 0 )
		return 0;

	if ( value == 1 )
		return 1;

	_dword roundupsize = 2;
	for ( _dword i = 1 ; ; i ++ )
	{
		if ( roundupsize >= value )
			return roundupsize;
		else
			roundupsize <<= 1;
	}
}

inline _dword Math::LowerBoundPowerOf2( _dword value )
{
	if ( value == 0 )
		return 0;

	if ( value == 1 )
		return 1;

	_dword roundupsize = 2;
	for ( _dword i = 1 ; ; i ++ )
	{
		if ( roundupsize >= value )
			return 1 << ( i - 1 );
		else
			roundupsize <<= 1;
	}
}

inline _dword Math::UpperArrange( _dword value, _dword arrangevalue )
{
	_dword temp = value % arrangevalue;
	if ( temp )
		return value + arrangevalue - temp;
	else
		return value;
}

inline _dword Math::LowerArrange( _dword value, _dword arrangevalue )
{
	return value - ( value % arrangevalue );
}

inline _float Math::Ceil( _float value )
{
#if (_USE_NEON_ == 1)
	return ceilf_neon( value );
#else
	return (_float) ceil( value );
#endif
}

inline _float Math::Floor( _float value )
{
#if (_USE_NEON_ == 1)
	return floorf_neon( value );
#else
	return (_float) floor( value );
#endif
}

inline _float Math::Fmod( _float valuex, _float valuey )
{
#if (_USE_NEON_ == 1)
	return fmodf_neon( valuex, valuey );
#else
	return (_float) fmod( valuex, valuey );
#endif
}

inline _float Math::Sqrt( _float value )
{
#if (_USE_NEON_ == 1)
	return sqrtf_neon( value );
#else
	/*
	// Thanks for sharing code: http://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
	const unsigned int	SQRT_MAGIC_F	= 0x5f3759df;
	const float			xhalf			= 0.5f * value;

	union // get bits for floating value
	{
		float x;
		int i;
	} u;
	u.x = value;
	u.i = SQRT_MAGIC_F - (u.i >> 1);  // gives initial guess y0
	
	return value*u.x*(1.5f - xhalf*u.x*u.x);// Newton step, repeating increases accuracy
	*/
	return ( _float )::sqrt( value );
#endif
}

inline _float Math::Exp( _float value )
{
#if (_USE_NEON_ == 1)
	return expf_neon( value );
#else
	return (_float) exp( value );
#endif
}

inline _float Math::Log( _float value )
{
#if (_USE_NEON_ == 1)
	return logf_neon( value );
#else
	return (_float) log( value );
#endif
}

inline _float Math::Pow( _float base, _float exponent )
{
#if (_USE_NEON_ == 1)
	return powf_neon( base, exponent );
#else
	return (_float) pow( base, exponent );
#endif
}

inline _float Math::WrapPi( _float radian )
{
	radian += cPi;
	radian -= Ceil( radian / c2Pi ) * c2Pi;
	radian += cPi;

	return radian;
}

inline _float Math::Sin( _float radian )
{
#if (_USE_NEON_ == 1)
	return sinf_neon( radian );
#else
	return (_float) sin( radian );
#endif
}

inline _float Math::Cos( _float radian )
{
#if (_USE_NEON_ == 1)
	return cosf_neon( radian );
#else
	return (_float) cos( radian );
#endif
}

inline _void Math::SinCos( _float radian, _float r[2] )
{
#if (_USE_NEON_ == 1)
	sincosf_neon( radian, r );
#else
	r[0] = Math::Sin( radian );
	r[1] = Math::Cos( radian );
#endif
}

inline _void Math::SinCos( _float radian, _float& sin_v, _float& cos_v )
{
#if (_USE_NEON_ == 1)
	_float r[2];
	sincosf_neon( radian, r );

	sin_v = r[0];
	cos_v = r[1];
#else
	sin_v = Math::Sin( radian );
	cos_v = Math::Cos( radian );
#endif
}

inline _float Math::Tan( _float radian )
{
#if (_USE_NEON_ == 1)
	return tanf_neon( radian );
#else
	return (_float) tan( radian );
#endif
}

inline _float Math::Cot( _float radian )
{
	return 1.0f / (_float) tan( radian );
}

inline _float Math::Asin( _float value )
{
	if ( value > 1.0f )
		return cPi / 2.0f;

	if ( value < -1.0f )
		return cPi / -2.0f;

#if (_USE_NEON_ == 1)
	return asinf_neon( value );
#else
	return (_float) asin( value );
#endif
}

inline _float Math::Acos( _float value )
{
	if ( value > 1.0f )
		return 0.0f;

	if ( value < -1.0f )
		return cPi;

#if (_USE_NEON_ == 1)
	return acosf_neon( value );
#else
	return (_float) acos( value );
#endif
}

inline _float Math::Atan( _float value )
{
#if (_USE_NEON_ == 1)
	return atanf_neon( value );
#else
	return (_float) atan( value );
#endif
}

inline _float Math::Atan( _float valuey, _float valuex )
{
#if (_USE_NEON_ == 1)
	return atan2f_neon( valuey, valuex );
#else
	return (_float) atan2( valuey, valuex );
#endif
}

}