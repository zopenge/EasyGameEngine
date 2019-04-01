//! @file     Triangle.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Triangle
//----------------------------------------------------------------------------

class Triangle {
public:
	Vector3 mVector1;
	Vector3 mVector2;
	Vector3 mVector3;

public:
	inline Triangle();
	inline Triangle(const Vector3& vector1, const Vector3& vector2,
	                const Vector3& vector3);

	inline Triangle& operator*=(const Matrix4& matrix);
	inline Triangle operator*(const Matrix4& matrix) const;

	inline Vector3 MiddleVector();
};

//----------------------------------------------------------------------------
// Triangle Implementation
//----------------------------------------------------------------------------

Triangle::Triangle() {
}

Triangle::Triangle(const Vector3& vector1, const Vector3& vector2,
                   const Vector3& vector3)
    : mVector1(vector1), mVector2(vector2), mVector3(vector3) {
}

Triangle& Triangle::operator*=(const Matrix4& matrix) {
	mVector1 *= matrix;
	mVector2 *= matrix;
	mVector3 *= matrix;

	return *this;
}

Triangle Triangle::operator*(const Matrix4& matrix) const {
	return Triangle(mVector1 * matrix, mVector2 * matrix, mVector3 * matrix);
}

Vector3 Triangle::MiddleVector() {
	return Vector3((mVector1.x + mVector2.x + mVector3.x) / 3.0f,
	               (mVector1.y + mVector2.y + mVector3.y) / 3.0f,
	               (mVector1.z + mVector2.z + mVector3.z) / 3.0f);
}

} // namespace EGE