//! @file     Path.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Path
//----------------------------------------------------------------------------

class Path
{
private:
 WStringArray mSubPath;

private:
 //! Search the directory separation character index.
 template< typename StringPtrType >
 inline static _dword SearchDirSeparationIndexL2R( StringPtrType path );
 template< typename StringPtrType >
 inline static _dword SearchDirSeparationIndexR2L( StringPtrType path );

private:
 //! Returns the file name and extension of the specified path string.
 template< typename StringType, typename StringPtrType >
 static StringType GetFileName( StringPtrType path, _ubool extension = _true );

 //! Returns the extension of the specified path string.
 template< typename StringType, typename StringPtrType >
 static StringType GetExtension( StringPtrType path );
 //! Replaces the extension of the specified path string.
 template< typename StringType, typename StringPtrType >
 static StringType ReplaceExtension( StringPtrType path, StringPtrType dot, StringPtrType extension );
 //! Remove the extension of the specified path string.
 template< typename StringType, typename StringPtrType >
 static StringType RemoveExtension( StringPtrType path );

 //! Gets the root directory information of the specified path.
 template< typename StringType, typename StringPtrType >
 static StringType GetPathRoot( StringPtrType path );
 //! Gets the root directory information of the specified path.
 template< typename StringType, typename StringPtrType >
 static StringType GetChildPathRoot( StringPtrType path );
 //! Returns the directory information for the specified path string.
 template< typename StringType, typename StringPtrType >
 static StringType GetDirectoryName( StringPtrType path );
 //! Returns the parent directory information for the specified path string.
 template< typename StringType, typename StringPtrType >
 static StringType GetParentDirectoryName( StringPtrType path );

 //! Get root URL address.
 template< typename StringType, typename StringPtrType >
 static StringType GetRootURLAddress( StringPtrType path, StringPtrType protocol_head_string, StringPtrType split_char, StringPtrType trim_char );
 //! Get sub URL address.
 template< typename StringType, typename StringPtrType >
 static StringType GetSubURLAddress( StringPtrType path, StringPtrType protocol_head_string, StringPtrType split_char, StringPtrType trim_char );

 template< typename StringType, typename StringPtrType >
 static _ubool IsIPAddress( StringPtrType url, StringPtrType split_char, StringPtrType trim_char );

 //! Build path.
 template< typename StringType, typename StringPtrType >
 static StringType BuildFilePath( StringPtrType path, StringPtrType filename, StringPtrType trim_strings );

 //! Build relative path.
 template< typename StringType, typename StringPtrType >
 static StringType GetRelativePath( StringPtrType patha, StringPtrType pathb );

 //! Normalize file name.
 template< typename StringType, typename StringPtrType >
 static StringType NormalizedFileName( StringPtrType filename );
 //! Normalize path name.
 template< typename StringType, typename StringPtrType >
 static StringType NormalizedPathName( StringPtrType pathname );
 //! Cleanup path.
 template< typename StringType, typename StringPtrType >
 static StringType CleanupPath( StringPtrType pathname );

 //! Check whether it's valid path string or not.
 template< typename StringPtrType >
 static _ubool IsPathString( StringPtrType string );

 //! Check whether it's path rooted or not.
 template< typename StringPtrType >
 static _ubool IsPathRooted( StringPtrType string );

public:
 Path( );
 Path( const Path& path );
 Path( WStringPtr path );

public:
 //! Operator functions.
 _ubool operator == ( const Path& path ) const;
 _ubool operator != ( const Path& path ) const;
 _ubool operator >  ( const Path& path ) const;
 _ubool operator <  ( const Path& path ) const;
 _ubool operator >= ( const Path& path ) const;
 _ubool operator <= ( const Path& path ) const;

 //! Get the sub-path.
 WStringPtr operator[] ( _dword index ) const;

public:
 //! Get the number of sub-path.
 //! @param none.
 //! @return The number of sub-path.
 _dword Number( ) const;

