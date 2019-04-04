#pragma once

namespace EGE {

/// <summary>
/// The raycaster.
/// </summary>
class Ray {
public:
	//! The null ray.
	static const Ray cNull;

public:
	Vector3 mOrigin;
	Vector3 mDirection;

public:
	Ray();
	Ray(_float x, _float y, _float z, _float i, _float j, _float k);
	Ray(const Vector3& origin, const Vector3& direction);
	Ray(_float x, _float y, const Matrix4& viewtransform,
	    const Matrix4& projectiontransform);

public:
	_ubool operator==(const Ray& ray) const;
	_ubool operator!=(const Ray& ray) const;

	Ray& operator*=(const Matrix4& matrix);
	Ray operator*(const Matrix4& matrix) const;

public:
	_ubool Equal(const Ray& ray, _float margin = Math::cFloatEpsilon) const;

	Vector3 DistanceVector(_float distance) const;

public:
	//! Get the pick ray.
	//! @param x						The screen
	//! x-position.
	//! @param y						The screen
	//! y-position.
	//! @param viewport_size			The viewport size.
	//! @param view_transform			The view transform.
	//! @param projection_transform	The projection transform.
	//! @return The pick ray.
	static Ray GetPickRay(_int x, _int y, const PointU& viewport_size,
	                      const Matrix4& view_transform,
	                      const Matrix4& projection_transform);
	static Ray GetPickRay(_float x, _float y, _float sizex, _float sizey,
	                      const Matrix4& view_transform,
	                      const Matrix4& projection_transform);
};

inline _ubool Ray::operator==(const Ray& ray) const {
	return mOrigin == ray.mOrigin && mDirection == ray.mDirection;
}

inline _ubool Ray::operator!=(const Ray& ray) const {
	return mOrigin != ray.mOrigin || mDirection != ray.mDirection;
}

inline Ray& Ray::operator*=(const Matrix4& matrix) {
	mOrigin *= matrix;
	mDirection = Vector4(mDirection, 0.0f) * matrix;

	return *this;
}

inline Ray Ray::operator*(const Matrix4& matrix) const {
	return Ray(mOrigin * matrix, Vector4(mDirection, 0.0f) * matrix);
}

inline _ubool Ray::Equal(const Ray& ray, _float margin) const {
	return mOrigin.Equal(ray.mOrigin) && mDirection.Equal(ray.mDirection);
}

inline Vector3 Ray::DistanceVector(_float distance) const {
	return mOrigin + mDirection * distance;
}

} // namespace EGE