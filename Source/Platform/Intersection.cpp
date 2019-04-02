//! @file     Intersection.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Intersection Implementation
//----------------------------------------------------------------------------

_ubool Intersection::RectangleVSRectangle(const Vector2& lt, const Vector2& rb, const RectU& region) {
	if (rb.x < (_float)region.l)
		return _false;

	if (rb.y < (_float)region.t)
		return _false;

	if (lt.x > (_float)region.r)
		return _false;

	if (lt.y > (_float)region.b)
		return _false;

	return _true;
}

_ubool Intersection::PointVSRectangle(const Vector2& pos, const Vector2& size, const Matrix3& transform) {
	// Build the world transform
	Matrix3 world_transform = transform;

	// Get the local vector
	Vector2 local_vector;
	local_vector.x = pos.x - world_transform.m[2][0];
	local_vector.y = pos.y - world_transform.m[2][1];

	// Remove the translation from world transform
	world_transform.m[2][0] = 0.0f;
	world_transform.m[2][1] = 0.0f;

	// Get the size
	_float half_of_size_x = size.x / 2.0f;
	_float half_of_size_y = size.y / 2.0f;

	// The vector list
	Vector2 vectors[] =
	    {
	        Vector2(-half_of_size_x, half_of_size_y),
	        Vector2(half_of_size_x, half_of_size_y),
	        Vector2(half_of_size_x, -half_of_size_y),
	        Vector2(-half_of_size_x, -half_of_size_y),
	    };

	// The normals vector list
	Vector2 normals[] =
	    {
	        Vector2(0.0f, 1.0f),
	        Vector2(1.0f, 0.0f),
	        Vector2(0.0f, -1.0f),
	        Vector2(-1.0f, 0.0f)};

	// Test the position
	for (_dword i = 0; i < EGE_ARRAY_NUMBER(normals); i++) {
		normals[i] *= world_transform;
		normals[i].Normalize();

		_float dot = Vector2::Dot(normals[i], (local_vector - vectors[i] * world_transform).Normalize());
		if (dot > 0.0f)
			return _false;
	}

	return _true;
}

_ubool Intersection::Line2DVsLine2D(const Line2D& line1, const Line2D& line2, Vector2* intersect_point) {
	Vector2 n1(line1.mPoints[1].y - line1.mPoints[0].y, line1.mPoints[0].x - line1.mPoints[1].x);
	Vector2 n2(line2.mPoints[1].y - line2.mPoints[0].y, line2.mPoints[0].x - line2.mPoints[1].x);

	_float denominator = Vector2::Cross(n1, n2);
	if (denominator == 0.0f) {
		//
		return _false;
	}

	_float distc_n2 = Vector2::Dot(n2, line2.mPoints[0]);
	_float dista_n2 = Vector2::Dot(n2, line1.mPoints[0]) - distc_n2;
	_float distb_n2 = Vector2::Dot(n2, line1.mPoints[1]) - distc_n2;

	if (dista_n2 * distb_n2 > 0.0f)
		return _false;

	_float dista_n1 = Vector2::Dot(n1, line1.mPoints[0]);
	_float distc_n1 = Vector2::Dot(n1, line2.mPoints[0]) - dista_n1;
	_float distd_n1 = Vector2::Dot(n1, line2.mPoints[1]) - dista_n1;

	if (distc_n1 * distd_n1 > 0.0f)
		return _false;

	if (intersect_point != _null) {
		_float fraction = dista_n2 / denominator;
		intersect_point->x = line1.mPoints[0].x + fraction * n1.y;
		intersect_point->y = line1.mPoints[0].y - fraction * n1.x;
	}

	return _true;
}

_float Intersection::IntervalDistance(_float minA, _float maxA, _float minB, _float maxB) {
	if (minA < minB)
		return minB - maxA;
	else
		return minA - maxB;
}

