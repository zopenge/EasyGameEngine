//! @file     IViewBasedApp.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IViewBasedApp
//----------------------------------------------------------------------------

class IViewBasedApp : public IApplication
{
public:
	//!	The application creation flag
	enum _CREATION_FLAG
	{
		_CF_OVERLAPPED,
		_CF_POPUP,
	};

	//!	The application options
	enum _OPTIONS
	{
		//!	Use the low power mode
		_OPTION_LOW_POWER_MODE		= 1 << 0,
		//!	Use the slow motion mode
		_OPTION_SLOW_MOTION_MODE	= 1 << 1,
	};

	//!	The orientation type
	enum _ORIENTATION
	{
		_ORIENTATION_UNKNOWN,
		_ORIENTATION_ANY,		//! Any type
		_ORIENTATION_PORT,		//!	Portrait
		_ORIENTATION_LAND,		//!	Landscape
		_ORIENTATION_SQUARE,	//!	Square
	};

public:
	//!	Make the application position to the center of the screen.
	//!	@param		none.
	//!	@return		none.
	virtual _void Center( ) PURE;
	//!	Move the application position by delta offset.
	//!	@param		delta_x			The delta x offset.
	//!	@param		delta_y			The delta y offset.
	//!	@return		none.
	virtual _void Move( _int delta_x, _int delta_y ) PURE;

	//!	Lock size.
	//!	@param		none.
	//!	@return		none.
	virtual _void LockSize( ) PURE;
	//!	Unlock size.
	//!	@param		none.
	//!	@return		none.
	virtual _void UnlockSize( ) PURE;

	//!	Set the application position.
	//!	@param		x				The application window left-top x position of screen.
	//!	@param		y				The application window left-top y position of screen.
	//!	@return		none.
	virtual _void SetPos( _dword x, _dword y ) PURE;
	//!	Get the application position.
	//!	@param		none.
	//!	@return		The application window left-top position of screen.
	virtual PointI GetPos( ) const PURE;
	//!	Set the application size.
	//!	@param		width			The application window width.
	//!	@param		height			The application window height.
	//!	@return		none.
	virtual _void SetSize( _dword width, _dword height ) PURE;
	//!	Get the application size.
	//!	@param		none.
	//!	@return		The application window size.
	virtual PointU GetSize( ) const PURE;
	//!	Set the application rect.
	//!	@param		rect			The application window rect.
	//!	@return		none.
	virtual RectI GetRect( ) const PURE;

	//!	Set the application client size.
	//!	@param		width			The client width.
	//!	@param		height			The client height.
	//!	@param		deltawidth		The delta-width of client to application window.
	//!	@param		deltaheight		The delta-height of client to application window.
	//!	@return		none.
	virtual _void SetClientSize( _dword width, _dword height, _int* deltawidth = _null, _int* deltaheight = _null ) PURE;
	//!	Get the application client region.
	//!	@param		rect			The application client region.
	//!	@return		none.
	virtual RectU GetClientRectU( ) const PURE;
	//!	Get the application client region.
	//!	@param		rect			The application client region.
	//!	@return		none.
	virtual RectF GetClientRectF( ) const PURE;
	//!	Get the application client size.
	//!	@param		none.
	//!	@return		The application client size.
	virtual PointU GetClientSize( ) const PURE;

	//! Get the orientation.
	//!	@param		none.
	//!	@return		The orientation of application.
	virtual _ORIENTATION GetOrientation( ) const PURE;

	//!	Enable/Disable options.
	//!	@param		options		The options, @see _OPTIONS.
	//!	@param		enable		True indicates enable options, otherwise disable.
	//!	@return		none.
	virtual _void EnableOptions( _dword options, _ubool enable ) PURE;
	//!	Check enable options or not.
	//!	@param		options		The options, @see _OPTIONS.
	//!	@return		True indicates these options enabled, otherwise disable.
	virtual _ubool IsEnableOptions( _dword options ) const PURE;

	//!	Sets the mouse capture to the specified window belonging to the current thread.
	//!	@param		none.
	//!	@return		none.
	virtual _void SetCapture( ) PURE;
	//!	Releases the mouse capture from a window in the current thread and restores normal mouse input processing.
	//!	@param		none.
	//!	@return		none.
	virtual _void ReleaseCapture( ) PURE;

	//!	Get the key down deferred processor.
	//!	@param		none.
	//!	@return		none.
	virtual DeferredProcessor& GetKeyDownDeferredProcessor( ) PURE;
	//!	Get the key down deferred processor.
	//!	@param		none.
	//!	@return		none.
	virtual const DeferredProcessor& GetKeyDownDeferredProcessor( ) const PURE;
};

}