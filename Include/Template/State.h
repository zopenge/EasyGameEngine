//! @file     State.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// State
//----------------------------------------------------------------------------

template< typename Type >
class State
{
protected:
	//!	The previous state
	Type	mPrevState;
	//!	The current state
	Type	mCurrentState;

protected:
	State( );

public:
	//!	Get the previous state.
	Type GetPrevState( ) const;
	//!	Get the current state.
	Type GetCurrentState( ) const;
	//!	Get the previous state.
	Type& GetPrevStateRef( );
	//!	Get the current state.
	Type& GetCurrentStateRef( );
	//!	Get the previous state.
	const Type& GetPrevStateRef( ) const;
	//!	Get the current state.
	const Type& GetCurrentStateRef( ) const;

	//!	Set the current state.
	_void SetCurrentState( Type state );
	//!	Set the current state.
	_void SetCurrentStateRef( const Type& state );
};

//----------------------------------------------------------------------------
// State Implementation
//----------------------------------------------------------------------------

template< typename Type >
State< Type >::State( )
{
	mPrevState		= 0;
	mCurrentState	= 0;
}

template< typename Type >
Type State< Type >::GetPrevState( ) const
{
	return mPrevState;
}

template< typename Type >
Type State< Type >::GetCurrentState( ) const
{
	return mCurrentState;
}

template< typename Type >
Type& State< Type >::GetPrevStateRef( )
{
	return mPrevState;
}

template< typename Type >
Type& State< Type >::GetCurrentStateRef( )
{
	return mCurrentState;
}

template< typename Type >
const Type& State< Type >::GetPrevStateRef( ) const
{
	return mPrevState;
}

template< typename Type >
const Type& State< Type >::GetCurrentStateRef( ) const
{
	return mCurrentState;
}

template< typename Type >
_void State< Type >::SetCurrentState( Type state )
{
	mPrevState		= mCurrentState;
	mCurrentState	= state;
}

template< typename Type >
_void State< Type >::SetCurrentStateRef( const Type& state )
{
	mPrevState		= mCurrentState;
	mCurrentState	= state;
}

}