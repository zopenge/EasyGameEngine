//! @file     Vector2.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

class Matrix2;
class Matrix3;

//----------------------------------------------------------------------------
// Vector2
//----------------------------------------------------------------------------

//! @export_script_class_cd("Vector2", "This class represents a 2D vector")
class Vector2 {
 public:
  //! @export_script_property("X-component of the vector")
  _float x;
  //! @export_script_property("Y-component of the vector")
  _float y;

 public:
  //! The origin vector.
  static const Vector2 cOrigin;
  //! The identity vector.
  static const Vector2 cIdentity;
  //! The x-axis vector.
  static const Vector2 cXAxis;
  //! The y-axis vector.
  static const Vector2 cYAxis;
  //! The maximal vector.
  static const Vector2 cMaxVector;
  //! The minimal vector.
  static const Vector2 cMinVector;

 public:
  //! Constructor, create a vector without sets x, y components.
  //! @param		none
  Vector2();
  //! Constructor, create a vector and sets x, y components.
  //! @param		xx			X-component of the vector.
  //! @param		yy			Y-component of the vector.
  Vector2(_float xx, _float yy);

  //! Get positive vector.
  //! @param		none
  //! @return		The positive vector.
  Vector2 operator+() const;
  //! Get negative vector.
  //! @param		none
  //! @return		The negative vector.
  Vector2 operator-() const;

  //! Copy a vector to current vector, and save result in current one.
  //! @param		vector		The vector to copy.
  //! @return		The result vector.
  Vector2& operator=(const Vector2& vector);

  //! Add a vector to current vector, and save result in current one.
  //! @param		vector		The vector to add.
  //! @return		The result vector of addition.
  Vector2& operator+=(const Vector2& vector);
  //! Subtract a vector from current vector, and save result in current one.
  //! @param		vector		The vector to subtract.
  //! @return		The result vector of subtraction.
  Vector2& operator-=(const Vector2& vector);
  //! Multiply a scalar to current vector, and save result in current one.
  //! @param		scalar		The scalar to multiply.
  //! @return		The result vector of multiplication.
  Vector2& operator*=(_float scalar);
  //! Multiply a vector to current vector, and save result in current one.
  //! @param		vector		The vector to multiply.
  //! @return		The result vector of multiplication.
  Vector2& operator*=(const Vector2& vector);
  //! Divide a scalar to current vector, and save result in current one.
  //! @param		scalar		The scalar to divide.
  //! @return		The result vector of division.
  Vector2& operator/=(_float scalar);
  //! Divide a vector to current vector, and save result in current one.
  //! @param		vector		The vector to divide.
  //! @return		The result vector of division.
  Vector2& operator/=(const Vector2& vector);

  //! Multiply a matrix to current vector, and save result in current one.
  //! @param		matrix		The matrix to multiply.
  //! @return		The result vector of multiplication.
  Vector2& operator*=(const Matrix2& matrix);
  //! Multiply a matrix to current vector, and save result in current one.
  //! @param		matrix		The matrix to multiply.
  //! @return		The result vector of multiplication.
  Vector2& operator*=(const Matrix3& matrix);

  //! Add a vector to current vector, return a new vector to save result.
  //! @param		vector		The vector to add.
  //! @return		The result vector of addition.
  Vector2 operator+(const Vector2& vector) const;
  //! Subtract a vector from current vector, return a new vector to save result.
  //! @param		vector		The vector to subtract.
  //! @return		The result vector of subtraction.
  Vector2 operator-(const Vector2& vector) const;
  //! Multiply a scalar to current vector, return a new vector to save result.
  //! @param		scalar		The scalar to multiply.
  //! @return		The result vector of multiplication.
  Vector2 operator*(_float scalar) const;
  //! Multiply a vector to current vector, return a new vector to save result.
  //! @param		vector		The vector to multiply.
  //! @return		The result vector of multiplication.
  Vector2 operator*(const Vector2& vector) const;
  //! Divide a scalar to current vector, return a new vector to save result.
  //! @param		scalar		The scalar to divide.
  //! @return		The result vector of division.
  Vector2 operator/(_float scalar) const;
  //! Divide a vector to current vector, return a new vector to save result.
  //! @param		vector		The vector to divide.
  //! @return		The result vector of division.
  Vector2 operator/(const Vector2& vector) const;

  //! Compare two vectors.
  //! @param		vector		The vector to compare with.
  //! @return		True if they are identical, false otherwise.
  _ubool operator==(const Vector2& vector) const;
  //! Compare two vectors.
  //! @param		vector		The vector to compare with.
  //! @return		True if they are not identical, false otherwise.
  _ubool operator!=(const Vector2& vector) const;

