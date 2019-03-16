//! @file     FileSystem.h
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FileSystem
//----------------------------------------------------------------------------

//! This class represents win32 file system.
class FileSystem
{
public:
 //! Check if the specified file is existing or not.
 //! @param filename   The name of the file.
 //! @return True if it's existing, false otherwise.
 static _ubool IsFileExist( WStringPtr filename );
 //! Check if the specified directory is existing or not.
 //! @param directory   The name of the directory.
 //! @return True if it's existing, false otherwise.
 static _ubool IsDirectoryExist( WStringPtr directory );
 //! Check if a directory is empty.
 //! @param directory   The name of the directory.
 //! @return True if it's empty, false otherwise.
 static _ubool IsDirectoryEmpty( WStringPtr directory );

 //! Get the internal path in domains.
 //! @param none.
 //! @return The internal path in domains.
 static WString GetInternalPathInDomains( );
 //! Get the external path in domains.
 //! @param none.
 //! @return The external path in domains.
 static WString GetExternalPathInDomains( );
 //! Get the document path in domains.
 //! @param none.
 //! @return The document path in domains.
 static WString GetDocumentPathInDomains( );

 //! Creates a name for a temporary directory.
 //! @param path    The specified path.
 //! @param name    The unique directory name.
 //! @return The temporary directory name.
 static _ubool GetTempDirName( WStringPtr path, WString& name );
 //! Creates a name for a temporary file.
 //! @param path    The specified path.
 //! @param extensionname  The extension name of unique file.
 //! @param filename   The unique file name.
 //! @return The temporary file name.
 static _ubool GetTempFileName( WStringPtr path, WStringPtr extensionname, WString& filename );

 //! Retrieves the size of the specified file in bytes.
 //! @param filename   The name of the file.
 //! @param bytes    Size of file to get from this function.
 //! @return True indicates success, false indicates failure.
 static _ubool GetFileSize( WStringPtr filename, _dword& bytes );
 //! Get attributes of a specified file.
 //! @param filename   The name of the file.
 //! @param attributes   Attributes of file to get from this function, @see _FILE_ATTRIBUTE.
 //! @return True indicates success, false indicates failure.
 static _ubool GetAttributes( WStringPtr filename, _dword& attributes );
 //! Set attributes of a specified file.
 //! @param filename   The name of the file.
 //! @param attributes   Attributes to set for the file, @see _FILE_ATTRIBUTE.
 //! @return True indicates success, false indicates failure.
 static _ubool SetAttributes( WStringPtr filename, _dword attributes );

 //! Get times of a specified file.
 //! @param filename   The name of the file.
 //! @param creation   The date and time the file was created.
 //! @param lastaccess   The date and time the file was last accessed.
 //! @param lastwrite   The date and time the file was last written to.
 //! @return True indicates success, false indicates failure.
 static _ubool GetTimes( WStringPtr filename, FileTime* creation, FileTime* lastaccess, FileTime* lastwrite );
 //! Get times of a specified file.
 //! @param filename   The name of the file.
 //! @param creation   The date and time the file was created.
 //! @param lastaccess   The date and time the file was last accessed.
 //! @param lastwrite   The date and time the file was last written to.
 //! @return True indicates success, false indicates failure.
 static _ubool GetTimes( WStringPtr filename, CalendarTime* creation, CalendarTime* lastaccess, CalendarTime* lastwrite );
 //! Set times of a specified file.
 //! @param filename   The name of the file.
 //! @param creation   The date and time the file was created.
 //! @param lastaccess   The date and time the file was last accessed.
 //! @param lastwrite   The date and time the file was last written to.
 //! @return True indicates success, false indicates failure.
 static _ubool SetTimes( WStringPtr filename, CalendarTime* creation, CalendarTime* lastaccess, CalendarTime* lastwrite );

