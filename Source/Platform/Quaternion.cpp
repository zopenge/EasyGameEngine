//! @file     Quaternion.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Quaternion Implementation
//----------------------------------------------------------------------------

const Quaternion Quaternion::cIdentity(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion& Quaternion::operator*=(const Quaternion& quaternion) {
	_float qx1 = x, qy1 = y, qz1 = z, qw1 = w;

	//  x = qw1 * quaternion.x + qx1 * quaternion.w + qy1 * quaternion.z - qz1 * quaternion.y;
	//  y = qw1 * quaternion.y - qx1 * quaternion.z + qy1 * quaternion.w + qz1 * quaternion.x;
	//  z = qw1 * quaternion.z + qx1 * quaternion.y - qy1 * quaternion.x + qz1 * quaternion.w;
	//  w = qw1 * quaternion.w - qx1 * quaternion.x - qy1 * quaternion.y - qz1 * quaternion.z;

	x = qw1 * quaternion.x + qx1 * quaternion.w - qy1 * quaternion.z + qz1 * quaternion.y;
	y = qw1 * quaternion.y + qx1 * quaternion.z + qy1 * quaternion.w - qz1 * quaternion.x;
	z = qw1 * quaternion.z - qx1 * quaternion.y + qy1 * quaternion.x + qz1 * quaternion.w;
	w = qw1 * quaternion.w - qx1 * quaternion.x - qy1 * quaternion.y - qz1 * quaternion.z;

	return *this;
}

Quaternion& Quaternion::operator/=(const Quaternion& quaternion) {
	Quaternion tempquaternion = *this;
	*this = -quaternion;

	return *this *= tempquaternion;
}

Quaternion Quaternion::operator*(const Quaternion& quaternion) const {
	Quaternion returnquaternion = *this;

	return returnquaternion *= quaternion;
}

Quaternion Quaternion::operator/(const Quaternion& quaternion) const {
	Quaternion returnquaternion = *this;

	return returnquaternion /= quaternion;
}

_ubool Quaternion::Equal(const Quaternion& quaternion, _float margin) const {
	if (Math::Abs(x - quaternion.x) > margin)
		return _false;

	if (Math::Abs(y - quaternion.y) > margin)
		return _false;

	if (Math::Abs(z - quaternion.z) > margin)
		return _false;

	if (Math::Abs(w - quaternion.w) > margin)
		return _false;

	return _true;
}

Quaternion& Quaternion::Identity() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 1.0f;

	return *this;
}

Quaternion& Quaternion::Normalize() {
	_float magnitude = Magnitude();

	if (Math::Abs(1.0f - magnitude) > Math::cFloatEpsilon) {
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		w /= magnitude;
	}

	return *this;
}

_float Quaternion::Magnitude() const {
	return Math::Sqrt(x * x + y * y + z * z + w * w);
}

_float Quaternion::MagnitudeSquared() const {
	return x * x + y * y + z * z + w * w;
}

Quaternion& Quaternion::RotationX(_float radian) {
	_float sincos_value[2];
	Math::SinCos(radian * 0.5f, sincos_value);

	x = sincos_value[0];
	y = 0.0f;
	z = 0.0f;
	w = sincos_value[1];

	return *this;
}

Quaternion& Quaternion::RotationY(_float radian) {
	_float sincos_value[2];
	Math::SinCos(radian * 0.5f, sincos_value);

	x = 0.0f;
	y = sincos_value[0];
	z = 0.0f;
	w = sincos_value[1];

	return *this;
}

Quaternion& Quaternion::RotationZ(_float radian) {
	_float sincos_value[2];
	Math::SinCos(radian * 0.5f, sincos_value);

	x = 0.0f;
	y = 0.0f;
	z = sincos_value[0];
	w = sincos_value[1];

	return *this;
}

Quaternion& Quaternion::Rotation(const Vector3& axis, _float radian) {
	_float sincos_value[2];
	Math::SinCos(radian * 0.5f, sincos_value);

	x = sincos_value[0] * axis.x;
	y = sincos_value[0] * axis.y;
	z = sincos_value[0] * axis.z;
	w = sincos_value[1];

	return *this;
}

