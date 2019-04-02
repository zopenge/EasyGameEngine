//! @file     Quaternion.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

class Vector3;
class EulerAngles;

//----------------------------------------------------------------------------
// Quaternion
//----------------------------------------------------------------------------

//! This class represents a quaternion.
class Quaternion {
public:
	//! X-component of the quaternion.
	_float x;
	//! Y-component of the quaternion.
	_float y;
	//! Z-component of the quaternion.
	_float z;
	//! W-component of the quaternion.
	_float w;

public:
	//! The identity quaternion.
	static const Quaternion cIdentity;

private:
	_int IsPositive(const Vector3& srcvector, const Vector3& desvector);
	Quaternion& FastRotation(const Vector3& srcvector, const Vector3& desvector);

public:
	//! Constructor, create a quaternion without sets x, y, z, w components.
	//! @param none
	inline Quaternion();
	//! Constructor, create a quaternion and sets x, y, z components.
	//! @param xx			X-component of the quaternion.
	//! @param yy			Y-component of the quaternion.
	//! @param zz			Z-component of the quaternion.
	inline Quaternion(_float xx, _float yy, _float zz, _float ww);

	//! Get positive quaternion.
	//! @param none
	//! @return The positive quaternion.
	inline Quaternion operator+() const;
	//! Get negative quaternion.
	//! @param none
	//! @return The negative quaternion.
	inline Quaternion operator-() const;

	//! Add a quaternion to current quaternion, and save result in current one.
	//! @param quaternion	The quaternion to add.
	//! @return The result quaternion of addition.
	inline Quaternion& operator+=(const Quaternion& quaternion);
	//! Subtract a quaternion from current quaternion, and save result in current
	//! one.
	//! @param quaternion	The quaternion to subtract.
	//! @return The result quaternion of subtraction.
	inline Quaternion& operator-=(const Quaternion& quaternion);
	//! Multiply a scalar to current vector, and save result
	//! Multiply a quaternion to current quaternion, and save result in current
	//! one.
	//! @param quaternion	The quaternion to multiply.
	//! @return The result quaternion of multiplication.
	Quaternion& operator*=(const Quaternion& quaternion);
	//! Divide a quaternion to current quaternion, and save result in current one.
	//! @param quaternion	The quaternion to divide.
	//! @return The result quaternion of division.
	Quaternion& operator/=(const Quaternion& quaternion);

	//! Add a quaternion to current quaternion, return a new quaternion to save
	//! result.
	//! @param quaternion	The quaternion to add.
	//! @return The result quaternion of addition.
	inline Quaternion operator+(const Quaternion& quaternion) const;
	//! Subtract a quaternion from current quaternion, return a new quaternion to save result.
	//! @param quaternion	The quaternion to subtract.
	//! @return The result quaternion of subtraction.
	inline Quaternion operator-(const Quaternion& quaternion) const;
	//! Multiply a quaternion to current quaternion, return a new quaternion to save result.( do not use the standard quaternion multiplication )
	//! @param quaternion	The quaternion to multiply.
	//! @return The result quaternion of multiplication.
	Quaternion operator*(const Quaternion& quaternion) const;
	//! Divide a quaternion to current quaternion, return a new quaternion to save result.
	//! @param quaternion	The quaternion to divide.
	//! @return The result quaternion of division.
	Quaternion operator/(const Quaternion& quaternion) const;

	//! Compare two quaternions with error margin.
	//! @param quaternion	The quaternion to compare with.
	//! @param margin		The margin that allows some error.
	//! @return True if they are identical, false otherwise.
	_ubool Equal(const Quaternion& quaternion, _float margin = Math::cFloatEpsilon) const;

	//! Calculates identity quaternion, and save result in current one.
	//! @param none
	//! @return The identity quaternion.
	Quaternion& Identity();
	//! Calculates normalized quaternion, and save result in current one.
	//! @param none
	//! @return The normalized quaternion.
	Quaternion& Normalize();

	//! Calculates quaternion magnitude.
	//! @param none
	//! @return The magnitude of quaternion.
	_float Magnitude() const;
	//! Calculates the square of quaternion magnitude, this function is faster
	//! than Magnitude.
	//! @param none
	//! @return The square of magnitude of quaternion.
	_float MagnitudeSquared() const;

