//! @file     Matrix2.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Matrix2
//----------------------------------------------------------------------------

class Matrix2 {
 public:
  //! The component of the matrix.
  _float m[2][2];

 public:
  //! The zero matrix.
  static const Matrix2 cZero;
  //! The identity matrix.
  static const Matrix2 cIdentity;

 public:
  //! Constructor, create a matrix withsets components.
  //! @param none
  Matrix2();
  //! Constructor, create a matrix and sets components.
  //! @param m00~m11  The component of the matrix.
  Matrix2(_float m00, _float m01, _float m10, _float m11);
  Matrix2(const Vector2& scale, _float radian);

  //! Get positive matrix.
  //! @param none
  //! @return The positive matrix.
  Matrix2 operator+() const;
  //! Get negative matrix.
  //! @param none
  //! @return The negative matrix.
  Matrix2 operator-() const;

  //! Get a row from matrix.
  //! @param row   Rom number of the matrix.
  //! @return The row vector.
  Vector2 GetRow(_dword row) const;
  //! Get a column from matrix.
  //! @param column  Column number of the matrix.
  //! @return The column vector.
  Vector2 GetColumn(_dword column) const;

  //! Add a matrix to current matrix, and save result current one.
  //! @param matrix  The matrix to add.
  //! @return The result matrix of addition.
  Matrix2& operator+=(const Matrix2& matrix);
  //! Subtract a matrix to current matrix, and save result current one.
  //! @param matrix  The matrix to subtract.
  //! @return The result matrix of subtraction.
  Matrix2& operator-=(const Matrix2& matrix);
  //! Multiply a matrix to current matrix, and save result current one.
  //! @param matrix  The matrix to multiply.
  //! @return The result matrix of multiplication.
  Matrix2& operator*=(const Matrix2& matrix);
  //! Multiply a scalar to current matrix, and save result current one.
  //! @param scalar  The scalar to multiply.
  //! @return The result matrix of multiplication.
  Matrix2& operator*=(_float scalar);
  //! Divide a scalar to current matrix, and save result current one.
  //! @param scalar  The scalar to divide.
  //! @return The result quaternion of division.
  Matrix2& operator/=(_float scalar);

  //! Add a matrix to current matrix, return a new matrix to save result.
  //! @param matrix  The matrix to add.
  //! @return The result matrix of addition.
  Matrix2 operator+(const Matrix2& matrix) const;
  //! Subtract a matrix to current matrix, return a new matrix to save result.
  //! @param matrix  The matrix to subtract.
  //! @return The result matrix of subtraction.
  Matrix2 operator-(const Matrix2& matrix) const;
  //! Multiply a matrix to current matrix, return a new matrix to save result.
  //! @param matrix  The matrix to multiply.
  //! @return The result matrix of multiplication.
  Matrix2 operator*(const Matrix2& matrix) const;
  //! Multiply a scalar to current matrix, return a new matrix to save result.
  //! @param scalar  The scalar to multiply.
  //! @return The result matrix of multiplication.
  Matrix2 operator*(_float scalar) const;
  //! Divide a scalar to current matrix, return a new matrix to save result.
  //! @param scalar  The scalar to divide.
  //! @return The result quaternion of division.
  Matrix2 operator/(_float scalar) const;

  //! Compare two matrix.
  //! @param matrix  The matrix to compare with.
  //! @return True if they are identical, false otherwise.
  _ubool operator==(const Matrix2& matrix) const;
  //! Compare two matrix.
  //! @param matrix  The matrix to compare with.
  //! @return True if they are not identical, false otherwise.
  _ubool operator!=(const Matrix2& matrix) const;

  //! Calculates the determinant of the matrix.
  //! @param none
  //! @return The determinant of the matrix.
  _float Determinant() const;

  //! Calculates identity matrix, and save result current one.
  //! @param none
  //! @return The identity matrix.
  Matrix2& Identity();
  //! Calculates transpose matrix, and save result current one.
  //! @param none
  //! @return The transpose matrix.
  Matrix2& Transpose();
  //! Calculates inverse matrix, and save result current one.
  //! @param none
  //! @return The inverse matrix.
  Matrix2& Inverse();
  //! Calculates adjoint matrix, and save result current one.
  //! @param none
  //! @return The adjoint matrix.
  Matrix2& Adjoint();

