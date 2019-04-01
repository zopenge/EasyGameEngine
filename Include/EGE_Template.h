//! @file     EGE_Template.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

#if defined(_PLATFORM_WINDOWS_)
// Standard C-RunTime Files
#	include <memory.h>
#	include <stdio.h>
#elif defined(_PLATFORM_IOS_)
// Standard C-RunTime Files
#	include <memory.h>
#	include <stdio.h>
#elif defined(_PLATFORM_OSX_)
// Standard C-RunTime Files
#	include <memory.h>
#	include <stdio.h>
#elif defined(_PLATFORM_ANDROID_)
// Standard C-RunTime Files
#	include <memory.h>
#	include <stdio.h>
// The android NDK memset() etc functions are not in the memory.h header file(Shit)
#	include <string.h> /* For memset() */
#endif

// Base Platform Files
#include "Platform/Maths.h"

// Base Template Files
#include "Template/CountOf.h"

// Template Files
#include "Template/Algorithm.h"
#include "Template/Array.h"
#include "Template/BinaryHeap.h"
#include "Template/BitArray.h"
#include "Template/CallbackFunc.h"
#include "Template/Compare.h"
#include "Template/DataField.h"
#include "Template/DataOwner.h"
#include "Template/DependencyGraph.h"
#include "Template/Graph.h"
#include "Template/HashMap.h"
#include "Template/Link.h"
#include "Template/Map.h"
#include "Template/MemArrayPtr.h"
#include "Template/MemPtr.h"
#include "Template/MemPtrBase.h"
#include "Template/MemSegmentPtr.h"
#include "Template/PagePool.h"
#include "Template/Pair.h"
#include "Template/Params.h"
#include "Template/PassRefPtr.h"
#include "Template/Point.h"
#include "Template/Progression.h"
#include "Template/Quadruple.h"
#include "Template/Queue.h"
#include "Template/RBTree.h"
#include "Template/Range.h"
#include "Template/Rect.h"
#include "Template/RefObject.h"
#include "Template/RefPtr.h"
#include "Template/SafeValue.h"
#include "Template/Stack.h"
#include "Template/Tree.h"
#include "Template/Triple.h"

