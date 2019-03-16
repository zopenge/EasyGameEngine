//! @file     IGUIAppDelegate.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIAppDelegate
//----------------------------------------------------------------------------

class IGUIAppDelegate : public IObject
{
public:
	//!	When initialize finished.
	//!	@param		application	The GUI application.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool OnInitialized( IGUIApplication* application ) PURE;
	//!	When load resource finished.
	//!	@param		application	The GUI application.
	//! @return		True indicates success, false indicates failure.
	virtual _void OnLoaded( IGUIApplication* application ) PURE;
	//!	When update GUI application.
	//!	@param		application	The GUI application.
	//! @param		elapse		The millisecond time of the update interval.
	//! @return		none.
	virtual _void OnTick( IGUIApplication* application, _dword elapse ) PURE;
	//!	When before to finalize.
	//!	@param		application	The GUI application.
	//! @return		none.
	virtual _void OnFinalize( IGUIApplication* application ) PURE;

#ifdef _EGE_CLR_
	//!	Invoke GUI event.
	//!	@param		object		The GUI object will receive this event.
	//!	@param		event		The GUI event.
	//! @return		True indicates this event has been handled.
	virtual _ubool Invoke( IGUIObject* object, const EventBase& event ) PURE;
#endif
};

}