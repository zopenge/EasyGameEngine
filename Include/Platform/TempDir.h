//! @file     TempDir.h
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TempDir
//----------------------------------------------------------------------------

class TempDir
{
private:
	WString mDirPath;

public:
	TempDir( WStringPtr root_dir );
	TempDir( const TempDir& root_dir );
	~TempDir( );

public:
	WStringPtr GetDirPath( ) const;
};

//----------------------------------------------------------------------------
// TempDir Implementation
//----------------------------------------------------------------------------

inline WStringPtr TempDir::GetDirPath( ) const
{
	return mDirPath;
}

}
