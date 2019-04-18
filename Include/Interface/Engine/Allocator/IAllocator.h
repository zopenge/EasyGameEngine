#pragma once

namespace EGE {

/// <summary>
/// The allocator.
/// </summary>
class IAllocator : public IObject {
public:
	//!	Cleanup pages.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _void Cleanup() PURE;

	//!	Get the arrange size in bytes.
	//!	@param		none.
	//!	@return		The arrange size in bytes.
	virtual _dword GetArrangeSize() const PURE;

	//!	Check whether can allocate by specified size.
	//!	@param		size	The buffer size in bytes.
	//!	@return		True indicates can allocate the buffer by specified size.
	virtual _ubool CanAlloc(_dword size) const PURE;

	//!	Allocate.
	//!	@param		size			The buffer size in bytes.
	//!	@return		The address of allocated memory block.
	virtual _byte* Alloc(_dword size) PURE;
	//!	Allocate and copy buffer data.
	//!	@param		size	The buffer size in bytes.
	//!	@param		buffer	The buffer data.
	//!	@return		The address of allocated memory block.
	virtual _byte* Alloc(_dword size, const _byte* buffer) PURE;
	//!	Reallocate.
	//!	@param		pointer	The original buffer pointer.
	//!	@param		size	The new buffer size in bytes.
	//!	@return		The address of allocated memory block.
	virtual _byte* ReAlloc(_void* pointer, _dword size) PURE;
	//!	Reallocate.
	//!	@param		pointer	The original buffer pointer.
	//!	@param		size	The new buffer size in bytes.
	//!	@param		buffer	The buffer data.
	//!	@return		The address of allocated memory block.
	virtual _byte* ReAlloc(_void* pointer, _dword size, const _byte* buffer) PURE;
	//!	Free.
	//!	@param		pointer	The address of allocated memory block.
	//!	@return		none.
	virtual _void Free(_void* pointer) PURE;
	//!	Free all allocated buffers.
	//!	@param		none.
	//!	@return		none.
	virtual _void FreeAll() PURE;
};

/// <summary>
/// The class to allocate and auto free in function.
/// </summary>
template <typename Type>
struct AllocatedOwner {
	IAllocatorRef mAllocator;
	Type* mBuffer;

	operator Type*() {
		return mBuffer;
	}
	operator const Type*() const {
		return mBuffer;
	}

	AllocatedOwner(_dword size, IAllocator* allocator) {
		EGE_ASSERT(size != 0);
		EGE_ASSERT(allocator != 0);

		mAllocator = allocator;
		mBuffer = (Type*)allocator->Alloc(size);
		EGE_ASSERT(mBuffer != _null);
	}
	~AllocatedOwner() {
		mAllocator->Free(mBuffer);
	}
};

} // namespace EGE