void Intersection::ProjectPolygon(const Vector2& axis, const Vector2 polygon[], _dword length, _float& min, _float& max) {
	// To project a point on an axis use the dot product
	_float dotProduct = Vector2::Dot(axis, polygon[0]);
	min = dotProduct;
	max = dotProduct;
	for (_dword i = 0; i < length; i++) {
		dotProduct = Vector2::Dot(polygon[i], axis);
		if (dotProduct < min) {
			min = dotProduct;
		} else {
			if (dotProduct > max) {
				max = dotProduct;
			}
		}
	}
}

PolygonCollisionResult Intersection::Polygon2DVSPolygon2D(const Vector2 polygon1[], _dword length1, const Vector2 polygon2[], _dword length2, const Vector2& velocity) {
	PolygonCollisionResult result;
	result.mIntersect = _true;
	result.mWillIntersect = _true;
	result.mMinimumTranslationVector = Vector2::cOrigin;

	_float minIntervalDistance = Math::cMaxFloat;
	Vector2 edge(Vector2::cOrigin);
	Vector2 translationAxis(Vector2::cOrigin);
	Vector2 centerA(Vector2::cOrigin);
	Vector2 centerB(Vector2::cOrigin);

	for (_dword i = 0; i < length1; ++i)
		centerA += polygon1[i];
	centerA /= (_float)length1;

	for (_dword i = 0; i < length2; ++i)
		centerB += polygon2[i];
	centerB /= (_float)length2;

	// Loop through all the edges of both polygons
	for (_dword i = 0; i < length1 + length2; ++i) {
		if (i < length1) {
			if (i == length1 - 1)
				edge = polygon1[0] - polygon1[i];
			else
				edge = polygon1[i + 1] - polygon1[i];
		} else {
			if (i == length1 + length2 - 1)
				edge = polygon2[0] - polygon2[i - length1];
			else
				edge = polygon2[i - length1 + 1] - polygon2[i - length1];
		}

		// ===== 1. Find if the polygons are currently intersecting =====
		// Find the axis perpendicular to the current edge
		Vector2 axis(-edge.y, edge.x);
		axis.Normalize();

		// Find the projection of the polygon on the current axis
		_float minA = 0;
		_float minB = 0;
		_float maxA = 0;
		_float maxB = 0;
		ProjectPolygon(axis, polygon1, length1, minA, maxA);
		ProjectPolygon(axis, polygon2, length2, minB, maxB);

		// Check if the polygon projections are currentlty intersecting
		if (IntervalDistance(minA, maxA, minB, maxB) > 0)
			result.mIntersect = _false;

		// ===== 2. Now find if the polygons *will* intersect =====

		// Project the velocity on the current axis
		_float velocityProjection = Vector2::Dot(axis, velocity);

		// Get the projection of polygon A during the movement
		if (velocityProjection < 0)
			minA += velocityProjection;
		else
			maxA += velocityProjection;

		// Do the same test as above for the new projection
		_float intervalDistance = IntervalDistance(minA, maxA, minB, maxB);
		if (intervalDistance > 0)
			result.mWillIntersect = _false;

		// If the polygons are not intersecting and won't intersect, exit the loop
		if (!result.mIntersect && !result.mWillIntersect)
			break;

		// Check if the current interval distance is the minimum one. If so store
		// the interval distance and the current distance.
		// This will be used to calculate the minimum translation vector
		intervalDistance = Math::Abs(intervalDistance);
		if (intervalDistance < minIntervalDistance) {
			minIntervalDistance = intervalDistance;
			translationAxis = axis;

			Vector2 d = centerA - centerB;
			if (Vector2::Dot(d, translationAxis) < 0)
				translationAxis = -translationAxis;
		}
	}

	// The minimum translation vector
	// can be used to push the polygons appart.
	if (result.mWillIntersect)
		result.mMinimumTranslationVector = translationAxis * minIntervalDistance;

	return result;
}

_ubool Intersection::RayVSPlane(const Ray& ray, const Plane& plane, _float* distance) {
	_float dotvalue = Vector3::Dot(plane.Normal(), ray.mDirection);

	if (Math::Abs(dotvalue) < Math::cFloatEpsilon)
		return _false;

	_float tempdistance = plane.Distance(ray.mOrigin) / -dotvalue;

	if (tempdistance < 0.0f)
		return _false;

	if (distance != _null)
		*distance = tempdistance;

	return _true;
}

