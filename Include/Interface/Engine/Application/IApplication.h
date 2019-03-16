//! @file     IApplication.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IApplication
//----------------------------------------------------------------------------

class IApplication : public IObserver
{
public:
	//!	Get the application type.
	//!	@param		none.
	//!	@return		The application type.
	virtual _APPLICATION_TYPE GetApplicationType( ) const PURE;
	//!	Get the application handle.
	//!	@param		none.
	//!	@return		The application handle.
	virtual _handle GetApplicationHandle( ) const PURE;
	//!	Get the application layer handle.
	//!	@param		none.
	//!	@return		The application layer handle.
	virtual _handle GetApplicationLayerHandle( ) const PURE;

	//!	Set the max limited elapsed time.
	//!	@param		elapse		The max limited elapsed time.
	//!	@return		none.
	virtual _void SetMaxLimitedElapsedTime( _dword elapse ) PURE;
	//!	Get the max limited elapsed time.
	//!	@param		none.
	//!	@return		The max limited elapsed time.
	virtual _dword GetMaxLimitedElapsedTime( ) const PURE;

	//!	Get the total elapsed time.
	//!	@param		none.
	//!	@return		The elapsed time in milliseconds.
	virtual _dword GetTotalElapsedTime( ) const PURE;

	//!	Verify.
	//!	@param		key				The decryption key.
	//!	@param		stream_reader	The stream reader.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool Verify( AStringPtr key, IStreamReader* stream_reader ) PURE;

	//!	Quit the application.
	//!	@param		none.
	//!	@return		none.
	virtual _void Quit( ) PURE;
	//!	Check whether the application is quit.
	//!	@param		none.
	//!	@return		True indicates the application is quit.
	virtual _ubool IsQuit( ) const PURE;

	//!	Restart the application.
	//!	@param		none.
	//!	@return		none.
	virtual _void Restart( ) PURE;
	//!	Check whether the application is restart.
	//!	@param		none.
	//!	@return		True indicates the application is restart.
	virtual _ubool IsRestart( ) const PURE;

	//!	Show application.
	//!	@param		none.
	//!	@return		none.
	virtual _void Show( ) PURE;
	//!	Hide application.
	//!	@param		none.
	//!	@return		none.
	virtual _void Hide( ) PURE;

	//!	Set the sleep time.
	//!	@param		time			The sleep time in milliseconds, -1 indicates never sleep.
	//!	@return		none.
	virtual _void SetSleepTime( _dword time ) PURE;
	//!	Get the sleep time.
	//!	@param		none.
	//!	@return		The sleep time in milliseconds, -1 indicates never sleep.
	virtual _dword GetSleepTime( ) const PURE;

	//!	Set title.
	//!	@param		title			The title name.
	//!	@return		none.
	virtual _void SetTitle( WStringPtr title ) PURE;
	//!	Get title.
	//!	@param		none.
	//!	@return		The title name.
	virtual WStringPtr GetTitle( ) const PURE;

	//!	Enable/Disable always on top.
	//!	@param		enable			True indicates always on top.
	//!	@return		none.
	virtual _void EnableAlwaysOnTop( _ubool enable ) PURE;
	//!	Check whether it's always on top.
	//!	@param		none.
	//!	@return		True indicates it's always on top.
	virtual _ubool IsEnableAlwaysOnTop( ) const PURE;

	//!	Run the application.
	//!	@remark		We just use the application delegate pointer directly without clone or copy. <br />
	//!				The user should never call this interface.
	//!	@param		app_delegate	The application delegate.
	//!	@param		cmd_parser		The command line parser.
	//!	@return		The return value.
	virtual _int Run( IAppDelegate* app_delegate, ICommandLineParser* cmd_parser ) PURE;

	//!	When before load modules.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool OnBeforeLoadModules( ) PURE;
	//!	When after load modules.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool OnAfterLoadModules( ) PURE;
};

}