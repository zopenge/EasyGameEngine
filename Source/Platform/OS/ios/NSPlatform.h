//! @file     NSPlatform.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosPlatformModule
//----------------------------------------------------------------------------

class iosPlatformModule : public IIOS_PlatformModule
{
	VIRTUAL_SINGLETON( iosPlatformModule )

private:
	//! The main bundle path
	WString mMainBundlePath;

// IIOS_PlatformModule Interface
public:
	virtual _ubool			Initialize( ) override;
	virtual _void			Finalize( ) override;

	virtual _dword			AnsiToUtf16( _charw* buffer, _dword size, const _chara* string, _dword number ) override;
	virtual _dword			Utf16ToAnsi( _chara* buffer, _dword size, const _charw* string, _dword number ) override;
	virtual _dword			Utf8ToUtf16( _charw* buffer, _dword size, const _chara* string, _dword number ) override;
	virtual _dword			Utf16ToUtf8( _chara* buffer, _dword size, const _charw* string, _dword number ) override;

	virtual _void			LogA( const _chara* buffer ) override;
	virtual _void			LogW( const _charw* buffer ) override;

	virtual _handle			CreateAutoReleasePool( ) override;
	virtual _void			ReleaseAutoReleasePool( _handle pool ) override;

	virtual _void*			GlobalAlloc( _dword size ) override;
	virtual _void*			GlobalReAlloc( _void* pointer, _dword size ) override;
	virtual _void			GlobalFree( _void* pointer ) override;

	virtual _ubool			GetFileAttributes( const _charw* filename, _dword& attributes ) override;
	virtual _ubool			GetDocumentPathInDomains( _charw* path, _dword length ) override;
	virtual _ubool			EnumResourceNames( const _charw* sub_dir_name, Platform::OnEnumResNameProc funcpointer, _void* parameter ) override;

	virtual _handle			LoadMainBundleResource( const _charw* relative_name ) override;
	virtual _dword			GetSizeOfMainBundleResource( _handle file ) override;
	virtual const _byte*	GetDataOfMainBundleResource( _handle file ) override;
	virtual _void			UnloadMainBundleResource( _handle file ) override;
};

}