_ubool Intersection::RayVSTriangle(const Ray& ray, const Triangle& triangle, _float* distance) {
	Vector3 edge1 = triangle.mVector2 - triangle.mVector1;
	Vector3 edge2 = triangle.mVector3 - triangle.mVector1;

	Vector3 tvec, pvec = Vector3::Cross(ray.mDirection, edge2);

	_float det = Vector3::Dot(edge1, pvec);

	if (det >= 0.0f) {
		tvec = ray.mOrigin - triangle.mVector1;
	} else {
		tvec = triangle.mVector1 - ray.mOrigin;
		det = -det;
	}

	if (det < Math::cFloatEpsilon)
		return _false;

	_float u = Vector3::Dot(tvec, pvec);
	if (u < 0.0f || u > det)
		return _false;

	Vector3 qvec = Vector3::Cross(tvec, edge1);

	_float v = Vector3::Dot(ray.mDirection, qvec);
	if (v < 0.0f || u + v > det)
		return _false;

	if (distance != _null)
		*distance = Vector3::Dot(edge2, qvec) / det;

	return _true;
}

_ubool Intersection::RayVSBox(const Ray& ray, const Box& box, _float* distance) {
	if (ray.mOrigin.x >= box.mVectors[0].x && ray.mOrigin.x <= box.mVectors[7].x &&
	    ray.mOrigin.y >= box.mVectors[0].y && ray.mOrigin.y <= box.mVectors[7].y &&
	    ray.mOrigin.z >= box.mVectors[0].z && ray.mOrigin.z <= box.mVectors[7].z) {
		if (distance != _null)
			*distance = 0.0f;

		return _true;
	}

	_float tempdistance1 = 0.0f, tempdistance2 = -1.0f;

	if (RayVSTriangle(ray, Triangle(box.mVectors[0], box.mVectors[1], box.mVectors[2]), &tempdistance1) == _true && (tempdistance2 < 0.0f || tempdistance2 > tempdistance1))
		tempdistance2 = tempdistance1;
	if (RayVSTriangle(ray, Triangle(box.mVectors[2], box.mVectors[1], box.mVectors[3]), &tempdistance1) == _true && (tempdistance2 < 0.0f || tempdistance2 > tempdistance1))
		tempdistance2 = tempdistance1;

	if (RayVSTriangle(ray, Triangle(box.mVectors[4], box.mVectors[6], box.mVectors[5]), &tempdistance1) == _true && (tempdistance2 < 0.0f || tempdistance2 > tempdistance1))
		tempdistance2 = tempdistance1;
	if (RayVSTriangle(ray, Triangle(box.mVectors[5], box.mVectors[6], box.mVectors[7]), &tempdistance1) == _true && (tempdistance2 < 0.0f || tempdistance2 > tempdistance1))
		tempdistance2 = tempdistance1;

	if (RayVSTriangle(ray, Triangle(box.mVectors[4], box.mVectors[5], box.mVectors[0]), &tempdistance1) == _true && (tempdistance2 < 0.0f || tempdistance2 > tempdistance1))
		tempdistance2 = tempdistance1;
	if (RayVSTriangle(ray, Triangle(box.mVectors[0], box.mVectors[5], box.mVectors[1]), &tempdistance1) == _true && (tempdistance2 < 0.0f || tempdistance2 > tempdistance1))
		tempdistance2 = tempdistance1;

	if (RayVSTriangle(ray, Triangle(box.mVectors[1], box.mVectors[5], box.mVectors[4]), &tempdistance1) == _true && (tempdistance2 < 0.0f || tempdistance2 > tempdistance1))
		tempdistance2 = tempdistance1;
	if (RayVSTriangle(ray, Triangle(box.mVectors[4], box.mVectors[5], box.mVectors[7]), &tempdistance1) == _true && (tempdistance2 < 0.0f || tempdistance2 > tempdistance1))
		tempdistance2 = tempdistance1;

	if (RayVSTriangle(ray, Triangle(box.mVectors[2], box.mVectors[3], box.mVectors[6]), &tempdistance1) == _true && (tempdistance2 < 0.0f || tempdistance2 > tempdistance1))
		tempdistance2 = tempdistance1;
	if (RayVSTriangle(ray, Triangle(box.mVectors[6], box.mVectors[3], box.mVectors[7]), &tempdistance1) == _true && (tempdistance2 < 0.0f || tempdistance2 > tempdistance1))
		tempdistance2 = tempdistance1;

	if (RayVSTriangle(ray, Triangle(box.mVectors[4], box.mVectors[0], box.mVectors[6]), &tempdistance1) == _true && (tempdistance2 < 0.0f || tempdistance2 > tempdistance1))
		tempdistance2 = tempdistance1;
	if (RayVSTriangle(ray, Triangle(box.mVectors[6], box.mVectors[0], box.mVectors[2]), &tempdistance1) == _true && (tempdistance2 < 0.0f || tempdistance2 > tempdistance1))
		tempdistance2 = tempdistance1;

	if (tempdistance2 < 0.0f)
		return _false;

	if (distance != _null)
		*distance = tempdistance2;

	return _true;
}

