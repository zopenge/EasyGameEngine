//! @file     IOSPlatform.h
//! @author   LiCode
//! @version  1.1.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IIOS_PlatformModule
//----------------------------------------------------------------------------

class IIOS_PlatformModule
{
public:
	//!	Initialize.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool Initialize( ) PURE;
	//!	Finalize.
	//!	@param		none.
	//!	@return		none.
	virtual _void Finalize( ) PURE;

	//!	Convert string form ANSI to UTF-16.
	//!	@param		buffer		The UTF-16 string buffer.
	//!	@param		size		The UTF-16 string buffer size in bytes.
	//!	@param		string		The ANSI string buffer.
	//!	@param		number		The number of ANSI string in bytes, do not contains '\0' character size.
	//!	@return		The UTF-16 string buffer size in bytes, do not contains '\0' character size.
	virtual _dword AnsiToUtf16( _charw* buffer, _dword size, const _chara* string, _dword number ) PURE;
	//!	Convert string form UTF-16 to ANSI.
	//!	@param		buffer		The ANSI string buffer.
	//!	@param		size		The ANSI string buffer size in bytes.
	//!	@param		string		The UTF-16 string buffer.
	//!	@param		number		The number of UTF-16 string in bytes, do not contains '\0' character size.
	//!	@return		The ANSI string buffer size in bytes, do not contains '\0' character size.
	virtual _dword Utf16ToAnsi( _chara* buffer, _dword size, const _charw* string, _dword number ) PURE;
	//!	Convert string form UTF-8 to UTF-16.
	//!	@param		buffer		The UTF-16 string buffer.
	//!	@param		size		The UTF-16 string buffer size in bytes.
	//!	@param		string		The UTF-8 string buffer.
	//!	@param		number		The number of UTF-8 string in bytes, do not contains '\0' character size.
	//!	@return		The UTF-16 string buffer size in bytes, do not contains '\0' character size.
	virtual _dword Utf8ToUtf16( _charw* buffer, _dword size, const _chara* string, _dword number ) PURE;
	//!	Convert string form UTF-16 to UTF-8.
	//!	@param		buffer		The UTF-8 string buffer.
	//!	@param		size		The UTF-8 string buffer size in bytes.
	//!	@param		string		The UTF-16 string buffer.
	//!	@param		number		The number of UTF-16 string in bytes, do not contains '\0' character size.
	//!	@return		The UTF-8 string buffer size in bytes, do not contains '\0' character size.
	virtual _dword Utf16ToUtf8( _chara* buffer, _dword size, const _charw* string, _dword number ) PURE;
	
	//!	Output log in ANSI format.
	//!	@param		buffer		The ANSI string buffer.
	//!	@return		none.
	virtual _void LogA( const _chara* buffer ) PURE;
	//!	Output log in UTF-16 format.
	//!	@param		buffer		The UTF-16 string buffer.
	//!	@return		none.
	virtual _void LogW( const _charw* buffer ) PURE;

	//!	Create auto-release pool.
	//!	@param		none.
	//!	@return		The handle of auto-release pool.
	virtual _handle CreateAutoReleasePool( ) PURE;
	//!	Release auto-release pool.
	//!	@param		pool	The handle of auto-release pool.
	//!	@return		none.
	virtual _void ReleaseAutoReleasePool( _handle pool ) PURE;

	//!	Global allocate.
	//!	@param		size	The size in bytes.
	//!	@return		The address of allocated memory.
	virtual _void* GlobalAlloc( _dword size ) PURE;
	//!	Global re-allocate.
	//!	@param		pointer	The allocated memory address.
	//!	@param		size	The size in bytes.
	//!	@return		The address of re-allocated memory.
	virtual _void* GlobalReAlloc( _void* pointer, _dword size ) PURE;
	//!	Free memory.
	//!	@param		pointer	The allocated memory address.
	//!	@return		The address of re-allocated memory.
	virtual _void GlobalFree( _void* pointer ) PURE;

	//!	Get the file attributes.
	//!	@param		filename	The file name.
	//!	@param		attributes	The file attributes, @see _FILE_ATTRIBUTE.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool GetFileAttributes( const _charw* filename, _dword& attributes ) PURE;
	//!	Get the document path in domains.
	//!	@param		path		The string buffer to receive document path info.
	//!	@param		length		The max length of string buffer.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool GetDocumentPathInDomains( _charw* path, _dword length ) PURE;
	//!	Enumerates resources of a specified type within a binary module. 
	//!	@param		funcpointer		A pointer to the callback function to be called for each enumerated resource name or ID.
	//!	@param		parameter		An application-defined value passed to the callback function.
	//! @return		True indicates success false indicates failure.
	virtual _ubool EnumResourceNames( const _charw* sub_dir_name, Platform::OnEnumResNameProc funcpointer, _void* parameter ) PURE;

	//!	Load resource path from main bundle by relative name.
	//!	@param		relative_name	The relative name.
	//!	@return		The file handle.
	virtual _handle LoadMainBundleResource( const _charw* relative_name ) PURE;
	//!	Get the resource size in bytes from main bundle.
	//!	@param		file			The file handle.
	//!	@return		The resource size in bytes.
	virtual _dword GetSizeOfMainBundleResource( _handle file ) PURE;
	//!	Get the resource data from main bundle.
	//!	@param		file			The file handle.
	//!	@return		The resource data.
	virtual const _byte* GetDataOfMainBundleResource( _handle file ) PURE;
	//!	Unload the resource from main bundle.
	//!	@param		file			The file handle.
	//!	@return		none.
	virtual _void UnloadMainBundleResource( _handle file ) PURE;
};

//!	Get the IOS-Platform module.
EGE_EXTERNAL IIOS_PlatformModule* GetIOSPlatformModule( );

}