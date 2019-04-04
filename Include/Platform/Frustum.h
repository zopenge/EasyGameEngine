#pragma once

namespace EGE {

/// <summary>
/// The frustum.
/// </summary>
class Frustum {
public:
	//! The identity Frustum.
	static const Frustum cIdentity;

public:
	Vector3 mVectors[8];
	Plane mPlanes[6];

public:
	Frustum();
	Frustum(const Matrix4& viewtransform, const Matrix4& projectiontransform);

public:
	//! Compare frustum.
	//! @param frustum  The frustum what you want to compare.
	//! @return True indicates it's equal.
	_ubool operator==(const Frustum& frustum) const;
	//! Compare frustum.
	//! @param frustum  The frustum what you want to compare.
	//! @return True indicates it's not equal.
	_ubool operator!=(const Frustum& frustum) const;

public:
	//! Get depth.
	//! @param none.
	//! @return The depth of frustum.
	_float Depth() const;

	//! Check whether box is in frustum or not.
	//! @param box   The box what you want to check.
	//! @return True indicates it's in the frustum.
	_ubool Inside(const Bounds& box) const;
	//! Check whether box is in frustum or not.
	//! @param box   The box what you want to check.
	//! @return True indicates it's in the frustum.
	_ubool Inside(const Box& box) const;
	//! Check whether line is in frustum or not.
	//! @param line  The line what you want to check.
	//! @return True indicates it's in the frustum.
	_ubool Inside(const Line3D& line) const;

	//! Check whether point is in frustum or not.
	//! @param line  The line what you want to check.
	//! @return True indicates it's in the frustum.
	_ubool Inside(const Vector3& point) const;

	//! Get the sub frustum.
	//! @param screensize The screen size
	//! @param subrect  The sub rect
	//! return  the sub frustum.
	Frustum SubFrustum(const PointI& screensize, const RectI& subrect) const;

	//! Get the Parallel plane
	//! @param point  A point in the plane.
	//! @return A plane parallel with the near plane.
	Plane ParallelPlane(const Vector3& point);
};

inline _ubool Frustum::operator==(const Frustum& frustum) const {
	return mPlanes[0] == frustum.mPlanes[0] && mPlanes[1] == frustum.mPlanes[1] && mPlanes[2] == frustum.mPlanes[2] && mPlanes[3] == frustum.mPlanes[3] && mPlanes[4] == frustum.mPlanes[4] && mPlanes[5] == frustum.mPlanes[5];
}

inline _ubool Frustum::operator!=(const Frustum& frustum) const {
	return mPlanes[0] != frustum.mPlanes[0] || mPlanes[1] != frustum.mPlanes[1] || mPlanes[2] != frustum.mPlanes[2] || mPlanes[3] != frustum.mPlanes[3] || mPlanes[4] != frustum.mPlanes[4] || mPlanes[5] != frustum.mPlanes[5];
}

inline _float Frustum::Depth() const {
	return Math::Abs(mPlanes[1].Distance(mVectors[0]));
}

} // namespace EGE