_ubool Intersection::RayVSAABox(const Ray& ray, const Bounds& box, _float* distance) {
	if (distance != _null)
		return RayVSBox(ray, Box(box.mMinVector, box.mMaxVector), distance);

	if (ray.mDirection.x < 0) {
		if (ray.mDirection.y < 0) {
			if (ray.mDirection.z < 0) {
				if ((ray.mOrigin.x < box.mMinVector.x) || (ray.mOrigin.y < box.mMinVector.y) || (ray.mOrigin.z < box.mMinVector.z))
					return _false;

				_float xa = box.mMinVector.x - ray.mOrigin.x;
				_float ya = box.mMinVector.y - ray.mOrigin.y;
				_float za = box.mMinVector.z - ray.mOrigin.z;
				_float xb = box.mMaxVector.x - ray.mOrigin.x;
				_float yb = box.mMaxVector.y - ray.mOrigin.y;
				_float zb = box.mMaxVector.z - ray.mOrigin.z;

				if ((ray.mDirection.x * ya - ray.mDirection.y * xb < 0) ||
				    (ray.mDirection.x * yb - ray.mDirection.y * xa > 0) ||
				    (ray.mDirection.x * zb - ray.mDirection.z * xa > 0) ||
				    (ray.mDirection.x * za - ray.mDirection.z * xb < 0) ||
				    (ray.mDirection.y * za - ray.mDirection.z * yb < 0) ||
				    (ray.mDirection.y * zb - ray.mDirection.z * ya > 0))
					return _false;

				return _true;
			} else {
				if ((ray.mOrigin.x < box.mMinVector.x) || (ray.mOrigin.y < box.mMinVector.y) || (ray.mOrigin.z > box.mMaxVector.z))
					return _false;

				_float xa = box.mMinVector.x - ray.mOrigin.x;
				_float ya = box.mMinVector.y - ray.mOrigin.y;
				_float za = box.mMinVector.z - ray.mOrigin.z;
				_float xb = box.mMaxVector.x - ray.mOrigin.x;
				_float yb = box.mMaxVector.y - ray.mOrigin.y;
				_float zb = box.mMaxVector.z - ray.mOrigin.z;

				if ((ray.mDirection.x * ya - ray.mDirection.y * xb < 0) ||
				    (ray.mDirection.x * yb - ray.mDirection.y * xa > 0) ||
				    (ray.mDirection.x * zb - ray.mDirection.z * xb > 0) ||
				    (ray.mDirection.x * za - ray.mDirection.z * xa < 0) ||
				    (ray.mDirection.y * za - ray.mDirection.z * ya < 0) ||
				    (ray.mDirection.y * zb - ray.mDirection.z * yb > 0))
					return _false;

				return _true;
			}
		} else {
			if (ray.mDirection.z < 0) {
				if ((ray.mOrigin.x < box.mMinVector.x) || (ray.mOrigin.y > box.mMaxVector.y) || (ray.mOrigin.z < box.mMinVector.z))
					return _false;

				_float xa = box.mMinVector.x - ray.mOrigin.x;
				_float ya = box.mMinVector.y - ray.mOrigin.y;
				_float za = box.mMinVector.z - ray.mOrigin.z;
				_float xb = box.mMaxVector.x - ray.mOrigin.x;
				_float yb = box.mMaxVector.y - ray.mOrigin.y;
				_float zb = box.mMaxVector.z - ray.mOrigin.z;

				if ((ray.mDirection.x * ya - ray.mDirection.y * xa < 0) ||
				    (ray.mDirection.x * yb - ray.mDirection.y * xb > 0) ||
				    (ray.mDirection.x * zb - ray.mDirection.z * xa > 0) ||
				    (ray.mDirection.x * za - ray.mDirection.z * xb < 0) ||
				    (ray.mDirection.y * zb - ray.mDirection.z * yb < 0) ||
				    (ray.mDirection.y * za - ray.mDirection.z * ya > 0))
					return _false;

				return _true;
			} else {
				if ((ray.mOrigin.x < box.mMinVector.x) || (ray.mOrigin.y > box.mMaxVector.y) || (ray.mOrigin.z > box.mMaxVector.z))
					return _false;

				_float xa = box.mMinVector.x - ray.mOrigin.x;
				_float ya = box.mMinVector.y - ray.mOrigin.y;
				_float za = box.mMinVector.z - ray.mOrigin.z;
				_float xb = box.mMaxVector.x - ray.mOrigin.x;
				_float yb = box.mMaxVector.y - ray.mOrigin.y;
				_float zb = box.mMaxVector.z - ray.mOrigin.z;

				if ((ray.mDirection.x * ya - ray.mDirection.y * xa < 0) ||
				    (ray.mDirection.x * yb - ray.mDirection.y * xb > 0) ||
				    (ray.mDirection.x * zb - ray.mDirection.z * xb > 0) ||
				    (ray.mDirection.x * za - ray.mDirection.z * xa < 0) ||
				    (ray.mDirection.y * zb - ray.mDirection.z * ya < 0) ||
				    (ray.mDirection.y * za - ray.mDirection.z * yb > 0))
					return _false;

				return _true;
			}
		}
	} else {
		if (ray.mDirection.y < 0) {
			if (ray.mDirection.z < 0) {
				if ((ray.mOrigin.x > box.mMaxVector.x) || (ray.mOrigin.y < box.mMinVector.y) || (ray.mOrigin.z < box.mMinVector.z))
					return _false;

				_float xa = box.mMinVector.x - ray.mOrigin.x;
				_float ya = box.mMinVector.y - ray.mOrigin.y;
				_float za = box.mMinVector.z - ray.mOrigin.z;
				_float xb = box.mMaxVector.x - ray.mOrigin.x;
				_float yb = box.mMaxVector.y - ray.mOrigin.y;
				_float zb = box.mMaxVector.z - ray.mOrigin.z;

				if ((ray.mDirection.x * yb - ray.mDirection.y * xb < 0) ||
				    (ray.mDirection.x * ya - ray.mDirection.y * xa > 0) ||
				    (ray.mDirection.x * za - ray.mDirection.z * xa > 0) ||
				    (ray.mDirection.x * zb - ray.mDirection.z * xb < 0) ||
				    (ray.mDirection.y * za - ray.mDirection.z * yb < 0) ||
				    (ray.mDirection.y * zb - ray.mDirection.z * ya > 0))
					return _false;

				return _true;
			} else {
				if ((ray.mOrigin.x > box.mMaxVector.x) || (ray.mOrigin.y < box.mMinVector.y) || (ray.mOrigin.z > box.mMaxVector.z))
					return _false;

				_float xa = box.mMinVector.x - ray.mOrigin.x;
				_float ya = box.mMinVector.y - ray.mOrigin.y;
				_float za = box.mMinVector.z - ray.mOrigin.z;
				_float xb = box.mMaxVector.x - ray.mOrigin.x;
				_float yb = box.mMaxVector.y - ray.mOrigin.y;
				_float zb = box.mMaxVector.z - ray.mOrigin.z;

				if ((ray.mDirection.x * yb - ray.mDirection.y * xb < 0) ||
				    (ray.mDirection.x * ya - ray.mDirection.y * xa > 0) ||
				    (ray.mDirection.x * za - ray.mDirection.z * xb > 0) ||
				    (ray.mDirection.x * zb - ray.mDirection.z * xa < 0) ||
				    (ray.mDirection.y * za - ray.mDirection.z * ya < 0) ||
				    (ray.mDirection.y * zb - ray.mDirection.z * yb > 0))
					return _false;

				return _true;
			}
		} else {
			if (ray.mDirection.z < 0) {
				if ((ray.mOrigin.x > box.mMaxVector.x) || (ray.mOrigin.y > box.mMaxVector.y) || (ray.mOrigin.z < box.mMinVector.z))
					return _false;

				_float xa = box.mMinVector.x - ray.mOrigin.x;
				_float ya = box.mMinVector.y - ray.mOrigin.y;
				_float za = box.mMinVector.z - ray.mOrigin.z;
				_float xb = box.mMaxVector.x - ray.mOrigin.x;
				_float yb = box.mMaxVector.y - ray.mOrigin.y;
				_float zb = box.mMaxVector.z - ray.mOrigin.z;

				if ((ray.mDirection.x * yb - ray.mDirection.y * xa < 0) ||
				    (ray.mDirection.x * ya - ray.mDirection.y * xb > 0) ||
				    (ray.mDirection.x * za - ray.mDirection.z * xa > 0) ||
				    (ray.mDirection.x * zb - ray.mDirection.z * xb < 0) ||
				    (ray.mDirection.y * zb - ray.mDirection.z * yb < 0) ||
				    (ray.mDirection.y * za - ray.mDirection.z * ya > 0))
					return _false;

				return _true;
			} else {
				if ((ray.mOrigin.x > box.mMaxVector.x) || (ray.mOrigin.y > box.mMaxVector.y) || (ray.mOrigin.z > box.mMaxVector.z))
					return _false;

				_float xa = box.mMinVector.x - ray.mOrigin.x;
				_float ya = box.mMinVector.y - ray.mOrigin.y;
				_float za = box.mMinVector.z - ray.mOrigin.z;
				_float xb = box.mMaxVector.x - ray.mOrigin.x;
				_float yb = box.mMaxVector.y - ray.mOrigin.y;
				_float zb = box.mMaxVector.z - ray.mOrigin.z;

				if ((ray.mDirection.x * yb - ray.mDirection.y * xa < 0) ||
				    (ray.mDirection.x * ya - ray.mDirection.y * xb > 0) ||
				    (ray.mDirection.x * za - ray.mDirection.z * xb > 0) ||
				    (ray.mDirection.x * zb - ray.mDirection.z * xa < 0) ||
				    (ray.mDirection.y * zb - ray.mDirection.z * ya < 0) ||
				    (ray.mDirection.y * za - ray.mDirection.z * yb > 0))
					return _false;

				return _true;
			}
		}
	}

	return _false;
}

