#pragma once

// Windows Platform
#if defined _PLATFORM_WINDOWS_

#	include "Platform/OS/windows/Win32Headers.h"
#	include "Platform/OS/windows/Win32Macros.h"

// IOS Platform
#elif defined _PLATFORM_IOS_

#	include "Platform/OS/ios/IOSHeaders.h"

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
#include "Platform/ColliderBox2D.h"
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

// AString
inline AString operator+(AString& str1, _chara character) {
	AString string(str1);
	string += character;

	return string;
}

inline AString operator+(const _chara* str1, const AString& str2) {
	AString string(str1);
	string += str2;

	return string;
}

inline AString operator+(const AString& str1, AStringPtr str2) {
	AString string(str1);
	string += str2;

	return string;
}

inline AString operator+(const AString& str1, const AString& str2) {
	AString string(str1);
	string += str2;

	return string;
}

// UString
inline UString operator+(UString& str1, _chara character) {
	UString string(str1);
	string += character;

	return string;
}

inline UString operator+(const _chara* str1, const UString& str2) {
	UString string(str1);
	string += str2;

	return string;
}

inline UString operator+(const UString& str1, UStringPtr str2) {
	UString string(str1);
	string += str2;

	return string;
}

inline UString operator+(const UString& str1, const UString& str2) {
	UString string(str1);
	string += str2;

	return string;
}

// WString
inline WString operator+(WString& str1, _charw character) {
	WString string(str1);
	string += character;

	return string;
}

inline WString operator+(const _charw* str1, const WString& str2) {
	WString string(str1);
	string += str2;

	return string;
}

inline WString operator+(const WString& str1, WStringPtr str2) {
	WString string(str1);
	string += str2;

	return string;
}

inline WString operator+(const WString& str1, const WString& str2) {
	WString string(str1);
	string += str2;

	return string;
}

//!	Copy string in safe way.
template <_dword _BUFFER_LENGTH, typename CharType>
CharType* SafeCopyString(CharType (&to)[_BUFFER_LENGTH], const CharType* from) {
	return Platform::CopyString(to, from, _BUFFER_LENGTH - 1);
}

//!	Compare key.
template <typename Key>
inline _int CompareKeyInMap(const Key& key1, const Key& key2) {
	if (key1 > key2)
		return 1;
	else if (key1 == key2)
		return 0;
	else
		return -1;
}

template <>
inline _int CompareKeyInMap<_int>(const _int& key1, const _int& key2) {
	return key1 - key2;
}
template <>
inline _int CompareKeyInMap<_dword>(const _dword& key1, const _dword& key2) {
	return (_int)(key1 - key2);
}

template <>
inline _int CompareKeyInMap<AString>(const AString& key1, const AString& key2) {
	return key1.Compare(key2, _false);
}
template <>
inline _int CompareKeyInMap<WString>(const WString& key1, const WString& key2) {
	return key1.Compare(key2, _false);
}

template <>
inline MutableString<_chara, Encoding::Ansi>& MutableString<_chara, Encoding::Ansi>::FormatBytes(_qword bytes) {
	if (bytes >= 1 GB)
		Format("%3.2f GB", (_float)bytes / (_float)1 GB);
	else if (bytes >= 1 MB)
		Format("%3.2f MB", (_float)bytes / (_float)1 MB);
	else
		Format("%3.2f KB", (_float)bytes / (_float)1 KB);

	return *this;
}

template <>
inline MutableString<_chara, Encoding::Utf8>& MutableString<_chara, Encoding::Utf8>::FormatBytes(_qword bytes) {
	if (bytes >= 1 GB)
		Format("%3.2f GB", (_float)bytes / (_float)1 GB);
	else if (bytes >= 1 MB)
		Format("%3.2f MB", (_float)bytes / (_float)1 MB);
	else
		Format("%3.2f KB", (_float)bytes / (_float)1 KB);

	return *this;
}

template <>
inline MutableString<_charw, Encoding::Utf16>& MutableString<_charw, Encoding::Utf16>::FormatBytes(_qword bytes) {
	if (bytes >= 1 GB)
		Format(L"%3.2f GB", (_float)bytes / (_float)1 GB);
	else if (bytes >= 1 MB)
		Format(L"%3.2f MB", (_float)bytes / (_float)1 MB);
	else
		Format(L"%3.2f KB", (_float)bytes / (_float)1 KB);

	return *this;
}

template <>
inline MutableString<_chara, Encoding::Ansi>& MutableString<_chara, Encoding::Ansi>::FormatCurrency(_qword currency) {
	// Max value 4294967295 => 4,294,967,295

	_dword a = (_dword)(currency / 1000000000);
	_dword b = (_dword)((currency % 1000000000) / 1000000);
	_dword c = (_dword)((currency % 1000000) / 1000);
	_dword d = (_dword)(currency % 1000);

	if (a > 0)
		Format("%d,%.3d,%.3d,%.3d", a, b, c, d);
	else if (b > 0)
		Format("%d,%.3d,%.3d", b, c, d);
	else if (c > 0)
		Format("%d,%.3d", c, d);
	else
		Format("%d", d);

	return *this;
}

