#pragma once

namespace EGE {

/// <summary>
/// This class represents a 2D point ( or a 2D size ) with integer coordinates.
/// </summary>
template <typename Type>
class Point {
public:
	//! X-component of the point.
	Type x;
	//! Y-component of the point.
	Type y;

public:
	//! The zero point.
	static const Point cZeroPoint;
	//! The maximum point.
	static const Point cMaxPoint;
	//! The minimum point.
	static const Point cMinPoint;

public:
	//! Constructor, create a point without sets x, y components.
	//! @param		none
	Point();
	//! Constructor, create a point and sets x, y components.
	//! @param		xx			X-component of the point.
	//! @param		yy			Y-component of the point.
	Point(Type xx, Type yy);

	//! Get positive point.
	//! @param		none
	//! @return		The positive point.
	Point<Type> operator+() const;
	//! Get negative point.
	//! @param		none
	//! @return		The negative point.
	Point<Type> operator-() const;

	//! Compare two points, that means compare each component of the points.
	//! @param		point		The point to compare with.
	//! @return		True if they are identical, false otherwise.
	_ubool operator==(const Point& point) const;
	//! Compare two points, that means compare each component of the points.
	//! @param		point		The point to compare with.
	//! @return		True if they are not identical, false otherwise.
	_ubool operator!=(const Point& point) const;

	//! Add a point to current point, and save result in current one.
	//! @param		point		The point to add.
	//! @return		The result point of addition.
	Point& operator+=(const Point& point);
	//! Subtract a point from current point, and save result in current one.
	//! @param		point		The point to subtract.
	//! @return		The result point of subtraction.
	Point& operator-=(const Point& point);
	//! Multiple a point to current point, and save result in current one.
	//! @param		point		The point to add.
	//! @return		The result point of addition.
	Point& operator*=(const Point& point);
	//! Divide a point from current point, and save result in current one.
	//! @param		point		The point to subtract.
	//! @return		The result point of subtraction.
	Point& operator/=(const Point& point);
	//! Multiple a value to current point, and save result in current one.
	//! @param		value		The value to multiple.
	//! @return		The result point of multiple.
	Point& operator*=(Type value);
	//! Divide a value to current point, and save result in current one.
	//! @param		value		The value to divide.
	//! @return		The result point of divide.
	Point& operator/=(Type value);

	//! Add a point to current point, return a new point to save result.
	//! @param		point		The point to add.
	//! @return		The result point of addition.
	Point<Type> operator+(const Point& point) const;
	//! Subtract a point from current point, return a new point to save result.
	//! @param		point		The point to subtract.
	//! @return		The result point of subtraction.
	Point<Type> operator-(const Point& point) const;
	//! Multiple a point to current point, return a new point to save result.
	//! @param		point		The point to add.
	//! @return		The result point of addition.
	Point<Type> operator*(const Point& point) const;
	//! Divide a point from current point, return a new point to save result.
	//! @param		point		The point to subtract.
	//! @return		The result point of subtraction.
	Point<Type> operator/(const Point& point) const;
	//! Multiple a value to current point, return a new point to save result.
	//! @param		value		The value to multiple.
	//! @return		The result point of multiple.
	Point<Type> operator*(Type value) const;
	//! Divide a value to current point, return a new point to save result.
	//! @param		value		The value to divide.
	//! @return		The result point of divide.
	Point<Type> operator/(Type value) const;

	//! Calculates point magnitude.
	//! @param		none
	//! @return		The magnitude of point.
	Type Magnitude() const;
	//! Calculates the square of point magnitude, this function is faster than Magnitude.
	//! @param		none
	//! @return		The square of magnitude of point.
	Type MagnitudeSquared() const;

	//!	Get the ratio.
	//!	@param		none.
	//!	@return		The ratio.
	_float GetRatio() const;
};

template <typename Type>
Point<Type>::Point() {
}

template <typename Type>
Point<Type>::Point(Type xx, Type yy)
    : x(xx), y(yy) {
}

template <typename Type>
Point<Type> Point<Type>::operator+() const {
	return Point(x, y);
}

template <typename Type>
Point<Type> Point<Type>::operator-() const {
	return Point(-x, -y);
}

template <typename Type>
_ubool Point<Type>::operator==(const Point& point) const {
	return x == point.x && y == point.y;
}

template <typename Type>
_ubool Point<Type>::operator!=(const Point& point) const {
	return x != point.x || y != point.y;
}

template <typename Type>
Point<Type>& Point<Type>::operator+=(const Point& point) {
	x += point.x;
	y += point.y;

	return *this;
}

template <typename Type>
Point<Type>& Point<Type>::operator-=(const Point& point) {
	x -= point.x;
	y -= point.y;

	return *this;
}

template <typename Type>
Point<Type>& Point<Type>::operator*=(const Point& point) {
	x *= point.x;
	y *= point.y;

	return *this;
}

template <typename Type>
Point<Type>& Point<Type>::operator/=(const Point& point) {
	x /= point.x;
	y /= point.y;

	return *this;
}

template <typename Type>
Point<Type>& Point<Type>::operator*=(Type value) {
	x *= value;
	y *= value;

	return *this;
}

template <typename Type>
Point<Type>& Point<Type>::operator/=(Type value) {
	x /= value;
	y /= value;

	return *this;
}

template <typename Type>
Point<Type> Point<Type>::operator+(const Point& point) const {
	return Point(x + point.x, y + point.y);
}

template <typename Type>
Point<Type> Point<Type>::operator-(const Point& point) const {
	return Point(x - point.x, y - point.y);
}

template <typename Type>
Point<Type> Point<Type>::operator*(const Point& point) const {
	return Point(x * point.x, y * point.y);
}

template <typename Type>
Point<Type> Point<Type>::operator/(const Point& point) const {
	return Point(x / point.x, y / point.y);
}

template <typename Type>
Point<Type> Point<Type>::operator*(Type value) const {
	return Point(x * value, y * value);
}

template <typename Type>
Point<Type> Point<Type>::operator/(Type value) const {
	return Point(x / value, y / value);
}

template <typename Type>
Type Point<Type>::Magnitude() const {
	return (Type)::sqrt((_double)(x * x + y * y));
}

template <typename Type>
Type Point<Type>::MagnitudeSquared() const {
	return x * x + y * y;
}

template <typename Type>
_float Point<Type>::GetRatio() const {
	return EGE_RATIO(x, y);
}

} // namespace EGE