//! @file     iosPlatformResource.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Resource Implementation
//----------------------------------------------------------------------------

_handle Platform::FindResource( _handle /*module*/, const _charw* resname, const _charw* path )
{
    // Build resource full file path
    _charw resname_fullpath[1024];
    Platform::FormatStringBuffer( resname_fullpath, 1024, L"%s/%s", path, resname );
                           
	return GetIOSResourceModule( )->LoadMainBundleResource( resname_fullpath );
}

_handle Platform::LoadResource( _handle /*module*/, _handle resinfo )
{
	// The resource info is resource data handle on iphone ( NSData pointer )
	return resinfo;
}

_void Platform::FreeResource( _handle module, _handle resinfo )
{
    if ( resinfo != _null )
        GetIOSResourceModule( )->UnloadMainBundleResource( resinfo );
}

const _byte* Platform::LockResource( _handle resdata )
{
	return GetIOSResourceModule( )->GetDataOfMainBundleResource( resdata );
}

_dword Platform::SizeOfResource( _handle /*module*/, _handle resinfo )
{
	// The resource info is resource data handle on iphone ( NSData pointer )
	return GetIOSResourceModule( )->GetSizeOfMainBundleResource( resinfo );
}

_ubool Platform::EnumResourceNames( _handle module, const _charw* sub_dir_name, OnEnumResNameProc funcpointer, _void* parameter )
{
	return _false;
}