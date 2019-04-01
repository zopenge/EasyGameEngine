#pragma once

namespace EGE {

/// <summary>
/// Line
/// </summary>
template <typename Type>
class Line {
public:
	Type mPoints[2];

public:
	Line();
	Line(const Type& point1, const Type& point2);

public:
	template <typename TransformType>
	Line& operator*=(const TransformType& transform) {
		mPoints[0] *= transform;
		mPoints[1] *= transform;

		return *this;
	}

	template <typename TransformType>
	Line operator*(const TransformType& transform) const {
		Line returnline(*this);

		return returnline *= transform;
	}

	Line& operator+=(const Type& point) {
		mPoints[0] += point;
		mPoints[1] += point;

		return *this;
	}

	Line operator+(const Type& point) const {
		Line returnline(*this);

		return returnline += point;
	}

	_float GetDistance(const Type& point, Type* nearest_point) const;
};

template <typename Type>
Line<Type>::Line() {
}

template <typename Type>
Line<Type>::Line(const Type& point1, const Type& point2) {
	mPoints[0] = point1;
	mPoints[1] = point2;
}

template <typename Type>
_float Line<Type>::GetDistance(const Type& point, Type* nearest_point) const {
	Type line_vector = mPoints[1] - mPoints[0];
	Type v0 = point - mPoints[0];
	Type v1 = point - mPoints[1];

	_float cross = Type::Dot(line_vector, v0);
	if (cross < 0.0f) {
		if (nearest_point != _null)
			*nearest_point = mPoints[0];
		return v0.Magnitude();
	}

	cross = Type::Dot(-line_vector, v1);
	if (cross < 0.0f) {
		if (nearest_point != _null)
			*nearest_point = mPoints[1];
		return v1.Magnitude();
	}

	Type proj = Type::Project(v0, line_vector);
	if (nearest_point != _null)
		*nearest_point = mPoints[0] + proj;

	return (v0 - proj).Magnitude();
}

} // namespace EGE