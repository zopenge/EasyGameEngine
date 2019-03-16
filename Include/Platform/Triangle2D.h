//! @file     Triangle2D.h
//! @author   foreven
//! @version  1.1
//! @date     2012.11.27
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Triangle2D
//----------------------------------------------------------------------------

class Triangle2D {
 public:
  Vector2 mVector1;
  Vector2 mVector2;
  Vector2 mVector3;

 public:
  inline Triangle2D();
  inline Triangle2D(const Vector2& vector1, const Vector2& vector2,
                    const Vector2& vector3);

 public:
  inline Triangle2D& operator*=(const Matrix3& matrix);
  inline Triangle2D operator*(const Matrix3& matrix) const;

  inline Vector2 MiddleVector();

  _ubool PointInTriangle(const Vector2& point) const;
  _float GetArea();
  _ubool IsValid();
};

//----------------------------------------------------------------------------
// Triangle2D Implementation
//----------------------------------------------------------------------------

Triangle2D::Triangle2D() {}

Triangle2D::Triangle2D(const Vector2& vector1, const Vector2& vector2,
                       const Vector2& vector3)
    : mVector1(vector1), mVector2(vector2), mVector3(vector3) {}

Triangle2D& Triangle2D::operator*=(const Matrix3& matrix) {
  mVector1 *= matrix;
  mVector2 *= matrix;
  mVector3 *= matrix;

  return *this;
}

Triangle2D Triangle2D::operator*(const Matrix3& matrix) const {
  return Triangle2D(mVector1 * matrix, mVector2 * matrix, mVector3 * matrix);
}

Vector2 Triangle2D::MiddleVector() {
  return Vector2((mVector1.x + mVector2.x + mVector3.x) / 3.0f,
                 (mVector1.y + mVector2.y + mVector3.y) / 3.0f);
}

}  // namespace EGE