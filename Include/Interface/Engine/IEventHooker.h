//! @file     IEventHooker.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IEventHooker
//----------------------------------------------------------------------------

//!	The event hooker interface
class IEventHooker : public IObject
{
public:
	//!	Invoke the event.
	virtual _ubool Invoke( IObject* object, const EventBase& event, const QwordParameters2& parameters ) const PURE;
};

//! The event hooker
class EventHooker
{
private:
	//!	The event hooker
	PassRefPtr< IEventHooker > mEventHooker;

public:
	EventHooker( )
	{
	}
	EventHooker( const EventHooker& event_hooker )
	{
		mEventHooker = event_hooker.mEventHooker;
	}

	template< typename Type, typename EventType >
	EventHooker( _ubool (Type::*function)(IObject*, const EventType&, const QwordParameters2&), Type* master )
		: mEventHooker( new TEventHooker<Type, EventType>(function, master) )
	{
	}

public:
	//!	Invoke the hooker function.
	_ubool Invoke( IObject* object, const EventBase& event, const QwordParameters2& parameters ) const
	{
		if ( mEventHooker.IsValid( ) )
			return mEventHooker->Invoke( object, event, parameters );

		return _false;
	}
};

}