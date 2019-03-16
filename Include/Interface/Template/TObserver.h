//! @file     TObserver.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TObserver
//----------------------------------------------------------------------------

template< typename Type >
class TObserver : public Type
{
protected:
	typedef Array< _dword > EventIDArray;

protected:
	//!	The listened event ID array
	EventIDArray	mListenedEventIDArray;

protected:
	TObserver( );
	virtual ~TObserver( );
	
// IObserver Interface
public:
	virtual _ubool 	IsListenTo( _dword event_id ) const override;
	virtual _void 	Listen( _dword event_id ) override;

	virtual _void 	Notify( const EventBase& event, const IObject* object, const IObservable* generator ) override;
};

//----------------------------------------------------------------------------
// TObserver Implementation
//----------------------------------------------------------------------------

template< typename Type >
TObserver< Type >::TObserver( )
{
}

template< typename Type >
TObserver< Type >::~TObserver( )
{
}

template< typename Type >
_ubool TObserver< Type >::IsListenTo( _dword event_id ) const
{
	return mListenedEventIDArray.SearchAscending( event_id ).IsValid( );
}

template< typename Type >
_void TObserver< Type >::Listen( _dword event_id )
{
	mListenedEventIDArray.InsertAscending( event_id );
}

template< typename Type >
_void TObserver< Type >::Notify( const EventBase& event, const IObject* object, const IObservable* generator )
{

}

}