 //! Get the path string.
 //! @param none.
 //! @return The path string.
 WString Str( ) const;
 //! Get the file name.
 //! @param extension  Whether need the extension of the the file name.
 //! @return The characters after the last directory character in path.
 WString GetFileName( _ubool extension = _true ) const;

public:
 //! Returns the file name and extension of the specified path string.
 //! @param path   The path string from which to obtain the file name and extension. 
 //! @param extension  Whether need the extension of the the file name.
 //! @return The characters after the last directory character in path.
 inline static AString GetFileName( AStringPtr path, _ubool extension = _true );
 //! Returns the file name and extension of the specified path string.
 //! @param path   The path string from which to obtain the file name and extension. 
 //! @param extension  Whether need the extension of the the file name.
 //! @return The characters after the last directory character in path.
 inline static UString GetFileNameU( UStringPtr path, _ubool extension = _true );
 //! Returns the file name and extension of the specified path string.
 //! @param path   The path string from which to obtain the file name and extension. 
 //! @param extension  Whether need the extension of the the file name.
 //! @return The characters after the last directory character in path.
 inline static WString GetFileName( WStringPtr path, _ubool extension = _true );

 //! Returns the extension of the specified path string.
 //! @param path   The path string from which to get the extension. 
 //! @return The extension of the specified path.
 inline static AString GetExtension( AStringPtr path );
 //! Returns the extension of the specified path string.
 //! @param path   The path string from which to get the extension. 
 //! @return The extension of the specified path.
 inline static UString GetExtensionU( UStringPtr path );
 //! Returns the extension of the specified path string.
 //! @param path   The path string from which to get the extension. 
 //! @return The extension of the specified path.
 inline static WString GetExtension( WStringPtr path );
 //! Replaces the extension of the specified path string.
 //! @param path   The path string from which to replace the extension. 
 //! @param extension  The new extension name will replace.
 //! @return The extension of the specified path.
 inline static AString ReplaceExtension( AStringPtr path, AStringPtr extension );
 //! Returns the extension of the specified path string.
 //! @param path   The path string from which to get the extension. 
 //! @param extension  The new extension name will replace.
 //! @return The extension of the specified path.
 inline static WString ReplaceExtension( WStringPtr path, WStringPtr extension );
 //! Removes the extension of the specified path string.
 //! @param path   The path string from which to remove the extension. 
 //! @return The extension of the specified path.
 inline static AString RemoveExtension( AStringPtr path );
 //! Removes the extension of the specified path string.
 //! @param path   The path string from which to remove the extension. 
 //! @return The extension of the specified path.
 inline static WString RemoveExtension( WStringPtr path );

 //! Gets the root directory information of the specified path.
 //! @param path   The path from which to obtain root directory information. 
 //! @return The root directory of path.
 inline static AString GetPathRoot( AStringPtr path );
 //! Gets the root directory information of the specified path.
 //! @param path   The path from which to obtain root directory information. 
 //! @return The root directory of path.
 inline static WString GetPathRoot( WStringPtr path );

 //! Gets the root directory information of the specified path.
 //! @param path   The path from which to obtain root directory information. 
 //! @return The root directory of path.
 inline static AString GetChildPathRoot( AStringPtr path );
 //! Gets the root directory information of the specified path.
 //! @param path   The path from which to obtain root directory information. 
 //! @return The root directory of path.
 inline static WString GetChildPathRoot( WStringPtr path );

 //! Returns the directory information for the specified path string.
 //! @param path   The path of a file or directory. 
 //! @return Directory information for path.
 inline static AString GetDirectoryName( AStringPtr path );
 //! Returns the directory information for the specified path string.
 //! @param path   The path of a file or directory. 
 //! @return Directory information for path.
 inline static WString GetDirectoryName( WStringPtr path );

 //! Returns the parent directory information for the specified path string.
 //! @param path   The path of a file or directory. 
 //! @return Parent directory information for path.
 inline static AString GetParentDirectoryName( AStringPtr path );
 //! Returns the parent directory information for the specified path string.
 //! @param path   The path of a file or directory. 
 //! @return Parent directory information for path.
 inline static WString GetParentDirectoryName( WStringPtr path );

