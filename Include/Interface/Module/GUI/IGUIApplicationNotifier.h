//! @file     IGUIApplicationNotifier.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIApplicationNotifier
//----------------------------------------------------------------------------

class IGUIApplicationNotifier : public IObject
{
public:
	//!	When GUI application after loaded.
	//!	@param		application	The GUI application.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool OnAfterLoad( IGUIApplication* application ) PURE;
	//!	When GUI application before unload.
	//!	@param		application	The GUI application.
	//! @return		none.
	virtual _void OnBeforeUnload( IGUIApplication* application ) PURE;

	//!	When handle GUI event.
	//!	@remark		Some GUI event do not handled by any GUI controls, so the user can handle it in this interface.
	//!	@param		application	The GUI application.
	//! @param		event		The GUI event.
	//!	@param		flags		The GUI event flags.
	//!	@return		True indicates this event has been handled.
	virtual _ubool OnHandleEvent( IGUIApplication* application, const EventBase& event, const FlagsObject& flags ) PURE;
};

}