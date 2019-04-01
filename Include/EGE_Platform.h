//! @file     EGE_Platform.h
//! @author   LiCode
//! @version  1.0.0.702
//! @date     2011/02/15
//! Copyright ...

#pragma once

// Windows Platform
#if defined _PLATFORM_WINDOWS_

#	include "Platform/OS/windows/Win32Headers.h"
#	include "Platform/OS/windows/Win32Macros.h"

// IOS Platform
#elif defined _PLATFORM_IOS_

#	include "Platform/OS/ios/IOSHeaders.h"

// OSX Platform
#elif defined _PLATFORM_OSX_

// Android Platform
#elif defined _PLATFORM_ANDROID_

#endif

// Platform Base Files
#include "Platform/CRC.h"
#include "Platform/Mathics.h"
#include "Platform/Platform.h"

// Platform-Kernel Files
#include "Platform/KernelObject.h"
#include "Platform/Lock.h"
#include "Platform/StringFormatter.h"
#include "Platform/SyncObject.h"
#include "Platform/Thread.h"
#include "Platform/Version.h"

// Platform-Vector Files
#include "Platform/Vector2.h"
#include "Platform/Vector3.h"
#include "Platform/Vector4.h"

// Platform-Rotation Files
#include "Platform/EulerAngles.h"
#include "Platform/Quaternion.h"

// Platform-Matrix Files
#include "Platform/Matrix2.h"
#include "Platform/Matrix3.h"
#include "Platform/Matrix3x4.h"
#include "Platform/Matrix4.h"
#include "Platform/Matrix4Adjustor.h"
#include "Platform/Transform2D.h"
#include "Platform/Transform3D.h"

// Platform-Template Files
#include "Template/Line.h"

namespace EGE {

//! Line
typedef Line<Vector2> Line2D;
typedef Line<Vector3> Line3D;
typedef Array<Line2D> Line2DArray;
typedef Array<Line3D> Line3DArray;

} // namespace EGE

// Platform-BaseGeometry Files
#include "Platform/Box.h"
#include "Platform/OrientedBox2D.h"
#include "Platform/Plane.h"
#include "Platform/Ray.h"
#include "Platform/Sphere.h"
#include "Platform/Triangle.h"
#include "Platform/Triangle2D.h"
#include "Platform/Viewport.h"

// Platform-Geometry Files
#include "Platform/Bounds.h"
#include "Platform/Frustum.h"

// Platform Files
#include "Platform/CallStackFrame.h"
#include "Platform/Camera.h"
#include "Platform/Camera2D.h"
#include "Platform/Color.h"
#include "Platform/DebugSymbol.h"
#include "Platform/DirectoryRecorder.h"
#include "Platform/FPSTimer.h"
#include "Platform/File.h"
#include "Platform/FileFinder.h"
#include "Platform/FileMapping.h"
#include "Platform/FileSystem.h"
#include "Platform/FlagsObject.h"
#include "Platform/IPAddress.h"
#include "Platform/Interpolation.h"
#include "Platform/Intersection.h"
#include "Platform/KeyCodes.h"
#include "Platform/Library.h"
#include "Platform/MD5.h"
#include "Platform/Memory.h"
#include "Platform/Path.h"
#include "Platform/PersistenceThread.h"
#include "Platform/Pipe.h"
#include "Platform/Polygon2D.h"
#include "Platform/Precision.h"
#include "Platform/Random.h"
#include "Platform/Ratio.h"
#include "Platform/Serializer.h"
#include "Platform/TempDir.h"
#include "Platform/Time.h"
#include "Platform/Timer.h"
#include "Platform/UID.h"
#include "Platform/ValueEncoder.h"
#include "Platform/Variable.h"

// Windows Platform
#if defined _PLATFORM_WINDOWS_

// IOS Platform
#elif defined _PLATFORM_IOS_

// Only work for OBJ-C mode.
#	ifdef __OBJC__
#		include "Platform/OS/ios/NSPlatform.h"
#	endif

