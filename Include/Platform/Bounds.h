#pragma once

namespace EGE {

/// <summary>
/// The axis aligned box.
/// </summary>
class Bounds {
public:
	static const Bounds cNull;
	static const Bounds cMax;

public:
	Vector3 mMinVector;
	Vector3 mMaxVector;

public:
	inline Bounds();
	inline Bounds(_float x1, _float y1, _float z1, _float x2, _float y2, _float z2);
	inline Bounds(const Vector3& minvector, const Vector3& maxvector);

public:
	inline _ubool operator==(const Bounds& box) const;
	inline _ubool operator!=(const Bounds& box) const;

	inline Bounds& operator+=(const Bounds& box);
	inline Bounds& operator+=(const Vector3& vector);
	inline Bounds& operator*=(const Matrix4& matrix);
	inline Bounds& operator*=(const Transform3D& transform);

	inline Bounds operator+(const Bounds& box) const;
	inline Bounds operator+(const Vector3& vector) const;
	inline Bounds operator*(const Matrix4& matrix) const;
	inline Bounds operator*(const Transform3D& transform) const;

	inline _ubool Equal(const Bounds& box, _float margin = Math::cFloatEpsilon) const;
	inline _ubool VectorInBox(const Vector3& vector) const;

	inline Vector3 CenterVector() const;
	inline Vector3 BoxSize() const;

public:
	//! Makes a box equal to the union of two existing ones.
	//! @param box1		The source box 1.
	//! @param box2		The source box 2.
	//! @return The union box that contains both source boxes.
	static Bounds Union(const Bounds& box1, const Bounds& box2);
};

Bounds::Bounds()
    : mMinVector(Vector3::cOrigin), mMaxVector(Vector3::cOrigin) {
}

Bounds::Bounds(_float x1, _float y1, _float z1, _float x2, _float y2, _float z2)
    : mMinVector(x1, y1, z1), mMaxVector(x2, y2, z2) {
}

Bounds::Bounds(const Vector3& minvector, const Vector3& maxvector) {
	if (minvector.x < maxvector.x) {
		mMinVector.x = minvector.x;
		mMaxVector.x = maxvector.x;
	} else {
		mMinVector.x = maxvector.x;
		mMaxVector.x = minvector.x;
	}

	if (minvector.y < maxvector.y) {
		mMinVector.y = minvector.y;
		mMaxVector.y = maxvector.y;
	} else {
		mMinVector.y = maxvector.y;
		mMaxVector.y = minvector.y;
	}

	if (minvector.z < maxvector.z) {
		mMinVector.z = minvector.z;
		mMaxVector.z = maxvector.z;
	} else {
		mMinVector.z = maxvector.z;
		mMaxVector.z = minvector.z;
	}
}

_ubool Bounds::operator==(const Bounds& box) const {
	return mMinVector == box.mMinVector && mMaxVector == box.mMaxVector;
}

_ubool Bounds::operator!=(const Bounds& box) const {
	return mMinVector != box.mMinVector || mMaxVector != box.mMaxVector;
}

Bounds& Bounds::operator+=(const Bounds& box) {
	mMinVector.x = Math::Min(mMinVector.x, box.mMinVector.x);
	mMinVector.y = Math::Min(mMinVector.y, box.mMinVector.y);
	mMinVector.z = Math::Min(mMinVector.z, box.mMinVector.z);
	mMaxVector.x = Math::Max(mMaxVector.x, box.mMaxVector.x);
	mMaxVector.y = Math::Max(mMaxVector.y, box.mMaxVector.y);
	mMaxVector.z = Math::Max(mMaxVector.z, box.mMaxVector.z);

	return *this;
}

Bounds& Bounds::operator+=(const Vector3& vector) {
	mMinVector.x = Math::Min(mMinVector.x, vector.x);
	mMinVector.y = Math::Min(mMinVector.y, vector.y);
	mMinVector.z = Math::Min(mMinVector.z, vector.z);
	mMaxVector.x = Math::Max(mMaxVector.x, vector.x);
	mMaxVector.y = Math::Max(mMaxVector.y, vector.y);
	mMaxVector.z = Math::Max(mMaxVector.z, vector.z);

	return *this;
}

Bounds& Bounds::operator*=(const Matrix4& matrix) {
	// Thanks for sharing the cool code :
	// http://dev.theomader.com/transform-bounding-boxes/
	Vector3 right(matrix.m[0][0], matrix.m[0][1], matrix.m[0][2]);
	Vector3 up(matrix.m[1][0], matrix.m[1][1], matrix.m[1][2]);
	Vector3 backward(matrix.m[2][0], matrix.m[2][1], matrix.m[2][2]);
	Vector3 translation(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);

	Vector3 xa = right * mMinVector.x;
	Vector3 xb = right * mMaxVector.x;

	Vector3 ya = up * mMinVector.y;
	Vector3 yb = up * mMaxVector.y;

	Vector3 za = backward * mMinVector.z;
	Vector3 zb = backward * mMaxVector.z;

	mMinVector = Vector3::Min(xa, xb) + Vector3::Min(ya, yb) +
	             Vector3::Min(za, zb) + translation;
	mMaxVector = Vector3::Max(xa, xb) + Vector3::Max(ya, yb) +
	             Vector3::Max(za, zb) + translation;

	return *this;
}

Bounds& Bounds::operator*=(const Transform3D& trasform) {
	Box box(mMinVector, mMaxVector);
	box *= trasform;

	mMinVector = mMaxVector = box.mVectors[0];

	for (_dword i = 1; i < 8; i++) {
		mMinVector.x = Math::Min(mMinVector.x, box.mVectors[i].x);
		mMinVector.y = Math::Min(mMinVector.y, box.mVectors[i].y);
		mMinVector.z = Math::Min(mMinVector.z, box.mVectors[i].z);
		mMaxVector.x = Math::Max(mMaxVector.x, box.mVectors[i].x);
		mMaxVector.y = Math::Max(mMaxVector.y, box.mVectors[i].y);
		mMaxVector.z = Math::Max(mMaxVector.z, box.mVectors[i].z);
	}

	return *this;
}

Bounds Bounds::operator+(const Bounds& box) const {
	Bounds returnbox(*this);

	return returnbox += box;
}

Bounds Bounds::operator+(const Vector3& vector) const {
	Bounds returnbox(*this);

	return returnbox += vector;
}

Bounds Bounds::operator*(const Matrix4& matrix) const {
	Bounds returnbox(*this);

	return returnbox *= matrix;
}

Bounds Bounds::operator*(const Transform3D& transform) const {
	Bounds returnbox(*this);

	return returnbox *= transform;
}

_ubool Bounds::Equal(const Bounds& box, _float margin) const {
	return mMinVector.Equal(box.mMinVector, margin) &&
	       mMaxVector.Equal(box.mMaxVector, margin);
}

_ubool Bounds::VectorInBox(const Vector3& vector) const {
	return vector.x >= mMinVector.x && vector.x <= mMaxVector.x &&
	       vector.y >= mMinVector.y && vector.y <= mMaxVector.y &&
	       vector.z >= mMinVector.z && vector.z <= mMaxVector.z;
}

Vector3 Bounds::CenterVector() const {
	return (mMinVector + mMaxVector) / 2.0f;
}

Vector3 Bounds::BoxSize() const {
	return (mMaxVector - mMinVector).Absolute();
}

} // namespace EGE