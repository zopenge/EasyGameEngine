//! @file     Rect.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Rect
//----------------------------------------------------------------------------

template< typename Type >
class Rect
{
public:
	// [Left,Top]
	Type	l;
	Type	t;
	// (Right,Bottom)
	Type	r;
	Type	b;

public:
	//! The empty rectangle.
	static const Rect cNull;
	static const Rect cMax;

public:
	Rect( );
	Rect( Type left, Type top, Type right, Type bottom );

public:
	//! Compare two rectangle, that means compare each component of the rectangles.
	//! @param		rect		The rectangle to compare with.
	//! @return		True if they are identical, false otherwise.
	_ubool operator == ( const Rect& rect ) const;
	//! Compare two rectangle, that means compare each component of the rectangles.
	//! @param		rect		The rectangle to compare with.
	//! @return		True if they are not identical, false otherwise.
	_ubool operator != ( const Rect& rect ) const;

	//! Add a point to current rectangle ( offset ), and save result in current one.
	//! @param		point		The point to add.
	//! @return		The result rectangle of addition.
	Rect& operator += ( const Point< Type >& point );
	//! Subtract a point from current rectangle ( offset ), and save result in current one.
	//! @param		point		The point to subtract.
	//! @return		The result rectangle of subtraction.
	Rect& operator -= ( const Point< Type >& point );
	//! Multi a point to current rectangle ( offset ), and save result in current one.
	//! @param		point		The point to add.
	//! @return		The result rectangle of addition.
	Rect& operator *= ( const Point< Type >& point );
	//! Div a point from current rectangle ( offset ), and save result in current one.
	//! @param		point		The point to subtract.
	//! @return		The result rectangle of subtraction.
	Rect& operator /= ( const Point< Type >& point );

	//! Add a point to current rectangle ( offset ), return a new rectangle to save result.
	//! @param		point		The point to add.
	//! @return		The result rectangle of addition.
	Rect operator + ( const Point< Type >& point ) const;
	//! Subtract a point from current rectangle ( offset ), return a new rectangle to save result.
	//! @param		point		The point to subtract.
	//! @return		The result rectangle of subtraction.
	Rect operator - ( const Point< Type >& point ) const;
	//! Multi a point to current rectangle ( offset ), return a new rectangle to save result.
	//! @param		point		The point to add.
	//! @return		The result rectangle of addition.
	Rect operator * ( const Point< Type >& point ) const;
	//! Div a point from current rectangle ( offset ), return a new rectangle to save result.
	//! @param		point		The point to subtract.
	//! @return		The result rectangle of subtraction.
	Rect operator / ( const Point< Type >& point ) const;

	//! Initialize by position.
	//!	@remark		The region is [left,top] to (right,bottom).
	//! @param		left		Left-component of the rectangle.
	//! @param		top			Top-component of the rectangle.
	//! @param		right		Right-component of the rectangle.
	//! @param		bottom		Bottom-component of the rectangle.
	//!	@return		none.
	Rect& InitWithPosition( Type left, Type top, Type right, Type bottom );
	//! Initialize by width and height.
	//! @param		lt			Left and Top component of the rectangle.
	//! @param		size		Size of the rectangle.
	//!	@return		none.
	Rect& InitWithSize( const Point< Type >& lt, const Point< Type >& size );
	//! Initialize by width and height.
	//! @param		left		Left-component of the rectangle.
	//! @param		top			Top-component of the rectangle.
	//! @param		width		Width of the rectangle.
	//! @param		height		Height of the rectangle.
	//!	@return		none.
	Rect& InitWithSize( Type left, Type top, Type width, Type height );
	//! Initialize by center position with size.
	//! @param		x			center-x position of the rectangle.
	//! @param		y			center-y position of the rectangle.
	//! @param		width		Width of the rectangle.
	//! @param		height		Height of the rectangle.
	//!	@return		none.
	Rect& InitWithCenterPosition( Type x, Type y, Type width, Type height );

	//! Get the width of the rectangle.
	//! @param		none
	//! @return		The width of the rectangle.
	Type GetWidth( ) const;
	//! Get the height of the rectangle.
	//! @param		none
	//! @return		The height of the rectangle.
	Type GetHeight( ) const;
	//! Set the width of the rectangle.
	//! @param		width		The width of the rectangle.
	//! @return		none.
	_void SetWidth( Type width );
	//! Set the height of the rectangle.
	//! @param		height		The height of the rectangle.
	//! @return		none.
	_void SetHeight( Type height );

