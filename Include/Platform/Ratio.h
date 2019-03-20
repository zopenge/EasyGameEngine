#pragma once

namespace EGE {

/// <summary>
/// Keep ratio with width and height
/// </summary>
class Ratio {
public:
	/// <summary>
	/// Ĭ��ֵ
	/// </summary>
	static Ratio cNull;

public:
	/// <summary>
	/// ����ϵ��
	/// </summary>
	_float scale;
	/// <summary>
	/// ��������ϵ��
	/// </summary>
	Vector2 baseSize;
	/// <summary>
	/// �����Ͻ�Ϊ����ƫ����
	/// </summary>
	Vector2 offset;

public:
	/// <summary>
	/// Ĭ�Ϲ���
	/// </summary>
	Ratio();
	/// <summary>
	///	Ĭ�Ͽ�������
	/// </summary>
	/// <param name="ratio">������Դ</param>
	Ratio(const Ratio& ratio);
	/// <summary>
	/// �Կ����Ϊ������Դ���г�ʼ��
	/// </summary>
	/// <param name="size">���</param>
	Ratio(const Vector2& size);
	/// <summary>
	/// �Կ����Ϊ������Դ���г�ʼ��
	/// </summary>
	/// <param name="width">���</param>
	/// <param name="height">�߶�</param>
	Ratio(_float width, _float height);

public:
	/// <summary>
	/// ��ȡ���Ź����
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