#pragma once

namespace EGE {

/// <summary>
/// This class referenced from here: http://www.flipcode.com/archives/2D_OBB_Intersection.shtml, thanks for open source
/// </summary>
class ColliderBox2D {
public:
	static const ColliderBox2D cNull;

public:
	// Corners of the box, where 0 is the lower left.
	Vector2 mCorner[4];
	// Two edges of the box extended away from corner[0].
	Vector2 mAxis[2];
	// origin[a] = corner[0].dot(axis[a])
	_float mOrigin[2];

private:
	//! Updates the axes after the corners move, assumes the corners actually form a rectangle.
	_void ComputeAxes();

public:
	ColliderBox2D();
	ColliderBox2D(const Vector2& lt, const Vector2& rt, const Vector2& rb, const Vector2& lb);
	ColliderBox2D(const Vector2& center, _float w, _float h, _float radian);
	ColliderBox2D(const ColliderBox2D& box);

public:
	//! Convert to rectangle.
	RectF ToRectF() const;
	//! Convert from rectangle.
	ColliderBox2D& FromRectF(const RectF& rect);

	//! Move center position.
	//! @param center The center position.
	//! @return none.
	_void MoveTo(const Vector2& center);

	//! Set the width and height
	//! @param width The width.
	//! @param height The height.
	//! @return none.
	_void SetSize(_float width, _float height);

	//! Returns true if other overlaps one dimension of this.
	//! @param other The other box.
	//! @return True indicates it's overlapped in one dimension.
	_ubool Overlaps1Way(const ColliderBox2D& other) const;

	//! Return true if the point in box
	//! @param point The point.
	//! @return True indicates the point in this box.
	_ubool PointInOrientedBox(const Vector2& point) const;

public:
	ColliderBox2D& operator*=(const Matrix3& matrix);
	ColliderBox2D operator*(const Matrix3& matrix) const;
};

} // namespace EGE