	//!	Get the size.
	//!	@param		none.
	//!	@return		The size of rectangle.
	Point< Type > GetSize( ) const;
	//! Set the size of the rectangle.
	//! @param		size		The size of the rectangle.
	//! @return		none.
	_void SetSize( const Point< Type >& size );
	//! Calculates the aspect ratio.
	//! @param		none
	//! @return		The aspect ratio of the rectangle.
	_float GetAspectRadtio( ) const;

	//! Get the center position of the rectangle.
	//! @param		none
	//! @return		The center position of the rectangle.
	Point< Type > GetCenter( ) const;
	//! Get the left-top position of the rectangle.
	//! @param		none
	//! @return		The left-top position of the rectangle.
	Point< Type > GetLeftTop( ) const;
	//! Get the left-bottom position of the rectangle.
	//! @param		none
	//! @return		The left-bottom position of the rectangle.
	Point< Type > GetLeftBottom( ) const;
	//! Get the right-top position of the rectangle.
	//! @param		none
	//! @return		The right-top position of the rectangle.
	Point< Type > GetRightTop( ) const;
	//! Get the right-top bottom of the rectangle.
	//! @param		none
	//! @return		The right-top bottom of the rectangle.
	Point< Type > GetRightBottom( ) const;

	//! Set the left-top position of the rectangle.
	//! @param		pos		The left-top position of the rectangle.
	//! @return		none.
	_void SetLeftTop( const Point< Type >& pos );

	//! Increases the width and height of the rectangle by moving its sides away from its center.
	//! @param		width		The number of units to inflate the left and right sides.
	//! @param		height		The number of units to inflate the top and bottom sides.
	//! @remarks	The inflate will happen at both sides, so the width and height of the result rectangle will increase two times arguments.
	Rect& Inflate( Type width, Type height );
	//! Increases the width and height of the rectangle by moving its sides away from its center.
	//! @param		size		The number of units to inflate both left-right sides and top-bottom sides.
	//! @remarks	The inflate will happen at both sides, so the width and height of the result rectangle will increase two times arguments.
	Rect& Inflate( const Point< Type >& size );
	//! Decreases the width and height of the rectangle by moving its sides toward its center.
	//! @param		width		The number of units to deflate the left and right sides.
	//! @param		height		The number of units to deflate the top and bottom sides.
	//! @remarks	The deflate will happen at both sides, so the width and height of the result rectangle will decrease two times arguments.
	Rect& Deflate( Type width, Type height );
	//! Decreases the width and height of the rectangle by moving its sides toward its center.
	//! @param		size		The number of units to deflate both left-right sides and top-bottom sides.
	//! @remarks	The deflate will happen at both sides, so the width and height of the result rectangle will decrease two times arguments.
	Rect& Deflate( const Point< Type >& size );

	//! Determines whether the specified point lies within the rectangle.
	//! @param		point		The point to determine.
	//! @return		True if the point lies within the rectangle, false otherwise.
	_ubool PointInRect( const Point< Type >& point ) const;
	//! Determines whether the specified point lies within the rectangle.
	//! @param		point		The point to determine.
	//! @return		True if the point lies within the rectangle, false otherwise.
	_ubool PointInRect( Type x, Type y ) const;
	//! Determines whether the specified rect intersect within the rectangle.
	//! @param		region		The region to determine.
	//! @return		True if the rect intersect within the rectangle, false otherwise.
	_ubool Intersect( const Rect< Type >& region ) const;
	//! Determines whether the specified rect intersect within the rectangle.
	//! @param		x			center-x position of the rectangle.
	//! @param		y			center-y position of the rectangle.
	//! @param		width		Width of the rectangle.
	//! @param		height		Height of the rectangle.
	//! @return		True if the rect intersect within the rectangle, false otherwise.
	_ubool Intersect( Type x, Type y, Type width, Type height ) const;

public:
	//! Makes a rectangle equal to the intersection of two existing ones.
	//! @param		rect1		The source rectangle 1.
	//! @param		rect2		The source rectangle 2.
	//! @return		The intersection rectangle that contains both source rectangles.
	static Rect Intersect( const Rect& rect1, const Rect& rect2 );
	//! Makes a rectangle equal to the union of two existing ones.
	//! @param		rect1		The source rectangle 1.
	//! @param		rect2		The source rectangle 2.
	//! @return		The union rectangle that contains both source rectangles.
	static Rect Union( const Rect& rect1, const Rect& rect2 );

