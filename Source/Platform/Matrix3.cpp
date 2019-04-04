#include "EGEPlatform.h"

const Matrix3 Matrix3::cZero(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
const Matrix3 Matrix3::cIdentity(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

Matrix3& Matrix3::operator+=(const Matrix3& matrix) {
	m[0][0] += matrix.m[0][0];
	m[0][1] += matrix.m[0][1];
	m[0][2] += matrix.m[0][2];
	m[1][0] += matrix.m[1][0];
	m[1][1] += matrix.m[1][1];
	m[1][2] += matrix.m[1][2];
	m[2][0] += matrix.m[2][0];
	m[2][1] += matrix.m[2][1];
	m[2][2] += matrix.m[2][2];

	return *this;
}

Matrix3& Matrix3::operator-=(const Matrix3& matrix) {
	m[0][0] -= matrix.m[0][0];
	m[0][1] -= matrix.m[0][1];
	m[0][2] -= matrix.m[0][2];
	m[1][0] -= matrix.m[1][0];
	m[1][1] -= matrix.m[1][1];
	m[1][2] -= matrix.m[1][2];
	m[2][0] -= matrix.m[2][0];
	m[2][1] -= matrix.m[2][1];
	m[2][2] -= matrix.m[2][2];

	return *this;
}

Matrix3& Matrix3::operator*=(const Matrix3& matrix) {
	_float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m10 = m[1][0], m11 = m[1][1],
	       m12 = m[1][2], m20 = m[2][0], m21 = m[2][1], m22 = m[2][2];

	m[0][0] = m00 * matrix.m[0][0] + m01 * matrix.m[1][0] + m02 * matrix.m[2][0];
	m[0][1] = m00 * matrix.m[0][1] + m01 * matrix.m[1][1] + m02 * matrix.m[2][1];
	m[0][2] = m00 * matrix.m[0][2] + m01 * matrix.m[1][2] + m02 * matrix.m[2][2];

	m[1][0] = m10 * matrix.m[0][0] + m11 * matrix.m[1][0] + m12 * matrix.m[2][0];
	m[1][1] = m10 * matrix.m[0][1] + m11 * matrix.m[1][1] + m12 * matrix.m[2][1];
	m[1][2] = m10 * matrix.m[0][2] + m11 * matrix.m[1][2] + m12 * matrix.m[2][2];

	m[2][0] = m20 * matrix.m[0][0] + m21 * matrix.m[1][0] + m22 * matrix.m[2][0];
	m[2][1] = m20 * matrix.m[0][1] + m21 * matrix.m[1][1] + m22 * matrix.m[2][1];
	m[2][2] = m20 * matrix.m[0][2] + m21 * matrix.m[1][2] + m22 * matrix.m[2][2];

	return *this;
}

Matrix3& Matrix3::operator*=(_float scalar) {
	m[0][0] *= scalar;
	m[0][1] *= scalar;
	m[0][2] *= scalar;
	m[1][0] *= scalar;
	m[1][1] *= scalar;
	m[1][2] *= scalar;
	m[2][0] *= scalar;
	m[2][1] *= scalar;
	m[2][2] *= scalar;

	return *this;
}

Matrix3& Matrix3::operator/=(_float scalar) {
	m[0][0] /= scalar;
	m[0][1] /= scalar;
	m[0][2] /= scalar;
	m[1][0] /= scalar;
	m[1][1] /= scalar;
	m[1][2] /= scalar;
	m[2][0] /= scalar;
	m[2][1] /= scalar;
	m[2][2] /= scalar;

	return *this;
}

Matrix3 Matrix3::operator+(const Matrix3& matrix) const {
	Matrix3 returnmatrix = *this;

	return returnmatrix += matrix;
}

Matrix3 Matrix3::operator-(const Matrix3& matrix) const {
	Matrix3 returnmatrix = *this;

	return returnmatrix -= matrix;
}

Matrix3 Matrix3::operator*(const Matrix3& matrix) const {
	Matrix3 returnmatrix = *this;

	return returnmatrix *= matrix;
}

Matrix3 Matrix3::operator*(_float scalar) const {
	Matrix3 returnmatrix = *this;

	return returnmatrix *= scalar;
}

Matrix3 Matrix3::operator/(_float scalar) const {
	Matrix3 returnmatrix = *this;

	return returnmatrix /= scalar;
}

_float Matrix3::Determinant() const {
	return m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1] - m[0][0] * m[1][2] * m[2][1] - m[0][1] * m[1][0] * m[2][2] - m[0][2] * m[1][1] * m[2][0];
}

Matrix3& Matrix3::Identity() {
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;

	return *this;
}

Matrix3& Matrix3::Transpose() {
	_float m01 = m[0][1], m02 = m[0][2], m10 = m[1][0], m12 = m[1][2], m20 = m[2][0], m21 = m[2][1];

	m[0][1] = m10;
	m[0][2] = m20;
	m[1][0] = m01;
	m[1][2] = m21;
	m[2][0] = m02;
	m[2][1] = m12;

	return *this;
}

Matrix3& Matrix3::Inverse() {
	_float determinant = Determinant();

	if (determinant != 0.0f) {
		Adjoint();

		m[0][0] /= determinant;
		m[0][1] /= determinant;
		m[0][2] /= determinant;
		m[1][0] /= determinant;
		m[1][1] /= determinant;
		m[1][2] /= determinant;
		m[2][0] /= determinant;
		m[2][1] /= determinant;
		m[2][2] /= determinant;
	}

	return *this;
}

Matrix3& Matrix3::Adjoint() {
	_float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m10 = m[1][0], m11 = m[1][1],
	       m12 = m[1][2], m20 = m[2][0], m21 = m[2][1], m22 = m[2][2];

	m[0][0] = m11 * m22 - m12 * m21;
	m[0][1] = m02 * m21 - m01 * m22;
	m[0][2] = m01 * m12 - m02 * m11;
	m[1][0] = m12 * m20 - m10 * m22;
	m[1][1] = m00 * m22 - m02 * m20;
	m[1][2] = m02 * m10 - m00 * m12;
	m[2][0] = m10 * m21 - m11 * m20;
	m[2][1] = m01 * m20 - m00 * m21;
	m[2][2] = m00 * m11 - m01 * m10;

	return *this;
}

_void Matrix3::ToRotation(Quaternion& quaternion) const {
	// Determine which of w, x, y, or z has the largest absolute value.
	_float fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];
	_float fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
	_float fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
	_float fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];

	_int biggestIndex = 0;
	_float fourBiggestSquaredMinus1 = fourWSquaredMinus1;

	if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) {
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}

	if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) {
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}

	if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) {
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}

	_float biggestVal = Math::Sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
	_float mult = 0.25f / biggestVal;

	// Apply table to compute quaternion values.
	switch (biggestIndex) {
		case 0:
			quaternion.w = biggestVal;
			quaternion.x = (m[1][2] - m[2][1]) * mult;
			quaternion.y = (m[2][0] - m[0][2]) * mult;
			quaternion.z = (m[0][1] - m[1][0]) * mult;
			break;

		case 1:
			quaternion.x = biggestVal;
			quaternion.w = (m[1][2] - m[2][1]) * mult;
			quaternion.y = (m[0][1] + m[1][0]) * mult;
			quaternion.z = (m[2][0] + m[0][2]) * mult;
			break;

		case 2:
			quaternion.y = biggestVal;
			quaternion.w = (m[2][0] - m[0][2]) * mult;
			quaternion.x = (m[0][1] + m[1][0]) * mult;
			quaternion.z = (m[1][2] + m[2][1]) * mult;
			break;

		case 3:
			quaternion.z = biggestVal;
			quaternion.w = (m[0][1] - m[1][0]) * mult;
			quaternion.x = (m[2][0] + m[0][2]) * mult;
			quaternion.y = (m[1][2] + m[2][1]) * mult;
			break;
	}
}

