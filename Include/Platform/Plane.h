#pragma once

namespace EGE {

/// <summary>
/// The plane shape.
/// </summary>
class Plane {
public:
	static const Plane cXYPlane;
	static const Plane cYZPlane;
	static const Plane cZXPlane;

	_float a;
	_float b;
	_float c;
	_float d;

public:
	inline Plane();
	inline Plane(_float aa, _float bb, _float cc, _float dd);
	inline Plane(const Vector3& position, const Vector3& normal);
	inline Plane(const Vector3& vector1, const Vector3& vector2,
	             const Vector3& vector3);

	inline Plane operator+() const;
	inline Plane operator-() const;

	inline Plane& operator*=(const Matrix4& matrix);
	inline Plane operator*(const Matrix4& matrix) const;

	inline _ubool operator==(const Plane& plane) const;
	inline _ubool operator!=(const Plane& plane) const;

	inline const Vector4& ToVector4() const;

	inline Vector3 Normal() const;
	inline _float Distance(const Vector3& vector) const;

	inline Vector3 Reflect(const Vector3& vector) const;
	inline Matrix4 GetReflectionMatrix() const;

	inline _ubool IsEqual(const Plane& plane, _float degree_tolerance) const;
};

Plane::Plane() {
}

Plane::Plane(_float aa, _float bb, _float cc, _float dd)
    : a(aa), b(bb), c(cc), d(dd) {
}

Plane::Plane(const Vector3& position, const Vector3& normal) {
	Vector3 n = normal;
	n.Normalize();

	a = n.x;
	b = n.y;
	c = n.z;
	d = -Vector3::Dot(position, n);
}

Plane::Plane(const Vector3& vector1, const Vector3& vector2,
             const Vector3& vector3) {
	Vector3 edge1 = vector2 - vector1;
	Vector3 edge2 = vector3 - vector1;
	Vector3 n = Vector3::Cross(edge1, edge2).Normalize();

	a = n.x;
	b = n.y;
	c = n.z;
	d = -Vector3::Dot(vector1, n);
}

Plane& Plane::operator*=(const Matrix4& matrix) {
	Vector3 normal(a, b, c);
	normal *= matrix.GetRotationMatrix();

	Vector3 vector = Vector3(a, b, c) * -d * matrix;

	a = normal.x;
	b = normal.y;
	c = normal.z;
	d = -Vector3::Dot(vector, normal);

	return *this;
}

Plane Plane::operator*(const Matrix4& matrix) const {
	Plane returnplane(*this);

	return returnplane *= matrix;
}

Plane Plane::operator+() const {
	return Plane(a, b, c, d);
}

Plane Plane::operator-() const {
	return Plane(-a, -b, -c, -d);
}

_ubool Plane::operator==(const Plane& plane) const {
	return a == plane.a && b == plane.b && c == plane.c && d == plane.d;
}

_ubool Plane::operator!=(const Plane& plane) const {
	return a != plane.a || b != plane.b || c != plane.c || d != plane.d;
}

const Vector4& Plane::ToVector4() const {
	return (const Vector4&)*this;
}

Vector3 Plane::Normal() const {
	return Vector3(a, b, c);
}

_float Plane::Distance(const Vector3& vector) const {
	return a * vector.x + b * vector.y + c * vector.z + d;
}

Vector3 Plane::Reflect(const Vector3& vector) const {
	_float length = vector.Magnitude();

	return (Vector3(vector).Normalize() + Vector3(a, b, c) * 2.0f) * length;
}

Matrix4 Plane::GetReflectionMatrix() const {
	_float ab, ac, bc;
	ab = a * b;
	ac = a * c;
	bc = b * c;
	return Matrix4(-2.0f * a * a + 1.0f, -2.0f * ab, -2.0f * ac, 0.0f, -2.0f * ab,
	               -2.0f * b * b + 1.0f, -2.0f * bc, 0.0f, -2.0f * ac, -2.0f * bc,
	               -2.0f * c * c + 1.0f, 0.0f, -2.0f * a * d, -2.0f * b * d,
	               -2.0f * c * d, 1.0f);
}

_ubool Plane::IsEqual(const Plane& plane, _float degree_tolerance) const {
	if (Math::Abs(d - plane.d) > degree_tolerance / 100.0f) return _false;

	Vector3 normal_1 = Normal().Normalize();
	Vector3 normal_2 = plane.Normal().Normalize();
	_float dotvalue = Vector3::Dot(normal_1, normal_2);
	_float angle = Math::Acos(dotvalue);
	if (Math::Abs(angle) > Math::Degree2Radian(degree_tolerance)) return _false;

	return _true;
}

} // namespace EGE