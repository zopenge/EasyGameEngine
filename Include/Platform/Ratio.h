#pragma once

namespace EGE {

/// <summary>
/// Keep ratio with width and height
/// </summary>
class Ratio {
public:
	/// <summary>
	/// 默认值
	/// </summary>
	static Ratio cNull;

public:
	/// <summary>
	/// 缩放系数
	/// </summary>
	_float scale;
	/// <summary>
	/// 基础缩放系数
	/// </summary>
	Vector2 baseSize;
	/// <summary>
	/// 以左上角为起点的偏移量
	/// </summary>
	Vector2 offset;

public:
	/// <summary>
	/// 默认构造
	/// </summary>
	Ratio();
	/// <summary>
	///	默认拷贝构造
	/// </summary>
	/// <param name="ratio">数据来源</param>
	Ratio(const Ratio& ratio);
	/// <summary>
	/// 以宽高作为数据来源进行初始化
	/// </summary>
	/// <param name="size">宽高</param>
	Ratio(const Vector2& size);
	/// <summary>
	/// 以宽高作为数据来源进行初始化
	/// </summary>
	/// <param name="width">宽度</param>
	/// <param name="height">高度</param>
	Ratio(_float width, _float height);

public:
	/// <summary>
	/// 获取缩放过后的
	/// </summary>
	template <typename Type>
	Vector2 getScaledPos(const Type& pos) const;
	template <typename Type>
	Vector2 InverseConvertPos(const Type& pos) const;

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
Vector2 Ratio::ConvertPos(const Type& pos) const {
	if (mScale > 0)
		return Vector2(((_float)pos.x - mOffset.x) / mScale, ((_float)pos.y - mOffset.y) / mScale);
	else
		return Vector2(0.0f, 0.0f);
}

template <typename Type>
Vector2 Ratio::InverseConvertPos(const Type& pos) const {
	if (scale > 0)
		return Vector2((_float)pos.x * scale + offset.x, (_float)pos.y * scale + offset.y);
	else
		return Vector2(0.0f, 0.0f);
}

} // namespace EGE