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

inline AString operator+(const AString& str1, const _chara* str2) {
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

inline UString operator+(const UString& str1, const _chara* str2) {
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

inline WString operator+(const WString& str1, const _charw* str2) {
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

} // namespace EGE