	//! Fit the rectangle with the same ratio.
	//! @param		rect1		The source rectangle 1, the center position will use this rectangle.
	//! @param		rect2		The source rectangle 2, the size will use this rectangle.
	//! @return		The rectangle with max size by the same ratio.
	static Rect ScaleToFitCenter( const Rect& rect1, const Rect& rect2 );
};

//----------------------------------------------------------------------------
// Rect Implementation
//----------------------------------------------------------------------------

template< typename Type >
Rect< Type >::Rect( )
{
}

template< typename Type >
Rect< Type >::Rect( Type left, Type top, Type right, Type bottom )
{
	l = left;
	t = top;
	r = right;
	b = bottom;
}

template< typename Type >
_ubool Rect< Type >::operator == ( const Rect& rect ) const
{
	return l == rect.l && t == rect.t && r == rect.r && b == rect.b;
}

template< typename Type >
_ubool Rect< Type >::operator != ( const Rect& rect ) const
{
	return l != rect.l || t != rect.t || r != rect.r || b != rect.b;
}

template< typename Type >
Rect< Type >& Rect< Type >::operator += ( const Point< Type >& point )
{
	l += point.x;
	t += point.y;
	r += point.x;
	b += point.y;

	return *this;
}

template< typename Type >
Rect< Type >& Rect< Type >::operator -= ( const Point< Type >& point )
{
	l -= point.x;
	t -= point.y;
	r -= point.x;
	b -= point.y;

	return *this;
}

template< typename Type >
Rect< Type >& Rect< Type >::operator *= ( const Point< Type >& point )
{
	l *= point.x;
	t *= point.y;
	r *= point.x;
	b *= point.y;

	return *this;
}

template< typename Type >
Rect< Type >& Rect< Type >::operator /= ( const Point< Type >& point )
{
	l /= point.x;
	t /= point.y;
	r /= point.x;
	b /= point.y;

	return *this;
}

template< typename Type >
Rect< Type > Rect< Type >::operator + ( const Point< Type >& point ) const
{
	return Rect( l + point.x, t + point.y, r + point.x, b + point.y );
}

template< typename Type >
Rect< Type > Rect< Type >::operator - ( const Point< Type >& point ) const
{
	return Rect( l - point.x, t - point.y, r - point.x, b - point.y );
}

template< typename Type >
Rect< Type > Rect< Type >::operator * ( const Point< Type >& point ) const
{
	return Rect( l * point.x, t * point.y, r * point.x, b * point.y );
}

template< typename Type >
Rect< Type > Rect< Type >::operator / ( const Point< Type >& point ) const
{
	return Rect( l / point.x, t / point.y, r / point.x, b / point.y );
}

template< typename Type >
Rect< Type >& Rect< Type >::InitWithPosition( Type left, Type top, Type right, Type bottom )
{
	l = left;
	t = top;
	r = right;
	b = bottom;

	return *this;
}

template< typename Type >
Rect< Type >& Rect< Type >::InitWithSize( const Point< Type >& lt, const Point< Type >& size )
{
	l = lt.x;
	t = lt.y;
	r = l + size.x;
	b = t + size.y;

	return *this;
}

template< typename Type >
Rect< Type >& Rect< Type >::InitWithSize( Type left, Type top, Type width, Type height )
{
	l = left;
	t = top;
	r = left + width;
	b = top + height;

	return *this;
}

template< typename Type >
Rect< Type >& Rect< Type >::InitWithCenterPosition( Type x, Type y, Type width, Type height )
{
	l = x - width / (Type) 2;
	t = y - height / (Type) 2;
	r = x + width / (Type) 2;
	b = y + height / (Type) 2;

	return *this;
}

template< typename Type >
Type Rect< Type >::GetWidth( ) const
{
	return r - l;
}

template< typename Type >
Type Rect< Type >::GetHeight( ) const
{
	return b - t;
}

template< typename Type >
_void Rect< Type >::SetWidth( Type width )
{
	r = l + width;
}

template< typename Type >
_void Rect< Type >::SetHeight( Type height )
{
	b = t + height;
}

template< typename Type >
Point< Type > Rect< Type >::GetSize( ) const
{
	return Point< Type >( GetWidth( ), GetHeight( ) );
}

template< typename Type >
_void Rect< Type >::SetSize( const Point< Type >& size )
{
	r = l + size.x;
	b = t + size.y;
}

template< typename Type >
_float Rect< Type >::GetAspectRadtio( ) const
{
	return _float( GetHeight( ) ) / _float( GetWidth( ) );
}

template< typename Type >
Point< Type > Rect< Type >::GetCenter( ) const
{
	return Point< Type >( ( l + r ) / 2, ( t + b ) / 2 );
}