 //! Returns the root URL address.
 //! @param path     The URL path. 
 //! @param protocol_head_string The protocol head string, ie 'http://'.
 //! @return The root URL address.
 inline static AString GetRootURLAddress( AStringPtr path, AStringPtr protocol_head_string );
 //! Returns the root URL address.
 //! @param path     The URL path. 
 //! @param protocol_head_string The protocol head string, ie 'http://'.
 //! @return The root URL address.
 inline static UString GetRootURLAddress( UStringPtr path, UStringPtr protocol_head_string );
 //! Returns the root URL address.
 //! @param path     The URL path. 
 //! @param protocol_head_string The protocol head string, ie 'http://'.
 //! @return The root URL address.
 inline static WString GetRootURLAddress( WStringPtr path, WStringPtr protocol_head_string );

 //! Returns the sub URL address.
 //! @param path     The URL path. 
 //! @param protocol_head_string The protocol head string, ie 'http://'.
 //! @return The sub URL address.
 inline static AString GetSubURLAddress( AStringPtr path, AStringPtr protocol_head_string );
 //! Returns the sub URL address.
 //! @param path     The URL path. 
 //! @param protocol_head_string The protocol head string, ie 'http://'.
 //! @return The sub URL address.
 inline static UString GetSubURLAddress( UStringPtr path, UStringPtr protocol_head_string );
 //! Returns the sub URL address.
 //! @param path     The URL path. 
 //! @param protocol_head_string The protocol head string, ie 'http://'.
 //! @return The sub URL address.
 inline static WString GetSubURLAddress( WStringPtr path, WStringPtr protocol_head_string );

 //! Check whether it's IP address.
 inline static _ubool IsIPAddress( AStringPtr url );
 //! Check whether it's IP address.
 inline static _ubool IsIPAddress( UStringPtr url );
 //! Check whether it's IP address.
 inline static _ubool IsIPAddress( WStringPtr url );

 //! Check whether it's HTTP/HTTPs protocol.
 inline static _ubool IsHTTPProtocol( AStringPtr url );
 //! Check whether it's HTTP/HTTPs protocol.
 inline static _ubool IsHTTPProtocol( UStringPtr url );
 //! Check whether it's HTTP/HTTPs protocol.
 inline static _ubool IsHTTPProtocol( WStringPtr url );

 //! Build path.
 //! @param path   The directory path.
 //! @param filename  The file name.
 //! @return The file path.
 inline static AString BuildFilePath( AStringPtr path, AStringPtr filename );
 //! Build path.
 //! @param path   The directory path.
 //! @param filename  The file name.
 //! @return The file path.
 inline static UString BuildFilePathU( UStringPtr path, UStringPtr filename );
 //! Build path.
 //! @param path   The directory path.
 //! @param filename  The file name.
 //! @return The file path.
 inline static WString BuildFilePath( WStringPtr path, WStringPtr filename );

 //! Check the file extension name with filter.
 //! @param filename  The file name.
 //! @param extension_list The extension name list.
 //! @param ignorecase  True indicates case insensitive when parsing.
 //! @return True indicates the file name fit the filter.
 inline static _ubool DoesMatchExtension( AStringPtr filename, AStringPtr extension_list, _ubool ignorecase = _false );
 //! Check the file extension name with filter.
 //! @param filename  The file name.
 //! @param extension_list The extension name list.
 //! @param ignorecase  True indicates case insensitive when parsing.
 //! @return True indicates the file name fit the filter.
 inline static _ubool DoesMatchExtension( WStringPtr filename, WStringPtr extension_list, _ubool ignorecase = _false );

 //! Get the relative path from path B to path A.( example: path A: "D:\A\c.png"; path B: "D:\A\B\", return "..\c.png"
 //! @param patha   The path A.
 //! @param pathb   The path B.( path B must be Directory )
 //! @return The relative path.
 inline static AString GetRelativePath( AStringPtr patha, AStringPtr pathb );
 //! Get the relative path from path B to path A.( example: path A: "D:\A\c.png"; path B: "D:\A\B\", return "..\c.png"
 //! @param patha   The path A.
 //! @param pathb   The path B.( path B must be Directory )
 //! @return The relative path.
 inline static WString GetRelativePath( WStringPtr patha, WStringPtr pathb );

