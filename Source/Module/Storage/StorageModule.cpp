//! @file     StorageModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEStorage.h"

//----------------------------------------------------------------------------
// StorageModule Implementation
//----------------------------------------------------------------------------

StorageModule::StorageModule( ) : BaseClass( L"Storage", Version( STORAGE_FILEVER ) )
{
}

StorageModule::~StorageModule( )
{
	Finalize( );

	GetModuleManager( )->UnregisterModule( this );
}

_ubool StorageModule::SetWorkingDirectory( WStringPtr working_dir, _ubool refresh_working_dir )
{
	mWorkingDir = working_dir;
	WLOG_TRACE_1( L"Set '%s' as working directory", working_dir.Str( ) );

#ifdef _PLATFORM_WINDOWS_

	// Use local archive
	StorageLocalArchive* local_archive = new StorageLocalArchive( );
	mWorkingArchive = local_archive;

	// Add whole working directory path
	WString abs_working_dir_path = GetPlatform( )->GetAbsoluteDirectory( working_dir );
	local_archive->AddPatchDir( abs_working_dir_path, refresh_working_dir );

	// Create working directory archive
	IArchiveRef patch = GetInterfaceFactory( )->CreateFileArchive( working_dir );
	if ( patch.IsNull( ) )
	{
		WLOG_ERROR_1( L"Create '%s' file archive failed", working_dir.Str( ) );
		return _false;
	}

	// Add working directory as patch
	if ( local_archive->AddPatchArchive( patch ) == -1 )
	{
		WLOG_ERROR_1( L"Add '%s' file archive as patch failed", working_dir.Str( ) );
		return _false;
	}

	// Let module to manage it
	local_archive->Release( );

#else

	// Create working directory archive
	mWorkingArchive = GetInterfaceFactory( )->CreatePEResArchive( working_dir );
	if ( mWorkingArchive.IsNull( ) )
	{
		WLOG_ERROR_1( L"Create '%s' PERes archive as working directory failed", working_dir.Str( ) );
		return _false;
	}

#endif

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

_ubool StorageModule::Initialize( WStringPtr working_dir )
{
	WLOG_TRACE( L"Create storage module ..." );

	// Initialize working directory
	if ( SetWorkingDirectory( working_dir, _false ) == _false )
		return _false;

	WLOG_TRACE( L"Create storage module DONE" );

	return _true;
}

_void StorageModule::Finalize( )
{
	WLOG_TRACE( L"Release storage module ..." );

	WLOG_TRACE( L"Releasing working archive ..." );
	mWorkingArchive.Clear( );
	WLOG_TRACE( L"Release working archive done" );

	WLOG_TRACE( L"Release storage module DONE" );

	// Clear global modules
	gStorageModule = _null;
}

_void StorageModule::Tick( _time_t tick, _dword elapse )
{
	mWorkingArchive->Tick( tick, elapse );
}

_void StorageModule::HandleEvent( EventBase& event )
{
	switch ( event.mEventID )
	{
		case _ENGINE_EVENT_LOAD_STREAM_BY_FILE_NAME:
		{
			EngineEventLoadStreamByFileName& ev = (EngineEventLoadStreamByFileName&) event;

			ev.mStreamReader = mWorkingArchive->LoadResourceByName( ev.mFileName );
		}
		break;

		case _EVENT_AFTER_LAUNCH_APP:
		{
			EventAfterLaunchApp& ev = (EventAfterLaunchApp&) event;

#ifdef _PLATFORM_WINDOWS_
			StorageLocalArchive* local_archive = mWorkingArchive.cast_static< StorageLocalArchive >( );
			local_archive->RefreshWorkingDir( );
#endif
		}
		break;

		default:
			break;
	}
}

WStringPtr StorageModule::GetWorkingDirectory( ) const
{
	return mWorkingDir;
}

_ubool StorageModule::SetWorkingDirectory( WStringPtr working_dir )
{
	return SetWorkingDirectory( working_dir, _true );
}

_ubool StorageModule::AddPatchDirectory( WStringPtr patch_dir )
{
#ifdef _PLATFORM_WINDOWS_
	// Use local archive
	StorageLocalArchive* local_archive = mWorkingArchive.cast_static< StorageLocalArchive >( );

	// Add patch directory
	if ( local_archive->AddPatchDir( patch_dir, _true ) == _false )
		return _false;

	return _true;
#else
	return _false;
#endif
}

_ubool StorageModule::RemovePatchDirectory( WStringPtr patch_dir )
{
#ifdef _PLATFORM_WINDOWS_
	// Use local archive
	StorageLocalArchive* local_archive = mWorkingArchive.cast_static< StorageLocalArchive >( );

	// Remove patch directory
	if ( local_archive->RemovePatchDir( patch_dir ) == _false )
		return _false;

	return _true;
#else
	return _false;
#endif
}

IArchive* StorageModule::GetWorkingArchive( )
{
	return mWorkingArchive;
}
