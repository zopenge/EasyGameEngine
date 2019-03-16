//! @file     EulerAngles.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// EulerAngles
//----------------------------------------------------------------------------

class EulerAngles {
 public:
  //! Rotation angle about x-axis.
  _float mPitch;
  //! Rotation angle about y-axis.
  _float mHeading;
  //! Rotation angle about z-axis.
  _float mBank;

 public:
  //! The identity euler angles.
  static const EulerAngles cIdentity;

 public:
  //! Constructor, create an euler angles without sets components.
  //! @param none
  inline EulerAngles();
  //! Constructor, create an euler angles and sets components.
  //! @param pitch  Rotation angle about x-axis.
  //! @param heading  Rotation angle about y-axis.
  //! @param bank  Rotation angle about z-axis.
  inline EulerAngles(_float pitch, _float heading, _float bank);

  //! Calculates identity euler angles, and save result in current one.
  //! @param none
  //! @return The identity euler angles.
  EulerAngles& Identity();
  //! Calculates canonica euler angles, and save result in current one.
  //! @param none
  //! @return The canonical euler angles.
  EulerAngles& Canonize();

  //! Calculates the axis and angle
  //! @param axis  the axis.
  //! @param angle  the angle.
  //! @return none.
  _void GetAxisAndAngle(Vector3& axis, _float& angle) const;

  //! Compare two EulerAngles.
  //! @param angle  The EulerAngles to compare with.
  //! @return True if they are identical, false otherwise.
  _ubool operator==(const EulerAngles& angle) const;
  //! Compare two EulerAngles.
  //! @param angle  The EulerAngles to compare with.
  //! @return True if they are not identical, false otherwise.
  _ubool operator!=(const EulerAngles& angle) const;

  inline EulerAngles operator+() const;
  inline EulerAngles operator-() const;
  inline EulerAngles& operator+=(const EulerAngles& vector);
  inline EulerAngles& operator-=(const EulerAngles& vector);
  inline EulerAngles& operator*=(_float scalar);
  inline EulerAngles& operator/=(_float scalar);
  inline EulerAngles operator+(const EulerAngles& vector) const;
  inline EulerAngles operator-(const EulerAngles& vector) const;
  inline EulerAngles operator*(_float scalar) const;
  inline EulerAngles operator/(_float scalar) const;
};

//----------------------------------------------------------------------------
// EulerAngles Implementation
//----------------------------------------------------------------------------

EulerAngles::EulerAngles() {}

EulerAngles::EulerAngles(_float pitch, _float heading, _float bank)
    : mPitch(pitch), mHeading(heading), mBank(bank) {}

inline _ubool EulerAngles::operator==(const EulerAngles& angle) const {
  return Math::Equal(mPitch, angle.mPitch) &&
         Math::Equal(mHeading, angle.mHeading) &&
         Math::Equal(mBank, angle.mBank);
}

inline _ubool EulerAngles::operator!=(const EulerAngles& angle) const {
  return (!Math::Equal(mPitch, angle.mPitch)) ||
         (!Math::Equal(mHeading, angle.mHeading)) ||
         (!Math::Equal(mBank, angle.mBank));
}

EulerAngles EulerAngles::operator+() const {
  return EulerAngles(mPitch, mHeading, mBank);
}

EulerAngles EulerAngles::operator-() const {
  return EulerAngles(-mPitch, -mHeading, -mBank);
}

EulerAngles& EulerAngles::operator+=(const EulerAngles& vector) {
  mPitch += vector.mPitch;
  mHeading += vector.mHeading;
  mBank += vector.mBank;

  return *this;
}

EulerAngles& EulerAngles::operator-=(const EulerAngles& vector) {
  mPitch -= vector.mPitch;
  mHeading -= vector.mHeading;
  mBank -= vector.mBank;

  return *this;
}

EulerAngles& EulerAngles::operator*=(_float scalar) {
  mPitch *= scalar;
  mHeading *= scalar;
  mBank *= scalar;

  return *this;
}

EulerAngles& EulerAngles::operator/=(_float scalar) {
  mPitch /= scalar;
  mHeading /= scalar;
  mBank /= scalar;

  return *this;
}

EulerAngles EulerAngles::operator+(const EulerAngles& vector) const {
  return EulerAngles(mPitch + vector.mPitch, mHeading + vector.mHeading,
                     mBank + vector.mBank);
}

EulerAngles EulerAngles::operator-(const EulerAngles& vector) const {
  return EulerAngles(mPitch - vector.mPitch, mHeading - vector.mHeading,
                     mBank - vector.mBank);
}

EulerAngles EulerAngles::operator*(_float scalar) const {
  return EulerAngles(mPitch * scalar, mHeading * scalar, mBank * scalar);
}

EulerAngles EulerAngles::operator/(_float scalar) const {
  return EulerAngles(mPitch / scalar, mHeading / scalar, mBank / scalar);
}

}  // namespace EGE