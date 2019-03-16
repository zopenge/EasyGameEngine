//! @file     SyncObject.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// EventObject
//----------------------------------------------------------------------------

//! This class represents a event object, used for threads synchronization in system.

//! An event object is a synchronization object whose state can be explicitly set to signaled
//! by use of the SetEvent function. Following are the two types of event object.
class EventObject : public KernelObject
{
public:
	//! Create a event object with or without a name, if it is already existed then copy the object handle.
	//! @param		manualreset		Whether the event object is manual-reset or auto-reset.
	//! @param		initialstate	The initial state of the event object, true means signaled.
	//! @return		True indicates success, false indicates failure.
	_ubool Create( _ubool manualreset, _ubool initialstate );

	//! Test if the event object is signaled.
	//! @param		none
	//! @return		True indicates signaled, false indicates not signaled.
	_ubool IsSignaled( ) const;

	//! Wait for the object when it is signaled, and obtains the ownership.
	//! @param		milliseconds	Time-out interval in milliseconds, -1 indicates wait forever.
	//! @return		True if the object is signaled before time out, false otherwise.
	_ubool Wait( _dword milliseconds = -1 );

	//! Set the state of the event object to signaled.
	//! @param		none
	//! @return		True indicates success, false indicates failure.
	_ubool Set( );
	//! Set the state of the event object to nonsignaled.
	//! @param		none
	//! @return		True indicates success, false indicates failure.
	_ubool Reset( );

	//! Clone.
	//! @param		none.
	//! @return		The cloned event.
	EventObject* Clone( ) const;
};

}