  //! Create a scaling matrix.
  //! @param x   The x-component of scaling.
  //! @param y   The y-component of scaling.
  //! @return The scaling matrix.
  Matrix2& Scaling(_float x, _float y);
  //! Create a scaling matrix.
  //! @param vector  The scaling vector.
  //! @return The scaling matrix.
  Matrix2& Scaling(const Vector2& vector);
  //! Create a scaling matrix by scale an arbitrary direction.
  //! @param vector  The normal vector defines the direction of
  //! scale.
  //! @param factor  The scale factor.
  //! @return The scaling matrix.
  Matrix2& Scaling(const Vector2& vector, _float factor);

  //! Create a rotation matrix by rotate around origin.
  //! @param radian  The angle of rotation radian.
  //! @return The rotation matrix.
  Matrix2& Rotation(_float radian);

  //! Create a projection matrix by project onto x-axis.
  //! @param none
  //! @return The projection matrix.
  Matrix2& ProjectX();
  //! Create a projection matrix by project onto y-axis.
  //! @param none
  //! @return The projection matrix.
  Matrix2& ProjectY();
  //! Create a projection matrix by project onto an arbitrary line.
  //! @param vector  The normal vector defines the project
  //! line.
  //! @return The projection matrix.
  Matrix2& Project(const Vector2& vector);

  //! Create a reflection matrix by flip around x-axis.
  //! @param none
  //! @return The reflection matrix.
  Matrix2& RefectionX();
  //! Create a reflection matrix by flip around y-axis.
  //! @param none
  //! @return The reflection matrix.
  Matrix2& RefectionY();
  //! Create a reflection matrix by flip around an arbitrary line.
  //! @param vector  The normal vector defines the reflect
  //! line.
  //! @return The reflection matrix.
  Matrix2& Refection(const Vector2& vector);
};

//----------------------------------------------------------------------------
// Matrix2 Implementation
//----------------------------------------------------------------------------

inline Matrix2::Matrix2() {}

inline Matrix2::Matrix2(_float m00, _float m01, _float m10, _float m11) {
  m[0][0] = m00;
  m[0][1] = m01;
  m[1][0] = m10;
  m[1][1] = m11;
}

inline Matrix2::Matrix2(const Vector2& scale, _float radian) {
  _float sincos_value[2];
  Math::SinCos(radian, sincos_value);

  m[0][0] = scale.x * sincos_value[1];
  m[0][1] = scale.x * sincos_value[0];
  m[1][0] = scale.y * -sincos_value[0];
  m[1][1] = scale.y * sincos_value[1];
}

inline Matrix2 Matrix2::operator+() const {
  return Matrix2(m[0][0], m[0][1], m[1][0], m[1][1]);
}

inline Matrix2 Matrix2::operator-() const {
  return Matrix2(-m[0][0], -m[0][1], -m[1][0], -m[1][1]);
}

inline _ubool Matrix2::operator==(const Matrix2& matrix) const {
  if (m[0][0] != matrix.m[0][0]) return _false;
  if (m[0][1] != matrix.m[0][1]) return _false;

  if (m[1][0] != matrix.m[1][0]) return _false;
  if (m[1][1] != matrix.m[1][1]) return _false;

  return _true;
}

inline _ubool Matrix2::operator!=(const Matrix2& matrix) const {
  if (m[0][0] != matrix.m[0][0]) return _true;
  if (m[0][1] != matrix.m[0][1]) return _true;

  if (m[1][0] != matrix.m[1][0]) return _true;
  if (m[1][1] != matrix.m[1][1]) return _true;

  return _false;
}

inline Vector2 Matrix2::GetRow(_dword row) const {
  EGE_ASSERT(row < 2)

  return Vector2(m[row][0], m[row][1]);
}

inline Vector2 Matrix2::GetColumn(_dword column) const {
  EGE_ASSERT(column < 2)

  return Vector2(m[0][column], m[1][column]);
}

}  // namespace EGE