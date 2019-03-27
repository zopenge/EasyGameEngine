#pragma once

namespace EGE {

/// <summary>
/// This class is template container class, represents a 2-element structure.
/// </summary>
template <typename Type1, typename Type2>
class Pair {
public:
	//! The first element.
	Type1 mObject1;
	//! The second element.
	Type2 mObject2;

public:
	Pair();
	Pair(const Pair& pair);
	Pair(const Type1& object1);
	Pair(const Type1& object1, const Type2& object2);
	~Pair();

public:
	//! Type conversion, get the first object.
	//! @param		none
	//! @return		The const reference of the first object.
	operator const Type1&() const;
};

template <typename Type1, typename Type2>
Pair<Type1, Type2>::Pair() {
}

template <typename Type1, typename Type2>
Pair<Type1, Type2>::Pair(const Pair& pair)
    : mObject1(pair.mObject1), mObject2(pair.mObject2) {
}

template <typename Type1, typename Type2>
Pair<Type1, Type2>::Pair(const Type1& object1)
    : mObject1(object1) {
}

template <typename Type1, typename Type2>
Pair<Type1, Type2>::Pair(const Type1& object1, const Type2& object2)
    : mObject1(object1), mObject2(object2) {
}

template <typename Type1, typename Type2>
Pair<Type1, Type2>::~Pair() {
}

template <typename Type1, typename Type2>
Pair<Type1, Type2>::operator const Type1&() const {
	return mObject1;
}

}; // namespace EGE