 //! Normalize an ANSI file name.
 //! @param string  The ANSI string.
 //! @return The string with path normalized.
 inline static AString NormalizedFileName( AStringPtr string );
 //! Normalize an UNICODE file name.
 //! @param string  The UNICODE string.
 //! @return The string with path normalized.
 inline static WString NormalizedFileName( WStringPtr string );
 //! Normalize an ANSI path name.
 //! @param string  The ANSI string.
 //! @return The string with path normalized.
 inline static AString NormalizedPathName( AStringPtr string );
 //! Normalize an UNICODE path name.
 //! @param string  The UNICODE string.
 //! @return The string with path normalized.
 inline static WString NormalizedPathName( WStringPtr string );

 //! Cleanup an ANSI path.
 //! @param string  The ANSI string.
 //! @return The string with cleaned path.
 inline static AString CleanupPath( AStringPtr string );
 //! Cleanup an UNICODE path.
 //! @param string  The UNICODE string.
 //! @return The string with cleaned path.
 inline static WString CleanupPath( WStringPtr string );

 //! Check whether it's valid path string or not.
 //! @param string  The ANSI string.
 //! @return True indicates it's valid path string.
 inline static _ubool IsPathString( AStringPtr string );
 //! Check whether it's valid path string or not.
 //! @param string  The UTF-16 string.
 //! @return True indicates it's valid path string.
 inline static _ubool IsPathString( WStringPtr string );

 //! Check whether it's path rooted or not.
 //! @param string  The ANSI string.
 //! @return True indicates it's path rooted.
 inline static _ubool IsPathRooted( AStringPtr string );
 //! Check whether it's path rooted or not.
 //! @param string  The UTF-16 string.
 //! @return True indicates it's path rooted.
 inline static _ubool IsPathRooted( WStringPtr string );
};

//----------------------------------------------------------------------------
// Path Implementation
//----------------------------------------------------------------------------

template< typename StringPtrType >
_dword Path::SearchDirSeparationIndexL2R( StringPtrType path )
{
 _dword i = path.SearchL2R( '\\' );
 if ( i == -1 )
 {
  i = path.SearchL2R( '/' );
 }
 else
 {
  _dword j = path.SearchL2R( '/' );
  if ( j != -1 )
   i = Math::Min( i, j );
 }

 return i;
}

template< typename StringPtrType >
_dword Path::SearchDirSeparationIndexR2L( StringPtrType path )
{
 _dword i = path.SearchR2L( '\\' );
 if ( i == -1 )
 {
  i = path.SearchR2L( '/' );
 }
 else
 {
  _dword j = path.SearchR2L( '/' );
  if ( j != -1 )
   i = Math::Max( i, j );
 }

 return i;
}

template< typename StringType, typename StringPtrType >
StringType Path::GetFileName( StringPtrType path, _ubool extension )
{
 // Search for the file name
 _dword i = SearchDirSeparationIndexR2L( path );

 // Get the extension name
 _dword j = -1;
 if ( extension == _false )
 {
  j = path.SearchR2L( '.' );

  // Prevent the '.' is on the left of sub-string
  if ( i != -1 && j < i )
   j = -1;
 }

 // Calculate the size of string to be copy
 _dword length = j == -1 ? path.GetLength( ) - i - 1 : j - i - 1;

 // Copy the file name
 StringType string;
 string.CopyString( path.Str( ) + (i + 1), length );

 return string;
}

template< typename StringType, typename StringPtrType >
StringType Path::GetExtension( StringPtrType path )
{
 _dword i = path.SearchR2L( '.' );

 // Calculate the size of string to be copy
 _dword length = i == -1 ? 0 : path.GetLength( ) - i - 1;

 // Copy the extension name
 StringType string;
 string.CopyString( path.Str( ) + (i + 1), length );

 return string;
}

template< typename StringType, typename StringPtrType >
StringType Path::RemoveExtension( StringPtrType path )
{
 _dword length = path.SearchR2L( '.' );
 if ( length == 0 || length == -1 )
  return path;

 // Copy string without extension name
 StringType string;
 string.CopyString( path.Str( ), length );

 return string;
}