template< typename Type >
Point< Type > Rect< Type >::GetLeftTop( ) const
{
	return Point< Type >( l, t );
}

template< typename Type >
Point< Type > Rect< Type >::GetLeftBottom( ) const
{
	return Point< Type >( l, b - (Type) 1 );
}

template< typename Type >
Point< Type > Rect< Type >::GetRightTop( ) const
{
	return Point< Type >( r - (Type) 1, t );
}

template< typename Type >
Point< Type > Rect< Type >::GetRightBottom( ) const
{
	return Point< Type >( r - (Type) 1, b - (Type) 1 );
}

template< typename Type >
_void Rect< Type >::SetLeftTop( const Point< Type >& pos )
{
	Type width	= GetWidth( );
	Type height = GetHeight( );

	InitWithSize( pos.x, pos.y, width, height );
}

template< typename Type >
Rect< Type >& Rect< Type >::Inflate( Type width, Type height )
{
	l -= width;
	t -= height;
	r += width;
	b += height;

	return *this;
}

template< typename Type >
Rect< Type >& Rect< Type >::Inflate( const Point< Type >& size )
{
	return Inflate( size.x, size.y );
}

template< typename Type >
Rect< Type >& Rect< Type >::Deflate( Type width, Type height )
{
	l += width;
	t += height;
	r -= width;
	b -= height;

	return *this;
}

template< typename Type >
Rect< Type >& Rect< Type >::Deflate( const Point< Type >& size )
{
	return Deflate( size.x, size.y );
}

template< typename Type >
_ubool Rect< Type >::PointInRect( const Point< Type >& point ) const
{
	return PointInRect( point.x, point.y );
}

template< typename Type >
_ubool Rect< Type >::PointInRect( Type x, Type y ) const
{
	if ( x < l )
		return _false;

	if ( x > r )
		return _false;

	if ( y < t )
		return _false;

	if ( y > b )
		return _false;

	return _true;
}

template< typename Type >
_ubool Rect< Type >::Intersect( const Rect< Type >& region ) const
{
	Type _l = MAX( l, region.l );
	if ( _l > r || _l > region.r )
		return _false;

	Type _r = MIN( r, region.r );
	if ( _r < l || _r < region.l )
		return _false;

	Type _t = MAX( t, region.t );
	if ( _t > b || _t > region.b )
		return _false;

	Type _b = MIN( b, region.b );
	if ( _b < t || _b < region.t )
		return _false;

	return _true;
}

template< typename Type >
_ubool Rect< Type >::Intersect( Type x, Type y, Type width, Type height ) const
{
	return Intersect( Rect< Type >( ).InitWithSize( x, y, width, height ) );
}

template< typename Type >
Rect< Type > Rect< Type >::Intersect( const Rect& rect1, const Rect& rect2 )
{
	Type l = MAX( rect1.l, rect2.l );
	if ( l > rect1.r || l > rect2.r )
		return cNull;

	Type r = MIN( rect1.r, rect2.r );
	if ( r < rect1.l || r < rect2.l )
		return cNull;

	Type t = MAX( rect1.t, rect2.t );
	if ( t > rect1.b || t > rect2.b )
		return cNull;

	Type b = MIN( rect1.b, rect2.b );
	if ( b < rect1.t || b < rect2.t )
		return cNull;

	return Rect< Type >( ).InitWithPosition( l, t, r, b );
}

template< typename Type >
Rect< Type > Rect< Type >::Union( const Rect& rect1, const Rect& rect2 )
{
	Type l = MIN( rect1.l, rect2.l );
	Type r = MAX( rect1.r, rect2.r );
	Type t = MIN( rect1.t, rect2.t );
	Type b = MAX( rect1.b, rect2.b );

	return Rect< Type >( ).InitWithPosition( l, t, r, b );
}

template< typename Type >
Rect< Type > Rect< Type >::ScaleToFitCenter( const Rect& rect1, const Rect& rect2 )
{
	_float scale = MIN( EGE_RATIO( rect1.GetWidth( ), rect2.GetWidth( ) ), 
		EGE_RATIO( rect1.GetHeight( ), rect2.GetHeight( ) ) );

	Point< Type > center( rect1.GetCenter( ) );
	Point< Type > size( (Type)(rect2.GetWidth( ) * scale), (Type)(rect2.GetHeight( ) * scale) );

	return Rect< Type >( ).InitWithCenterPosition( center.x, center.y, size.x, size.y );
}

}