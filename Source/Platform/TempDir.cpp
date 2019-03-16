//! @file     TempDir.cpp
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// TempDir Implementation
//----------------------------------------------------------------------------

TempDir::TempDir( WStringPtr root_dir )
{
 FileSystem::GetTempDirName( root_dir, mDirPath );
 FileSystem::CleanDir( mDirPath );
}

TempDir::TempDir( const TempDir& root_dir )
{
 FileSystem::GetTempDirName( root_dir.GetDirPath( ), mDirPath );
 FileSystem::CleanDir( mDirPath );
}

TempDir::~TempDir( )
{
 FileSystem::DeleteDir( mDirPath );
}
