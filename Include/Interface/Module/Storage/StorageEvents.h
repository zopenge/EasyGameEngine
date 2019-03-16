//! @file     StorageEvents.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2010 LiCode's Union.

#pragma once

// The event ID start value
#define EGE_EVENT_OFFSET 3000
#include "EGE_EventMacros.h"

//----------------------------------------------------------------------------
// Storage Event Classes 
//----------------------------------------------------------------------------

EGE_EVENT_SESSION_BEGIN( EGE, StorageEvents )

EGE_EVENT_SESSION_END( )
#undef EGE_EVENT_OFFSET