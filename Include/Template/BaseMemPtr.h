#pragma once

namespace EGE {

/// <summary>
/// The base memory pointer class.
/// </summary>
template <typename Type>
class BaseMemPtr {
protected:
	_ubool mAutoDelete;
	Type* mPointer;

protected:
	BaseMemPtr();
	BaseMemPtr(Type* pointer);
	~BaseMemPtr();

public:
	bool operator==(const BaseMemPtr& memptr) const;
	bool operator!=(const BaseMemPtr& memptr) const;
	bool operator==(const Type* pointer) const;
	bool operator!=(const Type* pointer) const;
	bool operator==(Type* pointer) const;
	bool operator!=(Type* pointer) const;

	operator Type*() const;
	operator const Type*() const;

	operator _void*() const;
	operator const _void*() const;

	_void EnableAutoDelete(_ubool enable);
	_ubool IsEnableAutoDelete() const;

	_ubool IsNull() const;
	_ubool IsValid() const;

	Type* GetPointer();
	const Type* GetPointer() const;

	_void SetPointer(Type* ptr);

	Type*& GetRawRef();

	Type& operator*() const;
	Type* operator->() const;
};

template <typename Type>
BaseMemPtr<Type>::BaseMemPtr() {
	mAutoDelete = _true;
	mPointer = _null;
}

template <typename Type>
BaseMemPtr<Type>::BaseMemPtr(Type* pointer) {
	mAutoDelete = _true;
	mPointer = pointer;
}

template <typename Type>
BaseMemPtr<Type>::~BaseMemPtr() {
	// The pointer must be clear in inherited class
	EGE_ASSERT(mPointer == _null);
}

template <typename Type>
bool BaseMemPtr<Type>::operator==(const BaseMemPtr& memptr) const {
	return mPointer == memptr.mpointer;
}

template <typename Type>
bool BaseMemPtr<Type>::operator!=(const BaseMemPtr& memptr) const {
	return mPointer != memptr.mpointer;
}

template <typename Type>
bool BaseMemPtr<Type>::operator==(const Type* pointer) const {
	return mPointer == pointer;
}

template <typename Type>
bool BaseMemPtr<Type>::operator!=(const Type* pointer) const {
	return mPointer != pointer;
}

template <typename Type>
bool BaseMemPtr<Type>::operator==(Type* pointer) const {
	return mPointer == pointer;
}

template <typename Type>
bool BaseMemPtr<Type>::operator!=(Type* pointer) const {
	return mPointer != pointer;
}

template <typename Type>
_void BaseMemPtr<Type>::EnableAutoDelete(_ubool enable) {
	mAutoDelete = enable;
}

template <typename Type>
_ubool BaseMemPtr<Type>::IsEnableAutoDelete() const {
	return mAutoDelete;
}

template <typename Type>
BaseMemPtr<Type>::operator Type*() const {
	return mPointer;
}

template <typename Type>
BaseMemPtr<Type>::operator const Type*() const {
	return mPointer;
}

template <typename Type>
BaseMemPtr<Type>::operator _void*() const {
	return mPointer;
}

template <typename Type>
BaseMemPtr<Type>::operator const _void*() const {
	return mPointer;
}

template <typename Type>
_ubool BaseMemPtr<Type>::IsNull() const {
	return mPointer == _null;
}

template <typename Type>
_ubool BaseMemPtr<Type>::IsValid() const {
	return mPointer != _null;
}

template <typename Type>
Type* BaseMemPtr<Type>::GetPointer() {
	return mPointer;
}

template <typename Type>
const Type* BaseMemPtr<Type>::GetPointer() const {
	return mPointer;
}

template <typename Type>
_void BaseMemPtr<Type>::SetPointer(Type* ptr) {
	mPointer = ptr;
}

template <typename Type>
Type*& BaseMemPtr<Type>::GetRawRef() {
	return mPointer;
}

template <typename Type>
Type& BaseMemPtr<Type>::operator*() const {
	return *mPointer;
}

template <typename Type>
Type* BaseMemPtr<Type>::operator->() const {
	return mPointer;
}

} // namespace EGE