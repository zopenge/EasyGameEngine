#include "EGEPlatform.h"

const Camera2D Camera2D::cNull(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), 0.0f);

Camera2D::Camera2D()
    : mOffset(Vector2::cOrigin), mScale(Vector2::cIdentity), mRotation(0.0f), mTransform(Matrix3::cIdentity) {
}

Camera2D::Camera2D(const Vector2& position, const Vector2& scale, _float rotation)
    : mOffset(position), mScale(scale), mRotation(rotation), mTransform(-position, scale, rotation) {
}

Camera2D::~Camera2D() {
}

_void Camera2D::SetOffset(const Vector2& offset) {
	mOffset = offset;
	mTransform = Matrix3(-mOffset, mScale, mRotation);
}

_void Camera2D::SetScale(const Vector2& scale) {
	mScale = scale;
	mTransform = Matrix3(-mOffset, mScale, mRotation);
}

_void Camera2D::SetRotation(_float rotation) {
	mRotation = rotation;
	mTransform = Matrix3(-mOffset, mScale, mRotation);
}

const Vector2& Camera2D::GetOffset() const {
	return mOffset;
}

const Vector2& Camera2D::GetScale() const {
	return mScale;
}

_float Camera2D::GetRotation() const {
	return mRotation;
}

const Matrix3& Camera2D::GetTransform() const {
	return mTransform;
}

_void Camera2D::Scale(const Vector2& scale, const Vector2& anchorpos) {
	mScale = scale;
	mTransform = Matrix3(-anchorpos, Vector2::cIdentity, 0.0f) *
	             Matrix3(-mOffset, mScale, mRotation) *
	             Matrix3(anchorpos, Vector2::cIdentity, 0.0f);
	mOffset = mTransform.GetTranslationVector();
}

_void Camera2D::Rotate(_float rotate, const Vector2& anchorpos) {
	mRotation = rotate;
	mTransform = Matrix3(-anchorpos, Vector2::cIdentity, 0.0f) *
	             Matrix3(-mOffset, mScale, mRotation) *
	             Matrix3(anchorpos, Vector2::cIdentity, 0.0f);
	mOffset = mTransform.GetTranslationVector();
}