#	include "Platform/OS/ios/IOSPlatform.h"

// OSX Platform
#elif defined _PLATFORM_OSX_

// Android Platform
#elif defined _PLATFORM_ANDROID_

#endif

namespace EGE {

typedef Range<Vector3> Vector3Range;
typedef Range<Color> ColorRange;

typedef Array<Color> ColorArray;
typedef Array<Variable> VariableArray;
typedef Array<Vector2> Vector2Array;
typedef Array<Vector3> Vector3Array;
typedef Array<Matrix2> Matrix2Array;
typedef Array<Matrix3> Matrix3Array;
typedef Array<Matrix3x4> Matrix3x4Array;
typedef Array<Matrix4> Matrix4Array;
typedef Array<Triangle> TriangleArray;
typedef Array<Triangle2D> Triangle2DArray;

typedef Stack<Matrix3> Matrix3Stack;
typedef Stack<Matrix4> Matrix4Stack;

typedef MemSegmentPtr<Vector2> Vector2MemSegmentPtr;
typedef MemSegmentPtr<Vector3> Vector3MemSegmentPtr;
typedef MemSegmentPtr<Vector4> Vector4MemSegmentPtr;

template <>
inline _ubool PointF::operator==(const PointF& point) const {
	return Math::Equal(x, point.x) && Math::Equal(y, point.y);
}

template <>
inline _ubool PointF::operator!=(const PointF& point) const {
	return (!Math::Equal(x, point.x)) || (!Math::Equal(y, point.y));
}

template <>
inline _ubool RectF::operator==(const RectF& rect) const {
	return Math::Equal(l, rect.l) && Math::Equal(t, rect.t) && Math::Equal(r, rect.r) && Math::Equal(b, rect.b);
}

template <>
inline _ubool RectF::operator!=(const RectF& rect) const {
	return (!Math::Equal(l, rect.l)) || (!Math::Equal(t, rect.t)) || (!Math::Equal(r, rect.r)) || (!Math::Equal(b, rect.b));
}

template <>
struct Compare<AStringPtr> : public BinaryFunction<AStringPtr, AStringPtr> {
	//!	Process compare operation.
	_int operator()(const AStringPtr& v1, const AStringPtr& v2) const {
		return Platform::CompareString(v1.CStr(), v2.CStr());
	}
};

template <>
struct NotCompare<AStringPtr> : public BinaryFunction<AStringPtr, AStringPtr> {
	//!	Process compare operation.
	_int operator()(const AStringPtr& v1, const AStringPtr& v2) const {
		return Platform::CompareString(v1.CStr(), v2.CStr()) * -1;
	}
};

template <>
struct Compare<UStringPtr> : public BinaryFunction<UStringPtr, UStringPtr> {
	//!	Process compare operation.
	_int operator()(const UStringPtr& v1, const UStringPtr& v2) const {
		return Platform::CompareString(v1.CStr(), v2.CStr());
	}
};

template <>
struct NotCompare<UStringPtr> : public BinaryFunction<UStringPtr, UStringPtr> {
	//!	Process compare operation.
	_int operator()(const UStringPtr& v1, const UStringPtr& v2) const {
		return Platform::CompareString(v1.CStr(), v2.CStr()) * -1;
	}
};

template <>
struct Compare<WStringPtr> : public BinaryFunction<WStringPtr, WStringPtr> {
	//!	Process compare operation.
	_int operator()(const WStringPtr& v1, const WStringPtr& v2) const {
		return Platform::CompareString(v1.CStr(), v2.CStr());
	}
};

template <>
struct NotCompare<WStringPtr> : public BinaryFunction<WStringPtr, WStringPtr> {
	//!	Process compare operation.
	_int operator()(const WStringPtr& v1, const WStringPtr& v2) const {
		return Platform::CompareString(v1.CStr(), v2.CStr()) * -1;
	}
};

} // namespace EGE