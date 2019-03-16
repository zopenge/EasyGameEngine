//! @file     androidMessages.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

// The event ID start value
#define EGE_EVENT_OFFSET 11000
#include "EGE_EventMacros.h"

//----------------------------------------------------------------------------
// Global Messages
//----------------------------------------------------------------------------

EGE_EVENT_SESSION_BEGIN( EGE, AndroidMessages )

//!	Application pause.
EGE_EVENT_0( AndroidMessagePause, _ANDROID_MESSAGE_PAUSE )
EGE_EVENT_END( )

//!	Application resume.
EGE_EVENT_0( AndroidMessageResume, _ANDROID_MESSAGE_RESUME )
EGE_EVENT_END( )

//!	Application stop.
EGE_EVENT_0( AndroidMessageStop, _ANDROID_MESSAGE_STOP )
EGE_EVENT_END( )

//!	Application restart.
EGE_EVENT_0( AndroidMessageRestart, _ANDROID_MESSAGE_RESTART )
EGE_EVENT_END( )

//!	Application start.
EGE_EVENT_0( AndroidMessageStart, _ANDROID_MESSAGE_START )
EGE_EVENT_END( )

//!	Application window focus changed.
EGE_EVENT_1( AndroidMessageWindowFocusChanged, _ANDROID_MESSAGE_WINDOW_FOCUS_CHANGED,
	_ubool, mHasFocus )
EGE_EVENT_END( )

//!	Application window change config.
EGE_EVENT_1( AndroidMessageWindowChangeConfig, _ANDROID_MESSAGE_WINDOW_CHANGE_CONFIG,
	AConfiguration*, mConfiguration )
EGE_EVENT_END( )

//!	Application create surface.
EGE_EVENT_0( AndroidMessageCreateSurface, _ANDROID_MESSAGE_CREATE_SURFACE )
EGE_EVENT_END( )

//!	Application resize surface.
EGE_EVENT_2( AndroidMessageResizeSurface, _ANDROID_MESSAGE_RESIZE_SURFACE,
	_dword, mWidth,
	_dword, mHeight )
EGE_EVENT_END( )

//!	Application memory low.
EGE_EVENT_0( AndroidMessageMemoryLow, _ANDROID_MESSAGE_MEMORY_LOW )
EGE_EVENT_END( )

//!	Application quit.
EGE_EVENT_0( AndroidMessageQuit, _ANDROID_MESSAGE_QUIT )
EGE_EVENT_END( )

EGE_EVENT_SESSION_END( )
#undef EGE_EVENT_OFFSET