#include "EGEPlatform.h"

const EulerAngles EulerAngles::cIdentity(0.0f, 0.0f, 0.0f);

EulerAngles& EulerAngles::Identity() {
	mHeading = 0.0f;
	mPitch = 0.0f;
	mBank = 0.0f;

	return *this;
}

EulerAngles& EulerAngles::Canonize() {
	// First, wrap pitch range ¨Cpi ... pi.
	mPitch = Math::WrapPi(mPitch);

	// Check for "the back side" of the matrix pitch outside the canonical range of ¨Cpi/2 ... pi/2.
	if (mPitch < Math::cPi * -0.5f) {
		mPitch = -Math::cPi - mPitch;
		mHeading = mHeading + Math::cPi;
		mBank = mBank + Math::cPi;
	} else if (mPitch > Math::cPi * 0.5f) {
		mPitch = Math::cPi - mPitch;
		mHeading = mHeading + Math::cPi;
		mBank = mBank + Math::cPi;
	}

	// Check for the gimbel lock case (witha slight tolerance).
	if (Math::Abs(mPitch) > Math::cPi * 0.5f - Math::cFloatEpsilon) {
		// gimbel lock. Assign all rotation abthe vertical axis to heading.
		mHeading = mHeading + mBank;
		mBank = 0.0f;
	} else {
		// Not gimbel lock. Wrap the bank angle canonical range.
		mBank = Math::WrapPi(mBank);
	}

	// Wrap heading canonical range.
	mHeading = Math::WrapPi(mHeading);

	return *this;
}

_void EulerAngles::GetAxisAndAngle(Vector3& axis, _float& angle) const {
	_float x = Math::Abs(mPitch / Math::c2Pi);
	_float y = Math::Abs(mHeading / Math::c2Pi);
	_float z = Math::Abs(mBank / Math::c2Pi);

	if (z < Math::cFloatEpsilon && y < Math::cFloatEpsilon) {
		axis = Vector3::cYAxis;
		angle = mPitch;
	} else if (x < Math::cFloatEpsilon && z < Math::cFloatEpsilon) {
		axis = Vector3::cYAxis;
		angle = mHeading;
	} else if (x < Math::cFloatEpsilon && y < Math::cFloatEpsilon) {
		axis = Vector3::cZAxis;
		angle = mBank;
	} else {
		Quaternion q;
		ToQuaternion(q);
		q.GetAxisAndAngle(axis, angle);
	}
}

_void EulerAngles::ToQuaternion(Quaternion& quaternion) const {
	_float cp = Math::Cos(mPitch / 2.0f);
	_float ch = Math::Cos(mHeading / 2.0f);
	_float cb = Math::Cos(mBank / 2.0f);
	_float sp = Math::Sin(mPitch / 2.0f);
	_float sh = Math::Sin(mHeading / 2.0f);
	_float sb = Math::Sin(mBank / 2.0f);

	quaternion.w = cp * ch * cb + sp * sh * sb;
	quaternion.x = sp * ch * cb - cp * sh * sb;
	quaternion.y = cp * sh * cb + sp * ch * sb;
	quaternion.z = cp * ch * sb - sp * sh * cb;
}

_void EulerAngles::ToMatrix(Matrix3& matrix) const {
	_float cp = Math::Cos(mPitch);
	_float ch = Math::Cos(mHeading);
	_float cb = Math::Cos(mBank);
	_float sp = Math::Sin(mPitch);
	_float sh = Math::Sin(mHeading);
	_float sb = Math::Sin(mBank);

	matrix.m[0][0] = ch * cb;
	matrix.m[0][1] = ch * sb;
	matrix.m[0][2] = -sh;
	matrix.m[1][0] = sp * sh * cb - cp * sb;
	matrix.m[1][1] = sp * sh * sb + cp * cb;
	matrix.m[1][2] = sp * ch;
	matrix.m[2][0] = cp * sh * cb + sp * sb;
	matrix.m[2][1] = cp * sh * sb - sp * cb;
	matrix.m[2][2] = cp * ch;
}
