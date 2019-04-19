#pragma once

namespace EGE {

/// <summary>
/// The stack allocator.
/// </summary>
class IStackAllocator : public IAllocator {
public:
	//!	Get the current offset in bytes.
	//!	@param		none.
	//!	@return		The offset in bytes.
	virtual _dword GetOffset() const PURE;
	//!	Set the current offset in bytes.
	//!	@param		offset		The offset in bytes.
	//!	@return		none.
	virtual _void SetOffset(_dword offset) PURE;

	//!	Get the total size in bytes.
	//!	@param		none.
	//!	@return		The total size in bytes.
	virtual _dword GetStackSize() const PURE;

	//!	Pop size in bytes.
	//!	@param		size		The size in bytes.
	//!	@return		none.
	virtual _void Pop(_dword size) PURE;
};

/// <summary>
/// The class to allocate from stack allocator and auto free in function.
/// </summary>
template <typename Type>
struct StackAllocatedOwner {
	IStackAllocatorRef mAllocator;
	Type* mBuffer;
	_dword mOffset;

	operator Type*() {
		return mBuffer;
	}
	operator const Type*() const {
		return mBuffer;
	}

	StackAllocatedOwner(_dword size, IStackAllocator* allocator) {
		EGE_ASSERT(size != 0);
		EGE_ASSERT(allocator != 0);

		mAllocator = allocator;
		mOffset = allocator->GetOffset();
		mBuffer = (Type*)allocator->Alloc(size);
		EGE_ASSERT(mBuffer != _null);
	}
	~StackAllocatedOwner() {
		mAllocator->SetOffset(mOffset);
	}
};

} // namespace EGE