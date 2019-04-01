//! @file     MemArrayPtr.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// MemArrayPtr
//----------------------------------------------------------------------------

template <typename Type>
class MemArrayPtr : public BaseMemPtr<Type> {
protected:
	typedef BaseMemPtr<Type> TBaseClass;

protected:
	//!	The number of elements
	_dword mNumber;

public:
	MemArrayPtr();
	MemArrayPtr(_dword number);
	~MemArrayPtr();

public:
	template <typename IndexType>
	Type& operator[](IndexType index);
	template <typename IndexType>
	const Type& operator[](IndexType index) const;

	MemArrayPtr& operator=(const MemArrayPtr& mem_ptr);

public:
	//!	Get number of elements.
	_dword Number() const;
	//!	Get size of elements.
	_dword SizeOfBytes() const;

	//!	Create elements.
	Type* Create(_dword number);
	Type* Create(_dword number, const Type* pointer);
	_void CreateInShareMode(_dword number, const Type* pointer);
	//!	Resize.
	_ubool Resize(_dword number);
	//!	Clear elements.
	_void Clear();
};

//----------------------------------------------------------------------------
// MemArrayPtr Implementation
//----------------------------------------------------------------------------

template <typename Type>
MemArrayPtr<Type>::MemArrayPtr() {
	mNumber = 0;
}

template <typename Type>
MemArrayPtr<Type>::MemArrayPtr(_dword number) {
	EGE_ASSERT(number > 0);

	this->EnableAutoDelete(_true);

	this->mPointer = new Type[number];
	this->mNumber = number;
}

template <typename Type>
MemArrayPtr<Type>::~MemArrayPtr() {
	Clear();
}

template <typename Type>
template <typename IndexType>
Type& MemArrayPtr<Type>::operator[](IndexType index) {
	return this->mPointer[index];
}

template <typename Type>
template <typename IndexType>
const Type& MemArrayPtr<Type>::operator[](IndexType index) const {
	return this->mPointer[index];
}

template <typename Type>
MemArrayPtr<Type>& MemArrayPtr<Type>::operator=(const MemArrayPtr& mem_ptr) {
	Clear();

	if (mem_ptr.IsEnableAutoDelete() && mem_ptr.GetPointer() != _null && mem_ptr.Number() != 0) {
		Create(mem_ptr.Number(), mem_ptr.GetPointer());
	} else {
		this->mPointer = (Type*)mem_ptr.GetPointer();
		this->mNumber = mem_ptr.Number();
	}

	return *this;
}

template <typename Type>
_dword MemArrayPtr<Type>::Number() const {
	return this->mNumber;
}

template <typename Type>
_dword MemArrayPtr<Type>::SizeOfBytes() const {
	return mNumber * sizeof(Type);
}

template <typename Type>
Type* MemArrayPtr<Type>::Create(_dword number) {
	EGE_ASSERT(number > 0);

	Clear();

	this->EnableAutoDelete(_true);

	this->mPointer = new Type[number];
	this->mNumber = number;

	return this->mPointer;
}

template <typename Type>
Type* MemArrayPtr<Type>::Create(_dword number, const Type* pointer) {
	Create(number);

	// Copy the pointer data
	if (pointer != _null)
		memcpy(this->mPointer, pointer, number);

	return this->mPointer;
}

template <typename Type>
_void MemArrayPtr<Type>::CreateInShareMode(_dword number, const Type* pointer) {
	Clear();

	this->EnableAutoDelete(_false);

	this->mPointer = (Type*)pointer;
	this->mNumber = number;
}

template <typename Type>
_ubool MemArrayPtr<Type>::Resize(_dword number) {
	if (this->IsEnableAutoDelete() == _false)
		return _false;

	if (number <= mNumber)
		return _false;

	Type* old_buffer = this->mPointer;
	_dword old_number = mNumber;

	this->mPointer = new Type[number];
	this->mNumber = number;

	if (old_buffer != _null) {
		for (_dword i = 0; i < old_number; i++)
			this->mPointer[i] = old_buffer[i];

		EGE_DELETE_ARRAY(old_buffer);
	}

	return _true;
}

template <typename Type>
_void MemArrayPtr<Type>::Clear() {
	if (this->IsEnableAutoDelete()) {
		EGE_DELETE_ARRAY(this->mPointer);
	}

	this->mPointer = _null;
	this->mNumber = 0;
}

} // namespace EGE