 //! Create an empty file.
 //! @remarks If the file already exists, it will not be truncated.
 //! @param filename   The name of the file.
 //! @param attributeflag  The attribute of file.
 //! @return True indicates success, false indicates failure.
 static _ubool CreateFile( WStringPtr filename, _dword attributeflag = 0 );
 //! Create a file with ANSI string.
 //! @remarks If the file already exists, it will be overwritten.
 //! @param filename   The name of the file.
 //! @param string    The ANSI string.
 //! @param attributeflag  The attribute of file.
 //! @return True indicates success, false indicates failure.
 static _ubool CreateFile( WStringPtr filename, AStringPtr string, _dword attributeflag = 0 );
 //! Create a file with specified buffer and size.
 //! @remarks If the file already exists, it will be overwritten.
 //! @param filename   The name of the file.
 //! @param size    The size of file.
 //! @param buffer    The buffer to be written into the file, it can be null, means only set file size.
 //! @param attributeflag  The attribute of file.
 //! @return True indicates success, false indicates failure.
 static _ubool CreateFile( WStringPtr filename, _dword size, const _void* buffer, _dword attributeflag = 0 );
 //! Delete an existing file.
 //! @param filename   The name of the file.
 //! @return True indicates success, false indicates failure.
 static _ubool DeleteFile( WStringPtr filename );
 //! Copy an existing file to a new one.
 //! @param desfilename   The name of the new file.
 //! @param srcfilename   The name of the existing file.
 //! @return True indicates success, false indicates failure.
 static _ubool CopyFile( WStringPtr desfilename, WStringPtr srcfilename );
 //! Renames an existing file or a directory.
 //! @param desfilename   The name of the new file.
 //! @param srcfilename   The name of the existing file.
 //! @return True indicates success, false indicates failure.
 static _ubool MoveFile( WStringPtr desfilename, WStringPtr srcfilename );
 //! Read an existing file as text.
 //! @param filename   The name of the file.
 //! @param string    The file buffer as string.
 //! @return True indicates success, false indicates failure.
 static _ubool ReadFile( WStringPtr filename, AString& string );
 //! Read an existing file as text.
 //! @param filename   The name of the file.
 //! @param string    The file buffer as string.
 //! @return True indicates success, false indicates failure.
 static _ubool ReadFile( WStringPtr filename, UString& string );
 //! Read an existing file as text.
 //! @param filename   The name of the file.
 //! @param string    The file buffer as string.
 //! @return True indicates success, false indicates failure.
 static _ubool ReadFile( WStringPtr filename, WString& string );
 //! Get the file encoding type.
 //! @param filename   The name of the file.
 //! @return The file encoding type.
 static _ENCODING GetFileEncodingType( WStringPtr filename );

 //! Get the current directory for the current process.
 //! @param none
 //! @return The path string of current directory.
 static WString GetCurrentDir( );
 //! Set the current directory for the current process.
 //! @param directory   The path name of new current directory.
 //! @return True indicates success, false indicates failure.
 static _ubool SetCurrentDir( WStringPtr directory );

 //! Create a new directory.
 //! @param directory   The path name of new directory.
 //! @return True indicates success, false indicates failure.
 static _ubool CreateDir( WStringPtr directory );
 //! Delete a directory tree, includes all files and sub directories.
 //! @param directory   The path name of directory to be deleted.
 //! @return True indicates success, false indicates failure.
 static _ubool DeleteDir( WStringPtr directory );
 //! Copy a directory tree, includes all files and sub directories.
 //! @param desdirectory  The path name of directory to copy into.
 //! @param srcdirectory  The path name of directory to be copied.
 //! @return True indicates success, false indicates failure.
 static _ubool CopyDir( WStringPtr desdirectory, WStringPtr srcdirectory );
 //! Move a directory tree, includes all files and sub directories.
 //! @param desdirectory  The path name of directory to move into.
 //! @param srcdirectory  The path name of directory to be moved.
 //! @return True indicates success, false indicates failure.
 static _ubool MoveDir( WStringPtr desdirectory, WStringPtr srcdirectory );
 //! Trim a directory, delete any empty sub directories.
 //! @param directory   The path name of directory to be trimmed.
 //! @return True indicates success, false indicates failure.
 static _ubool TrimDir( WStringPtr directory );
 //! Clean a directory, delete all sub-directories and sub-files.
 //! @param directory   The path name of directory to be cleaned.
 //! @return True indicates success, false indicates failure.
 static _ubool CleanDir( WStringPtr directory );

 //! Delete a directory or file.
 //! @param path    The directory path or file path.
 //! @return True indicates success, false indicates failure.
 static _ubool Delete( WStringPtr path );

 //! Get information about the amount of space on a disk volume.
 //! @param directory   Pointer to a null-terminated string that specifies a directory on the specified disk.
 //! @param total    Number of total bytes on a disk get from this function.
 //! @param available   Number of free bytes on a disk get from this function.
 //! @return True indicates success, false indicates failure.
 static _ubool GetDiskSpace( WStringPtr directory, _qword& total, _qword& available );

 //! Compare two files.
 //! @param srcfilename   The name of the source file.
 //! @param desfilename   The name of the target file.
 //! @return True if two files are exactly same, otherwise false.
 static _ubool CompareFile( WStringPtr srcfilename, WStringPtr desfilename );
 //! Compare two folders.
 //! @param srcdirectory  The name of the source directory.
 //! @param desdirectory  The name of the target directory.
 //! @param deletesame   If delete same file in target directory.
 //! @return True if two directories are exactly same, otherwise false.
 static _ubool CompareDir( WStringPtr srcdirectory, WStringPtr desdirectory, _ubool deletesame );

 //! Enumerate/Walk each files/directories in recursively.
 //! @param path   The relative directory path.
 //! @param filter   The extension name filter.
 //! @param flags   The enumeration flags, @see _FILE_FINDER_ENUMERATION.
 //! @param depth   The enumeration depth.
 //! @param items   The file or directories items info.
 //! @return True indicates success, false indicates failure.
 static _ubool EnumResources( WStringPtr path, WStringPtr filter, _dword flags, _dword depth, FileInfoArray& items );

 //! Check whether it's text file.
 //! @param filename  The file name.
 //! @return True indicates it's text file.
 static _ubool IsTextFile( WStringPtr filename );
};

}