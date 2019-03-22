//! @file     DataOwner.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// DataOwner
//----------------------------------------------------------------------------

template <typename Type>
class DataOwner {
private:
	Type& mDataRef;
	Type mDataCopy;

public:
	DataOwner(Type& data);
	~DataOwner();
};

//----------------------------------------------------------------------------
// DataOwner Implementation
//----------------------------------------------------------------------------

template <typename Type>
DataOwner<Type>::DataOwner(Type& data)
    : mDataRef(data), mDataCopy(data) {
}

template <typename Type>
DataOwner<Type>::~DataOwner() {
	mDataRef = mDataCopy;
}

} // namespace EGE