template< typename StringType, typename StringPtrType >
StringType Path::ReplaceExtension( StringPtrType path, StringPtrType dot, StringPtrType extension )
{
 return RemoveExtension( path ) + dot + extension;
}

template< typename StringType, typename StringPtrType >
StringType Path::GetPathRoot( StringPtrType path )
{
 // Search for the directory separation character from left to right
 _dword i = SearchDirSeparationIndexL2R( path );

 // Calculate the size of string to be copy
 _dword length = i == -1 ? 0 : i;

 // Copy the path name
 StringType string;
 string.CopyString( path.Str( ), length );

 return string;
}

template< typename StringType, typename StringPtrType >
StringType Path::GetChildPathRoot( StringPtrType path )
{
 // Search for the directory separation character from left to right
 _dword i = SearchDirSeparationIndexL2R( path );
 if ( i == -1 )
  return StringType( );

 // Copy the path name
 return path.SubString( i + 1 );
}

template< typename StringType, typename StringPtrType >
StringType Path::GetDirectoryName( StringPtrType path )
{
 // Search for the directory separation character from right to left
 _dword i = SearchDirSeparationIndexR2L( path );

 // Calculate the size of string to be copy
 _dword length = i == -1 ? 0 : i;

 // Copy the path name
 StringType string;
 string.CopyString( path.Str( ), length );

 return string;
}

template< typename StringType, typename StringPtrType >
StringType Path::GetParentDirectoryName( StringPtrType path )
{
 return GetFileName< StringType, StringPtrType >( GetDirectoryName< StringType, StringPtrType >( path ), _true );
}

template< typename StringType, typename StringPtrType >
StringType Path::GetRootURLAddress( StringPtrType path, StringPtrType protocol_head_string, StringPtrType split_char, StringPtrType trim_char )
{
 Array< StringType > protocol_head_strings;
 StringFormatter::SplitString( protocol_head_string, protocol_head_strings, split_char, trim_char );

 for ( _dword i = 0; i < protocol_head_strings.Number( ); i ++ )
 {
  if ( path.StartsWith( protocol_head_strings[i] ) == _false )
   continue;

  return GetPathRoot< StringType, StringPtrType >( path.SubString( protocol_head_strings[i].GetLength( ) ) );
 }

 return StringType( );
}

template< typename StringType, typename StringPtrType >
StringType Path::GetSubURLAddress( StringPtrType path, StringPtrType protocol_head_string, StringPtrType split_char, StringPtrType trim_char )
{
 Array< StringType > protocol_head_strings;
 StringFormatter::SplitString( protocol_head_string, protocol_head_strings, split_char, trim_char );

 for ( _dword i = 0; i < protocol_head_strings.Number( ); i ++ )
 {
  if ( path.StartsWith( protocol_head_strings[i] ) == _false )
   continue;

  StringType url_root  = GetPathRoot< StringType, StringPtrType >( path.SubString( protocol_head_strings[i].GetLength( ) ) );
  StringType url_address = path.SubString( protocol_head_strings[i].GetLength( ) + url_root.GetLength( ) + 1 );

  return url_address;
 }

 return StringType( );
}

template< typename StringType, typename StringPtrType >
_ubool Path::IsIPAddress( StringPtrType url, StringPtrType split_char, StringPtrType trim_char )
{
 Array< StringType > strings;
 if ( StringFormatter::SplitString( url, strings, split_char, trim_char ) != 4 )
  return _false;

 for ( _dword i = 0; i < strings.Number( ); i ++ )
 {
  if ( StringFormatter::IsIntegerNumber( strings[i] ) == _false )
   return _false;
 }

 return _true;
}

template< typename StringType, typename StringPtrType >
StringType Path::BuildFilePath( StringPtrType path, StringPtrType filename, StringPtrType trim_strings )
{
 if ( path.IsEmpty( ) )
  return filename;

 if ( filename.IsEmpty( ) )
  return path;

 StringType combined_path = path;
 combined_path.TrimRight( trim_strings );

 StringType combined_filename = filename;
 combined_filename.TrimLeft( trim_strings );

 combined_path += '/' + combined_filename;
 combined_path.ReplaceAll( '\\', '/' );

 return combined_path;
}

