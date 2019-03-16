//! @file     Color.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Color
//----------------------------------------------------------------------------

//! This class represents a color use four float-point number to store r, g, b, a components. [ARGB]
class Color
{
public:
	//! Blue-component of the Color.
	_byte	b;
	//! Green-component of the Color.
	_byte	g;
	//! Red-component of the Color.
	_byte	r;
	//! Alpha-component of the Color.
	_byte	a;

public:
	//!	The int -> float convertion table
	static _float sInt2FloatConvertionTable[ 256 ];

public:
	//! The null color, has RGBA as 0.0f, 0.0f, 0.0f, 0.0f.
	static const Color cNull;

	//! Red, #FF0000
	static const Color cRed;
	//! Dark red, #8B0000
	static const Color cDarkRed;
	//! Indian red, #CD5C5C
	static const Color cIndianRed;
	//! Orange red, #FF4500
	static const Color cOrangeRed;

	//! Green, #00FF00
	static const Color cGreen;
	//! Dark green, #008B00
	static const Color cDarkGreen;
	//! Lawn green, #7CFC00
	static const Color cLawnGreen;
	//! Sea green, #2E8B57
	static const Color cSeaGreen;

	//! Blue, #0000FF
	static const Color cBlue;
	//! Dark blue, #00008B
	static const Color cDarkBlue;
	//! Sky blue, #00BFFF
	static const Color cSkyBlue;
	//! Midnight blue, #191970
	static const Color cMidnightBlue;

	//! White, #FFFFFF
	static const Color cWhite;
	//! Black, #000000
	static const Color cBlack;
	//! Gray, #808080
	static const Color cGray;
	//! Silver, #C0C0C0
	static const Color cSilver;

	//! Yellow, #FFFF00
	static const Color cYellow;
	//! Purple, #800080
	static const Color cPurple;
	//! Teal, #008080
	static const Color cTeal;
	//! Lime, #00FF00
	static const Color cLime;
	//! Tomato, #FF6347
	static const Color cTomato;
	//! Orange, #FFA500
	static const Color cOrange;
	//! Brown, #A52A2A
	static const Color cBrown;
	//! Bisque, #FFE4C4
	static const Color cBisque;
	//! Pink, #FFC0CB
	static const Color cPink;
	//! Violet, #EE82EE
	static const Color cViolet;
	//! Magenta, #FF00FF
	static const Color cMagenta;
	//! Orchid, #DA70D6
	static const Color cOrchid;
	//! Chocolate, #D2691E
	static const Color cChocolate;

public:
	//! Constructor, create a color without sets rgba components.
	//! @param		none
	inline Color( );
	//! Constructor, create a color from a color.
	//! @param		color		The ARGB color.
	inline Color( const Color& color );
	//! Constructor, create a color and sets rgba components.
	//! @param		rr			Red-component of the vector.
	//! @param		gg			Green-component of the vector.
	//! @param		bb			Blue-component of the vector.
	//! @param		aa			Alpha-component of the vector.
	inline Color( _float rr, _float gg, _float bb, _float aa = 1.0f );
	//! Constructor, create a color and sets rgba components.
	//! @param		rr			Red-component of the vector.
	//! @param		gg			Green-component of the vector.
	//! @param		bb			Blue-component of the vector.
	//! @param		aa			Alpha-component of the vector.
	inline Color( _byte rr, _byte gg, _byte bb, _byte aa = 255 );
	//! Constructor, create a color from a dword.
	//! @param		color		The ARGB color dword.
	inline Color( _dword color );

	//! Type conversion, converts color from 4 floats to a dword.
	//! @param		none
	//! @return		The color represent in dword.
	inline operator _dword ( ) const;

	//! Compare a color to current color.
	//! @param		color		The color to compare.
	//! @return		True indicates it's equal.
	inline _ubool operator == ( const Color& color ) const;
	//! Compare a color to current color.
	//! @param		color		The color to compare.
	//! @return		True indicates it's not equal.
	inline _ubool operator != ( const Color& color ) const;

	//! Add a color to current color, and save result in current one.
	//! @param		color		The color to add.
	//! @return		The result color of addition.
	inline Color& operator += ( const Color& color );
	//! Subtract a color to current color, and save result in current one.
	//! @param		color		The color to subtract.
	//! @return		The result color of subtraction.
	inline Color& operator -= ( const Color& color );
	//! Multiply a color to current color, and save result in current one.
	//! @param		color		The color to multiply.
	//! @return		The result color of multiplication.
	inline Color& operator *= ( const Color& color );
	//! Divide a color to current color, and save result in current one.
	//! @param		color		The color to divide.
	//! @return		The result color of division.
	inline Color& operator /= ( const Color& color );

	//! Multiply a scalar to current color, and save result in current one.
	//! @param		scalar		The scalar to multiply.
	//! @return		The result color of multiplication.
	inline Color& operator *= ( _float scalar );
	//! Divide a scalar to current color, and save result in current one.
	//! @param		scalar		The scalar to divide.
	//! @return		The result color of division.
	inline Color& operator /= ( _float scalar );

