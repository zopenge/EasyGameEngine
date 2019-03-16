//! @file     chromePlatformResource.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Resource Implementation
//----------------------------------------------------------------------------

_handle Platform::FindResource( _handle module, const _charw* resname, const _charw* path )
{
	return _null;
}

_handle Platform::LoadResource( _handle module, _handle resinfo )
{
	return _null;
}

_void Platform::FreeResource( _handle module, _handle resinfo )
{
}

const _byte* Platform::LockResource( _handle resdata )
{
	return _null;
}

_dword Platform::SizeOfResource( _handle module, _handle resinfo )
{
	return 0;
}

_ubool Platform::EnumResourceNames( _handle module, const _charw* sub_dir_name, OnEnumResNameProc funcpointer, _void* parameter )
{
	// The windows do not support sub directory name search mode
	if ( sub_dir_name != _null )
		return _false;

	return _false;
}