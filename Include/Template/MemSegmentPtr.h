#pragma once

namespace EGE {

/// <summary>
/// The allocated memory segment pointer.
/// </summary>
template <typename Type>
class MemSegmentPtr : public BaseMemPtr<Type> {
protected:
	typedef BaseMemPtr<Type> TBaseClass;

protected:
	//!	The number of elements
	_dword mNumber;
	//! The buffer stride
	_dword mStride;

public:
	MemSegmentPtr();
	~MemSegmentPtr();

public:
	Type& operator[](_dword index);
	const Type& operator[](_dword index) const;

	MemSegmentPtr& operator=(const MemSegmentPtr& mem_ptr);

public:
	//!	Get number of elements.
	_dword Number() const;
	//!	Get stride of elements.
	_dword GetStride() const;

	//!	Create elements.
	Type* Create(_dword number);
	Type* Create(_dword number, const _void* pointer);
	Type* Share(_dword number, _void* pointer);
	Type* Share(_dword number, _void* pointer, _dword stride);
	//!	Clear elements.
	_void Clear();
};

template <typename Type>
MemSegmentPtr<Type>::MemSegmentPtr() {
	this->mNumber = 0;
	this->mStride = sizeof(Type);
	this->mPointer = _null;
	this->mAutoDelete = _false;
}

template <typename Type>
MemSegmentPtr<Type>::~MemSegmentPtr() {
	this->Clear();
}

template <typename Type>
Type& MemSegmentPtr<Type>::operator[](_dword index) {
	EGE_ASSERT(index < this->mNumber);

	return *((Type*)(((_byte*)this->mPointer) + this->mStride * index));
}

template <typename Type>
const Type& MemSegmentPtr<Type>::operator[](_dword index) const {
	EGE_ASSERT(index < this->mNumber);

	return *((const Type*)(((const _byte*)this->mPointer) + this->mStride * index));
}

template <typename Type>
MemSegmentPtr<Type>& MemSegmentPtr<Type>::operator=(const MemSegmentPtr& mem_ptr) {
	if (mem_ptr.IsEnableAutoDelete() && mem_ptr.GetPointer() != _null && mem_ptr.Number() != 0) {
		this->Create(mem_ptr.Number(), mem_ptr.GetPointer());
	} else {
		this->Share(mem_ptr.Number(), mem_ptr.GetPointer(), mem_ptr.GetStride());
	}

	return *this;
}

template <typename Type>
_dword MemSegmentPtr<Type>::Number() const {
	return this->mNumber;
}

template <typename Type>
_dword MemSegmentPtr<Type>::GetStride() const {
	return this->mStride;
}

template <typename Type>
Type* MemSegmentPtr<Type>::Create(_dword number) {
	EGE_ASSERT(number > 0);

	Clear();

	this->mAutoDelete = _true;
	this->mPointer = new Type[number];
	this->mNumber = number;

	return this->mPointer;
}

template <typename Type>
Type* MemSegmentPtr<Type>::Create(_dword number, const _void* pointer) {
	Create(number);

	// Copy the pointer data
	if (pointer != _null)
		memcpy(this->mPointer, (Type*)pointer, number);

	return this->mPointer;
}

template <typename Type>
Type* MemSegmentPtr<Type>::Share(_dword number, _void* pointer) {
	Clear();

	this->mNumber = number;
	this->mPointer = (Type*)pointer;

	return this->mPointer;
}

template <typename Type>
Type* MemSegmentPtr<Type>::Share(_dword number, _void* pointer, _dword stride) {
	Clear();

	this->mNumber = number;
	this->mPointer = (Type*)pointer;
	this->mStride = stride;

	return this->mPointer;
}

template <typename Type>
_void MemSegmentPtr<Type>::Clear() {
	if (this->mAutoDelete) {
		EGE_DELETE_ARRAY(this->mPointer);
	}

	this->mNumber = 0;
	this->mStride = sizeof(Type);
	this->mPointer = _null;
	this->mAutoDelete = _false;
}

} // namespace EGE