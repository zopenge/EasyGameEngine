//! @file     IAppDelegate.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IAppDelegate
//----------------------------------------------------------------------------

class IAppDelegate : public IObserver
{
public:
	//!	When get help info.
	//!	@param		none.
	//!	@return		The help info.
	virtual WStringR OnGetHelpInfo( ) const PURE;

	//!	When launch the application.
	//!	@remark		We should just process tasks lightly in this callback function, otherwise it could be killed by OS.
	//!	@param		application		The application.
	//! @param		cmd_parser		The command line parser.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool OnLaunch( IApplication* application, ICommandLineParser* cmd_parser ) PURE;
	//!	When load the application.
	//!	@param		application		The application.
	//!	@param		loading_times	The loading times counter.
	//!	@param		keep_loading	True indicates keep to call OnLoad() interface.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool OnLoad( IApplication* application, _dword loading_times, _ubool& keep_loading ) PURE;
	//!	When unload the application.
	//! @param		none.
	//! @return		none.
	virtual _void OnUnload( ) PURE;

	//!	When update the application.
	//! @param		limited_elapse	The millisecond time of the animation update interval.
	//! @param		elapse			The millisecond time of the update interval.
	//! @return		none.
	virtual _void OnTick( _dword limited_elapse, _dword elapse ) PURE;

	//!	When handle the application event.
	//!	@param		event		The event info.
	//!	@return		none.
	virtual _void OnHandleEvent( EventBase& event ) PURE;
	//!	When handle command.
	//!	@param		cmd			The command string.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool OnHandleCommand( WStringPtr cmd ) PURE;
};

}