_ubool Intersection::RayVSMesh(const Ray& ray, _dword stride, _dword vertex_number, const _byte* vertex_buffer, _dword index_number, const _word* index_buffer, _float* distance) {
	if (stride == 0 || vertex_number == 0 || vertex_buffer == _null)
		return _false;

	_float nearest = -1.0f;

	// No index.
	if (index_buffer == _null) {
		for (_dword i = 0; i < vertex_number; i += 3) {
			_dword a = i + 0;
			_dword b = i + 1;
			_dword c = i + 2;

			const Vector3* vector1 = (const Vector3*)(vertex_buffer + a * stride);
			const Vector3* vector2 = (const Vector3*)(vertex_buffer + b * stride);
			const Vector3* vector3 = (const Vector3*)(vertex_buffer + c * stride);

			Triangle triangle(*vector1, *vector2, *vector3);

			_float temp_distance = 0.0f;
			if (Intersection::RayVSTriangle(ray, triangle, &temp_distance)) {
				if (nearest < 0.0f || nearest > temp_distance)
					nearest = temp_distance;
			}
		}
	} else {
		for (_dword i = 0; i < index_number; i += 3) {
			_dword a = index_buffer[i + 0];
			_dword b = index_buffer[i + 1];
			_dword c = index_buffer[i + 2];

			const Vector3* vector1 = (const Vector3*)(vertex_buffer + a * stride);
			const Vector3* vector2 = (const Vector3*)(vertex_buffer + b * stride);
			const Vector3* vector3 = (const Vector3*)(vertex_buffer + c * stride);

			Triangle triangle(*vector1, *vector2, *vector3);

			_float temp_distance = 0.0f;
			if (Intersection::RayVSTriangle(ray, triangle, &temp_distance)) {
				if (nearest < 0.0f || nearest > temp_distance)
					nearest = temp_distance;
			}
		}
	}

	if (distance != _null && nearest >= 0.0f)
		*distance = nearest;

	return nearest >= 0.0f;
}