template< typename StringType, typename StringPtrType >
StringType Path::GetRelativePath( StringPtrType patha, StringPtrType pathb )
{
 if ( patha.IsEmpty( ) || pathb.IsEmpty( ) )
  return StringType( );

 StringType path1 = Path::NormalizedPathName( patha );
 StringType path2 = Path::NormalizedPathName( pathb );
 if ( path2.EndsWith( '/' ) == _false )
  path2 += '/';

 _dword number = 0;

 while ( _true )
 {
  if ( path1.StartsWith( path2 ) )
  {
   StringType result = '/';

   if ( number != 0 )
   {
    for ( _dword i = 0; i < number - 1; ++ i )
    {
     result += '.';
     result += '.';
     result += '/';
    }
   }

   StringType temp = path1.SubString( path2.GetLength( ), path1.GetLength( ) - path2.GetLength( ) );
   temp.TrimLeft( '/' );

   result += temp;
   return result;
  }

  path2.SubString( 0, path2.GetLength( ) - 1 );
  _dword seperation = SearchDirSeparationIndexR2L( path2 );
  if ( seperation == -1 )
   break;

  StringType temp = path2.SubString( 0, seperation );
  path2 = temp;

  number ++;
 }

 return path1;
}

template< typename StringType, typename StringPtrType >
StringType Path::NormalizedFileName( StringPtrType filename )
{
 StringType string = filename;
 string.TrimLeft( '\t' );
 string.TrimLeft( '\\' );
 string.TrimLeft( '/' );
 string.TrimLeft( ' ' );

 for ( _dword i = 0; string[i] != 0; i ++ )
 {
  if ( string[i] == ':' || string[i] == '/' || string[i] == '\\' )
   string[i] = '_';
 }

 return string;
}

template< typename StringType, typename StringPtrType >
StringType Path::NormalizedPathName( StringPtrType pathname )
{
 StringType string = pathname;
 string.TrimLeft( '\t' );
 string.TrimLeft( '\\' );
 string.TrimLeft( '/' );
 string.TrimLeft( ' ' );

 for ( _dword i = 0; string[i] != 0; i ++ )
 {
  if ( string[i] == ':' )
   string[i] = '_';
  else if ( string[i] == '\\' )
   string[i] = '/';
 }

 return string;
}

template< typename StringType, typename StringPtrType >
StringType Path::CleanupPath( StringPtrType pathname )
{
 StringType string = pathname;

 for ( _int i = 0; string[i] != 0; )
 {
  // Check whether it's backward path string
  if ( EGE_IS_SPLIT_CHAR( string[i] ) && string[i + 1] == '.' && string[i + 2] == '.' && EGE_IS_SPLIT_CHAR( string[i + 3] ) )
  {
   _ubool remove_flag = _false;

   // Find the parent directory 
   for ( _int j = i - 1; j >= 0; j -- )
   {
    if ( EGE_IS_SPLIT_CHAR( string[j] ) && string[j + 1] != '.' && string[j + 2] != '.' )
    {
     // Get the remove string length ( + '..\' )
     _dword length = ( i - j ) + 3;

     // Remove parent path
     string.Remove( j, length );
     i = j;

     remove_flag = _true;
     break;
    }
   }

   if ( remove_flag )
    continue;
  }

  i ++;
 }

 return string;
}

template< typename StringPtrType >
_ubool Path::IsPathString( StringPtrType string )
{
 if ( string.SearchL2R( '/' ) != -1 || string.SearchL2R( '\\' ) != -1 )
  return _true;

 return _false;
}

template< typename StringPtrType >
_ubool Path::IsPathRooted( StringPtrType string )
{
 _dword length = string.GetLength( );
 if ( length > 1 )
 {
   if ( string[0] == '/' || string[0] == '\\' )
   return _true;
 
  if ( string[1] == ':' )
  {
   if ( string[0] >= 'a' && string[0] <= 'z' )
    return _true;
   if ( string[0] >= 'A' && string[0] <= 'Z' )
    return _true;
  }
 }

 return _false;
}

AString Path::GetFileName( AStringPtr path, _ubool extension )
{
 return GetFileName< AString, AStringPtr >( path, extension );
}

