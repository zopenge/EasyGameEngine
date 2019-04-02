//! @file     Polygon2D.cpp
//! @author   foreven
//! @version  1.1
//! @date     2012.12.5
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Polygon2D Implementation
//----------------------------------------------------------------------------

Polygon2D::_VERTEX_TYPE Polygon2D::GetVertexType(_dword vertex_index) const {
	_dword prev = vertex_index - 1;
	_dword next = vertex_index + 1;
	if (prev == -1)
		prev = mVertexArray.Number() - 1;
	if (next == mVertexArray.Number())
		next = 0;

	EGE_ASSERT(vertex_index != prev && vertex_index != next && prev != next);

	Vector2 v1 = mVertexArray[prev] - mVertexArray[vertex_index];
	Vector2 v2 = mVertexArray[next] - mVertexArray[vertex_index];
	if (v1 == Vector2::cOrigin || v2 == Vector2::cOrigin)
		return _FLAT;

	_float rotation_angle = Vector2::GetRotateAngle(v1, v2);

	if (rotation_angle > 0)
		return _CONVEX;

	//@
	if (rotation_angle == 0)
		return _FLAT;

	return _CONCAVE;
}

_ubool Polygon2D::IsTriangleValid(_dword v1_index, _dword v2_index, _dword v3_index) const {
	Triangle2D triangle(mVertexArray[v1_index], mVertexArray[v2_index], mVertexArray[v3_index]);
	for (_dword i = 0; i < mVertexArray.Number(); ++i) {
		if (i == v1_index || i == v2_index || i == v3_index)
			continue;

		if (triangle.PointInTriangle(mVertexArray[i]))
			return _false;
	}
	return _true;
}

Vector2 Polygon2D::MiddleVector() const {
	Vector2 middle = Vector2::cOrigin;
	for (_dword i = 0; i < mVertexArray.Number(); ++i) {
		middle += mVertexArray[i];
	}
	if (mVertexArray.Number() != 0)
		middle /= (_float)mVertexArray.Number();

	return middle;
}

_void Polygon2D::ToTriangleArray(Array<Triangle2D>& triangles) const {
	Polygon2D polygon = *this;

	_dword i = 0;
	_dword invalid_number = 0;
	while (_true) {
		if (polygon.mVertexArray.Number() < 3)
			break;

		if (polygon.mVertexArray.Number() == 3) {
			Triangle2D triangle(polygon.mVertexArray[0], polygon.mVertexArray[1], polygon.mVertexArray[2]);
			if (triangle.IsValid())
				triangles.Append(triangle);

			break;
		}

		if (invalid_number >= polygon.mVertexArray.Number())
			break;

		_VERTEX_TYPE vertex_type = polygon.GetVertexType(i);
		if (vertex_type == _FLAT) {
			polygon.mVertexArray.RemoveByIndex(i);
			invalid_number = 0;
			if (i >= polygon.mVertexArray.Number())
				i = 0;
			continue;
		} else if (vertex_type == _CONVEX) {
			_dword prev = i - 1;
			_dword next = i + 1;
			if (prev == -1)
				prev = polygon.mVertexArray.Number() - 1;
			if (next == polygon.mVertexArray.Number())
				next = 0;

			EGE_ASSERT(i != prev && i != next && prev != next);

			if (polygon.IsTriangleValid(prev, i, next)) {
				Triangle2D triangle(polygon.mVertexArray[prev], polygon.mVertexArray[i], polygon.mVertexArray[next]);
				if (triangle.IsValid())
					triangles.Append(triangle);

				polygon.mVertexArray.RemoveByIndex(i);
				invalid_number = 0;
				if (i >= polygon.mVertexArray.Number())
					i = 0;
				continue;
			} else {
				invalid_number++;
			}
		} else {
			invalid_number++;
		}

		i++;
		if (i >= polygon.mVertexArray.Number())
			i = 0;
	}
}