_ubool Intersection::OBBoxVSOBBox(const ColliderBox2D& box1, const ColliderBox2D& box2) {
	return box1.Overlaps1Way(box2) && box2.Overlaps1Way(box1);
}

_ubool Intersection::AABoxVSAABox(const Bounds& box1, const Bounds& box2) {
	_float x1 = Math::Max(box1.mMinVector.x, box2.mMinVector.x);
	if (x1 >= box1.mMaxVector.x || x1 >= box2.mMaxVector.x)
		return _false;

	_float x2 = Math::Min(box1.mMaxVector.x, box2.mMaxVector.x);
	if (x2 <= box1.mMinVector.x || x2 <= box2.mMinVector.x)
		return _false;

	_float y1 = Math::Max(box1.mMinVector.y, box2.mMinVector.y);
	if (y1 >= box1.mMaxVector.y || y1 >= box2.mMaxVector.y)
		return _false;

	_float y2 = Math::Min(box1.mMaxVector.y, box2.mMaxVector.y);
	if (y2 <= box1.mMinVector.y || y2 <= box2.mMinVector.y)
		return _false;

	_float z1 = Math::Max(box1.mMinVector.z, box2.mMinVector.z);
	if (z1 >= box1.mMaxVector.z || z1 >= box2.mMaxVector.z)
		return _false;

	_float z2 = Math::Min(box1.mMaxVector.z, box2.mMaxVector.z);
	if (z2 <= box1.mMinVector.z || z2 <= box2.mMinVector.z)
		return _false;

	return _true;
}

