//! @file     CallbackFunc.h
//! @author   LiCode
//! @version  1.0.0.702
//! @date     2011/02/15
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// CallbackFunc
//----------------------------------------------------------------------------

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
class CallbackFunc {
private:
	//!	The function pointer
	FuncDecl mFuncPointer;
	//!	The Params
	ParamsType mParams;

public:
	CallbackFunc();

public:
	//!	Check whether is valid.
	_ubool IsValid() const;
	//!	Check whether is null.
	_ubool IsNull() const;
	//!	Get the function pointer.
	FuncDecl GetFuncPointer() const;
	//!	Get the Params.
	const ParamsType& GetParams() const;

	//!	Initialize callback function.
	_void Init(FuncDecl funcpointer, const ParamsType& Params);
	//!	Clear.
	_void Clear();

	//!	Invoke callback function by return nothing without Params.
	_void Invoke() const;
	_void Invoke();

	//!	Invoke callback function by return nothing.
	template <typename T1>
	_void Invoke(T1& arg1) const;
	template <typename T1, typename T2>
	_void Invoke(T1& arg1, T2& arg2) const;
	template <typename T1, typename T2, typename T3>
	_void Invoke(T1& arg1, T2& arg2, T3& arg3) const;
	template <typename T1, typename T2, typename T3, typename T4>
	_void Invoke(T1& arg1, T2& arg2, T3& arg3, T4& arg4) const;
	template <typename T1, typename T2, typename T3, typename T4, typename T5>
	_void Invoke(T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5) const;
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	_void Invoke(T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6) const;
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	_void Invoke(T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6, T7& arg7) const;

	//!	Invoke callback function by return nothing (CONST).
	template <typename T1>
	_void Invoke(const T1& arg1) const;
	template <typename T1, typename T2>
	_void Invoke(const T1& arg1, const T2& arg2) const;
	template <typename T1, typename T2, typename T3>
	_void Invoke(const T1& arg1, const T2& arg2, const T3& arg3) const;
	template <typename T1, typename T2, typename T3, typename T4>
	_void Invoke(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4) const;
	template <typename T1, typename T2, typename T3, typename T4, typename T5>
	_void Invoke(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5) const;
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	_void Invoke(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6) const;
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	_void Invoke(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7) const;

	//!	Invoke callback function by return something without Params.
	FuncReturnType InvokeR();
	FuncReturnType InvokeR() const;

	//!	Invoke callback function by return something.
	template <typename T1>
	FuncReturnType InvokeR(T1& arg1) const;
	template <typename T1, typename T2>
	FuncReturnType InvokeR(T1& arg1, T2& arg2) const;
	template <typename T1, typename T2, typename T3>
	FuncReturnType InvokeR(T1& arg1, T2& arg2, T3& arg3) const;
	template <typename T1, typename T2, typename T3, typename T4>
	FuncReturnType InvokeR(T1& arg1, T2& arg2, T3& arg3, T4& arg4) const;
	template <typename T1, typename T2, typename T3, typename T4, typename T5>
	FuncReturnType InvokeR(T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5) const;
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	FuncReturnType InvokeR(T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6) const;
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	FuncReturnType InvokeR(T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6, T7& arg7) const;

	//!	Invoke callback function by return something (CONST).
	template <typename T1>
	FuncReturnType InvokeR(const T1& arg1) const;
	template <typename T1, typename T2>
	FuncReturnType InvokeR(const T1& arg1, const T2& arg2) const;
	template <typename T1, typename T2, typename T3>
	FuncReturnType InvokeR(const T1& arg1, const T2& arg2, const T3& arg3) const;
	template <typename T1, typename T2, typename T3, typename T4>
	FuncReturnType InvokeR(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4) const;
	template <typename T1, typename T2, typename T3, typename T4, typename T5>
	FuncReturnType InvokeR(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5) const;
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	FuncReturnType InvokeR(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6) const;
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	FuncReturnType InvokeR(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7) const;
};

//----------------------------------------------------------------------------
// CallbackFunc Implementation
//----------------------------------------------------------------------------

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::CallbackFunc() {
	mFuncPointer = _null;
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
_ubool CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::IsValid() const {
	return mFuncPointer != _null;
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
_ubool CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::IsNull() const {
	return mFuncPointer == _null;
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
FuncDecl CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::GetFuncPointer() const {
	return mFuncPointer;
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
const ParamsType& CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::GetParams() const {
	return mParams;
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Init(FuncDecl funcpointer, const ParamsType& Params) {
	mFuncPointer = funcpointer;
	mParams = Params;
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Clear() {
	mFuncPointer = _null;
	mParams = ParamsType::cNull;
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke() {
	if (mFuncPointer != _null)
		(*mFuncPointer)(mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke() const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(T1& arg1) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(T1& arg1, T2& arg2) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, arg2, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(T1& arg1, T2& arg2, T3& arg3) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, arg2, arg3, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(T1& arg1, T2& arg2, T3& arg3, T4& arg4) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, arg2, arg3, arg4, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4, typename T5>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, arg2, arg3, arg4, arg5, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, arg2, arg3, arg4, arg5, arg6, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6, T7& arg7) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(const T1& arg1) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(const T1& arg1, const T2& arg2) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, arg2, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(const T1& arg1, const T2& arg2, const T3& arg3) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, arg2, arg3, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, arg2, arg3, arg4, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4, typename T5>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, arg2, arg3, arg4, arg5, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, arg2, arg3, arg4, arg5, arg6, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
_void CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::Invoke(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7) const {
	if (mFuncPointer != _null)
		(*mFuncPointer)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR() {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR() const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(T1& arg1) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(T1& arg1, T2& arg2) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, arg2, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(T1& arg1, T2& arg2, T3& arg3) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, arg2, arg3, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(T1& arg1, T2& arg2, T3& arg3, T4& arg4) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, arg2, arg3, arg4, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4, typename T5>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, arg2, arg3, arg4, arg5, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, arg2, arg3, arg4, arg5, arg6, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6, T7& arg7) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(const T1& arg1) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(const T1& arg1, const T2& arg2) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, arg2, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(const T1& arg1, const T2& arg2, const T3& arg3) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, arg2, arg3, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, arg2, arg3, arg4, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4, typename T5>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, arg2, arg3, arg4, arg5, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, arg2, arg3, arg4, arg5, arg6, mParams);
}

template <typename FuncDecl, typename FuncReturnType, class ParamsType>
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
FuncReturnType CallbackFunc<FuncDecl, FuncReturnType, ParamsType>::InvokeR(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7) const {
	EGE_ASSERT(mFuncPointer != _null);

	return (*mFuncPointer)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, mParams);
}

} // namespace EGE
