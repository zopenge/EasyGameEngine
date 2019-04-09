#pragma once

namespace EGE {

/// <summary>
/// The referenced class that auto increase/decrease referenced count.
/// </summary>
template <typename Type>
class RefObject : public Type {
protected:
	_dword mRefCount;

protected:
	RefObject()
	    : mRefCount(1) {
	}
	virtual ~RefObject() {
		EGE_ASSERT(mRefCount == 1);
	}

public:
	virtual _dword GetRefCount() const {
		return mRefCount;
	}
	virtual _dword AddRef() {
		return ++mRefCount;
	}
	virtual _dword Release() {
		if (mRefCount > 1) {
			mRefCount--;
			return mRefCount;
		} else {
			delete this;
			return 0;
		}
	}
};

} // namespace EGE