UString Path::GetFileNameU( UStringPtr path, _ubool extension )
{
 return GetFileName< UString, UStringPtr >( path, extension );
}

WString Path::GetFileName( WStringPtr path, _ubool extension )
{
 return GetFileName< WString, WStringPtr >( path, extension );
}

AString Path::GetExtension( AStringPtr path )
{
 return GetExtension< AString, AStringPtr >( path );
}

UString Path::GetExtensionU( UStringPtr path )
{
 return GetExtension< UString, UStringPtr >( path );
}

WString Path::GetExtension( WStringPtr path )
{
 return GetExtension< WString, WStringPtr >( path );
}

AString Path::ReplaceExtension( AStringPtr path, AStringPtr extension )
{
 return ReplaceExtension< AString, AStringPtr >( path, ".", extension );
}

WString Path::ReplaceExtension( WStringPtr path, WStringPtr extension )
{
 return ReplaceExtension< WString, WStringPtr >( path, L".", extension );
}

AString Path::RemoveExtension( AStringPtr path )
{
 return RemoveExtension< AString, AStringPtr >( path ); 
}

WString Path::RemoveExtension( WStringPtr path )
{
 return RemoveExtension< WString, WStringPtr >( path );
}

AString Path::GetPathRoot( AStringPtr path )
{
 return GetPathRoot< AString, AStringPtr >( path );
}

WString Path::GetPathRoot( WStringPtr path )
{
 return GetPathRoot< WString, WStringPtr >( path );
}

AString Path::GetChildPathRoot( AStringPtr path )
{
 return GetChildPathRoot< AString, AStringPtr >( path );
}

WString Path::GetChildPathRoot( WStringPtr path )
{
 return GetChildPathRoot< WString, WStringPtr >( path );
}

AString Path::GetDirectoryName( AStringPtr path )
{
 return GetDirectoryName< AString, AStringPtr >( path );
}

WString Path::GetDirectoryName( WStringPtr path )
{
 return GetDirectoryName< WString, WStringPtr >( path );
}

AString Path::GetParentDirectoryName( AStringPtr path )
{
 return GetParentDirectoryName< AString, AStringPtr >( path );
}

WString Path::GetParentDirectoryName( WStringPtr path )
{
 return GetParentDirectoryName< WString, WStringPtr >( path );
}

AString Path::GetRootURLAddress( AStringPtr path, AStringPtr protocol_head_string )
{
 return GetRootURLAddress< AString, AStringPtr >( path, protocol_head_string, "|", " \t" );
}

UString Path::GetRootURLAddress( UStringPtr path, UStringPtr protocol_head_string )
{
 return GetRootURLAddress< UString, UStringPtr >( path, protocol_head_string, "|", " \t" );
}

WString Path::GetRootURLAddress( WStringPtr path, WStringPtr protocol_head_string )
{
 return GetRootURLAddress< WString, WStringPtr >( path, protocol_head_string, L"|", L" \t" );
}

AString Path::GetSubURLAddress( AStringPtr path, AStringPtr protocol_head_string )
{
 return GetSubURLAddress< AString, AStringPtr >( path, protocol_head_string, "|", " \t" );
}

UString Path::GetSubURLAddress( UStringPtr path, UStringPtr protocol_head_string )
{
 return GetSubURLAddress< UString, UStringPtr >( path, protocol_head_string, "|", " \t" );
}

WString Path::GetSubURLAddress( WStringPtr path, WStringPtr protocol_head_string )
{
 return GetSubURLAddress< WString, WStringPtr >( path, protocol_head_string, L"|", L" \t" );
}

_ubool Path::IsIPAddress( AStringPtr url )
{
 return IsIPAddress< AString, AStringPtr >( url, ".", " \t" );
}

_ubool Path::IsIPAddress( UStringPtr url )
{
 return IsIPAddress< UString, UStringPtr >( url, ".", " \t" );
}

_ubool Path::IsIPAddress( WStringPtr url )
{
 return IsIPAddress< WString, WStringPtr >( url, L".", L" \t" );
}

