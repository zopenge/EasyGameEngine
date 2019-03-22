//! @file     Pair.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Pair
//----------------------------------------------------------------------------

//! This class is template container class, represents a 2-element structure.

//! Template parameter "Type1" defines the first element type.<br>
//! Template parameter "Type2" defines the second element type.<br>
//! A comparision of pair only care about the first element type, the <b>Key<b> type.
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

//----------------------------------------------------------------------------
// Pair Implementation
//----------------------------------------------------------------------------

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