#pragma once

namespace EGE {

/// <summary>
/// Keep ratio with width and height
/// </summary>
class Ratio {
public:
	/// <summary>
	/// The null ratio.
	/// </summary>
	static Ratio cNull;

public:
	/// <summary>
	/// The scale factor.
	/// </summary>
	_float mScale;
	/// <summary>
	/// The base scale factor.
	/// </summary>
	Vector2 mBaseSize;
	/// <summary>
	/// The offset from left-top.
	/// </summary>
	Vector2 mOffset;

public:
	/// <summary>
	/// Constructor
	/// </summary>
	Ratio();
	/// <summary>
	///	Copy constructor
	/// </summary>
	/// <param name="ratio">数据来源</param>
	Ratio(const Ratio& ratio);
	/// <summary>
	/// Construct from width and height
	/// </summary>
	/// <param name="size">width and height</param>
	Ratio(const Vector2& size);
	/// <summary>
	/// Construct from width and height
	/// </summary>
	/// <param name="width">width</param>
	/// <param name="height">height</param>
	Ratio(_float width, _float height);

public:
	/// <summary>
	/// Get the scaled position.
	/// </summary>
	template <typename Type>
	Vector2 getScaledPos(const Type& pos) const;
	/// <summary>
	/// Get the inversed original position.
	/// </summary>
	template <typename Type>
	Vector2 getInversedScaledPos(const Type& pos) const;

	_ubool operator==(const Ratio& ratio) const;
	_ubool operator!=(const Ratio& ratio) const;

public:
	/// <summary>
	///
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <returns></returns>
	_void Init(_float width, _float height);
	//! Update size.
	Vector2 UpdateSize(_float width, _float height);
	PointU UpdateSize(_dword width, _dword height);

	//! Get the base size.
	Vector2 GetBaseSize() const;
	//! Get the offset.
	Vector2 GetOffset() const;

	//! Fix size.
	PointU FixSizeU(const PointU& size) const;
	Vector2 FixSizeF(const PointU& size) const;

public:
	//! Fix size by ratio info.
	static PointU FixSizeU(const Ratio& ratio, const PointU& size);
	static Vector2 FixSizeF(const Ratio& ratio, const PointU& size);

	//! Keep the ratio and use the new size to create ratio.
	static Ratio Create(const Ratio& ratio, const PointU& size);
};

//----------------------------------------------------------------------------
// Ratio Implementation
//----------------------------------------------------------------------------

template <typename Type>
Vector2 Ratio::getScaledPos(const Type& pos) const {
	if (mScale > 0)
		return Vector2(((_float)pos.x - mOffset.x) / mScale, ((_float)pos.y - mOffset.y) / mScale);
	else
		return Vector2(0.0f, 0.0f);
}

template <typename Type>
Vector2 Ratio::getInversedScaledPos(const Type& pos) const {
	if (mScale > 0)
		return Vector2((_float)pos.x * mScale + mOffset.x, (_float)pos.y * mScale + mOffset.y);
	else
		return Vector2(0.0f, 0.0f);
}

} // namespace EGE