Quaternion& Quaternion::FastRotation(const Vector3& vector1, const Vector3& vector2) {
	_float dotvalue = Vector3::Dot(vector1, vector2);
	if (dotvalue >= 1.0f - Math::cFloatEpsilon)
		return (*this = Quaternion::cIdentity);

	if (dotvalue <= Math::cFloatEpsilon - 1.0f)
		return Rotation(Vector3::cZAxis, Math::cPi);

	_float sqrtvalue = Math::Sqrt((1.0f + dotvalue) * 2.0f);
	if (sqrtvalue < Math::cFloatEpsilon)
		return (*this = Quaternion::cIdentity);

	Vector3 axis = Vector3::Cross(vector1, vector2);

	x = axis.x / sqrtvalue;
	y = axis.y / sqrtvalue;
	z = axis.z / sqrtvalue;
	w = sqrtvalue * 0.5f;

	return *this;
}

Quaternion& Quaternion::Rotation(const Vector3& srcvector, const Vector3& desvector) {
	Vector3 vector1 = srcvector;
	vector1.Normalize();

	Vector3 vector2 = desvector;
	vector2.Normalize();

	return FastRotation(vector1, vector2);
}

_int Quaternion::IsPositive(const Vector3& vector1, const Vector3& vector2) {
	_float dotvalue = Vector3::Dot(vector1, vector2);

	if (dotvalue >= 1.0f - Math::cFloatEpsilon)
		return 1;

	if (dotvalue <= Math::cFloatEpsilon - 1.0f)
		return -1;

	return 0;
}

Quaternion& Quaternion::Rotation(const Vector3& src_coordinate_axis1, const Vector3& src_coordinate_axis2, const Vector3& des_coordinate_axis1, const Vector3& des_coordinate_axis2) {
	Vector3 src_axis1 = src_coordinate_axis1;
	Vector3 des_axis1 = des_coordinate_axis1;
	Vector3 src_axis2 = src_coordinate_axis2;
	Vector3 des_axis2 = des_coordinate_axis2;
	src_axis1.Normalize();
	des_axis1.Normalize();
	src_axis2.Normalize();
	des_axis2.Normalize();

	_int positive_1 = IsPositive(src_axis1, des_axis1);
	switch (positive_1) {
		case -1: {
			Rotation(des_axis2, Math::cPi);
			Vector3 new_src_axis1 = src_axis1 * *this;
			Vector3 new_src_axis2 = src_axis2 * *this;
			Quaternion quat = Quaternion().FastRotation(new_src_axis2, des_axis2);
			*this *= quat;
			Vector3 new_src_axis3 = Vector3::Cross(new_src_axis1, new_src_axis2) * quat;
			Vector3 des_axis3 = Vector3::Cross(des_axis1, des_axis2);
			_int positive_3 = IsPositive(new_src_axis3, des_axis3);
			if (positive_3 == -1) {
				*this *= Quaternion().Rotation(des_axis1, Math::cPi);
			}
		} break;
		case 0: {
			FastRotation(src_axis1, des_axis1);
			Vector3 new_src_axis2 = src_axis2 * *this;
			_int positive_2 = IsPositive(new_src_axis2, des_axis2);
			switch (positive_2) {
				case -1: {
					*this *= Quaternion().Rotation(des_axis1, Math::cPi);
				} break;
				case 0: {
					*this *= Quaternion().FastRotation(new_src_axis2, des_axis2);
				} break;
			}
		} break;
		case 1: {
			FastRotation(src_axis2, des_axis2);
			Vector3 new_src_axis3 = Vector3::Cross(src_axis1, src_axis2) * *this;
			Vector3 des_axis3 = Vector3::Cross(des_axis1, des_axis2);
			_int positive_3 = IsPositive(new_src_axis3, des_axis3);
			if (positive_3 == -1) {
				*this *= Quaternion().Rotation(des_axis1, Math::cPi);
			}
		} break;
	}

	return *this;
}

_void Quaternion::GetAxisAndAngle(Vector3& axis, _float& radian) const {
	_float length = x * x + y * y + z * z;

	if (length > Math::cFloatEpsilon) {
		length = Math::Sqrt(length);

		axis.x = x / length;
		axis.y = y / length;
		axis.z = z / length;
		radian = 2.0f * Math::Acos(w);
	} else {
		axis.x = 0.0f;
		axis.y = 0.0f;
		axis.z = 1.0f;
		radian = 0.0f;
	}

	axis.Normalize();
}

