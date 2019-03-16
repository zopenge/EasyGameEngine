//! @file     IGarbageCollector.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGarbageCollector
//----------------------------------------------------------------------------

class IGarbageCollector : public IObject
{
public:
	//!	Enable/Disable.
	//!	@param		enable		True indicates enable it, false indicates disable it.
	//!	@return		none.
	virtual _void Enable( _ubool enable ) PURE;
	//!	Check whether has enable.
	//!	@param		none.
	//!	@return		True indicates enable it, false indicates disable it.
	virtual _ubool IsEnabled( ) const PURE;

	//!	Cleanup.
	//!	@param		timeout		The time out in milliseconds.
	//!	@return		none.
	virtual _void Cleanup( _dword timeout ) PURE;
	//!	Set the maximal time of GC cleanup in milliseconds.
	//!	@param		time		The time in milliseconds, -1 indicates unlimited.
	//!	@return		none.
	virtual _void SetCleanupMaxTime( _dword time ) PURE;

	//!	Add object.
	//!	@param		object		The object.
	//!	@return		none.
	virtual _void AddObject( IObject* object ) PURE;
};

}