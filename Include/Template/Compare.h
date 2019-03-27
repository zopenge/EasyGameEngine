#pragma once

namespace EGE {

/// <summary>
/// The dummy binary operation function.
/// </summary>
template <typename T1, typename T2>
struct BinaryFunction {
};

/// <summary>
/// Convert type to key function.
/// </summary>
template <typename Type, typename Key>
struct Type2Key {
	Key operator()(const Type& element) const {
		Key key = (Key)element;
		return key;
	}
};

/// <summary>
/// Convert pointer type to key function.
/// </summary>
template <typename Type, typename Key>
struct PtrType2Key {
	const Key operator()(const Type& element) const {
		Key key = (Key)*element;
		return key;
	}
};

/// <summary>
/// This class is template class to process compare operation.
/// </summary>
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

/// <summary>
/// This class is template class to process NOT-compare operation.
/// </summary>
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

/// <summary>
/// This class is template class to process NOT-compare operation.
/// </summary>
template <typename Type>
struct EqualTo : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		return v1 == v2;
	}
};

/// <summary>
/// This class is template class to process NOT-compare operation.
/// </summary>
template <typename Type>
struct NotEqualTo : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		return v1 != v2;
	}
};

/// <summary>
/// This class is template class to process NOT-compare operation.
/// </summary>
template <typename Type>
struct Greater : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		return v1 > v2;
	}
};

/// <summary>
/// This class is template class to process NOT-compare operation.
/// </summary>
template <typename Type>
struct GreaterEqual : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		return v1 >= v2;
	}
};

/// <summary>
/// This class is template class to process NOT-compare operation.
/// </summary>
template <typename Type>
struct Less : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		return v1 < v2;
	}
};

/// <summary>
/// This class is template class to process NOT-compare operation.
/// </summary>
template <typename Type>
struct LessEqual : public BinaryFunction<Type, Type> {
	//!	Process compare operation.
	_int operator()(const Type& v1, const Type& v2) const {
		return v1 <= v2;
	}
};

} // namespace EGE