template <>
inline MutableString<_chara, Encoding::Utf8>& MutableString<_chara, Encoding::Utf8>::FormatCurrency(_qword currency) {
	// Max value 4294967295 => 4,294,967,295

	_dword a = (_dword)(currency / 1000000000);
	_dword b = (_dword)((currency % 1000000000) / 1000000);
	_dword c = (_dword)((currency % 1000000) / 1000);
	_dword d = (_dword)(currency % 1000);

	if (a > 0)
		Format("%d,%.3d,%.3d,%.3d", a, b, c, d);
	else if (b > 0)
		Format("%d,%.3d,%.3d", b, c, d);
	else if (c > 0)
		Format("%d,%.3d", c, d);
	else
		Format("%d", d);

	return *this;
}

template <>
inline MutableString<_charw, Encoding::Utf16>& MutableString<_charw, Encoding::Utf16>::FormatCurrency(_qword currency) {
	// Max value 4294967295 => 4,294,967,295

	_dword a = (_dword)(currency / 1000000000);
	_dword b = (_dword)((currency % 1000000000) / 1000000);
	_dword c = (_dword)((currency % 1000000) / 1000);
	_dword d = (_dword)(currency % 1000);

	if (a > 0)
		Format(L"%d,%.3d,%.3d,%.3d", a, b, c, d);
	else if (b > 0)
		Format(L"%d,%.3d,%.3d", b, c, d);
	else if (c > 0)
		Format(L"%d,%.3d", c, d);
	else
		Format(L"%d", d);

	return *this;
}

template <>
inline MutableString<_chara, Encoding::Ansi>& MutableString<_chara, Encoding::Ansi>::FormatTime(_qword millisecond) {
	_dword hourunit = 60 * 60 * 1000, minuteunit = 60 * 1000, secondunit = 1000;

	_dword hours = (_dword)(millisecond / hourunit);
	_dword minutes = (_dword)((millisecond - hours * hourunit) / minuteunit);
	_dword seconds = (_dword)((millisecond - hours * hourunit - minutes * minuteunit) / secondunit);

	Format("%.2d:%.2d:%.2d", hours, minutes, seconds);

	return *this;
}

template <>
inline MutableString<_chara, Encoding::Utf8>& MutableString<_chara, Encoding::Utf8>::FormatTime(_qword millisecond) {
	_dword hourunit = 60 * 60 * 1000, minuteunit = 60 * 1000, secondunit = 1000;

	_dword hours = (_dword)(millisecond / hourunit);
	_dword minutes = (_dword)((millisecond - hours * hourunit) / minuteunit);
	_dword seconds = (_dword)((millisecond - hours * hourunit - minutes * minuteunit) / secondunit);

	Format("%.2d:%.2d:%.2d", hours, minutes, seconds);

	return *this;
}

template <>
inline MutableString<_charw, Encoding::Utf16>& MutableString<_charw, Encoding::Utf16>::FormatTime(_qword millisecond) {
	_dword hourunit = 60 * 60 * 1000, minuteunit = 60 * 1000, secondunit = 1000;

	_dword hours = (_dword)(millisecond / hourunit);
	_dword minutes = (_dword)((millisecond - hours * hourunit) / minuteunit);
	_dword seconds = (_dword)((millisecond - hours * hourunit - minutes * minuteunit) / secondunit);

	Format(L"%.2d:%.2d:%.2d", hours, minutes, seconds);

	return *this;
}

template <>
inline Params<_qword, 2>::Params() {
	mValues[0] = 0;
	mValues[1] = 0;
}
template <>
inline Params<_qword, 2>::Params(_qword p1) {
	mValues[0] = p1;
	mValues[1] = 0;
}
template <>
inline Params<_qword, 2>::Params(_qword p1, _qword p2) {
	mValues[0] = p1;
	mValues[1] = p2;
}
template <>
inline Params<_qword, 2>::Params(const Params& pars) {
	mValues[0] = pars.mValues[0];
	mValues[1] = pars.mValues[1];
}
template <>
inline Params<_qword, 2>& Params<_qword, 2>::operator=(const Params& pars) {
	mValues[0] = pars.mValues[0];
	mValues[1] = pars.mValues[1];

	return *this;
}
template <>
inline _void Params<_qword, 2>::Clear() {
	mValues[0] = 0;
	mValues[1] = 0;
}