  //! Multiply a matrix to current vector, return a new vector to save result.
  //! @param		matrix		The matrix to multiply.
  //! @return		The result vector of multiplication.
  Vector2 operator*(const Matrix2& matrix) const;
  //! Multiply a matrix to current vector, return a new vector to save result.
  //! @param		matrix		The matrix to multiply.
  //! @return		The result vector of multiplication.
  Vector2 operator*(const Matrix3& matrix) const;

  //! @export_script_method("Compare two vectors with error margin")
  //! @param		vector		The vector to compare with.
  //! @param		margin		The margin that allows some error.
  //! @return		True if they are identical, false otherwise.
  _ubool Equal(const Vector2& vector,
               _float margin = Math::cFloatEpsilon) const;

  //! Make the current vector absolute, that all coordinates are nonnegative.
  //! @param		none
  //! @return		The absolute vector.
  Vector2& Absolute();
  //! Make the current vector normalized, that has one unit magnitude.
  //! @param		none
  //! @return		The normalized vector.
  Vector2& Normalize();

  //! Make the current vector normalized by bounding box, that x, y, z is from 0
  //! ~ 1
  //! @param		none
  //! @return		The normalized vector.
  Vector2& NormalizeByBoundingBox(const Vector2& bounding_min,
                                  const Vector2& bounding_max);

  //! @export_script_method("Calculates vector magnitude")
  //! @param		none
  //! @return		The magnitude of vector.
  _float Magnitude() const;
  //! @export_script_method("Calculates the square of vector magnitude, this
  //! function is faster than Magnitude")
  //! @param		none
  //! @return		The square of magnitude of vector.
  _float MagnitudeSquared() const;

  //! Round
  //! @paranm		none.
  //! @return		The rounded vector
  Vector2& Round();

  //! Calculates dot product of two vectors.
  //! @param		vector1		Source vector 1.
  //! @param		vector2		Source vector 2.
  //! @return		The dot product result.
  static _float Dot(const Vector2& vector1, const Vector2& vector2);
  //! Calculates cross product of two vectors, return the z-component.
  //! @param		vector1		Source vector 1.
  //! @param		vector2		Source vector 2.
  //! @return		The z-component of cross product result.
  static _float Cross(const Vector2& vector1, const Vector2& vector2);
  //! Calculates vector by project one vector to another.
  //! @param		vector1		The vector to be projected.
  //! @param		vector2		The project reference vector.
  //! @return		The projected vector, that has same direction of
  //! vector2.
  static Vector2 Project(const Vector2& vector1, const Vector2& vector2);
  //! Calculates vector by plumb one vector to another.
  //! @param		vector1		The vector to be projected.
  //! @param		vector2		The project reference vector.
  //! @return		The plumbed vector, that is vertical of vector2.
  static Vector2 Plumb(const Vector2& vector1, const Vector2& vector2);
  //! Calculates linear interpolation of two vectors.
  //! @param		vector1		Source vector 1.
  //! @param		vector2		Target vector 2.
  //! @param		factor		The interpolation factor, will clamp to
  //! between 0 to 1.
  //! @return		The result vector of interpolation, vector1 + ( vector2
  //! - vector1 ) * factor.
  static Vector2 Lerp(const Vector2& vector1, const Vector2& vector2,
                      _float factor);
  //! Calculates radian of two vectors.
  //! @param		vector1		Source vector 1.
  //! @param		vector2		Target vector 2.
  //! @return		The result vector of radian.
  static _float Radian(const Vector2& vector1, const Vector2& vector2);

  //! Calculates angle vector1 rotate to vector2;
  //! @param		vector1		rotation begin vector;
  //! @param		vector2		rotation end vector;
  //! @return		The angle vector1 rotate to vector2;
  static _float GetRotateAngle(const Vector2& vector1, const Vector2& vector2);
  //! Compares two arguments and returns the smaller one.
  //! @param		value1		Vector2 value 1.
  //! @param		value2		Vector2 value 2.
  //! @return		The smaller one.
  static Vector2 Min(const Vector2& vector1, const Vector2& vector2);
  //! Compares two arguments and returns the larger one.
  //! @param		value1		Vector2 value 1.
  //! @param		value2		Vector2 value 2.
  //! @return		The larger one.
  static Vector2 Max(const Vector2& vector1, const Vector2& vector2);
  //! Clamp value into the range specified by min and max.
  //! @param		value		Integer value to be clamped.
  //! @param		min			Minimal value of the range.
  //! @param		max			Maximal value of the range.
  //! @return		The clamped value.
  static Vector2 Clamp(const Vector2& vector, const Vector2& min,
                       const Vector2& max);
};

//----------------------------------------------------------------------------
// Vector2 Implementation
//----------------------------------------------------------------------------