_void Quaternion::ToEulerAngles(EulerAngles& angles) const {
	_float sh = 2.0f * (w * y - x * z);
	if (sh <= -1.0f)
		angles.mHeading = -Math::cPi * 0.5f;
	else if (sh >= 1.0f)
		angles.mHeading = Math::cPi * 0.5f;
	else
		angles.mHeading = Math::Asin(sh);

	if (sh > 1.0f - Math::cFloatEpsilon) {
		angles.mBank = 0.0f;
		angles.mPitch = Math::Atan(2.0f * (x * y - w * z), 2.0f * (x * z + w * y));
	} else {
		angles.mBank = Math::Atan(2.0f * (x * y + w * z), 1.0f - 2.0f * (y * y + z * z));
		angles.mPitch = Math::Atan(2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
	}
}

_void Quaternion::ToMatrix(Matrix3& matrix) const {
	_float xx = x * x * 2.0f, yy = y * y * 2.0f, zz = z * z * 2.0f;
	_float xy = x * y * 2.0f, zw = z * w * 2.0f, xz = x * z * 2.0f;
	_float yw = y * w * 2.0f, yz = y * z * 2.0f, xw = x * w * 2.0f;

	matrix.m[0][0] = 1.0f - yy - zz;
	matrix.m[0][1] = xy + zw;
	matrix.m[0][2] = xz - yw;
	matrix.m[1][0] = xy - zw;
	matrix.m[1][1] = 1.0f - xx - zz;
	matrix.m[1][2] = yz + xw;
	matrix.m[2][0] = xz + yw;
	matrix.m[2][1] = yz - xw;
	matrix.m[2][2] = 1.0f - xx - yy;
}

_float Quaternion::Dot(const Quaternion& quaternion1, const Quaternion& quaternion2) {
	return quaternion1.x * quaternion2.x + quaternion1.y * quaternion2.y + quaternion1.z * quaternion2.z + quaternion1.w * quaternion2.w;
}

_void Quaternion::Fix() {
	if (x == 0.0f && y == 0.0f && z == 0.0f)
		w = 1.0f;
}

Quaternion Quaternion::Slerp(const Quaternion& quaternion1, const Quaternion& quaternion2, _float factor) {
	_float dot = Dot(quaternion1, quaternion2);

	_ubool flip = dot < 0.0f;

	if (dot < 0.0f)
		dot = -dot;

	_float divide = 0.0f;

	if (1.0f - dot < Math::cFloatEpsilon) {
		divide = 1.0f - factor;
	} else {
		_float theta = Math::Acos(dot);
		_float recipsqrt = 1.0f / Math::Sin(theta);

		divide = Math::Sin((1.0f - factor) * theta) * recipsqrt;
		factor = Math::Sin(factor * theta) * recipsqrt;
	}

	if (flip)
		factor = -factor;

	return Quaternion(
	    quaternion1.x * divide + quaternion2.x * factor,
	    quaternion1.y * divide + quaternion2.y * factor,
	    quaternion1.z * divide + quaternion2.z * factor,
	    quaternion1.w * divide + quaternion2.w * factor);
}

Quaternion Quaternion::Slerp(const Quaternion& quaternion1, const Quaternion& quaternion2, _float dot, _float theta, _float recipsqrt, _float factor) {
	_ubool flip = dot < 0.0f;

	if (dot < 0.0f)
		dot = -dot;

	_float divide = 0.0f;

	if (1.0f - dot < Math::cFloatEpsilon) {
		divide = 1.0f - factor;
	} else {
		divide = Math::Sin((1.0f - factor) * theta) * recipsqrt;
		factor = Math::Sin(factor * theta) * recipsqrt;
	}

	if (flip)
		factor = -factor;

	return Quaternion(
	    quaternion1.x * divide + quaternion2.x * factor,
	    quaternion1.y * divide + quaternion2.y * factor,
	    quaternion1.z * divide + quaternion2.z * factor,
	    quaternion1.w * divide + quaternion2.w * factor);
}
