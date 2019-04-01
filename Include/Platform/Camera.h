#pragma once

namespace EGE {

/// <summary>
/// The camera.
/// </summary>
class Camera {
public:
	static const Camera cNull;

private:
	Vector3 mPosition;
	Vector3 mLook;
	Vector3 mUp;
	Vector3 mRight;
	_float mFOVDegree;

public:
	Camera();
	Camera(const Vector3& position, const Vector3& look, const Vector3& up, _float fovdegree = 58.0f);

public:
	_void LookAt(const Vector3& look);

	_void Strafe(_float units);
	_void Fly(_float units);

	_void Radius(_float units);
	_void Phi(_float radian);
	_void Theta(_float radian);

	_void PhiReverse(_float radian);
	_void ThetaReverse(_float radian);

	Camera& operator*=(const Matrix4& transform);
	Camera operator*(const Matrix4& transform) const;
};

} // namespace EGE