_ubool Intersection::AABoxVSPlane(const Bounds& box, const Plane& plane) {
	_float d1 = plane.Distance(Vector3(box.mMinVector.x, box.mMinVector.y, box.mMinVector.z));
	_float d2 = plane.Distance(Vector3(box.mMaxVector.x, box.mMaxVector.y, box.mMaxVector.z));

	_float t = d1 * d2;
	if (t <= Math::cFloatEpsilon)
		return _true;

	t *= plane.Distance(Vector3(box.mMaxVector.x, box.mMinVector.y, box.mMinVector.z));
	if (t <= Math::cFloatEpsilon)
		return _true;

	t *= plane.Distance(Vector3(box.mMinVector.x, box.mMaxVector.y, box.mMinVector.z));
	if (t <= Math::cFloatEpsilon)
		return _true;

	t *= plane.Distance(Vector3(box.mMaxVector.x, box.mMaxVector.y, box.mMinVector.z));
	if (t <= Math::cFloatEpsilon)
		return _true;

	t *= plane.Distance(Vector3(box.mMinVector.x, box.mMinVector.y, box.mMaxVector.z));
	if (t <= Math::cFloatEpsilon)
		return _true;

	t *= plane.Distance(Vector3(box.mMaxVector.x, box.mMinVector.y, box.mMaxVector.z));
	if (t <= Math::cFloatEpsilon)
		return _true;

	t *= plane.Distance(Vector3(box.mMinVector.x, box.mMaxVector.y, box.mMaxVector.z));
	if (t <= Math::cFloatEpsilon)
		return _true;

	return _false;
}