Matrix3& Matrix3::FromRotation(const Quaternion& quaternion) {
	_float xx = quaternion.x * quaternion.x * 2.0f, yy = quaternion.y * quaternion.y * 2.0f, zz = quaternion.z * quaternion.z * 2.0f;
	_float xy = quaternion.x * quaternion.y * 2.0f, zw = quaternion.z * quaternion.w * 2.0f, xz = quaternion.x * quaternion.z * 2.0f;
	_float yw = quaternion.y * quaternion.w * 2.0f, yz = quaternion.y * quaternion.z * 2.0f, xw = quaternion.x * quaternion.w * 2.0f;

	m[0][0] = 1.0f - yy - zz;
	m[0][1] = xy + zw;
	m[0][2] = xz - yw;
	m[1][0] = xy - zw;
	m[1][1] = 1.0f - xx - zz;
	m[1][2] = yz + xw;
	m[2][0] = xz + yw;
	m[2][1] = yz - xw;
	m[2][2] = 1.0f - xx - yy;

	return *this;
}

_void Matrix3::AnalysisMatrix(Vector2& position, Vector2& scale, _float& radian) const {
	position.x = m[2][0];
	position.y = m[2][1];

	//scale.x = Math::Sqrt( m[0][0] * m[0][0] + m[0][1] * m[0][1] );
	//scale.x = Math::Sqrt( m[1][0] * m[1][0] + m[1][1] * m[0][1] );

	Vector2 tmp = Vector2::cXAxis;
	tmp *= *this;
	tmp -= position;
	scale.x = tmp.Magnitude();

	// _float radian2 = Vector2::GetRotateAngle( Vector2::cXAxis, tmp );

	tmp = Vector2::cYAxis;
	tmp *= *this;
	tmp -= position;
	scale.y = tmp.Magnitude();

	radian = Vector2::GetRotateAngle(Vector2::cYAxis, tmp);
}

