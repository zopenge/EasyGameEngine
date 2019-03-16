//! @file     GraphicEvents.h
//! @author   LiCode
//! @version  1.1.0.556
//! @date     2011/01/08
//! Copyright 2009-2011 LiCode's Union.

#pragma once

// The event ID start value
#define EGE_EVENT_OFFSET 2000
#include "EGE_EventMacros.h"

//----------------------------------------------------------------------------
// Global Events
//----------------------------------------------------------------------------

EGE_EVENT_SESSION_BEGIN( EGE, GraphicEvents )

//!	Create sub-process event
EGE_EVENT_1( EventShaderCreated, _GRAPHIC_EVENT_SHADER_CREATED,
	IGraphicEffectRef, mEffect )
EGE_EVENT_END( )

EGE_EVENT_SESSION_END( )
#undef EGE_EVENT_OFFSET