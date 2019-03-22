//! @file     Triple.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Triple
//----------------------------------------------------------------------------

//! This class is template container class, represents a 3-element structure.

//! Template parameter "Type1" defines the first element type.<br>
//! Template parameter "Type2" defines the second element type.<br>
//! Template parameter "Type3" defines the third element type.<br>
//! A comparision of triple only care about the first element type, the <b>Key<b> type.
template <typename Type1, typename Type2, typename Type3>
class Triple {
public:
	//! The first element.
	Type1 mObject1;
	//! The second element.
	Type2 mObject2;
	//! The third element.
	Type3 mObject3;

public:
	//! Constructor, create a triple without assigning of elements.
	//! @param		none
	Triple();
	//! Constructor, create a triple and assign elements.
	//! @param		none
	Triple(const Type1& object1, const Type2& object2, const Type3& object3);

public:
	//!	Convert to pair type.
	operator Pair<Type1, Type2>&();
	operator const Pair<Type1, Type2>&() const;

	//! Type conversion, get the first object.
	//! @param		none
	//! @return		The const reference of the first object.
	operator const Type1&() const;
};

//----------------------------------------------------------------------------
// Triple Implementation
//----------------------------------------------------------------------------

template <typename Type1, typename Type2, typename Type3>
Triple<Type1, Type2, Type3>::Triple() {
}

template <typename Type1, typename Type2, typename Type3>
Triple<Type1, Type2, Type3>::Triple(const Type1& object1, const Type2& object2, const Type3& object3)
    : mObject1(object1), mObject2(object2), mObject3(object3) {
}

template <typename Type1, typename Type2, typename Type3>
Triple<Type1, Type2, Type3>::operator Pair<Type1, Type2>&() {
	return (Pair<Type1, Type2>&)*this;
}

template <typename Type1, typename Type2, typename Type3>
Triple<Type1, Type2, Type3>::operator const Pair<Type1, Type2>&() const {
	return (const Pair<Type1, Type2>&)*this;
}

template <typename Type1, typename Type2, typename Type3>
Triple<Type1, Type2, Type3>::operator const Type1&() const {
	return mObject1;
}

}; // namespace EGE