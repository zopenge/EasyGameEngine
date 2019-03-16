//! @file     GraphicModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicModule Implementation
//----------------------------------------------------------------------------

_ubool GraphicModule::HandleEventInMainThread( EventBase& event )
{
	if ( gDynamicRHI->HandleEventsInMainThread( event ) )
		return _true;

	return _false;
}

_ubool GraphicModule::IsBlockEvent( _dword event_id, _ubool& is_async ) const
{
	if ( gDynamicRHI->IsBlockEvent( event_id, is_async ) )
		return _true;

	return _false;
}