	//! Add a color to current color, return a new color to save result.
	//! @param		color		The color to add.
	//! @return		The result color of addition.
	inline Color operator + ( const Color& color ) const;
	//! Subtract a color to current color, return a new color to save result.
	//! @param		color		The color to subtract.
	//! @return		The result color of subtraction.
	inline Color operator - ( const Color& color ) const;
	//! Multiply a color to current color, return a new color to save result.
	//! @param		color		The color to multiply.
	//! @return		The result color of multiplication.
	inline Color operator * ( const Color& color ) const;
	//! Divide a color to current color, return a new color to save result.
	//! @param		color		The color to divide.
	//! @return		The result color of division.
	inline Color operator / ( const Color& color ) const;

	//! Multiply a scalar to current color, return a new color to save result.
	//! @param		scalar		The scalar to multiply.
	//! @return		The result color of multiplication.
	inline Color operator * ( _float scalar ) const;
	//! Divide a scalar to current color, return a new color to save result.
	//! @param		scalar		The scalar to divide.
	//! @return		The result color of division.
	inline Color operator / ( _float scalar ) const;

	//!	Get red component in floating-point.
	//!	@param		none.
	//!	@return		The red component in [0.0, 1.0].
	inline _float Red( ) const;
	//!	Get green component in floating-point.
	//!	@param		none.
	//!	@return		The green component in [0.0, 1.0].
	inline _float Green( ) const;
	//!	Get blue component in floating-point.
	//!	@param		none.
	//!	@return		The blue component in [0.0, 1.0].
	inline _float Blue( ) const;
	//!	Get alpha component in floating-point.
	//!	@param		none.
	//!	@return		The alpha component in [0.0, 1.0].
	inline _float Alpha( ) const;

	//!	Set red component in floating-point.
	//!	@param		none.
	//!	@return		none.
	inline _void Red( _float value );
	//!	Set green component in floating-point.
	//!	@param		none.
	//!	@return		none.
	inline _void Green( _float value );
	//!	Set blue component in floating-point.
	//!	@param		none.
	//!	@return		none.
	inline _void Blue( _float value );
	//!	Set alpha component in floating-point.
	//!	@param		none.
	//!	@return		none.
	inline _void Alpha( _float value );

	inline _ubool IsNullColor( ) const;

public:
	//!	The average of red.
	//! @param		color1		Source color 1.
	//! @param		color2		Target color 2.
	//!	@return		The red color component.
	inline static _byte AvgRed( const Color& color1, const Color& color2 );
	//!	The average of green.
	//! @param		color1		Source color 1.
	//! @param		color2		Target color 2.
	//!	@return		The green color component.
	inline static _byte AvgGreen( const Color& color1, const Color& color2 );
	//!	The average of blue.
	//! @param		color1		Source color 1.
	//! @param		color2		Target color 2.
	//!	@return		The blue color component.
	inline static _byte AvgBlue( const Color& color1, const Color& color2 );
	//!	The average of alpha.
	//! @param		color1		Source color 1.
	//! @param		color2		Target color 2.
	//!	@return		The alpha color component.
	inline static _byte AvgAlpha( const Color& color1, const Color& color2 );

	//! Calculates dot product of two colors.
	//! @param		color1		Source color 1.
	//! @param		color2		Target color 2.
	//! @return		The result color dot product.
	//! @remarks	Modulate the components of each argument as signed components, add their products;
	//!				then replicate the sum to all color channels, including alpha.
	static Color Dot( const Color& color1, const Color& color2 );
	//! Calculates linear interpolation of two colors.
	//! @param		color1		Source color 1.
	//! @param		color2		Target color 2.
	//! @param		alpha		The interpolation factor, will clamp to between 0 to 1.
	//! @return		The result color of interpolation, color1 + ( color2 - color1 ) * alpha.
	static Color Lerp( const Color& color1, const Color& color2, _float alpha );

	//! Mix two colors.
	//! @param		color1		Source color 1.
	//! @param		color2		Target color 2.
	//! @return		The result color of interpolation, Lerp color1 and color2 by color2's alpha.
	static Color Mix( const Color& color1, const Color& color2 );
};

//----------------------------------------------------------------------------
// Color Implementation
//----------------------------------------------------------------------------

Color::Color( )
{
}

Color::Color( const Color& color )
{
	*(_dword*) this = *(_dword*) &color;
}

Color::Color( _float rr, _float gg, _float bb, _float aa )
{
	a = _byte( aa * 255.0f );
	r = _byte( rr * 255.0f );
	g = _byte( gg * 255.0f );
	b = _byte( bb * 255.0f );
}

Color::Color( _byte rr, _byte gg, _byte bb, _byte aa )
	: b( bb ), g( gg ), r( rr ), a( aa )
{
}

Color::Color( _dword color )
{
	*( _dword* ) this = color;
}

Color::operator _dword ( ) const
{
	return *(_dword*) this;
}

_ubool Color::operator == ( const Color& color ) const
{
	return (_dword)*this == (_dword)color;
}

_ubool Color::operator != ( const Color& color ) const
{
	return (_dword)*this != (_dword)color;
}

