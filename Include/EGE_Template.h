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

// Base Template Files
#include "Template/Compare.h"
#include "Template/CountOf.h"
#include "Template/Pair.h"
#include "Template/Quadruple.h"
#include "Template/Triple.h"

// Base Container Template Files
#include "Template/Algorithm.h"
#include "Template/Array.h"
#include "Template/FixedArray.h"
#include "Template/HashMap.h"
#include "Template/Link.h"
#include "Template/Queue.h"
#include "Template/RBTree.h"
#include "Template/Stack.h"
#include "Template/Tree.h"

// Template Files
#include "Template/BaseMemPtr.h"
#include "Template/BaseRef.h"
#include "Template/BinaryHeap.h"
#include "Template/BitArray.h"
#include "Template/CallbackFunc.h"
#include "Template/DataField.h"
#include "Template/DataOwner.h"
#include "Template/MemArrayPtr.h"
#include "Template/MemPtr.h"
#include "Template/MemSegmentPtr.h"
#include "Template/PagePool.h"
#include "Template/Params.h"
#include "Template/PassRefPtr.h"
#include "Template/Point.h"
#include "Template/Progression.h"
#include "Template/Range.h"
#include "Template/Rect.h"
#include "Template/RefObject.h"
#include "Template/RefPtr.h"
#include "Template/SafeValue.h"

// Complex-Map Template Files
#include "Template/Map.h"
// Complex-Graph Template Files
#include "Template/Graph.h"
// Complex-DependencyGraph Template Files
#include "Template/DependencyGraph.h"

// String Template Files
#include "Template/ConstString.h"
#include "Template/MutableString.h"

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

//! Memory segments
typedef MemSegmentPtr<_short> ShortMemSegmentPtr;
typedef MemSegmentPtr<_int> IntMemSegmentPtr;
typedef MemSegmentPtr<_byte> ByteMemSegmentPtr;
typedef MemSegmentPtr<_word> WordMemSegmentPtr;
typedef MemSegmentPtr<_dword> DwordMemSegmentPtr;
typedef MemSegmentPtr<_qword> QwordMemSegmentPtr;
typedef MemSegmentPtr<_float> FloatMemSegmentPtr;

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

typedef Array<_word> WordArray;
typedef Array<_dword> DwordArray;
typedef Array<_qword> QwordArray;
typedef Array<_int> IntArray;
typedef Array<_large> LargeArray;
typedef Array<_float> FloatArray;
typedef Array<_double> DoubleArray;
typedef Stack<_word> WordStack;
typedef Stack<_dword> DwordStack;

typedef ConstString<_chara, Encoding::Ansi> AStringPtr;
typedef ConstString<_chara, Encoding::Utf8> UStringPtr;
typedef ConstString<_charw, Encoding::Utf16> WStringPtr;

typedef MutableString<_chara, Encoding::Ansi> AString;
typedef MutableString<_chara, Encoding::Utf8> UString;
typedef MutableString<_charw, Encoding::Utf16> WString;

typedef Array<AString> AStringArray;
typedef Array<UString> UStringArray;
typedef Array<WString> WStringArray;

typedef Map<AString, AString> AStringMap;
typedef Map<UString, UString> UStringMap;
typedef Map<WString, WString> WStringMap;

typedef BitArray<1> OneBitArray;

typedef Queue<AString> AStringQueue;
typedef Queue<UString> UStringQueue;
typedef Queue<WString> WStringQueue;

} // namespace EGE
