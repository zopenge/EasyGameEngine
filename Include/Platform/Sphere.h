//! @file     Sphere.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Sphere
//----------------------------------------------------------------------------

class Sphere {
 public:
  Vector3 mCenter;
  _float mRadius;

 public:
  inline Sphere();
  inline Sphere(const Vector3& center, _float radius);

  inline Sphere& operator*=(const Matrix4& matrix);
  inline Sphere operator*(const Matrix4& matrix) const;
};

//----------------------------------------------------------------------------
// Sphere Implementation
//----------------------------------------------------------------------------

Sphere::Sphere() {}

Sphere::Sphere(const Vector3& center, _float radius) {
  mCenter = center;
  mRadius = radius;
}

Sphere& Sphere::operator*=(const Matrix4& matrix) {
  mCenter *= matrix;

  return *this;
}

Sphere Sphere::operator*(const Matrix4& matrix) const {
  return Sphere(mCenter * matrix, mRadius);
}

}  // namespace EGE