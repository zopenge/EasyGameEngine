#pragma once

namespace EGE {

/// <summary>
/// The box.
/// </summary>
class Box {
public:
	static const Box cNull;

public:
	Vector3 mVectors[8];

public:
	inline Box();
	inline Box(_float min_x, _float min_y, _float min_z, _float max_x, _float max_y, _float max_z);
	inline Box(const Vector3& minvector, const Vector3& maxvector);

	inline Box& operator*=(const Matrix4& matrix);
	inline Box operator*(const Matrix4& matrix) const;
	inline Box& operator*=(const Transform3D& transform);
	inline Box operator*(const Transform3D& transform) const;

	Box& Expand(_float expand_size);
	Vector3 GetCenter() const;
};

Box::Box() {
}

Box::Box(_float min_x, _float min_y, _float min_z, _float max_x, _float max_y, _float max_z) {
	mVectors[0] = Vector3(min_x, min_y, min_z);
	mVectors[1] = Vector3(max_x, min_y, min_z);
	mVectors[2] = Vector3(min_x, max_y, min_z);
	mVectors[3] = Vector3(max_x, max_y, min_z);
	mVectors[4] = Vector3(min_x, min_y, max_z);
	mVectors[5] = Vector3(max_x, min_y, max_z);
	mVectors[6] = Vector3(min_x, max_y, max_z);
	mVectors[7] = Vector3(max_x, max_y, max_z);
}

Box::Box(const Vector3& minvector, const Vector3& maxvector) {
	mVectors[0] = Vector3(minvector.x, minvector.y, minvector.z);
	mVectors[1] = Vector3(maxvector.x, minvector.y, minvector.z);
	mVectors[2] = Vector3(minvector.x, maxvector.y, minvector.z);
	mVectors[3] = Vector3(maxvector.x, maxvector.y, minvector.z);
	mVectors[4] = Vector3(minvector.x, minvector.y, maxvector.z);
	mVectors[5] = Vector3(maxvector.x, minvector.y, maxvector.z);
	mVectors[6] = Vector3(minvector.x, maxvector.y, maxvector.z);
	mVectors[7] = Vector3(maxvector.x, maxvector.y, maxvector.z);
}

Box& Box::operator*=(const Matrix4& matrix) {
	mVectors[0] *= matrix;
	mVectors[1] *= matrix;
	mVectors[2] *= matrix;
	mVectors[3] *= matrix;
	mVectors[4] *= matrix;
	mVectors[5] *= matrix;
	mVectors[6] *= matrix;
	mVectors[7] *= matrix;

	return *this;
}

Box Box::operator*(const Matrix4& matrix) const {
	Box returnbox(*this);

	return returnbox *= matrix;
}

Box& Box::operator*=(const Transform3D& transform) {
	mVectors[0] *= transform;
	mVectors[1] *= transform;
	mVectors[2] *= transform;
	mVectors[3] *= transform;
	mVectors[4] *= transform;
	mVectors[5] *= transform;
	mVectors[6] *= transform;
	mVectors[7] *= transform;

	return *this;
}

Box Box::operator*(const Transform3D& transform) const {
	Box returnbox(*this);

	return returnbox *= transform;
}

} // namespace EGE