_void Matrix3::ToEulerAngles(EulerAngles& angles) const {
	_float sh = -m[0][2];
	if (sh <= -1.0f)
		angles.mHeading = -Math::cPi * 0.5f;
	else if (sh >= 1.0f)
		angles.mHeading = Math::cPi * 0.5f;
	else
		angles.mHeading = Math::Asin(sh);

	if (sh > 1.0f - Math::cFloatEpsilon) {
		angles.mBank = 0.0f;
		angles.mPitch = Math::Atan(m[1][0], m[2][0]);
	} else {
		angles.mBank = Math::Atan(m[0][1], m[0][0]);
		angles.mPitch = Math::Atan(m[1][2], m[2][2]);
	}
}

Matrix3 Matrix3::CreateTranslation(_float x, _float y) {
	Matrix3 transform;
	transform.m[0][0] = 1.0f;
	transform.m[0][1] = 0.0f;
	transform.m[0][2] = 0.0f;
	transform.m[1][0] = 0.0f;
	transform.m[1][1] = 1.0f;
	transform.m[1][2] = 0.0f;
	transform.m[2][0] = x;
	transform.m[2][1] = y;
	transform.m[2][2] = 1.0f;

	return transform;
}

Matrix3 Matrix3::CreateTranslation(const Vector2& vector) {
	return CreateTranslation(vector.x, vector.y);
}

Matrix3 Matrix3::CreateScaling(_float x, _float y, _float z) {
	Matrix3 transform;
	transform.m[0][0] = x;
	transform.m[0][1] = 0.0f;
	transform.m[0][2] = 0.0f;
	transform.m[1][0] = 0.0f;
	transform.m[1][1] = y;
	transform.m[1][2] = 0.0f;
	transform.m[2][0] = 0.0f;
	transform.m[2][1] = 0.0f;
	transform.m[2][2] = z;

	return transform;
}

Matrix3 Matrix3::CreateScaling(const Vector3& vector) {
	return CreateScaling(vector.x, vector.y, vector.z);
}

Matrix3 Matrix3::CreateScaling(const Vector3& vector, _float factor) {
	Vector3 normal(vector);
	normal.Normalize();

	_float k = factor - 1.0f;
	_float xx = normal.x * normal.x;
	_float yy = normal.y * normal.y;
	_float zz = normal.z * normal.z;
	_float xy = normal.x * normal.y;
	_float yz = normal.y * normal.z;
	_float zx = normal.z * normal.x;

	Matrix3 transform;
	transform.m[0][0] = 1.0f + k * xx;
	transform.m[0][1] = k * xy;
	transform.m[0][2] = k * zx;
	transform.m[1][0] = k * xy;
	transform.m[1][1] = 1.0f + k * yy;
	transform.m[1][2] = k * yz;
	transform.m[2][0] = k * zx;
	transform.m[2][1] = k * yz;
	transform.m[2][2] = 1.0f + k * zz;

	return transform;
}

