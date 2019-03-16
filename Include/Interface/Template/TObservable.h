//! @file     TObservable.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TObservable
//----------------------------------------------------------------------------

template< typename Type >
class TObservable : public Type
{
protected:
	typedef Array< IObserverRef > ObserverArray;

protected:
	//!	The observers
	ObserverArray	mObservers;

protected:
	TObservable( IObserver* observer = _null );
	virtual ~TObservable( );

// IObservable Interface
public:
	virtual _void 	RegisterObserver( IObserver* observer ) override;
	virtual _void 	UnregisterObserver( IObserver* observer ) override;

	virtual _void	NotifyObservers( const IObservable* generator, const EventBase& event ) override;
};

//----------------------------------------------------------------------------
// TObservable Implementation
//----------------------------------------------------------------------------

template< typename Type >
TObservable< Type >::TObservable( IObserver* observer )
{
	RegisterObserver( observer );
}

template< typename Type >
TObservable< Type >::~TObservable( )
{
}

template< typename Type >
_void TObservable< Type >::RegisterObserver( IObserver* observer )
{
	if ( observer == _null )
		return;

	// Skip the duplicate observer
	if ( mObservers.Search( observer ).IsValid( ) )
		return;

	mObservers.Append( observer );
}

template< typename Type >
void TObservable< Type >::UnregisterObserver( IObserver* observer )
{
	if ( observer == _null )
		return;

	for ( _dword i = 0; i < mObservers.Number( ); i ++ )
	{
		if ( mObservers[i] == observer )
		{
			mObservers.RemoveByIndex( i );
			return;
		}
	}
}

template< typename Type >
_void TObservable< Type >::NotifyObservers( const IObservable* generator, const EventBase& event )
{
	for ( _dword i = 0; i < mObservers.Number( ); i ++ )
		mObservers[i]->Notify( event, this, generator );
}

}