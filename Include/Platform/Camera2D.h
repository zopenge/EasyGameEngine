
#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Camera2D
//----------------------------------------------------------------------------

class Camera2D {
public:
	static const Camera2D cNull;

private:
	Vector2 mOffset;
	Vector2 mScale;
	_float mRotation;
	Matrix3 mTransform;

public:
	Camera2D();
	Camera2D(const Vector2& position, const Vector2& scale, _float rotation);
	~Camera2D();

public:
	_void SetOffset(const Vector2& offset);
	_void SetScale(const Vector2& scale);
	_void SetRotation(_float rotation);

	const Vector2& GetOffset() const;
	const Vector2& GetScale() const;
	_float GetRotation() const;
	const Matrix3& GetTransform() const;

	_void Scale(const Vector2& scale, const Vector2& anchorpos);
	_void Rotate(_float rotate, const Vector2& anchorpos);
};

} // namespace EGE