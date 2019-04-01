#include "EGEPlatform.h"

const Camera Camera::cNull(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.0f);

Camera::Camera() {
	mPosition = Vector3(100.0f, 100.0f, 100.0f);
	mLook = Vector3::cOrigin;
	mUp = Vector3::cZAxis;
	mRight = Vector3::Cross(mLook - mPosition, mUp).Normalize();
	mFOVDegree = 58.0f;
}

Camera::Camera(const Vector3& position, const Vector3& look, const Vector3& up, _float fovdegree) {
	mPosition = position;
	mLook = look;
	mUp = up;
	mRight = Vector3::Cross(mLook - mPosition, mUp).Normalize();
	mFOVDegree = fovdegree; // 58.0 / 1.3 ~= PI / 4( old value )
}

_void Camera::LookAt(const Vector3& look) {
	Vector3 temp = mLook;

	mLook = look;
	mPosition = mLook + (mPosition - temp);
	mRight = Vector3::Cross(mLook - mPosition, mUp).Normalize();
}

_void Camera::Strafe(_float units) {
	mLook += mRight * units;
	mPosition += mRight * units;
}

_void Camera::Fly(_float units) {
	mLook += mUp * units;
	mPosition += mUp * units;
}

_void Camera::Radius(_float units) {
	Vector3 direction = mPosition - mLook;
	Vector3 position = mPosition + direction.Normalize() * units;

	// Avoid #ind value
	if (position.Equal(mLook))
		return;

	if (Vector3::Dot(mPosition - mLook, position - mLook) > 0.0f)
		mPosition = position;
}

_void Camera::Phi(_float radian) {
	mPosition *= Matrix4().Translation(-mLook) * Matrix4().Rotation(mUp, radian) * Matrix4().Translation(mLook);

	mRight = Vector3::Cross(mLook - mPosition, mUp).Normalize();
}

_void Camera::Theta(_float radian) {
	Vector3 vector1 = Vector3::Cross(mPosition - mLook, mRight);

	mPosition *= Matrix4().Translation(-mLook) * Matrix4().Rotation(mRight, radian) * Matrix4().Translation(mLook);

	Vector3 vector2 = Vector3::Cross(mPosition - mLook, mRight);

	if (Vector3::Dot(vector1, mUp) * Vector3::Dot(vector2, mUp) < 0.0f)
		mUp = -mUp;
}

_void Camera::PhiReverse(_float radian) {
	mLook *= Matrix4().Translation(-mPosition) * Matrix4().Rotation(mUp, radian) * Matrix4().Translation(mPosition);

	mRight = Vector3::Cross(mLook - mPosition, mUp).Normalize();
}

_void Camera::ThetaReverse(_float radian) {
	Vector3 vector1 = Vector3::Cross(mLook - mPosition, mRight);

	mLook *= Matrix4().Translation(-mPosition) * Matrix4().Rotation(mRight, radian) * Matrix4().Translation(mPosition);

	Vector3 vector2 = Vector3::Cross(mLook - mPosition, mRight);

	if (Vector3::Dot(vector1, mUp) * Vector3::Dot(vector2, mUp) < 0.0f)
		mUp = -mUp;
}

Camera& Camera::operator*=(const Matrix4& transform) {
	Vector3 translation;
	Matrix3 rotation;
	transform.ToTranslationRotation(translation, rotation);

	mPosition *= transform;
	mLook *= transform;
	mUp *= rotation;
	mRight = Vector3::Cross(mLook - mPosition, mUp).Normalize();

	return *this;
}

Camera Camera::operator*(const Matrix4& transform) const {
	Camera returncamera = *this;

	return returncamera *= transform;
}