Matrix3 Matrix3::CreateRotation(_float radian) {
	_float sincos_value[2];
	Math::SinCos(radian, sincos_value);

	Matrix3 transform;
	transform.m[0][0] = sincos_value[1];
	transform.m[0][1] = sincos_value[0];
	transform.m[0][2] = 0.0f;
	transform.m[1][0] = -sincos_value[0];
	transform.m[1][1] = sincos_value[1];
	transform.m[1][2] = 0.0f;
	transform.m[2][0] = 0.0f;
	transform.m[2][1] = 0.0f;
	transform.m[2][2] = 1.0f;

	return transform;
}

Matrix3 Matrix3::CreateRotationX(_float radian) {
	_float sincos_value[2];
	Math::SinCos(radian, sincos_value);

	Matrix3 transform;
	transform.m[0][0] = 1.0f;
	transform.m[0][1] = 0.0f;
	transform.m[0][2] = 0.0f;
	transform.m[1][0] = 0.0f;
	transform.m[1][1] = sincos_value[1];
	transform.m[1][2] = sincos_value[0];
	transform.m[2][0] = 0.0f;
	transform.m[2][1] = -sincos_value[0];
	transform.m[2][2] = sincos_value[1];

	return transform;
}

Matrix3 Matrix3::CreateRotationY(_float radian) {
	_float sincos_value[2];
	Math::SinCos(radian, sincos_value);

	Matrix3 transform;
	transform.m[0][0] = sincos_value[1];
	transform.m[0][1] = 0.0f;
	transform.m[0][2] = -sincos_value[0];
	transform.m[1][0] = 0.0f;
	transform.m[1][1] = 1.0f;
	transform.m[1][2] = 0.0f;
	transform.m[2][0] = sincos_value[0];
	transform.m[2][1] = 0.0f;
	transform.m[2][2] = sincos_value[1];

	return transform;
}

Matrix3 Matrix3::CreateRotationZ(_float radian) {
	_float sincos_value[2];
	Math::SinCos(radian, sincos_value);

	Matrix3 transform;
	transform.m[0][0] = sincos_value[1];
	transform.m[0][1] = sincos_value[0];
	transform.m[0][2] = 0.0f;
	transform.m[1][0] = -sincos_value[0];
	transform.m[1][1] = sincos_value[1];
	transform.m[1][2] = 0.0f;
	transform.m[2][0] = 0.0f;
	transform.m[2][1] = 0.0f;
	transform.m[2][2] = 1.0f;

	return transform;
}

Matrix3 Matrix3::CreateRotation(const Vector3& axis, _float radian) {
	_float sincos_value[2];
	Math::SinCos(radian, sincos_value);

	_float cosreverse = 1.0f - sincos_value[1];

	Vector3 axisnormal(axis);
	axisnormal.Normalize();

	Matrix3 transform;

	transform.m[0][0] = cosreverse * axisnormal.x * axisnormal.x + sincos_value[1];
	transform.m[0][1] = cosreverse * axisnormal.x * axisnormal.y + sincos_value[0] * axisnormal.z;
	transform.m[0][2] = cosreverse * axisnormal.x * axisnormal.z - sincos_value[0] * axisnormal.y;

	transform.m[1][0] = cosreverse * axisnormal.x * axisnormal.y - sincos_value[0] * axisnormal.z;
	transform.m[1][1] = cosreverse * axisnormal.y * axisnormal.y + sincos_value[1];
	transform.m[1][2] = cosreverse * axisnormal.y * axisnormal.z + sincos_value[0] * axisnormal.x;

	transform.m[2][0] = cosreverse * axisnormal.x * axisnormal.z + sincos_value[0] * axisnormal.y;
	transform.m[2][1] = cosreverse * axisnormal.y * axisnormal.z - sincos_value[0] * axisnormal.x;
	transform.m[2][2] = cosreverse * axisnormal.z * axisnormal.z + sincos_value[1];

	return transform;
}

Matrix3 Matrix3::CreateProjectXY() {
	Matrix3 transform;
	transform.m[0][0] = 1.0f;
	transform.m[0][1] = 0.0f;
	transform.m[0][2] = 0.0f;
	transform.m[1][0] = 0.0f;
	transform.m[1][1] = 1.0f;
	transform.m[1][2] = 0.0f;
	transform.m[2][0] = 0.0f;
	transform.m[2][1] = 0.0f;
	transform.m[2][2] = 0.0f;

	return transform;
}

