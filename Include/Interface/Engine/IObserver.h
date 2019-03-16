//! @file     IObserver.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IObserver
//----------------------------------------------------------------------------

class IObserver : public IObservable
{
public:
	//!	Check whether listen to specified event or not.
	//!	@param		event_id	The event ID.
	//!	@return		True indicates it has listen to the specified event already.
	virtual _ubool IsListenTo( _dword event_id ) const PURE;
	//!	Listen to the specified event.
	//!	@param		event_id	The event ID.
	//!	@return		none.
	virtual _void Listen( _dword event_id ) PURE;

	//!	Notify the observer when listened event has been signaled.
	//!	@param		event		The event info.
	//!	@param		object		The observable object what passed this event.
	//!	@param		generator	The event generator.
	//!	@return		none.
	virtual _void Notify( const EventBase& event, const IObject* object, const IObservable* generator ) PURE;
};

}