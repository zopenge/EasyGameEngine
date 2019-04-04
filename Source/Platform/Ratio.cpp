#include "EGEPlatform.h"

Ratio Ratio::cNull;

Ratio::Ratio() {
	scale = 1.0f;
	baseSize = PointF::cZeroPoint;
	offset = PointF::cZeroPoint;
}

Ratio::Ratio(const Ratio& ratio) {
	scale = ratio.scale;
	baseSize = ratio.baseSize;
	offset = ratio.offset;
}

Ratio::Ratio(const Vector2& size) {
	Init(size.x, size.y);
}

Ratio::Ratio(_float width, _float height) {
	Init(width, height);
}

_ubool Ratio::operator==(const Ratio& ratio) const {
	if (Math::Equal(scale, ratio.scale) == _false)
		return _false;

	if (baseSize != ratio.baseSize)
		return _false;

	if (offset != ratio.offset)
		return _false;

	return _true;
}

_ubool Ratio::operator!=(const Ratio& ratio) const {
	if (Math::Equal(scale, ratio.scale) == _false)
		return _true;

	if (baseSize != ratio.baseSize)
		return _true;

	if (offset != ratio.offset)
		return _true;

	return _false;
}

_void Ratio::Init(_float width, _float height) {
	height = Math::Max<_float>(1.0f, height);

	scale = 1.0f;
	baseSize = PointF(width, height);
	offset = PointF::cZeroPoint;

	UpdateSize(width, height);
}

Vector2 Ratio::UpdateSize(_float width, _float height) {
	_float ratiow = width / baseSize.x;
	_float ratioh = height / baseSize.y;

	if (height > baseSize.y * ratiow) {
		scale = ratiow;
		offset.x = 0;
		offset.y = (height - baseSize.y * ratiow) / 2.0f;

		return PointF(width, baseSize.y * ratiow);
	} else {
		scale = ratioh;
		offset.x = (width - baseSize.x * ratioh) / 2.0f;
		offset.y = 0;

		return PointF(baseSize.x * ratioh, height);
	}
}

PointU Ratio::UpdateSize(_dword width, _dword height) {
	Vector2 size = UpdateSize((_float)width, (_float)height);
	return PointU((_dword)size.x, (_dword)size.y);
}

Vector2 Ratio::GetBaseSize() const {
	return Vector2(baseSize.x, baseSize.y);
}

Vector2 Ratio::GetOffset() const {
	return Vector2(offset.x, offset.y);
}

PointU Ratio::FixSizeU(const PointU& size) const {
	return FixSizeU(*this, size);
}

Vector2 Ratio::FixSizeF(const PointU& size) const {
	return FixSizeF(*this, size);
}

PointU Ratio::FixSizeU(const Ratio& ratio, const PointU& size) {
	Vector2 fixed_size = FixSizeF(ratio, size);
	return PointU((_dword)fixed_size.x, (_dword)fixed_size.y);
}

Vector2 Ratio::FixSizeF(const Ratio& ratio, const PointU& size) {
	if (ratio == Ratio::cNull) {
		return PointF((_float)size.x, (_float)size.y);
	} else {
		Vector2 fixed_size = Ratio(ratio).UpdateSize((_float)size.x, (_float)size.y);
		return fixed_size;
	}
}

Ratio Ratio::Create(const Ratio& ratio, const PointU& size) {
	Ratio ratio_tmp = ratio;
	Vector2 fixed_size = ratio_tmp.UpdateSize((_float)size.x, (_float)size.y);
	return Ratio(fixed_size.x, fixed_size.y);
}
