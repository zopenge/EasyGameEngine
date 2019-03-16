//! @file     IObservable.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IObservable
//----------------------------------------------------------------------------

class IObservable : public IObject
{
public:
	//!	Register observer.
	//!	@param		observer	The observer.
	//!	@return		none.
	virtual _void RegisterObserver( IObserver* observer ) PURE;
	//!	Unregister observer.
	//!	@param		observer	The observer.
	//!	@return		none.
	virtual _void UnregisterObserver( IObserver* observer ) PURE;

	//!	Notify all observers.
	//!	@param		generator	The event generator.
	//!	@param		event		The event info.
	//!	@return		none.
	virtual _void NotifyObservers( const IObservable* generator, const EventBase& event ) PURE;
};

}