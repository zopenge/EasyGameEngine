//! @file     CallbackFunc.h
//! @author   LiCode
//! @version  1.0.0.702
//! @date     2011/02/15
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// CallbackFunc
//----------------------------------------------------------------------------

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
class CallbackFunc
{
private:
	//!	The function pointer
	FuncDecl		mFuncPointer;
	//!	The parameters
	ParametersType	mParameters;

public:
	CallbackFunc( );

public:
	//!	Check whether is valid.
	_ubool IsValid( ) const;
	//!	Check whether is null.
	_ubool IsNull( ) const;
	//!	Get the function pointer.
	FuncDecl GetFuncPointer( ) const;
	//!	Get the parameters.
	const ParametersType& GetParameters( ) const;
	
	//!	Initialize callback function.
	_void Init( FuncDecl funcpointer, const ParametersType& parameters );
	//!	Clear.
	_void Clear( );

	//!	Invoke callback function by return nothing without parameters.
	_void Invoke( ) const;
	_void Invoke( );

	//!	Invoke callback function by return nothing.
	template< typename T1 >
	_void Invoke( T1& arg1 ) const;
	template< typename T1, typename T2 >
	_void Invoke( T1& arg1, T2& arg2 ) const;
	template< typename T1, typename T2, typename T3 >
	_void Invoke( T1& arg1, T2& arg2, T3& arg3 ) const;
	template< typename T1, typename T2, typename T3, typename T4 >
	_void Invoke( T1& arg1, T2& arg2, T3& arg3, T4& arg4 ) const;
	template< typename T1, typename T2, typename T3, typename T4, typename T5 >
	_void Invoke( T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5 ) const;
	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
	_void Invoke( T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6 ) const;
	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
	_void Invoke( T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6, T7& arg7 ) const;

	//!	Invoke callback function by return nothing (CONST).
	template< typename T1 >
	_void Invoke( const T1& arg1 ) const;
	template< typename T1, typename T2 >
	_void Invoke( const T1& arg1, const T2& arg2 ) const;
	template< typename T1, typename T2, typename T3 >
	_void Invoke( const T1& arg1, const T2& arg2, const T3& arg3 ) const;
	template< typename T1, typename T2, typename T3, typename T4 >
	_void Invoke( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4 ) const;
	template< typename T1, typename T2, typename T3, typename T4, typename T5 >
	_void Invoke( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5 ) const;
	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
	_void Invoke( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6 ) const;
	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
	_void Invoke( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7 ) const;

	//!	Invoke callback function by return something without parameters.
	FuncReturnType InvokeR( );
	FuncReturnType InvokeR( ) const;

	//!	Invoke callback function by return something.
	template< typename T1 >
	FuncReturnType InvokeR( T1& arg1 ) const;
	template< typename T1, typename T2 >
	FuncReturnType InvokeR( T1& arg1, T2& arg2 ) const;
	template< typename T1, typename T2, typename T3 >
	FuncReturnType InvokeR( T1& arg1, T2& arg2, T3& arg3 ) const;
	template< typename T1, typename T2, typename T3, typename T4 >
	FuncReturnType InvokeR( T1& arg1, T2& arg2, T3& arg3, T4& arg4 ) const;
	template< typename T1, typename T2, typename T3, typename T4, typename T5 >
	FuncReturnType InvokeR( T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5 ) const;
	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
	FuncReturnType InvokeR( T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6 ) const;
	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
	FuncReturnType InvokeR( T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6, T7& arg7 ) const;

	//!	Invoke callback function by return something (CONST).
	template< typename T1 >
	FuncReturnType InvokeR( const T1& arg1 ) const;
	template< typename T1, typename T2 >
	FuncReturnType InvokeR( const T1& arg1, const T2& arg2 ) const;
	template< typename T1, typename T2, typename T3 >
	FuncReturnType InvokeR( const T1& arg1, const T2& arg2, const T3& arg3 ) const;
	template< typename T1, typename T2, typename T3, typename T4 >
	FuncReturnType InvokeR( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4 ) const;
	template< typename T1, typename T2, typename T3, typename T4, typename T5 >
	FuncReturnType InvokeR( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5 ) const;
	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
	FuncReturnType InvokeR( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6 ) const;
	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
	FuncReturnType InvokeR( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7 ) const;
};

//----------------------------------------------------------------------------
// CallbackFunc Implementation
//----------------------------------------------------------------------------

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::CallbackFunc( )
{
	mFuncPointer = _null;
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
_ubool CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::IsValid( ) const
{
	return mFuncPointer != _null;
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
_ubool CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::IsNull( ) const
{
	return mFuncPointer == _null;
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
FuncDecl CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::GetFuncPointer( ) const
{
	return mFuncPointer;
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
const ParametersType& CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::GetParameters( ) const
{
	return mParameters;
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Init( FuncDecl funcpointer, const ParametersType& parameters )
{
	mFuncPointer	= funcpointer;
	mParameters		= parameters;
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Clear( )
{
	mFuncPointer	= _null;
	mParameters		= ParametersType::cNull;
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( )
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( T1& arg1 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( T1& arg1, T2& arg2 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, arg2, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( T1& arg1, T2& arg2, T3& arg3 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, arg2, arg3, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( T1& arg1, T2& arg2, T3& arg3, T4& arg4 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, arg2, arg3, arg4, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4, typename T5 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, arg2, arg3, arg4, arg5, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, arg2, arg3, arg4, arg5, arg6, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6, T7& arg7 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, arg2, arg3, arg4, arg5, arg6, arg7, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( const T1& arg1 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( const T1& arg1, const T2& arg2 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, arg2, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( const T1& arg1, const T2& arg2, const T3& arg3 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, arg2, arg3, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, arg2, arg3, arg4, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4, typename T5 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, arg2, arg3, arg4, arg5, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, arg2, arg3, arg4, arg5, arg6, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
_void CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::Invoke( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7 ) const
{
	if ( mFuncPointer != _null )
		(*mFuncPointer)( arg1, arg2, arg3, arg4, arg5, arg6, arg7, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( )
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( T1& arg1 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( T1& arg1, T2& arg2 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, arg2, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( T1& arg1, T2& arg2, T3& arg3 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, arg2, arg3, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( T1& arg1, T2& arg2, T3& arg3, T4& arg4 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, arg2, arg3, arg4, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4, typename T5 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, arg2, arg3, arg4, arg5, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, arg2, arg3, arg4, arg5, arg6, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5, T6& arg6, T7& arg7 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, arg2, arg3, arg4, arg5, arg6, arg7, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( const T1& arg1 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( const T1& arg1, const T2& arg2 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, arg2, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( const T1& arg1, const T2& arg2, const T3& arg3 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, arg2, arg3, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, arg2, arg3, arg4, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4, typename T5 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, arg2, arg3, arg4, arg5, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, arg2, arg3, arg4, arg5, arg6, mParameters );
}

template< typename FuncDecl, typename FuncReturnType, class ParametersType >
template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
FuncReturnType CallbackFunc< FuncDecl, FuncReturnType, ParametersType >::InvokeR( const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5, const T6& arg6, const T7& arg7 ) const
{
	EGE_ASSERT( mFuncPointer != _null );

	return (*mFuncPointer)( arg1, arg2, arg3, arg4, arg5, arg6, arg7, mParameters );
}

}
