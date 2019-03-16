//! @file     FileFinder.h
//! @author   LiCode
//! @version  1.1.0.702
//! @date     2011/02/15
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FileFinder
//----------------------------------------------------------------------------

class FileFinder
{
public:
 //! The get files type
 enum _GET_FILE_TYPE
 {
  _GET_FILE_TYPE_FULL_PATH,  //! Use the full path to get files
  _GET_FILE_TYPE_RELATIVE_PATH, //! Use the relative path to get files
  _GET_FILE_TYPE_NAME_ONLY,  //! Use the name only to get files
 };

private:
 //! The file finder data
 struct FolderData
 {
  //! The relative path
  WString mRelativePath;
  //! The absolute path
  WString mAbsolutePath;

  //! The file finder handle
  _handle mFinderHandle;

  FolderData( )
   : mFinderHandle( _null ) { }
 };

private:
 typedef Stack< FolderData > FolderDataStack;

private:
 //! The root directory
 WString   mRootDirectory;
 //! The item number counter of walking
 _dword   mItemNumber;

 //! The find finder stack, we use it to enumerate files/directories, it will record the directories stack
 FolderDataStack mFolderDataStack;

private:
 //! Push the directory.
 //! @param relative_path The relative path.
 //! @param absolute_path The absolute path.
 //! @return True indicates success, false indicates failure.
 _ubool PushDir( WStringPtr relative_path, WStringPtr absolute_path );
 //! Pop the directory.
 //! @param none.
 //! @return none.
 _void PopDir( );

 //! Read the next file in the directory.
 //! @param filefinder The file finder.
 //! @param fileinfo The file info.
 //! @param filter  The extension name filter.
 //! @param flags  The enumeration flags.
 //! @return True indicates success, false indicates failure.
 _ubool ReadDir( FolderData& filefinder, FileInfo& fileinfo, WStringPtr filter, _dword flags );

public:
 FileFinder( );
 ~FileFinder( );

public:
 //! Open the root directory.
 //! @param path  The root directory.
 //! @return True indicates success, false indicates failure.
 _ubool Open( WStringPtr path );
 //! Close.
 //! @param none.
 //! @return none.
 _void Close( );

 //! Get the directory path.
 //! @param none.
 //! @return The directory path.
 WStringPtr GetDirectoryPath( ) const;
 //! Get the file by name.
 //! @remark  Make sure we just have only unique file in this directory.
 //! @param name  The file name.
 //! @return The relative file path.
 WString GetFileByName( WStringPtr name );
 //! Check whether has file with specified extension name.
 //! @param extension_name The file extension name.
 //! @param depth   The enumeration depth.
 //! @return True indicates it has file with specified extension name.
 _ubool HasFile( WStringPtr extension_name, _dword depth = -1 );

 //! Get the files.
 //! @param get_type The get file type.
 //! @param filter  The extension name filter.
 //! @param depth  The enumeration depth.
 //! @return The files.
 WStringArray GetFiles( _GET_FILE_TYPE get_type, WStringPtr filter = L"", _dword depth = -1 );

 //! Enumerate/Walk each files/directories in the root directory recursively.
 //! @param fileinfo The file info.
 //! @param filter  The extension name filter.
 //! @param flags  The enumeration flags, @see _FILE_FINDER_ENUMERATION.
 //! @param depth  The enumeration depth.
 //! @return True indicates there are some files or directories what need to walk, otherwise indicates enumerate/walk finished.
 _ubool Walk( FileInfo& fileinfo, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1 );
};

}