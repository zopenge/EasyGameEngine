#pragma once

namespace EGE {

/// <summary>
/// This class is template container class, represents a 4-element structure.
/// </summary>
template <typename Type1, typename Type2, typename Type3, typename Type4>
class Quadruple {
public:
	//! The first element.
	Type1 mObject1;
	//! The second element.
	Type2 mObject2;
	//! The third element.
	Type3 mObject3;
	//! The fourth element.
	Type4 mObject4;

	//! Constructor, create a quadruple without assigning of elements.
	//! @param		none
	Quadruple();
	//! Constructor, create a quadruple and assign elements.
	//! @param		none
	Quadruple(const Type1& object1, const Type2& object2, const Type3& object3, const Type4& object4);
};

template <typename Type1, typename Type2, typename Type3, typename Type4>
Quadruple<Type1, Type2, Type3, Type4>::Quadruple() {
}

template <typename Type1, typename Type2, typename Type3, typename Type4>
Quadruple<Type1, Type2, Type3, Type4>::Quadruple(const Type1& object1, const Type2& object2, const Type3& object3, const Type4& object4)
    : mObject1(object1), mObject2(object2), mObject3(object3), mObject4(object4) {
}

}; // namespace EGE