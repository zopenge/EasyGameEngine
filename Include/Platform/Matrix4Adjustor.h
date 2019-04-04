#pragma once

namespace EGE {

class Matrix4Adjustor {
private:
	Vector3 mTranslation;
	_dword mTranslationDuration;
	_qword mTranslationTickCount;

	Vector3 mScaling;
	_dword mScalingDuration;
	_qword mScalingTickCount;

	Vector3 mRotation;
	_dword mRotationDuration;
	_qword mRotationTickCount;

	_float mHeight;
	_dword mHeightDuration;
	_qword mHeightTickCount;

public:
	Matrix4Adjustor();

	inline const Vector3& GetTranslation() const;
	inline const Vector3& GetScaling() const;
	inline const Vector3& GetRotation() const;
	inline _float GetHeight() const;

	inline _float GetTranslationProgress() const;
	inline _float GetScalingProgress() const;
	inline _float GetRotationProgress() const;
	inline _float GetHeightProgress() const;

	_void Translation(_float x, _float y, _float z, _dword duration);
	_void Translation(const Vector3& vector, _dword duration);

	_void Scaling(_float x, _float y, _float z, _dword duration);
	_void Scaling(const Vector3& vector, _dword duration);

	_void Rotation(_float x, _float y, _float z, _dword duration);
	_void Rotation(const Vector3& vector, _dword duration);

	_void Height(_float height, _dword duration);

	_void Tick(_dword elapse);

	Matrix4 AdjustMatrix(const Matrix4& matrix) const;
};

//----------------------------------------------------------------------------
// Matrix4Adjustor Implementation
//----------------------------------------------------------------------------

const Vector3& Matrix4Adjustor::GetTranslation() const {
	return mTranslation;
}

const Vector3& Matrix4Adjustor::GetScaling() const {
	return mScaling;
}

const Vector3& Matrix4Adjustor::GetRotation() const {
	return mRotation;
}

_float Matrix4Adjustor::GetHeight() const {
	return mHeight;
}

_float Matrix4Adjustor::GetTranslationProgress() const {
	return mTranslationDuration == 0 ? 0.0f
	                                 : 1.0f - (_float)mTranslationTickCount /
	                                              (_float)mTranslationDuration;
}

_float Matrix4Adjustor::GetScalingProgress() const {
	return mScalingDuration == 0
	           ? 0.0f
	           : 1.0f - (_float)mScalingTickCount / (_float)mScalingDuration;
}

_float Matrix4Adjustor::GetRotationProgress() const {
	return mRotationDuration == 0
	           ? 0.0f
	           : 1.0f - (_float)mRotationTickCount / (_float)mRotationDuration;
}

_float Matrix4Adjustor::GetHeightProgress() const {
	return mHeightDuration == 0
	           ? 0.0f
	           : 1.0f - (_float)mHeightTickCount / (_float)mHeightDuration;
}

} // namespace EGE