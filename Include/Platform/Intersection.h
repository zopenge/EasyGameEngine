//! @file     Intersection.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Intersection
//----------------------------------------------------------------------------

struct PolygonCollisionResult
{
public:
 // Are the polygons going to intersect forward in time?
 _ubool mWillIntersect;
 // Are the polygons currently intersecting?
 _ubool mIntersect;
 // The translation to apply to the first polygon to push the polygons apart.
 Vector2 mMinimumTranslationVector;
};

class Intersection
{
public:
 //! Rectangle VS rectangle.
 //! @param lt   The left-top position.
 //! @param rb   The right-bottom position.
 //! @param region  The region.
 //! @return True indicates hit successful.
 static _ubool RectangleVSRectangle( const Vector2& lt, const Vector2& rb, const RectU& region );

 //! Point VS rectangle by world transform.
 //! @param pos   The position.
 //! @param size  The size of rectangle.
 //! @param transform The world transform of rectangle.
 //! @return True indicates point hit rectangle successful.
 static _ubool PointVSRectangle( const Vector2& pos, const Vector2& size, const Matrix3& transform );

 //! Line2D VS Line2D.
 //! @param line1  The line1.
 //! @param line2  The line2.
 //! @param intersect_point The intersect point of line1 and line2.
 //! @return True indicates line1 hit line2 successful.
 static _ubool Line2DVsLine2D( const Line2D& line1, const Line2D& line2, Vector2* intersect_point = _null );

 static _float IntervalDistance( _float minA, _float maxA, _float minB, _float maxB );
 //! Calculate the projection of a polygon on an axis and returns it as a [min, max] interval
 //! @param axis  The axis.
 //! @param polygon  The polygon.
 //! @param length  The polygon vertex number.
 //! @param min   The result min.
 //! @param max   The result max.
 //! @return none.
 static void ProjectPolygon( const Vector2& axis, const Vector2 polygon [], _dword length, _float& min, _float& max );
 //! Check if polygon 1 is going to collide with polygon 2.
 //! @param polygon1 The polygon1.
 //! @param length1  The polygon1 vertex number.
 //! @param polygon2 The polygon2.
 //! @param length2  The polygon2 vertex number.
 //! @param velocity The relative velocity of the polygons( velocity1 - velocity2 )
 //! @return The polygon collision result.
 static PolygonCollisionResult Polygon2DVSPolygon2D( const Vector2 polygon1 [], _dword length1, const Vector2 polygon2 [], _dword length2, const Vector2& velocity );

 //! Ray VS plane.
 //! @param ray   The ray.
 //! @param plane  The plane.
 //! @param distance The distance from plane to ray.
 //! @return True indicates ray hit plane successful.
 static _ubool RayVSPlane( const Ray& ray, const Plane& plane, _float* distance = _null );
 //! Ray VS triangle.
 //! @param ray   The ray.
 //! @param triangle The triangle.
 //! @param distance The distance from ray to triangle.
 //! @return True indicates ray hit triangle successful.
 static _ubool RayVSTriangle( const Ray& ray, const Triangle& triangle, _float* distance = _null );
 //! Ray VS box.
 //! @param ray   The ray.
 //! @param box   The box.
 //! @param distance The distance from ray to box.
 //! @return True indicates ray hit box successful.
 static _ubool RayVSBox( const Ray& ray, const Box& box, _float* distance = _null );
 //! Ray VS bound-box.
 //! @param ray   The ray.
 //! @param box   The bound-box.
 //! @param distance The distance from ray to bound-box.
 //! @return True indicates ray hit bound-box successful.
 static _ubool RayVSAABox( const Ray& ray, const AxisAlignedBox& box, _float* distance = _null );
 //! Ray VS mesh.
 //! @param ray    The ray.
 //! @param stride   The vertex stride size in bytes.
 //! @param vertex_number The vertex number.
 //! @param vertex_buffer The vertex buffer.
 //! @param index_number The index number.
 //! @param index_buffer The index buffer.
 //! @param distance  The distance from ray to mesh.
 //! @return True indicates ray hit bound-box successful.
 static _ubool RayVSMesh( const Ray& ray, _dword stride, _dword vertex_number, const _byte* vertex_buffer, _dword index_number, const _word* index_buffer, _float* distance = _null );

 //! Oriented-box VS Oriented-box.
 //! @param box1  The oriented-box 1.
 //! @param box2  The oriented-box 2.
 //! @return True indicates oriented-box 1 hit oriented-box 2 successful.
 static _ubool OBBoxVSOBBox( const OrientedBox2D& box1, const OrientedBox2D& box2 );

 //! Bound-box VS bound-box.
 //! @param box1  The bound-box 1.
 //! @param box2  The bound-box 2.
 //! @return True indicates bound-box 1 hit bound-box 2 successful.
 static _ubool AABoxVSAABox( const AxisAlignedBox& box1, const AxisAlignedBox& box2 );
 //! Bound-box VS plane.
 //! @param box   The bound-box.
 //! @param plane  The plane.
 //! @return True indicates bound-box hit plane successful.
 static _ubool AABoxVSPlane( const AxisAlignedBox& box, const Plane& plane );

 static _ubool AABoxVSSphere( const AxisAlignedBox& box, const Sphere& sphere );

 //! Sphere VS sphere.
 //! @param sphere1  The sphere 1.
 //! @param sphere2  The sphere 2.
 //! @return True indicates sphere 1 hit sphere 2 successful.
 static _ubool SphereVSSphere( const Sphere& sphere1, const Sphere& sphere2 );
 //! Sphere VS plane.
 //! @param sphere1  The sphere.
 //! @param plane  The plane.
 //! @return True indicates sphere hit plane successful.
 static _ubool SphereVSPlane( const Sphere& sphere, const Plane& plane );
 //! Sphere VS box.
 //! @param sphere1  The sphere.
 //! @param box   The box.
 //! @return True indicates sphere hit box successful.
 static _ubool SphereVSBox( const Sphere& sphere, const Box& box );

 //----------------------------------------------------------------------------
 // Separate Axis Testing
 //----------------------------------------------------------------------------

 //! Box VS Box
 //! @param box1  The Box 1.
 //! @param box2  The Box 2.
 //! @return True indicates Box 1 hit Box 2 successful.
 static _ubool BoxVSBox( const Box& box1, const Box& box2 );

 static _ubool SeperateAxisTesting( const Vector3& sperateaxis, const Vector3 polygon1[], _dword length1, const Vector3 polygon2[], _dword length2 );

 static _ubool SeperateAxisTesting( const Vector2& sperateaxis, const Vector2 polygon1[], _dword length1, const Vector2 polygon2[], _dword length2 );
};

}