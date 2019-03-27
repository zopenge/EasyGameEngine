#pragma once

namespace EGE {

/// <summary>
///	The safe value to prevent HACKER to change value in memory.
/// </summary>
template <typename ToValueType, typename FromValueType, typename CodeType = _dword>
class SafeValue {
public:
	typedef ToValueType SafeValueToValueType;
	typedef FromValueType SafeValueFromValueType;
	typedef CodeType SafeValueCodeType;

private:
	CodeType mCode;
	CodeType* mValue;

#ifdef _DEBUG
	ToValueType mDebugValue;
#endif

public:
	SafeValue();
	explicit SafeValue(const FromValueType& value);
	SafeValue(const CodeType& code, const FromValueType& value);
	~SafeValue();
	//private:
	SafeValue(const SafeValue<ToValueType, FromValueType, CodeType>& value);

public:
	_void SetCode(const CodeType& code);
	_void SetValue(const FromValueType& value);
	CodeType GetCode() const;
	ToValueType GetValue() const;

	operator ToValueType() const;
	SafeValue& operator=(const FromValueType& value);
	SafeValue& operator=(const SafeValue<ToValueType, FromValueType, CodeType>& value);

	SafeValue& operator+=(const FromValueType& value);
	SafeValue& operator-=(const FromValueType& value);
	SafeValue& operator*=(const FromValueType& value);
	SafeValue& operator/=(const FromValueType& value);
};

template <typename ToValueType, typename FromValueType, typename CodeType>
SafeValue<ToValueType, FromValueType, CodeType>::SafeValue()
    : mCode((CodeType)rand()), mValue(_null) {
	mValue = new CodeType;
	*mValue = 0;
	*mValue = *mValue ^ mCode;
#ifdef _DEBUG
	mDebugValue = 0;
#endif
}

template <typename ToValueType, typename FromValueType, typename CodeType>
SafeValue<ToValueType, FromValueType, CodeType>::SafeValue(const FromValueType& value)
    : mCode((CodeType)rand()), mValue(_null) {
	mValue = new CodeType;
	*mValue = *((CodeType*)(&value));
	*mValue = *mValue ^ mCode;
#ifdef _DEBUG
	mDebugValue = value;
#endif
}

template <typename ToValueType, typename FromValueType, typename CodeType>
SafeValue<ToValueType, FromValueType, CodeType>::SafeValue(const CodeType& code, const FromValueType& value)
    : mCode(code), mValue(_null) {
	mValue = new CodeType;
	*mValue = *((CodeType*)(&value));
	*mValue = *mValue ^ mCode;
#ifdef _DEBUG
	mDebugValue = value;
#endif
}

template <typename ToValueType, typename FromValueType, typename CodeType>
SafeValue<ToValueType, FromValueType, CodeType>::SafeValue(const SafeValue<ToValueType, FromValueType, CodeType>& value)
    : mCode(value.mCode), mValue(_null) {
	mValue = new CodeType;
	*mValue = *(value.mValue);
#ifdef _DEBUG
	mDebugValue = (ToValueType)(value);
#endif
}

template <typename ToValueType, typename FromValueType, typename CodeType>
SafeValue<ToValueType, FromValueType, CodeType>::~SafeValue() {
	EGE_DELETE(mValue);
}

template <typename ToValueType, typename FromValueType, typename CodeType>
SafeValue<ToValueType, FromValueType, CodeType>::operator ToValueType() const {
	CodeType value = *mValue ^ mCode;
	ToValueType result = *((ToValueType*)(&value));
	return result;
}

template <typename ToValueType, typename FromValueType, typename CodeType>
SafeValue<ToValueType, FromValueType, CodeType>& SafeValue<ToValueType, FromValueType, CodeType>::operator=(const FromValueType& value) {
	CodeType new_value = *((CodeType*)&value) ^ mCode;
	if (*mValue == new_value)
		return *this;

	CodeType* old_value = mValue;
	mValue = new CodeType;
	EGE_DELETE(old_value);
	*mValue = new_value;
#ifdef _DEBUG
	mDebugValue = value;
#endif
	return *this;
}

template <typename ToValueType, typename FromValueType, typename CodeType>
SafeValue<ToValueType, FromValueType, CodeType>& SafeValue<ToValueType, FromValueType, CodeType>::operator=(const SafeValue<ToValueType, FromValueType, CodeType>& value) {
	*this = (ToValueType)value;
	return *this;
}

template <typename ToValueType, typename FromValueType, typename CodeType>
_void SafeValue<ToValueType, FromValueType, CodeType>::SetCode(const CodeType& code) {
	ToValueType backup = *this;
	mCode = code;
	*this = backup;
}

template <typename ToValueType, typename FromValueType, typename CodeType>
_void SafeValue<ToValueType, FromValueType, CodeType>::SetValue(const FromValueType& value) {
	*this = value;
}

template <typename ToValueType, typename FromValueType, typename CodeType>
CodeType SafeValue<ToValueType, FromValueType, CodeType>::GetCode() const {
	return mCode;
}

template <typename ToValueType, typename FromValueType, typename CodeType>
ToValueType SafeValue<ToValueType, FromValueType, CodeType>::GetValue() const {
	return *this;
}

template <typename ToValueType, typename FromValueType, typename CodeType>
SafeValue<ToValueType, FromValueType, CodeType>& SafeValue<ToValueType, FromValueType, CodeType>::operator+=(const FromValueType& value) {
	*this = ((ToValueType)(*this) + value);
	return *this;
}

template <typename ToValueType, typename FromValueType, typename CodeType>
SafeValue<ToValueType, FromValueType, CodeType>& SafeValue<ToValueType, FromValueType, CodeType>::operator-=(const FromValueType& value) {
	*this = ((ToValueType)(*this) - value);
	return *this;
}

template <typename ToValueType, typename FromValueType, typename CodeType>
SafeValue<ToValueType, FromValueType, CodeType>& SafeValue<ToValueType, FromValueType, CodeType>::operator*=(const FromValueType& value) {
	*this = ((ToValueType)(*this) * value);
	return *this;
}

template <typename ToValueType, typename FromValueType, typename CodeType>
SafeValue<ToValueType, FromValueType, CodeType>& SafeValue<ToValueType, FromValueType, CodeType>::operator/=(const FromValueType& value) {
	*this = ((ToValueType)(*this) / value);
	return *this;
}

} // namespace EGE
