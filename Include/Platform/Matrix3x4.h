//! @file     Matrix3x4.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Matrix3x4
//----------------------------------------------------------------------------

//! This class represents a 3x4 Matrix.
class Matrix3x4 {
 public:
  //! The component of the matrix, column major.
  _float m[4][3];

 public:
  //! The zero matrix.
  static const Matrix3x4 cZero;
  //! The identity matrix.
  static const Matrix3x4 cIdentity;

 public:
  //! Constructor, create a matrix without sets components.
  //! @param none
  inline Matrix3x4();
  //! Constructor, create a matrix and sets components.
  //! @param m00~m23  The component of the matrix.
  inline Matrix3x4(_float m00, _float m01, _float m02, _float m10, _float m11,
                   _float m12, _float m20, _float m21, _float m22, _float m30,
                   _float m31, _float m32);
  //! Constructor, create a matrix and sets components.
  //! @param translation The vector of translation.
  //! @param rotation The matrix of rotation.
  inline Matrix3x4(const Vector3& translation, const Matrix3& rotation);

  //! Get a row from matrix by row number.
  //! @param row   Rom number of the matrix.
  //! @return The row of the matrix.
  inline const _float* operator[](_dword row) const;

  //! Get positive matrix.
  //! @param none
  //! @return The positive matrix.
  inline Matrix3x4 operator+() const;
  //! Get negative matrix.
  //! @param none
  //! @return The negative matrix.
  inline Matrix3x4 operator-() const;

  //! Get 3 x 4 matrix from a 4 x 4 matrix.
  //! @param matrix
  //! @return The 3 x 4 matrix.
  Matrix3x4& operator=(const Matrix4& matrix);

  //! Add a matrix to current matrix, and save result in current one.
  //! @param matrix  The matrix to add.
  //! @return The result matrix of addition.
  Matrix3x4& operator+=(const Matrix3x4& matrix);
  //! Subtract a matrix to current matrix, and save result in current one.
  //! @param matrix  The matrix to multiply.
  //! @return The result matrix of subtraction.
  Matrix3x4& operator-=(const Matrix3x4& matrix);
  //! Multiply a scalar to current matrix, and save result in current one.
  //! @param scalar  The scalar to multiply.
  //! @return The result matrix of multiplication.
  Matrix3x4& operator*=(_float scalar);
  //! Divide a scalar to current matrix, and save result in current one.
  //! @param scalar  The scalar to divide.
  //! @return The result quaternion of division.
  Matrix3x4& operator/=(_float scalar);

  //! Add a matrix to current matrix, return a new matrix to save result.
  //! @param matrix  The matrix to add.
  //! @return The result matrix of addition.
  Matrix3x4 operator+(const Matrix3x4& matrix) const;
  //! Subtract a matrix to current matrix, return a new matrix to save result.
  //! @param matrix  The matrix to subtract.
  //! @return The result matrix of subtraction.
  Matrix3x4 operator-(const Matrix3x4& matrix) const;
  //! Multiply a scalar to current matrix, return a new matrix to save result.
  //! @param scalar  The scalar to multiply.
  //! @return The result matrix of multiplication.
  Matrix3x4 operator*(_float scalar) const;
  //! Divide a scalar to current matrix, return a new matrix to save result.
  //! @param scalar  The scalar to divide.
  //! @return The result quaternion of division.
  Matrix3x4 operator/(_float scalar) const;

  //! Get the rotation matrix, without translation.
  //! @param none
  //! @return The rotation matrix.
  inline Matrix3 GetRotationMatrix() const;

  //! Get the translation vector, without rotation.
  //! @param none
  //! @return The translation vector.
  inline Vector3 GetTranslationVector() const;

  //! Create a translation matrix.
  //! @param x   The x-component of translation.
  //! @param y   The y-component of translation.
  //! @param z   The z-component of translation.
  //! @return The translation matrix.
  Matrix3x4& Translation(_float x, _float y, _float z);
  //! Create a translation matrix.
  //! @param vector  The translation vector.
  //! @return The translation matrix.
  Matrix3x4& Translation(const Vector3& vector);

  //! Create a rotation matrix by rotate around x-axis.
  //! @param radian  The angle of rotation in radian.
  //! @return The rotation matrix.
  Matrix3x4& RotationX(_float radian);
  //! Create a rotation matrix by rotate around y-axis.
  //! @param radian  The angle of rotation in radian.
  //! @return The rotation matrix.
  Matrix3x4& RotationY(_float radian);
  //! Create a rotation matrix by rotate around z-axis.
  //! @param radian  The angle of rotation in radian.
  //! @return The rotation matrix.
  Matrix3x4& RotationZ(_float radian);

  //! Create a matrix from a matrix and a vector.
  //! @param translation The vector of translation.
  //! @param rotation The matrix of rotation.
  //! @return The reference of current matrix.
  Matrix3x4& FromTranslationRotation(const Vector3& translation,
                                     const Matrix3& rotation);
  //! Get the translation vector and rotation matrix from current matrix.
  //! @param translation The vector of translation, get from this
  //! function.
  //! @param rotation The matrix of rotation, get from this
  //! function.
  _void ToTranslationRotation(Vector3& translation, Matrix3& rotation) const;
};

//----------------------------------------------------------------------------
// Matrix3x4 Implementation
//----------------------------------------------------------------------------

Matrix3x4::Matrix3x4() {}

Matrix3x4::Matrix3x4(_float m00, _float m01, _float m02, _float m10, _float m11,
                     _float m12, _float m20, _float m21, _float m22, _float m30,
                     _float m31, _float m32) {
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
}

Matrix3x4::Matrix3x4(const Vector3& translation, const Matrix3& rotation) {
  m[0][0] = rotation.m[0][0];
  m[0][1] = rotation.m[1][0];
  m[0][2] = rotation.m[2][0];
  m[1][0] = rotation.m[0][1];
  m[1][1] = rotation.m[1][1];
  m[1][2] = rotation.m[2][1];
  m[2][0] = rotation.m[0][2];
  m[2][1] = rotation.m[1][2];
  m[2][2] = rotation.m[2][2];
  m[3][0] = translation.x;
  m[3][1] = translation.y;
  m[3][2] = translation.z;
}

const _float* Matrix3x4::operator[](_dword row) const {
  EGE_ASSERT(row < 4);

  return m[row];
}

Matrix3x4 Matrix3x4::operator+() const {
  return Matrix3x4(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2],
                   m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);
}

Matrix3x4 Matrix3x4::operator-() const {
  return Matrix3x4(-m[0][0], -m[0][1], -m[0][2], -m[1][0], -m[1][1], -m[1][2],
                   -m[2][0], -m[2][1], -m[2][2], -m[3][0], -m[3][1], -m[3][2]);
}

Matrix3 Matrix3x4::GetRotationMatrix() const {
  return Matrix3(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0],
                 m[2][1], m[2][2]);
}

Vector3 Matrix3x4::GetTranslationVector() const {
  return Vector3(m[3][0], m[3][1], m[3][2]);
}

}  // namespace EGE