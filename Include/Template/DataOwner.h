#pragma once

namespace EGE {

/// <summary>
///	The reference keeper to restore value when end lifetime.
/// </summary>
template <typename Type>
class DataOwner {
private:
	Type& mDataRef;
	Type mDataCopy;

public:
	DataOwner(Type& data);
	~DataOwner();
};

template <typename Type>
DataOwner<Type>::DataOwner(Type& data)
    : mDataRef(data), mDataCopy(data) {
}

template <typename Type>
DataOwner<Type>::~DataOwner() {
	mDataRef = mDataCopy;
}

} // namespace EGE