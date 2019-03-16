//! @file     TEventHooker.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//!	The event hooker template class
template< typename Type, typename EventType >
class TEventHooker : public TObject< IEventHooker >
{
public:
	//! The event hooker function declaration.
	//!	@param		object		The object.
	//!	@param		event		The event.
	//!	@param		parameters	The user defined parameters.
	//!	@return		True indicates skip to pass event to other controls.
	typedef _ubool (Type::*HookerFunc)( IObject* object, const EventType& event, const QwordParameters2& parameters );

private:
	//!	The hooker function pointer
	HookerFunc	mHookerFunc;
	//!	The master of hooker function to process event
	Type*		mMaster;

public:
	TEventHooker( HookerFunc func, Type* master ) 
		: mHookerFunc( func ), mMaster( master ) { }

// IEventHooker Interface
public:
	virtual _ubool Invoke( IObject* object, const EventBase& event, const QwordParameters2& parameters ) const
	{
		EGE_ASSERT( mMaster != _null && mHookerFunc != _null );
		return (mMaster->*mHookerFunc)( object, (const EventType&) event, parameters );
	}
};

}