Matrix3 Matrix3::CreateProjectYZ() {
	Matrix3 transform;
	transform.m[0][0] = 0.0f;
	transform.m[0][1] = 0.0f;
	transform.m[0][2] = 0.0f;
	transform.m[1][0] = 0.0f;
	transform.m[1][1] = 1.0f;
	transform.m[1][2] = 0.0f;
	transform.m[2][0] = 0.0f;
	transform.m[2][1] = 0.0f;
	transform.m[2][2] = 1.0f;

	return transform;
}

Matrix3 Matrix3::CreateProjectZX() {
	Matrix3 transform;
	transform.m[0][0] = 1.0f;
	transform.m[0][1] = 0.0f;
	transform.m[0][2] = 0.0f;
	transform.m[1][0] = 0.0f;
	transform.m[1][1] = 0.0f;
	transform.m[1][2] = 0.0f;
	transform.m[2][0] = 0.0f;
	transform.m[2][1] = 0.0f;
	transform.m[2][2] = 1.0f;

	return transform;
}

Matrix3 Matrix3::CreateProject(const Vector3& vector) {
	return CreateScaling(vector, 0.0f);
}

Matrix3 Matrix3::CreateRefectionXY() {
	Matrix3 transform;
	transform.m[0][0] = 1.0f;
	transform.m[0][1] = 0.0f;
	transform.m[0][2] = 0.0f;
	transform.m[1][0] = 0.0f;
	transform.m[1][1] = 1.0f;
	transform.m[1][2] = 0.0f;
	transform.m[2][0] = 0.0f;
	transform.m[2][1] = 0.0f;
	transform.m[2][2] = -1.0f;

	return transform;
}

Matrix3 Matrix3::CreateRefectionYZ() {
	Matrix3 transform;
	transform.m[0][0] = -1.0f;
	transform.m[0][1] = 0.0f;
	transform.m[0][2] = 0.0f;
	transform.m[1][0] = 0.0f;
	transform.m[1][1] = 1.0f;
	transform.m[1][2] = 0.0f;
	transform.m[2][0] = 0.0f;
	transform.m[2][1] = 0.0f;
	transform.m[2][2] = 1.0f;

	return transform;
}

Matrix3 Matrix3::CreateRefectionZX() {
	Matrix3 transform;
	transform.m[0][0] = 1.0f;
	transform.m[0][1] = 0.0f;
	transform.m[0][2] = 0.0f;
	transform.m[1][0] = 0.0f;
	transform.m[1][1] = -1.0f;
	transform.m[1][2] = 0.0f;
	transform.m[2][0] = 0.0f;
	transform.m[2][1] = 0.0f;
	transform.m[2][2] = 1.0f;

	return transform;
}

Matrix3 Matrix3::CreateRefection(const Vector3& vector) {
	return CreateScaling(vector, -1.0f);
}

Matrix3 Matrix3::CreateFromRegion(const RectF& region) {
	return CreateFromRegion(region, Vector2(region.GetWidth(), region.GetHeight()), Vector2::cOrigin);
}

Matrix3 Matrix3::CreateFromRegion(const RectF& region, const Vector2& size) {
	return CreateFromRegion(region, size, Vector2::cOrigin);
}

Matrix3 Matrix3::CreateFromRegion(const RectF& region, const Vector2& size, const Vector2& base_offset) {
	// The offset and scale
	Vector3 scale(1.0f, 1.0f, 1.0f);

	// Get the scale
	if (size.x > region.GetWidth() || size.y > region.GetHeight()) {
		scale.x = region.GetSize().x / size.x;
		scale.y = region.GetSize().y / size.y;

		// Keep the ratio
		Ratio ratio(size.x, size.y);
		Vector2 updatedSize = ratio.UpdateSize(region.GetSize().x, region.GetSize().y);

		// Update the scale
		scale.x = EGE_RATIO(updatedSize.x, size.x);
		scale.y = EGE_RATIO(updatedSize.y, size.y);
	}

	// Get the region size
	const PointF& region_size = region.GetSize();

	// Get the offset
	Vector2 offset;
	offset.x = region.l + (region_size.x / 2.0f);
	offset.y = region.t + (region_size.y / 2.0f);

	// Fix the position by base offset
	offset.x -= base_offset.x * scale.x;
	offset.y -= base_offset.y * scale.y;

	// Build the transform
	Matrix3 transform = CreateScaling(scale) * CreateTranslation(offset);
	return transform;
}