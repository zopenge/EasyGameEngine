//! @file     chromeMessages.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

// Chrome messages
#define EGE_CHROME_MESSAGE_OFFSET 12000
#define EGE_CHROME_MESSAGE_BEGIN( struct_name, id_value )	\
	EGE_USER_MESSAGE_BEGIN( struct_name, id_value, EGE_CHROME_MESSAGE_OFFSET )

//----------------------------------------------------------------------------
// Global Messages
//----------------------------------------------------------------------------

EGE_BEGIN_NAMESPACE_2( EGE, ChromeMessages )

DECLARE_COUNTER;

//!	Application load.
EGE_CHROME_MESSAGE_BEGIN( ChromeMessageLoad, _CHROME_MESSAGE_LOAD )
	EGE_MESSAGE_CLONE_0( ChromeMessageLoad )
EGE_MESSAGE_END( )

//!	Application changed view.
EGE_CHROME_MESSAGE_BEGIN( ChromeMessageChangedView, _CHROME_MESSAGE_CHANGED_VIEW )
	_ubool	mIsVisible;
	_ubool	mIsPageVisible;
	RectI	mRect;
	RectI	mClipRect;
	_float	mDeviceScale;
	_float	mCSSScale;
	PointI	mScrollOffset;
	EGE_MESSAGE_CLONE_7( ChromeMessageChangedView, mIsVisible, mIsPageVisible, mRect, mClipRect, mDeviceScale, mCSSScale, mScrollOffset )
EGE_MESSAGE_END( )

//!	Application changed focus.
EGE_CHROME_MESSAGE_BEGIN( ChromeMessageChangedFocus, _CHROME_MESSAGE_CHANGED_FOCUS )
	_ubool	mHasFocus;
	EGE_MESSAGE_CLONE_1( ChromeMessageChangedFocus, mHasFocus )
EGE_MESSAGE_END( )

EGE_END_NAMESPACE_2( )