_ubool Path::IsHTTPProtocol( AStringPtr url )
{
 if ( url.StartsWith( "http://" ) )
  return _true;

 if ( url.StartsWith( "https://" ) )
  return _true;

 return _false;
}

_ubool Path::IsHTTPProtocol( UStringPtr url )
{
 if ( url.StartsWith( "http://" ) )
  return _true;

 if ( url.StartsWith( "https://" ) )
  return _true;

 return _false;
}

_ubool Path::IsHTTPProtocol( WStringPtr url )
{
 if ( url.StartsWith( L"http://" ) )
  return _true;

 if ( url.StartsWith( L"https://" ) )
  return _true;

 return _false;
}

AString Path::BuildFilePath( AStringPtr path, AStringPtr filename )
{
 return BuildFilePath< AString, AStringPtr >( path, filename, "\\/" );
}

UString Path::BuildFilePathU( UStringPtr path, UStringPtr filename )
{
 return BuildFilePath< UString, UStringPtr >( path, filename, "\\/" );
}

WString Path::BuildFilePath( WStringPtr path, WStringPtr filename )
{
 return BuildFilePath< WString, WStringPtr >( path, filename, L"\\/" );
}

_ubool Path::DoesMatchExtension( AStringPtr filename, AStringPtr extension_list, _ubool ignorecase )
{
 if ( filename.IsEmpty( ) || extension_list.IsEmpty( ) )
  return _false;

 _charw filename_unicode[1024];
 Platform::AnsiToUtf16( filename_unicode, 1024, filename.Str( ) );

 _charw extension_list_unicode[1024];
 Platform::AnsiToUtf16( extension_list_unicode, 1024, extension_list.Str( ) );

 return DoesMatchExtension( filename_unicode, extension_list_unicode, ignorecase );
}

_ubool Path::DoesMatchExtension( WStringPtr filename, WStringPtr extension_list, _ubool ignorecase )
{
 if ( filename.IsEmpty( ) || extension_list.IsEmpty( ) )
  return _false;

 // Get the extension of file name
 WString extension_of_file = Path::GetExtension( filename );
 if ( extension_of_file.IsEmpty( ) )
  return _false; // We don't have extension name of file

 // Split the extension list
 FixedArray< WString, 128 > extensions;
 if ( StringFormatter::SplitString( extension_list, extensions, L",|", L" \t*." ) == 0 )
  return _false; // We don't have any extensions to check

 // Check the extension name
 for ( _dword i = 0; i < extensions.Number( ); i ++ )
 {
  if ( extensions[i].IsEqual( extension_of_file, ignorecase ) )
   return _true;
 }

 return _false;
}

AString Path::GetRelativePath( AStringPtr patha, AStringPtr pathb )
{
 return GetRelativePath< AString, AStringPtr >( patha, pathb );
}

WString Path::GetRelativePath( WStringPtr patha, WStringPtr pathb )
{
 return GetRelativePath< WString, WStringPtr >( patha, pathb );
}

AString Path::NormalizedFileName( AStringPtr string )
{
 return NormalizedFileName< AString, AStringPtr >( string );
}

WString Path::NormalizedFileName( WStringPtr string )
{
 return NormalizedFileName< WString, WStringPtr >( string );
}

AString Path::NormalizedPathName( AStringPtr string )
{
 return NormalizedPathName< AString, AStringPtr >( string );
}

WString Path::NormalizedPathName( WStringPtr string )
{
 return NormalizedPathName< WString, WStringPtr >( string );
}

AString Path::CleanupPath( AStringPtr string )
{
 return CleanupPath< AString, AStringPtr >( string );
}

WString Path::CleanupPath( WStringPtr string )
{
 return CleanupPath< WString, WStringPtr >( string );
}

_ubool Path::IsPathString( AStringPtr string )
{
 return IsPathString< AStringPtr >( string );
}

_ubool Path::IsPathString( WStringPtr string )
{
 return IsPathString< WStringPtr >( string );
}

_ubool Path::IsPathRooted( AStringPtr string )
{
 return IsPathRooted< AStringPtr >( string );
}

_ubool Path::IsPathRooted( WStringPtr string )
{
 return IsPathRooted< WStringPtr >( string );
}

}