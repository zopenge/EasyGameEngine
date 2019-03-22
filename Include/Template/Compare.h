//! @file     Compare.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// BinaryFunction
//----------------------------------------------------------------------------

template <typename T1, typename T2>
struct BinaryFunction {
};

//----------------------------------------------------------------------------
// Convert type to key
//----------------------------------------------------------------------------

template <typename Type, typename Key>
struct Type2Key {
	Key operator()(const Type& element) const {
		Key key = (Key)element;
		return key;
	}
};

template <typename Type, typename Key>
struct PtrType2Key {
	const Key operator()(const Type& element) const {
		Key key = (Key)*element;
		return key;
	}
};

//----------------------------------------------------------------------------
// Compare
//----------------------------------------------------------------------------

//! This class is template class to process compare operation.
template <typename Type>
struct Compare : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		if (v1 > v2)
			return 1;
		else if (v1 == v2)
			return 0;
		else
			return -1;
	}
};

//----------------------------------------------------------------------------
// NotCompare
//----------------------------------------------------------------------------

//! This class is template class to process NOT-compare operation.
template <typename Type>
struct NotCompare : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		if (v1 > v2)
			return -1;
		else if (v1 == v2)
			return 0;
		else
			return 1;
	}
};

//----------------------------------------------------------------------------
// EqualTo
//----------------------------------------------------------------------------

//! This class is template class to process NOT-compare operation.
template <typename Type>
struct EqualTo : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		return v1 == v2;
	}
};

//----------------------------------------------------------------------------
// NotEqualTo
//----------------------------------------------------------------------------

//! This class is template class to process NOT-compare operation.
template <typename Type>
struct NotEqualTo : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		return v1 != v2;
	}
};

//----------------------------------------------------------------------------
// Greater
//----------------------------------------------------------------------------

//! This class is template class to process NOT-compare operation.
template <typename Type>
struct Greater : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		return v1 > v2;
	}
};

//----------------------------------------------------------------------------
// GreaterEqual
//----------------------------------------------------------------------------

//! This class is template class to process NOT-compare operation.
template <typename Type>
struct GreaterEqual : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		return v1 >= v2;
	}
};

//----------------------------------------------------------------------------
// Less
//----------------------------------------------------------------------------

//! This class is template class to process NOT-compare operation.
template <typename Type>
struct Less : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		return v1 < v2;
	}
};

//----------------------------------------------------------------------------
// LessEqual
//----------------------------------------------------------------------------

//! This class is template class to process NOT-compare operation.
template <typename Type>
struct LessEqual : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		return v1 <= v2;
	}
};

} // namespace EGE