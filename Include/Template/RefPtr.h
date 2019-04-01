#pragma once

namespace EGE {

/// <summary>
/// The referenced pointer type with auto increase/decrease referenced count.
/// </summary>
template <typename Type>
class RefPtr : public BaseRef<Type> {
protected:
	typedef BaseRef<Type> TBaseClass;

public:
	RefPtr();
	RefPtr(Type* object);
	RefPtr(const RefPtr& refptr);
	RefPtr(const PassRefPtr<Type>& refptr);
	template <typename AnyType>
	RefPtr(PassRefPtr<AnyType>& refptr);
	~RefPtr();

public:
	RefPtr<Type>& operator=(Type* pointer);
	RefPtr<Type>& operator=(const RefPtr& refptr);
	RefPtr<Type>& operator=(const PassRefPtr<Type>& refptr);
	template <typename AnyType>
	RefPtr<Type>& operator=(PassRefPtr<AnyType>& refptr);

public:
	operator Type*() const;

	_void SetPtr(Type* pointer);
};

template <typename Type>
RefPtr<Type>::RefPtr() {
}

template <typename Type>
RefPtr<Type>::RefPtr(Type* object) {
	if (object != _null)
		object->AddRef();

	TBaseClass::mObject = object;
}

template <typename Type>
RefPtr<Type>::RefPtr(const RefPtr& refptr) {
	if (refptr.mObject != _null)
		refptr.mObject->AddRef();

	TBaseClass::mObject = refptr.mObject;
}

template <typename Type>
RefPtr<Type>::RefPtr(const PassRefPtr<Type>& refptr) {
	if (refptr.GetPtr() != _null)
		refptr.GetPtr()->AddRef();

	TBaseClass::mObject = refptr.GetPtr();
}

template <typename Type>
template <typename AnyType>
RefPtr<Type>::RefPtr(PassRefPtr<AnyType>& refptr) {
	Type* object = refptr.template cast_static<Type>();
	if (object != _null)
		object->AddRef();

	TBaseClass::mObject = object;
}

template <typename Type>
RefPtr<Type>::~RefPtr() {
}

template <typename Type>
RefPtr<Type>& RefPtr<Type>::operator=(Type* pointer) {
	if (pointer != _null)
		pointer->AddRef();

	this->Clear();

	TBaseClass::mObject = pointer;

	return *this;
}

template <typename Type>
RefPtr<Type>& RefPtr<Type>::operator=(const RefPtr& refptr) {
	if (refptr.mObject != _null)
		refptr.mObject->AddRef();

	this->Clear();

	TBaseClass::mObject = refptr.mObject;

	return *this;
}

template <typename Type>
RefPtr<Type>& RefPtr<Type>::operator=(const PassRefPtr<Type>& refptr) {
	if (refptr.GetPtr() != _null)
		refptr.GetPtr()->AddRef();

	this->Clear();

	TBaseClass::mObject = refptr.GetPtr();

	return *this;
}

template <typename Type>
template <typename AnyType>
RefPtr<Type>& RefPtr<Type>::operator=(PassRefPtr<AnyType>& refptr) {
	Type* object = refptr.template cast_static<Type>();
	if (object != _null)
		object->AddRef();

	this->Clear();

	TBaseClass::mObject = object;

	return *this;
}

template <typename Type>
RefPtr<Type>::operator Type*() const {
	return TBaseClass::mObject;
}

template <typename Type>
_void RefPtr<Type>::SetPtr(Type* pointer) {
	TBaseClass::mObject = pointer;
}

} // namespace EGE