template <>
inline Params<_qword, 3>::Params() {
	mValues[0] = 0;
	mValues[1] = 0;
	mValues[2] = 0;
}
template <>
inline Params<_qword, 3>::Params(_qword p1) {
	mValues[0] = p1;
	mValues[1] = 0;
	mValues[2] = 0;
}
template <>
inline Params<_qword, 3>::Params(_qword p1, _qword p2) {
	mValues[0] = p1;
	mValues[1] = p2;
	mValues[2] = 0;
}
template <>
inline Params<_qword, 3>::Params(_qword p1, _qword p2, _qword p3) {
	mValues[0] = p1;
	mValues[1] = p2;
	mValues[2] = p3;
}
template <>
inline Params<_qword, 3>::Params(const Params& pars) {
	mValues[0] = pars.mValues[0];
	mValues[1] = pars.mValues[1];
	mValues[2] = pars.mValues[2];
}
template <>
inline Params<_qword, 3>& Params<_qword, 3>::operator=(const Params& pars) {
	mValues[0] = pars.mValues[0];
	mValues[1] = pars.mValues[1];
	mValues[2] = pars.mValues[2];

	return *this;
}
template <>
inline _void Params<_qword, 3>::Clear() {
	mValues[0] = 0;
	mValues[1] = 0;
	mValues[2] = 0;
}

template <>
inline Params<_qword, 4>::Params() {
	mValues[0] = 0;
	mValues[1] = 0;
	mValues[2] = 0;
	mValues[3] = 0;
}
template <>
inline Params<_qword, 4>::Params(_qword p1) {
	mValues[0] = p1;
	mValues[1] = 0;
	mValues[2] = 0;
	mValues[3] = 0;
}
template <>
inline Params<_qword, 4>::Params(_qword p1, _qword p2) {
	mValues[0] = p1;
	mValues[1] = p2;
	mValues[2] = 0;
	mValues[3] = 0;
}
template <>
inline Params<_qword, 4>::Params(_qword p1, _qword p2, _qword p3) {
	mValues[0] = p1;
	mValues[1] = p2;
	mValues[2] = p3;
	mValues[3] = 0;
}
template <>
inline Params<_qword, 4>::Params(_qword p1, _qword p2, _qword p3, _qword p4) {
	mValues[0] = p1;
	mValues[1] = p2;
	mValues[2] = p3;
	mValues[3] = p4;
}
template <>
inline Params<_qword, 4>::Params(const Params& pars) {
	mValues[0] = pars.mValues[0];
	mValues[1] = pars.mValues[1];
	mValues[2] = pars.mValues[2];
	mValues[3] = pars.mValues[3];
}
template <>
inline Params<_qword, 4>& Params<_qword, 4>::operator=(const Params& pars) {
	mValues[0] = pars.mValues[0];
	mValues[1] = pars.mValues[1];
	mValues[2] = pars.mValues[2];
	mValues[3] = pars.mValues[3];

	return *this;
}
template <>
inline _void Params<_qword, 4>::Clear() {
	mValues[0] = 0;
	mValues[1] = 0;
	mValues[2] = 0;
	mValues[3] = 0;
}

//!	Swap elements.
template <typename Type>
void Swap(Type& e1, Type& e2) {
	Type e = e1;
	e1 = e2;
	e2 = e;
}

template <typename Type>
struct Type2Long {
	const _int operator()(const Type& element) const {
		return (_int)element;
	}
};

template <typename Type>
struct Type2Dword {
	const _dword operator()(const Type& element) const {
		return (_dword)element;
	}
};

template <typename Type>
struct Type2Float {
	const _float operator()(const Type& element) const {
		return (_float)element;
	}
};

template <typename Type>
struct Type2Double {
	const _double operator()(const Type& element) const {
		return (_double)element;
	}
};

template <typename Type>
struct Type2AStringPtr {
	const AStringPtr operator()(const Type& element) const {
		return (AStringPtr)element;
	}
};

template <typename Type>
struct Type2UStringPtr {
	const UStringPtr operator()(const Type& element) const {
		return (UStringPtr)element;
	}
};

template <typename Type>
struct Type2WStringPtr {
	const WStringPtr operator()(const Type& element) const {
		return (WStringPtr)element;
	}
};

template <typename Type>
struct PtrType2Long {
	const _int operator()(const Type& element) const {
		return (_int)*element;
	}
};

template <typename Type>
struct PtrType2Dword {
	const _dword operator()(const Type& element) const {
		return (_dword)*element;
	}
};

template <typename Type>
struct PtrType2Qword {
	const _qword operator()(const Type& element) const {
		return (_qword)*element;
	}
};

template <typename Type>
struct PtrType2Float {
	const _float operator()(const Type& element) const {
		return (_float)*element;
	}
};

template <typename Type>
struct PtrType2Double {
	const _double operator()(const Type& element) const {
		return (_double)*element;
	}
};

template <typename Type>
struct PtrType2AStringPtr {
	const AStringPtr operator()(const Type& element) const {
		return (AStringPtr)*element;
	}
};

template <typename Type>
struct PtrType2UStringPtr {
	const UStringPtr operator()(const Type& element) const {
		return (UStringPtr)*element;
	}
};

template <typename Type>
struct PtrType2WStringPtr {
	const WStringPtr operator()(const Type& element) const {
		return (WStringPtr)*element;
	}
};

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