namespace EGE {

//!	Qword Params
typedef Params<_qword, 2> QwordParams2;
typedef Params<_qword, 3> QwordParams3;
typedef Params<_qword, 4> QwordParams4;

//! Point
typedef Point<_int> PointI;
typedef Point<_dword> PointU;
typedef Point<_float> PointF;

//! Rect
typedef Rect<_int> RectI;
typedef Rect<_dword> RectU;
typedef Rect<_float> RectF;

//! SafeValue
typedef SafeValue<_int, _int, _dword> SafeInt;
typedef SafeValue<_dword, _dword, _dword> SafeDword;
typedef SafeValue<_float, _float, _dword> SafeFloat;
typedef SafeValue<_boolean, _ubool, _dword> SafeBool;
typedef SafeValue<_double, _double, _qword> SafeDouble;
typedef SafeValue<_time_t, _time_t, _qword> SafeTime;
typedef SafeValue<_large, _large, _qword> SafeLarge;
typedef SafeValue<_qword, _qword, _qword> SafeQword;

typedef Array<SafeInt> SafeIntArray;
typedef Array<SafeDword> SafeDwordArray;
typedef Array<SafeFloat> SafeFloatArray;
typedef Array<SafeBool> SafeBoolArray;
typedef Array<SafeDouble> SafeDoubleArray;
typedef Array<SafeTime> SafeTimeArray;
typedef Array<SafeLarge> SafeLargeArray;
typedef Array<SafeQword> SafeQwordArray;

//! FadeObject
typedef FadeObject<_int> IntFadeObject;
typedef FadeObject<_dword> DwordFadeObject;
typedef FadeObject<_float> FloatFadeObject;
typedef FadeObject<_ubool> BoolFadeObject;
typedef FadeObject<SafeInt> SafeIntFadeObject;
typedef FadeObject<SafeDword> SafeDwordFadeObject;
typedef FadeObject<SafeQword> SafeQwordFadeObject;
typedef FadeObject<SafeFloat> SafeFloatFadeObject;
typedef FadeObject<SafeBool> SafeBoolFadeObject;

//! Line
class Vector2;
class Vector3;
typedef Line<Vector2> Line2D;
typedef Line<Vector3> Line3D;
typedef Array<Line2D> Line2DArray;
typedef Array<Line3D> Line3DArray;

//! Range
typedef Range<_short> ShortRange;
typedef Range<_int> IntRange;
typedef Range<_word> WordRange;
typedef Range<_dword> DwordRange;
typedef Range<_qword> QwordRange;
typedef Range<_float> FloatRange;

//! Progression
typedef Progression<_word> WordProgression;
typedef Progression<_dword> DwordProgression;
typedef Progression<_float> FloatProgression;

//! DataField
typedef DataField<_word> WordDataField;
typedef DataField<_dword> DwordDataField;
typedef DataField<_float> FloatDataField;

//! Memory
typedef MemSegmentPtr<_short> ShortMemSegmentPtr;
typedef MemSegmentPtr<_int> IntMemSegmentPtr;
typedef MemSegmentPtr<_byte> ByteMemSegmentPtr;
typedef MemSegmentPtr<_word> WordMemSegmentPtr;
typedef MemSegmentPtr<_dword> DwordMemSegmentPtr;
typedef MemSegmentPtr<_qword> QwordMemSegmentPtr;
typedef MemSegmentPtr<_float> FloatMemSegmentPtr;
typedef MemSegmentPtr<Vector2> Vector2MemSegmentPtr;
typedef MemSegmentPtr<Vector3> Vector3MemSegmentPtr;
typedef MemSegmentPtr<Vector4> Vector4MemSegmentPtr;

//!	Qword Params
typedef Params<_qword, 2> QwordParams2;
typedef Params<_qword, 3> QwordParams3;
typedef Params<_qword, 4> QwordParams4;

//! Point
typedef Point<_int> PointI;
typedef Point<_dword> PointU;
typedef Point<_float> PointF;

//! Rect
typedef Rect<_int> RectI;
typedef Rect<_dword> RectU;
typedef Rect<_float> RectF;

//! SafeValue
typedef SafeValue<_int, _int, _dword> SafeInt;
typedef SafeValue<_dword, _dword, _dword> SafeDword;
typedef SafeValue<_float, _float, _dword> SafeFloat;
typedef SafeValue<_boolean, _ubool, _dword> SafeBool;
typedef SafeValue<_double, _double, _qword> SafeDouble;
typedef SafeValue<_time_t, _time_t, _qword> SafeTime;
typedef SafeValue<_large, _large, _qword> SafeLarge;
typedef SafeValue<_qword, _qword, _qword> SafeQword;

typedef Array<SafeInt> SafeIntArray;
typedef Array<SafeDword> SafeDwordArray;
typedef Array<SafeFloat> SafeFloatArray;
typedef Array<SafeBool> SafeBoolArray;
typedef Array<SafeDouble> SafeDoubleArray;
typedef Array<SafeTime> SafeTimeArray;
typedef Array<SafeLarge> SafeLargeArray;
typedef Array<SafeQword> SafeQwordArray;

//! FadeObject
typedef FadeObject<_int> IntFadeObject;
typedef FadeObject<_dword> DwordFadeObject;
typedef FadeObject<_float> FloatFadeObject;
typedef FadeObject<_ubool> BoolFadeObject;
typedef FadeObject<SafeInt> SafeIntFadeObject;
typedef FadeObject<SafeDword> SafeDwordFadeObject;
typedef FadeObject<SafeQword> SafeQwordFadeObject;
typedef FadeObject<SafeFloat> SafeFloatFadeObject;
typedef FadeObject<SafeBool> SafeBoolFadeObject;

//! Line
class Vector2;
class Vector3;
typedef Line<Vector2> Line2D;
typedef Line<Vector3> Line3D;
typedef Array<Line2D> Line2DArray;
typedef Array<Line3D> Line3DArray;

//! Range
typedef Range<_short> ShortRange;
typedef Range<_int> IntRange;
typedef Range<_word> WordRange;
typedef Range<_dword> DwordRange;
typedef Range<_qword> QwordRange;
typedef Range<_float> FloatRange;

//! Progression
typedef Progression<_word> WordProgression;
typedef Progression<_dword> DwordProgression;
typedef Progression<_float> FloatProgression;

//! DataField
typedef DataField<_word> WordDataField;
typedef DataField<_dword> DwordDataField;
typedef DataField<_float> FloatDataField;

//! Memory
typedef MemSegmentPtr<_short> ShortMemSegmentPtr;
typedef MemSegmentPtr<_int> IntMemSegmentPtr;
typedef MemSegmentPtr<_byte> ByteMemSegmentPtr;
typedef MemSegmentPtr<_word> WordMemSegmentPtr;
typedef MemSegmentPtr<_dword> DwordMemSegmentPtr;
typedef MemSegmentPtr<_qword> QwordMemSegmentPtr;
typedef MemSegmentPtr<_float> FloatMemSegmentPtr;
typedef MemSegmentPtr<Vector2> Vector2MemSegmentPtr;
typedef MemSegmentPtr<Vector3> Vector3MemSegmentPtr;
typedef MemSegmentPtr<Vector4> Vector4MemSegmentPtr;

//----------------------------------------------------------------------------
// Template function implementation
//----------------------------------------------------------------------------

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
inline Params<_qword, 2>::Params() {
	mParams[0] = 0;
	mParams[1] = 0;
}
template <>
inline Params<_qword, 2>::Params(_qword p1) {
	mParams[0] = p1;
	mParams[1] = 0;
}
template <>
inline Params<_qword, 2>::Params(_qword p1, _qword p2) {
	mParams[0] = p1;
	mParams[1] = p2;
}
template <>
inline Params<_qword, 2>::Params(const Params& pars) {
	mParams[0] = pars.mParams[0];
	mParams[1] = pars.mParams[1];
}
template <>
inline Params<_qword, 2>& Params<_qword, 2>::operator=(const Params& pars) {
	mParams[0] = pars.mParams[0];
	mParams[1] = pars.mParams[1];

	return *this;
}
template <>
inline _void Params<_qword, 2>::Clear() {
	mParams[0] = 0;
	mParams[1] = 0;
}

template <>
inline Params<_qword, 3>::Params() {
	mParams[0] = 0;
	mParams[1] = 0;
	mParams[2] = 0;
}
template <>
inline Params<_qword, 3>::Params(_qword p1) {
	mParams[0] = p1;
	mParams[1] = 0;
	mParams[2] = 0;
}
template <>
inline Params<_qword, 3>::Params(_qword p1, _qword p2) {
	mParams[0] = p1;
	mParams[1] = p2;
	mParams[2] = 0;
}
template <>
inline Params<_qword, 3>::Params(_qword p1, _qword p2, _qword p3) {
	mParams[0] = p1;
	mParams[1] = p2;
	mParams[2] = p3;
}
template <>
inline Params<_qword, 3>::Params(const Params& pars) {
	mParams[0] = pars.mParams[0];
	mParams[1] = pars.mParams[1];
	mParams[2] = pars.mParams[2];
}
template <>
inline Params<_qword, 3>& Params<_qword, 3>::operator=(const Params& pars) {
	mParams[0] = pars.mParams[0];
	mParams[1] = pars.mParams[1];
	mParams[2] = pars.mParams[2];

	return *this;
}
template <>
inline _void Params<_qword, 3>::Clear() {
	mParams[0] = 0;
	mParams[1] = 0;
	mParams[2] = 0;
}

template <>
inline Params<_qword, 4>::Params() {
	mParams[0] = 0;
	mParams[1] = 0;
	mParams[2] = 0;
	mParams[3] = 0;
}
template <>
inline Params<_qword, 4>::Params(_qword p1) {
	mParams[0] = p1;
	mParams[1] = 0;
	mParams[2] = 0;
	mParams[3] = 0;
}
template <>
inline Params<_qword, 4>::Params(_qword p1, _qword p2) {
	mParams[0] = p1;
	mParams[1] = p2;
	mParams[2] = 0;
	mParams[3] = 0;
}
template <>
inline Params<_qword, 4>::Params(_qword p1, _qword p2, _qword p3) {
	mParams[0] = p1;
	mParams[1] = p2;
	mParams[2] = p3;
	mParams[3] = 0;
}
template <>
inline Params<_qword, 4>::Params(_qword p1, _qword p2, _qword p3, _qword p4) {
	mParams[0] = p1;
	mParams[1] = p2;
	mParams[2] = p3;
	mParams[3] = p4;
}
template <>
inline Params<_qword, 4>::Params(const Params& pars) {
	mParams[0] = pars.mParams[0];
	mParams[1] = pars.mParams[1];
	mParams[2] = pars.mParams[2];
	mParams[3] = pars.mParams[3];
}
template <>
inline Params<_qword, 4>& Params<_qword, 4>::operator=(const Params& pars) {
	mParams[0] = pars.mParams[0];
	mParams[1] = pars.mParams[1];
	mParams[2] = pars.mParams[2];
	mParams[3] = pars.mParams[3];

	return *this;
}
template <>
inline _void Params<_qword, 4>::Clear() {
	mParams[0] = 0;
	mParams[1] = 0;
	mParams[2] = 0;
	mParams[3] = 0;
}

//!	Swap elements.
template <typename Type>
void Swap(Type& e1, Type& e2) {
	Type e = e1;
	e1 = e2;
	e2 = e;
}

} // namespace EGE
