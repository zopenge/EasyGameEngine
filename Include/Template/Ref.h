//! @file     Ref.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Ref
//----------------------------------------------------------------------------

template <typename Type>
class Ref {
protected:
	Type* mObject;

protected:
	explicit Ref();
	~Ref();

public:
	_void Clear();

	_ubool IsValid() const;
	_ubool IsNull() const;

	Type* GetPtr() const;
	Type*& GetRawRef();

	Type& operator*() const;
	Type* operator->() const;

	template <class ClassType>
	ClassType* cast_static();
	template <class ClassType>
	const ClassType* cast_static() const;

	template <class ClassType>
	ClassType* cast_dynamic();
	template <class ClassType>
	const ClassType* cast_dynamic() const;
};

//----------------------------------------------------------------------------
// Ref Implementation
//----------------------------------------------------------------------------

template <typename Type>
Ref<Type>::Ref()
    : mObject(_null) {
}

template <typename Type>
Ref<Type>::~Ref() {
	Clear();
}

template <typename Type>
_void Ref<Type>::Clear() {
	EGE_RELEASE(mObject);
}

template <typename Type>
_ubool Ref<Type>::IsValid() const {
	return mObject != _null;
}

template <typename Type>
_ubool Ref<Type>::IsNull() const {
	return mObject == _null;
}

template <typename Type>
Type* Ref<Type>::GetPtr() const {
	return mObject;
}

template <typename Type>
Type*& Ref<Type>::GetRawRef() {
	return mObject;
}

template <typename Type>
Type& Ref<Type>::operator*() const {
	return *mObject;
}

template <typename Type>
Type* Ref<Type>::operator->() const {
	return mObject;
}

template <typename Type>
template <class ClassType>
ClassType* Ref<Type>::cast_static() {
	return static_cast<ClassType*>(mObject);
}

template <typename Type>
template <class ClassType>
const ClassType* Ref<Type>::cast_static() const {
	return static_cast<const ClassType*>(mObject);
}

template <typename Type>
template <class ClassType>
ClassType* Ref<Type>::cast_dynamic() {
	return dynamic_cast<ClassType*>(mObject);
}

template <typename Type>
template <class ClassType>
const ClassType* Ref<Type>::cast_dynamic() const {
	return dynamic_cast<const ClassType*>(mObject);
}

} // namespace EGE