//! @file     TPlatform.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TPlatform
//----------------------------------------------------------------------------

template< typename Type >
class TPlatform : public TObject< Type >
{
protected:
	//!	The custom internal directory
	WString					mCustomInternalDirectory;
	//!	The custom external directory
	WString					mCustomExternalDirectory;
	//!	The custom document directory
	WString					mCustomDocumentDirectory;

	//!	The current working directory
	WString					mWorkingDir;
	//!	The current working archive
	IArchiveRef				mWorkingArchive;

	//!	The device info
	PlatformDeviceInfo		mDeviceInfo;

protected:
	//!	Get CPU features.
	_dword GetCPUFeatures( ) const;
	//!	Check CPU features.
	_ubool CheckCPUFeatures( _dword cpu_features ) const;

protected:
	TPlatform( );
	virtual ~TPlatform( );

// IPlatform Interface
public:
	virtual _ubool						Initialize( ) override;
	virtual _void						Finalize( ) override;

	virtual WStringPtr					GetWorkingDirectory( ) const override;
	virtual _ubool						SetWorkingDirectory( WStringPtr working_dir ) override;

	virtual _ubool						AddPatchDirectory( WStringPtr patch_dir ) override;
	virtual _ubool						RemovePatchDirectory( WStringPtr patch_dir ) override;

	virtual IArchive*					GetWorkingArchive( ) override;

	virtual const PlatformDeviceInfo&	GetDeviceInfo( ) override;

	virtual WString					GetIMSI( ) const override;

	virtual _ubool						CleanTempDirectory( ) override;
	virtual WString					GetTempDirectory( ) const override;
	virtual _ubool						CreateTempFileInTempDirectory( WStringPtr relative_path, WStringPtr extension_name, const _byte* buffer, _dword size, WString& filename ) override;

	virtual WString					GetAbsoluteDirectory( WStringPtr path ) override;

	virtual _void						SetCurrentDirectory( WStringPtr path ) override;
	virtual WString					GetCurrentDirectory( ) const override;
	virtual _void						SetDocumentDirectory( WStringPtr path ) override;
	virtual WString					GetDocumentDirectory( ) const override;
	virtual _void						SetInternalDirectory( WStringPtr path ) override;
	virtual WString					GetInternalDirectory( ) const override;
	virtual _void						SetExternalDirectory( WStringPtr path ) override;
	virtual WString					GetExternalDirectory( ) const override;

	virtual _ubool						IsSameFile( WStringPtr filename_1, WStringPtr filename_2 ) const override;

	virtual _ubool						RunProcess( WStringPtr modulename, WStringPtr cmdline, _dword creationflags, WStringPtr workdir, _ubool nodebugheap = _true, _ubool fastmode = _false, _dword* exit_code = _null ) override;

	virtual Array< DwordRange >			GetLanguageUTF16CodeRange( _LANG language ) const override;

	virtual _ubool						GetSystemFontFiles( FileInfoArray& files ) override;
	virtual _ubool						GetSystemFontFiles( FileInfoArray& files, const DwordRange& utf16_code_range, _dword max_number = -1 ) override;
	virtual _ubool						GetSystemFontFiles( FileInfoArray& files, const Array< DwordRange >& utf16_code_ranges, _dword max_number = -1 ) override;

	virtual _ubool						RegisterExportFunction( AStringPtr path, AStringPtr func_name, AStringPtr func_decl, _void* func_pointer ) override;

	virtual _ubool						RunProcess( WStringPtr cmdline ) override;
};

//----------------------------------------------------------------------------
// TPlatform Implementation
//----------------------------------------------------------------------------

template< typename Type >
TPlatform< Type >::TPlatform( )
{
}

template< typename Type >
TPlatform< Type >::~TPlatform( )
{

}

template< typename Type >
_dword TPlatform< Type >::GetCPUFeatures( ) const
{
	// Get the CPU cpu_features
	_dword cpu_features = Platform::GetCPUFeatures( );

	// Show features
	WString string;
	for ( _dword i = 0; i < 31 && cpu_features != 0; i ++, cpu_features >>= 1 )
	{
		if ( cpu_features & 1 )
		{
			switch ( 1 << i )
			{
				case _CPU_FEATURE_SSSE3:		string += L"SSE3;"; break;
				case _CPU_FEATURE_POPCNT:		string += L"POPCNT;"; break;
				case _CPU_FEATURE_MOVBE:		string += L"MOVBE;"; break;
				case _CPU_FEATURE_ARMv7:		string += L"ARMv7;"; break;
				case _CPU_FEATURE_VFPv3:		string += L"VFPv3;"; break;
				case _CPU_FEATURE_NEON:			string += L"NEON;"; break;
				case _CPU_FEATURE_LDREX_STREX:	string += L"LDREX_STREX;"; break;
				default:
					break;
			}
		}
	}

	OUTPUT_DEBUG_STRING( FORMAT_WSTRING_1( L"The CPU features: %s\n", string.Str( ) ) );

	return cpu_features;
}

