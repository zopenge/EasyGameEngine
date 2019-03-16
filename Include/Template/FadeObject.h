//! @file     FadeObject.h
//! @author   foreven
//! @version  1.0
//! @date     2013.08.07
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FadeObject
//----------------------------------------------------------------------------

template< typename Type >
class FadeObject
{
private:
	Type	mFadeObject;
	_qword	mFadeUserData;
	_dword	mFadeTick;
	_dword	mFadeTime;
	_ubool	mFadeIn;

public:
	FadeObject( );
	~FadeObject( );

public:
	//!	Get the fade object.
	//!	@param		none.
	//!	@return		The fade object.
	Type& GetFadeObject( );
	//!	Get the fade object.
	//!	@param		none.
	//!	@return		The fade object.
	const Type& GetFadeObject( ) const;

	//!	Set the fade user data.
	//!	@param		user_data	The fade user data.
	//!	@return		none.
	_void SetFadeUserData( _qword user_data );
	//!	Get the fade user data.
	//!	@param		none.
	//!	@return		The fade user data.
	_qword GetFadeUserData( ) const;

	//!	Get the fade tick.
	//!	@param		none.
	//!	@return		The fade tick in milliseconds.
	_dword GetFadeTick( ) const;
	//!	Set the fade tick.
	//!	@param		tick		The fade tick in milliseconds.
	//!	@return		none.
	_void SetFadeTick( _dword tick );

	//!	Get the fade time.
	//!	@param		none.
	//!	@return		The fade time in milliseconds.
	_dword GetFadeTime( ) const;
	//!	Set the fade time.
	//!	@param		time	The fade time in milliseconds.
	//!	@return		none.
	_void SetFadeTime( _dword time );

	//!	Get the fade alpha in [0.0, 1.0].
	//!	@param		none.
	//!	@return		The fade alpha.
	_float GetFadeAlpha( ) const;

	//!	Check whether it's fade in.
	//!	@param		none.
	//!	@return		True indicates it's fade in.
	_ubool IsFadeIn( ) const;
	//!	Check whether it's fade out.
	//!	@param		none.
	//!	@return		True indicates it's fade out.
	_ubool IsFadeOut( ) const;
	//!	Check whether it finished.
	//!	@param		none.
	//!	@return		True indicates it finished the fade procession.
	_ubool IsFinished( ) const;

	//!	Fade in.
	//!	@param		object		The fade object.
	//!	@param		duration	The fade duration in milliseconds.
	//!	@param		user_data	The fade user data.
	//!	@return		none.
	_void FadeIn( const Type& object, _dword duration, _qword user_data = 0 );
	//!	Fade out.
	//!	@param		object		The fade object.
	//!	@param		duration	The fade duration in milliseconds.
	//!	@param		user_data	The fade user data.
	//!	@return		none.
	_void FadeOut( const Type& object, _dword duration, _qword user_data = 0 );

	//!	Clear.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );

	//!	Update.
	//!	@param		elapse		The elapse time in milliseconds.
	//!	@return		none.
	_void Tick( _dword elapse );
};

//----------------------------------------------------------------------------
// FadeObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
FadeObject< Type >::FadeObject( )
	: mFadeObject( (Type) 0 )
	, mFadeUserData( 0 )
	, mFadeTick( 0 )
	, mFadeTime( 0 )
	, mFadeIn( _false )
{
}

template< typename Type >
FadeObject< Type >::~FadeObject( )
{
}

template< typename Type >
Type& FadeObject< Type >::GetFadeObject( )
{
	return mFadeObject;
}

template< typename Type >
const Type& FadeObject< Type >::GetFadeObject( ) const
{
	return mFadeObject;
}

template< typename Type >
_void FadeObject< Type >::SetFadeUserData( _qword user_data )
{
	mFadeUserData = user_data;
}

template< typename Type >
_qword FadeObject< Type >::GetFadeUserData( ) const
{
	return mFadeUserData;
}

template< typename Type >
_dword FadeObject< Type >::GetFadeTick( ) const
{
	return mFadeTick;
}

template< typename Type >
_void FadeObject< Type >::SetFadeTick( _dword tick )
{
	mFadeTick = tick;
}

template< typename Type >
_dword FadeObject< Type >::GetFadeTime( ) const
{
	return mFadeTime;
}

template< typename Type >
_void FadeObject< Type >::SetFadeTime( _dword time )
{
	mFadeTime = time;
}

template< typename Type >
_float FadeObject< Type >::GetFadeAlpha( ) const
{
	if ( mFadeTime == 0 )
		return 0.0f;

	_float alpha = (_float)mFadeTick / (_float)mFadeTime;
	alpha = Math::Clamp( alpha, 0.0f, 1.0f );
	if ( mFadeIn )
		return alpha;

	return 1.0f - alpha;
}

template< typename Type >
_ubool FadeObject< Type >::IsFadeIn( ) const
{
	return mFadeIn;
}

template< typename Type >
_ubool FadeObject< Type >::IsFadeOut( ) const
{
	return EGE_BOOLEAN( !mFadeIn );
}

template< typename Type >
_ubool FadeObject< Type >::IsFinished( ) const
{
	if ( mFadeTick >= mFadeTime )
		return _true;

	return _false;
}

template< typename Type >
_void FadeObject< Type >::FadeIn( const Type& object, _dword duration, _qword user_data )
{
	mFadeIn			= _true;
	mFadeObject		= object;
	mFadeUserData	= user_data;
	mFadeTick		= 0;
	mFadeTime		= duration;
}

template< typename Type >
_void FadeObject< Type >::FadeOut( const Type& object, _dword duration, _qword user_data )
{
	mFadeIn			= _false;
	mFadeObject		= object;
	mFadeUserData	= user_data;
	mFadeTick		= 0;
	mFadeTime		= duration;
}

template< typename Type >
_void FadeObject< Type >::Clear( )
{
	mFadeIn			= _false;
	mFadeObject		= (Type) 0;
	mFadeUserData	= 0;
	mFadeTime		= 0;
	mFadeTick		= 0;
}

template< typename Type >
_void FadeObject< Type >::Tick( _dword elapse )
{
	mFadeTick = Math::Min( mFadeTick + elapse, mFadeTime );
}

}