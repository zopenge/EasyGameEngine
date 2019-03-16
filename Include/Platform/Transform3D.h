
#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Transform3D
//----------------------------------------------------------------------------

class Transform3D {
 public:
  //! The rotation of transform3d
  Quaternion mRotation;
  //! The translate of transform3d
  Vector3 mTranslate;

 public:
  //! The identity Transform3D.
  static const Transform3D cZero;

 public:
  //! Constructor, create a Transform3D without sets rotation and translate
  //! components.
  //! @param none
  inline Transform3D();
  //! Constructor, create a quaternion and sets rotation and translate
  //! components.
  //! @param rotation	rotation component of the Transform3D.
  //! @param scale		scale component of the Transform3D.
  //! @param translate	translate component of the Transform3D.
  inline Transform3D(const Quaternion& rotation, const Vector3& translate);

  inline Transform3D(const Quaternion& rotation);
  inline Transform3D(const Vector3& translate);

 public:
  //! Multiply a Transform3D to current Transform3D, and save result in current
  //! one.
  //! @param Transform3D		The Transform3D to multiply.
  //! @return The result Transform3D of multiplication.
  Transform3D& operator*=(const Transform3D& transform);

  //! Multiply a Transform3D to current Transform3D, return a new Transform3D to
  //! save result.
  //! @param Transform3D		The Transform3D to multiply.
  //! @return The result Transform3D of multiplication.
  Transform3D operator*(const Transform3D& transform) const;

  //! Compare two Transform3D.
  //! @param transform	The Transform3D to compare with.
  //! @return True if they are identical, false otherwise.
  inline _ubool operator==(const Transform3D& transform) const;
  //! Compare two Transform3D.
  //! @param transform		The Transform3D to compare with.
  //! @return True if they are not identical, false otherwise.
  inline _ubool operator!=(const Transform3D& transform) const;

  //! Calculates inverse Transform3D, and save result in current one.
  //! @param none
  //! @return The inverse Transform3D.
  Transform3D& Inverse();

  //! Calculates transform matrix
  //! @param none
  //! @return The transform matrix;
  Matrix4 ToMatrix() const;

  //! Calculates linear interpolation of two Transform3D.
  //! @param transform1	Source transform 1.
  //! @param transform2	Source transform 2.
  //! @param factor		The interpolation factor, will clamp to between
  //! 0 to 1.
  //! @return The result transform of interpolation, transform1 + (
  //! transform2 - transform1 ) * factor.
  static Transform3D Lerp(const Transform3D& transform1,
                          const Transform3D& transform2, _float factor);
};

//----------------------------------------------------------------------------
// Transform3D Implementation
//----------------------------------------------------------------------------

Transform3D::Transform3D()
    : mRotation(Quaternion::cIdentity), mTranslate(Vector3::cOrigin) {}

Transform3D::Transform3D(const Quaternion& rotation, const Vector3& translate)
    : mRotation(rotation), mTranslate(translate) {}

Transform3D::Transform3D(const Quaternion& rotation)
    : mRotation(rotation), mTranslate(Vector3::cOrigin) {}

Transform3D::Transform3D(const Vector3& translate)
    : mRotation(Quaternion::cIdentity), mTranslate(translate) {}

_ubool Transform3D::operator==(const Transform3D& transform) const {
  if (mTranslate != transform.mTranslate) return _false;

  if (!mRotation.Equal(transform.mRotation)) return _false;

  return _true;
}

_ubool Transform3D::operator!=(const Transform3D& transform) const {
  if (mTranslate != transform.mTranslate) return _true;

  if (!mRotation.Equal(transform.mRotation)) return _true;

  return _false;
}

}  // namespace EGE