template< typename Type >
_ubool TPlatform< Type >::CheckCPUFeatures( _dword cpu_features ) const
{
	// If we enable NEON instructions then we need to check whether CPU support or not
#if (_USE_NEON_ == 1)
	if ( ( cpu_features & _CPU_FEATURE_NEON ) == 0 )
	{
		OUTPUT_DEBUG_STRING( L"The CPU does not support NEON instructions\n" );
		return _false;
	}
#endif

	return _true;
}

template< typename Type >
_ubool TPlatform< Type >::Initialize( )
{
	_dword cpu_features = GetCPUFeatures( );

	if ( CheckCPUFeatures( cpu_features  ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_void TPlatform< Type >::Finalize( )
{
	mCustomInternalDirectory.Clear( _true );
	mCustomExternalDirectory.Clear( _true );
	mCustomDocumentDirectory.Clear( _true );

	mWorkingDir.Clear( _true );

	mWorkingArchive.Clear( );

	mDeviceInfo = PlatformDeviceInfo( );
}

template< typename Type >
WStringPtr TPlatform< Type >::GetWorkingDirectory( ) const
{
	return mWorkingDir;
}

template< typename Type >
_ubool TPlatform< Type >::SetWorkingDirectory( WStringPtr working_dir )
{
	mWorkingDir = working_dir;
	WLOG_TRACE_1( L"Set '%s' as working directory", working_dir.Str( ) );

	// Create working directory archive
	if ( mWorkingArchive.IsNull( ) )
	{
		mWorkingArchive = GetInterfaceFactory( )->CreatePEResArchive( working_dir );
		if ( mWorkingArchive.IsNull( ) )
		{
			WLOG_ERROR_1( L"Create '%s' PERes archive as working directory failed", working_dir.Str( ) );
			return _false;
		}
	}

	// Get the document path in domains
	_charw document[1024];
	if ( Platform::GetDocumentPathInDomains( document, 1024 ) == _false )
		return _false;

	// Create document archive
	IArchiveRef document_archive = GetInterfaceFactory( )->CreateFileArchive( document );
	if ( document_archive.IsNull( ) )
	{
		WLOG_ERROR_1( L"Create '%s' document file archive failed", (const _charw*)document );
		return _false;
	}

	// Append document archive as patch archive
	if ( mWorkingArchive->AddPatchArchive( document_archive ) == -1 )
	{
		WLOG_ERROR_1( L"Add '%s' document file archive as patch failed", (const _charw*)document );
		return _false;
	}

	return _true;
}

template< typename Type >
_ubool TPlatform< Type >::AddPatchDirectory( WStringPtr patch_dir )
{
	return _false;
}

template< typename Type >
_ubool TPlatform< Type >::RemovePatchDirectory( WStringPtr patch_dir )
{
	return _false;
}

template< typename Type >
IArchive* TPlatform< Type >::GetWorkingArchive( )
{
	return mWorkingArchive;
}

template< typename Type >
const PlatformDeviceInfo& TPlatform< Type >::GetDeviceInfo( )
{
	return mDeviceInfo;
}

template< typename Type >
WString TPlatform< Type >::GetIMSI( ) const
{
	return WString( L"" );
}

template< typename Type >
_ubool TPlatform< Type >::CleanTempDirectory( )
{
	WString temp_dir = GetPlatform( )->GetTempDirectory( );

	// Clean temp directory if exists
	if ( FileSystem::IsDirectoryExist( temp_dir ) )
	{
		WLOG_TRACE_1( L"Cleanup '%s' temporary directory ...", temp_dir.Str( ) );
		if ( FileSystem::CleanDir( temp_dir ) == _false )
		{
			WLOG_ERROR_1( L"Cleanup '%s' temporary directory failed", temp_dir.Str( ) );
			return _false;
		}

		WLOG_TRACE_1( L"Cleanup '%s' temporary directory OK", temp_dir.Str( ) );
	}
	// Create temp directory if it's not existing
	else
	{
		WLOG_TRACE_1( L"Create '%s' temporary directory ...", temp_dir.Str( ) );
		if ( FileSystem::CreateDir( temp_dir ) == _false )
		{
			WLOG_ERROR_1( L"Create '%s' temporary directory failed", temp_dir.Str( ) );
			return _false;
		}
		WLOG_TRACE_1( L"Create '%s' temporary directory OK", temp_dir.Str( ) );
	}

	return _true;
}

template< typename Type >
WString TPlatform< Type >::GetTempDirectory( ) const
{
	_charw path[1024];
	Platform::GetDocumentPathInDomains( path, 1024 );

	return Path::BuildFilePath( path, L"__temp__" );
}

template< typename Type >
_ubool TPlatform< Type >::CreateTempFileInTempDirectory( WStringPtr relative_path, WStringPtr extension_name, const _byte* buffer, _dword size, WString& filename )
{
	WString path = GetTempDirectory( );
	if ( relative_path.IsEmpty( ) == _false )
		path += L"/" + relative_path;

	if ( FileSystem::GetTempFileName( path, extension_name, filename ) == _false )
		return _false;

	if ( FileSystem::CreateFile( filename, size, buffer ) == _false )
		return _false;

	return _true;
}

template< typename Type >
WString TPlatform< Type >::GetAbsoluteDirectory( WStringPtr path )
{
	_charw abs_path[1024]; abs_path[0] = 0;
	if ( Platform::GetAbsoluteDirectory( path.Str( ), abs_path, 1024 ) == _false )
		return L"";

	WString fixed_path = abs_path;
	fixed_path.ReplaceAll( L"\\", L"/" );

	return fixed_path;
}

template< typename Type >
_void TPlatform< Type >::SetCurrentDirectory( WStringPtr path )
{
	Platform::SetCurrentDirectory( path.Str( ) );
}

template< typename Type >
WString TPlatform< Type >::GetCurrentDirectory( ) const
{
	_charw path[1024]; path[0] = 0;
	Platform::GetCurrentDirectory( path, 1024 );

	WString fixed_path = path;
	fixed_path.ReplaceAll( L"\\", L"/" );

	return fixed_path;
}

template< typename Type >
_void TPlatform< Type >::SetDocumentDirectory( WStringPtr path )
{
	mCustomDocumentDirectory = path;
}

template< typename Type >
WString TPlatform< Type >::GetDocumentDirectory( ) const
{
	if ( mCustomDocumentDirectory.IsEmpty( ) )
	{
		_charw path[1024] = {0};
		if ( Platform::GetDocumentPathInDomains( path, 1024 ) == _false )
			return WString( L"" );

		return path;
	}
	else
	{
		return mCustomDocumentDirectory;
	}
}

template< typename Type >
_void TPlatform< Type >::SetInternalDirectory( WStringPtr path )
{
	mCustomInternalDirectory = path;
}

template< typename Type >
WString TPlatform< Type >::GetInternalDirectory( ) const
{
	if ( mCustomInternalDirectory.IsEmpty( ) )
	{
		_charw path[1024] = {0};
		if ( Platform::GetInternalPathInDomains( path, 1024 ) == _false )
			return WString( L"" );

		return path;
	}
	else
	{
		return mCustomInternalDirectory;
	}
}

template< typename Type >
_void TPlatform< Type >::SetExternalDirectory( WStringPtr path )
{
	mCustomExternalDirectory = path;
}

template< typename Type >
WString TPlatform< Type >::GetExternalDirectory( ) const
{
	if ( mCustomExternalDirectory.IsEmpty( ) )
	{
		_charw path[1024] = {0};
		if ( Platform::GetExternalPathInDomains( path, 1024 ) == _false )
			return WString( L"" );

		return path;
	}
	else
	{
		return mCustomExternalDirectory;
	}
}

template< typename Type >
_ubool TPlatform< Type >::IsSameFile( WStringPtr filename_1, WStringPtr filename_2 ) const
{
	MD5Code md5_code_1;
	if ( GetInterfaceFactory( )->BuildMD5CodeFromFile( filename_1, md5_code_1 ) == _false )
		return _false;

	MD5Code md5_code_2;
	if ( GetInterfaceFactory( )->BuildMD5CodeFromFile( filename_2, md5_code_2 ) == _false )
		return _false;

	if ( md5_code_1 != md5_code_2 )
		return _false;

	return _true;
}

template< typename Type >
_ubool TPlatform< Type >::RunProcess( WStringPtr modulename, WStringPtr cmdline, _dword creationflags, WStringPtr workdir, _ubool nodebugheap, _ubool fastmode, _dword* exit_code )
{
	IProcessDebuggerRef debugger = GetInterfaceFactory( )->CreateProcessDebugger( );
	if ( debugger.IsNull( ) )
		return _false;

	if ( debugger->Run( modulename, cmdline, creationflags, workdir, nodebugheap, fastmode ) == _false )
		return _false;

	if ( exit_code != _null )
		*exit_code = debugger->GetExitCode( );

	return _true;
}

template< typename Type >
Array< DwordRange > TPlatform< Type >::GetLanguageUTF16CodeRange( _LANG language ) const
{
	Array< DwordRange > utf16_code_ranges;

	switch ( language )
	{
		case _LANG_ENG:
			utf16_code_ranges.Append( DwordRange( 0x30, 0x39 ) ); // 0~9
			utf16_code_ranges.Append( DwordRange( 0x61, 0x7A ) ); // a~z
			utf16_code_ranges.Append( DwordRange( 0x41, 0x5A ) ); // A~Z
			break;

		case _LANG_CHS:
		case _LANG_CHT:
			utf16_code_ranges.Append( DwordRange( 0x4E00, 0x9FA5 ) );
			break;

		default:
			break;
	}

	return utf16_code_ranges;
}

template< typename Type >
_ubool TPlatform< Type >::GetSystemFontFiles( FileInfoArray& files )
{
	// Get the system font path
	_charw font_path[1024] = {0};
	if ( Platform::GetSystemFontPath( font_path, 1024 ) == _false )
		return _false;

	// Open the system font directory
	FileFinder file_finder;
	if ( file_finder.Open( font_path ) == _false )
		return _false;

	// Get the font files
	FileInfo file_info;
	while ( file_finder.Walk( file_info, L"*.ttf|*.otf|*.ttc", _FILE_FINDER_ENUMERATION_FILE_ONLY, 1 ) )
	{
		files.Append( file_info );
	}

	return _true;
}

template< typename Type >
_ubool TPlatform< Type >::GetSystemFontFiles( FileInfoArray& files, const DwordRange& utf16_code_range, _dword max_number )
{
	if ( max_number == 0 )
		return _true;

	FileInfoArray font_files;
	if ( GetSystemFontFiles( font_files ) == _false )
		return _false;

	FileInfoArray filter_font_files;
	for ( _dword i = 0; i < font_files.Number( ); i ++ )
	{
		IFileStreamReaderRef file_stream_reader = GetInterfaceFactory( )->CreateFileStreamReader( font_files[i].mAbsolutePath );
		if ( file_stream_reader.IsNull( ) )
			continue;

		IFontFaceRef font_face = GetInterfaceFactory( )->CreateFontFace( _FONT_FACE_FREETYPE2, file_stream_reader );
		if ( font_face.IsNull( ) )
			continue;

		if ( font_face->HasCharacter( utf16_code_range.mMinValue ) == _false )
			continue;

		if ( font_face->HasCharacter( utf16_code_range.mMaxValue ) == _false )
			continue;

		files.Append( font_files[i] );

		if ( files.Number( ) >= max_number )
			break;
	}

	return _true;
}

template< typename Type >
_ubool TPlatform< Type >::GetSystemFontFiles( FileInfoArray& files, const Array< DwordRange >& utf16_code_ranges, _dword max_number )
{
	if ( max_number == 0 )
		return _true;

	FileInfoArray font_files;
	if ( GetSystemFontFiles( font_files ) == _false )
		return _false;

	FileInfoArray filter_font_files;
	for ( _dword i = 0; i < font_files.Number( ); i ++ )
	{
		IFileStreamReaderRef file_stream_reader = GetInterfaceFactory( )->CreateFileStreamReader( font_files[i].mAbsolutePath );
		if ( file_stream_reader.IsNull( ) )
			continue;

		IFontFaceRef font_face = GetInterfaceFactory( )->CreateFontFace( _FONT_FACE_FREETYPE2, file_stream_reader );
		if ( font_face.IsNull( ) )
			continue;

		for ( _dword j = 0; j < utf16_code_ranges.Number( ); j ++ )
		{
			const DwordRange& utf16_code_range = utf16_code_ranges[i];

			if ( font_face->HasCharacter( utf16_code_range.mMinValue ) == _false )
				continue;

			if ( font_face->HasCharacter( utf16_code_range.mMaxValue ) == _false )
				continue;

			files.Append( font_files[i] );

			if ( files.Number( ) >= max_number )
				break;
		}
	}

	return _true;
}

template< typename Type >
_ubool TPlatform< Type >::RegisterExportFunction( AStringPtr path, AStringPtr func_name, AStringPtr func_decl, _void* func_pointer )
{
	return _false;
}

template< typename Type >
_ubool TPlatform< Type >::RunProcess( WStringPtr cmdline )
{
	// Start to convert to ppm file
	_handle process_handle = _null;
	if ( Platform::CreateProcess( _null, cmdline.Str( ), _PROCESS_CREATION_NO_WINDOW, _null, &process_handle ) == _false )
	{
		WLOG_TRACE( FORMAT_WSTRING_1( L"Run processor with '%s' command line failed", cmdline.Str( ) ) );
		return _false;
	}

	// Wait for exit
	while ( Platform::IsProcessAlive( process_handle ) )
		Platform::Sleep( 100 );

	return _true;
}

}