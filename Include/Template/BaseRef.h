#pragma once

namespace EGE {

/// <summary>
/// The base class for manage point referenced count.
/// </summary>
template <typename Type>
class BaseRef {
protected:
	Type* mObject;

protected:
	explicit BaseRef();
	~BaseRef();

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

template <typename Type>
BaseRef<Type>::BaseRef()
    : mObject(_null) {
}

template <typename Type>
BaseRef<Type>::~BaseRef() {
	Clear();
}

template <typename Type>
_void BaseRef<Type>::Clear() {
	EGE_RELEASE(mObject);
}

template <typename Type>
_ubool BaseRef<Type>::IsValid() const {
	return mObject != _null;
}

template <typename Type>
_ubool BaseRef<Type>::IsNull() const {
	return mObject == _null;
}

template <typename Type>
Type* BaseRef<Type>::GetPtr() const {
	return mObject;
}

template <typename Type>
Type*& BaseRef<Type>::GetRawRef() {
	return mObject;
}

template <typename Type>
Type& BaseRef<Type>::operator*() const {
	return *mObject;
}

template <typename Type>
Type* BaseRef<Type>::operator->() const {
	return mObject;
}

template <typename Type>
template <class ClassType>
ClassType* BaseRef<Type>::cast_static() {
	return static_cast<ClassType*>(mObject);
}

template <typename Type>
template <class ClassType>
const ClassType* BaseRef<Type>::cast_static() const {
	return static_cast<const ClassType*>(mObject);
}

template <typename Type>
template <class ClassType>
ClassType* BaseRef<Type>::cast_dynamic() {
	return dynamic_cast<ClassType*>(mObject);
}

template <typename Type>
template <class ClassType>
const ClassType* BaseRef<Type>::cast_dynamic() const {
	return dynamic_cast<const ClassType*>(mObject);
}

} // namespace EGE