#include "EGEPlatform.h"

const Matrix3x4 Matrix3x4::cZero(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
const Matrix3x4 Matrix3x4::cIdentity(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);

Matrix3x4& Matrix3x4::operator=(const Matrix4& matrix) {
	m[0][0] = matrix.m[0][0];
	m[0][1] = matrix.m[1][0];
	m[0][2] = matrix.m[2][0];
	m[1][0] = matrix.m[0][1];
	m[1][1] = matrix.m[1][1];
	m[1][2] = matrix.m[2][1];
	m[2][0] = matrix.m[0][2];
	m[2][1] = matrix.m[1][2];
	m[2][2] = matrix.m[2][2];
	m[3][0] = matrix.m[0][3];
	m[3][1] = matrix.m[1][3];
	m[3][2] = matrix.m[2][3];

	return *this;
}

Matrix3x4& Matrix3x4::operator+=(const Matrix3x4& matrix) {
	m[0][0] += matrix.m[0][0];
	m[0][1] += matrix.m[0][1];
	m[0][2] += matrix.m[0][2];
	m[1][0] += matrix.m[1][0];
	m[1][1] += matrix.m[1][1];
	m[1][2] += matrix.m[1][2];
	m[2][0] += matrix.m[2][0];
	m[2][1] += matrix.m[2][1];
	m[2][2] += matrix.m[2][2];
	m[3][0] += matrix.m[3][0];
	m[3][1] += matrix.m[3][1];
	m[3][2] += matrix.m[3][2];

	return *this;
}

Matrix3x4& Matrix3x4::operator-=(const Matrix3x4& matrix) {
	m[0][0] -= matrix.m[0][0];
	m[0][1] -= matrix.m[0][1];
	m[0][2] -= matrix.m[0][2];
	m[1][0] -= matrix.m[1][0];
	m[1][1] -= matrix.m[1][1];
	m[1][2] -= matrix.m[1][2];
	m[2][0] -= matrix.m[2][0];
	m[2][1] -= matrix.m[2][1];
	m[2][2] -= matrix.m[2][2];
	m[3][0] -= matrix.m[3][0];
	m[3][1] -= matrix.m[3][1];
	m[3][2] -= matrix.m[3][2];

	return *this;
}

Matrix3x4& Matrix3x4::operator*=(_float scalar) {
	m[0][0] *= scalar;
	m[0][1] *= scalar;
	m[0][2] *= scalar;
	m[1][0] *= scalar;
	m[1][1] *= scalar;
	m[1][2] *= scalar;
	m[2][0] *= scalar;
	m[2][1] *= scalar;
	m[2][2] *= scalar;
	m[3][0] *= scalar;
	m[3][1] *= scalar;
	m[3][2] *= scalar;

	return *this;
}

Matrix3x4& Matrix3x4::operator/=(_float scalar) {
	m[0][0] /= scalar;
	m[0][1] /= scalar;
	m[0][2] /= scalar;
	m[1][0] /= scalar;
	m[1][1] /= scalar;
	m[1][2] /= scalar;
	m[2][0] /= scalar;
	m[2][1] /= scalar;
	m[2][2] /= scalar;
	m[3][0] /= scalar;
	m[3][1] /= scalar;
	m[3][2] /= scalar;

	return *this;
}

Matrix3x4 Matrix3x4::operator+(const Matrix3x4& matrix) const {
	Matrix3x4 returnmatrix = *this;

	return returnmatrix += matrix;
}

Matrix3x4 Matrix3x4::operator-(const Matrix3x4& matrix) const {
	Matrix3x4 returnmatrix = *this;

	return returnmatrix -= matrix;
}

Matrix3x4 Matrix3x4::operator*(_float scalar) const {
	Matrix3x4 returnmatrix = *this;

	return returnmatrix *= scalar;
}

Matrix3x4 Matrix3x4::operator/(_float scalar) const {
	Matrix3x4 returnmatrix = *this;

	return returnmatrix /= scalar;
}

Matrix3x4& Matrix3x4::Translation(_float x, _float y, _float z) {
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;

	return *this;
}

Matrix3x4& Matrix3x4::Translation(const Vector3& vector) {
	return Translation(vector.x, vector.y, vector.z);
}

Matrix3x4& Matrix3x4::RotationX(_float radian) {
	_float sincos_value[2];
	Math::SinCos(radian, sincos_value);

	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[1][0] = 0.0f;
	m[1][1] = sincos_value[1];
	m[1][2] = sincos_value[0];
	m[2][0] = 0.0f;
	m[2][1] = -sincos_value[0];
	m[2][2] = sincos_value[1];

	return *this;
}

Matrix3x4& Matrix3x4::RotationY(_float radian) {
	_float sincos_value[2];
	Math::SinCos(radian, sincos_value);

	m[0][0] = sincos_value[1];
	m[0][1] = 0.0f;
	m[0][2] = -sincos_value[0];
	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[2][0] = sincos_value[0];
	m[2][1] = 0.0f;
	m[2][2] = sincos_value[1];

	return *this;
}

Matrix3x4& Matrix3x4::RotationZ(_float radian) {
	_float sincos_value[2];
	Math::SinCos(radian, sincos_value);

	m[0][0] = sincos_value[1];
	m[0][1] = sincos_value[0];
	m[0][2] = 0.0f;
	m[1][0] = -sincos_value[0];
	m[1][1] = sincos_value[1];
	m[1][2] = 0.0f;
	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;

	return *this;
}

Matrix3x4& Matrix3x4::FromTranslationRotation(const Vector3& translation, const Matrix3& rotation) {
	m[0][0] = rotation.m[0][0];
	m[0][1] = rotation.m[0][1];
	m[0][2] = rotation.m[0][2];
	m[1][0] = rotation.m[1][0];
	m[1][1] = rotation.m[1][1];
	m[1][2] = rotation.m[1][2];
	m[2][0] = rotation.m[2][0];
	m[2][1] = rotation.m[2][1];
	m[2][2] = rotation.m[2][2];
	m[3][0] = translation.x;
	m[3][1] = translation.y;
	m[3][2] = translation.z;

	return *this;
}

_void Matrix3x4::ToTranslationRotation(Vector3& translation, Matrix3& rotation) const {
	translation.x = m[3][0];
	translation.y = m[3][1];
	translation.z = m[3][2];

	rotation.m[0][0] = m[0][0];
	rotation.m[0][1] = m[0][1];
	rotation.m[0][2] = m[0][2];
	rotation.m[1][0] = m[1][0];
	rotation.m[1][1] = m[1][1];
	rotation.m[1][2] = m[1][2];
	rotation.m[2][0] = m[2][0];
	rotation.m[2][1] = m[2][1];
	rotation.m[2][2] = m[2][2];
}