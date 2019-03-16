//! @file     PlatformGlobal.h
//! @author   LiCode
//! @version  1.1.0.702
//! @date     2011/02/15
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// The platform structures
//----------------------------------------------------------------------------

//! The source file line info
template< typename CharType >
struct SrcFileLineInfo
{
	_dword		mAddress;
	CharType	mFileName[256];
	_dword		mLinenumber;

	_ubool operator == ( const SrcFileLineInfo& info ) const
	{
		if ( mAddress != info.mAddress )
			return _false;

		if ( Platform::CompareString( mFileName, info.mFileName ) != 0 )
			return _false;

		if ( mLinenumber != info.mLinenumber )
			return _false;

		return _true;
	}

	SrcFileLineInfo( ) : mAddress( 0 ), mLinenumber( 0 ) 
	{
		mFileName[0] = 0;
	}
	SrcFileLineInfo( _dword address, const CharType* file_name, _dword line_number ) : mAddress( address ), mLinenumber( line_number ) 
	{
		SafeCopyString( mFileName, file_name );
	}
};
typedef SrcFileLineInfo< _chara > ASrcFileLineInfo;
typedef SrcFileLineInfo< _charw > WSrcFileLineInfo;
typedef Array< ASrcFileLineInfo > ASrcFileLineInfoArray;
typedef Array< WSrcFileLineInfo > WSrcFileLineInfoArray;
typedef FixedArray< ASrcFileLineInfo, 256 > ASrcFileLineInfoFixedArray;
typedef FixedArray< WSrcFileLineInfo, 256 > WSrcFileLineInfoFixedArray;

//! The detail of file or directory info
struct FileInfo
{
	//! The enumeration depth
	_dword	mDepth;
	//! The number of items found so far.
	_dword	mItemNumber;

	//! The relative path
	WString	mRelativePath;
	//! The absolute path
	WString	mAbsolutePath;
	//! The file name
	WString	mFileName;

	//! The file size
	_qword	mSize;
	//! The file attributes, @see _FILE_ATTRIBUTE
	_dword	mAttributes;
	//! The last write time
	_qword	mLastWriteTime;

	FileInfo( )
		: mDepth( 0 ), mItemNumber( 0 ), mSize( 0 ), mAttributes( 0 ), mLastWriteTime( 0 ) { }
};
typedef Array< FileInfo > FileInfoArray;

}