	//! Create a rotation quaternion by rotate around x-axis.
	//! @param radian		The angle of rotation in radian.
	//! @return The rotation quaternion.
	Quaternion& RotationX(_float radian);
	//! Create a rotation quaternion by rotate around y-axis.
	//! @param radian		The angle of rotation in radian.
	//! @return The rotation quaternion.
	Quaternion& RotationY(_float radian);
	//! Create a rotation quaternion by rotate around z-axis.
	//! @param radian		The angle of rotation in radian.
	//! @return The rotation matrix.
	Quaternion& RotationZ(_float radian);
	//! Create a rotation quaternion by rotate around an arbitrary axis.
	//! @param axis		The axis to rotate around.
	//! @param radian		The angle of rotation in radian.
	//! @return The rotation quaternion.
	Quaternion& Rotation(const Vector3& axis, _float radian);
	//! Create a rotation quaternion that rotate one vector into another.
	//! @param srcvector	The source vector to be rotated.
	//! @param desvector	The target vector to rotate into.
	//! @return The rotation quaternion.
	Quaternion& Rotation(const Vector3& srcvector, const Vector3& desvector);
	//! Create a rotation quaternion that rotate one coordinate into another.
	//! @param src_coordinate_axis1	The one axis of source coordinate system to be rotated.
	//! @param src_coordinate_axis2	The another axis of source coordinate system to be rotated.
	//! @param des_coordinate_axis1	The one axis of the target coordinate system to rotate into.
	//! @param des_coordinate_axis2	The another axis of the target coordinate system to rotate into.
	//! @return The rotation quaternion.
	Quaternion& Rotation(const Vector3& src_coordinate_axis1, const Vector3& src_coordinate_axis2, const Vector3& des_coordinate_axis1, const Vector3& des_coordinate_axis2);

	//! Get the rotation axis and the angle from quaternion.
	//! @param axis		The axis to rotate around, get from this
	//! function.
	//! @param radian	The angle of rotation in radian, get from this function.
	_void GetAxisAndAngle(Vector3& axis, _float& radian) const;

	_void Fix();

	//! Convert quaternion to euler angles
	//! @param angles The euler angles
	//! @return none.
	_void ToEulerAngles(EulerAngles& angles) const;

	_void ToMatrix(Matrix3& matrix) const;

	// Calculates dot product of two quaternions.
	//! @param quaternion1	Source quaternion 1.
	//! @param quaternion2	Source quaternion 2.
	//! @return The dot product result.
	static _float Dot(const Quaternion& quaternion1, const Quaternion& quaternion2);

	//! Calculates spherical linear interpolation of two quaternions.
	//! @param quaternion1	Source quaternion 1.
	//! @param quaternion2	Source quaternion 2.
	//! @param factor		The interpolation factor, will clamp to between 0 to 1.
	//! @return The result quaternion of interpolation.
	static Quaternion Slerp(const Quaternion& quaternion1, const Quaternion& quaternion2, _float factor);

	//! Calculates spherical linear interpolation of two quaternions, with some precomputed Params.
	//! @param quaternion1	Source quaternion 1.
	//! @param quaternion2	Source quaternion 2.
	//! @param dont		The dot product of two quaternions.
	//! @param theta		Parameter for slerp.
	//! @param recipsqrt	Parameter for slerp.
	//! @param factor		The interpolation factor, will clamp to between 0 to 1.
	//! @return The result quaternion of interpolation.
	static Quaternion Slerp(const Quaternion& quaternion1, const Quaternion& quaternion2, _float dot, _float theta, _float recipsqrt, _float factor);
};

//----------------------------------------------------------------------------
// Quaternion Implementation
//----------------------------------------------------------------------------

Quaternion::Quaternion() {
}

Quaternion::Quaternion(_float xx, _float yy, _float zz, _float ww)
    : x(xx), y(yy), z(zz), w(ww) {
}

Quaternion Quaternion::operator+() const {
	return Quaternion(x, y, z, w);
}

Quaternion Quaternion::operator-() const {
	return Quaternion(-x, -y, -z, w);
}

Quaternion& Quaternion::operator+=(const Quaternion& quaternion) {
	x += quaternion.x;
	y += quaternion.y;
	z += quaternion.z;
	w += quaternion.w;

	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& quaternion) {
	x -= quaternion.x;
	y -= quaternion.y;
	z -= quaternion.z;
	w -= quaternion.w;

	return *this;
}

Quaternion Quaternion::operator+(const Quaternion& quaternion) const {
	return Quaternion(x + quaternion.x, y + quaternion.y, z + quaternion.z,
	                  w + quaternion.w);
}

Quaternion Quaternion::operator-(const Quaternion& quaternion) const {
	return Quaternion(x - quaternion.x, y - quaternion.y, z - quaternion.z,
	                  w - quaternion.w);
}

} // namespace EGE