inline Vector2::Vector2() {}

inline Vector2::Vector2(_float xx, _float yy) : x(xx), y(yy) {}

inline Vector2 Vector2::operator+() const { return Vector2(x, y); }

inline Vector2 Vector2::operator-() const { return Vector2(-x, -y); }

inline Vector2& Vector2::operator=(const Vector2& vector) {
  x = vector.x;
  y = vector.y;

  return *this;
}

inline Vector2& Vector2::operator+=(const Vector2& vector) {
  x += vector.x;
  y += vector.y;

  return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& vector) {
  x -= vector.x;
  y -= vector.y;

  return *this;
}

inline Vector2& Vector2::operator*=(_float scalar) {
  x *= scalar;
  y *= scalar;

  return *this;
}

inline Vector2& Vector2::operator*=(const Vector2& vector) {
  x *= vector.x;
  y *= vector.y;

  return *this;
}

inline Vector2& Vector2::operator/=(_float scalar) {
  x /= scalar;
  y /= scalar;

  return *this;
}

inline Vector2& Vector2::operator/=(const Vector2& vector) {
  x /= vector.x;
  y /= vector.y;

  return *this;
}

inline Vector2 Vector2::operator+(const Vector2& vector) const {
  return Vector2(x + vector.x, y + vector.y);
}

inline Vector2 Vector2::operator-(const Vector2& vector) const {
  return Vector2(x - vector.x, y - vector.y);
}

inline Vector2 Vector2::operator*(_float scalar) const {
  return Vector2(x * scalar, y * scalar);
}

inline Vector2 Vector2::operator*(const Vector2& vector) const {
  return Vector2(x * vector.x, y * vector.y);
}

inline Vector2 Vector2::operator/(_float scalar) const {
  return Vector2(x / scalar, y / scalar);
}

inline Vector2 Vector2::operator/(const Vector2& vector) const {
  return Vector2(x / vector.x, y / vector.y);
}

inline _ubool Vector2::operator==(const Vector2& vector) const {
  return x == vector.x && y == vector.y;
}

inline _ubool Vector2::operator!=(const Vector2& vector) const {
  return x != vector.x || y != vector.y;
}

inline _ubool Vector2::Equal(const Vector2& vector, _float margin) const {
  if (Math::Abs(x - vector.x) > margin) return _false;

  if (Math::Abs(y - vector.y) > margin) return _false;

  return _true;
}

inline Vector2& Vector2::Absolute() {
  if (x < 0.0f) x = -x;

  if (y < 0.0f) y = -y;

  return *this;
}

inline Vector2& Vector2::Normalize() {
  _float magnitude = Magnitude();

  if (magnitude > 0.0f) {
    x /= magnitude;
    y /= magnitude;
  } else {
    x = 1.0f;
    y = 0.0f;
  }

  return *this;
}

inline Vector2& Vector2::NormalizeByBoundingBox(const Vector2& bounding_min,
                                                const Vector2& bounding_max) {
  Vector2 bounding_size = bounding_max - bounding_min;

  x = bounding_size.x == 0.0f ? 0.0f : ((x - bounding_min.x) / bounding_size.x);
  y = bounding_size.y == 0.0f ? 0.0f : ((y - bounding_min.y) / bounding_size.y);

  return *this;
}

inline _float Vector2::Magnitude() const { return Math::Sqrt(x * x + y * y); }

inline _float Vector2::MagnitudeSquared() const { return x * x + y * y; }

inline _float Vector2::Dot(const Vector2& vector1, const Vector2& vector2) {
  return vector1.x * vector2.x + vector1.y * vector2.y;
}

inline _float Vector2::Cross(const Vector2& vector1, const Vector2& vector2) {
  return vector1.x * vector2.y - vector1.y * vector2.x;
}

inline Vector2& Vector2::Round() {
  x = _float(_int(x + 0.5f));
  y = _float(_int(y + 0.5f));
  return *this;
}

inline Vector2 Vector2::Min(const Vector2& vector1, const Vector2& vector2) {
  _float x = Math::Min(vector1.x, vector2.x);
  _float y = Math::Min(vector1.y, vector2.y);
  return Vector2(x, y);
}

inline Vector2 Vector2::Max(const Vector2& vector1, const Vector2& vector2) {
  _float x = Math::Max(vector1.x, vector2.x);
  _float y = Math::Max(vector1.y, vector2.y);
  return Vector2(x, y);
}

inline Vector2 Vector2::Clamp(const Vector2& vector, const Vector2& min,
                              const Vector2& max) {
  _float x = Math::Clamp(vector.x, min.x, max.x);
  _float y = Math::Clamp(vector.x, min.y, max.y);
  return Vector2(x, y);
}

}  // namespace EGE