_ubool Intersection::AABoxVSSphere(const Bounds& box, const Sphere& sphere) {
	Vector3 closestPointInAabb = Vector3::Min(Vector3::Max(sphere.mCenter, box.mMinVector), box.mMaxVector);
	_float distanceSquard = (closestPointInAabb - sphere.mCenter).MagnitudeSquared();
	return distanceSquard < (sphere.mRadius * sphere.mRadius);
}

_ubool Intersection::SphereVSSphere(const Sphere& sphere1, const Sphere& sphere2) {
	return Math::Abs(sphere1.mRadius) + Math::Abs(sphere2.mRadius) > Vector3(sphere1.mCenter - sphere2.mCenter).Magnitude();
}

_ubool Intersection::SphereVSPlane(const Sphere& sphere, const Plane& plane) {
	return Math::Abs(plane.Distance(sphere.mCenter)) <= Math::Abs(sphere.mRadius);
}

_ubool Intersection::SphereVSBox(const Sphere& sphere, const Box& box) {
	//
	return _false;
}

_ubool Intersection::BoxVSBox(const Box& box1, const Box& box2) {
	Vector3 axis[15];
	// box1's
	axis[0] = box1.mVectors[1] - box1.mVectors[0];
	axis[1] = box1.mVectors[2] - box1.mVectors[0];
	axis[2] = box1.mVectors[4] - box1.mVectors[0];
	// box2's
	axis[3] = box2.mVectors[1] - box2.mVectors[0];
	axis[4] = box2.mVectors[2] - box2.mVectors[0];
	axis[5] = box2.mVectors[4] - box2.mVectors[0];
	// box1 & box2 's
	for (_dword i = 0; i < 3; ++i) {
		for (_dword j = 0; j < 3; ++j) {
			axis[6 + i * 3 + j] = Vector3::Cross(axis[i], axis[j]);
		}
	}

	for (_dword i = 0; i < 15; ++i) {
		if (SeperateAxisTesting(axis[i], box1.mVectors, 8, box2.mVectors, 8) == _true)
			return _false;
	}

	return _true;
}

_ubool Intersection::SeperateAxisTesting(const Vector3& sperateaxis, const Vector3 polygon1[], _dword length1, const Vector3 polygon2[], _dword length2) {
	_float value1, value2, min1, max1, min2, max2;

	for (_dword i = 0; i < length1; ++i) {
		value1 = Vector3::Dot(sperateaxis, polygon1[i]);
		if (i == 0) {
			min1 = max1 = value1;
		} else {
			min1 = Math::Min(min1, value1);
			max1 = Math::Max(max1, value1);
		}
	}
	for (_dword i = 0; i < length2; ++i) {
		value2 = Vector3::Dot(sperateaxis, polygon2[i]);
		if (i == 0) {
			min2 = max2 = value2;
		} else {
			min2 = Math::Min(min2, value2);
			max2 = Math::Max(max2, value2);
		}
	}

	if (max1 < min2 || max2 < min1)
		return _true;

	return _false;
}

_ubool Intersection::SeperateAxisTesting(const Vector2& sperateaxis, const Vector2 polygon1[], _dword length1, const Vector2 polygon2[], _dword length2) {
	_float value1, value2, min1, max1, min2, max2;

	for (_dword i = 0; i < length1; ++i) {
		value1 = Vector2::Dot(sperateaxis, polygon1[i]);
		if (i == 0) {
			min1 = max1 = value1;
		} else {
			min1 = Math::Min(min1, value1);
			max1 = Math::Max(max1, value1);
		}
	}
	for (_dword i = 0; i < length2; ++i) {
		value2 = Vector2::Dot(sperateaxis, polygon2[i]);
		if (i == 0) {
			min2 = max2 = value2;
		} else {
			min2 = Math::Min(min2, value2);
			max2 = Math::Max(max2, value2);
		}
	}

	if (max1 < min2 || max2 < min1)
		return _true;

	return _false;
}