//! @file     iosControllerManager.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// iosControllerManager Implementation
//----------------------------------------------------------------------------

iosControllerManager::iosControllerManager( )
{
}

iosControllerManager::~iosControllerManager( )
{
}

_ubool iosControllerManager::Initialize( IViewBasedApp* application )
{
	return _true;
}

_void iosControllerManager::Pause( )
{
}

_void iosControllerManager::Resume( )
{
}

_dword iosControllerManager::GetJoystickNumber( ) const
{
	return 0;
}

IJoystickRef iosControllerManager::GetJoystickByIndex( _dword index ) const
{
	return _null;
}