Color& Color::operator += ( const Color& color )
{
	r = Math::Min( r + color.r, 255 );
	g = Math::Min( g + color.g, 255 );
	b = Math::Min( b + color.b, 255 );
	a = Math::Min( a + color.a, 255 );

	return *this;
}

Color& Color::operator -= ( const Color& color )
{
	r = r > color.r ? r - color.r : 0;
	g = g > color.g ? g - color.g : 0;
	b = b > color.b ? b - color.b : 0;
	a = a > color.a ? a - color.a : 0;

	return *this;
}

Color& Color::operator *= ( const Color& color )
{
	r = (_byte) ( sInt2FloatConvertionTable[r] * sInt2FloatConvertionTable[color.r] * 255.0f );
	g = (_byte) ( sInt2FloatConvertionTable[g] * sInt2FloatConvertionTable[color.g] * 255.0f );
	b = (_byte) ( sInt2FloatConvertionTable[b] * sInt2FloatConvertionTable[color.b] * 255.0f );
	a = (_byte) ( sInt2FloatConvertionTable[a] * sInt2FloatConvertionTable[color.a] * 255.0f );

	return *this;
}

Color& Color::operator /= ( const Color& color )
{
	r = (_byte) ( sInt2FloatConvertionTable[r] / sInt2FloatConvertionTable[color.r] * 255.0f );
	g = (_byte) ( sInt2FloatConvertionTable[g] / sInt2FloatConvertionTable[color.g] * 255.0f );
	b = (_byte) ( sInt2FloatConvertionTable[b] / sInt2FloatConvertionTable[color.b] * 255.0f );
	a = (_byte) ( sInt2FloatConvertionTable[a] / sInt2FloatConvertionTable[color.a] * 255.0f );

	return *this;
}

Color& Color::operator *= ( _float scalar )
{
	r = Math::Min< _byte >( _byte( r * scalar ), 255 );
	g = Math::Min< _byte >( _byte( g * scalar ), 255 );
	b = Math::Min< _byte >( _byte( b * scalar ), 255 );
	a = Math::Min< _byte >( _byte( a * scalar ), 255 );

	return *this;
}

Color& Color::operator /= ( _float scalar )
{
	r = Math::Min< _byte >( _byte( r / scalar ), 255 );
	g = Math::Min< _byte >( _byte( g / scalar ), 255 );
	b = Math::Min< _byte >( _byte( b / scalar ), 255 );
	a = Math::Min< _byte >( _byte( a / scalar ), 255 );

	return *this;
}

Color Color::operator + ( const Color& color ) const
{
	Color color_tmp( *this );
	color_tmp += color;

	return color_tmp;
}

Color Color::operator - ( const Color& color ) const
{
	Color color_tmp( *this );
	color_tmp -= color;

	return color_tmp;
}

Color Color::operator * ( const Color& color ) const
{
	Color color_tmp( *this );
	color_tmp *= color;

	return color_tmp;
}

Color Color::operator / ( const Color& color ) const
{
	Color color_tmp( *this );
	color_tmp /= color;

	return color_tmp;
}

Color Color::operator * ( _float scalar ) const
{
	Color color_tmp( *this );
	color_tmp *= scalar;

	return color_tmp;
}

Color Color::operator / ( _float scalar ) const
{
	Color color_tmp( *this );
	color_tmp /= scalar;

	return color_tmp;
}

_float Color::Red( ) const
{
	return sInt2FloatConvertionTable[ r ];
}

_float Color::Green( ) const
{
	return sInt2FloatConvertionTable[ g ];
}

_float Color::Blue( ) const
{
	return sInt2FloatConvertionTable[ b ];
}

_float Color::Alpha( ) const
{
	return sInt2FloatConvertionTable[ a ];
}

_void Color::Red( _float value )
{
	a = _byte( value * 255.0f );
}

_void Color::Green( _float value )
{
	g = _byte( value * 255.0f );
}

_void Color::Blue( _float value )
{
	b = _byte( value * 255.0f );
}

_void Color::Alpha( _float value )
{
	a = _byte( value * 255.0f );
}

_byte Color::AvgRed( const Color& color1, const Color& color2 )
{
	return (_byte) ( ( (_dword)color1.r + (_dword)color2.r ) / 2 );
}

_byte Color::AvgGreen( const Color& color1, const Color& color2 )
{
	return (_byte) ( ( (_dword)color1.g + (_dword)color2.g ) / 2 );
}

_byte Color::AvgBlue( const Color& color1, const Color& color2 )
{
	return (_byte) ( ( (_dword)color1.b + (_dword)color2.b ) / 2 );
}

_byte Color::AvgAlpha( const Color& color1, const Color& color2 )
{
	return (_byte) ( ( (_dword)color1.a + (_dword)color2.a ) / 2 );
}

_ubool Color::IsNullColor( ) const
{
	if ( a == (_byte)0 )
		return _true;
	if ( r != (_byte)0 )
		return _false;
	if ( g != (_byte)0 )
		return _false;
	if ( b != (_byte)0 )
		return _false;
	return _true;
}

}