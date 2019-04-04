#include "EGEPlatform.h"

const Frustum Frustum::cIdentity(
    Matrix4(1.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0, 0.0f, 0.0f, 0.0f, 0.0, 1.0f, 0.0f, 0.0f, 0.0, 0.0f, 1.0f),
    Matrix4(1.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0, 0.0f, 0.0f, 0.0f, 0.0, 1.0f, 0.0f, 0.0f, 0.0, 0.0f, 1.0f));

Frustum::Frustum() {
}

Frustum::Frustum(const Matrix4& viewtransform, const Matrix4& projectiontransform) {
	Matrix4 inversematrix = viewtransform * projectiontransform;
	inversematrix.Inverse();

	mVectors[0] = Vector3(-1.0f, -1.0f, 0.0f) * inversematrix;
	mVectors[1] = Vector3(-1.0f, 1.0f, 0.0f) * inversematrix;
	mVectors[2] = Vector3(1.0f, 1.0f, 0.0f) * inversematrix;
	mVectors[3] = Vector3(1.0f, -1.0f, 0.0f) * inversematrix;
	mVectors[4] = Vector3(-1.0f, -1.0f, 1.0f) * inversematrix;
	mVectors[5] = Vector3(-1.0f, 1.0f, 1.0f) * inversematrix;
	mVectors[6] = Vector3(1.0f, 1.0f, 1.0f) * inversematrix;
	mVectors[7] = Vector3(1.0f, -1.0f, 1.0f) * inversematrix;

	mPlanes[0] = Plane(mVectors[0], mVectors[1], mVectors[2]); // Near
	mPlanes[1] = Plane(mVectors[5], mVectors[7], mVectors[6]); // Far
	mPlanes[2] = Plane(mVectors[1], mVectors[4], mVectors[5]); // Left
	mPlanes[3] = Plane(mVectors[6], mVectors[7], mVectors[2]); // Right
	mPlanes[4] = Plane(mVectors[1], mVectors[5], mVectors[2]); // Top
	mPlanes[5] = Plane(mVectors[3], mVectors[4], mVectors[0]); // Bottom
}

Frustum Frustum::SubFrustum(const PointI& screensize, const RectI& subrect) const {
	Frustum subfrustum(*this);

	Vector3 vecx = mVectors[5] - mVectors[6];
	Vector3 vecy = mVectors[7] - mVectors[6];
	subfrustum.mVectors[6] += vecx * (_float(subrect.l) / _float(screensize.x));
	subfrustum.mVectors[6] += vecy * (_float(subrect.t) / _float(screensize.y));
	subfrustum.mVectors[5] = subfrustum.mVectors[6] + vecx * (_float(subrect.GetWidth()) / _float(screensize.x));
	subfrustum.mVectors[7] = subfrustum.mVectors[6] + vecy * (_float(subrect.GetHeight()) / _float(screensize.y));
	subfrustum.mVectors[4] = subfrustum.mVectors[5] + vecy * (_float(subrect.GetHeight()) / _float(screensize.y));

	vecx = mVectors[1] - mVectors[2];
	vecy = mVectors[3] - mVectors[2];
	subfrustum.mVectors[2] += vecx * (_float(subrect.l) / _float(screensize.x));
	subfrustum.mVectors[2] += vecy * (_float(subrect.t) / _float(screensize.y));
	subfrustum.mVectors[1] = subfrustum.mVectors[2] + vecx * (_float(subrect.GetWidth()) / _float(screensize.x));
	subfrustum.mVectors[3] = subfrustum.mVectors[2] + vecy * (_float(subrect.GetHeight()) / _float(screensize.y));
	subfrustum.mVectors[0] = subfrustum.mVectors[1] + vecy * (_float(subrect.GetHeight()) / _float(screensize.y));

	subfrustum.mPlanes[0] = Plane(subfrustum.mVectors[0], subfrustum.mVectors[1], subfrustum.mVectors[2]); // Near
	subfrustum.mPlanes[1] = Plane(subfrustum.mVectors[5], subfrustum.mVectors[7], subfrustum.mVectors[6]); // Far
	subfrustum.mPlanes[2] = Plane(subfrustum.mVectors[1], subfrustum.mVectors[4], subfrustum.mVectors[5]); // Left
	subfrustum.mPlanes[3] = Plane(subfrustum.mVectors[6], subfrustum.mVectors[7], subfrustum.mVectors[2]); // Right
	subfrustum.mPlanes[4] = Plane(subfrustum.mVectors[1], subfrustum.mVectors[5], subfrustum.mVectors[2]); // Top
	subfrustum.mPlanes[5] = Plane(subfrustum.mVectors[3], subfrustum.mVectors[4], subfrustum.mVectors[0]); // Bottom

	return subfrustum;
}

_ubool Frustum::Inside(const Bounds& box) const {
	Vector3 vmin;

	for (_dword i = 0; i < 6; i++) {
		// X axis.
		vmin.x = mPlanes[i].a < 0.0f ? box.mMinVector.x : box.mMaxVector.x;

		// Y axis.
		vmin.y = mPlanes[i].b < 0.0f ? box.mMinVector.y : box.mMaxVector.y;

		// Z axis.
		vmin.z = mPlanes[i].c < 0.0f ? box.mMinVector.z : box.mMaxVector.z;

		if (mPlanes[i].Distance(vmin) < 0.0f)
			return _false;
	}

	return _true;
}

_ubool Frustum::Inside(const Box& box) const {
	_byte outside[8] = {0};

	for (_int i = 0; i < 8; i++) {
		for (_int j = 0; j < 6; j++) {
			if (mPlanes[j].Distance(box.mVectors[i]) > 0.0f) {
				outside[i] |= 1 << j;
			}
		}

		if (outside[i] == 0)
			return _true;
	}

	return (outside[0] & outside[1] & outside[2] & outside[3] & outside[4] & outside[5] & outside[6] & outside[7]) == 0;
}

_ubool Frustum::Inside(const Line3D& line) const {
	_byte outside[2] = {0};
	for (_int j = 0; j < 6; j++) {
		if (mPlanes[j].Distance(line.mPoints[0]) > 0.0f) {
			outside[0] |= 1 << j;
		}
	}
	if (outside[0] == 0)
		return _true;

	for (_int j = 0; j < 6; j++) {
		if (mPlanes[j].Distance(line.mPoints[1]) > 0.0f) {
			outside[1] |= 1 << j;
		}
	}
	if (outside[1] == 0)
		return _true;

	return (outside[0] & outside[1]) == 0;
}

_ubool Frustum::Inside(const Vector3& point) const {
	for (_int j = 0; j < 6; j++) {
		if (mPlanes[j].Distance(point) < 0.0f) {
			return _false;
		}
	}

	return _true;
}

Plane Frustum::ParallelPlane(const Vector3& point) {
	_float distance = Math::Abs(mPlanes[0].Distance(point));
	_float depth = Depth();
	_float factor = 0.0f;
	if (depth != 0.0f)
		factor = distance / depth;

	Vector3 point0 = mVectors[0] + (mVectors[4] - mVectors[0]) * factor;
	Vector3 point1 = mVectors[1] + (mVectors[5] - mVectors[1]) * factor;
	Vector3 point2 = mVectors[2] + (mVectors[6] - mVectors[2]) * factor;

	return Plane(point0, point1, point2);
}