_ubool Polygon2D::DividePolygon(const Array<Vector2>& divide_lines, Polygon2D& polygon1, Polygon2D& polygon2) {
	if (mVertexArray.Number() < 3)
		return _false;

	if (divide_lines.Number() < 2)
		return _false;

	MinDistanceInfo head_min_distance_info;
	head_min_distance_info.mVertexIndex = mVertexArray.Number() - 1;
	head_min_distance_info.mDistance = Line2D(mVertexArray[head_min_distance_info.mVertexIndex], mVertexArray[0]).GetDistance(divide_lines.GetHeadElement(), _null);

	MinDistanceInfo tail_min_distance_info;
	tail_min_distance_info.mVertexIndex = mVertexArray.Number() - 1;
	tail_min_distance_info.mDistance = Line2D(mVertexArray[tail_min_distance_info.mVertexIndex], mVertexArray[0]).GetDistance(divide_lines.GetTailElement(), _null);

	for (_dword i = 1; i < mVertexArray.Number(); ++i) {
		MinDistanceInfo min_distance_info;
		min_distance_info.mVertexIndex = i - 1;

		min_distance_info.mDistance = Line2D(mVertexArray[min_distance_info.mVertexIndex], mVertexArray[i]).GetDistance(divide_lines.GetHeadElement(), _null);
		if (min_distance_info.mDistance < head_min_distance_info.mDistance)
			head_min_distance_info = min_distance_info;

		min_distance_info.mDistance = Line2D(mVertexArray[min_distance_info.mVertexIndex], mVertexArray[i]).GetDistance(divide_lines.GetTailElement(), _null);
		if (min_distance_info.mDistance < tail_min_distance_info.mDistance)
			tail_min_distance_info = min_distance_info;
	}

	polygon1.mVertexArray.Clear();
	polygon2.mVertexArray.Clear();

	_ubool generate_ascending = _true;

	if (head_min_distance_info.mVertexIndex < tail_min_distance_info.mVertexIndex) {
		generate_ascending = _true;
	} else if (head_min_distance_info.mVertexIndex > tail_min_distance_info.mVertexIndex) {
		generate_ascending = _false;
	} else if (head_min_distance_info.mVertexIndex == tail_min_distance_info.mVertexIndex) {
		_float head_distance = (divide_lines.GetHeadElement() - mVertexArray[head_min_distance_info.mVertexIndex]).Magnitude();
		_float tail_distance = (divide_lines.GetTailElement() - mVertexArray[head_min_distance_info.mVertexIndex]).Magnitude();
		if (head_distance <= tail_distance)
			generate_ascending = _true;
		else
			generate_ascending = _false;
	}

	if (generate_ascending) {
		// generate polygon1
		for (_dword i = 0; i <= head_min_distance_info.mVertexIndex; ++i)
			polygon1.mVertexArray.Append(mVertexArray[i]);
		for (_dword i = 0; i < divide_lines.Number(); ++i)
			polygon1.mVertexArray.Append(divide_lines[i]);
		for (_dword i = tail_min_distance_info.mVertexIndex + 1; i < mVertexArray.Number(); ++i)
			polygon1.mVertexArray.Append(mVertexArray[i]);

		// generate polygon2
		for (_dword i = head_min_distance_info.mVertexIndex + 1; i <= tail_min_distance_info.mVertexIndex; ++i)
			polygon2.mVertexArray.Append(mVertexArray[i]);
		for (_int i = (_int)divide_lines.Number() - 1; i >= 0; --i)
			polygon2.mVertexArray.Append(divide_lines[i]);
	} else {
		// generate polygon1
		for (_dword i = 0; i <= tail_min_distance_info.mVertexIndex; ++i)
			polygon1.mVertexArray.Append(mVertexArray[i]);
		for (_int i = (_int)divide_lines.Number() - 1; i >= 0; --i)
			polygon1.mVertexArray.Append(divide_lines[i]);
		for (_dword i = head_min_distance_info.mVertexIndex + 1; i < mVertexArray.Number(); ++i)
			polygon1.mVertexArray.Append(mVertexArray[i]);

		// generate polegon2
		for (_dword i = tail_min_distance_info.mVertexIndex + 1; i <= head_min_distance_info.mVertexIndex; ++i)
			polygon2.mVertexArray.Append(mVertexArray[i]);
		for (_dword i = 0; i < divide_lines.Number(); ++i)
			polygon2.mVertexArray.Append(divide_lines[i]);
	}

	polygon1.FixPolygon();
	polygon2.FixPolygon();

	return _true;
}

