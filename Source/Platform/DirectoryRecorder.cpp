//! @file     DirectoryRecorder.cpp
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// DirectoryRecorder Implementation
//----------------------------------------------------------------------------

DirectoryRecorder::DirectoryRecorder( WStringPtr directory )
	: mOldDirectory( FileSystem::GetCurrentDir( ) )
{
	FileSystem::SetCurrentDir( directory );
}

DirectoryRecorder::~DirectoryRecorder( )
{
	FileSystem::SetCurrentDir( mOldDirectory );
}