_void Polygon2D::FixPolygon() {
	if (mVertexArray.Number() <= 3)
		return;

	for (_dword i = 0; i < mVertexArray.Number(); ++i) {
		if (GetVertexType(i) == _FLAT)
			mVertexArray.RemoveByIndex(i--);
	}
}

_ubool Polygon2D::IsPointIn(const Vector2& point) {
	if (mVertexArray.Number() < 3)
		return _false;

	_dword cross_number = 0;
	for (_dword i = 0; i < mVertexArray.Number(); ++i) {
		_dword curr_index = i;
		_dword next_index = (i + 1) % mVertexArray.Number();

		const Vector2& p1 = mVertexArray[curr_index];
		const Vector2& p2 = mVertexArray[next_index];

		if (p1.y == p2.y)
			continue;

		if (point.y < Math::Min(p1.y, p2.y))
			continue;

		if (point.y >= Math::Max(p1.y, p2.y))
			continue;

		_float x = (point.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
		if (x > point.x)
			cross_number++;
	}

	return (cross_number % 2 == 1);
}

_ubool Polygon2D::GetCircleProgressPolygon(const Vector2& pos, const Vector2& size, const FloatRange& angle_range, Polygon2D& polygon) {
	polygon.mVertexArray.Clear();

	if (Math::Equal(Math::WrapPi(angle_range.mMinValue), Math::WrapPi(angle_range.mMaxValue)))
		return _false;

	Vector2 rotation1 = Vector2::cXAxis * Matrix2().Rotation(angle_range.mMaxValue);
	Vector2 rotation2 = Vector2::cXAxis * Matrix2().Rotation(angle_range.mMinValue);
	Line2D line1(Vector2::cOrigin, rotation1 * 100000.0f);
	Line2D line2(Vector2::cOrigin, rotation2 * 100000.0f);
	Vector2 points[] =
	    {
	        pos,
	        pos + Vector2(0.0f, size.y),
	        pos + size,
	        pos + Vector2(size.x, 0.0f)};
	Vector2 point1 = points[0];
	Vector2 point2 = points[0];
	_dword index1 = -1;
	_dword index2 = -1;
	for (_dword i = 0; i < 4; ++i) {
		Vector2 intersect_point;
		_dword next_index = i == 3 ? 0 : i + 1;
		Line2D line(points[i], points[next_index]);

		if (index1 == -1) {
			if (Intersection::Line2DVsLine2D(line, line1, &intersect_point)) {
				index1 = i;
				point1 = intersect_point;
			}
		}

		if (index2 == -1) {
			if (Intersection::Line2DVsLine2D(line, line2, &intersect_point)) {
				index2 = i;
				point2 = intersect_point;
			}
		}
	}

	polygon.mVertexArray.Append(point1);
	if (index1 == index2) {
		if ((point1 - points[index1]).MagnitudeSquared() > (point2 - points[index2]).MagnitudeSquared()) {
			_dword next_index1 = index1 == 3 ? 0 : index1 + 1;
			_dword count = 0;
			for (_dword i = next_index1; count < 4; ++count) {
				polygon.mVertexArray.Append(points[i]);

				i = i == 3 ? 0 : i + 1;
			}
		}
	} else {
		_dword next_index1 = index1 == 3 ? 0 : index1 + 1;
		_dword next_index2 = index2 == 3 ? 0 : index2 + 1;
		for (_dword i = next_index1; i != next_index2;) {
			polygon.mVertexArray.Append(points[i]);

			i = i == 3 ? 0 : i + 1;
		}
	}
	polygon.mVertexArray.Append(point2);
	polygon.mVertexArray.Append(Vector2::cOrigin);

	polygon.FixPolygon();

	return _true;
}

_ubool Polygon2D::GetCircleProgressPolygon(const Vector2& pos, const Vector2& size, const FloatRange& angle_range, Array<Triangle2D>& triangles) {
	Polygon2D polygon;
	if (GetCircleProgressPolygon(pos, size, angle_range, polygon) == _false)
		return _false;

	polygon.ToTriangleArray(triangles);

	return _true;
}
